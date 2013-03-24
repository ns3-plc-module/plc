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

namespace ns3 {

Time
CalculateFixedRateTxDuration(size_t uncoded_bytes, ModulationAndCodingType mcs, size_t subbands)
{
	double code_rate;
	size_t bits_per_subcarrier;
	switch (mcs)
	{
		case BPSK_1_4:
		{
			code_rate = 0.25;
			bits_per_subcarrier = 1;
			break;
		}
		case BPSK_1_2:
		{
			code_rate = 0.5;
			bits_per_subcarrier = 1;
			break;
		}
		case QPSK_1_2:
		{
			code_rate = 0.5;
			bits_per_subcarrier = 2;
			break;
		}

		case QAM16_1_2:
		{
			code_rate = 0.5;
			bits_per_subcarrier = 4;
			break;
		}

		case QAM64_16_21:
		{
			code_rate = 16/21;
			bits_per_subcarrier = 6;
			break;
		}

		default:
		{
			NS_ABORT_MSG("Modulation and Coding Scheme " << mcs << " not supported");
			break;
		}
	}

	size_t num_symbols = ceil((uncoded_bytes * 8 / code_rate) / (subbands * bits_per_subcarrier));
	NS_LOG_LOGIC("num_symbols: " << num_symbols);

	Time duration = Time::FromInteger((PLC_Phy::GetSymbolDuration().GetInteger() * num_symbols), Time::GetResolution());

	NS_LOG_INFO("Calculated tx duration: " << duration);

	return duration;
}

size_t
RawBitsPerOfdmSymbol(ModulationAndCodingType mcs, size_t numSubcarriers)
{
	switch(mcs)
	{
		case BPSK_1_4:
		case BPSK_1_2:
		case BPSK_RATELESS:
		{
			return numSubcarriers;
		}
		case QPSK_1_2:
		case QAM4_RATELESS:
		{
			return 2*numSubcarriers;
		}
		case QAM16_1_2:
		case QAM16_RATELESS:
		{
			return 4*numSubcarriers;
		}
		case QAM64_16_21:
		{
			return 6*numSubcarriers;
		}
		default:
		{
			NS_ABORT_MSG("Unsupported Modulation and Coding Type");
			return 0;
		}
	}
}

size_t
RawBytesInOfdmSymbols(ModulationAndCodingType mcs, size_t numSubcarriers, size_t num_bytes)
{
	return ceil(num_bytes * 8 / (double) RawBitsPerOfdmSymbol(mcs, numSubcarriers));
}

double
CodeRate (ModulationAndCodingType mcs)
{
	switch(mcs)
	{
		case BPSK_1_4:
			return 0.25;
		case BPSK_1_2:
		case QPSK_1_2:
		case QAM16_1_2:
			return 0.5;
		case QAM64_16_21:
			return 16/21;
		default:
		{
			NS_ABORT_MSG("Not a fixed rate code");
			return 0;
		}
	}
}

////////////////////////////// PLC_Phy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_Phy);

Time PLC_Phy::symbol_duration = NanoSeconds(8192);

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
PLC_Phy::StartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, ModulationAndCodingType mcs, Time duration)
{
	NS_LOG_FUNCTION (this << p);
	DoStartRx (p, txId, rxPsd, mcs, duration);
}

void
PLC_Phy::RxPsdChanged (uint32_t txId, Ptr<SpectrumValue> newRxPsd)
{
	NS_LOG_FUNCTION (this << txId << newRxPsd);
	DoUpdateRxPsd (txId, newRxPsd);
}

