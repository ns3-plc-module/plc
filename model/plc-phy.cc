/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 University of British Columbia, Vancouver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#include <algorithm>

#include <ns3/simulator.h>
#include <ns3/abort.h>
#include <ns3/random-variable.h>
#include <ns3/callback.h>
#include <ns3/log.h>
#include <ns3/abort.h>
#include <ns3/object-factory.h>
#include "plc-phy.h"
#include "plc-simulator-impl.h"
#include "plc-channel.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Phy");

#define PLC_PHY_LOGIC(msg)\
	do {\
		if (m_node) {\
			NS_LOG_LOGIC("PLC_Phy[" << m_node->GetName() << "]: " << msg);\
		}\
		else {\
			NS_LOG_LOGIC("PLC_Phy: " << msg);\
		}\
	} while(0)

#define PLC_PHY_FUNCTION(msg)\
	do {\
		if (m_node) {\
			NS_LOG_FUNCTION(m_node->GetName() << msg);\
		}\
		else {\
			NS_LOG_FUNCTION(msg);\
		}\
	} while(0)

#define PLC_PHY_INFO(msg)\
	do {\
		if (m_node) {\
			NS_LOG_INFO("PLC_Phy[" << m_node->GetName() << "]: " << msg);\
		}\
		else {\
			NS_LOG_INFO("PLC_Phy: " << msg);\
		}\
	} while(0)

#define PLC_PHY_DEBUG(msg)\
	do {\
		if (m_node) {\
			NS_LOG_DEBUG(m_node->GetName() << msg);\
		}\
		else {\
			NS_LOG_DEBUG(msg);\
		}\
	} while(0)

size_t
RequiredSymbols (size_t encoded_bits, ModulationAndCodingType mcs, size_t subbands)
{
	size_t bits_per_subcarrier = GetBitsPerSymbol (mcs);
	return ceil((double) encoded_bits / (subbands * bits_per_subcarrier));
}

Time
CalculateTransmissionDuration(size_t encoded_bits, ModulationAndCodingType mcs, size_t subbands)
{
	size_t num_symbols = RequiredSymbols (encoded_bits, mcs, subbands);
	NS_LOG_LOGIC("required symbols: " << num_symbols);

	return Time::FromInteger((PLC_Phy::GetSymbolDuration().GetInteger() * num_symbols), Time::GetResolution());
}

////////////////////////////// PLC_Phy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_Phy);

//Time PLC_Phy::symbol_duration = NanoSeconds(8192);
Time PLC_Phy::symbol_duration = MicroSeconds(2240);

TypeId
PLC_Phy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_Phy")
    .SetParent<Object> ()
  ;
  return tid;
}

PLC_Phy::~PLC_Phy ()
{
}

void
PLC_Phy::DoStart(void)
{
	NS_LOG_FUNCTION (this);
}

void
PLC_Phy::DoDispose ()
{
	NS_LOG_FUNCTION (this);
}

void
PLC_Phy::SetSymbolDuration(Time tSymbol)
{
	NS_LOG_FUNCTION ("Phy symbol duration set to " << tSymbol);
	symbol_duration = tSymbol;
}

Time
PLC_Phy::GetSymbolDuration (void)
{
	return symbol_duration;
}

bool
PLC_Phy::StartTx (Ptr<Packet> p)
{
	NS_LOG_FUNCTION (this << p);
	return DoStartTx (p);
}

void
PLC_Phy::StartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	NS_LOG_FUNCTION (this << p);
	DoStartRx (p, txId, rxPsd, duration, metaInfo);
}

void
PLC_Phy::RxPsdChanged (uint32_t txId, Ptr<SpectrumValue> newRxPsd)
{
	NS_LOG_FUNCTION (this << txId << newRxPsd);
	DoUpdateRxPsd (txId, newRxPsd);
}

void
PLC_Phy::SetFrameSentCallback(PLC_PhyFrameSentCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_frame_sent_callback = c;
}

void
PLC_Phy::SetReceiveSuccessCallback(PhyRxEndOkCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_receive_success_cb = c;
}

void
PLC_Phy::SetReceiveErrorCallback(PhyRxEndErrorCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_receive_error_cb = c;
}

void
PLC_Phy::NotifyFrameSent (void)
{
	if (!m_frame_sent_callback.IsNull())
	{
		m_frame_sent_callback();
	}
}

PLC_ChannelTransferImpl *
PLC_Phy::GetChannelTransferImpl (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	return DoGetChannelTransferImpl(rxPhy);
}

Ptr<PLC_TransferBase>
PLC_Phy::GetChannelTransferVector(Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	PLC_ChannelTransferImpl *cti = GetChannelTransferImpl(rxPhy);
	NS_ASSERT_MSG (cti, "No channel to rxPhy " << rxPhy);
	return cti->GetChannelTransferVector();
}


////////////////////////////// PLC_HalfDuplexOfdmPhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_HalfDuplexOfdmPhy);

Time PLC_HalfDuplexOfdmPhy::guard_interval_duration = MicroSeconds(20);

TypeId
PLC_HalfDuplexOfdmPhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_HalfDuplexOfdmPhy")
	.SetParent<PLC_Phy> ()
  ;
  return tid;
}

PLC_HalfDuplexOfdmPhy::PLC_HalfDuplexOfdmPhy()
{
	PLC_PHY_FUNCTION(this);
	m_incoming_packet = 0;
	m_state = IDLE;
}

PLC_HalfDuplexOfdmPhy::~PLC_HalfDuplexOfdmPhy()
{
	PLC_PHY_FUNCTION(this);
}

void
PLC_HalfDuplexOfdmPhy::DoStart(void)
{
	PLC_PHY_FUNCTION(this);
	m_state = IDLE;
	PLC_Phy::DoStart();
}

void
PLC_HalfDuplexOfdmPhy::DoDispose ()
{
	m_txImpedance = 0;
	m_rxImpedance = 0;
	m_outlet = 0;
	m_txPsd = 0;
 	m_txInterface = 0;
 	m_rxInterface = 0;
	m_shuntImpedance = 0;
	m_txImpedance = 0;
	m_rxImpedance = 0;
	m_eqRxImpedance = 0;
	m_eqTxImpedance = 0;
	m_incoming_packet = 0;

	PLC_Phy::DoDispose();
}

PLC_ChannelTransferImpl *
PLC_HalfDuplexOfdmPhy::DoGetChannelTransferImpl (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	NS_ASSERT_MSG(rxPhy->GetInstanceTypeId().IsChildOf(PLC_HalfDuplexOfdmPhy::GetTypeId()), "RX Phy not of type PLC_HalfDuplexOfdmPhy");
	Ptr<PLC_RxInterface> rxIf = (StaticCast<PLC_HalfDuplexOfdmPhy, PLC_Phy> (rxPhy))->GetRxInterface ();
	return GetTxInterface()->GetChannelTransferImpl(PeekPointer(rxIf));
}

void
PLC_HalfDuplexOfdmPhy::SetGuardIntervalDuration (Time duration)
{
	guard_interval_duration = duration;
}

Time
PLC_HalfDuplexOfdmPhy::GetGuardIntervalDuration (void)
{
	return guard_interval_duration;
}

