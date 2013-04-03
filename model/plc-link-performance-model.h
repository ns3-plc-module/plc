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

#ifndef PLC_LINK_PERFORMANCE_MODEL_H_
#define PLC_LINK_PERFORMANCE_MODEL_H_

#include <map>
#include <ns3/object.h>
#include <ns3/nstime.h>
#include <ns3/traced-value.h>
#include <ns3/trace-source-accessor.h>
#include "plc-defs.h"
#include "plc-interference.h"
#include "plc-dcmc-capacity.h"

namespace ns3 {

/**
 *
 */
class PLC_LinkPerformanceModel : public Object
{
public:
	static TypeId GetTypeId (void);

	PLC_LinkPerformanceModel ();
	PLC_LinkPerformanceModel (Ptr<const SpectrumValue> noiseFloor);
	virtual ~PLC_LinkPerformanceModel () = 0;

	void SetNoiseFloor(Ptr<const SpectrumValue> noiseFloor);
	double GetTotalRxPower(void);
	double GetTotalNoisePower(void);

	void StartRx(ModulationAndCodingType mcs, Ptr<const SpectrumValue> rxPsd, double requiredInformationBits = 0);
	void AlterRxSignal(Ptr<const SpectrumValue> rxPsd);
	void AddNoiseSignal(Ptr<const SpectrumValue> noisePsd);
	void RemoveNoiseSignal(Ptr<const SpectrumValue> noisePsd);
	void EvaluateChunk(void);
	bool EndRx(void);

	void SetSinrBase(Ptr<const SpectrumValue> sinrBase);

	Ptr<PLC_Interference> GetInterference(void) { return m_interference; }

protected:
	virtual void DoDispose(void);
	virtual void DoStartRx(double requiredInformationBits) = 0;
	virtual void DoEvaluateChunk(void) = 0;
	virtual bool DoEndRx(void) = 0;

	bool m_receiving;
	ModulationAndCodingType m_mcs;
	Time m_lastChangeTime;
	Ptr<PLC_Interference> m_interference;

	TracedCallback<Time, Ptr<const SpectrumValue> > m_sinrTracer;
};

/**
 * \brief An empirical PHY abstraction model for emulating block error rates
 *
 * The implementation is based on the publication:
 * "PHY Abstraction Methology for Performance Evaluation of PLC Channels", IEEE 2010
 * by K. Kim, H. Lee, Y.Lee, S. Kim
 */
class PLC_ErrorRateModel : public PLC_LinkPerformanceModel
{
public:
	enum ChannelCondition
	{
		EXCELLENT = 0,
		GOOD = 1,
		MEDIUM = 2,
		BAD = 3
	};

	static TypeId GetTypeId (void);

	PLC_ErrorRateModel();
	PLC_ErrorRateModel(Time block_duration);

	void SetChannelCondition(ChannelCondition cond);
	void SetBlockDuration(Time duration) { m_block_duration = duration; }
	Time GetBlockDuration(void) { return m_block_duration; }

private:
	static double s_A[8][3];
	static double s_B[8][3];

	void DoStartRx(double requiredInformationBits);
	void DoEvaluateChunk(void);
	bool DoEndRx(void);

	double GetChunkSuccessRate(uint32_t numBlocks);
	double GetBler(ModulationAndCodingType mcs, SpectrumValue& sinr);

	Time m_block_duration;
	double m_packet_success_rate;
	ChannelCondition m_channel_condition;
};

/**
 *
 */
class PLC_InformationRateModel : public PLC_LinkPerformanceModel
{
public:
	struct McsInfo
	{
		Modulation mod;
		short cardinality;
		double code_rate;
	};

	static TypeId GetTypeId (void);

	PLC_InformationRateModel();

	void SetSymbolDuration (Time duration) { m_symbol_duration = duration; }
	Time GetSymbolDuration (void) { return m_symbol_duration; }
	void SetGuardIntervalDuration (Time duration) { m_guard_interval_duration = duration; }
	Time GetGuardIntervalDuration (void) { return m_symbol_duration; }

	double GetGatheredMutualInformation(void) { return m_gathered_information_bits; }

private:
	static McsInfo s_mcs_info[10];

	void DoStartRx(double requiredInformationBits);
	void DoEvaluateChunk(void);
	bool DoEndRx(void);

	double CalculateChunkGuardIntervals (Time chunk_duration);

	Time m_symbol_duration;
	Time m_guard_interval_duration;
	int64_t m_last_symbol_residual;

	double m_required_information_bits;
	double m_gathered_information_bits;
};

}

#endif /* PLC_LINK_PERFORMANCE_MODEL_H_ */
