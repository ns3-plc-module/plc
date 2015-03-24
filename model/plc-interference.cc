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

#include <iomanip>

NS_LOG_COMPONENT_DEFINE ("PLC_Interference");

namespace ns3 {

bool IsPositive (Ptr<const SpectrumValue> psd)
{
	Bands::const_iterator bit = psd->ConstBandsBegin();
	Values::const_iterator vit = psd->ConstValuesBegin();

	bool ret = true;
	while (bit != psd->ConstBandsEnd())
	{
		NS_ASSERT (vit != psd->ConstValuesEnd());
		if (*vit < 0)
		{
			ret = false;
			break;
		}

		++bit;
		++vit;
	}

	return ret;
}

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
							 "Sum of all interfering signals at the receiver frontend",
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
PLC_Interference::InitializeRx (Ptr<const SpectrumValue> rxPsd)
{
	NS_LOG_FUNCTION (this << rxPsd);
	NS_LOG_LOGIC (*rxPsd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	NS_ASSERT (rxPsd->GetSpectrumModel () == this->m_noiseSignals->GetSpectrumModel ());

	m_receiving = true;
	m_rxSignal = rxPsd;
	(*m_allSignals) +=  (*rxPsd);

	NS_LOG_DEBUG ("m_rxSignal: " << (*m_rxSignal));
	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));

	CalcSinr();

	m_rxSignalTracer (Simulator::Now (), rxPsd);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::AlterRxSignal (Ptr<const SpectrumValue> rxSignal)
{
	NS_LOG_FUNCTION (this << rxSignal);
	NS_LOG_LOGIC ("Recent rxPsd: " << (*m_rxSignal));
	NS_LOG_LOGIC ("New rxPsd: " << (*rxSignal));
	NS_LOG_LOGIC ("Psd base:" << (*m_allSignals)-(*m_rxSignal));

	NS_ASSERT_MSG (m_receiving, "PLC_Interference object not in receiving mode");
	NS_ASSERT_MSG (m_noiseFloor, "Noise floor psd has to be set first before using PLC_Interference instance!");

	(*m_allSignals)  =   (*m_allSignals) +  (*rxSignal) -  (*m_rxSignal);
	this->m_rxSignal = rxSignal;

	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));

	CalcSinr();

	m_rxSignalTracer (Simulator::Now (), rxSignal);
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
}

void
PLC_Interference::EndRx (void)
{
	NS_LOG_FUNCTION (this);
	NS_LOG_LOGIC ("Recent rxPsd: " << (*m_rxSignal));

	m_receiving = false;
	(*m_allSignals) -=  (*m_rxSignal);
	(*m_sinr) = 0;
	m_sinr_base = 0;

	NS_LOG_DEBUG ("Remove m_rxSignal: " << (*m_rxSignal));
	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));

	NS_LOG_LOGIC ("Sum Psd: " << (*m_allSignals));

	m_rxSignalTracer (Simulator::Now (), Create<SpectrumValue>  (m_allSignals->GetSpectrumModel ()));
	m_sumSignalTracer (Simulator::Now (), m_allSignals);
	m_SinrTracer (Simulator::Now (), m_sinr);
}

void
PLC_Interference::AddInterferenceSignal (Ptr<const SpectrumValue> psd)
{
	NS_LOG_FUNCTION (this << psd);
	NS_LOG_LOGIC ("Interference psd: " << *psd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");

	(*m_noiseSignals) +=  (*psd);
	(*m_allSignals) +=  (*psd);

	NS_LOG_DEBUG ("Interference psd: " << *psd);
	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));

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
	NS_LOG_FUNCTION (this << psd);
	NS_LOG_LOGIC (*psd);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");

	(*m_noiseSignals) -=  (*psd);
	(*m_allSignals) -=  (*psd);

	NS_LOG_DEBUG ("Interference psd: " << *psd);
	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));
	NS_LOG_LOGIC ("m_noiseSignals: " << (*m_noiseSignals));

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
	NS_LOG_FUNCTION (this);
	NS_LOG_LOGIC (*noiseFloor);
	m_noiseFloor = noiseFloor;
	m_noiseSignals = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());
	m_allSignals = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());
	m_sinr = Create<SpectrumValue>  (noiseFloor->GetSpectrumModel ());

	(*m_sinr) = 0;
	(*m_noiseSignals) = (*noiseFloor);

	m_sumSignalTracer (Simulator::Now (), m_allSignals);
	m_noiseSignalTracer (Simulator::Now (), m_noiseSignals);
	m_SinrTracer (Simulator::Now (), m_sinr);
}

Ptr<SpectrumValue>
PLC_Interference::GetSinr(void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	return m_sinr;
}

double
PLC_Interference::GetTotalRxPower (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	return Pwr(*m_allSignals);
}

double
PLC_Interference::GetMeanRxPower (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	double meanPwr = Sum(*m_allSignals) / (m_allSignals->GetSpectrumModel()->GetNumBands());

	NS_LOG_LOGIC ("Mean power: " << meanPwr);
	NS_LOG_DEBUG ("m_noiseSignals: " << std::setprecision(15) << (*m_noiseSignals));
	NS_LOG_DEBUG ("m_allSignals: "  << std::setprecision(15) << (*m_allSignals));

	return meanPwr;
}

double
PLC_Interference::GetTotalNoisePower (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_noiseFloor, "PLC_Interference: Noise floor psd has to be set before using interference instance!");
	NS_LOG_DEBUG ("m_noiseSignals before: " << std::setprecision(15) << (*m_noiseSignals));
	SpectrumValue noise = (*m_noiseSignals);
	NS_LOG_DEBUG ("m_noiseSignals after: " << std::setprecision(15) << (*m_noiseSignals));
	return Pwr(noise);
}

void
PLC_Interference::SetSinrBase(Ptr<const SpectrumValue> baseSinr)
{
	NS_LOG_FUNCTION (this << baseSinr);
	m_sinr_base = baseSinr;

	if (m_receiving)
	{
		CalcSinr ();
	}
}

Ptr<const SpectrumValue>
PLC_Interference::GetSinrBase(void)
{
	NS_LOG_FUNCTION (this);
	return m_sinr_base;
}

void
PLC_Interference::CalcSinr(void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT (m_rxSignal);

	(*m_sinr) =  (*m_rxSignal) /  (*m_noiseSignals);

	if (m_sinr_base)
	{
		(*m_sinr) += (*m_sinr_base);
		NS_LOG_LOGIC ("increased m_sinr: " << *m_sinr);
	}

	m_SinrTracer (Simulator::Now (), m_sinr);
}

}