void
PLC_HalfDuplexOfdmPhy::CreateInterfaces (Ptr<PLC_Outlet> outlet, Ptr<SpectrumValue> txPsd, Ptr<PLC_Impedance> rxImpedance, Ptr<PLC_Impedance> txImpedance)
{
	m_node = outlet->GetNode();

	NS_ASSERT_MSG(m_node, "PLC_HalfDuplexOfdmPhy::CreateInterfaces: outlet has to be bound to a PLC_Node");
	m_outlet = outlet;

	Ptr<PLC_Graph> graph = m_node->GetGraph();
	NS_ASSERT_MSG(graph, "PLC_HalfDuplexOfdmPhy::CreateInterfaces: PLC_Node the outlet is located on is not attached to a PLC_Graph");

	Ptr<PLC_Channel> ch = graph->GetChannel();
	NS_ASSERT_MSG(ch, "PLC_HalfDuplexOfdmPhy::CreateInterfaces: the graph the outlet's node is connected to is not bound to a PLC_Channel");

	if (!m_txInterface)
	{
		m_txInterface = CreateObject<PLC_TxInterface> (m_node, txPsd->GetSpectrumModel());
	}
	m_txInterface->SetPhy(Ptr<PLC_Phy> (this));

	if (!m_rxInterface)
	{
		m_rxInterface = CreateObject<PLC_RxInterface> (m_node, txPsd->GetSpectrumModel());
	}
	m_rxInterface->SetPhy(Ptr<PLC_Phy> (this));
	m_rxInterface->SetOutlet(m_outlet);

	m_txInterface->SetIdx(ch->AddTxInterface(m_txInterface));
	m_rxInterface->SetIdx(ch->AddRxInterface(m_rxInterface));

	if (m_node->GetImpedancePtr())
	{
		NS_LOG_LOGIC("Node has shunt impedance");
		m_shuntImpedance = m_node->GetImpedancePtr();
	}

	SetTxPowerSpectralDensity(txPsd);
	SetRxImpedance(rxImpedance);
	SetTxImpedance(txImpedance);
	ComputeEquivalentImpedances();
}

Ptr<PLC_TxInterface> PLC_HalfDuplexOfdmPhy::GetTxInterface (void)
{
	PLC_LOG_FUNCTION(this);
	NS_ASSERT_MSG (m_txInterface, "TX interface not yet created!");
	return m_txInterface;
}

Ptr<PLC_RxInterface> PLC_HalfDuplexOfdmPhy::GetRxInterface (void)
{
	PLC_LOG_FUNCTION(this);
	return m_rxInterface;
}


void
PLC_HalfDuplexOfdmPhy::SetTxPowerSpectralDensity (Ptr<SpectrumValue> txPsd)
{
	NS_ASSERT_MSG (m_txInterface, "Phy interfaces have to be created first before changing txPsd");
	if (m_txPsd)
		NS_ASSERT_MSG (txPsd->GetSpectrumModel() == m_txPsd->GetSpectrumModel(), "PLC_HalfDuplexOfdmPhy::SetTxPowerSpectralDensity: new txPsd uses different SpectrumModel");

	m_txPsd = txPsd;
	m_numSubcarriers = m_txPsd->GetSpectrumModel()->GetNumBands();
}

void
PLC_HalfDuplexOfdmPhy::SetShuntImpedance(Ptr<PLC_Impedance> shuntImpedance)
{
	PLC_PHY_FUNCTION(this << shuntImpedance);

#ifdef PLC_USE_IMPEDANCE_HASHING
	if (shuntImpedance)
	{
		m_shuntImpedance = shuntImpedance->Copy();
	}
	else
	{
		m_shuntImpedance = NULL;
	}
#else
	m_shuntImpedance = shuntImpedance;
#endif

	ComputeEquivalentImpedances();

	if (m_outlet)
	{
		if (GetState () == TX)
		{
			m_outlet->SetImpedance(m_eqTxImpedance);
		}
		else
		{
			m_outlet->SetImpedance(m_eqRxImpedance);
		}
	}
}

void
PLC_HalfDuplexOfdmPhy::SetRxImpedance(Ptr<PLC_Impedance> rxImpedance)
{
	PLC_PHY_FUNCTION(this << rxImpedance);

#ifdef PLC_USE_IMPEDANCE_HASHING
	if (rxImpedance)
	{
		m_rxImpedance = rxImpedance->Copy();
	}
	else
	{
		m_rxImpedance = NULL;
	}
#else
	m_rxImpedance = rxImpedance;
#endif

	ComputeEquivalentImpedances();

	if (m_outlet)
	{
		if (GetState () == TX)
		{
			m_outlet->SetImpedance(m_eqTxImpedance);
		}
		else
		{
			m_outlet->SetImpedance(m_eqRxImpedance);
		}
	}
}

void
PLC_HalfDuplexOfdmPhy::SetTxImpedance(Ptr<PLC_Impedance> txImpedance)
{
	PLC_PHY_FUNCTION(this << txImpedance);

#ifdef PLC_USE_IMPEDANCE_HASHING
	if (txImpedance)
	{
		m_txImpedance = txImpedance->Copy();
	}
	else
	{
		m_txImpedance = NULL;
	}
#else
	m_txImpedance = txImpedance;
#endif

	ComputeEquivalentImpedances();

	if (m_outlet)
	{
		if (GetState () == TX)
		{
			m_outlet->SetImpedance(m_eqTxImpedance);
		}
		else
		{
			m_outlet->SetImpedance(m_eqRxImpedance);
		}
	}
}

void
PLC_HalfDuplexOfdmPhy::SetNoiseFloor (Ptr<const SpectrumValue> noiseFloor)
{
	PLC_PHY_FUNCTION (this << noiseFloor);
	DoSetNoiseFloor (noiseFloor);
}


void
PLC_HalfDuplexOfdmPhy::ComputeEquivalentImpedances(void)
{
	PLC_PHY_FUNCTION(this);
	if (m_shuntImpedance)
	{
		if (m_rxImpedance)
		{
			NS_LOG_INFO("Node has shunt impedance. Using equivalent value of the parallel circuit as RX access impedance");
			m_eqRxImpedance = Divide(Multiply(m_rxImpedance, m_shuntImpedance), Add(m_rxImpedance, m_shuntImpedance));
			NS_LOG_LOGIC("Equivalent RX impedance: " << *m_eqRxImpedance);
		}
		else
		{
			m_eqRxImpedance = m_shuntImpedance;
		}
		if (m_txImpedance)
		{
			NS_LOG_INFO("Node has shunt impedance. Using equivalent value of the parallel circuit as TX access impedance");
			m_eqTxImpedance = Divide(Multiply(m_txImpedance, m_shuntImpedance), Add(m_txImpedance, m_shuntImpedance));
			NS_LOG_LOGIC("Equivalent TX impedance: " << *m_eqTxImpedance);
		}
		else
		{
			m_eqTxImpedance = m_shuntImpedance;
		}
	}
	else
	{
		m_eqRxImpedance = m_rxImpedance;
		m_eqTxImpedance = m_txImpedance;
	}
}

void
PLC_HalfDuplexOfdmPhy::SwitchImpedance(State state)
{
	PLC_PHY_FUNCTION(this);

	if (GetState () == state) return;

	NS_LOG_LOGIC ("m_eqRxImpedance: " << m_eqRxImpedance);
	NS_LOG_LOGIC ("m_eqTxImpedance: " << m_eqRxImpedance);

	if (state == TX)
	{
		m_outlet->SetImpedance(m_eqTxImpedance);
	}
	else if (GetState () == TX)
	{
		m_outlet->SetImpedance(m_eqRxImpedance);
	}
}

void
PLC_HalfDuplexOfdmPhy::CcaRequest(void)
{
	PLC_PHY_FUNCTION(this);
	static Time ccaTime = Seconds(CCA_NUM_SYMBOLS * GetSymbolDuration().GetSeconds());
	m_ccaEndEvent = Simulator::Schedule(ccaTime, &PLC_HalfDuplexOfdmPhy::EndCca, this);
}

