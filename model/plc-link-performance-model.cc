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
#include "plc-phy.h"

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
	m_mcs = BPSK_1_2;
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
PLC_InformationRateModel::s_mcs_info[10] =
{
		{QAM, 2, 1/4}, 		// BPSK_1_4
		{QAM, 2, 1/2}, 		// BPSK_1_2
		{QAM, 4, 1/2}, 		// QPSK_1_2
		{QAM, 16, 1/2}, 	// QAM16_1_2
		{QAM, 64, 16/21}, 	// QAM64_16_21
		{QAM, 2, 0}, 		// BPSK_RATELESS
		{QAM, 4, 0}, 		// QAM4_RATELESS
		{QAM, 16, 0}, 		// QAM16_RATELESS
		{QAM, 32, 0},		// QAM32_RATELESS
		{QAM, 64, 0},		// QAM64_RATELESS
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
{
	NS_LOG_FUNCTION(this);
	m_gathered_information_bits = 0;
	m_required_information_bits = 0;
	m_last_symbol_residual = 0;
	m_symbol_duration = Seconds (0);
	m_guard_interval_duration = Seconds (0);
}

void
PLC_InformationRateModel::DoStartRx(double requiredInformationBits)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG((size_t) m_mcs < sizeof(s_mcs_info) / sizeof(struct McsInfo), "Unsupported Modulation and Coding Scheme");
	NS_ASSERT_MSG(requiredInformationBits, "Message with zero information");

	m_required_information_bits = requiredInformationBits;
	m_gathered_information_bits = 0;
	m_lastChangeTime = Now ();
}

double
PLC_InformationRateModel::CalculateChunkGuardIntervals (Time chunk_duration)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT (m_symbol_duration > m_guard_interval_duration);

	int64_t symbol_residual = chunk_duration.GetInteger() % m_symbol_duration.GetInteger();

	NS_LOG_LOGIC ("Chunk duration: " << chunk_duration  << " (" << chunk_duration.GetInteger() << ")");
	NS_LOG_LOGIC ("Symbol duration: " << m_symbol_duration << " (" << m_symbol_duration.GetInteger() << ")");
	NS_LOG_LOGIC ("Guard interval duration: " << m_guard_interval_duration << " (" << m_guard_interval_duration.GetInteger() << ")");
	NS_LOG_LOGIC ("Last symbol residual: " << m_last_symbol_residual);
	NS_LOG_LOGIC ("New symbol residual: " << symbol_residual);

	double chunk_guard_intervals = 0;
	if (m_last_symbol_residual < m_guard_interval_duration.GetInteger())
	{
		NS_LOG_LOGIC ("Consider remaining guard interval fraction of first symbol");

		int64_t first_guard_interval_residual = m_guard_interval_duration.GetInteger() - m_last_symbol_residual;
		NS_LOG_LOGIC ("First guard interval residual: " << first_guard_interval_residual);

		if (first_guard_interval_residual > chunk_duration.GetInteger())
		{
			NS_LOG_LOGIC ("Guard interval of first symbol is not completed with current chunk");
			chunk_guard_intervals += (double) chunk_duration.GetInteger() / m_guard_interval_duration.GetInteger();
		}
		else
		{
			NS_LOG_LOGIC ("Considering guard intervals of completed chunk symbols");
			chunk_guard_intervals += (double) first_guard_interval_residual / m_guard_interval_duration.GetInteger();
			chunk_guard_intervals += chunk_duration.GetInteger() / m_symbol_duration.GetInteger();

			if (symbol_residual >= m_guard_interval_duration.GetInteger())
			{
				NS_LOG_LOGIC ("Guard interval of last chunk symbol complete");
				chunk_guard_intervals += 1;
			}
			else
			{
				NS_LOG_LOGIC ("Guard interval of last chunk not complete");
				chunk_guard_intervals += (double) symbol_residual / m_guard_interval_duration.GetInteger();
			}
		}
	}
	else if (chunk_duration > m_symbol_duration - m_guard_interval_duration)
	{
		NS_LOG_LOGIC ("Considering guard intervals of completed chunk symbols");
		chunk_guard_intervals += chunk_duration.GetInteger() / m_symbol_duration.GetInteger();

		if (symbol_residual >= m_guard_interval_duration.GetInteger())
		{
			NS_LOG_LOGIC ("Guard interval of last chunk symbol complete");
			chunk_guard_intervals += 1;
		}
		else
		{
			NS_LOG_LOGIC ("Guard interval of last chunk not complete");
			chunk_guard_intervals += (double) symbol_residual / m_guard_interval_duration.GetInteger();
		}

	}
	m_last_symbol_residual = symbol_residual;

	NS_LOG_LOGIC ("chunk_duration_s: " << chunk_duration.GetSeconds());
	NS_LOG_LOGIC ("guard_interval_duration_s: " << m_guard_interval_duration.GetSeconds());
	NS_LOG_LOGIC ("chunk guard intervals: " << chunk_guard_intervals);

	return chunk_duration.GetSeconds() - (m_guard_interval_duration.GetSeconds()*chunk_guard_intervals);
}

void
PLC_InformationRateModel::DoEvaluateChunk(void)
{
	NS_LOG_FUNCTION(this);

	Time chunk_duration = Now () - m_lastChangeTime;
	double effective_duration_s = chunk_duration.GetSeconds();

	if (m_guard_interval_duration > Seconds(0))
	{
		// Determine effective rx duration, i.e. (virtually) remove guard intervals
		double chunk_guard_intervals = CalculateChunkGuardIntervals (chunk_duration);
		effective_duration_s -= m_guard_interval_duration.GetSeconds() * chunk_guard_intervals;
	}

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
