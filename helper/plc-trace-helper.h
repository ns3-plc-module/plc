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

#ifndef PLC_TRACE_HELPER_H_
#define PLC_TRACE_HELPER_H_

#include "ns3/plc-phy.h"

namespace ns3{

typedef std::vector<std::pair<Time, int> >  PLC_StateTrace;
typedef std::vector<std::pair<Time, Ptr<PLC_ValueBase> > > PLC_ChannelTrace;
typedef std::vector<std::pair<Time, double> > PLC_AccumulatedBitsTrace;

/**
 * Helper class for tracing phy data
 */
class PLC_PhyTraceHelper
{
public:
	PLC_PhyTraceHelper(void);
	PLC_PhyTraceHelper(Ptr<PLC_Phy> phy);

	void SetPhy(Ptr<PLC_Phy> phy) { m_phy = phy; }
	Ptr<PLC_Phy> GetPhy(void) { return m_phy; }

//	/**
//	 * Enable PHY state tracing
//	 */
//	void EnableStateTracing(void);

	/**
	 * Enable trace of the total PSD of the PHY's
	 * interference model
	 */
	void EnableSumPsdTracing(void);

	/**
	 * Trace PSD values the PHY's receiver locks to.
	 * If the PHY is not in receiving state
	 * the PSD will be zero.
	 */
//	void EnableLockedRxPsdTracing(void);

	/**
	 * Enable noise PSD tracing
	 * The traced values are the sum of all interfering
	 * signals but without the static noise floor of
	 * the PHY's interference model
	 */
	void EnableNoisePsdTracing(void);

	/**
	 * Enable Signal To Noise Ration tracing (non logarithmic)
	 * If the receiver is not locked to a signal, the traced
	 * value will be zero
	 */
	void EnableSnrTracing(void);

//	/**
//	 * Trace Shannon Channel Capacity at the given PHY
//	 * If the receiver is not locked to a signal,
//	 * the capacity is zero
//	 *
//	 * Beware that the traced values can origin from different
//	 * channels, depending on which transmitter the locks while simulation
//	 */
//	void EnableRxCapacityTracing(void);
//
//	/**
//	 * Trace accumulation of deliverable bits of the PHY's error model
//	 * according to Shannon's channel capacity
//	 */
//	void EnableBitAccumulationTracing (void);
//
//
//	void EnableRxPacketTracing(Ptr<PLC_HalfDuplexOfdmPhy> txPhy);

	/**
	 * Trace callbacks
	 */
//	void TraceState(Time time, PLC_HalfDuplexOfdmPhy::State state);
	void TraceSumPsd(Time time, Ptr<const SpectrumValue> psd);
//	void TraceLockedRxPsd(Time time, Ptr<const SpectrumValue> psd);
	void TraceNoisePsd(Time time, Ptr<const SpectrumValue> psd);
	void TraceSnr(Time time, Ptr<const SpectrumValue> snr);
//	void TraceRxCapacity(Time time, Ptr<const SpectrumValue> psd);
//	void TraceBitAccumulation(Time time, double bits);
//	void TracePacketDrop(Time time, Ptr<const Packet> p);

	/**
	 * Trace Getter Functions
	 * @return
	 */
//	PLC_StateTrace *GetStateTrace(void) { return &m_phyState_trace; }
//	PLC_SpectrumValueTrace *GetPsdTrace(void) { return &m_phySumPsd_trace; }
//	PLC_SpectrumValueTrace *GetLockedRxPsdTrace(void) { return &m_phyLockedRxPsd_trace; }
//	PLC_SpectrumValueTrace *GetNoiseRxPsdTrace(void) { return &m_phyLockedRxPsd_trace; }
//	PLC_SpectrumValueTrace *GetSnrTrace(void) { return &m_phySnr_trace; }
//	PLC_SpectrumValueTrace *GetRxCapacityTrace(void) { return &m_phyRxCapacity_trace; }
//	PLC_AccumulatedBitsTrace *GetBitAccumulationTrace(void) { return &m_phyAccumulatedBits_trace; }

	void SaveSumPsdTraceToFile (std::string filename);
	void SaveNoisePsdTraceToFile (std::string filename);
	void SaveSnrTraceToFile (std::string filename);

private:
	void SaveTraceToFile(PLC_SpectrumValueTrace& psdTrace, std::string filename);

	Ptr<PLC_Phy> 	m_phy;
//	PLC_StateTrace 	m_phyState_trace;
	PLC_SpectrumValueTrace	m_phySumPsd_trace;
//	PLC_SpectrumValueTrace	m_phyLockedRxPsd_trace;
	PLC_SpectrumValueTrace	m_phyNoisePsd_trace;
	PLC_SpectrumValueTrace	m_phySnr_trace;
//	PLC_SpectrumValueTrace	m_phyRxCapacity_trace;
//	PLC_AccumulatedBitsTrace m_phyAccumulatedBits_trace;
};

}


#endif /* PLC_TRACE_HELPER_H_ */
