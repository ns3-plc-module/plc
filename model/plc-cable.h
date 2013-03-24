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

#ifndef PLC_CABLE_H_
#define PLC_CABLE_H_

#include <cmath>
#include <iostream>
#include <complex>

#include <ns3/object.h>
#include <ns3/type-id.h>
#include <ns3/spectrum-model.h>

#include "plc-defs.h"
#include "plc-value.h"

// Cable model parameters
#define EPS_0 	8.854188e-12 	// F/m
#define MU_0	12.566371e-7	// H/m
#define MU_R	1
#define RHO		2.82e-8			// for aluminium (multiple references; to fit Dostert's curves)
#define TAND	0.01			// depends on insulation
#define MU		(MU_0 * MU_R)
#define EPS_R	4
#define EPS_P	(EPS_0 * EPS_R)

#define NAYY150SE_D		1.8e-3		// insulation, m
#define NAYY150SE_A		6e-4		// conductor area, 4*150e-6m^2
#define NAYY150SE_THETA	3.6e-3		// 2*NAYY150SE_D
#define NAYY150SE_R		13.82e-3	// radius, m, r = sqrt(A/pi)

#define NAYY50SE_D		1.4e-3		// insulation, m
#define NAYY50SE_A		2e-4		// conductor area, 4*50e-6m^2
#define NAYY50SE_THETA	2.8e-3		// 2*NAYY50SE_D
#define NAYY50SE_R		7.98e-3		// radius, m, r = sqrt(A/pi)

#define AL3X95XLPE_EPS_R	0.9
#define AL3X95XLPE_KAPPA	0.285714286
#define AL3X95XLPE_R_A		10e-3
#define AL3X95XLPE_R_I		9.52e-3
#define AL3X95XLPE_TAND		0.004

#define COPPER_CONDUCTIVITY	5.96e7 // (S/m) at 20 degree celcius
#define NYCY70SM35_R_O 8.448e-3 // radius to outer conductor
#define NYCY70SM35_R_I 7.048e-3 // inner conductor radius

namespace ns3 {

/**
 *	This class describes lossy transmission lines with the two wire conductor theory for TEM waves.
 *	Based on the distributed circuit parameters R',G',L',C' the characteristic impedance z_c
 *	and the propagation constant gamma are calculated.
 */
class PLC_Cable : public Object
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 */
	PLC_Cable () {}

	/**
	 * Constructor
	 * @param sm  The used spectrum model
	 */
	PLC_Cable(Ptr<const SpectrumModel> sm);

	virtual void Calculate() = 0;

	/**
	 *
	 * @param R Distributed resistance
	 * @param G Distributed conductance
	 * @param L Distributed inductance
	 * @param C Distributed capacity
	 * @param sm Spectrum model
	 */
	PLC_Cable(const PLC_FreqSelectiveResistance& R, const PLC_FreqSelectiveConductance& G, const PLC_FreqSelectiveInductance& L, const PLC_FreqSelectiveCapacitance& C, Ptr<const SpectrumModel> sm);

	void SetSpectrumModel(Ptr<const SpectrumModel> sm);
	Ptr<const SpectrumModel> GetSpectrumModel(void) { return m_spectrum_model; }

	/**
	 * Get the characteristic impedance of the cable
	 * @return z_c
	 */
	Ptr<const PLC_FreqSelectiveImpedance> GetCharImp(void) const;

	/**
	 * Get the propagation constant of the cable
	 * @return gamma
	 */
	Ptr<const PLC_FreqSelectiveImpedance> GetTransConst(void) const;

	/**
	 * Get the wave propagation speed for the lossless line as an approximation to calculate a signal's
	 * propagation delay
	 * @return v
	 */
	double GetPropSpeedApprox(void) { return v; }

	/**
	 *
	 * @return The used spectrum model
	 */
	Ptr<const SpectrumModel> GetSpectrumModel(void) const { return m_spectrum_model; }

	/**
	 * Cable mutex lock functions
	 */
	void Lock() 		{ m_cable_mutex.Lock(); }
	void Unlock()	{ m_cable_mutex.Unlock(); }

	/**
	 *
	 * @return Distributed resistance (frequency dependent)
	 */
	PLC_FreqSelectiveResistance *GetDistResRef(void) { return &R; }

	/**
	 *
	 * @return Distributed conductance (frequency dependent)
	 */
	PLC_FreqSelectiveResistance *GetDistConRef(void) { return &G; }

private:
	mutable PLC_Mutex 			m_cable_mutex;

protected:
	virtual void DoDispose();

	Ptr<const SpectrumModel> 	m_spectrum_model;