void
PLC_HalfDuplexOfdmPhy::CancelCca(void)
{
	PLC_PHY_FUNCTION(this);
	m_ccaEndEvent.Cancel();
}

void
PLC_HalfDuplexOfdmPhy::EndCca(void)
{
	PLC_PHY_FUNCTION(this);
	if (!m_ccaConfirmCallback.IsNull())
	{
		m_ccaConfirmCallback(ClearChannelAssessment());
	}
}

void
PLC_HalfDuplexOfdmPhy::SetCcaConfirmCallback(PLC_PhyCcaConfirmCallback c)
{
	PLC_LOG_FUNCTION(this);
	m_ccaConfirmCallback = c;
}

void
PLC_HalfDuplexOfdmPhy::ChangeState(State newState)
{
	PLC_PHY_FUNCTION(this);
	if (newState != GetState ())
	{
		PLC_LOG_LOGIC (this << " state: " << GetState () << " -> " << newState);
		NS_ASSERT_MSG(m_outlet, "PHY's outlet is not set!");

		if (newState == TX)
			SwitchImpedance(TX);
		else
			SwitchImpedance(RX);

		m_PhyStateLogger(Simulator::Now(), newState);
		m_state = newState;
	}
}

PLC_HalfDuplexOfdmPhy::State
PLC_HalfDuplexOfdmPhy::GetState(void)
{
	PLC_PHY_FUNCTION(this);
	return m_state;
}

Time
PLC_HalfDuplexOfdmPhy::CalculateTxDuration (size_t nSymbols)
{
	PLC_PHY_FUNCTION(this);
	PLC_PHY_LOGIC("Symbol duration: " << GetSymbolDuration());
	Time duration = NanoSeconds(nSymbols * GetSymbolDuration().ToInteger(Time::NS));
	NS_LOG_LOGIC("Time needed to send " << nSymbols << " symbols: " << duration);
	return duration;
}

////////////////////////////// PLC_ErrorRatePhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ErrorRatePhy);

TypeId
PLC_ErrorRatePhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_ErrorRatePhy")
	.SetParent<PLC_HalfDuplexOfdmPhy> ()
	.AddConstructor<PLC_ErrorRatePhy> ()
    ;
  return tid;
}

PLC_ErrorRatePhy::PLC_ErrorRatePhy(void)
{
	PLC_PHY_FUNCTION(this);
	m_mcs = BPSK_1_2;
	m_error_rate_model = CreateObject<PLC_ErrorRateModel> (GetSymbolDuration());
	ChangeState (IDLE);
}

void
PLC_ErrorRatePhy::DoStart (void)
{
	PLC_PHY_FUNCTION(this);
	PLC_HalfDuplexOfdmPhy::DoStart();
}

void
PLC_ErrorRatePhy::DoDispose(void)
{
	m_rxNoisePsdMap.clear();
	m_error_rate_model = 0;
	m_ccaConfirmCallback = MakeNullCallback< void, PLC_PhyCcaResult > ();
	m_frame_sent_callback = MakeNullCallback< void > ();
	PLC_HalfDuplexOfdmPhy::DoDispose();
}

void
PLC_ErrorRatePhy::DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor)
{
	PLC_PHY_FUNCTION (this << noiseFloor);
	NS_ASSERT_MSG (m_error_rate_model, "Error rate model has to be instanced prior to setting noise floor!");
	m_error_rate_model->SetNoiseFloor(noiseFloor);
}

bool
PLC_ErrorRatePhy::DoStartTx (Ptr<Packet> p)
{
	PLC_PHY_FUNCTION(this << p);
	NS_ASSERT_MSG(m_txInterface, "Phy has no tx interface");

	// Compose meta information
	Ptr<PLC_TrxMetaInfo> metaInfo = CreateObject<PLC_TrxMetaInfo> ();
	metaInfo->SetUncodedMessage(p); // uncoded packet reference
	metaInfo->SetHeaderMcs(m_mcs); 	// header and
	metaInfo->SetPayloadMcs(m_mcs);	// payload with same mcs

	// Calculate transmission duration of PPDU p
	Time duration = CalculateTxDuration(p);

	// Add preamble
	PLC_Preamble preamble;
	p->AddHeader(preamble);
	duration += preamble.GetDuration();

	PLC_PHY_INFO("Calculated tx duration: " << duration);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Start sending packet: " << *p);
		ChangeState(TX);
		m_txInterface->StartTx(p, m_txPsd, duration, metaInfo);
		Simulator::Schedule(duration, &PLC_ErrorRatePhy::ChangeState, this, IDLE);

		if (!m_frame_sent_callback.IsNull())
		{
			Simulator::Schedule(duration, &PLC_ErrorRatePhy::m_frame_sent_callback, this);
		}

		return true;
	}

	PLC_LOG_INFO("Phy busy, cannot send frame");

	return false;
}

void
PLC_ErrorRatePhy::PreambleDetectionSuccessful (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << p << txId << rxPsd << duration << metaInfo);
	PLC_PHY_LOGIC ("Preamble detection successfull");
	m_locked_txId = txId;
	m_incoming_packet = p->Copy();

	NS_ASSERT (metaInfo && metaInfo->GetUncodedMessage());
	size_t uncoded_bits = metaInfo->GetUncodedMessage()->GetSize() * 8;
	ModulationAndCodingType mcs = metaInfo->GetHeaderMcs();
	m_error_rate_model->StartRx(mcs, rxPsd, uncoded_bits);
}

void
PLC_ErrorRatePhy::DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this << p << txId << rxPsd << duration << metaInfo);
	NS_ASSERT_MSG(m_error_rate_model, "PLC_HalfDuplexOfdmPhy: an error model has to be assigned to the Phy previous to data reception!");

	PLC_PHY_LOGIC ("Receive Power: " << Pwr(*rxPsd));

	if (p &&
		GetState () == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		metaInfo && // meta information present
		metaInfo->GetHeaderMcs() == GetModulationAndCodingScheme() && 	// same modulation and coding scheme (preamble detection is supposed to be always successful)
		W2dBm(Pwr((*rxPsd)/* / GetTotalNoisePower()*/)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization
	{
		PLC_LOG_LOGIC (this << "Starting preamble detections..." << *p);
		Simulator::Schedule (PLC_Preamble::GetDuration(), &PLC_ErrorRatePhy::PreambleDetectionSuccessful, this, p, txId, rxPsd, duration, metaInfo);
		m_locked_txId = 0;
		ChangeState(RX);
	}
	else
	{
		// signal is interference
		// TODO: update receive psd when transmitter's psd changes
		NS_ASSERT(m_rxNoisePsdMap.find(txId) == m_rxNoisePsdMap.end());
		m_rxNoisePsdMap[txId] = rxPsd;
		m_error_rate_model->AddNoiseSignal(rxPsd);
		NS_LOG_LOGIC("Interference signal from " << txId << " added");
	}

	Simulator::Schedule(duration, &PLC_ErrorRatePhy::EndRx, this, txId);
}

void
PLC_ErrorRatePhy::DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> rxSignal)
{
	PLC_PHY_FUNCTION(this << txId << rxSignal);
	if (GetState () == RX && m_locked_txId == txId)
	{
		m_error_rate_model->AlterRxSignal(rxSignal);
	}
	else
	{
		if (m_rxNoisePsdMap.find(txId) != m_rxNoisePsdMap.end())
		{
			m_error_rate_model->RemoveNoiseSignal(m_rxNoisePsdMap[txId]);
			m_error_rate_model->AddNoiseSignal(rxSignal);
			m_rxNoisePsdMap[txId] = rxSignal;
		}
	}
}

