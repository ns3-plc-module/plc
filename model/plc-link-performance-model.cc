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

#include <cmath>
#include <ns3/log.h>
#include <ns3/abort.h>
#include <ns3/simulator.h>
#include <ns3/random-variable.h>
#include "plc-link-performance-model.h"

NS_LOG_COMPONENT_DEFINE ("PLC_LinkPerformanceModel");

namespace ns3 {

/////////////////////////////////////// PLC_LinkPerformanceModel /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_LinkPerformanceModel);

TypeId
PLC_LinkPerformanceModel::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_LinkPerformanceModel")
	.SetParent<Object> ()
	.AddTraceSource  ("SinrTrace",
					 "Signal to Interference plus Noise Ratio while receiving",
					 MakeTraceSourceAccessor  (&PLC_LinkPerformanceModel::m_sinrTracer))
	;
	return tid;
}

PLC_LinkPerformanceModel::PLC_LinkPerformanceModel ()
{
	m_interference = CreateObject<PLC_Interference> ();
	m_receiving = false;
	m_mcs = NONE_MCS;
}

PLC_LinkPerformanceModel::PLC_LinkPerformanceModel (Ptr<const SpectrumValue> noiseFloor)
{
	SetNoiseFloor(noiseFloor);
	m_receiving = false;
}

PLC_LinkPerformanceModel::~PLC_LinkPerformanceModel ()
{
}

void
PLC_LinkPerformanceModel::DoDispose(void)
{
	NS_LOG_FUNCTION(this);
	m_interference = 0;
	Object::DoDispose();
}

void
PLC_LinkPerformanceModel::SetNoiseFloor(Ptr<const SpectrumValue> noiseFloor)
{
	NS_LOG_FUNCTION(this);
	EvaluateChunk();
	m_interference->SetNoiseFloor(noiseFloor);
}

double
PLC_LinkPerformanceModel::GetTotalRxPower(void)
{
	NS_LOG_FUNCTION(this);
	return m_interference->GetTotalRxPower();
}

double
PLC_LinkPerformanceModel::GetTotalNoisePower(void)
{
	NS_LOG_FUNCTION(this);
	return m_interference->GetTotalNoisePower();
}

void
PLC_LinkPerformanceModel::StartRx(ModulationAndCodingType mcs, Ptr<const SpectrumValue> rxPsd, double requiredInformationBits)
{
	NS_LOG_FUNCTION(this << mcs << rxPsd << requiredInformationBits);
	m_mcs = mcs;
	m_interference->StartRx(rxPsd);
	m_receiving = true;

	DoStartRx(requiredInformationBits);

	m_sinrTracer(Now(), m_interference->GetSinr());
}

void
PLC_LinkPerformanceModel::EvaluateChunk(void)
{
	NS_LOG_FUNCTION(this);

	if (m_receiving && m_lastChangeTime < Now())
	{
		DoEvaluateChunk();
		m_sinrTracer(Now(), m_interference->GetSinr());
	}
}

bool
PLC_LinkPerformanceModel::EndRx(void)
{
	NS_LOG_FUNCTION(this);
	EvaluateChunk();
	m_interference->EndRx();
	m_receiving = false;
	return DoEndRx();
}

void
PLC_LinkPerformanceModel::AlterRxSignal(Ptr<const SpectrumValue> rxPsd)
{
	NS_LOG_FUNCTION(this);
	EvaluateChunk();
	m_interference->AlterRxSignal(rxPsd);
}

void
PLC_LinkPerformanceModel::AddNoiseSignal(Ptr<const SpectrumValue> noisePsd)
{
	NS_LOG_FUNCTION(this);
	NS_LOG_LOGIC ("Adding noise psd: " << *noisePsd);
	EvaluateChunk();
	m_interference->AddInterferenceSignal(noisePsd);
}

void
PLC_LinkPerformanceModel::RemoveNoiseSignal(Ptr<const SpectrumValue> noisePsd)
{
	NS_LOG_FUNCTION(this);
	EvaluateChunk();
	m_interference->RemoveInterferenceSignal(noisePsd);
}

