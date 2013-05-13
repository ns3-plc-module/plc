/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012
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

#include <ns3/log.h>
#include <ns3/type-id.h>
#include "plc-cable.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("PLC_Cable");
NS_OBJECT_ENSURE_REGISTERED(PLC_Cable);
NS_OBJECT_ENSURE_REGISTERED(PLC_ThreeCoreConcentricCable);
NS_OBJECT_ENSURE_REGISTERED(PLC_FourSectorPowerSupplyCable);
NS_OBJECT_ENSURE_REGISTERED(PLC_AL3x95XLPE_Cable);
NS_OBJECT_ENSURE_REGISTERED(PLC_NAYY150SE_Cable);
NS_OBJECT_ENSURE_REGISTERED(PLC_NAYY50SE_Cable);
NS_OBJECT_ENSURE_REGISTERED(PLC_NYCY70SM35_Cable);

TypeId
PLC_Cable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_Cable")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_Cable::PLC_Cable(Ptr<const SpectrumModel> sm)
	: m_spectrum_model(sm)
{
	z_c 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);
	gamma 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);
}

PLC_Cable::PLC_Cable (const PLC_FreqSelectiveResistance& R, const PLC_FreqSelectiveConductance& G, const PLC_FreqSelectiveInductance& L, const PLC_FreqSelectiveCapacitance& C, Ptr<const SpectrumModel> sm)
	: m_spectrum_model(sm)
{
	NS_ASSERT(R.size() == sm->GetNumBands());
	NS_ASSERT(G.size() == sm->GetNumBands());
	NS_ASSERT(C.size() == sm->GetNumBands());
	NS_ASSERT(L.size() == sm->GetNumBands());

	uint32_t cIdx = sm->GetNumBands()/2;

	this->R = R;
	this->G = G;
	this->L = L;
	this->C = C;
	this->v = 1 / sqrt(L[cIdx]*C[cIdx]);

	z_c 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);
	gamma 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);

	this->CalcCharImp();
	this->CalcTransConst();
}

void
PLC_Cable::SetSpectrumModel(Ptr<const SpectrumModel> sm)
{
	m_spectrum_model = sm;
	z_c 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);
	gamma 	= CreateObject<PLC_FreqSelectiveImpedance>(sm);
}

void
PLC_Cable::DoDispose ()
{
	z_c = 0;
	gamma = 0;
	m_spectrum_model = 0;
}

void
PLC_Cable::CalcCharImp (void)
{
	unsigned int i;
	Bands::const_iterator it;
	for (it = this->z_c->GetSpectrumModel()->Begin(), i = 0; it != this->z_c->GetSpectrumModel()->End(); it++, i++) {
		double f = it->fc;
		(*this->z_c)[i] = sqrt(PLC_ImpedanceValue(R[i], 2*M_PI*f*L[i]) / PLC_ImpedanceValue(G[i], 2*M_PI*f*C[i]));
	}
}

void
PLC_Cable::CalcTransConst (void)
{
	unsigned int i;
	Bands::const_iterator it;
	for (it = this->gamma->GetSpectrumModel()->Begin(), i = 0; it != this->gamma->GetSpectrumModel()->End(); it++, i++) {
		double f = it->fc;
		(*this->gamma)[i] = sqrt(PLC_ImpedanceValue(R[i], 2*M_PI*f*L[i]) * PLC_ImpedanceValue(G[i], 2*M_PI*f*C[i]));
	}
}

Ptr<const PLC_FreqSelectiveImpedance>
PLC_Cable::GetCharImp(void) const
{
	return this->z_c;
}

Ptr<const PLC_FreqSelectiveImpedance>
PLC_Cable::GetTransConst(void) const
{
	return this->gamma;
}

TypeId
PLC_ThreeCoreConcentricCable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_ThreeCoreConcentricCable")
    		.SetParent<PLC_Cable> ()
    		;
	return tid;
}

PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable(double eps_r, double kappa, double r_a, double r_i, double tand, Ptr<const SpectrumModel> sm) : PLC_Cable(sm)
{
	Calculate(eps_r, kappa, r_a, r_i, tand, sm);
}

PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable(PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, PLC_FreqSelectiveRealValue tand, Ptr<const SpectrumModel> sm) : PLC_Cable(sm)
{
	Calculate(eps_r, kappa, r_a, r_i, tand, sm);
}

void PLC_ThreeCoreConcentricCable::Calculate(double eps_r, double kappa, double r_a, double r_i, double tand, Ptr<const SpectrumModel> sm)
{
	double C_const = (2*M_PI*EPS_0*eps_r)/log(r_a/r_i);
	double L_const = (MU_0/(2*M_PI))*log(r_a/r_i);

	this->C = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), C_const);
	this->L = PLC_FreqSelectiveInductance(sm->GetNumBands(), L_const);
	this->v = 1 / sqrt(L_const*C_const);

	Bands::const_iterator it;
	for (it = sm->Begin(); it != sm->End(); it++) {
		double f = it->fc;
		this->R.push_back(0.5*sqrt(f*MU_0/(kappa*M_PI) * (1/r_a + 1/r_i)));
		this->G.push_back(2*M_PI*f*C_const*tand);
	}

	this->CalcCharImp();
	this->CalcTransConst();
}

