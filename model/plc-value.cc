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

#include <cmath>
#include <complex>
#include <ns3/log.h>
#include "plc-value.h"

namespace ns3 {

Ptr<PLC_ValueBase> Add(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2)
{
	NS_ASSERT(op1->GetSpectrumModel() == op2->GetSpectrumModel());
	Ptr<PLC_ValueBase> ret;

	switch (op1->GetValueType()) {
		case PLC_ValueBase::CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_ConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default:
				{
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) +
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}

		default: {
			NS_FATAL_ERROR("wrong plc value type");
			break;
		}
	}

	return ret;
}

Ptr<PLC_ValueBase> Subtract(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2)
{
	NS_ASSERT(op1->GetSpectrumModel() == op2->GetSpectrumModel());
	Ptr<PLC_ValueBase> ret;

	switch (op1->GetValueType()) {
		case PLC_ValueBase::CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_ConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default:
				{
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) -
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}

		default: {
			NS_FATAL_ERROR("wrong plc value type");
			break;
		}
	}

	return ret;
}

Ptr<PLC_ValueBase> Multiply(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2)
{
	NS_ASSERT(op1->GetSpectrumModel() == op2->GetSpectrumModel());
	Ptr<PLC_ValueBase> ret;

	switch (op1->GetValueType()) {
		case PLC_ValueBase::CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_ConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default:
				{
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) *
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}

		default: {
			NS_FATAL_ERROR("wrong plc value type");
			break;
		}
	}

	return ret;
}

Ptr<PLC_ValueBase> Divide(Ptr<PLC_ValueBase> op1, Ptr<PLC_ValueBase> op2)
{
	NS_ASSERT(op1->GetSpectrumModel() == op2->GetSpectrumModel());
	Ptr<PLC_ValueBase> ret;

	switch (op1->GetValueType()) {
		case PLC_ValueBase::CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_ConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_ConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_FreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default:
				{
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_CONSTANT:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantConstValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}
		case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
		{
			switch (op2->GetValueType()) {
				case PLC_ValueBase::CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_ConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_FreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantConstValue *> (PeekPointer(op2)))
					);
					break;
				}
				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					ret = CreateObject<PLC_TimeVariantFreqSelectiveValue>
					(
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op1))) /
							(*static_cast<PLC_TimeVariantFreqSelectiveValue *> (PeekPointer(op2)))
					);
					break;
				}
				default: {
					NS_FATAL_ERROR("wrong plc value type");
					break;
				}
			}
			break;
		}

		default: {
			NS_FATAL_ERROR("wrong plc value type");
			break;
		}
	}

	return ret;
}

//////////////////////////////////////// PLC_ValueBase /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ValueBase);

TypeId
PLC_ValueBase::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_ValueBase")
	.SetParent<Object> ()
  ;
  return tid;
}


PLC_ValueBase::PLC_ValueBase(Ptr<const SpectrumModel> sm, PLC_ValueBase::PLC_ValueType type) : m_spectrum_model(sm), m_value_type(type)
{
}

PLC_ValueBase::~PLC_ValueBase(void)
{
}

bool PLC_ValueBase::IsTimeVariant(void) const
{
	return (this->m_value_type == PLC_ValueBase::TIMEVARIANT_CONSTANT || this->m_value_type == PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE);
}

std::ostream& operator<<(std::ostream& stream, PLC_ValueBase& value)
{
	switch (value.GetValueType()) {

		case (PLC_ValueBase::CONSTANT):
				stream << *static_cast<PLC_ConstImpedance *> (&value);
				break;

		case (PLC_ValueBase::FREQ_SELECTIVE):
				stream << *static_cast<PLC_FreqSelectiveImpedance *> (&value);
				break;

		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
				stream << *static_cast<PLC_TimeVariantConstImpedance *> (&value);
				break;

		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
				stream << *static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (&value);
				break;

		default:
				NS_FATAL_ERROR("Invalid value");
				break;
	}

	return stream;
}

Ptr<PLC_ValueBase> PLC_ValueBase::Copy(void)
{
	Ptr<PLC_ValueBase> ret;

	switch (GetValueType()) {

		case (PLC_ValueBase::CONSTANT):
				ret = CreateObject<PLC_ConstValue> (* static_cast<PLC_ConstValue *> (this));
				break;

		case (PLC_ValueBase::FREQ_SELECTIVE):
				ret = CreateObject<PLC_FreqSelectiveImpedance> (* static_cast<PLC_FreqSelectiveImpedance *> (this));
				break;

		case (PLC_ValueBase::TIMEVARIANT_CONSTANT):
				ret = CreateObject<PLC_TimeVariantConstImpedance> (* static_cast<PLC_TimeVariantConstImpedance *> (this));
				break;

		case (PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE):
				ret = CreateObject<PLC_TimeVariantFreqSelectiveImpedance> (* static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (this));
				break;

		default:
				NS_FATAL_ERROR("Invalid value");
				break;
	}

	return ret;
}

//////////////////////////////////////// PLC_ConstValue /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ConstValue);

TypeId
PLC_ConstValue::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_ConstValue")
	.SetParent<PLC_ValueBase> ()
  ;
  return tid;
}


