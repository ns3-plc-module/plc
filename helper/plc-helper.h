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

#ifndef PLC_HELPER_H
#define PLC_HELPER_H

#include <ns3/object.h>
#include <ns3/random-variable.h>

#include "ns3/plc-node.h"
#include "ns3/plc-outlet.h"
#include "ns3/plc-noise.h"
#include "ns3/plc-edge.h"
#include "ns3/plc-channel.h"
#include "ns3/plc-phy.h"

namespace ns3 {

#define CELENEC_A_LOW	9e3
#define CELENEC_A_HIGH	95e3
#define CELENEC_B_LOW	95e3
#define CELENEC_B_HIGH	125e3
#define CELENEC_C_LOW	125e3
#define CELENEC_C_HIGH	140e3
#define CELENEC_D_LOW	140e3
#define CELENEC_D_HIGH	148.5e3

#define G3_BAND_LOW		35e3
#define G3_BAND_HIGH	91e3
#define G3_NSUBCARRIER	36

/**
 * Helper class for generating random impedance values
 */
class PLC_ImpedanceHelper : public Object
{
public:
	static TypeId GetTypeId(void);

	PLC_ImpedanceHelper(Ptr<const SpectrumModel> sm);

	Ptr<PLC_FreqSelectiveImpedance> CreateIdleTransformerImpedance(double R, double C, double L);

	Ptr<PLC_FreqSelectiveImpedance> CreateSeriesResonanceImpedance(double R, double C, double L);

	void SetConstImpedanceBounds(double rmin, double rmax, double imin, double imax);
	Ptr<PLC_ConstImpedance> CreateConstImpedance();

	void SetFreqSelectiveImpedanceBounds(double Rmin, double Rmax, double Qmin, double Qmax, double f0min, double f0max);
	Ptr<PLC_FreqSelectiveImpedance> CreateFreqSelectiveImpedance();

	// TODO: PLC_TimeVariantConstImpedance
	void SetTimeVariantFreqSelectiveImpedanceBounds(double RoffsMin, double RoffsMax, double QoffsMin, double QoffsMax, double f0offsMin, double f0offsMax, double RamplMin, double RamplMax, double QamplMin, double QamplMax, double f0amplMin, double f0amplMax, double phiMin, double phiMax);
	Ptr<PLC_TimeVariantFreqSelectiveImpedance> CreateTimeVariantFreqSelectiveImpedance();

private:
	Ptr<const SpectrumModel> m_spectrum_model;

	UniformVariable m_uni;
	double m_rmin, m_rmax, m_imin, m_imax;
	double m_Rmin, m_Rmax, m_Qmin, m_Qmax, m_f0min, m_f0max;
	double m_RoffsMin, m_RoffsMax, m_QoffsMin, m_QoffsMax, m_f0offsMin, m_f0offsMax, m_RamplMin, m_RamplMax, m_QamplMin, m_QamplMax, m_f0amplMin, m_f0amplMax, m_phiMin, m_phiMax;
};

class PLC_ChannelHelper : public Object
{
public:
	static TypeId GetTypeId(void);

	PLC_ChannelHelper();
	PLC_ChannelHelper(Ptr<const SpectrumModel> sm);

	void SetSpectrumModel(Ptr<const SpectrumModel> sm);
	Ptr<PLC_Channel> GetChannel(void) { return m_channel; }

	void Install(PLC_NodeList nodes);

private:
	Ptr<const SpectrumModel> m_spectrum_model;
	Ptr<PLC_Graph>		m_graph;
	Ptr<PLC_Channel>	m_channel;

	PLC_NodeList 		m_nodes;
};

}

#endif /* PLC_HELPER_H */