void
PLC_ErrorRatePhy::EndRx(uint32_t txId)
{
	PLC_PHY_FUNCTION(this << txId);

	if (GetState () == RX && m_locked_txId == txId)
	{
		NS_ASSERT(m_incoming_packet);
		ChangeState(IDLE);

		if (m_error_rate_model->EndRx ())
		{
			PLC_PHY_INFO ("Packet " << m_incoming_packet << " successfully received");
			PLC_PHY_LOGIC("Packet: " << *m_incoming_packet);

			if (!m_receive_success_cb.IsNull())
			{
				// Remove PHY header and forward packet to MAC layer
				Ptr<Packet> rxPacket = m_incoming_packet->Copy();
				PLC_PhyFrameControlHeader fch;
				rxPacket->RemoveHeader(fch);
				m_receive_success_cb(rxPacket);
			}
		}
		else
		{
			PLC_PHY_INFO ("Packet " << m_incoming_packet << " lost");
			if (!m_receive_error_cb.IsNull())
			{
				m_receive_error_cb();
			}
		}

		m_locked_txId = 0;
	}
	else
	{
		if (m_rxNoisePsdMap.find(txId) != m_rxNoisePsdMap.end())
		{
			m_error_rate_model->RemoveNoiseSignal(m_rxNoisePsdMap[txId]);
			m_rxNoisePsdMap.erase(txId);
		}
	}
}

void
PLC_ErrorRatePhy::SetModulationAndCodingScheme(ModulationAndCodingType mcs)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(mcs < BPSK_RATELESS, "Rateless encoding not supported by PLC_ErrorRatePhy");
	m_mcs = mcs;
}

PLC_PhyCcaResult
PLC_ErrorRatePhy::ClearChannelAssessment(void)
{
	PLC_PHY_FUNCTION(this);
	if (GetState () == IDLE && m_error_rate_model->GetTotalRxPower() <= CCA_THRESHOLD_POWER)
		return CHANNEL_CLEAR;
	else
		return CHANNEL_OCCUPIED;
}

Time
PLC_ErrorRatePhy::CalculateTxDuration(Ptr<const Packet> p)
{
	PLC_PHY_FUNCTION(this << m_mcs);
	NS_ASSERT_MSG(m_txPsd, "Tx power spectral density has to be set before using PLC_ErrorRatePhy");
	NS_ASSERT_MSG(m_mcs < BPSK_RATELESS, "Error rate phy model cannot handle rateless mcs");

	// reduce number of subcarriers if not all are used (e.g. some are reserved for pilot transmission)
	size_t subbands = m_txPsd->GetSpectrumModel()->GetNumBands();
	double code_rate = GetCodeRate (m_mcs);
	size_t encoded_bits = p->GetSize() * 8 / code_rate;
	return CalculateTransmissionDuration(encoded_bits, m_mcs, subbands);
}

std::ostream&
operator<<(std::ostream& os, PLC_HalfDuplexOfdmPhy::State state)
{
	switch (state)
	{
	case (PLC_HalfDuplexOfdmPhy::IDLE):
		{
			os << "IDLE";
			break;
		}
	case (PLC_HalfDuplexOfdmPhy::TX):
		{
			os << "TX";
			break;
		}
	case (PLC_HalfDuplexOfdmPhy::RX):
		{
			os << "RX";
			break;
		}
	default:
		{
			os << "INVALID STATE";
			break;
		}
	}
	return os;
}

////////////////////////////// PLC_InformationRatePhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_InformationRatePhy);

size_t PLC_InformationRatePhy::modulation_symbols_per_code_block = 1;
double PLC_InformationRatePhy::rateless_coding_overhead = 0.2;

TypeId
PLC_InformationRatePhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_InformationRatePhy")
	.SetParent<PLC_HalfDuplexOfdmPhy> ()
	.AddConstructor<PLC_InformationRatePhy> ()
    ;
  return tid;
}

PLC_InformationRatePhy::PLC_InformationRatePhy (void)
{
	PLC_PHY_FUNCTION(this);
	m_header_mcs = BPSK_1_2;
	m_payload_mcs = BPSK_1_2;
	m_information_rate_model = CreateObject<PLC_InformationRateModel> ();
	m_information_rate_model->SetSymbolDuration(GetSymbolDuration());
	m_information_rate_model->SetGuardIntervalDuration(GetGuardIntervalDuration());
}

void
PLC_InformationRatePhy::SetOfdmSymbolsPerCodeBlock(size_t symbols)
{
	modulation_symbols_per_code_block = symbols;
}

size_t
PLC_InformationRatePhy::GetOfdmSymbolsPerCodeBlock(void)
{
	return modulation_symbols_per_code_block;
}

void
PLC_InformationRatePhy::SetRatelessCodingOverhead(double overhead)
{
	NS_ASSERT(overhead >= 0);
	rateless_coding_overhead = overhead;
}

size_t
PLC_InformationRatePhy::RequiredChunks(size_t num_blocks)
{
	PLC_PHY_FUNCTION(this);
	size_t ret = ceil(num_blocks * (1 + rateless_coding_overhead));
	PLC_PHY_INFO("minimum required chunks to decode datagramm: " << ret);
	return ret;
}

size_t
PLC_InformationRatePhy::ChunksInByte(size_t num_chunks, size_t raw_bits_per_symbol)
{
	PLC_PHY_FUNCTION(this);
	return ceil(GetOfdmSymbolsPerCodeBlock() * raw_bits_per_symbol * num_chunks / (double) 8);
}

void
PLC_InformationRatePhy::ReceptionFailure(void)
{
	PLC_PHY_FUNCTION(this);
	if (!m_receive_error_cb.IsNull())
	{
		m_receive_error_cb();
	}
}

void
PLC_InformationRatePhy::DoStart (void)
{
	PLC_PHY_FUNCTION(this);
	PLC_HalfDuplexOfdmPhy::DoStart();
}

void
PLC_InformationRatePhy::DoDispose(void)
{
	PLC_PHY_FUNCTION(this);
	ChangeState(IDLE);
	m_information_rate_model = 0;
	m_frame_sent_callback = MakeNullCallback<void> ();
	PLC_HalfDuplexOfdmPhy::DoDispose();
}

void
PLC_InformationRatePhy::DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor)
{
	PLC_PHY_FUNCTION (this << noiseFloor);
	NS_ASSERT_MSG (m_information_rate_model, "Information rate model has to be instanced prior to setting noise floor!");
	m_information_rate_model->SetNoiseFloor(noiseFloor);
}

void
PLC_InformationRatePhy::DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> rxSignal)
{
	PLC_PHY_FUNCTION(this << txId << rxSignal);
	if (GetState () == RX && m_locked_txId == txId)
	{
		m_information_rate_model->AlterRxSignal(rxSignal);
	}
	else
	{
		if (m_rxNoisePsdMap.find(txId) != m_rxNoisePsdMap.end())
		{
			m_information_rate_model->RemoveNoiseSignal(m_rxNoisePsdMap[txId]);
			m_information_rate_model->AddNoiseSignal(rxSignal);
			m_rxNoisePsdMap[txId] = rxSignal;
		}
	}
}

bool
PLC_InformationRatePhy::DoStartTx (Ptr<Packet> p)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(m_txPsd, "TxPsd not set!");
	NS_ASSERT_MSG(m_header_mcs < BPSK_RATELESS, "Header cannot be encoded rateless");

	// Compose meta information
	Ptr<PLC_TrxMetaInfo> metaInfo = CreateObject<PLC_TrxMetaInfo> ();
	metaInfo->SetUncodedMessage(p);
	metaInfo->SetHeaderMcs(m_header_mcs);
	metaInfo->SetPayloadMcs(m_payload_mcs);

	// (Virtually) encode packet
	Ptr<Packet> encoded_packet = CreateEncodedPacket (metaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Device idle, sending frame: " << *encoded_packet);
		SendFrame (encoded_packet, metaInfo);
		return true;
	}

	PLC_LOG_INFO("Phy busy, cannot send frame");
	return false;
}

