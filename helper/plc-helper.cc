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

#include "plc-helper.h"
#include <ns3/node.h>
#include <ns3/object-factory.h>
#include <ns3/log.h>

namespace ns3 {

////////////////////////////////// PLC_ImpedanceHelper /////////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_ImpedanceHelper);

TypeId
PLC_ImpedanceHelper::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_ImpedanceHelper")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_ImpedanceHelper::PLC_ImpedanceHelper(Ptr<const SpectrumModel> sm)
	: m_spectrum_model(sm)
{
	m_rmin = 0;
	m_rmax = 500;
	m_imin = 0;
	m_imax = 500;
}

Ptr<PLC_FreqSelectiveImpedance>
PLC_ImpedanceHelper::CreateIdleTransformerImpedance(double Rt, double Ct, double Lt)
{
 	PLC_FreqSelectiveValue Zp1(m_spectrum_model);
 	PLC_FreqSelectiveValue Zp2(m_spectrum_model);

 	size_t i;
 	Bands::const_iterator bit = m_spectrum_model->Begin();
 	for (i = 0; i < m_spectrum_model->GetNumBands(); i++)
 	{
 		double f = bit->fc;
 		Zp1[i] = PLC_Value(0, 2*M_PI*f*Lt);
 		Zp2[i] = PLC_Value(Rt, 1/(2*M_PI*f*Ct));
 		++bit;
 	}

 	return CreateObject<PLC_FreqSelectiveImpedance>(((Zp1*Zp2)/(Zp1+Zp2)));
}

Ptr<PLC_FreqSelectiveImpedance>
PLC_ImpedanceHelper::CreateSeriesResonanceImpedance(double R, double C, double L)
{
	Ptr<PLC_FreqSelectiveImpedance> ret = CreateObject<PLC_FreqSelectiveImpedance> (m_spectrum_model);

	size_t i;
 	Bands::const_iterator bit = m_spectrum_model->Begin();
 	for (i = 0; i < m_spectrum_model->GetNumBands(); i++)
 	{
 		double f = bit->fc;
 		(*ret)[i] = PLC_Value(R, 2*M_PI*f*L - (1/(2*M_PI*f*C)));
 		++bit;
 	}

 	return ret;
}

void
PLC_ImpedanceHelper::SetConstImpedanceBounds(double rmin, double rmax, double imin, double imax)
{
	NS_ASSERT(rmin >= 0 && rmin <= rmax && imin <= imax);
	m_rmin = rmin;
	m_rmax = rmax;
	m_imin = imin;
	m_imax = imax;
}

Ptr<PLC_ConstImpedance>
PLC_ImpedanceHelper::CreateConstImpedance()
{
	PLC_Value val(m_uni.GetValue(m_rmin, m_rmax), m_uni.GetValue(m_imin, m_imax));
	return CreateObject<PLC_ConstImpedance> (m_spectrum_model, val);
}

void
PLC_ImpedanceHelper::SetFreqSelectiveImpedanceBounds(double Rmin, double Rmax, double Qmin, double Qmax, double f0min, double f0max)
{
	NS_ASSERT(Rmin >= 0 && Rmin <= Rmax && Qmin >= 0 && Qmin <= Qmax && f0min >= 0 && f0min <= f0max);
	m_Rmin = Rmin;
	m_Rmax = Rmax;
	m_Qmin = Qmin;
	m_Qmax = Qmax;
	m_f0min = f0min;
	m_f0max = f0max;
}

Ptr<PLC_FreqSelectiveImpedance>
PLC_ImpedanceHelper::CreateFreqSelectiveImpedance()
{
	double R = m_uni.GetValue(m_Rmin, m_Rmax);
	double Q = m_uni.GetValue(m_Qmin, m_Qmax);
	double f0 = m_uni.GetValue(m_f0min, m_f0max);

	return CreateObject<PLC_FreqSelectiveImpedance> (m_spectrum_model, R, Q, f0);
}

void
PLC_ImpedanceHelper::SetTimeVariantFreqSelectiveImpedanceBounds(double RoffsMin, double RoffsMax, double QoffsMin, double QoffsMax, double f0offsMin, double f0offsMax, double RamplMin, double RamplMax, double QamplMin, double QamplMax, double f0amplMin, double f0amplMax, double phiMin, double phiMax)
{
	m_RoffsMin = RoffsMin;
	m_RoffsMax = RoffsMax;
	m_QoffsMin = QoffsMin;
	m_QoffsMax = QoffsMax;
	m_f0offsMin = f0offsMin;
	m_f0offsMax = f0offsMax;
	m_RamplMin = RamplMin;
	m_RamplMax = RamplMax;
	m_QamplMin = QamplMin;
	m_QamplMax = QamplMax;
	m_f0amplMin = f0amplMin;
	m_f0amplMax = f0amplMax;
	m_phiMin = phiMin;
	m_phiMax = phiMax;
}

Ptr<PLC_TimeVariantFreqSelectiveImpedance>
PLC_ImpedanceHelper::CreateTimeVariantFreqSelectiveImpedance()
{
	PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet paramSet;
	paramSet.R_offset = m_uni.GetValue(m_RoffsMin, m_RoffsMax);
	paramSet.Q_offset = m_uni.GetValue(m_QoffsMin, m_QoffsMax);
	paramSet.f_0_offset = m_uni.GetValue(m_f0offsMin, m_f0offsMax);
	paramSet.R_amplitude = m_uni.GetValue(m_RamplMin, m_RamplMax);
	paramSet.Q_amplitude = m_uni.GetValue(m_QamplMin, m_QamplMax);
	paramSet.f0_amplitude = m_uni.GetValue(m_f0amplMin, m_f0amplMax);
	paramSet.phi = m_uni.GetValue(m_phiMin, m_phiMax);

	return CreateObject<PLC_TimeVariantFreqSelectiveImpedance> (m_spectrum_model, paramSet);
}

////////////////////////////////// PLC_ChannelHelper /////////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_ChannelHelper);

TypeId
PLC_ChannelHelper::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_ChannelHelper")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_ChannelHelper::PLC_ChannelHelper ()
{
	m_graph = CreateObject<PLC_Graph> ();
	m_channel = CreateObject<PLC_Channel> ();
	m_channel->SetGraph(m_graph);
}

PLC_ChannelHelper::PLC_ChannelHelper(Ptr<const SpectrumModel> sm)
	: m_spectrum_model(sm)
{
	m_graph = CreateObject<PLC_Graph> ();
	m_channel = CreateObject<PLC_Channel> ();
	m_channel->SetGraph(m_graph);
}

void
PLC_ChannelHelper::SetSpectrumModel(Ptr<const SpectrumModel> sm)
{
	m_spectrum_model = sm;
}

void
PLC_ChannelHelper::Install(PLC_NodeList nodes)
{
	m_nodes = nodes;

	PLC_NodeList::iterator nit;
	for (nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		m_graph->AddNode(*nit);
	}
}

} // namespace ns3
