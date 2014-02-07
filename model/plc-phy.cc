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
			PLC_LOG_LOGIC("PLC_Phy[" << m_node->GetName() << "]: " << msg);\
		}\
		else {\
			PLC_LOG_LOGIC("PLC_Phy: " << msg);\
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
			PLC_LOG_DEBUG(m_node->GetName() << msg);\
		}\
		else {\
			PLC_LOG_DEBUG(msg);\
		}\
	} while(0)

size_t
EncodedBits (size_t uncoded_bits, ModulationAndCodingType mct)
{
	return ceil(((double) uncoded_bits) / GetCodeRate(mct));
}

size_t
RequiredSymbols (size_t encoded_bits, ModulationAndCodingType mct, size_t subbands)
{
	NS_LOG_LOGIC ("encoded bits: " << encoded_bits << "mct: " << mct << "subbands: " << subbands);
	size_t bits_per_subcarrier = GetBitsPerSymbol (mct);
	return ceil((double) encoded_bits / (subbands * bits_per_subcarrier));
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
PLC_Phy::DoInitialize(void)
{
	NS_LOG_FUNCTION (this);
}

void
PLC_Phy::DoDispose ()
{
	NS_LOG_FUNCTION (this);
	m_rxMetaInfo = 0;
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
PLC_Phy::InitializeTx (Ptr<const Packet> p)
{
	NS_LOG_FUNCTION (this << p);
	return DoInitializeTx (p);
}

void
PLC_Phy::InitializeRx (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	NS_LOG_FUNCTION (this << txId << rxPsd << duration << metaInfo);

	m_rx_signal_trace.clear ();
	m_noise_trace.clear ();

	DoInitializeRx (txId, rxPsd, duration, metaInfo);
}

void
PLC_Phy::RxPsdChanged (uint32_t txId, Ptr<const SpectrumValue> newRxPsd)
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
PLC_Phy::SetReceiveEndCallback (PhyRxEndCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_rx_end_cb = c;

	// Enable rx signal tracing
	GetLinkPerformanceModel ()->GetInterference ()->
			TraceConnectWithoutContext ("RxSignal", MakeCallback (&PLC_Phy::TraceRxSignal, this));

	// Enable noise tracing
	GetLinkPerformanceModel ()->GetInterference ()->
			TraceConnectWithoutContext ("NoiseSignals", MakeCallback (&PLC_Phy::TraceNoise, this));
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

Ptr<PLC_ChannelTransferImpl>
PLC_Phy::GetChannelTransferImplPtr (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	return DoGetChannelTransferImplPtr(rxPhy);
}


Ptr<PLC_TransferBase>
PLC_Phy::GetChannelTransferVector (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	PLC_ChannelTransferImpl *cti = GetChannelTransferImpl(rxPhy);
	NS_ASSERT_MSG (cti, "No channel to rxPhy " << rxPhy);
	return cti->GetChannelTransferVector();
}

Ptr<PLC_LinkPerformanceModel>
PLC_Phy::GetLinkPerformanceModel (void)
{
	PLC_PHY_FUNCTION (this);
	return DoGetLinkPerformanceModel ();
}

void
PLC_Phy::TraceRxSignal (Time t, Ptr<const SpectrumValue> rxPsd)
{
	PLC_PHY_FUNCTION(this << t << rxPsd);

	NS_ASSERT_MSG (t >= m_rxInitializeTime, "Rx signal trace time less than packet reception start time, something went wrong...");
	Time offset = t - m_rxInitializeTime;

	m_rx_signal_trace.push_back(std::pair<Time, Ptr<const SpectrumValue> > (offset, rxPsd->Copy()));
}

void
PLC_Phy::TraceNoise (Time t, Ptr<const SpectrumValue> noisePsd)
{
	PLC_PHY_FUNCTION(this << t << noisePsd);

	NS_ASSERT_MSG (t >= m_rxInitializeTime, "Rx signal trace time less than packet reception start time, something went wrong...");
	Time offset = t - m_rxInitializeTime;

	m_noise_trace.push_back(std::pair<Time, Ptr<const SpectrumValue> > (offset, noisePsd->Copy()));
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
	m_state = IDLE;
}

PLC_HalfDuplexOfdmPhy::~PLC_HalfDuplexOfdmPhy()
{
	PLC_PHY_FUNCTION(this);
}

void
PLC_HalfDuplexOfdmPhy::DoInitialize(void)
{
	PLC_PHY_FUNCTION(this);
	m_state = IDLE;
	PLC_Phy::DoInitialize();
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

Ptr<PLC_ChannelTransferImpl>
PLC_HalfDuplexOfdmPhy::DoGetChannelTransferImplPtr (Ptr<PLC_Phy> rxPhy)
{
	PLC_PHY_FUNCTION (this << rxPhy);
	NS_ASSERT_MSG(rxPhy->GetInstanceTypeId().IsChildOf(PLC_HalfDuplexOfdmPhy::GetTypeId()), "RX Phy not of type PLC_HalfDuplexOfdmPhy");
	Ptr<PLC_RxInterface> rxIf = (StaticCast<PLC_HalfDuplexOfdmPhy, PLC_Phy> (rxPhy))->GetRxInterface ();
	return Ptr<PLC_ChannelTransferImpl> (GetTxInterface()->GetChannelTransferImpl(PeekPointer(rxIf)));
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
	PLC_PHY_FUNCTION (this << outlet << txPsd << rxImpedance << txImpedance);
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

	m_txInterface->SetTxIfIdx(ch->AddTxInterface(m_txInterface));
	m_txInterface->SetNoiseIfIdx(ch->AddTxInterface(m_txInterface));
	m_rxInterface->SetRxIfIdx(ch->AddRxInterface(m_rxInterface));

	if (m_node->GetImpedancePtr())
	{
		PLC_LOG_LOGIC("Node has shunt impedance");
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
	GetLinkPerformanceModel ()-> SetNoiseFloor (noiseFloor);
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
			PLC_LOG_LOGIC("Equivalent RX impedance: " << *m_eqRxImpedance);
		}
		else
		{
			m_eqRxImpedance = m_shuntImpedance;
		}
		if (m_txImpedance)
		{
			NS_LOG_INFO("Node has shunt impedance. Using equivalent value of the parallel circuit as TX access impedance");
			m_eqTxImpedance = Divide(Multiply(m_txImpedance, m_shuntImpedance), Add(m_txImpedance, m_shuntImpedance));
			PLC_LOG_LOGIC("Equivalent TX impedance: " << *m_eqTxImpedance);
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

	PLC_LOG_LOGIC ("m_eqRxImpedance: " << m_eqRxImpedance);
	PLC_LOG_LOGIC ("m_eqTxImpedance: " << m_eqRxImpedance);

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
PLC_HalfDuplexOfdmPhy::CalculateTransmissionDuration(size_t symbols)
{
	return Time::FromInteger(((PLC_Phy::GetSymbolDuration().GetInteger() + GetGuardIntervalDuration().GetInteger()) * symbols), Time::GetResolution());
}

void
PLC_HalfDuplexOfdmPhy::SendFrame (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT_MSG (m_txInterface, "Phy has no tx interface");
	NS_ASSERT (metaInfo && metaInfo->GetFrame ());

	Ptr<Packet> frame = metaInfo->GetFrame ();

	Time tx_duration = metaInfo->GetHeaderDuration () + metaInfo->GetPayloadDuration () + PLC_Preamble::GetDuration();

	PLC_PHY_LOGIC ("Initialize sending frame...");
	ChangeState(TX);
	m_txInterface->InitializeTx(m_txPsd, tx_duration, metaInfo);
	Simulator::Schedule(tx_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
	Simulator::Schedule(tx_duration, &PLC_Phy::NotifyFrameSent, this);
}

void
PLC_HalfDuplexOfdmPhy::NoiseInitialize (uint32_t txId, Ptr<const SpectrumValue> psd, Time duration)
{
	PLC_PHY_FUNCTION (this << txId << psd);

	EventId noiseRemoveEvent;
	if (m_rxNoisePsdMap.find (txId) != m_rxNoisePsdMap.end ())
	{
		noiseRemoveEvent = m_rxNoisePsdMap[txId].first;
		noiseRemoveEvent.Cancel ();
		GetLinkPerformanceModel ()->RemoveNoiseSignal (m_rxNoisePsdMap[txId].second);
	}

	PLC_LOG_LOGIC("Adding " << txId << " to noise psd map");
	m_rxNoisePsdMap[txId].second = psd;
	GetLinkPerformanceModel ()->AddNoiseSignal (psd);
	PLC_LOG_LOGIC ("Interference signal: " << *psd);

	noiseRemoveEvent = Simulator::Schedule(duration, &PLC_HalfDuplexOfdmPhy::NoiseStop, this, txId);
	m_rxNoisePsdMap[txId].first = noiseRemoveEvent;
}

void
PLC_HalfDuplexOfdmPhy::NoiseStop (uint32_t txId)
{
	PLC_PHY_FUNCTION (this << txId);

	PLC_LOG_LOGIC("Removing " << txId << " from noise psd map");
	NS_ASSERT (m_rxNoisePsdMap.find (txId) != m_rxNoisePsdMap.end ());

	GetLinkPerformanceModel ()->RemoveNoiseSignal (m_rxNoisePsdMap[txId].second);
	m_rxNoisePsdMap.erase (txId);
}

void
PLC_HalfDuplexOfdmPhy::DoUpdateRxPsd (uint32_t txId, Ptr<const SpectrumValue> rxSignal)
{
	PLC_PHY_FUNCTION (this << txId << rxSignal);

	if (GetState () == RX && m_locked_txId == txId)
	{
		NS_ASSERT_MSG (m_rxNoisePsdMap.find (txId) == m_rxNoisePsdMap.end (), "TxId also registered as interfering source, something went wrong...");
		GetLinkPerformanceModel ()->AlterRxSignal (rxSignal);
	}
	else
	{
		if (m_rxNoisePsdMap.find (txId) != m_rxNoisePsdMap.end ())
		{
			GetLinkPerformanceModel ()->RemoveNoiseSignal (m_rxNoisePsdMap[txId].second);
			GetLinkPerformanceModel ()->AddNoiseSignal (rxSignal);

			PLC_LOG_LOGIC ("Adding " << txId << " to noise psd map");
			m_rxNoisePsdMap[txId].second = rxSignal;
		}
	}
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
	m_mcs = ModulationAndCodingScheme (BPSK_1_2, 0);
	m_error_rate_model = CreateObject<PLC_ErrorRateModel> (GetSymbolDuration());
	ChangeState (IDLE);
}

void
PLC_ErrorRatePhy::DoInitialize (void)
{
	PLC_PHY_FUNCTION(this);
	PLC_HalfDuplexOfdmPhy::DoInitialize();
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

bool
PLC_ErrorRatePhy::DoInitializeTx (Ptr<const Packet> ppdu)
{
	PLC_PHY_FUNCTION(this << ppdu);
	NS_ASSERT_MSG(m_txInterface, "Phy has no tx interface");

	// (Uncoded) transmission frame
	Ptr<Packet> frame = ppdu->Copy();

	// Create FCH
	PLC_PhyFrameControlHeader fch;

	// (Virtually) encode packet
	size_t uncoded_bits = (ppdu->GetSize() + fch.GetSerializedSize()) * 8;
	size_t encoded_bits = EncodedBits (uncoded_bits, GetModulationAndCodingScheme ().mct);
	size_t symbols = RequiredSymbols (encoded_bits, GetModulationAndCodingScheme ().mct, m_numSubcarriers);

	// Append FCH
	frame->AddHeader(fch);

	// Calculate transmission duration
	Time duration = CalculateTransmissionDuration(symbols);

	// Add preamble
	PLC_Preamble preamble;
	frame->AddHeader(preamble);
	duration += preamble.GetDuration();

	PLC_PHY_LOGIC ("TX duration: " << duration);

	// Compose meta information
	Ptr<PLC_TrxMetaInfo> metaInfo = Create<PLC_TrxMetaInfo> ();
	metaInfo->SetFrame (frame); 		// Uncoded frame
	metaInfo->SetMessage (ppdu);		// Message (actually not needed for fixed rate transmission)
	metaInfo->SetHeaderMcs (m_mcs); 	// header and ...
	metaInfo->SetPayloadMcs (m_mcs);	// ... payload with same mcs

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Initialize sending packet: " << *frame);
		ChangeState(TX);
		m_txInterface->InitializeTx(m_txPsd, duration, metaInfo);
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
PLC_ErrorRatePhy::DoInitializeRx (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this << txId << rxPsd << duration << metaInfo);
	NS_ASSERT_MSG(m_error_rate_model, "PLC_HalfDuplexOfdmPhy: an error model has to be assigned to the Phy previous to data reception!");

	PLC_PHY_LOGIC ("Receive Power: " << Pwr(*rxPsd));

	if (metaInfo && // meta information present
		GetState () == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		metaInfo->GetHeaderMcs().mct == GetModulationAndCodingScheme().mct && 	// same modulation and coding type (preamble detection is supposed to be always successful)
		W2dBm(Pwr((*rxPsd)/* / GetTotalNoisePower()*/)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization
	{
		PLC_LOG_LOGIC ("Initializeing preamble detection...");
		ChangeState (RX);
		Simulator::Schedule (PLC_Preamble::GetDuration(), &PLC_ErrorRatePhy::PreambleDetectionSuccessful, this, txId, rxPsd, duration, metaInfo);
	}
	else
	{
		PLC_LOG_LOGIC ("Signal is interference");
		NoiseInitialize (txId, rxPsd, duration);
	}
}

void
PLC_ErrorRatePhy::PreambleDetectionSuccessful (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << txId << rxPsd << duration << metaInfo);
	PLC_PHY_LOGIC ("Preamble detection successfull");
	NS_ASSERT (metaInfo && metaInfo->GetFrame());

//	// Lock to reception signal
	m_locked_txId = txId;
	m_incoming_frame = metaInfo->GetFrame()->Copy();

	// Remove preamble
	PLC_Preamble preamble;
	m_incoming_frame->RemoveHeader(preamble);

	// Initialize reception
	size_t information_bits = m_incoming_frame->GetSize() * 8;
	ModulationAndCodingScheme mcs = metaInfo->GetHeaderMcs();
	m_error_rate_model->InitializeRx(mcs, rxPsd, information_bits);
	Simulator::Schedule(duration - preamble.GetDuration(), &PLC_ErrorRatePhy::EndRx, this, txId);
}

void
PLC_ErrorRatePhy::EndRx(uint32_t txId)
{
	PLC_PHY_FUNCTION(this << txId);

	if (GetState () == RX && m_locked_txId == txId)
	{
		NS_ASSERT(m_incoming_frame);
		ChangeState(IDLE);

		if (m_error_rate_model->EndRx ())
		{
			PLC_PHY_INFO ("Frame " << m_incoming_frame << " successfully received");
			PLC_PHY_LOGIC("Frame: " << *m_incoming_frame);

			if (!m_receive_success_cb.IsNull())
			{
				// Remove FCH
				PLC_PhyFrameControlHeader fch;
				m_incoming_frame->RemoveHeader(fch);

				// Forward PPDU to MAC layer
				m_receive_success_cb(m_incoming_frame, fch.GetMessageId());
			}
		}
		else
		{
			PLC_PHY_INFO ("Packet " << m_incoming_frame << " lost");
			if (!m_receive_error_cb.IsNull())
			{
				m_receive_error_cb();
			}
		}

		m_locked_txId = 0;
		m_incoming_frame = 0;
	}
}

void
PLC_ErrorRatePhy::SetModulationAndCodingScheme(ModulationAndCodingScheme mcs)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(mcs.mct < BPSK_RATELESS, "Rateless encoding not supported by PLC_ErrorRatePhy");
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

Ptr<PLC_LinkPerformanceModel>
PLC_ErrorRatePhy::DoGetLinkPerformanceModel (void)
{
	PLC_PHY_FUNCTION (this);
	return m_error_rate_model;
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
	.AddAttribute ("MaxRxQueueSize", "Maximum size of RX queue for redundancy reception.",
				   UintegerValue (5),
				   MakeUintegerAccessor (&PLC_InformationRatePhy::m_maxRxQueueSize),
				   MakeUintegerChecker<size_t> ())
	;
	return tid;
}

PLC_InformationRatePhy::PLC_InformationRatePhy (void)
{
	PLC_PHY_FUNCTION(this);
	m_header_mcs = ModulationAndCodingScheme (BPSK_1_2, 0);
	m_payload_mcs = ModulationAndCodingScheme (BPSK_1_2, 0);
	m_information_rate_model = CreateObject<PLC_InformationRateModel> ();
	m_information_rate_model->SetSymbolDuration(GetSymbolDuration());
	m_information_rate_model->SetGuardIntervalDuration(GetGuardIntervalDuration());

	UniformVariable u;
	m_txMessageId = u.GetInteger(1,65535);
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
	NS_ASSERT (overhead >= 0);
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

double
PLC_InformationRatePhy::GetTransmissionRateLimit(Ptr<SpectrumValue> rxPsd)
{
	PLC_PHY_FUNCTION(rxPsd);
	return m_information_rate_model->GetTransmissionRateLimit (rxPsd, GetPayloadModulationAndCodingScheme ());
}

void
PLC_InformationRatePhy::DoInitialize (void)
{
	PLC_PHY_FUNCTION(this);
	PLC_HalfDuplexOfdmPhy::DoInitialize();
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

Ptr<PLC_LinkPerformanceModel>
PLC_InformationRatePhy::DoGetLinkPerformanceModel (void)
{
	PLC_PHY_FUNCTION (this);
	return m_information_rate_model;
}

bool
PLC_InformationRatePhy::DoInitializeTx (Ptr<const Packet> ppdu)
{
	PLC_PHY_FUNCTION(this << ppdu);
	NS_ASSERT_MSG(m_txPsd, "TxPsd not set!");
	NS_ASSERT_MSG(m_header_mcs.mct < BPSK_RATELESS, "Header cannot be encoded rateless");

	NS_LOG_LOGIC ("Phy Protocol Data Unit: " << *ppdu);

	// Create meta information object
	Ptr<PLC_TrxMetaInfo> metaInfo = Create<PLC_TrxMetaInfo> ();
	metaInfo->SetMessage (ppdu);
	metaInfo->SetHeaderMcs (GetHeaderModulationAndCodingScheme ());
	metaInfo->SetPayloadMcs (GetPayloadModulationAndCodingScheme ());

	// (Virtually encode frame)
	PrepareTransmission (metaInfo);

	// Initialize sending
	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Device idle, sending frame: " << *metaInfo);
		SendFrame (metaInfo);
		return true;
	}

	PLC_LOG_INFO("Phy busy, cannot send frame");
	return false;
}

void
PLC_InformationRatePhy::PrepareTransmission (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo && metaInfo->GetMessage ());

	if (metaInfo->GetPayloadMcs().mct < BPSK_RATELESS)
	{
		// Fixed rate payload encoding
		PrepareFixedRateTransmission (metaInfo);
	}
	else
	{
		// Rateless payload encoding
		PrepareRatelessTransmission (metaInfo);
	}
}

void
PLC_InformationRatePhy::PrepareFixedRateTransmission (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo && metaInfo->GetMessage ());
	NS_ASSERT (metaInfo->GetHeaderMcs().mct < BPSK_RATELESS && metaInfo->GetPayloadMcs ().mct < BPSK_RATELESS);

	Ptr<Packet> frame = metaInfo->GetMessage ()->Copy ();
	ModulationAndCodingScheme header_mcs = metaInfo->GetHeaderMcs ();
	ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();

	// (Virtually) encode packet
	size_t uncoded_header_bits = m_txFch.GetSerializedSize()*8;
	size_t encoded_header_bits = EncodedBits (uncoded_header_bits, header_mcs.mct);
	size_t header_symbols = RequiredSymbols (encoded_header_bits, header_mcs.mct, GetNumSubcarriers ());
	Time header_duration = CalculateTransmissionDuration (header_symbols);

	NS_LOG_LOGIC ("symbol duration: " << GetSymbolDuration());
	NS_LOG_LOGIC ("encoded_header_bits: " << encoded_header_bits);
	NS_LOG_LOGIC ("header mcs: " << header_mcs);
	NS_LOG_LOGIC ("header symbols: " << header_symbols);
	NS_LOG_LOGIC ("header duration: " << header_duration);

	size_t uncoded_payload_bits = frame->GetSize()*8;
	size_t encoded_payload_bits = EncodedBits (uncoded_payload_bits, payload_mcs.mct);
	size_t payload_symbols = RequiredSymbols (encoded_payload_bits, header_mcs.mct, GetNumSubcarriers ());
	Time payload_duration = CalculateTransmissionDuration (payload_symbols);

	NS_LOG_LOGIC ("encoded_payload_bits: " << encoded_payload_bits);
	NS_LOG_LOGIC ("payload_mcs: " << payload_mcs);
	NS_LOG_LOGIC ("payload symbols: " << header_symbols);
	NS_LOG_LOGIC ("payload duration: " << header_duration);

	// Write FCH
	m_txFch.SetMessageId(m_txMessageId++);
	m_txFch.SetPayloadMct(payload_mcs.mct);
	m_txFch.SetPayloadSymbols (payload_symbols);

	// Append FCH
	frame->AddHeader(m_txFch);

	//Append preamble
	PLC_PHY_LOGIC ("Adding preamble...");
	frame->AddHeader(PLC_Preamble ());

	// Complete metaInfo
	metaInfo->SetFrame (frame);
	metaInfo->SetHeaderDuration (header_duration);
	metaInfo->SetPayloadDuration (payload_duration);
}

void
PLC_InformationRatePhy::PrepareRatelessTransmission (Ptr<PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT (metaInfo && metaInfo->GetMessage ());
	NS_ASSERT (metaInfo->GetHeaderMcs().mct < BPSK_RATELESS && metaInfo->GetPayloadMcs ().mct >= BPSK_RATELESS);

	// Read mcs info
	ModulationAndCodingScheme header_mcs = metaInfo->GetHeaderMcs();
	ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs();

	m_txFch.SetMessageId(m_txMessageId++);
	m_txFch.SetPayloadMct(payload_mcs.mct);

	// (Virtually) encode frame

	// Get number of raw bits an OFDM header/payload symbol is able to carry
	// (if not all subcarriers are used for transmission m_numSubcarriers should be adjusted)
	size_t bitsPerOfdmHeaderSymbol	= GetBitsPerSymbol(header_mcs.mct) * GetNumSubcarriers ();
	size_t bitsPerOfdmPayloadSymbol	= GetBitsPerSymbol(payload_mcs.mct) * GetNumSubcarriers ();
	PLC_LOG_LOGIC("Raw bits per ofdm header symbol: " << bitsPerOfdmHeaderSymbol);
	PLC_LOG_LOGIC("Raw bits per ofdm payload symbol: " << bitsPerOfdmPayloadSymbol);

	// Segment ppdu into blocks
	size_t num_blocks = ceil (metaInfo->GetMessage ()->GetSize ()*8 / (double) (GetOfdmSymbolsPerCodeBlock() * bitsPerOfdmPayloadSymbol));
	m_txFch.SetNumBlocks (num_blocks);
	PLC_LOG_LOGIC ("Number of uncoded blocks: " << num_blocks);

	// Estimate how many encoded blocks (chunks) are at least required for successful decoding
	size_t required_chunks = RequiredChunks(num_blocks);
	PLC_LOG_LOGIC("Required chunks: " << required_chunks);

	// Calculate length of the encoded packet
	size_t encoded_payload_size = ChunksInByte(required_chunks, bitsPerOfdmPayloadSymbol);
	PLC_LOG_LOGIC("Encoded payload size: " << encoded_payload_size);

	// Create frame
	// The frame is composed of the uncoded header and rateless encoded payload blocks
	Ptr<Packet> frame = Create<Packet> (encoded_payload_size);

	// Determine header symbols
	size_t uncoded_header_bits = m_txFch.GetSerializedSize ()*8;
	size_t encoded_header_bits = EncodedBits (uncoded_header_bits, header_mcs.mct);
	size_t header_symbols = RequiredSymbols (encoded_header_bits, header_mcs.mct, GetNumSubcarriers ());

	// Determine payload symbols
	size_t payload_symbols = RequiredSymbols (encoded_payload_size*8, payload_mcs.mct, GetNumSubcarriers ());
	m_txFch.SetPayloadSymbols(payload_symbols);

	// Calculate tx duration of packet segments
	Time header_duration 	= CalculateTransmissionDuration (header_symbols);
	Time payload_duration 	= CalculateTransmissionDuration (payload_symbols);

	NS_LOG_LOGIC ("symbol duration: " << GetSymbolDuration());
	NS_LOG_LOGIC ("encoded_header_bits: " << encoded_header_bits);
	NS_LOG_LOGIC ("header_mcs: " << header_mcs);
	NS_LOG_LOGIC ("header_duration: " << header_duration);
	NS_LOG_LOGIC ("header_symbols: " << header_symbols);

	// Add frame control header
	frame->AddHeader(m_txFch);

	//Append preamble
	PLC_PHY_LOGIC ("Adding preamble...");
	frame->AddHeader(PLC_Preamble ());

	// Complete meta information
	metaInfo->SetFrame (frame);
	metaInfo->SetHeaderDuration (header_duration);
	metaInfo->SetPayloadDuration (payload_duration);
}

bool
PLC_InformationRatePhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);
	return false;
}

void
PLC_InformationRatePhy::DoInitializeRx (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this << txId << rxPsd << duration << metaInfo);
	NS_ASSERT_MSG(m_information_rate_model, "PLC_HalfDuplexOfdmPhy: an error model has to be assigned to the Phy previous to data reception!");

	PLC_PHY_LOGIC ("Receive Power: " << Pwr(*rxPsd));

	if (metaInfo && // meta information present
		GetState () == IDLE && 	// PHY will only start receiving in IDLE state (TODO: conditional resynchronization to the new signal if PHY is currently in receiving state)
		metaInfo->GetHeaderMcs().mct == GetHeaderModulationAndCodingScheme().mct && 	// same modulation and coding type (preamble detection is supposed to be always successful)
		W2dBm(Pwr((*rxPsd)/* / GetTotalNoisePower()*/)) >= PLC_RECEIVER_SENSIVITY) // power is sufficient for synchronization
	{
		PLC_LOG_LOGIC (this << "Initializeing preamble detection...");
		Simulator::Schedule (PLC_Preamble::GetDuration(), &PLC_InformationRatePhy::PreambleDetectionSuccessful, this, txId, rxPsd, duration, metaInfo);
		m_locked_txId = 0;
		ChangeState(RX);
	}
	else
	{
		NoiseInitialize (txId, rxPsd, duration);
	}
}

void
PLC_InformationRatePhy::PreambleDetectionSuccessful (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << txId << rxPsd << duration << metaInfo);
	PLC_PHY_INFO ("Preamble detection successful");

	NS_ASSERT (GetState() == RX);
	NS_ASSERT (metaInfo && metaInfo->GetFrame ());

	m_locked_txId = txId;
	m_incoming_frame = metaInfo->GetFrame ()->Copy ();

//	PLC_PHY_LOGIC ("Locked on incoming signal");
	PLC_PHY_LOGIC("Incoming frame: " << *m_incoming_frame);

	// Remove preamble
	PLC_Preamble preamble;
	m_incoming_frame->RemoveHeader(preamble);

	// Initialize frame reception
	InitializeReception(txId, rxPsd, duration, metaInfo);
}

void
PLC_InformationRatePhy::InitializeReception (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << txId << rxPsd << duration << metaInfo);
	PLC_PHY_INFO ("Initializeing frame reception...");

	// Determine uncoded header bits
	ModulationAndCodingScheme header_mcs = metaInfo->GetHeaderMcs ();
	size_t uncoded_header_bits = PLC_PhyFrameControlHeader ().GetSerializedSize ()*8;

	// Receive header
	Time header_duration = metaInfo->GetHeaderDuration ();
	NS_LOG_LOGIC ("header duration: " << header_duration);

	// header is not FEC encoded => no coding overhead
	m_information_rate_model->SetCodingOverhead(0);
	m_information_rate_model->InitializeRx(header_mcs, rxPsd, uncoded_header_bits);
	Simulator::Schedule (header_duration, &PLC_InformationRatePhy::EndRxHeader, this, txId, rxPsd, metaInfo);
}

void
PLC_InformationRatePhy::EndRxHeader(uint32_t txId, Ptr<const SpectrumValue> rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT(GetState () == RX);

	ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();
	Time payload_duration = metaInfo->GetPayloadDuration ();

	if (payload_mcs.mct == GetPayloadModulationAndCodingScheme ().mct)
	{
		if (m_information_rate_model->EndRx ())
		{
			PLC_PHY_INFO ("Successfully received header, starting payload reception");

			ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();

			// Remove frame control header
			m_incoming_frame->RemoveHeader (m_rxFch);

			// If header is rateless encoded take coding overhead into account for reception
			if (payload_mcs.mct >= BPSK_RATELESS)
			{
				m_information_rate_model->SetCodingOverhead (GetRatelessCodingOverhead ());
			}
			else
			{
				m_information_rate_model->SetCodingOverhead (0);
			}

			PLC_PHY_INFO ("Remaining rx time: " << payload_duration);

			size_t uncoded_payload_bits = m_incoming_frame->GetSize ()*8;

			NS_LOG_LOGIC ("Initializeing payload reception: " << payload_duration << payload_mcs << uncoded_payload_bits);

			m_information_rate_model->InitializeRx (payload_mcs, rxPsd, uncoded_payload_bits);
			Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::EndRxPayload, this, metaInfo);
			Simulator::Schedule (payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
		}
		else
		{
			PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");

			NoiseInitialize (txId, rxPsd, payload_duration);

			Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
			ChangeState (IDLE);
		}
	}
	else
	{
		PLC_PHY_INFO ("Different modulation and coding scheme: PHY (" <<GetPayloadModulationAndCodingScheme () << "), message (" << payload_mcs << "), remaining signal treated as interference");

		NoiseInitialize (txId, rxPsd, payload_duration);

		Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState (IDLE);
	}
}

void
PLC_InformationRatePhy::EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this);
	if (m_information_rate_model->EndRx())
	{
		// Successful payload reception
		PLC_PHY_INFO("Message successfully decoded");
		PLC_PHY_LOGIC("Decoded packet: " << *m_incoming_frame);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(metaInfo->GetMessage (), m_rxFch.GetMessageId());
		}

		NotifySuccessfulReception();
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram");
		NotifyPayloadReceptionFailed (metaInfo);
		ReceptionFailure();
	}

	m_incoming_frame = 0;
}

