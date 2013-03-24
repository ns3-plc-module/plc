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

#include <math.h>
#include "plc-spectrum-helper.h"

namespace ns3 {

////////////////////////////////// PLC_SpectrumModelHelper /////////////////////////////////////////////////

void PLC_SpectrumModelHelper::CreateSpectrumModel(void)
{
	std::vector<double> center_freqs;
	double f_cs = this->m_resolution / 2;

	size_t i;
	for (i = 0; i < this->m_numbands; i++) center_freqs.push_back(this->m_fl + f_cs + i * this->m_resolution);

	this->m_spectrum_model = Create<SpectrumModel> (center_freqs);
}

double PLC_SpectrumModelHelper::GetCenterFreq(void)
{
	if (m_spectrum_model == NULL) return 0;

	return (this->m_spectrum_model->Begin() + this->m_spectrum_model->GetNumBands() / 2)->fc;
}

Ptr<const SpectrumModel> PLC_SpectrumModelHelper::GetSpectrumModel(double fl, double fh, size_t numbands)
{
	m_fl = fl;
	m_fh = fh;
	m_numbands = numbands;
	m_resolution = (fh - fl) / numbands;

	CreateSpectrumModel();

	return this->m_spectrum_model;
}

Ptr<const SpectrumModel> PLC_SpectrumModelHelper::GetG3SpectrumModel(void)
{
	m_fl = G3_BAND_LOW;
	m_fh = G3_BAND_HIGH;
	m_numbands = G3_NSUBCARRIER;
	m_resolution = (m_fh - m_fl) / m_numbands;

	CreateSpectrumModel();

	return this->m_spectrum_model;
}

////////////////////////////////// PLC_SincSpectrumHelper /////////////////////////////////////////////////

PLC_SincSpectrumHelper::PLC_SincSpectrumHelper(double f_c, double main_lobe_bw, double peakPwr, Ptr<const SpectrumModel> sm) : PLC_TimeInvariantSpectrumHelper(sm), m_f_c(f_c), m_main_lobe_bw(main_lobe_bw), m_pwr(peakPwr)
{
	Bands::const_iterator b_it;
	Values::iterator v_it;
	for (b_it = this->m_spectrum_model->Begin(), v_it = this->m_power_spectral_density->ValuesBegin(); b_it != this->m_spectrum_model->End(), v_it != this->m_power_spectral_density->ValuesEnd(); b_it++, v_it++) {
		if (b_it->fc - f_c == 0)
			*v_it = pow(10, peakPwr/10);
		else {
			*v_it = pow(10, peakPwr/10) * pow((sin((b_it->fc - f_c) / (main_lobe_bw / 2)) / ((b_it->fc - f_c) / (main_lobe_bw / 2))), 2);
		}
	}
}

////////////////////////////////// PLC_NoiseFloorHelper /////////////////////////////////////////////////

PLC_NoiseFloorHelper::PLC_NoiseFloorHelper(double pwr, Ptr<const SpectrumModel> sm) : PLC_TimeInvariantSpectrumHelper(sm), m_pwr(pwr)
{
	Values::iterator v_it;
	for (v_it = this->m_power_spectral_density->ValuesBegin(); v_it != this->m_power_spectral_density->ValuesEnd(); v_it++) {
		*v_it = pwr;
	}
}


} // namespace ns3