void
PLC_InformationRatePhy::SendFrame (Ptr<Packet> p, Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << p << metaInfo);
	NS_ASSERT_MSG (m_txInterface, "Phy has no tx interface");
	NS_ASSERT (metaInfo);

	Time tx_duration = metaInfo->GetHeaderDuration () + metaInfo->GetPayloadDuration ();

	PLC_PHY_LOGIC ("Adding preamble...");
	PLC_Preamble preamble;
	p->AddHeader(preamble);

	tx_duration += preamble.GetDuration();

	PLC_PHY_LOGIC ("Start sending frame...");
	ChangeState(TX);
	m_txInterface->StartTx(p, m_txPsd, tx_duration, metaInfo);
	Simulator::Schedule(tx_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
	Simulator::Schedule(tx_duration, &PLC_Phy::NotifyFrameSent, this);
}

bool
PLC_InformationRatePhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);
	return false;
}

void
PLC_InformationRatePhy::DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this << p << txId << rxPsd << duration << metaInfo);
	NS_ASSERT_MSG(m_information_rate_model, "PLC_HalfDuplexOfdmPhy: an error model has to be assigned to the Phy previous to data reception!");

	PLC_PHY_LOGIC ("Receive Power: " << Pwr(*rxPsd));

	if (p &&
		GetState () == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		metaInfo && // meta information present
		metaInfo->GetHeaderMcs() == GetHeaderModulationAndCodingScheme() && 	// same modulation and coding scheme (preamble detection is supposed to be always successful)
		W2dBm(Pwr((*rxPsd)/* / GetTotalNoisePower()*/)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization
	{
		PLC_LOG_LOGIC (this << "Starting preamble detection..." << *p);
		Simulator::Schedule (PLC_Preamble::GetDuration(), &PLC_InformationRatePhy::PreambleDetectionSuccessful, this, p, txId, rxPsd, duration, metaInfo);
		m_locked_txId = 0;
		ChangeState(RX);
	}
	else
	{
		// signal is treated as interference
		PLC_PHY_INFO ("Signal is interference");
		m_rxNoisePsdMap[txId] = rxPsd;
		m_information_rate_model->AddNoiseSignal(rxPsd);
		NS_LOG_LOGIC("Interference signal from " << txId << " added");
		NS_LOG_LOGIC ("Interference signal: " << *rxPsd);

		Simulator::Schedule(duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, rxPsd);
	}
}

void
PLC_InformationRatePhy::PreambleDetectionSuccessful (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << p << txId << rxPsd << duration << metaInfo);
	PLC_PHY_INFO ("Preamble detection successful");
	NS_ASSERT (GetState() == RX);
	NS_ASSERT (metaInfo && metaInfo->GetUncodedMessage());

	m_locked_txId = txId;
	m_incoming_packet = p->Copy();

	PLC_PHY_LOGIC ("Locked on incoming signal");
	PLC_PHY_LOGIC("Incoming frame: " << *m_incoming_packet);

	// Remove preamble
	PLC_Preamble preamble;
	m_incoming_packet->RemoveHeader(preamble);

	// Start frame reception
	StartReception(p, txId, rxPsd, duration, metaInfo);
}

void
PLC_InformationRatePhy::StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << p << txId << rxPsd << duration << metaInfo);
	PLC_PHY_INFO ("Starting frame reception...");

	// Determine uncoded header bits
	size_t uncoded_header_bits;
	ModulationAndCodingType header_mcs = metaInfo->GetHeaderMcs ();
	if (header_mcs >= BPSK_RATELESS)
	{
		// rateless phy frame control header
		PLC_PhyRatelessFrameControlHeader fch;
		NS_ASSERT_MSG(m_incoming_packet->PeekHeader(fch), "Rateless encoded packet without rateless frame control header");
		uncoded_header_bits = fch.GetSerializedSize();
	}
	else
	{
		// phy frame control header
		PLC_PhyFrameControlHeader fch;
		NS_ASSERT_MSG(m_incoming_packet->PeekHeader(fch), "Packet without frame control header");
		uncoded_header_bits = fch.GetSerializedSize();
	}

	// Receive header
	Time header_duration = metaInfo->GetHeaderDuration();
	m_information_rate_model->StartRx(header_mcs, rxPsd, uncoded_header_bits);
	Simulator::Schedule (header_duration, &PLC_InformationRatePhy::EndRxHeader, this, rxPsd, metaInfo);
}

void
PLC_InformationRatePhy::EndRxHeader(Ptr<SpectrumValue>& rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT(GetState () == RX);

	ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs ();
	Time payload_duration = metaInfo->GetPayloadDuration ();

	if (payload_mcs == GetPayloadModulationAndCodingScheme ())
	{
		if (m_information_rate_model->EndRx ())
		{
			PLC_PHY_INFO("Successfully received header, starting payload reception");

			ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs();
			size_t uncoded_payload_bits = metaInfo->GetUncodedMessage()->GetSize() * 8;

			// Remove frame control header
			if (payload_mcs >= BPSK_RATELESS)
			{
				// rateless phy frame control header
				PLC_PhyRatelessFrameControlHeader fch;
				NS_ASSERT_MSG(m_incoming_packet->RemoveHeader(fch), "Rateless encoded packet without rateless frame control header");
			}
			else
			{
				PLC_PhyFrameControlHeader fch;
				NS_ASSERT_MSG(m_incoming_packet->RemoveHeader(fch), "Packet without frame control header");
			}

			PLC_PHY_INFO("Remaining rx time: " << payload_duration);

			m_information_rate_model->StartRx(payload_mcs, rxPsd, uncoded_payload_bits);
			Simulator::Schedule(payload_duration, &PLC_InformationRatePhy::EndRxPayload, this, metaInfo);
			Simulator::Schedule(payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
		}
		else
		{
			PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");
			m_information_rate_model->AddNoiseSignal(rxPsd);
			Simulator::Schedule(payload_duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, rxPsd);
			Simulator::Schedule(payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
			ChangeState(IDLE);
		}
	}
	else
	{
		PLC_PHY_INFO ("Different modulation and coding scheme: PHY (" <<GetPayloadModulationAndCodingScheme () << "), message (" << payload_mcs << ")");
		m_information_rate_model->AddNoiseSignal(rxPsd);
		Simulator::Schedule(payload_duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, rxPsd);
		Simulator::Schedule(payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState(IDLE);
	}
}

void
PLC_InformationRatePhy::EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this);
	if (m_information_rate_model->EndRx())
	{
		// Successful payload reception
		// (Virtually) decode packet
		Ptr<Packet> decoded_packet = metaInfo->GetUncodedMessage()->Copy();

		PLC_PHY_INFO("Message successfully decoded");
		PLC_PHY_LOGIC("Decoded packet: " << *decoded_packet);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(decoded_packet);
		}

		NotifySuccessfulReception();
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram");
		ReceptionFailure();
	}
}

void
PLC_InformationRatePhy::SetHeaderModulationAndCodingScheme(ModulationAndCodingType mcs)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(mcs < BPSK_RATELESS, "Not a fixed rate modulation and coding scheme!");
	m_header_mcs = mcs;
}