void
PLC_InformationRatePhy::SetHeaderModulationAndCodingScheme(ModulationAndCodingScheme mcs)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(mcs.mct < BPSK_RATELESS, "Not a fixed rate modulation and coding scheme!");
	m_header_mcs = mcs;
}

ModulationAndCodingScheme
PLC_InformationRatePhy::GetHeaderModulationAndCodingScheme(void)
{
	PLC_PHY_FUNCTION(this);
	return m_header_mcs;
}

void
PLC_InformationRatePhy::SetPayloadModulationAndCodingScheme(ModulationAndCodingScheme mcs)
{
	PLC_PHY_FUNCTION(this);
	m_payload_mcs = mcs;
}

ModulationAndCodingScheme
PLC_InformationRatePhy::GetPayloadModulationAndCodingScheme(void)
{
	PLC_PHY_FUNCTION(this);
	return m_payload_mcs;
}

void
PLC_InformationRatePhy::SetPayloadReceptionFailedCallback(PLC_PayloadReceptionFailedCallback c)
{
	PLC_PHY_FUNCTION(this);
	m_payload_reception_failed_cb = c;
}

PLC_PhyCcaResult
PLC_InformationRatePhy::ClearChannelAssessment(void)
{
	PLC_PHY_FUNCTION(this);

	double mean_rx_pwr = m_information_rate_model->GetMeanRxPower();
	PLC_LOG_LOGIC ("Mean RX power: " << mean_rx_pwr);

	if (GetState () == IDLE && mean_rx_pwr <= CCA_THRESHOLD_POWER)
		return CHANNEL_CLEAR;
	else
		return CHANNEL_OCCUPIED;
}