void
PLC_Phy::SetDataFrameSentCallback(PLC_PhyDataFrameSentCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_data_frame_sent_callback = c;
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
PLC_Phy::NotifyDataFrameSent (void)
{
	if (!m_data_frame_sent_callback.IsNull())
	{
		m_data_frame_sent_callback();
	}
}

PLC_ChannelTransferImpl *
PLC_Phy::GetChannelTransferImpl (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	return DoGetChannelTransferImpl(rxPhy);
}

////////////////////////////// PLC_HalfDuplexOfdmPhy /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_HalfDuplexOfdmPhy);

Time PLC_HalfDuplexOfdmPhy::guard_interval_duration = Seconds(0);

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
	ChangeState(IDLE);
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

	m_txInterface = CreateObject<PLC_TxInterface> (m_node, txPsd->GetSpectrumModel());
	m_txInterface->SetPhy(Ptr<PLC_Phy> (this));

	m_rxInterface = CreateObject<PLC_RxInterface> (m_node, txPsd->GetSpectrumModel());
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
		if (m_state == TX)
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
		if (m_state == TX)
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
		if (m_state == TX)
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

	if (m_state == state) return;

	NS_LOG_LOGIC ("m_eqRxImpedance: " << m_eqRxImpedance);
	NS_LOG_LOGIC ("m_eqTxImpedance: " << m_eqRxImpedance);

	if (state == TX)
	{
		m_outlet->SetImpedance(m_eqTxImpedance);
	}
	else if (m_state == TX)
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
	if (newState != m_state)
	{
		PLC_LOG_LOGIC (this << " state: " << m_state << " -> " << newState);
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
	m_state = IDLE;
	m_mcs = BPSK_1_2;
	m_error_rate_model = CreateObject<PLC_ErrorRateModel> (GetSymbolDuration());
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
	m_rxPacket = 0;
	m_error_rate_model = 0;
	m_ccaConfirmCallback = MakeNullCallback< void, PLC_PhyCcaResult > ();
	m_data_frame_sent_callback = MakeNullCallback< void > ();
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

	// Add PHY header
	PLC_PhyHeader phyHeader;
	p->AddHeader(phyHeader);

	// Calculate transmission duration
	Time duration = CalculateTxDuration(p);
	NS_ASSERT_MSG(m_txInterface, "Phy has no tx interface");

	if (m_state == IDLE)
	{
		PLC_PHY_INFO("Start sending packet: " << *p);
		ChangeState(TX);
		m_txInterface->StartTx(p, m_txPsd, m_mcs, duration);
		Simulator::Schedule(duration, &PLC_ErrorRatePhy::ChangeState, this, IDLE);

		if (!m_data_frame_sent_callback.IsNull())
		{
			Simulator::Schedule(duration, &PLC_ErrorRatePhy::m_data_frame_sent_callback, this);
		}

		return true;
	}

	PLC_LOG_INFO("Device not idle, cannot send frame");

	return false;
}

void
PLC_ErrorRatePhy::DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, ModulationAndCodingType mcs, Time duration)
{
	PLC_PHY_FUNCTION(this << p << txId << rxPsd << duration);
	NS_ASSERT_MSG(m_error_rate_model, "PLC_HalfDuplexOfdmPhy: an error model has to be assigned to the Phy previous to data reception!");

	PLC_PHY_LOGIC ("Receive Power: " << Pwr(*rxPsd));

	if (m_state == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		mcs == m_mcs && 	// same modulation and coding scheme (preamble detection is supposed to be always successful)
		W2dBm(Pwr((*rxPsd)/* / GetTotalNoisePower()*/)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization
	{
		PLC_LOG_LOGIC (this << " start receiving packet " << *p);
		m_locked_txId = txId;
		m_rxPacket = p;

		size_t uncoded_bits = p->GetSize() * 8;

		m_error_rate_model->StartRx(mcs, rxPsd, uncoded_bits);
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
	if (m_state == RX && m_locked_txId == txId)
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

	if (m_state == RX && m_locked_txId == txId)
	{
		NS_ASSERT(m_rxPacket);
		ChangeState(IDLE);

		if (m_error_rate_model->EndRx ())
		{
			PLC_PHY_INFO ("Packet " << m_rxPacket << " successfully received");
			PLC_PHY_LOGIC("Packet: " << *m_rxPacket);

			if (!m_receive_success_cb.IsNull())
			{
				// Remove PHY header and forward packet to MAC layer
				Ptr<Packet> rxPacket = m_rxPacket->Copy();
				PLC_PhyHeader phyHeader;
				rxPacket->RemoveHeader(phyHeader);
				m_receive_success_cb(rxPacket);
			}
		}
		else
		{
			PLC_PHY_INFO ("Packet " << m_rxPacket << " lost");
			if (!m_receive_error_cb.IsNull())
			{
				m_receive_error_cb();
			}
		}
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
	if (m_state == IDLE && m_error_rate_model->GetTotalRxPower() <= CCA_THRESHOLD_POWER)
		return CHANNEL_CLEAR;
	else
		return CHANNEL_OCCUPIED;
}

Time
PLC_ErrorRatePhy::CalculateTxDuration(Ptr<const Packet> p)
{
	PLC_PHY_FUNCTION(this << m_mcs);
	NS_ASSERT_MSG(m_txPsd, "Tx power spectral density has to be set before using PLC_ErrorRatePhy");

	// reduce number of subcarriers if not all are used (e.g. some are reserved for pilot transmission)
	size_t subbands = m_txPsd->GetSpectrumModel()->GetNumBands();
	return CalculateFixedRateTxDuration(p->GetSize(), m_mcs, subbands);
}

size_t
PLC_ErrorRatePhy::GetUncodedBitCnt(ModulationAndCodingType mcs, Ptr<const Packet> p)
{
	size_t coded_bits = p->GetSize() * 8;
	double code_rate;

	switch (m_mcs)
	{
		case BPSK_1_4:
		{
			code_rate = 0.25;
			break;
		}
		case BPSK_1_2:
		{
			code_rate = 0.5;
			break;
		}

		case QPSK_1_2:
		{
			code_rate = 0.5;
			break;
		}

		case QAM16_1_2:
		{
			code_rate = 0.5;
			break;
		}

		case QAM64_16_21:
		{
			code_rate = 16/21;
			break;
		}

		default:
		{
			NS_ABORT_MSG("Modulation and Coding Scheme " << m_mcs << " not supported");
			break;
		}
	}

	return (size_t) (ceil(coded_bits * code_rate));
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
	m_receiving_payload = false;
	m_header_mcs = BPSK_1_2;
	m_payload_mcs = BPSK_1_2;
	UniformVariable u;
	m_txDatagramId = u.GetInteger(1, 65535);
	m_rxDatagramId = 0;
	m_information_rate_model = CreateObject<PLC_InformationRateModel> ();
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

Ptr<const Packet>
PLC_InformationRatePhy::GetUncodedPacket(void)
{
	PLC_PHY_FUNCTION(this);
	return m_uncoded_packet;
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
	m_rxPsd = 0;
	m_uncoded_packet = 0;
	m_incoming_packet = 0;
	m_data_frame_sent_callback = MakeNullCallback<void> ();
	PLC_HalfDuplexOfdmPhy::DoDispose();
}

void
PLC_InformationRatePhy::DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor)
{
	PLC_PHY_FUNCTION (this << noiseFloor);
	NS_ASSERT_MSG (m_information_rate_model, "Information rate model has to be instanced prior to setting noise floor!");
	m_information_rate_model->SetNoiseFloor(noiseFloor);
}

bool
PLC_InformationRatePhy::DoStartTx (Ptr<Packet> p)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(m_txPsd, "TxPsd not set!");
	NS_ASSERT(m_header_mcs < BPSK_RATELESS);

	m_uncoded_packet = p;

	PLC_PhyHeader phyHeader;
	PLC_PhyPacketTag tag;

	Ptr<Packet> txPacket;
	Time duration;
	Time payload_duration;

	if (m_payload_mcs < BPSK_RATELESS)
	{
		// Fixed rate payload encoding

		size_t encoded_payload_size = ceil(((double) p->GetSize()) / CodeRate(m_payload_mcs));
		txPacket = Create<Packet> (encoded_payload_size);

		payload_duration = CalculateFixedRateTxDuration(encoded_payload_size, m_payload_mcs, m_numSubcarriers);
		duration = CalculateFixedRateTxDuration(phyHeader.GetSerializedSize(), m_header_mcs, m_numSubcarriers) + payload_duration;
	}
	else
	{
		// Rateless payload encoding

		// Get number of bits an OFDM symbol is able to carry (if not all subcarriers are used for transmission m_numSubcarriers should be adjusted)
		size_t raw_bits_per_symbol = RawBitsPerOfdmSymbol(m_payload_mcs, m_numSubcarriers);
		PLC_LOG_LOGIC("raw_bits_per_symbol: " << raw_bits_per_symbol);

		// segment packet into blocks
		size_t num_blocks = ceil(p->GetSize()*8 / (double) (GetOfdmSymbolsPerCodeBlock() * raw_bits_per_symbol));

		NS_ABORT_IF(num_blocks > MAX_NUM_BLOCKS);
		NS_LOG_LOGIC ("num_blocks: " << num_blocks);

		// estimate how many encoded blocks (chunks) are at least required for successful decoding
		size_t required_chunks = RequiredChunks(num_blocks);
		PLC_LOG_LOGIC("required_chunks: " << required_chunks);

		// Calculate the packets length
		size_t length = ChunksInByte(required_chunks, raw_bits_per_symbol);
		PLC_LOG_LOGIC("length: " << length);

		// Create packet
		txPacket = Create<Packet> (length);

		// Determine the number of payload symbols
		size_t payload_symbols = RawBytesInOfdmSymbols(m_payload_mcs, m_numSubcarriers, length);
		PLC_LOG_LOGIC("payload_symbols: " << payload_symbols);

		// Append meta-information for rateless decoding
		PLC_RatelessPhyHeader rlHdr;
		rlHdr.SetFirstChunkSqn(0);
		rlHdr.SetDatagramId(m_txDatagramId++);
		rlHdr.SetControlFrame(false);
		rlHdr.SetNumBlocks(num_blocks);
		UniformVariable u;
		rlHdr.SetPrngSeed(u.GetInteger(1, 65535));

		// Add rateless PHY header
		txPacket->AddHeader(rlHdr);

		// Calculate time needed for transmission (the baudrate is supposed to be the same for both modulation types)
		Time hdr_duration = CalculateFixedRateTxDuration(phyHeader.GetSerializedSize() + rlHdr.GetSerializedSize(), m_header_mcs, m_numSubcarriers);
		payload_duration = CalculateTxDuration(payload_symbols);
		PLC_PHY_LOGIC("header duration: " << hdr_duration);
		PLC_PHY_LOGIC("payload_duration: " << payload_duration);

		duration = hdr_duration + payload_duration;
	}

	// Add PHY header
	txPacket->AddHeader(phyHeader);

	// Add packet tag to avoid recomputation of payload_duration and uncoded bit amount at the receiver
	tag.SetPayloadMcs(m_payload_mcs);
	tag.SetPayloadDuration(payload_duration);
	tag.SetUncodedBits(p->GetSize()*8);
	txPacket->AddPacketTag(tag);

	NS_ASSERT_MSG(m_txInterface, "Phy has no tx interface");

	if (m_state == IDLE)
	{
		PLC_PHY_INFO("Start sending packet: " << *p);
		ChangeState(TX);
		m_txInterface->StartTx(txPacket, m_txPsd, m_header_mcs, duration);
		Simulator::Schedule(duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
		Simulator::Schedule(duration, &PLC_Phy::NotifyDataFrameSent, this);

		return true;
	}

	PLC_LOG_INFO("Device not idle, cannot send frame");

	return false;
}

void
PLC_InformationRatePhy::DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, ModulationAndCodingType mcs, Time duration)
{
	PLC_PHY_FUNCTION(this << p << txId << rxPsd << mcs);
	PLC_PHY_INFO ("Start receiving");

	NS_ASSERT(m_information_rate_model);

	if (p &&
		m_state == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		mcs == m_header_mcs && // packet header and control frame begin with fixed rate mcs
		W2dBm(Pwr(*rxPsd)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization TODO: take noise level into account
	{
		// receive header
		ChangeState(RX);

		PLC_PHY_INFO ("Locked on incoming signal");
		PLC_PHY_LOGIC("Incoming frame: " << *p);

		m_locked_txId = txId;
		m_rxPsd = rxPsd;
		m_incoming_packet = p->Copy();

		PLC_PhyHeader phyHeader;
		m_incoming_packet->RemoveHeader(phyHeader);

		PLC_PhyPacketTag tag;
		NS_ASSERT_MSG(m_incoming_packet->RemovePacketTag(tag), "Packet is not tagged, something went wrong...");
		ModulationAndCodingType payload_mcs = tag.GetPayloadMcs();
		Time payload_duration = tag.GetPayloadDuration();
		m_uncoded_rx_bits = tag.GetUncodedBits();

		size_t uncoded_header_bits;
		if (m_payload_mcs >= BPSK_RATELESS)
		{
			// Rateless encoded payload
			// Remove rateless header
			m_incoming_packet->RemoveHeader(m_rateless_header);
			uncoded_header_bits = (phyHeader.GetSerializedSize() + m_rateless_header.GetSerializedSize()) * 8 * CodeRate(mcs);
		}
		else
		{
			// fixed rate encoded payload
			uncoded_header_bits = phyHeader.GetSerializedSize() * 8 * CodeRate(mcs);
		}
		PLC_PHY_LOGIC("Uncoded header bits: " << uncoded_header_bits);

		Time hdr_duration = duration - payload_duration;
		m_information_rate_model->StartRx(mcs, m_rxPsd, uncoded_header_bits);
		Simulator::Schedule(hdr_duration, &PLC_InformationRatePhy::EndRxHeader, this, payload_mcs, payload_duration);
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
PLC_InformationRatePhy::DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> rxSignal)
{
	PLC_PHY_FUNCTION(this << txId << rxSignal);
	if (m_state == RX && m_locked_txId == txId)
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

void
PLC_InformationRatePhy::EndRxHeader(ModulationAndCodingType mcs, Time duration)
{
	PLC_PHY_FUNCTION(this << mcs << duration);
	NS_ASSERT(m_state == RX);

	if (mcs == m_payload_mcs && m_information_rate_model->EndRx())
	{
		PLC_PHY_INFO("Successfully received header, starting payload reception");
		PLC_PHY_INFO("Remaining rx time: " << duration);

		m_receiving_payload = true;
		m_information_rate_model->StartRx(mcs, m_rxPsd, m_uncoded_rx_bits);
		Simulator::Schedule(duration, &PLC_InformationRatePhy::EndRxPayload, this);
		Simulator::Schedule(duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
	}
	else
	{
		PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");
		// header reception failed -> payload signal treated as interference
		m_information_rate_model->AddNoiseSignal(m_rxPsd);
		Simulator::Schedule(duration, &PLC_InformationRateModel::RemoveNoiseSignal, m_information_rate_model, m_rxPsd);
		Simulator::Schedule(duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState(IDLE);
	}
}

void
PLC_InformationRatePhy::EndRxPayload(void)
{
	PLC_PHY_FUNCTION(this);
	if (m_information_rate_model->EndRx())
	{
		// Get uncoded packet reference
		Ptr<PLC_Phy> txPhy = GetRxInterface()->GetChannel()->GetTxInterface(m_locked_txId)->GetPhy();
		m_uncoded_packet = (static_cast<PLC_InformationRatePhy *> (PeekPointer(txPhy)))->GetUncodedPacket();

		PLC_PHY_INFO("Message successfully decoded");
		PLC_PHY_LOGIC("Uncoded packet: " << *m_uncoded_packet);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(m_uncoded_packet);
		}
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram");
		ReceptionFailure();
	}

	m_receiving_payload = false;
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
	if (m_state == IDLE && m_information_rate_model->GetTotalRxPower() <= CCA_THRESHOLD_POWER)
		return CHANNEL_CLEAR;
	else
		return CHANNEL_OCCUPIED;
}

}
