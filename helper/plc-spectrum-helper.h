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

#ifndef PLC_SPECTRUM_HELPER_H
#define PLC_SPECTRUM_HELPER_H

#include <ns3/object.h>
#include <ns3/random-variable.h>
#include <ns3/spectrum-value.h>
#include <ns3/spectrum-model.h>

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
 * Helper class to create spectrum models with equidistant
 * frequency samples
 */
class PLC_SpectrumModelHelper : public Object
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Create a spectrum model with lower band limit fl,
	 * higher band limit fh and numbands of subbands
	 *
	 * @param fl
	 * @param fh
	 * @param numbands
	 * @return Spectrum model
	 */
	Ptr<const SpectrumModel> GetSpectrumModel(double fl, double fh, size_t numbands);

	/**
	 * Get the spectrum model of the G3 standard
	 * @return
	 */
	Ptr<const SpectrumModel> GetG3SpectrumModel(void);

	/**
	 * @return The center frequency of a previous created spectrum model
	 * or 0 if none has been created before
	 */
	double GetCenterFreq(void);

private:
	void CreateSpectrumModel(void);

	double m_fl, m_fh, m_resolution, m_fc;
	size_t m_numbands;
	Ptr<SpectrumModel> m_spectrum_model;
};

/**
 *
 */
class PLC_TimeInvariantSpectrumHelper : public Object
{
public:
	static TypeId GetTypeId(void);

	PLC_TimeInvariantSpectrumHelper(Ptr<const SpectrumModel> sm);
	Ptr<SpectrumValue> GetPowerSpectralDensity(void) { return m_power_spectral_density; }

protected:
	Ptr<const SpectrumModel> 	m_spectrum_model;
	Ptr<SpectrumValue> 			m_power_spectral_density;
};

class PLC_SincSpectrumHelper : public PLC_TimeInvariantSpectrumHelper
{
public:
	static TypeId GetTypeId(void);

	PLC_SincSpectrumHelper(double f_c, double main_lobe_bw, double peakPwr, Ptr<const SpectrumModel> sm);

private:
	double m_f_c, m_main_lobe_bw, m_pwr;
};

}

#endif /* PLC_SPECTRUM_HELPER_H */