PLC_ConstValue::PLC_ConstValue(void)
{
}

PLC_ConstValue::PLC_ConstValue(Ptr<const SpectrumModel> sm, double real) : PLC_ValueBase(sm, PLC_ValueBase::CONSTANT)
{
	this->m_value = PLC_Value(real, 0);
}

PLC_ConstValue::PLC_ConstValue(Ptr<const SpectrumModel> sm, PLC_Value value) : PLC_ValueBase(sm, PLC_ValueBase::CONSTANT)
{
	this->m_value = PLC_Value(value);
}

PLC_ConstValue::PLC_ConstValue(const PLC_ConstValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::CONSTANT)
{
	this->m_value = value.GetValue();
}

//PLC_Value
std::complex<double>
PLC_ConstValue::GetValue(void) const 
{ 
    return m_value; 
}

PLC_ConstValue& PLC_ConstValue::operator=(const PLC_ConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_value = value.GetValue();
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator+=(double value)
{
	this->m_value += PLC_Value(value, 0);
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator+=(const PLC_Value& value)
{
	this->m_value += value;
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator+=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	this->m_value += value.GetValue();
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator-=(double value)
{
	this->m_value -= PLC_Value(value, 0);
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator-=(const PLC_Value& value)
{
	this->m_value -= value;
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator-=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	this->m_value -= value.GetValue();
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator*=(double value)
{
	this->m_value *= PLC_Value(value, 0);
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator*=(const PLC_Value& value)
{
	this->m_value *= value;
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator*=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	this->m_value *= value.GetValue();
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator/=(double value)
{
	this->m_value /= PLC_Value(value, 0);
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator/=(const PLC_Value& value)
{
	this->m_value /= value;
	return *this;
}

PLC_ConstValue& PLC_ConstValue::operator/=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	this->m_value /= value.GetValue();
	return *this;
}

PLC_ConstValue operator+(const PLC_ConstValue& value)
{
	return value;
}

PLC_ConstValue operator-(const PLC_ConstValue& value)
{
	PLC_ConstValue ret(value);
	ret.m_value = -ret.m_value;
	return ret;
}

PLC_ConstValue operator+(const PLC_ConstValue& lhs, double rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value + rhs);
	return ret;
}

PLC_ConstValue operator+(double lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs + rhs.m_value);
	return ret;
}

PLC_ConstValue operator+(const PLC_ConstValue& lhs, const PLC_Value& rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value + rhs);
	return ret;
}

PLC_ConstValue operator+(const PLC_Value& lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs + rhs.m_value);
	return ret;
}

PLC_ConstValue operator+(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value + rhs.m_value);
	return ret;
}

PLC_ConstValue operator-(const PLC_ConstValue& lhs, double rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value - rhs);
	return ret;
}

PLC_ConstValue operator-(double lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs - rhs.m_value);
	return ret;
}

PLC_ConstValue operator-(const PLC_ConstValue& lhs, const PLC_Value& rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value - rhs);
	return ret;
}

PLC_ConstValue operator-(const PLC_Value& lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs - rhs.m_value);
	return ret;
}

PLC_ConstValue operator-(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value - rhs.m_value);
	return ret;
}

PLC_ConstValue operator*(const PLC_ConstValue& lhs, double rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value * rhs);
	return ret;
}

PLC_ConstValue operator*(double lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs * rhs.m_value);
	return ret;
}

PLC_ConstValue operator*(const PLC_ConstValue& lhs, const PLC_Value& rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value * rhs);
	return ret;
}

PLC_ConstValue operator*(const PLC_Value& lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs * rhs.m_value);
	return ret;
}

PLC_ConstValue operator*(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value * rhs.m_value);
	return ret;
}

PLC_ConstValue operator/(const PLC_ConstValue& lhs, double rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value / rhs);
	return ret;
}

PLC_ConstValue operator/(double lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs / rhs.m_value);
	return ret;
}

PLC_ConstValue operator/(const PLC_ConstValue& lhs, const PLC_Value& rhs)
{
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value / rhs);
	return ret;
}

PLC_ConstValue operator/(const PLC_Value& lhs, const PLC_ConstValue& rhs)
{
	PLC_ConstValue ret(rhs.GetSpectrumModel(), lhs / rhs.m_value);
	return ret;
}

PLC_ConstValue operator/(const PLC_ConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_ConstValue ret(lhs.GetSpectrumModel(), lhs.m_value / rhs.m_value);
	return ret;
}

std::ostream& operator<<(std::ostream& stream, PLC_ConstValue& value)
{
	stream << "PLC_ConstValue: [ " << value.GetValue() << " ]";
	return stream;
}

//////////////////////////////////////// PLC_FreqSelectiveValue /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_FreqSelectiveValue);

TypeId
PLC_FreqSelectiveValue::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_FreqSelectiveValue")
	.SetParent<PLC_ValueBase> ()
  ;
  return tid;
}

PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, PLC_Value value) : PLC_ValueBase(sm, PLC_ValueBase::FREQ_SELECTIVE)
{
	this->m_values = PLC_ValueSpectrum(sm->GetNumBands(), value);
}

PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_ValueSpectrum& values) : PLC_ValueBase(sm, PLC_ValueBase::FREQ_SELECTIVE)
{
	NS_ASSERT(values.size() == sm->GetNumBands());
	this->m_values = values;
}

PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(Ptr<const SpectrumModel> sm, double R, double Q, double f_0) : PLC_ValueBase(sm, PLC_ValueBase::FREQ_SELECTIVE)
{
	Bands::const_iterator b_it;
	for (b_it = sm->Begin(); b_it != sm->End(); b_it++) {
		double f_c = b_it->fc;

		PLC_Value numerator 	= PLC_Value(R, 0);
		PLC_Value denumerator 	= PLC_Value(1, Q*((2*M_PI*f_c)/(2*M_PI*f_0) - (2*M_PI*f_0)/(2*M_PI*f_c)));

		this->m_values.push_back(numerator/denumerator);
	}

	NS_ASSERT(this->m_values.size() == sm->GetNumBands());
}

PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(const PLC_FreqSelectiveValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::FREQ_SELECTIVE)
{
	this->m_values = value.GetValues();
}

PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(const PLC_ConstValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::FREQ_SELECTIVE)
{
	this->m_values = PLC_ValueSpectrum(value.GetSpectrumModel()->GetNumBands(), value.GetValue());
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator=(const PLC_ConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = PLC_ValueSpectrum(this->m_spectrum_model->GetNumBands(), value.GetValue());
	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator=(const PLC_FreqSelectiveValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = value.GetValues();
	NS_ASSERT(this->m_values.size() == this->m_spectrum_model->GetNumBands());
	return *this;
}

PLC_Value PLC_FreqSelectiveValue::operator[](size_t i) const
{
	NS_ASSERT(i < this->m_values.size());
	return this->m_values[i];
}

PLC_Value& PLC_FreqSelectiveValue::operator[](size_t i)
{
	NS_ASSERT_MSG(i < this->m_values.size(), "i:" << i << ", size: " << this->m_values.size());
	return this->m_values[i];
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator+=(double value)
{
	PLC_Value val(value, 0);

	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] += val;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator+=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] += value;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator+=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] += value.GetValue();

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator+=(const PLC_FreqSelectiveValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] += value[i];

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator-=(double value)
{
	PLC_Value val(value, 0);

	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] -= val;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator-=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] -= value;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator-=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] -= value.GetValue();

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator-=(const PLC_FreqSelectiveValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] -= value[i];

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator*=(double value)
{
	PLC_Value val(value, 0);

	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] *= val;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator*=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] *= value;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator*=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] *= value.GetValue();

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator*=(const PLC_FreqSelectiveValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] *= value[i];

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator/=(double value)
{
	PLC_Value val(value, 0);

	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] /= val;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator/=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] /= value;

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator/=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] /= value.GetValue();

	return *this;
}

PLC_FreqSelectiveValue& PLC_FreqSelectiveValue::operator/=(const PLC_FreqSelectiveValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		this->m_values[i] /= value[i];

	return *this;
}

PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& value)
{
	return value;
}

PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value);
	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = -ret.m_values[i];

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, double rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs;

	return ret;
}

PLC_FreqSelectiveValue operator+(double lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += lhs;

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs;

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += lhs;

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += val;

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(rhs);
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += val;

	return ret;
}

PLC_FreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, double rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator-(double lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs - rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs - rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= val;

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = val - rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, double rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator*(double lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= lhs;

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= lhs;

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= val;

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(rhs);
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= val;

	return ret;
}

PLC_FreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, double rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator/(double lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs / rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs;

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_Value& lhs, const PLC_FreqSelectiveValue& rhs)
{
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs / rhs.m_values[i];

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= val;

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_ConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(rhs.GetSpectrumModel());
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = val / rhs[i];

	return ret;
}

PLC_FreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_FreqSelectiveValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs[i];

	return ret;
}

std::ostream& operator<<(std::ostream& stream, PLC_FreqSelectiveValue& value)
{
        stream << "PLC_FreqSelectiveValue: [ ";

        size_t i;
        for (i = 0; i < value.m_values.size(); i++) stream << value[i];

        stream << " ]";
        return stream;
}

//////////////////////////////////////// PLC_TimeVariantConstValue /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_TimeVariantConstValue);

TypeId
PLC_TimeVariantConstValue::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_TimeVariantConstValue")
	.SetParent<PLC_ValueBase> ()
  ;
  return tid;
}

PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(Ptr<const SpectrumModel> sm, PLC_Value value, size_t timeslots) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_CONSTANT)
{
	this->m_values = PLC_TimeVariantValue(timeslots, value);
}

PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValue& values) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_CONSTANT)
{
	NS_ASSERT(values.size() == PLC_Time::GetNumTimeslots());
	this->m_values = values;
}

PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(const PLC_ConstValue& value, size_t timeslots) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_CONSTANT)
{
	this->m_values = PLC_TimeVariantValue(timeslots, value.GetValue());
}

PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(const PLC_TimeVariantConstValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_CONSTANT)
{
	this->m_values = value.GetValues();
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator=(const PLC_ConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = PLC_TimeVariantValue(this->GetNumTimeSlots(), value.GetValue());
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator=(const PLC_TimeVariantConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = value.GetValues();
	NS_ASSERT(this->m_values.size() == this->m_spectrum_model->GetNumBands());
	return *this;
}

PLC_Value PLC_TimeVariantConstValue::operator[](size_t i) const
{
	NS_ASSERT(i < this->m_values.size());
	return this->m_values[i];
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator+=(double value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] += PLC_Value(value, 0);
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator+=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] += value;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator+=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	PLC_Value val = value.GetValue();
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] += val;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator+=(const PLC_TimeVariantConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] += value[i];
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator-=(double value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] -= PLC_Value(value, 0);
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator-=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] -= value;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator-=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	PLC_Value val = value.GetValue();
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] -= val;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator-=(const PLC_TimeVariantConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] -= value[i];
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator*=(double value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] *= PLC_Value(value, 0);
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator*=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] *= value;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator*=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	PLC_Value val = value.GetValue();
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] *= val;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator*=(const PLC_TimeVariantConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] *= value[i];
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator/=(double value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] /= PLC_Value(value, 0);
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator/=(const PLC_Value& value)
{
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] /= value;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator/=(const PLC_ConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	PLC_Value val = value.GetValue();
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] /= val;
	return *this;
}

PLC_TimeVariantConstValue& PLC_TimeVariantConstValue::operator/=(const PLC_TimeVariantConstValue& value)
{
	NS_ASSERT(value.GetSpectrumModel() == this->m_spectrum_model);
	size_t i;
	for (i = 0; i < this->m_values.size(); i++) this->m_values[i] /= value[i];
	return *this;
}

PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs)
{
	return lhs;
}

PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs)
{
	PLC_TimeVariantConstValue ret(lhs.GetSpectrumModel());
	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = -lhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, double rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs;

	return ret;
}

PLC_TimeVariantConstValue operator+(double lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += lhs;

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs;

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += lhs;

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += val;

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(rhs);
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += val;

	return ret;
}

PLC_TimeVariantConstValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] += rhs.m_values[i];

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(lhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(rhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += lhs[j];
	}

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, double rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator-(double lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs - rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs - rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= val;

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = val - rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] -= rhs.m_values[i];

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(lhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[j] - rhs[i];
	}

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, double rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator*(double lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= lhs;

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= lhs;

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= val;

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(rhs);
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= val;

	return ret;
}

PLC_TimeVariantConstValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] *= rhs.m_values[i];

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(lhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(rhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= lhs[j];
	}

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, double rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator/(double lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs / rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_Value& rhs)
{
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs;

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_Value& lhs, const PLC_TimeVariantConstValue& rhs)
{
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = lhs / rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_ConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);
	PLC_Value val = rhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= val;

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_ConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(rhs.GetSpectrumModel());
	PLC_Value val = lhs.GetValue();

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] = val / rhs.m_values[i];

	return ret;
}

PLC_TimeVariantConstValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantConstValue ret(lhs);

	size_t i;
	for (i = 0; i < ret.m_values.size(); i++)
		ret.m_values[i] /= rhs.m_values[i];

	return ret;
}

std::ostream& operator<<(std::ostream& stream, PLC_TimeVariantConstValue& value)
{
	stream << "PLC_TimeVariantConstValue: [ ";

	size_t i;
	for (i = 0; i < value.m_values.size(); i++) stream << value[i];

	stream << " ]";
	return stream;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(lhs);

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());

	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[j] / rhs[i];
	}

	return ret;
}

//////////////////////////////////////// PLC_TimeVariantFreqSelectiveValue /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_TimeVariantFreqSelectiveValue);