void
PLC_LinkPerformanceModel::SetSinrBase(Ptr<const SpectrumValue> sinrBase)
{
	NS_LOG_FUNCTION (this << sinrBase);
	NS_ASSERT(m_interference);
	m_interference->SetSinrBase(sinrBase);

	if (m_receiving)
	{
		EvaluateChunk();
	}
}

/////////////////////////////////////// PLC_ErrorRateModel /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ErrorRateModel);

double PLC_ErrorRateModel::s_A[8][3] = {{5.0, -4.0, -4.6}, {5.0, -4.0, -4.6}, {5.0, -4.0, -4.6}, {5.0, -4.0, -4.6}, {-5.1, -4.3, -4.7}, {-5.3, -4.1, -4.5}, {-4.9, -4.2, -4.6}, {-5.5, -4.4, -5.1}};
double PLC_ErrorRateModel::s_B[8][3] = {{2.4, 8.5, 17}, {2.4, 8.5, 17}, {2.4, 8.5, 17}, {2.4, 8.5, 17}, {2.5, 8.4, 16.3}, {2.7, 8.1, 17.2}, {2.7, 8.0, 17.8}, {2.9, 7.0, 18.0}};

TypeId
PLC_ErrorRateModel::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_ErrorRateModel")
	.SetParent<PLC_LinkPerformanceModel> ()
	.AddConstructor<PLC_ErrorRateModel> ()
	;
	return tid;
}

PLC_ErrorRateModel::PLC_ErrorRateModel()
	: m_block_duration(Seconds(0)), m_channel_condition(PLC_ErrorRateModel::GOOD)
{
	NS_LOG_FUNCTION(this);
}

PLC_ErrorRateModel::PLC_ErrorRateModel(Time block_duration)
	: m_block_duration(block_duration), m_channel_condition(PLC_ErrorRateModel::GOOD)
{
	NS_LOG_FUNCTION(this);
}

double
PLC_ErrorRateModel::GetChunkSuccessRate(uint32_t numBlocks)
{
	NS_LOG_FUNCTION(this);
	SpectrumValue& sinr = *(m_interference->GetSinr());
	double bler = GetBler(m_mcs, sinr);
	return pow(1-bler, numBlocks);
}

double
PLC_ErrorRateModel::GetBler(ModulationAndCodingType mcs, SpectrumValue& sinr)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG(mcs < 3, "Unsupported Modulation and Coding Scheme for PLC_ErrorRateModel!");
	double C = Sum(Log2((1 + sinr))) / sinr.GetSpectrumModel()->GetNumBands();
	double BlerApprox = pow(10, (s_A[m_channel_condition][mcs]*C + s_B[m_channel_condition][mcs]));
	NS_LOG_LOGIC("BlerApprox: " << BlerApprox);

	if (BlerApprox > 1) BlerApprox = 1;

	return BlerApprox;
}

void
PLC_ErrorRateModel::SetChannelCondition(PLC_ErrorRateModel::ChannelCondition cond)
{
	NS_LOG_FUNCTION(this);
	m_channel_condition = cond;
}

void
PLC_ErrorRateModel::DoStartRx(double requiredInformationBits)
{
	NS_LOG_FUNCTION(this);
	m_packet_success_rate = 1;
	m_lastChangeTime = Now();
}

void
PLC_ErrorRateModel::DoEvaluateChunk(void)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG(m_block_duration > 0, "Block duration is not set!");
	double numblocks = (Now() - m_lastChangeTime).GetInteger() / GetBlockDuration().GetInteger();

	m_packet_success_rate *= GetChunkSuccessRate(numblocks);
	m_lastChangeTime = Now();
}

bool
PLC_ErrorRateModel::DoEndRx(void)
{
	NS_LOG_FUNCTION(this);

	UniformVariable u;
	double random = u.GetValue();

	if (random > m_packet_success_rate)
	{
		NS_LOG_INFO("packet reception failed (random number " << random << " > packet success rate " << m_packet_success_rate << ")");
		return false;
	}
	else
	{
		NS_LOG_INFO("packet reception successful (random number " << random << " <= packet success rate "<< m_packet_success_rate << ")");
		return true;
	}
}

/////////////////////////////////////// PLC_InformationRateModel /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_InformationRateModel);