void PLC_ThreeCoreConcentricCable::Calculate(PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, PLC_FreqSelectiveRealValue tand, Ptr<const SpectrumModel> sm)
{
	NS_ASSERT_MSG (sm->GetNumBands() == eps_r.size(), "Vector of frequency selective permittivity eps_r has different size than spectrum model");
	NS_ASSERT_MSG (sm->GetNumBands() == tand.size(), "Vector of frequency selective loss tangent tand has different size than spectrum model");

	double L_const = (MU_0/(2*M_PI))*log(r_a/r_i);
	this->L = PLC_FreqSelectiveInductance(sm->GetNumBands(), L_const);
	this->C = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);
	this->R = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);
	this->G = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);

	size_t i;
	Bands::const_iterator bit = sm->Begin();
	for (i=0; i<sm->GetNumBands(); i++)
	{
		double f = (bit + i)->fc;
		C[i] = (2*M_PI*EPS_0*eps_r[i])/log(r_a/r_i);
		R[i] = 0.5*sqrt(f*MU_0/(kappa*M_PI) * (1/r_a + 1/r_i));
		G[i] = 2*M_PI*f*C[i]*tand[i];
	}

	size_t mIdx = m_spectrum_model->GetNumBands() / 2;
	this->v = 1 / sqrt(L[mIdx]*C[mIdx]);

	this->CalcCharImp();
	this->CalcTransConst();
}

TypeId
PLC_FourSectorPowerSupplyCable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_FourSectorPowerSupplyCable")
    		.SetParent<PLC_Cable> ()
    		;
	return tid;
}

PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, Ptr<const SpectrumModel> sm) : PLC_Cable(sm)
{
	Calculate(radius, conductor_distance, tan_loss_angle, epsilon_r, rho, sm);
}

PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, PLC_FreqSelectiveRealValue tan_loss_angle, PLC_FreqSelectiveRealValue epsilon_r, double rho, Ptr<const SpectrumModel> sm) : PLC_Cable(sm)
{
	Calculate(radius, conductor_distance, tan_loss_angle, epsilon_r, rho, sm);
}

void
PLC_FourSectorPowerSupplyCable::Calculate(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, Ptr<const SpectrumModel> sm)
{
	double C_const = 2*EPS_0*epsilon_r*radius/conductor_distance;
	double L_const = MU_0*conductor_distance/(2*radius);

	this->C = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), C_const);
	this->L = PLC_FreqSelectiveInductance(sm->GetNumBands(), L_const);

	this->v = 1 / sqrt(L_const*C_const);

	Bands::const_iterator it;
	for (it = sm->Begin(); it != sm->End(); it++) {
		double f = it->fc;
		this->R.push_back(sqrt(rho*M_PI*f*MU_0/(pow(radius, 2))));
		this->G.push_back(2*M_PI*f*C_const*tan_loss_angle);
	}

	this->CalcCharImp();
	this->CalcTransConst();
}

void
PLC_FourSectorPowerSupplyCable::Calculate(double radius, double conductor_distance, PLC_FreqSelectiveRealValue tan_loss_angle, PLC_FreqSelectiveRealValue epsilon_r, double rho, Ptr<const SpectrumModel> sm)
{
	NS_ASSERT_MSG (sm->GetNumBands() == epsilon_r.size(), "Vector of frequency selective permittivity epsilon_r has different size than spectrum model");
	NS_ASSERT_MSG (sm->GetNumBands() == tan_loss_angle.size(), "Vector of frequency selective loss tangent tand has different size than spectrum model");

	double L_const = MU_0*conductor_distance/(2*radius);

	this->L = PLC_FreqSelectiveInductance(sm->GetNumBands(), L_const);
	this->C = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);
	this->R = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);
	this->G = PLC_FreqSelectiveCapacitance(sm->GetNumBands(), 0);

	size_t i;
	Bands::const_iterator bit = sm->Begin();
	for (i=0; i<sm->GetNumBands(); i++)
	{
		double f = (bit + i)->fc;
		C[i] = 2*EPS_0*epsilon_r[i]*radius/conductor_distance;
		R[i] = sqrt(rho*M_PI*f*MU_0/(pow(radius, 2)));
		G[i] = 2*M_PI*f*C[i]*tan_loss_angle[i];
	}

	this->v = 1 / sqrt(L_const*C[sm->GetNumBands()/2]);

	this->CalcCharImp();
	this->CalcTransConst();
}

PLC_AL3x95XLPE_Cable::PLC_AL3x95XLPE_Cable(Ptr<const SpectrumModel> sm) : PLC_ThreeCoreConcentricCable(AL3X95XLPE_EPS_R, AL3X95XLPE_KAPPA, AL3X95XLPE_R_A, AL3X95XLPE_R_I, AL3X95XLPE_TAND, sm)
{
}

