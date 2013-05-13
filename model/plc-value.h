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

#ifndef PLC_VALUE_H_
#define PLC_VALUE_H_

#include <iostream>
#include <vector>

#include <ns3/ptr.h>
#include <ns3/simple-ref-count.h>
#include <ns3/spectrum-model.h>
#include <ns3/spectrum-value.h>

#include "plc-defs.h"
#include "plc-time.h"

namespace ns3 {

Ptr<PLC_ValueBase> Add(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2);
Ptr<PLC_ValueBase> Subtract(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2);
Ptr<PLC_ValueBase> Divide(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2);
Ptr<PLC_ValueBase> Multiply(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2);

/**
 * \class PLC_ValueBase
 *
 * \brief Base class for PLC values types
 *
 * The PLC value classes are used for efficient operations among
 * different value types. A value is a set of complex numbers which can be constant
 * in time and/or frequency as well as time variant with respect to the main cycle.
 * PLC value classes are used to represent network impedances, channel
 * transfer functions and ABCD parameters for two port networks.
 */
class PLC_ValueBase : public Object
{
public:
	static TypeId GetTypeId (void);

	enum PLC_ValueType {
		CONSTANT,
		FREQ_SELECTIVE,
		TIMEVARIANT_CONSTANT,
		TIMEVARIANT_FREQ_SELECTIVE
	};

    PLC_ValueBase() {}
    ~PLC_ValueBase() = 0;
	PLC_ValueBase(Ptr<const SpectrumModel> sm, PLC_ValueType type);

	PLC_ValueType GetValueType(void) const { return m_value_type; }
	Ptr<const SpectrumModel> GetSpectrumModel(void) const { return m_spectrum_model; }
	size_t GetNumBands(void) const { return m_spectrum_model->GetNumBands(); }

	void Lock(void) const 	{ m_mutex.Lock(); }
	void Unlock(void) const 	{ m_mutex.Unlock(); }

	bool IsTimeVariant(void) const;

	friend std::ostream& operator<<(std::ostream& stream, PLC_ValueBase& value);

	Ptr<PLC_ValueBase> Copy(void);

protected:
    // pure virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) = 0;

	mutable PLC_Mutex			m_mutex;
	Ptr<const SpectrumModel> 	m_spectrum_model;
	PLC_ValueType				m_value_type;
};

/**
 * Constant value in time and frequency
 */
class PLC_ConstValue : public PLC_ValueBase
{

public:
	static TypeId GetTypeId (void);

    PLC_ConstValue();
	PLC_ConstValue(Ptr<const SpectrumModel> sm, double real);
	PLC_ConstValue(Ptr<const SpectrumModel> sm, PLC_Value value = PLC_Value(0, 0));
	PLC_ConstValue(const PLC_ConstValue& value);

//	PLC_Value GetValue(void) const;
	std::complex<double> GetValue(void) const;

	PLC_ConstValue& operator=(const PLC_ConstValue& value);

	PLC_ConstValue& operator+=(double value);
	PLC_ConstValue& operator+=(const PLC_Value& value);
	PLC_ConstValue& operator+=(const PLC_ConstValue& value);

	PLC_ConstValue& operator-=(double value);
	PLC_ConstValue& operator-=(const PLC_Value& value);
	PLC_ConstValue& operator-=(const PLC_ConstValue& value);

	PLC_ConstValue& operator*=(double value);
	PLC_ConstValue& operator*=(const PLC_Value& value);
	PLC_ConstValue& operator*=(const PLC_ConstValue& value);

	PLC_ConstValue& operator/=(double value);
	PLC_ConstValue& operator/=(const PLC_Value& value);
	PLC_ConstValue& operator/=(const PLC_ConstValue& value);

	friend PLC_ConstValue operator+(const PLC_ConstValue& value);
	friend PLC_ConstValue operator-(const PLC_ConstValue& value);