PLC_InformationRateModel::McsInfo
PLC_InformationRateModel::s_mcs_info[8] =
{
		{QAM, 2, 1/4}, 		// BPSK_1_4
		{QAM, 2, 1/2}, 		// BPSK_1_2
		{QAM, 4, 1/2}, 		// QPSK_1_2
		{QAM, 16, 1/2}, 	// QAM16_1_2
		{QAM, 64, 16/21}, 	// QAM64_16_21
		{QAM, 2, 0}, 		// BPSK_RATELESS
		{QAM, 4, 0}, 		// QAM4_RATELESS
		{QAM, 16, 0}, 		// QAM16_RATELESS
};

TypeId
PLC_InformationRateModel::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_InformationRateModel")
	.SetParent<PLC_LinkPerformanceModel> ()
	.AddConstructor<PLC_InformationRateModel> ()
	;
	return tid;
}

PLC_InformationRateModel::PLC_InformationRateModel()
	: m_ineffective_time_proportion(0), m_gathered_information_bits(0)
{
	NS_LOG_FUNCTION(this);
}

void
PLC_InformationRateModel::SetIneffectiveTimeProportion(double prop)
{
	NS_LOG_FUNCTION(this << prop);
	NS_ASSERT_MSG(prop < 1, "Ineffective time proportion has to be less than 1");
	m_ineffective_time_proportion = prop;
}

void
PLC_InformationRateModel::DoStartRx(double requiredInformationBits)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG((size_t) m_mcs < sizeof(s_mcs_info) / sizeof(struct McsInfo), "Unsupported Modulation and Coding Scheme");
	NS_ASSERT_MSG(requiredInformationBits, "Message with zero information");

	m_required_information_bits = requiredInformationBits;
	m_gathered_information_bits = 0;
	m_lastChangeTime = Now();
}

void
PLC_InformationRateModel::DoEvaluateChunk(void)
{
	NS_LOG_FUNCTION(this);

	double effective_duration_s = ((Now() - m_lastChangeTime).GetSeconds())*(1-m_ineffective_time_proportion);
	NS_LOG_LOGIC ("Effective duration: " << effective_duration_s);

	Ptr<SpectrumValue> sinr = m_interference->GetSinr();
	NS_LOG_LOGIC ("SINR: " << *sinr);

	SpectrumValue CapacityPerHertz = GetCapacity((*sinr), s_mcs_info[m_mcs].mod, s_mcs_info[m_mcs].cardinality);
	NS_LOG_LOGIC ("Capacity per hertz: " << CapacityPerHertz);

	Bands::const_iterator bi = CapacityPerHertz.ConstBandsBegin ();
	Values::const_iterator vi = CapacityPerHertz.ConstValuesBegin ();

	double chunk_bit_information = 0;
	while (bi != CapacityPerHertz.ConstBandsEnd ())
	{
		NS_ASSERT (vi != CapacityPerHertz.ConstValuesEnd ());
		double subchannel_capacity = (bi->fh - bi->fl) * (*vi);
		chunk_bit_information += subchannel_capacity * effective_duration_s;
		++bi;
		++vi;
	}
	NS_ASSERT (vi == CapacityPerHertz.ConstValuesEnd ());

	NS_LOG_LOGIC("Chunk information in bits: " << chunk_bit_information);

	m_gathered_information_bits += chunk_bit_information;

	NS_LOG_LOGIC("Bits required for decoding: " << m_required_information_bits);
	NS_LOG_LOGIC("Collected bits: " << m_gathered_information_bits);

	m_lastChangeTime = Now();
}

bool
PLC_InformationRateModel::DoEndRx(void)
{
	NS_LOG_FUNCTION(this);

	NS_LOG_INFO("Required bits: " << m_required_information_bits);
	NS_LOG_INFO("Gathered bits: " << m_gathered_information_bits);

	if (m_gathered_information_bits >= m_required_information_bits)
	{
		NS_LOG_INFO("PLC_InformationRateModel: reception successful");
		return true;
	}
	else
	{
		NS_LOG_INFO("PLC_InformationRateModel: reception failed");
		return false;
	}
}

}