void
PLC_InformationRatePhy::NotifySuccessfulReception (void)
{
	PLC_PHY_FUNCTION (this);
}

void
PLC_InformationRatePhy::NotifyPayloadReceptionFailed (Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
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
	m_txMetaInfo = 0;
}

void
PLC_ChaseCombiningPhy::EnableSinrTracing (void)
{
	PLC_PHY_FUNCTION (this);
	NS_ASSERT (m_information_rate_model);
	m_information_rate_model->TraceConnectWithoutContext ("SinrTrace", MakeCallback (&PLC_ChaseCombiningPhy::TraceSinrBase, this));
}

void
PLC_ChaseCombiningPhy::DisableSinrTracing (void)
{
	PLC_PHY_FUNCTION (this);
	NS_ASSERT (m_information_rate_model);
	m_information_rate_model->TraceDisconnectWithoutContext ("SinrTrace", MakeCallback (&PLC_ChaseCombiningPhy::TraceSinrBase, this));
}

void
PLC_ChaseCombiningPhy::UpdateSinrBase (Ptr<const SpectrumValue> newSinrBase)
{
	PLC_PHY_FUNCTION (this << newSinrBase);
	m_information_rate_model->SetSinrBase(newSinrBase);
}

void
PLC_ChaseCombiningPhy::TraceSinrBase (Time t, Ptr<const SpectrumValue> sinr)
{
	PLC_PHY_FUNCTION(this << t << sinr);

	NS_ASSERT_MSG (t >= m_sinrBaseTraceInitializeTime, "SINR trace time less than packet reception start time, something went wrong...");
	Time offset = t - m_sinrBaseTraceInitializeTime;

	m_sinrBaseTrace.push_back(std::pair<Time, Ptr<const SpectrumValue> > (offset, sinr->Copy()));
}