	friend PLC_ConstValue operator+(const PLC_ConstValue& lhs, double rhs);
	friend PLC_ConstValue operator+(double lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator+(const PLC_ConstValue& lhs, const PLC_Value& rhs);
	friend PLC_ConstValue operator+(const PLC_Value& lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator+(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs);

	friend PLC_ConstValue operator-(const PLC_ConstValue& lhs, double rhs);
	friend PLC_ConstValue operator-(double lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator-(const PLC_ConstValue& lhs, const PLC_Value& rhs);
	friend PLC_ConstValue operator-(const PLC_Value& lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator-(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs);

	friend PLC_ConstValue operator*(const PLC_ConstValue& lhs, double rhs);
	friend PLC_ConstValue operator*(double lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator*(const PLC_ConstValue& lhs, const PLC_Value& rhs);
	friend PLC_ConstValue operator*(const PLC_Value& lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator*(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs);

	friend PLC_ConstValue operator/(const PLC_ConstValue& lhs, double rhs);
	friend PLC_ConstValue operator/(double lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator/(const PLC_ConstValue& lhs, const PLC_Value& rhs);
	friend PLC_ConstValue operator/(const PLC_Value& lhs, const PLC_ConstValue& rhs);
	friend PLC_ConstValue operator/(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs);

	friend std::ostream& operator<<(std::ostream& stream, PLC_ConstValue& value);

protected:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:

	PLC_Value m_value;
};

/**
 * Frequency selective, but time invariant, value
 */
class PLC_FreqSelectiveValue : public PLC_ValueBase
{
public:
	static TypeId GetTypeId (void);

    PLC_FreqSelectiveValue() {}
	PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, PLC_Value value = PLC_Value(0, 0));
	PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_ValueSpectrum& values);
	PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, double R, double Q, double f_0);
	PLC_FreqSelectiveValue(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue(const PLC_FreqSelectiveValue& value);

	PLC_ValueSpectrum GetValues(void) const { return m_values; }
	PLC_ValueSpectrum *GetValuesRef(void) { return &m_values; }

	PLC_FreqSelectiveValue& operator=(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue& operator=(const PLC_FreqSelectiveValue& value);

	PLC_Value operator[](size_t i) const;
	PLC_Value& operator[](size_t i);

	PLC_FreqSelectiveValue& operator+=(double value);
	PLC_FreqSelectiveValue& operator+=(const PLC_Value& value);
	PLC_FreqSelectiveValue& operator+=(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue& operator+=(const PLC_FreqSelectiveValue& value);

	PLC_FreqSelectiveValue& operator-=(double value);
	PLC_FreqSelectiveValue& operator-=(const PLC_Value& value);
	PLC_FreqSelectiveValue& operator-=(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue& operator-=(const PLC_FreqSelectiveValue& value);

	PLC_FreqSelectiveValue& operator*=(double value);
	PLC_FreqSelectiveValue& operator*=(const PLC_Value& value);
	PLC_FreqSelectiveValue& operator*=(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue& operator*=(const PLC_FreqSelectiveValue& value);

	PLC_FreqSelectiveValue& operator/=(double value);
	PLC_FreqSelectiveValue& operator/=(const PLC_Value& value);
	PLC_FreqSelectiveValue& operator/=(const PLC_ConstValue& value);
	PLC_FreqSelectiveValue& operator/=(const PLC_FreqSelectiveValue& value);

	friend PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& value);
	friend PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& value);

	friend PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, double rhs);
	friend PLC_FreqSelectiveValue operator+(double lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_FreqSelectiveValue operator+(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_FreqSelectiveValue operator+(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, double rhs);
	friend PLC_FreqSelectiveValue operator-(double lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_FreqSelectiveValue operator-(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_FreqSelectiveValue operator-(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, double rhs);
	friend PLC_FreqSelectiveValue operator*(double lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_FreqSelectiveValue operator*(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_FreqSelectiveValue operator*(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, double rhs);
	friend PLC_FreqSelectiveValue operator/(double lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_FreqSelectiveValue operator/(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_FreqSelectiveValue operator/(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend std::ostream& operator<<(std::ostream& stream, PLC_FreqSelectiveValue& value);

protected:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:

	PLC_ValueSpectrum	m_values;
};

/**
 * Frequency constant but time variant value
 */
class PLC_TimeVariantConstValue : public PLC_ValueBase
{
public:
	static TypeId GetTypeId (void);

    PLC_TimeVariantConstValue() {}
	PLC_TimeVariantConstValue(Ptr<const SpectrumModel> sm, PLC_Value value = PLC_Value(0, 0), size_t timeslots = PLC_Time::GetNumTimeslots());
	PLC_TimeVariantConstValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValue& values);
	PLC_TimeVariantConstValue(const PLC_ConstValue& value, size_t timeslots = PLC_Time::GetNumTimeslots());
	PLC_TimeVariantConstValue(const PLC_TimeVariantConstValue& value);

	PLC_TimeVariantValue GetValues(void) const { return m_values; }
	size_t GetNumTimeSlots(void) const { return m_values.size(); }

	PLC_TimeVariantConstValue& operator=(const PLC_ConstValue& value);
	PLC_TimeVariantConstValue& operator=(const PLC_TimeVariantConstValue& value);

	PLC_Value operator[](size_t i) const;

	PLC_TimeVariantConstValue& operator+=(double value);
	PLC_TimeVariantConstValue& operator+=(const PLC_Value& value);
	PLC_TimeVariantConstValue& operator+=(const PLC_ConstValue& value);
	PLC_TimeVariantConstValue& operator+=(const PLC_TimeVariantConstValue& value);

	PLC_TimeVariantConstValue& operator-=(double value);
	PLC_TimeVariantConstValue& operator-=(const PLC_Value& value);
	PLC_TimeVariantConstValue& operator-=(const PLC_ConstValue& value);
	PLC_TimeVariantConstValue& operator-=(const PLC_TimeVariantConstValue& value);

	PLC_TimeVariantConstValue& operator*=(double value);
	PLC_TimeVariantConstValue& operator*=(const PLC_Value& value);
	PLC_TimeVariantConstValue& operator*=(const PLC_ConstValue& value);
	PLC_TimeVariantConstValue& operator*=(const PLC_TimeVariantConstValue& value);

	PLC_TimeVariantConstValue& operator/=(double value);
	PLC_TimeVariantConstValue& operator/=(const PLC_Value& value);
	PLC_TimeVariantConstValue& operator/=(const PLC_ConstValue& value);
	PLC_TimeVariantConstValue& operator/=(const PLC_TimeVariantConstValue& value);

	friend PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& value);
	friend PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& value);

	friend PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, double rhs);
	friend PLC_TimeVariantConstValue operator+(double lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantConstValue operator+(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantConstValue operator+(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, double rhs);
	friend PLC_TimeVariantConstValue operator-(double lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantConstValue operator-(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantConstValue operator-(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, double rhs);
	friend PLC_TimeVariantConstValue operator*(double lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantConstValue operator*(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantConstValue operator*(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, double rhs);
	friend PLC_TimeVariantConstValue operator/(double lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantConstValue operator/(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantConstValue operator/(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);


	friend std::ostream& operator<<(std::ostream& stream, PLC_TimeVariantConstValue& value);

protected:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:

	PLC_TimeVariantValue	m_values;
};

/**
 * Frequency selective and time variant value
 */
class PLC_TimeVariantFreqSelectiveValue : public PLC_ValueBase
{
public:
	static TypeId GetTypeId (void);

	struct PLC_TimeVariantParamSet
	{
		double R_offset;
		double Q_offset;
		double f_0_offset;
		double R_amplitude;
		double Q_amplitude;
		double f0_amplitude;
		double phi;
	};

    PLC_TimeVariantFreqSelectiveValue() {}
	PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, size_t timeslots = PLC_Time::GetNumTimeslots(), PLC_Value value = PLC_Value(0, 0));
	PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValue& values);
	PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValueSpectrum& values);
	PLC_TimeVariantFreqSelectiveValue(const PLC_ConstValue& value, size_t timeslots = PLC_Time::GetNumTimeslots());
	PLC_TimeVariantFreqSelectiveValue(const PLC_FreqSelectiveValue& value, size_t timeslots = PLC_Time::GetNumTimeslots());
	PLC_TimeVariantFreqSelectiveValue(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue(const PLC_TimeVariantFreqSelectiveValue& value);
	PLC_TimeVariantFreqSelectiveValue(PLC_FreqSelectiveValue& offset, PLC_FreqSelectiveValue& amplitude, double phi, size_t timeslots = PLC_Time::GetNumTimeslots());
	PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, struct PLC_TimeVariantParamSet& paramSet, size_t timeslots = PLC_Time::GetNumTimeslots());

	PLC_TimeVariantValueSpectrum GetValues(void) const { return m_values; }
	PLC_TimeVariantValueSpectrum *GetValuesRef(void) { return &m_values; }

	size_t GetNumTimeSlots(void) const { return m_values.size(); }

	PLC_ValueSpectrum operator[](size_t i) const;
	PLC_ValueSpectrum& operator[](size_t i);

	PLC_TimeVariantFreqSelectiveValue& operator=(const PLC_ConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator=(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator=(const PLC_TimeVariantFreqSelectiveValue& value);

	PLC_TimeVariantFreqSelectiveValue& operator+=(double value);
	PLC_TimeVariantFreqSelectiveValue& operator+=(const PLC_Value& value);
	PLC_TimeVariantFreqSelectiveValue& operator+=(const PLC_ConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator+=(const PLC_FreqSelectiveValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator+=(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator+=(const PLC_TimeVariantFreqSelectiveValue& value);

	PLC_TimeVariantFreqSelectiveValue& operator-=(double value);
	PLC_TimeVariantFreqSelectiveValue& operator-=(const PLC_Value& value);
	PLC_TimeVariantFreqSelectiveValue& operator-=(const PLC_ConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator-=(const PLC_FreqSelectiveValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator-=(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator-=(const PLC_TimeVariantFreqSelectiveValue& value);

	PLC_TimeVariantFreqSelectiveValue& operator*=(double value);
	PLC_TimeVariantFreqSelectiveValue& operator*=(const PLC_Value& value);
	PLC_TimeVariantFreqSelectiveValue& operator*=(const PLC_ConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator*=(const PLC_FreqSelectiveValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator*=(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator*=(const PLC_TimeVariantFreqSelectiveValue& value);

	PLC_TimeVariantFreqSelectiveValue& operator/=(double value);
	PLC_TimeVariantFreqSelectiveValue& operator/=(const PLC_Value& value);
	PLC_TimeVariantFreqSelectiveValue& operator/=(const PLC_ConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator/=(const PLC_FreqSelectiveValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator/=(const PLC_TimeVariantConstValue& value);
	PLC_TimeVariantFreqSelectiveValue& operator/=(const PLC_TimeVariantFreqSelectiveValue& value);

	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& value);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& value);

	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs);
	friend PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs);

	friend std::ostream& operator<<(std::ostream& stream, PLC_TimeVariantFreqSelectiveValue& value);

protected:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:

	PLC_TimeVariantValueSpectrum m_values;
};

double abs(const PLC_ConstValue& value);
PLC_FreqSelectiveRealValue abs(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantRealValue abs(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveRealValue abs(const PLC_TimeVariantFreqSelectiveValue& value);

double arg(const PLC_ConstValue& value);
PLC_FreqSelectiveRealValue arg(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantRealValue arg(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveRealValue arg(const PLC_TimeVariantFreqSelectiveValue& value);

double real(const PLC_ConstValue& value);
PLC_FreqSelectiveRealValue real(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantRealValue real(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveRealValue real(const PLC_TimeVariantFreqSelectiveValue& value);

double imag(const PLC_ConstValue& value);
PLC_FreqSelectiveRealValue imag(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantRealValue imag(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveRealValue imag(const PLC_TimeVariantFreqSelectiveValue& value);

double absSqr(const PLC_ConstValue& value);
PLC_FreqSelectiveRealValue absSqr(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantRealValue absSqr(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveRealValue absSqr(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue sinh(const PLC_ConstValue& value);
PLC_FreqSelectiveValue sinh(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue sinh(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue sinh(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue cosh(const PLC_ConstValue& value);
PLC_FreqSelectiveValue cosh(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue cosh(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue cosh(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue exp(const PLC_ConstValue& value);
PLC_FreqSelectiveValue exp(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue exp(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue exp(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue log10(const PLC_ConstValue& value);
PLC_FreqSelectiveValue log10(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue log10(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue log10(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue tan(const PLC_ConstValue& value);
PLC_FreqSelectiveValue tan(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue tan(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue tan(const PLC_TimeVariantFreqSelectiveValue& value);

PLC_ConstValue tanh(const PLC_ConstValue& value);
PLC_FreqSelectiveValue tanh(const PLC_FreqSelectiveValue& value);
PLC_TimeVariantConstValue tanh(const PLC_TimeVariantConstValue& value);
PLC_TimeVariantFreqSelectiveValue tanh(const PLC_TimeVariantFreqSelectiveValue& value);

double max(SpectrumValue& value);
double min(SpectrumValue& value);

// power (integral of power spectral density)
double Pwr(const SpectrumValue& value);

// Watts to dBm
double W2dBm(double watt);

double max(PLC_FreqSelectiveRealValue& value);
double min(PLC_FreqSelectiveRealValue& value);

void AddInverseValue(PLC_ValueBase *res, PLC_ValueBase *imp);

template<typename ImpedanceReturnType>
Ptr<ImpedanceReturnType> CalcEquivalentImpedance(Ptr<const SpectrumModel> sm, std::vector<PLC_Impedance *> parallel_impedances)
{
	ImpedanceReturnType inv_ret(sm);

	std::vector<PLC_Impedance *>::iterator p_it;
	for (p_it = parallel_impedances.begin(); p_it != parallel_impedances.end(); p_it++) {
		(*p_it)->Lock();
		AddInverseValue(&inv_ret, *p_it);
		(*p_it)->Unlock();
	}

	return Create<ImpedanceReturnType>(1 / inv_ret);
}

}

#endif /* PLC_VALUE_H_ */