TypeId
PLC_AL3x95XLPE_Cable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_AL3x95XLPE_Cable")
    		.SetParent<PLC_ThreeCoreConcentricCable> ()
    		.AddConstructor<PLC_AL3x95XLPE_Cable> ()
    		;
	return tid;
}

void
PLC_AL3x95XLPE_Cable::Calculate(void)
{
	NS_ASSERT(m_spectrum_model);
	PLC_ThreeCoreConcentricCable::Calculate(AL3X95XLPE_EPS_R, AL3X95XLPE_KAPPA, AL3X95XLPE_R_A, AL3X95XLPE_R_I, AL3X95XLPE_TAND, m_spectrum_model);
}

//////////////////////////////// PLC_NAYY150SE_Cable /////////////////////////////////////////////

PLC_NYCY70SM35_Cable::PLC_NYCY70SM35_Cable(Ptr<const SpectrumModel> sm) : PLC_ThreeCoreConcentricCable(AL3X95XLPE_EPS_R, AL3X95XLPE_KAPPA, AL3X95XLPE_R_A, AL3X95XLPE_R_I, AL3X95XLPE_TAND, sm)
{
}

TypeId
PLC_NYCY70SM35_Cable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_NYCY70SM35_Cable")
    		.SetParent<PLC_ThreeCoreConcentricCable> ()
    		.AddConstructor<PLC_NYCY70SM35_Cable> ()
    		;
	return tid;
}

void
PLC_NYCY70SM35_Cable::Calculate(void)
{
	NS_ASSERT(m_spectrum_model);

	PLC_FreqSelectiveRealValue eps_r(m_spectrum_model->GetNumBands(), 0);
	PLC_FreqSelectiveRealValue tand(m_spectrum_model->GetNumBands(), 0);

	size_t i;
	for (i=0; i<m_spectrum_model->GetNumBands(); i++)
	{
		double f = (m_spectrum_model->Begin() + i)->fc;
		eps_r[i] = 7.95 - ((0.9/std::log10(20))*std::log10(f));
		tand[i] = 0.2345 - ((0.04/std::log10(20))*std::log10(f));
	}

	PLC_ThreeCoreConcentricCable::Calculate(eps_r, COPPER_CONDUCTIVITY, NYCY70SM35_R_O, NYCY70SM35_R_I, tand, m_spectrum_model);
}

//////////////////////////////// PLC_NAYY150SE_Cable /////////////////////////////////////////////

TypeId
PLC_NAYY150SE_Cable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_NAYY150SE_Cable")
    		.SetParent<PLC_FourSectorPowerSupplyCable> ()
    		.AddConstructor<PLC_NAYY150SE_Cable> ()
    		;
	return tid;
}

PLC_NAYY150SE_Cable::PLC_NAYY150SE_Cable(Ptr<const SpectrumModel> sm)
	: PLC_FourSectorPowerSupplyCable(NAYY150SE_R, NAYY150SE_THETA, TAND, EPS_R, RHO, sm)
{
}

void
PLC_NAYY150SE_Cable::Calculate(void)
{
	NS_ASSERT(m_spectrum_model);

	PLC_FreqSelectiveRealValue eps_r(m_spectrum_model->GetNumBands(), 0);
	PLC_FreqSelectiveRealValue tand(m_spectrum_model->GetNumBands(), 0);

	size_t i;
	for (i=0; i<m_spectrum_model->GetNumBands(); i++)
	{
		double f = (m_spectrum_model->Begin() + i)->fc;
		eps_r[i] = 7.95 - ((0.9/std::log10(20))*std::log10(f));
		tand[i] = 0.2345 - ((0.04/std::log10(20))*std::log10(f));
	}

	PLC_FourSectorPowerSupplyCable::Calculate(NAYY150SE_R, NAYY150SE_THETA, tand, eps_r, RHO, m_spectrum_model);
}

//////////////////////////////// PLC_NAYY50SE_Cable /////////////////////////////////////////////

TypeId
PLC_NAYY50SE_Cable::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("PLC_NAYY50SE_Cable")
    		.SetParent<PLC_FourSectorPowerSupplyCable> ()
    		.AddConstructor<PLC_NAYY50SE_Cable> ()
    		;
	return tid;
}

PLC_NAYY50SE_Cable::PLC_NAYY50SE_Cable(Ptr<const SpectrumModel> sm)
	: PLC_FourSectorPowerSupplyCable(NAYY50SE_R, NAYY50SE_THETA, TAND, EPS_R, RHO, sm)
{
}

void
PLC_NAYY50SE_Cable::Calculate(void)
{
	NS_ASSERT(m_spectrum_model);
	PLC_FourSectorPowerSupplyCable::Calculate(NAYY50SE_R, NAYY50SE_THETA, TAND, EPS_R, RHO, m_spectrum_model);
}

}