void
PLC_ChaseCombiningPhy::DoInitialize (void)
{
	PLC_PHY_FUNCTION(this);
	m_txMetaInfo = 0;
	PLC_InformationRatePhy::DoInitialize();
}

void
PLC_ChaseCombiningPhy::DoDispose(void)
{
	PLC_PHY_FUNCTION(this);
	m_txMetaInfo = 0;
	m_sinrBaseTrace.clear();
	PLC_InformationRatePhy::DoDispose();
}

bool
PLC_ChaseCombiningPhy::DoInitializeTx (Ptr<const Packet> ppdu)
{
	PLC_PHY_FUNCTION(this);
	NS_ASSERT_MSG(m_txPsd, "TxPsd not set!");
	NS_ASSERT_MSG(m_header_mcs.mct < BPSK_RATELESS, "Header cannot be encoded rateless");

	// Compose meta information
	m_txMetaInfo = Create<PLC_TrxMetaInfo> ();
	m_txMetaInfo->SetMessage (ppdu);
	m_txMetaInfo->SetHeaderMcs (m_header_mcs);
	m_txMetaInfo->SetPayloadMcs (m_payload_mcs);

	// (Virtually encode frame)
	PrepareTransmission (m_txMetaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("Device idle, sending frame: " << *(m_txMetaInfo->GetFrame ()));
		SendFrame (m_txMetaInfo);
		return true;
	}

	PLC_LOG_INFO("Phy busy, cannot send frame");
	return false;
}

