/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 University of British Columbia, Vancouver
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

#include <ns3/output-stream-wrapper.h>
#include "plc-trace-helper.h"

namespace ns3 {

////////////////////////////////////////// PLC_PhyTraceHelper //////////////////////////////////////////////////////

PLC_PhyTraceHelper::PLC_PhyTraceHelper (void)
{
}

PLC_PhyTraceHelper::PLC_PhyTraceHelper (Ptr<PLC_Phy> phy)
	: m_phy (phy)
{
}

//void PLC_PhyTraceHelper::EnableStateTracing (void)
//{
//	NS_ASSERT_MSG(m_phy, "Phy not set");
//	m_phy->TraceConnectWithoutContext  ("PLC_PhyState", MakeCallback (&PLC_PhyTraceHelper::TraceState, this));
//}

void PLC_PhyTraceHelper::EnableSumPsdTracing (void)
{
	NS_ASSERT_MSG(m_phy, "Phy not set");
	m_phy->GetLinkPerformanceModel ()->GetInterference ()->TraceConnectWithoutContext  ("AllSignals", MakeCallback (&PLC_PhyTraceHelper::TraceSumPsd, this));
}

//void PLC_PhyTraceHelper::EnableLockedRxPsdTracing (void)
//{
//	NS_ASSERT_MSG(m_phy, "Phy not set");
//	m_phy->GetInterference ()->TraceConnectWithoutContext  ("RxSignal", MakeCallback (&PLC_PhyTraceHelper::TraceLockedRxPsd, this));
//}

void PLC_PhyTraceHelper::EnableNoisePsdTracing (void)
{
	NS_ASSERT_MSG(m_phy, "Phy not set");
	m_phy->GetLinkPerformanceModel()->GetInterference ()->TraceConnectWithoutContext  ("NoiseSignals", MakeCallback (&PLC_PhyTraceHelper::TraceNoisePsd, this));
}

void PLC_PhyTraceHelper::EnableSnrTracing (void)
{
	NS_ASSERT_MSG(m_phy, "Phy not set");
	m_phy->GetLinkPerformanceModel ()->TraceConnectWithoutContext  ("SinrTrace", MakeCallback (&PLC_PhyTraceHelper::TraceSnr, this));
}

//void PLC_PhyTraceHelper::EnableRxCapacityTracing (void)
//{
////	Ptr<PLC_ChannelCapacityErrorModel> error_model = m_phy->GetErrorModel ();
////	error_model->TraceConnectWithoutContext  ("PLC_Capacity", MakeCallback (&PLC_PhyTraceHelper::TraceRxCapacity, this));
//}
//
//void PLC_PhyTraceHelper::EnableBitAccumulationTracing (void)
//{
//	NS_ASSERT_MSG(m_phy, "Phy not set");
//
//	if (m_phy->GetInstanceTypeId() != PLC_IncrementalRedundancyPhyImpl::GetTypeId())
//	{
//		NS_ASSERT_MSG (m_phy->GetErrorModel()->GetInstanceTypeId() == PLC_ChannelCapacityErrorModel::GetTypeId(), "Bit accumulation tracing only possible with PLC_ChannelCapacityErrorModel");
//		Ptr<PLC_ChannelCapacityErrorModel> error_model = StaticCast<PLC_ChannelCapacityErrorModel, PLC_ErrorModel> (m_phy->GetErrorModel ());
//		error_model->TraceConnectWithoutContext  ("PLC_GatheredBitInformation", MakeCallback (&PLC_PhyTraceHelper::TraceBitAccumulation, this));
//	}
//	else
//	{
//		NS_ASSERT_MSG (m_phy->GetInstanceTypeId() == PLC_IncrementalRedundancyPhyImpl::GetTypeId(), "Payload bit accumulation tracing only possible with PLC_IncrementalRedundancyPhyImpl");
//		Ptr<PLC_IncrementalRedundancyPhyImpl> ir_phy = StaticCast<PLC_IncrementalRedundancyPhyImpl, PLC_Phy> (m_phy);
//		ir_phy->TraceConnectWithoutContext  ("PLC_PayloadBitAccumulation", MakeCallback (&PLC_PhyTraceHelper::TraceBitAccumulation, this));
//	}
//}
//
//void PLC_PhyTraceHelper::EnableRxPacketTracing (Ptr<PLC_HalfDuplexOfdmPhy> txPhy)
//{
//
//}


//void PLC_PhyTraceHelper::TraceState (Time time, PLC_HalfDuplexOfdmPhy::State state)
//{
//	m_phyState_trace.push_back (std::pair<Time, int>  (time, state));
//}

void PLC_PhyTraceHelper::TraceSumPsd (Time time, Ptr<const SpectrumValue> psd)
{
	m_phySumPsd_trace.push_back (std::pair<Time, Ptr<SpectrumValue> >  (time, psd->Copy ()));
}

//void PLC_PhyTraceHelper::TraceLockedRxPsd (Time time, Ptr<const SpectrumValue> psd)
//{
//	m_phyLockedRxPsd_trace.push_back (std::pair<Time, Ptr<SpectrumValue> >  (time, psd->Copy ()));
//}

void PLC_PhyTraceHelper::TraceSnr (Time time, Ptr<const SpectrumValue> sinr)
{
	m_phySnr_trace.push_back (std::pair<Time, Ptr<SpectrumValue> >  (time, sinr->Copy ()));
}

void PLC_PhyTraceHelper::TraceNoisePsd (Time time, Ptr<const SpectrumValue> psd)
{
	NS_ASSERT_MSG(m_phy, "Phy not set");
	Ptr<SpectrumValue> noise = Create<SpectrumValue>  (psd->GetSpectrumModel ());
	 (*noise) =  (*m_phy->GetLinkPerformanceModel()->GetInterference ()->GetNoiseFloor ()) +  (*psd);
	m_phyNoisePsd_trace.push_back (std::pair<Time, Ptr<SpectrumValue> >  (time, noise));
}

//void PLC_PhyTraceHelper::TraceRxCapacity (Time time, Ptr<const SpectrumValue> psd)
//{
//	m_phyRxCapacity_trace.push_back (std::pair<Time, Ptr<SpectrumValue> >  (time, psd->Copy ()));
//}
//
//void PLC_PhyTraceHelper::TraceBitAccumulation(Time time, double bits)
//{
//	m_phyAccumulatedBits_trace.push_back(std::pair<Time, double> (time, bits));
//}

void
PLC_PhyTraceHelper::SaveSumPsdTraceToFile (std::string filename)
{
	SaveTraceToFile(m_phySumPsd_trace,filename);
}

void
PLC_PhyTraceHelper::SaveNoisePsdTraceToFile (std::string filename)
{
	SaveTraceToFile(m_phyNoisePsd_trace,filename);
}

void
PLC_PhyTraceHelper::SaveSnrTraceToFile (std::string filename)
{
	SaveTraceToFile(m_phySnr_trace,filename);
}


void
PLC_PhyTraceHelper::SaveTraceToFile (PLC_SpectrumValueTrace& psdTrace, std::string filename)
{
	OutputStreamWrapper wrapper (filename, std::ios_base::out);
	std::ostream *os = wrapper.GetStream ();

	PLC_SpectrumValueTrace::iterator tit;
	for  (tit = psdTrace.begin (); tit != psdTrace.end (); tit++)
	{
		Ptr<const SpectrumValue> psd = tit->second;
		Bands::const_iterator bit = psd->ConstBandsBegin();
		Values::const_iterator vit = psd->ConstValuesBegin();
		while (bit != psd->ConstBandsEnd())
		{
			NS_ASSERT (vit != psd->ConstValuesEnd());
			(*os) << tit->first.GetSeconds() << " " << bit->fc << " " << (*vit) << std::endl;
			++bit;
			++vit;
		}

		(*os) << std::endl;
	}
}

}