	/**
	 * distributed resistance
	 */
	PLC_FreqSelectiveResistance R;
	/**
	 * distributed conductance
	 */
	PLC_FreqSelectiveConductance G;
	/**
	 * distributed inductance
	 */
	PLC_FreqSelectiveInductance L;
	/**
	 * distributed capacitance
	 */
	PLC_FreqSelectiveCapacitance C;
	/**
	 * characteristic impedance
	 */
	Ptr<PLC_FreqSelectiveImpedance> z_c;
	/**
	 * transmission constant
	 */
	Ptr<PLC_FreqSelectiveImpedance> gamma;

	/**
	 * Popagation speed
	 *
	 * assumption: flat propagation over lossless medium
	 */
	double v;

	/**
	 * Calculates characteristic impedance of the cable
	 */
	void CalcCharImp(void);

	/**
	 * Calculates propagation constant of the cable
	 */
	void CalcTransConst(void);
};

/**
 * Coaxial model for the three core concentric cable
 * from "Powerline Communications" by K. Dostert
 */
class PLC_ThreeCoreConcentricCable : public PLC_Cable
{
public:
	static TypeId GetTypeId(void);

	PLC_ThreeCoreConcentricCable() : PLC_Cable() {}

	virtual void Calculate() = 0;

	/**
	 *
	 * @param eps_r dielectric constant
	 * @param kappa specific conductivity
	 * @param r_a Cable radius
	 * @param r_i Conductor sector radius
	 * @param tand Tangents loss angle
	 * @param sm Spectrum model
	 */
	PLC_ThreeCoreConcentricCable(double eps_r, double kappa, double r_a, double r_i, double tand, Ptr<const SpectrumModel> sm);

	PLC_ThreeCoreConcentricCable(PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, PLC_FreqSelectiveRealValue tand, Ptr<const SpectrumModel> sm);

	void Calculate(double eps_r, double kappa, double r_a, double r_i, double tand, Ptr<const SpectrumModel> sm);
	void Calculate(PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, PLC_FreqSelectiveRealValue tand, Ptr<const SpectrumModel> sm);
};

/**
 * Model for a four sector cable
 */
class PLC_FourSectorPowerSupplyCable : public PLC_Cable
{
public:
	static TypeId GetTypeId(void);

	PLC_FourSectorPowerSupplyCable() : PLC_Cable() {}

	virtual void Calculate() = 0;

	/**
	 * @param radius Radius of the cable
	 * @param conductor_distance Distance between conductors
	 * @param tan_loss_angle Tangents loss angle
	 * @param epsilon_r Dielectric constant
	 * @param rho
	 * @param sm
	 */
	PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, Ptr<const SpectrumModel> sm);
	PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, PLC_FreqSelectiveRealValue tan_loss_angle, PLC_FreqSelectiveRealValue epsilon_r, double rho, Ptr<const SpectrumModel> sm);

	void Calculate(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, Ptr<const SpectrumModel> sm);
	void Calculate(double radius, double conductor_distance, PLC_FreqSelectiveRealValue tan_loss_angle, PLC_FreqSelectiveRealValue epsilon_r, double rho, Ptr<const SpectrumModel> sm);
};

/**
 * Parameter model for the power supply cable NAYY150SE
 */
class PLC_NAYY150SE_Cable : public PLC_FourSectorPowerSupplyCable
{
public:
	static TypeId GetTypeId(void);

	PLC_NAYY150SE_Cable() : PLC_FourSectorPowerSupplyCable() {}
	PLC_NAYY150SE_Cable(Ptr<const SpectrumModel> sm);
	void Calculate();
};

/**
 * Parameter model for the power supply cable NAYY50SE
 */
class PLC_NAYY50SE_Cable : public PLC_FourSectorPowerSupplyCable
{
public:
	static TypeId GetTypeId(void);

	PLC_NAYY50SE_Cable() : PLC_FourSectorPowerSupplyCable() {}
	PLC_NAYY50SE_Cable(Ptr<const SpectrumModel> sm);
	void Calculate();
};

/**
 * Parameter model for the power supply cable AL3x95XLPE
 */
class PLC_AL3x95XLPE_Cable : public PLC_ThreeCoreConcentricCable
{
public:
	static TypeId GetTypeId(void);

	PLC_AL3x95XLPE_Cable() : PLC_ThreeCoreConcentricCable() {}
	PLC_AL3x95XLPE_Cable(Ptr<const SpectrumModel> sm);
	void Calculate();
};

/**
 * Parameter model for the power supply cable NYCY70SM/35
 */
class PLC_NYCY70SM35_Cable : public PLC_ThreeCoreConcentricCable
{
public:
	static TypeId GetTypeId(void);

	PLC_NYCY70SM35_Cable() : PLC_ThreeCoreConcentricCable() {}
	PLC_NYCY70SM35_Cable(Ptr<const SpectrumModel> sm);
	void Calculate();
};

}

#endif /* PLC_CABLE_H_ */