bool
PLC_ChaseCombiningPhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);
	NS_ASSERT_MSG (m_txMetaInfo, "Meta information of tx packet not set, cannot send redundancy");

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO ("Sending redundancy frame...");
		SendFrame (m_txMetaInfo);
		return true;
	}
	else
	{
		PLC_PHY_INFO ("PHY not idle, cannot send redundancy frame");
		return false;
	}
}

void
PLC_ChaseCombiningPhy::InitializeReception (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << txId << rxPsd << duration << metaInfo);
	PLC_PHY_INFO ("Initializeing frame reception...");

	// Determine uncoded header bits
	ModulationAndCodingScheme header_mcs = metaInfo->GetHeaderMcs ();
	size_t uncoded_header_bits = PLC_PhyFrameControlHeader ().GetSerializedSize ()*8;

	// Receive header
	Time header_duration = metaInfo->GetHeaderDuration ();
	NS_LOG_LOGIC ("header duration: " << header_duration);

	// Disable chase combining for header reception
	DisableSinrTracing ();
	m_information_rate_model->SetSinrBase(0);

	// header is not rateless encoded => no coding overhead
	m_information_rate_model->SetCodingOverhead(0);
	m_information_rate_model->InitializeRx(header_mcs, rxPsd, uncoded_header_bits);
	Simulator::Schedule (header_duration, &PLC_ChaseCombiningPhy::EndRxHeader, this, txId, rxPsd, metaInfo);
}

