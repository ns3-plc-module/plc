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

#include <ns3/simulator.h>
#include <ns3/log.h>
#include "plc-defs.h"
#include "plc-interference.h"
#include "plc-value.h"

NS_LOG_COMPONENT_DEFINE ("PLC_Interference");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (PLC_Interference);

TypeId
PLC_Interference::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_Interference")
			.SetParent<Object>  ()
			.AddTraceSource  ("AllSignals",
							 "Sum of all signal PSDs at the receiver frontend",
							 MakeTraceSourceAccessor  (&PLC_Interference::m_sumSignalTracer))
			.AddTraceSource  ("RxSignal",
							 "PSD of the signal the receiver is currently locked to",
							 MakeTraceSourceAccessor  (&PLC_Interference::m_rxSignalTracer))
			.AddTraceSource  ("NoiseSignals",
							 "Sum of all interfering signals at the receiver frontend  (without noise floor)",
							 MakeTraceSourceAccessor  (&PLC_Interference::m_noiseSignalTracer))
			.AddTraceSource  ("SINR",
							 "Signal to Interference plus Noise Ratio while receiving",
							 MakeTraceSourceAccessor  (&PLC_Interference::m_SinrTracer))
			;
	return tid;
}

PLC_Interference::PLC_Interference () :
		m_receiving (false), m_allSignals (0), m_rxSignal (0), m_noiseSignals (0), m_noiseFloor (0)
{
}

void
PLC_Interference::DoDispose ()
{
	m_allSignals = 0;
	m_rxSignal = 0;
	m_noiseSignals = 0;
	m_noiseFloor = 0;
	m_sinr = 0;
	m_sinr_base = 0;
	Object::DoDispose ();
}

void
PLC_Interference::StartRx (Ptr<const SpectrumValue> rxPsd)
{
	PLC_LOG_FUNCTION (this << rxPsd);
	PLC_LOG_LOGIC (*rxPsd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	NS_ASSERT (rxPsd->GetSpectrumModel () == this->m_noiseSignals->GetSpectrumModel ());

	m_receiving = true;
	m_rxSignal = rxPsd;
	(*m_allSignals) +=  (*rxPsd);

	CalcSinr();

	m_rxSignalTracer (Simulator::Now (), rxPsd);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::AlterRxSignal (Ptr<const SpectrumValue> rxSignal)
{
	PLC_LOG_FUNCTION (this << rxSignal);
	NS_LOG_DEBUG ("RX signal difference: " << ((*m_rxSignal) - (*rxSignal)));

	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	(*m_allSignals)  =   (*m_allSignals) +  (*rxSignal) -  (*m_rxSignal);
	this->m_rxSignal = rxSignal;

	CalcSinr();

	m_rxSignalTracer (Simulator::Now (), rxSignal);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::EndRx (void)
{
	PLC_LOG_FUNCTION (this);

	(*m_allSignals) -=  (*m_rxSignal);
	(*m_sinr) = 0;
	m_sinr_base = 0;

	m_rxSignalTracer (Simulator::Now (), Create<SpectrumValue>  (m_allSignals->GetSpectrumModel ()));
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
	m_SinrTracer (Simulator::Now (), m_sinr);
}

void
PLC_Interference::AddInterferenceSignal (Ptr<const SpectrumValue> psd)
{
	PLC_LOG_FUNCTION (this);
	PLC_LOG_LOGIC (*psd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");

	(*m_noiseSignals) +=  (*psd);
	(*m_allSignals) +=  (*psd);

	if (m_receiving)
	{
		CalcSinr();
	}

	m_noiseSignalTracer (Simulator::Now (), m_noiseSignals);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::RemoveInterferenceSignal (Ptr<const SpectrumValue> psd)
{
	PLC_LOG_FUNCTION (this);
	PLC_LOG_LOGIC (*psd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");

	(*m_noiseSignals) -=  (*psd);
	(*m_allSignals) -=  (*psd);

	if (m_receiving)
	{
		CalcSinr();
	}

	m_noiseSignalTracer (Simulator::Now (), m_noiseSignals);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::SetNoiseFloor (Ptr<const SpectrumValue> noiseFloor)
{
	PLC_LOG_FUNCTION (this);
	PLC_LOG_LOGIC (*noiseFloor);
	m_noiseFloor = noiseFloor;
	m_noiseSignals = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());
	m_allSignals = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());
	m_sinr = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());

	(*m_sinr) = 0;

	m_sumSignalTracer (Simulator::Now (), m_allSignals);
	m_noiseSignalTracer (Simulator::Now (), m_noiseSignals);
	m_SinrTracer (Simulator::Now (), m_sinr);
}

Ptr<SpectrumValue>
PLC_Interference::GetSinr(void)
{
	PLC_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	return m_sinr;
}

double
PLC_Interference::GetTotalRxPower (void)
{
	PLC_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	return Pwr(*m_allSignals);
}

double
PLC_Interference::GetTotalNoisePower (void)
{
	PLC_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	SpectrumValue noise = (*m_noiseSignals) + (*m_noiseFloor);
	return Pwr(noise);
}

void
PLC_Interference::SetSinrBase(Ptr<const SpectrumValue> baseSinr)
{
	PLC_LOG_FUNCTION (this << baseSinr);
	m_sinr_base = baseSinr;
	CalcSinr ();
}

Ptr<const SpectrumValue>
PLC_Interference::GetSinrBase(void)
{
	PLC_LOG_FUNCTION (this);
	return m_sinr_base;
}

void
PLC_Interference::CalcSinr(void)
{
	PLC_LOG_FUNCTION (this);
	(*m_sinr) =  (*m_rxSignal) /  ( (*m_noiseSignals) + (*m_noiseFloor));
	PLC_LOG_LOGIC ("m_sinr: " << *m_sinr);

	if (m_sinr_base)
	{
		(*m_sinr) += (*m_sinr_base);
		PLC_LOG_LOGIC ("increased m_sinr: " << *m_sinr);
	}

	m_SinrTracer (Simulator::Now (), m_sinr);
}

}
