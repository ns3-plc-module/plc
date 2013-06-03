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

#include <sstream>
#include <math.h>
#include <ns3/output-stream-wrapper.h>
#include <ns3/fatal-error.h>
#include "plc-output-helper.h"

namespace ns3 {

////////////////////////////////// PLC_OutputHelper /////////////////////////////////////////////////

void
PLC_OutputHelper::PrintComplex(std::string name, Ptr<const PLC_ValueBase> value)
{
	Ptr<const SpectrumModel> sm = value->GetSpectrumModel();

	OutputStreamWrapper dwrapper (name+".dat", std::ios_base::out);
	std::ostream *dos = dwrapper.GetStream ();

	OutputStreamWrapper pwrapper (name+".gpl", std::ios_base::out);
	std::ostream *pos = dwrapper.GetStream ();

	(*pos) << "set terminal pdf" << std::endl;
	(*pos) << "set terminal pdf" << std::endl;
	(*pos) << "set output '" << name <<".pdf'" << std::endl;
//
//	set xlabel 't [ms]'
//	set ylabel 'f [MHz]'
//	set zlabel '|Z| [$\Omega$]' offset 3,0
//	set ytics offset 1,0
//	set xtics offset 0,-0.2
//	set palette gray
//	set ticslevel 0
//
//	splot 'tv-imp.txt' with pm3d


	switch (value->GetValueType())
	{
		case (PLC_ValueBase::CONSTANT):
		{
			Ptr<const PLC_ConstValue> val = StaticCast<const PLC_ConstValue, const PLC_ValueBase> (value);
			std::complex<double> v = val->GetValue();
			(*dos) << sm->Begin()->fc << " " << v.real() << " " << v.imag() << std::endl;
			(*dos) << (--sm->End())->fc << " " << v.real() << " " << v.imag() << std::endl;
			break;
		}
		case (PLC_ValueBase::FREQ_SELECTIVE):
		{
			Ptr<const PLC_FreqSelectiveValue> val = StaticCast<const PLC_FreqSelectiveValue, const PLC_ValueBase> (value);
			Bands::const_iterator sit = sm->Begin();
			for (uint32_t i=0; i<val->GetNumBands(); i++)
			{
				std::complex<double> v = (*val)[i];
				// frequency in MHz
				(*dos) << sit->fc*1e-6 << " " << v.real() << " " << v.imag() << std::endl;
				++sit;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
		{
			Ptr<const PLC_TimeVariantConstValue> val = StaticCast<const PLC_TimeVariantConstValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				std::complex<double> v = (*val)[t];
				(*dos) << t*res << " " << v.real() << " " << v.imag() << std::endl;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
		{
			Ptr<const PLC_TimeVariantFreqSelectiveValue> val = StaticCast<const PLC_TimeVariantFreqSelectiveValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				Bands::const_iterator sit = sm->Begin();
				for (uint32_t i=0; i<val->GetNumBands(); i++)
				{
					std::complex<double> v = (*val)[t][i];
					(*dos) << t*res << " " << sit->fc*1e-6 << " " << v.real() << " " << v.imag() << std::endl;
					++sit;
				}
				(*dos) << std::endl;
			}
			break;
		}
		default:
		{
			NS_FATAL_ERROR("Unknown value type. Nothing printed to file");
			break;
		}
	}
}

void
PLC_OutputHelper::PrintAbsolute(std::string fileName, Ptr<const PLC_ValueBase> value)
{
	Ptr<const SpectrumModel> sm = value->GetSpectrumModel();
	OutputStreamWrapper wrapper (fileName, std::ios_base::out);
	std::ostream *os = wrapper.GetStream ();

	switch (value->GetValueType())
	{
		case (PLC_ValueBase::CONSTANT):
		{
			Ptr<const PLC_ConstValue> val = StaticCast<const PLC_ConstValue, const PLC_ValueBase> (value);
			std::complex<double> v = val->GetValue();
			(*os) << sm->Begin()->fc << " " << std::abs(v) << std::endl;
			(*os) << (--sm->End())->fc << " " << std::abs(v) << std::endl;
			break;
		}
		case (PLC_ValueBase::FREQ_SELECTIVE):
		{
			Ptr<const PLC_FreqSelectiveValue> val = StaticCast<const PLC_FreqSelectiveValue, const PLC_ValueBase> (value);
			Bands::const_iterator sit = sm->Begin();
			for (uint32_t i=0; i<val->GetNumBands(); i++)
			{
				// frequency in MHz
				(*os) << sit->fc*1e-6 << " " << std::abs((*val)[i]) << std::endl;
				++sit;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
		{
			Ptr<const PLC_TimeVariantConstValue> val = StaticCast<const PLC_TimeVariantConstValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				(*os) << t*res << " " << std::abs((*val)[t]) << std::endl;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
		{
			Ptr<const PLC_TimeVariantFreqSelectiveValue> val = StaticCast<const PLC_TimeVariantFreqSelectiveValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				Bands::const_iterator sit = sm->Begin();
				for (uint32_t i=0; i<val->GetNumBands(); i++)
				{
					(*os) << t*res << " " << sit->fc*1e-6 << " " << std::abs((*val)[t][i]) << std::endl;
					++sit;
				}
				(*os) << std::endl;
			}
			break;
		}
		default:
		{
			NS_FATAL_ERROR("Unknown value type. Nothing printed to file");
			break;
		}
	}
}

void
PLC_OutputHelper::PrintBode(std::string prefix, Ptr<const PLC_ValueBase> value)
{
	Ptr<const SpectrumModel> sm = value->GetSpectrumModel();

	std::string magnFile = prefix;
	magnFile += "-magnitude.dat";

	std::string phaseFile = prefix;
	phaseFile += "-phase.dat";

	OutputStreamWrapper wrapper1 (magnFile, std::ios_base::out);
	std::ostream *os1 = wrapper1.GetStream ();

	OutputStreamWrapper wrapper2 (phaseFile, std::ios_base::out);
	std::ostream *os2 = wrapper2.GetStream ();

	switch (value->GetValueType())
	{
		case (PLC_ValueBase::CONSTANT):
		{
			Ptr<const PLC_ConstValue> val = StaticCast<const PLC_ConstValue, const PLC_ValueBase> (value);
			std::complex<double> v = val->GetValue();
			(*os1) << sm->Begin()->fc << " " << 20*std::log10(std::abs(v)) << std::endl;
			(*os2) << sm->Begin()->fc << " " << std::arg(v) << std::endl;
			(*os1) << (--sm->End())->fc << " " << 20*std::log10(std::abs(v)) << std::endl;
			(*os2) << (--sm->End())->fc << " " << std::arg(v) << std::endl;
			break;
		}
		case (PLC_ValueBase::FREQ_SELECTIVE):
		{
			Ptr<const PLC_FreqSelectiveValue> val = StaticCast<const PLC_FreqSelectiveValue, const PLC_ValueBase> (value);
			Bands::const_iterator sit = sm->Begin();
			for (uint32_t i=0; i<val->GetNumBands(); i++)
			{
				// frequency in MHz
				(*os1) << sit->fc*1e-6 << " " << 20*std::log10(std::abs((*val)[i])) << std::endl;
				(*os2) << sit->fc*1e-6 << " " << std::arg((*val)[i]) << std::endl;
				++sit;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
		{
			Ptr<const PLC_TimeVariantConstValue> val = StaticCast<const PLC_TimeVariantConstValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				(*os1) << t*res << " " << 20*std::log10(std::abs((*val)[t])) << std::endl;
				(*os2) << t*res << " " << std::arg((*val)[t]) << std::endl;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
		{
			Ptr<const PLC_TimeVariantFreqSelectiveValue> val = StaticCast<const PLC_TimeVariantFreqSelectiveValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				Bands::const_iterator sit = sm->Begin();
				for (uint32_t i=0; i<val->GetNumBands(); i++)
				{
					(*os1) << t*res << " " << sit->fc*1e-6 << " " << 20*std::log10(std::abs((*val)[t][i])) << std::endl;
					(*os2) << t*res << " " << sit->fc*1e-6 << " " << std::arg((*val)[t][i]) << std::endl;
					++sit;
				}
				(*os1) << std::endl;
				(*os2) << std::endl;
			}
			break;
		}
		default:
		{
			NS_FATAL_ERROR("Unknown value type. Nothing printed to file");
			break;
		}
	}
}

void
PLC_OutputHelper::PrintSeparatedBode(std::string prefix, Ptr<const PLC_ValueBase> value)
{
	Ptr<const SpectrumModel> sm = value->GetSpectrumModel();

	std::string magnFile = prefix;
	magnFile += "-magnitude.dat";

	std::string phaseFile = prefix;
	phaseFile += "-phase.dat";

	OutputStreamWrapper wrapper1 (magnFile, std::ios_base::out);
	std::ostream *os1 = wrapper1.GetStream ();

	OutputStreamWrapper wrapper2 (phaseFile, std::ios_base::out);
	std::ostream *os2 = wrapper2.GetStream ();

	switch (value->GetValueType())
	{
		case (PLC_ValueBase::CONSTANT):
		{
			Ptr<const PLC_ConstValue> val = StaticCast<const PLC_ConstValue, const PLC_ValueBase> (value);
			std::complex<double> v = val->GetValue();
			(*os1) << sm->Begin()->fc << " " << 20*std::log10(std::abs(v)) << std::endl;
			(*os2) << sm->Begin()->fc << " " << std::arg(v) << std::endl;
			(*os1) << (--sm->End())->fc << " " << 20*std::log10(std::abs(v)) << std::endl;
			(*os2) << (--sm->End())->fc << " " << std::arg(v) << std::endl;
			break;
		}
		case (PLC_ValueBase::FREQ_SELECTIVE):
		{
			Ptr<const PLC_FreqSelectiveValue> val = StaticCast<const PLC_FreqSelectiveValue, const PLC_ValueBase> (value);
			Bands::const_iterator sit = sm->Begin();
			for (uint32_t i=0; i<val->GetNumBands(); i++)
			{
				// frequency in MHz
				(*os1) << sit->fc*1e-6 << " " << 20*std::log10(std::abs((*val)[i])) << std::endl;
				(*os2) << sit->fc*1e-6 << " " << std::arg((*val)[i]) << std::endl;
				++sit;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
		{
			Ptr<const PLC_TimeVariantConstValue> val = StaticCast<const PLC_TimeVariantConstValue, const PLC_ValueBase> (value);
			// time steps in ms
			double res = PLC_Time::GetResolutionS()*10e3;
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				(*os1) << t*res << " " << 20*std::log10(std::abs((*val)[t])) << std::endl;
				(*os2) << t*res << " " << std::arg((*val)[t]) << std::endl;
			}
			break;
		}
		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
		{
			Ptr<const PLC_TimeVariantFreqSelectiveValue> val = StaticCast<const PLC_TimeVariantFreqSelectiveValue, const PLC_ValueBase> (value);
			size_t t;
			for (t=0; t<val->GetNumTimeSlots(); t++)
			{
				std::stringstream ss1;
				ss1 << prefix << "-magnitude-ts" << t << ".dat";
				std::string magnFile = ss1.str ();

				std::stringstream ss2;
				ss2 << prefix << "-phase-ts" << t << ".dat";
				std::string phaseFile = ss2.str ();

				OutputStreamWrapper wrapper1 (magnFile, std::ios_base::out);
				std::ostream *os1 = wrapper1.GetStream ();

				OutputStreamWrapper wrapper2 (phaseFile, std::ios_base::out);
				std::ostream *os2 = wrapper2.GetStream ();

				Bands::const_iterator sit = sm->Begin();
				for (uint32_t i=0; i<val->GetNumBands(); i++)
				{
					(*os1) << sit->fc*1e-6 << " " << 20*std::log10(std::abs((*val)[t][i])) << std::endl;
					(*os2) << sit->fc*1e-6 << " " << std::arg((*val)[t][i]) << std::endl;
					++sit;
				}
			}
			break;
		}
		default:
		{
			NS_FATAL_ERROR("Unknown value type. Nothing printed to file");
			break;
		}
	}
}

}