ModulationAndCodingType
PLC_InformationRatePhy::GetHeaderModulationAndCodingScheme(void)
{
	PLC_PHY_FUNCTION(this);
	return m_header_mcs;
}

void
PLC_InformationRatePhy::SetPayloadModulationAndCodingScheme(ModulationAndCodingType mcs)
{
	PLC_PHY_FUNCTION(this);
	m_payload_mcs = mcs;
}

ModulationAndCodingType
PLC_InformationRatePhy::GetPayloadModulationAndCodingScheme(void)
{
	PLC_PHY_FUNCTION(this);
	return m_payload_mcs;
}

PLC_PhyCcaResult
PLC_InformationRatePhy::ClearChannelAssessment(void)
{
	PLC_PHY_FUNCTION(this);
	if (GetState () == IDLE && m_information_rate_model->GetTotalRxPower() <= CCA_THRESHOLD_POWER)
		return CHANNEL_CLEAR;
	else
		return CHANNEL_OCCUPIED;
}

void
PLC_InformationRatePhy::NotifySuccessfulReception (void)
{
	PLC_PHY_FUNCTION (this);
}

Ptr<Packet>
PLC_InformationRatePhy::CreateEncodedPacket (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo);

	if (metaInfo->GetPayloadMcs() < BPSK_RATELESS)
	{
		// Fixed rate payload encoding
		return CreateFixedRateEncodedFrame (metaInfo);
	}
	else
	{
		// Rateless payload encoding
		return CreateRatelessEncodedFrame (metaInfo);
	}
}

Ptr<Packet>
PLC_InformationRatePhy::CreateFixedRateEncodedFrame (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo);

	Ptr<Packet> encoded_packet;

	// Read mcs info
	ModulationAndCodingType header_mcs = metaInfo->GetHeaderMcs();
	ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs();

	// Create frame control header
	PLC_PhyFrameControlHeader fch;
	fch.SetDelimiterType(PLC_PhyFrameControlHeader::DATA);
	fch.SetPayloadMcs(payload_mcs);

	NS_ASSERT_MSG (header_mcs < BPSK_RATELESS, "Phy header cannot be encoded rateless");

	// Determine header size
	size_t uncoded_header_size = fch.GetSerializedSize();
	size_t encoded_header_size = ceil(((double) uncoded_header_size) / GetCodeRate(header_mcs));

	// Determine size of phy protocol data unit (ppdu)
	size_t uncoded_ppdu_size = metaInfo->GetUncodedMessage()->GetSize();
	size_t encoded_ppdu_size = ceil(((double) uncoded_ppdu_size) / GetCodeRate(payload_mcs));

	// Determine payload symbols
	size_t payload_symbols = RequiredSymbols (encoded_ppdu_size*8, payload_mcs, m_numSubcarriers);
	NS_ASSERT_MSG (payload_symbols <= MAX_PPDU_SYMBOLS, "Number of payload symbols currently restricted to " << MAX_PPDU_SYMBOLS);
	fch.SetPayloadSymbols ((uint16_t) payload_symbols);

	// Calculate tx duration of packet segments
	Time header_duration 	= CalculateTransmissionDuration (encoded_header_size*8, header_mcs, m_numSubcarriers);
	Time payload_duration 	= CalculateTransmissionDuration (encoded_ppdu_size*8, payload_mcs, m_numSubcarriers);

	// Complete meta information
	metaInfo->SetHeaderDuration (header_duration);
	metaInfo->SetPayloadDuration (payload_duration);

	// Create packet
	encoded_packet = Create<Packet> (encoded_ppdu_size);

	// Add frame control header
	encoded_packet->AddHeader(fch);

	PLC_PHY_LOGIC ("Created fixed rate encoded packet: " << *encoded_packet);

	return encoded_packet;
}

Ptr<Packet>
PLC_InformationRatePhy::CreateRatelessEncodedFrame (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo);

	Ptr<const Packet> uncoded_packet = metaInfo->GetUncodedMessage();
	Ptr<Packet> encoded_packet;

	// Read mcs info
	ModulationAndCodingType header_mcs = metaInfo->GetHeaderMcs();
	ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs();
	NS_ASSERT_MSG (header_mcs < BPSK_RATELESS, "Phy header cannot be encoded rateless");

	// Create frame control header
	PLC_PhyRatelessFrameControlHeader fch;
	fch.SetDelimiterType(PLC_PhyRatelessFrameControlHeader::DATA);
	fch.SetPayloadMcs(payload_mcs);

	// Get number of raw bits an OFDM header/payload symbol is able to carry
	// (if not all subcarriers are used for transmission m_numSubcarriers should be adjusted)
	size_t bitsPerOfdmHeaderSymbol	= GetBitsPerSymbol(header_mcs) * m_numSubcarriers;
	size_t bitsPerOfdmPayloadSymbol	= GetBitsPerSymbol(payload_mcs) * m_numSubcarriers;

	PLC_LOG_LOGIC("Raw bits per ofdm header symbol: " << bitsPerOfdmHeaderSymbol);
	PLC_LOG_LOGIC("Raw bits per ofdm payload symbol: " << bitsPerOfdmPayloadSymbol);

	// Segment ppdu into blocks
	size_t num_blocks = ceil(uncoded_packet->GetSize()*8 / (double) (GetOfdmSymbolsPerCodeBlock() * bitsPerOfdmPayloadSymbol));
	fch.SetNumBlocks(num_blocks);
	NS_LOG_LOGIC ("Blocks: " << num_blocks);

	// Estimate how many encoded blocks (chunks) are at least required for successful decoding
	size_t required_chunks = RequiredChunks(num_blocks);
	PLC_LOG_LOGIC("Required chunks: " << required_chunks);

	// Calculate length of the encoded packet
	size_t encoded_payload_size = ChunksInByte(required_chunks, bitsPerOfdmPayloadSymbol);
	PLC_LOG_LOGIC("Encoded payload size: " << encoded_payload_size);

	// Determine payload symbols
	size_t payload_symbols = RequiredSymbols (encoded_payload_size*8, payload_mcs, m_numSubcarriers);
	fch.SetPayloadSymbols(payload_symbols);

	// Determine header size
	size_t uncoded_header_size = fch.GetSerializedSize();
	size_t encoded_header_size = ceil(((double) uncoded_header_size) / GetCodeRate(header_mcs));

	// Calculate tx duration of packet segments
	Time header_duration 	= CalculateTransmissionDuration (encoded_header_size*8, header_mcs, m_numSubcarriers);
	Time payload_duration 	= CalculateTransmissionDuration (encoded_payload_size*8, payload_mcs, m_numSubcarriers);

	// Complete meta information
	metaInfo->SetHeaderDuration (header_duration);
	metaInfo->SetPayloadDuration (payload_duration);

	// Create packet
	encoded_packet = Create<Packet> (encoded_payload_size);

	// Add frame control header
	encoded_packet->AddHeader(fch);

	return encoded_packet;
}

////////////////////////////// PLC_ChaseCombiningPhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ChaseCombiningPhy);

TypeId
PLC_ChaseCombiningPhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_ChaseCombiningPhy")
	.SetParent<PLC_InformationRatePhy> ()
	.AddConstructor<PLC_ChaseCombiningPhy> ()
    ;
  return tid;
}

PLC_ChaseCombiningPhy::PLC_ChaseCombiningPhy (void)
{
	m_txPacket = 0;
	m_rxPacketRef = 0;
	m_information_rate_model->TraceConnectWithoutContext ("SinrTrace", MakeCallback (&PLC_ChaseCombiningPhy::TraceSinr, this));
}