TypeId
PLC_TimeVariantFreqSelectiveValue::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_TimeVariantFreqSelectiveValue")
	.SetParent<PLC_ValueBase> ()
  ;
  return tid;
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, size_t timeslots, PLC_Value value) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	this->m_values = PLC_TimeVariantValueSpectrum(timeslots, PLC_ValueSpectrum(sm->GetNumBands(), value));
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValue& values) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	size_t i;
	for (i = 0; i < values.size(); i++)
		this->m_values.push_back(PLC_TimeVariantValue(sm->GetNumBands(), values[i]));
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, const PLC_TimeVariantValueSpectrum& values) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	NS_ASSERT(values.size() == PLC_Time::GetNumTimeslots());
	this->m_values = values;
	size_t i;
	for (i = 0; i < this->m_values.size(); i++)
		NS_ASSERT(this->m_values[i].size() == sm->GetNumBands());
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(const PLC_ConstValue& value, size_t timeslots) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	this->m_values = PLC_TimeVariantValueSpectrum(timeslots, PLC_ValueSpectrum(value.GetNumBands(), value.GetValue()));
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(const PLC_FreqSelectiveValue& value, size_t timeslots) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	this->m_values = PLC_TimeVariantValueSpectrum(timeslots, value.GetValues());
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(const PLC_TimeVariantConstValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		this->m_values.push_back(PLC_ValueSpectrum(value.GetNumBands(), value[i]));
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(const PLC_TimeVariantFreqSelectiveValue& value) : PLC_ValueBase(value.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	this->m_values = value.GetValues();
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(PLC_FreqSelectiveValue& offset, PLC_FreqSelectiveValue& amplitude, double phi, size_t timeslots) : PLC_ValueBase(offset.GetSpectrumModel(), PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	NS_ASSERT(offset.GetSpectrumModel() == amplitude.GetSpectrumModel());

	size_t i;
	for (i = 0; i < timeslots; i++) {
		double t = 0.5*PLC_Time::GetResolutionS() + i * PLC_Time::GetResolutionS();
//		double variation = fabs(sin(2*M_PI*t/PLC_Time::GetPeriodS() + phi));
		double variation = sin(2*M_PI*t/PLC_Time::GetPeriodS() + phi);

		this->m_values.push_back((offset + (amplitude * variation)).GetValues());
	}
}

PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(Ptr<const SpectrumModel> sm, struct PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet& paramSet, size_t timeslots) : PLC_ValueBase(sm, PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE)
{
	PLC_FreqSelectiveValue offset(sm, paramSet.R_offset, paramSet.Q_offset, paramSet.f_0_offset);
	PLC_FreqSelectiveValue amplitude(sm, paramSet.R_offset, paramSet.Q_offset, paramSet.f_0_offset);

	size_t i;
	for (i = 0; i < timeslots; i++) {
		double t = 0.5*PLC_Time::GetResolutionS() + i * PLC_Time::GetResolutionS();
//		double variation = fabs(sin(2*M_PI*t/PLC_Time::GetPeriodS() + paramSet.phi));
		double variation = sin(2*M_PI*t/PLC_Time::GetPeriodS() + paramSet.phi);

		this->m_values.push_back((offset + (amplitude * variation)).GetValues());
	}
}

PLC_ValueSpectrum PLC_TimeVariantFreqSelectiveValue::operator[](size_t i) const
{
	NS_ASSERT(i < this->m_values.size());
	return this->m_values[i];
}

PLC_ValueSpectrum& PLC_TimeVariantFreqSelectiveValue::operator[](size_t i)
{
	NS_ASSERT(i < this->m_values.size());
	return this->m_values[i];
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator=(const PLC_ConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = PLC_TimeVariantValueSpectrum(this->GetNumTimeSlots(), PLC_ValueSpectrum(m_spectrum_model->GetNumBands(), value.GetValue()));
	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator=(const PLC_TimeVariantConstValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	PLC_TimeVariantValue values = value.GetValues();

	m_values.clear();
	unsigned int i;
	for (i=0; i < value.GetNumTimeSlots (); i++)
        {
            m_values.push_back(PLC_ValueSpectrum(m_spectrum_model->GetNumBands(), values[i]));
        }
	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator=(const PLC_TimeVariantFreqSelectiveValue& value)
{
	this->m_spectrum_model = value.GetSpectrumModel();
	this->m_values = value.GetValues();
	NS_ASSERT(this->m_values.size() == this->m_spectrum_model->GetNumBands());
	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(double value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += PLC_Value(value, 0);
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(const PLC_Value& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += value;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(const PLC_ConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());
	PLC_Value val = value.GetValue();

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += val;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(const PLC_FreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += value[j];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(const PLC_TimeVariantConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += value[i];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator+=(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] += value[i][j];
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(double value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= PLC_Value(value, 0);
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(const PLC_Value& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= value;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(const PLC_ConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());
	PLC_Value val = value.GetValue();

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= val;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(const PLC_FreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= value[j];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(const PLC_TimeVariantConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= value[i];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator-=(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] -= value[i][j];
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(double value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= PLC_Value(value, 0);
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(const PLC_Value& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= value;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(const PLC_ConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());
	PLC_Value val = value.GetValue();

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= val;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(const PLC_FreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= value[j];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(const PLC_TimeVariantConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= value[i];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator*=(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] *= value[i][j];
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(double value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= PLC_Value(value, 0);
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(const PLC_Value& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= value;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(const PLC_ConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());
	PLC_Value val = value.GetValue();

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= val;
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(const PLC_FreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= value[j];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(const PLC_TimeVariantConstValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= value[i];
	}

	return *this;

}

PLC_TimeVariantFreqSelectiveValue& PLC_TimeVariantFreqSelectiveValue::operator/=(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = this->m_values.size()) < INT_MAX);
	NS_ASSERT(value.GetSpectrumModel() == this->GetSpectrumModel());

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < this->m_values[i].size(); j++)
			this->m_values[i][j] /= value[i][j];
	}

	return *this;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& value)
{
	return value;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, size;
	NS_ASSERT((size = value.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(value);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= -1;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += lhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += lhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = rhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = lhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += lhs[j];
	}
	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += lhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator+(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] += rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs - rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs - rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = rhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = lhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = val - rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[j] - rhs[i][j];
	}
	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[i] - rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator-(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] -= rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= lhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= lhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = rhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = lhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= lhs[j];
	}
	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(rhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= lhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator*(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] *= rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, double rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(double lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs / rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_Value& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_Value& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs / rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_ConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = rhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= val;
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_ConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_Value val = lhs.GetValue();
	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = val / rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_FreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs[j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_FreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[j] / rhs[i][j];
	}
	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantConstValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs[i];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantConstValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = rhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(rhs.GetSpectrumModel(), rhs.GetNumTimeSlots());
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] = lhs[i] / rhs[i][j];
	}

	return ret;
}

PLC_TimeVariantFreqSelectiveValue operator/(const PLC_TimeVariantFreqSelectiveValue& lhs, const PLC_TimeVariantFreqSelectiveValue& rhs)
{
	int i, size;
	NS_ASSERT((size = lhs.m_values.size()) < INT_MAX);
	NS_ASSERT(lhs.GetSpectrumModel() == rhs.GetSpectrumModel());
	NS_ASSERT(lhs.GetNumTimeSlots() == rhs.GetNumTimeSlots());

	PLC_TimeVariantFreqSelectiveValue ret(lhs);
#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.m_values[i].size(); j++)
			ret.m_values[i][j] /= rhs[i][j];
	}

	return ret;
}

std::ostream& operator<<(std::ostream& stream, PLC_TimeVariantFreqSelectiveValue& value)
{
        stream << "PLC_TimeVariantFreqSelectiveValue: [\n";

        size_t i, j;
        for (i = 0; i < value.m_values.size(); i++) {
        	stream << "\nTimeslot " << i << ": [\n";
        	for (j = 0; j < value.m_values[i].size(); j++)
        		stream << value.m_values[i][j];

        	stream << "\n]";
        }

        stream << "\n]";
        return stream;
}
//////////////////////////////////////// global functions /////////////////////////////////////////////

double abs(const PLC_ConstValue& value)
{
	return abs(value.GetValue());
}

PLC_FreqSelectiveRealValue abs(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveRealValue ret(value.GetSpectrumModel()->GetNumBands(), 0);

	size_t i;
	for (i = 0; i < value.GetSpectrumModel()->GetNumBands(); i++)
		ret[i] = abs(value[i]);

	return ret;
}

PLC_TimeVariantRealValue abs(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantRealValue ret;

	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret.push_back(abs(value[i]));

	return ret;
}

PLC_TimeVariantFreqSelectiveRealValue abs(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, j, numtimeslots, numbands;
	NS_ASSERT((numtimeslots = value.GetNumTimeSlots()) < INT_MAX);
	NS_ASSERT((numbands = value.GetNumBands()) < INT_MAX);
	numbands = value.GetNumBands();

	PLC_TimeVariantFreqSelectiveRealValue ret(numtimeslots, PLC_FreqSelectiveRealValue(numbands, 0));

//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < numtimeslots; i++) {
		for (j = 0; j < numbands; j++) {
			ret[i][j] = abs(value[i][j]);
		}
	}

	return ret;
}

double arg(const PLC_ConstValue& value)
{
	return arg(value.GetValue());
}

PLC_FreqSelectiveRealValue arg(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveRealValue ret(value.GetSpectrumModel()->GetNumBands(), 0);

	size_t i;
	for (i = 0; i < value.GetSpectrumModel()->GetNumBands(); i++)
		ret[i] = arg(value[i]);

	return ret;
}

PLC_TimeVariantRealValue arg(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantRealValue ret;

	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret.push_back(arg(value[i]));

	return ret;
}

PLC_TimeVariantFreqSelectiveRealValue arg(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, j, numtimeslots, numbands;
	NS_ASSERT((numtimeslots = value.GetNumTimeSlots()) < INT_MAX);
	NS_ASSERT((numbands = value.GetNumBands()) < INT_MAX);
	numbands = value.GetNumBands();

	PLC_TimeVariantFreqSelectiveRealValue ret(numtimeslots, PLC_FreqSelectiveRealValue(numbands, 0));

//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < numtimeslots; i++) {
		for (j = 0; j < numbands; j++) {
			ret[i][j] = arg(value[i][j]);
		}
	}

	return ret;
}

double real(const PLC_ConstValue& value)
{
	return real(value.GetValue());
}

PLC_FreqSelectiveRealValue real(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveRealValue ret(value.GetSpectrumModel()->GetNumBands(), 0);

	size_t i;
	for (i = 0; i < value.GetSpectrumModel()->GetNumBands(); i++)
		ret[i] = real(value[i]);

	return ret;
}

PLC_TimeVariantRealValue real(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantRealValue ret;

	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret.push_back(real(value[i]));

	return ret;
}

PLC_TimeVariantFreqSelectiveRealValue real(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, j, numtimeslots, numbands;
	NS_ASSERT((numtimeslots = value.GetNumTimeSlots()) < INT_MAX);
	NS_ASSERT((numbands = value.GetNumBands()) < INT_MAX);
	numbands = value.GetNumBands();

	PLC_TimeVariantFreqSelectiveRealValue ret(numtimeslots, PLC_FreqSelectiveRealValue(numbands, 0));

//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < numtimeslots; i++) {
		for (j = 0; j < numbands; j++) {
			ret[i][j] = real(value[i][j]);
		}
	}

	return ret;
}

double imag(const PLC_ConstValue& value)
{
	return imag(value.GetValue());
}

PLC_FreqSelectiveRealValue imag(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveRealValue ret(value.GetSpectrumModel()->GetNumBands(), 0);

	size_t i;
	for (i = 0; i < value.GetSpectrumModel()->GetNumBands(); i++)
		ret[i] = imag(value[i]);

	return ret;
}

PLC_TimeVariantRealValue imag(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantRealValue ret;

	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret.push_back(imag(value[i]));

	return ret;
}

PLC_TimeVariantFreqSelectiveRealValue imag(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, j, numtimeslots, numbands;
	NS_ASSERT((numtimeslots = value.GetNumTimeSlots()) < INT_MAX);
	NS_ASSERT((numbands = value.GetNumBands()) < INT_MAX);
	numbands = value.GetNumBands();

	PLC_TimeVariantFreqSelectiveRealValue ret(numtimeslots, PLC_FreqSelectiveRealValue(numbands, 0));

//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < numtimeslots; i++) {
		for (j = 0; j < numbands; j++) {
			ret[i][j] = imag(value[i][j]);
		}
	}

	return ret;
}

double absSqr(const PLC_ConstValue& value)
{
	return (pow(real(value.GetValue()), 2) + pow(imag(value.GetValue()), 2));
}

PLC_FreqSelectiveRealValue absSqr(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveRealValue ret(value.GetSpectrumModel()->GetNumBands(), 0);

	size_t i;
	for (i = 0; i < value.GetSpectrumModel()->GetNumBands(); i++)
		ret[i] = pow(real(value[i]), 2) + pow(imag(value[i]), 2);

	return ret;
}

PLC_TimeVariantRealValue absSqr(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantRealValue ret;

	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret.push_back(pow(real(value[i]), 2) + pow(imag(value[i]), 2));

	return ret;
}

PLC_TimeVariantFreqSelectiveRealValue absSqr(const PLC_TimeVariantFreqSelectiveValue& value)
{
	int i, j, numtimeslots, numbands;
	NS_ASSERT((numtimeslots = value.GetNumTimeSlots()) < INT_MAX);
	NS_ASSERT((numbands = value.GetNumBands()) < INT_MAX);
	numbands = value.GetNumBands();

	PLC_TimeVariantFreqSelectiveRealValue ret(numtimeslots, PLC_FreqSelectiveRealValue(numbands, 0));

	// qwt plot gets screwed up by parallel processing
//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < numtimeslots; i++) {
		for (j = 0; j < numbands; j++) {
			ret[i][j] = pow(real(value[i][j]), 2) + pow(imag(value[i][j]), 2);
		}
	}

	return ret;
}

PLC_ConstValue sinh(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), sinh(value.GetValue()));
}

PLC_FreqSelectiveValue sinh(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
	{
		ret[i] = sinh(value[i]);
	}

	return ret;
}

PLC_TimeVariantConstValue sinh(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = sinh(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue sinh(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = sinh(value[i][j]);
		}
	}

	return ret;
}

PLC_ConstValue cosh(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), cosh(value.GetValue()));
}

PLC_FreqSelectiveValue cosh(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
	{
		ret[i] = cosh(value[i]);
	}

	return ret;
}

PLC_TimeVariantConstValue cosh(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = cosh(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue cosh(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = cosh(value[i][j]);
		}
	}

	return ret;
}

PLC_ConstValue exp(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), exp(value.GetValue()));
}

PLC_FreqSelectiveValue exp(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
	{
		ret[i] = exp(value[i]);
	}

	return ret;
}

PLC_TimeVariantConstValue exp(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = exp(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue exp(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = exp(value[i][j]);
		}
	}

	return ret;
}

PLC_ConstValue log10(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), log10(value.GetValue()));
}

PLC_FreqSelectiveValue log10(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
		ret[i] = log10(value[i]);

	return ret;
}

PLC_TimeVariantConstValue log10(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = log10(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue log10(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

//#ifdef PLC_MULTITHREADING
//#pragma omp parallel for
//#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = log10(value[i][j]);
		}
	}

	return ret;
}

PLC_ConstValue tan(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), tan(value.GetValue()));
}