void
PLC_ChaseCombiningPhy::EndRxHeader(uint32_t txId, Ptr<const SpectrumValue> rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT(GetState () == RX);

	ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();
	Time payload_duration = metaInfo->GetPayloadDuration ();

	if (payload_mcs.mct == GetPayloadModulationAndCodingScheme ().mct)
	{
		if (m_information_rate_model->EndRx ())
		{
			PLC_PHY_INFO ("Successfully received header, starting payload reception");

			ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();

			// Remove frame control header
			m_incoming_frame->RemoveHeader (m_rxFch);

			// Test if payload is redundancy
			RxQueueElem *elem;
			if ((elem = GetRxQueueElement(m_rxFch.GetMessageId ())) != NULL)
			{
				// Is redundancy packet
				PLC_PHY_INFO ("Is redundancy, starting chase combining reception...");

				// Schedule sinr base updates
				PLC_SpectrumValueTrace::const_iterator it = elem->sinrTrace.begin();

				NS_ASSERT_MSG (it != elem->sinrTrace.end(), "No sinr base entries for redundancy packet reception");
				NS_ASSERT_MSG (it->first == Seconds(0), "Offset time of first sinr base entry not zero");

				UpdateSinrBase(it->second);
				while (++it != elem->sinrTrace.end())
				{
					Simulator::Schedule(it->first, &PLC_ChaseCombiningPhy::UpdateSinrBase, this, it->second);
				}
			}
			else
			{
				// Is new packet
				PLC_PHY_INFO ("Is new data frame, starting reception...");
				m_information_rate_model->SetSinrBase(0);
			}

			// If header is rateless encoded take coding overhead into account for reception
			if (payload_mcs.mct >= BPSK_RATELESS)
			{
				m_information_rate_model->SetCodingOverhead (GetRatelessCodingOverhead ());
			}
			else
			{
				m_information_rate_model->SetCodingOverhead (0);
			}

			PLC_PHY_INFO ("Remaining rx time: " << payload_duration);

			size_t uncoded_payload_bits = m_incoming_frame->GetSize ()*8;

			NS_LOG_LOGIC ("Initializeing payload reception: " << payload_duration << payload_mcs << uncoded_payload_bits);

			// Configure SINR tracing
			m_sinrBaseTrace.clear ();
			m_sinrBaseTraceInitializeTime = Simulator::Now ();
			EnableSinrTracing ();

			// Initialize payload reception
			m_information_rate_model->InitializeRx (payload_mcs, rxPsd, uncoded_payload_bits);
			Simulator::Schedule (payload_duration, &PLC_ChaseCombiningPhy::EndRxPayload, this, metaInfo);
			Simulator::Schedule (payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, IDLE);
		}
		else
		{
			PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");

			NoiseInitialize (txId, rxPsd, payload_duration);

			Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
			ChangeState (IDLE);
		}
	}
	else
	{
		PLC_PHY_INFO ("Different modulation and coding scheme: PHY (" <<GetPayloadModulationAndCodingScheme () << "), message (" << payload_mcs << "), remaining signal treated as interference");

		NoiseInitialize (txId, rxPsd, payload_duration);

		Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState (IDLE);
	}
}