void
PLC_ChaseCombiningPhy::UpdateSinrBase (Ptr<const SpectrumValue> newSinrBase)
{
	PLC_PHY_FUNCTION (this << newSinrBase);
	m_information_rate_model->SetSinrBase(newSinrBase);
}

void
PLC_ChaseCombiningPhy::TraceSinr (Time t, Ptr<const SpectrumValue> sinr)
{
	PLC_PHY_FUNCTION(this << t << sinr);
	NS_ASSERT_MSG (t >= m_rxStartTime, "SINR trace time less than packet reception start time, something went wrong...");
	Time offset = t - m_rxStartTime;
	m_sinrBaseTrace.push_back(std::pair<Time, Ptr<const SpectrumValue> > (offset, sinr->Copy()));
}

void
PLC_ChaseCombiningPhy::DoStart (void)
{
	PLC_PHY_FUNCTION(this);
	m_txPacket = 0;
	m_rxPacketRef = 0;
	PLC_InformationRatePhy::DoStart();
}

void
PLC_ChaseCombiningPhy::DoDispose(void)
{
	PLC_PHY_FUNCTION(this);
	m_txPacket = 0;
	m_rxPacketRef = 0;
	m_sinrBaseTrace.clear();
	PLC_InformationRatePhy::DoDispose();
}

bool
PLC_ChaseCombiningPhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);
	NS_ASSERT_MSG (m_txPacket, "No previous tx packet, cannot send redundancy");
	NS_ASSERT_MSG (m_txMetaInfo, "Meta information of tx packet not set, cannot send redundancy");

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO ("Sending redundancy frame...");
		SendFrame (m_txPacket, m_txMetaInfo);
		return true;
	}
	else
	{
		PLC_PHY_INFO ("PHY not idle, cannot send redundancy frame");
		return false;
	}
}

bool
PLC_ChaseCombiningPhy::DoStartTx (Ptr<Packet> p)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(m_txPsd, "TxPsd not set!");
	NS_ASSERT_MSG(m_header_mcs < BPSK_RATELESS, "Header cannot be encoded rateless");

	// Compose meta information
	m_txMetaInfo = CreateObject<PLC_TrxMetaInfo> ();
	m_txMetaInfo->SetUncodedMessage(p);
	m_txMetaInfo->SetHeaderMcs(m_header_mcs);
	m_txMetaInfo->SetPayloadMcs(m_payload_mcs);

	// (Virtually) encode packet
	Ptr<Packet> encoded_packet = CreateEncodedPacket (m_txMetaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Device idle, sending frame: " << *encoded_packet);
		m_txPacket = encoded_packet;
		SendFrame (encoded_packet, m_txMetaInfo);
		return true;
	}

	PLC_LOG_INFO("Phy busy, cannot send frame");
	return false;
}

void
PLC_ChaseCombiningPhy::StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this << p << txId << rxPsd << duration << metaInfo);
	NS_ASSERT (metaInfo);

	// Determine delimiter type
	bool isDataFrame = false;
	if (metaInfo->GetPayloadMcs() >= BPSK_RATELESS)
	{
		PLC_PhyRatelessFrameControlHeader fch;
		NS_ASSERT_MSG(p->PeekHeader (fch), "Rateless encoded packet without rateless frame control header");
		if (fch.GetDelimiterType() == PLC_PhyRatelessFrameControlHeader::DATA)
		{
			isDataFrame = true;
		}
	}
	else
	{
		PLC_PhyRatelessFrameControlHeader fch;
		NS_ASSERT_MSG(p->PeekHeader (fch), "Packet without frame control header");
		if (fch.GetDelimiterType() == PLC_PhyRatelessFrameControlHeader::DATA)
		{
			isDataFrame = true;
		}
	}

	if (isDataFrame)
	{
		PLC_PHY_INFO ("Starting reception of data frame " << p);

		m_rxStartTime = Now();
		Ptr<const Packet> packetRef = metaInfo->GetUncodedMessage();

		// Test if packet is redundancy
		// TODO: redundancy packet recognition via PHY frame control header
		if (packetRef == m_rxPacketRef)
		{
			// Is redundancy packet
			PLC_PHY_INFO ("Is redundancy frame, starting chase combining reception...");

			// Schedule sinr base updates
			PLC_SinrTrace::const_iterator it = m_sinrBaseTrace.begin();

			NS_ASSERT_MSG (it != m_sinrBaseTrace.end(), "No sinr base entries for redundancy packet reception");
			NS_ASSERT_MSG (it->first == Seconds(0), "Offset time of first sinr base entry not zero");

			UpdateSinrBase(it->second);

			while (++it != m_sinrBaseTrace.end())
			{
				Simulator::Schedule(it->first, &PLC_ChaseCombiningPhy::UpdateSinrBase, this, it->second);
			}
		}
		else
		{
			// Is new packet
			PLC_PHY_INFO ("Is new data frame, starting reception...");
			m_rxPacketRef = packetRef;
		}

		m_sinrBaseTrace.clear();
	}

	PLC_InformationRatePhy::StartReception (p, txId, rxPsd, duration, metaInfo);
}

void
PLC_ChaseCombiningPhy::NotifySuccessfulReception (void)
{
	PLC_PHY_FUNCTION (this);
	m_rxPacketRef = 0;
	m_sinrBaseTrace.clear();
}

////////////////////////////// PLC_IncrementalRedundancyPhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_IncrementalRedundancyPhy);

Time PLC_IncrementalRedundancyPhy::reception_failure_timeout = MilliSeconds (50);

TypeId
PLC_IncrementalRedundancyPhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_IncrementalRedundancyPhy")
	.SetParent<PLC_InformationRatePhy> ()
	.AddConstructor<PLC_IncrementalRedundancyPhy> ()
    ;
  return tid;
}

PLC_IncrementalRedundancyPhy::PLC_IncrementalRedundancyPhy (void)
{
	m_awaiting_redundancy = false;
	m_uncoded_msg = 0;
	m_redundancy_chunks = 20;
	m_remaining_bits = 0;
}

void
PLC_IncrementalRedundancyPhy::DoStart (void)
{
	PLC_PHY_FUNCTION(this);
	m_awaiting_redundancy = false;
	m_uncoded_msg = 0;
	m_redundancy_chunks = 20;
	m_remaining_bits = 0;
	PLC_InformationRatePhy::DoStart();
}

void
PLC_IncrementalRedundancyPhy::DoDispose(void)
{
	PLC_PHY_FUNCTION (this);
	m_uncoded_msg = 0;
	m_receptionFailureTimeoutEvent.Cancel ();
	PLC_InformationRatePhy::DoDispose ();
}

bool
PLC_IncrementalRedundancyPhy::DoStartTx (Ptr<Packet> p)
{
	PLC_PHY_FUNCTION (this << p);

	if (m_awaiting_redundancy)
	{
		PLC_PHY_INFO ("Still awaiting redundancy of last message, cannot send frame");
		return false;
	}

	// Remember message to be sent
	m_uncoded_msg = p;

	// Create meta information
	Ptr<PLC_TrxMetaInfo> metaInfo = CreateObject<PLC_TrxMetaInfo> ();
	metaInfo->SetUncodedMessage (p);
	metaInfo->SetHeaderMcs (m_header_mcs);
	metaInfo->SetPayloadMcs (m_payload_mcs);

	// Create first rateless encoded frame of message
	Ptr<Packet> frame = CreateRatelessEncodedFrame (metaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("PHY idle, sending frame: " << *frame);
		SendFrame (frame, metaInfo);
		return true;
	}

	PLC_PHY_INFO ("Phy busy, cannot send frame");
	return false;
}