PLC_FreqSelectiveValue tan(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
		ret[i] = tan(value[i]);

	return ret;
}

PLC_TimeVariantConstValue tan(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = tan(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue tan(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = tan(value[i][j]);
		}
	}

	return ret;
}

PLC_ConstValue tanh(const PLC_ConstValue& value)
{
	return PLC_ConstValue(value.GetSpectrumModel(), tanh(value.GetValue()));
}

PLC_FreqSelectiveValue tanh(const PLC_FreqSelectiveValue& value)
{
	PLC_FreqSelectiveValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumBands(); i++)
		ret[i] = tanh(value[i]);

	return ret;
}

PLC_TimeVariantConstValue tanh(const PLC_TimeVariantConstValue& value)
{
	PLC_TimeVariantConstValue ret(value.GetSpectrumModel());
	size_t i;
	for (i = 0; i < value.GetNumTimeSlots(); i++)
		ret[i] = tanh(value[i]);

	return ret;
}

PLC_TimeVariantFreqSelectiveValue tanh(const PLC_TimeVariantFreqSelectiveValue& value)
{
	PLC_TimeVariantFreqSelectiveValue ret(value.GetSpectrumModel());
	int i, size;
	NS_ASSERT((size = value.GetNumTimeSlots()) < INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
	for (i = 0; i < size; i++) {
		size_t j;
		for (j = 0; j < ret.GetNumBands(); j++) {
			ret[i][j] = tanh(value[i][j]);
		}
	}

	return ret;
}

double max(SpectrumValue& value)
{
	double ret = *value.ValuesBegin();

	Values::const_iterator it;
	for (it = value.ValuesBegin(); it != value.ValuesEnd(); it++)
	{
		if (*it > ret) ret = *it;
	}

	return ret;
}

double min(SpectrumValue& value)
{
	double ret = *value.ValuesBegin();

	Values::const_iterator it;
	for (it = value.ValuesBegin(); it != value.ValuesEnd(); it++)
	{
		if (*it < ret) ret = *it;
	}

	return ret;
}

double Pwr(const SpectrumValue& value)
{
	double pwr = 0;

	Values::const_iterator vit = value.ConstValuesBegin ();
	Bands::const_iterator bit = value.ConstBandsBegin ();

	while  (bit != value.ConstBandsEnd ()) {
		NS_ASSERT (vit != value.ConstValuesEnd ());
		pwr +=  (*vit) *  (bit->fh - bit->fl);
		++bit;
		++vit;
	}

	return pwr;
}

double W2dBm(double watt)
{
	return 10*std::log10(watt * 10e3);
}

double max(PLC_FreqSelectiveRealValue& value)
{
	double ret = 0;
	size_t i;
	for (i = 0; i < value.size(); i++)
	{
		if (value[i] > ret) ret = value[i];
	}

	return ret;
}

double min(PLC_FreqSelectiveRealValue& value)
{
	if (value.empty())
		return 0;

	double ret = value[0];
	size_t i;
	for (i = 1; i < value.size(); i++)
	{
		if (value[i] < ret) ret = value[i];
	}

	return ret;
}

void AddInverseValue(PLC_ValueBase *res, PLC_ValueBase *imp)
{
	switch(res->GetValueType()) {

		case PLC_ValueBase::CONSTANT:
		{
			PLC_ConstImpedance *res_imp = static_cast<PLC_ConstImpedance *> (res);

			switch (imp->GetValueType()) {

				case PLC_ValueBase::CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_ConstImpedance *> (imp));
					break;
				}

				default:
				{
					NS_FATAL_ERROR("AddInverseValue(): incompatible impedance type");
					break;
				}
			}

			break;
		}

		case PLC_ValueBase::FREQ_SELECTIVE:
		{
			PLC_FreqSelectiveImpedance *res_imp = static_cast<PLC_FreqSelectiveImpedance *> (res);

			switch (imp->GetValueType()) {

				case PLC_ValueBase::CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_ConstImpedance *> (imp));
					break;
				}

				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					(*res_imp) += 1 / (*static_cast<PLC_FreqSelectiveImpedance *> (imp));
					break;
				}

				default:
				{
					NS_FATAL_ERROR("AddInverseValue(): incompatible impedance type");
					break;
				}
			}

			break;
		}

		case PLC_ValueBase::TIMEVARIANT_CONSTANT:
		{
			PLC_TimeVariantConstImpedance *res_imp = static_cast<PLC_TimeVariantConstImpedance *> (res);

			switch (imp->GetValueType()) {

				case PLC_ValueBase::CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_ConstImpedance *> (imp));
					break;
				}

				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_TimeVariantConstImpedance *> (imp));
					break;
				}

				default:
				{
					NS_FATAL_ERROR("AddInverseValue(): incompatible impedance type");
					break;
				}

			}

			break;
		}

		case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
		{
			PLC_TimeVariantFreqSelectiveImpedance *res_imp = static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (res);

			switch (imp->GetValueType()) {

				case PLC_ValueBase::CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_ConstImpedance *> (imp));
					break;
				}

				case PLC_ValueBase::FREQ_SELECTIVE:
				{
					(*res_imp) += 1 / (*static_cast<PLC_FreqSelectiveImpedance *> (imp));
					break;
				}

				case PLC_ValueBase::TIMEVARIANT_CONSTANT:
				{
					(*res_imp) += 1 / (*static_cast<PLC_TimeVariantConstImpedance *> (imp));
					break;
				}

				case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
				{
					(*res_imp) += 1 / (*static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (imp));
					break;
				}

				default:
				{
					NS_FATAL_ERROR("AddInverseValue(): incompatible impedance type");
					break;
				}

			}

			break;
		}

		default:
		{
			NS_FATAL_ERROR("CalcEquivalentImpedance(): not compatible impedance type");
			break;
		}
	}
}

}