void
PLC_ChaseCombiningPhy::EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this);

	// Update or create rx queue element
	uint16_t msgId = m_rxFch.GetMessageId ();
	RxQueueElem *elem;
	if ((elem = GetRxQueueElement (msgId)) == NULL)
	{
		// Create new entry
		RxQueueElem el;
		el.msgId = msgId;
		el.metaInfo = metaInfo;
		el.sinrTrace = m_sinrBaseTrace;

		PushRxQueueElement (el);
	}
	else
	{
		// update entry
		elem->metaInfo = metaInfo;
		elem->sinrTrace = m_sinrBaseTrace;
	}

	DisableSinrTracing ();
	m_sinrBaseTrace.clear ();

	// Evaluate payload reception
	if (m_information_rate_model->EndRx())
	{
		// Successful payload reception
		PLC_PHY_INFO("Message successfully decoded");
		PLC_PHY_LOGIC("Decoded packet: " << *m_incoming_frame);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(metaInfo->GetMessage (), msgId);
		}

		NotifySuccessfulReception();
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram");

		NotifyPayloadReceptionFailed (metaInfo);
		ReceptionFailure();
	}

	m_incoming_frame = 0;
}

void
PLC_ChaseCombiningPhy::PushRxQueueElement (RxQueueElem elem)
{
	PLC_PHY_FUNCTION (this << &elem);

	// FIFO queue with m_maxRxQueueSize elements
	if (m_rxQueue.size () == m_maxRxQueueSize)
	{
		m_rxQueue.pop_back ();
	}

	m_rxQueue.push_front (elem);
}

PLC_ChaseCombiningPhy::RxQueueElem *
PLC_ChaseCombiningPhy::GetRxQueueElement (uint16_t msgId)
{
	PLC_PHY_FUNCTION (this << msgId);

	// Iterate over queue to find element with msgId
	std::deque<RxQueueElem>::iterator qit = m_rxQueue.begin();
	while (qit != m_rxQueue.end ())
	{
		if (qit->msgId == msgId)
		{
			return &(*qit);
		}
		++qit;
	}

	// No entry
	return NULL;
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
	.AddAttribute ("RedundancyChunks", "Number of encoding symbols (chunks) used for redundancy frames.",
				   UintegerValue (20),
				   MakeUintegerAccessor (&PLC_IncrementalRedundancyPhy::m_num_redundancy_chunks),
				   MakeUintegerChecker<size_t> ())
	;
	return tid;
}

PLC_IncrementalRedundancyPhy::PLC_IncrementalRedundancyPhy (void)
{
}

void
PLC_IncrementalRedundancyPhy::DoInitialize (void)
{
	PLC_PHY_FUNCTION(this);
	PLC_InformationRatePhy::DoInitialize();
}

void
PLC_IncrementalRedundancyPhy::DoDispose(void)
{
	PLC_PHY_FUNCTION (this);
	m_receptionFailureTimeoutEvent.Cancel ();
	PLC_InformationRatePhy::DoDispose ();
}

bool
PLC_IncrementalRedundancyPhy::DoInitializeTx (Ptr<const Packet> ppdu)
{
	PLC_PHY_FUNCTION (this << ppdu);

	// Create meta information
	m_txMetaInfo = Create<PLC_TrxMetaInfo> ();
	m_txMetaInfo->SetMessage (ppdu);
	m_txMetaInfo->SetHeaderMcs (m_header_mcs);
	m_txMetaInfo->SetPayloadMcs (m_payload_mcs);

	// (Virtually encode frame)
	PrepareTransmission (m_txMetaInfo);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO("PHY idle, sending frame: " << *m_txMetaInfo);
		SendFrame (m_txMetaInfo);
		return true;
	}

	PLC_PHY_INFO ("Phy busy, cannot send frame");
	return false;
}

bool
PLC_IncrementalRedundancyPhy::SendRedundancy (void)
{
	PLC_PHY_FUNCTION (this);

	if (!m_txMetaInfo)
	{
		PLC_PHY_INFO ("No previous sent message, cannot send redundancy");
		return false;
	}

	size_t chunks = GetNumRedundancyFrameChunks ();
	PLC_PHY_LOGIC ("Creating redundancy frame with " << chunks << " chunks");

	// Calculate length of redundancy frame
	ModulationAndCodingScheme payload_mcs = m_txMetaInfo->GetPayloadMcs ();
	size_t bitsPerOfdmPayloadSymbol	= GetBitsPerSymbol (payload_mcs.mct) * GetNumSubcarriers ();
	size_t length = ChunksInByte(chunks, bitsPerOfdmPayloadSymbol);
	PLC_LOG_LOGIC("Redundancy frame length: " << length);
	size_t payload_symbols = RequiredSymbols (length*8, payload_mcs.mct, GetNumSubcarriers ());
	Time payload_duration = CalculateTransmissionDuration (payload_symbols);

	// Update fch
	m_txFch.SetPayloadSymbols (payload_symbols);

	// Create redundancy frame
	Ptr<Packet> frame = Create<Packet> (length);
	frame->AddHeader (m_txFch);

	//Append preamble
	PLC_PHY_LOGIC ("Adding preamble...");
	frame->AddHeader(PLC_Preamble ());

	// Complete meta information
	m_txMetaInfo->SetFrame (frame);
	m_txMetaInfo->SetPayloadDuration (payload_duration);

	if (GetState () == IDLE)
	{
		PLC_PHY_INFO ("Sending redundancy frame...");
		SendFrame (m_txMetaInfo);
		return true;
	}
	else
	{
		PLC_PHY_INFO ("PHY not idle, cannot send redundancy frame");
		return false;
	}
}