bool
PLC_IncrementalRedundancyPhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);

	if (!m_uncoded_msg)
	{
		PLC_PHY_INFO ("No previous sent message, cannot send redundancy");
		return false;
	}

	// Create meta information
	Ptr<PLC_TrxMetaInfo> metaInfo = CreateObject<PLC_TrxMetaInfo> ();
	metaInfo->SetUncodedMessage (m_uncoded_msg);
	metaInfo->SetHeaderMcs (m_header_mcs);
	metaInfo->SetPayloadMcs (m_payload_mcs);

	// Create redundancy frame
	PLC_PHY_LOGIC ("Creating redundancy frame with " << m_redundancy_chunks << " chunks");
	Ptr<Packet> frame = CreateRedundancyFrame (m_redundancy_chunks, metaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO ("Sending redundancy frame...");
		SendFrame (frame, metaInfo);
		return true;
	}
	else
	{
		PLC_PHY_INFO ("PHY not idle, cannot send redundancy frame");
		return false;
	}
}

Ptr<Packet>
PLC_IncrementalRedundancyPhy::CreateRedundancyFrame (size_t chunks, Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo);

	// Calculate length of redundancy frame
	ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs ();
	size_t bitsPerOfdmPayloadSymbol	= GetBitsPerSymbol (payload_mcs) * m_numSubcarriers;
	size_t length = ChunksInByte(chunks, bitsPerOfdmPayloadSymbol);
	PLC_LOG_LOGIC("Redundancy frame length: " << length);

	// Complete meta information
	Time payload_duration = CalculateTransmissionDuration (length*8, payload_mcs, m_numSubcarriers);
	metaInfo->SetHeaderDuration (Seconds(0));
	metaInfo->SetPayloadDuration (payload_duration);

	return Create<Packet> (length);
}

void
PLC_IncrementalRedundancyPhy::StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << p << txId << rxPsd << duration << metaInfo);
	NS_ASSERT(PLC_HalfDuplexOfdmPhy::GetState() == PLC_HalfDuplexOfdmPhy::RX);
	NS_ASSERT (metaInfo);
	NS_ASSERT_MSG (metaInfo->GetPayloadMcs() >= BPSK_RATELESS, "Packet not rateless encoded");

	PLC_PHY_LOGIC ("Starting frame reception...");

	if (m_awaiting_redundancy)
	{
		PLC_PHY_LOGIC ("Continue incremental redundancy reception");
		m_receptionFailureTimeoutEvent.Cancel ();
		Time payload_duration = metaInfo->GetPayloadDuration();
		m_information_rate_model->StartRx(metaInfo->GetPayloadMcs(), rxPsd, m_remaining_bits);
		Simulator::Schedule(payload_duration, &PLC_IncrementalRedundancyPhy::EndRxPayload, this, metaInfo);
		Simulator::Schedule(payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
	}
	else
	{
		PLC_PHY_LOGIC ("Receiving fch header of new message");
		// Determine uncoded header bits
		size_t uncoded_header_bits;
		ModulationAndCodingType header_mcs = metaInfo->GetHeaderMcs ();

		// rateless phy frame control header
		PLC_PhyRatelessFrameControlHeader fch;
		NS_ASSERT_MSG(m_incoming_packet->PeekHeader(fch), "Missing PLC_PhyRatelessFrameControlHeader in new message");
		uncoded_header_bits = fch.GetSerializedSize();

		// Receive header
		Time header_duration = metaInfo->GetHeaderDuration();
		m_information_rate_model->StartRx(header_mcs, rxPsd, uncoded_header_bits);
		Simulator::Schedule (header_duration, &PLC_InformationRatePhy::EndRxHeader, this, rxPsd, metaInfo);
	}
}

void
PLC_IncrementalRedundancyPhy::EndRxHeader(Ptr<SpectrumValue>& rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT(PLC_HalfDuplexOfdmPhy::GetState() == PLC_HalfDuplexOfdmPhy::RX);

	ModulationAndCodingType payload_mcs = metaInfo->GetPayloadMcs ();
	Time payload_duration = metaInfo->GetPayloadDuration ();

	if (payload_mcs == GetPayloadModulationAndCodingScheme ())
	{
		if (m_information_rate_model->EndRx ())
		{
			PLC_PHY_INFO("Successfully received header, beginning incremental redundancy reception...");

			m_remaining_bits = metaInfo->GetUncodedMessage()->GetSize() * 8;

			// Remove frame control header
			PLC_PhyRatelessFrameControlHeader fch;
			NS_ASSERT_MSG(m_incoming_packet->PeekHeader(fch), "Missing PLC_PhyRatelessFrameControlHeader in new message");

			m_information_rate_model->StartRx(payload_mcs, rxPsd, m_remaining_bits);
			Simulator::Schedule(payload_duration, &PLC_IncrementalRedundancyPhy::EndRxPayload, this, metaInfo);
			Simulator::Schedule(payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, PLC_HalfDuplexOfdmPhy::IDLE);
		}
		else
		{
			PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");
			m_information_rate_model->AddNoiseSignal(rxPsd);
			Simulator::Schedule(payload_duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, rxPsd);
			PLC_HalfDuplexOfdmPhy::ChangeState(PLC_HalfDuplexOfdmPhy::IDLE);
		}
	}
	else
	{
		PLC_PHY_INFO ("Different modulation and coding scheme: PHY ("
				<< GetPayloadModulationAndCodingScheme () << "), message ("
				<< payload_mcs << "), remaining signal treated as interference");
		m_information_rate_model->AddNoiseSignal(rxPsd);
		Simulator::Schedule(payload_duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, rxPsd);
		Simulator::Schedule(payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState(PLC_HalfDuplexOfdmPhy::IDLE);
	}
}

void
PLC_IncrementalRedundancyPhy::EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this);
	if (m_information_rate_model->EndRx())
	{
		// Successful payload reception
		// (Virtually) decode packet
		Ptr<Packet> decoded_packet = metaInfo->GetUncodedMessage()->Copy();

		PLC_PHY_INFO("Message successfully decoded");

		m_uncoded_msg = 0;
		m_remaining_bits = 0;
		m_receptionFailureTimeoutEvent.Cancel();
		m_awaiting_redundancy = false;

		PLC_PHY_LOGIC("Decoded packet: " << *decoded_packet);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(decoded_packet);
		}
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram, waiting for redundancy");
		m_awaiting_redundancy = true;

		size_t gathered_bits = m_information_rate_model->GetGatheredMutualInformation();
		NS_ASSERT (m_remaining_bits > gathered_bits);
		m_remaining_bits -= gathered_bits;

		PLC_PHY_LOGIC ("Gathered bits: " << gathered_bits << ", Remaining bits: " << m_remaining_bits << ")");
		PLC_PHY_LOGIC ("Resetting reception failure timeout clock");
		m_receptionFailureTimeoutEvent.Cancel ();
		m_receptionFailureTimeoutEvent = Simulator::Schedule (reception_failure_timeout, &PLC_IncrementalRedundancyPhy::ReceptionFailureTimeout, this);
	}
}

void
PLC_IncrementalRedundancyPhy::SetReceptionFailureTimeout (Time timeout)
{
	reception_failure_timeout = timeout;
}

Time
PLC_IncrementalRedundancyPhy::GetReceptionFailureTimeout (void)
{
	return reception_failure_timeout;
}

void
PLC_IncrementalRedundancyPhy::ReceptionFailureTimeout (void)
{
	PLC_PHY_FUNCTION (this);
	PLC_PHY_INFO ("Incremental redundancy reception failed");
	m_uncoded_msg = 0;
	m_remaining_bits = 0;
	m_awaiting_redundancy = false;
	ReceptionFailure ();
}

}