void
PLC_IncrementalRedundancyPhy::InitializeReception (uint32_t txId, Ptr<const SpectrumValue> rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << txId << rxPsd << duration << metaInfo);
	NS_ASSERT(PLC_HalfDuplexOfdmPhy::GetState() == PLC_HalfDuplexOfdmPhy::RX);
	NS_ASSERT (metaInfo);

	NS_ASSERT_MSG (metaInfo->GetPayloadMcs().mct >= BPSK_RATELESS, "Packet not rateless encoded");

	PLC_PHY_LOGIC ("Initializeing frame reception...");

	m_rxFrame = m_incoming_frame->Copy ();

	// Determine uncoded header bits
	size_t uncoded_header_bits;
	ModulationAndCodingScheme header_mcs = metaInfo->GetHeaderMcs ();

	// determine header information bits
	uncoded_header_bits = m_rxFch.GetSerializedSize()*8;

	// Receive header
	Time header_duration = metaInfo->GetHeaderDuration();
	m_information_rate_model->SetCodingOverhead(0);
	m_information_rate_model->InitializeRx(header_mcs, rxPsd, uncoded_header_bits);
	Simulator::Schedule (header_duration, &PLC_InformationRatePhy::EndRxHeader, this, txId, rxPsd, metaInfo);
}

void
PLC_IncrementalRedundancyPhy::EndRxHeader(uint32_t txId, Ptr<const SpectrumValue> rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION (this << metaInfo);
	NS_ASSERT(PLC_HalfDuplexOfdmPhy::GetState() == PLC_HalfDuplexOfdmPhy::RX);

	ModulationAndCodingScheme payload_mcs = metaInfo->GetPayloadMcs ();
	Time payload_duration = metaInfo->GetPayloadDuration ();

	if (payload_mcs.mct == GetPayloadModulationAndCodingScheme ().mct)
	{
		if (m_information_rate_model->EndRx ())
		{
			NS_LOG_LOGIC ("Header reception successful");

			PLC_PHY_INFO("Successfully received header");
			NS_LOG_LOGIC ("rx frame: " << *m_rxFrame);

			// Remove FCH
			m_rxFrame->RemoveHeader(m_rxFch);

			// Get message id
			uint16_t msgId = m_rxFch.GetMessageId ();

			// Determine remaining information bits for successful decoding
			size_t remaining_bits;

			// Test if payload is redundancy
			RxQueueElem *elem;
			if ((elem = GetRxQueueElement (msgId)) != NULL)
			{
				// Is redundancy packet
				PLC_PHY_INFO ("Is redundancy, continue incremental redundancy reception...");
				remaining_bits = elem->remaining_bits;
				PLC_PHY_LOGIC ("Remaining bits: " << remaining_bits);
			}
			else
			{
				// Is new packet
				PLC_PHY_INFO ("Is new message, starting incremental redundancy reception...");
				remaining_bits = metaInfo->GetMessage()->GetSize()*8;
				PLC_PHY_LOGIC ("Remaining bits: " << remaining_bits);

				// Create rx queue element
				RxQueueElem el;
				el.msgId = msgId;
				el.metaInfo = metaInfo;
				el.remaining_bits = remaining_bits;

				PushRxQueueElement (el);
			}

			m_information_rate_model->SetCodingOverhead(rateless_coding_overhead);
			m_information_rate_model->InitializeRx(payload_mcs, rxPsd, remaining_bits);

			NS_LOG_LOGIC ("Initializeing payload reception: " << payload_duration << payload_mcs << remaining_bits);

			Simulator::Schedule(payload_duration, &PLC_IncrementalRedundancyPhy::EndRxPayload, this, metaInfo);
			Simulator::Schedule(payload_duration, &PLC_HalfDuplexOfdmPhy::ChangeState, this, PLC_HalfDuplexOfdmPhy::IDLE);
		}
		else
		{
			PLC_PHY_INFO ("Header reception failed, remaining signal treated as interference");

			NoiseInitialize (txId, rxPsd, payload_duration);

			Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
			ChangeState (IDLE);
		}
	}
	else
	{
		PLC_PHY_INFO ("Different modulation and coding scheme: PHY (" <<GetPayloadModulationAndCodingScheme () << "), message (" << payload_mcs << ")");

		NoiseInitialize (txId, rxPsd, payload_duration);

		Simulator::Schedule (payload_duration, &PLC_InformationRatePhy::ReceptionFailure, this);
		ChangeState (IDLE);
	}
}

void
PLC_IncrementalRedundancyPhy::EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_PHY_FUNCTION(this);

	// Get rx queue entry
	uint16_t msgId = m_rxFch.GetMessageId ();
	RxQueueElem *elem = GetRxQueueElement(msgId);
	NS_ASSERT_MSG (elem, "No queue entry for message ID: " << msgId <<", something went wrong...");

	if (m_information_rate_model->EndRx())
	{
		// Successful payload reception
		// (Virtually) decode packet
		Ptr<const Packet> decoded_packet = metaInfo->GetMessage ();

		PLC_PHY_INFO("Message successfully decoded");

		m_receptionFailureTimeoutEvent.Cancel();
		m_rxFrame = 0;

		PLC_PHY_LOGIC("Decoded packet: " << *decoded_packet);

		if (!m_receive_success_cb.IsNull())
		{
			m_receive_success_cb(decoded_packet, m_rxFch.GetMessageId());
		}

		// Update rx queue entry
		elem->metaInfo = metaInfo;
		elem->remaining_bits = 0;
	}
	else
	{
		PLC_PHY_INFO("Not able to decode datagram, waiting for redundancy");

		size_t gathered_bits = m_information_rate_model->GetGatheredMutualInformation();
		NS_ASSERT (elem->remaining_bits > gathered_bits);
		elem->remaining_bits -= gathered_bits;

		PLC_PHY_LOGIC ("Gathered bits: " << gathered_bits << ", Remaining bits: " << elem->remaining_bits << ")");
		PLC_PHY_LOGIC ("Resetting reception failure timeout clock");
		m_receptionFailureTimeoutEvent.Cancel ();
		m_receptionFailureTimeoutEvent = Simulator::Schedule (reception_failure_timeout, &PLC_IncrementalRedundancyPhy::ReceptionFailureTimeout, this);

		NotifyPayloadReceptionFailed (metaInfo);
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
	ReceptionFailure ();
}

void
PLC_IncrementalRedundancyPhy::PushRxQueueElement (RxQueueElem elem)
{
	PLC_PHY_FUNCTION (this << &elem);

	if (m_rxQueue.size () == m_maxRxQueueSize)
	{
		m_rxQueue.pop_back ();
	}

	m_rxQueue.push_front (elem);
}

PLC_IncrementalRedundancyPhy::RxQueueElem *
PLC_IncrementalRedundancyPhy::GetRxQueueElement (uint16_t msgId)
{
	PLC_PHY_FUNCTION (this << msgId);

	std::deque<RxQueueElem>::iterator qit = m_rxQueue.begin();

	while (qit != m_rxQueue.end ())
	{
		if (qit->msgId == msgId)
		{
			return &(*qit);
		}
		++qit;
	}

	return NULL;
}

}
