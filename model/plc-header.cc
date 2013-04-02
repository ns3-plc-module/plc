/*
 * plc-header.cc
 *
 *  Created on: 2012-05-25
 *      Author: deadlock
 */

#include <ns3/address-utils.h>
#include "plc-header.h"

namespace ns3 {

//////////////////////// PLC_Preamble //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_Preamble);

Time PLC_Preamble::preamble_duration = MicroSeconds(10);

TypeId
PLC_Preamble::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_Preamble")
    .SetParent<Header> ()
    .AddConstructor<PLC_Preamble> ();
  return tid;
}

PLC_Preamble::PLC_Preamble (void)
{
}

PLC_Preamble::~PLC_Preamble (void)
{
}

void
PLC_Preamble::SetDuration (Time duration)
{
	preamble_duration = duration;
}

Time
PLC_Preamble::GetDuration (void)
{
	return preamble_duration;
}

uint32_t
PLC_Preamble::GetSerializedSize (void) const
{
	return 0;
}

TypeId
PLC_Preamble::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_Preamble::Serialize (Buffer::Iterator start) const
{
}

uint32_t
PLC_Preamble::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	return i.GetDistanceFrom(start);
}

void
PLC_Preamble::Print (std::ostream &os) const
{
	os << "duration = " << GetDuration();
}

//////////////////////// PLC_PhyFrameControlHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_PhyFrameControlHeader);

TypeId
PLC_PhyFrameControlHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_PhyFrameControlHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_PhyFrameControlHeader> ();
  return tid;
}

PLC_PhyFrameControlHeader::PLC_PhyFrameControlHeader(void)
{
}

PLC_PhyFrameControlHeader::~PLC_PhyFrameControlHeader(void)
{
}

uint32_t
PLC_PhyFrameControlHeader::GetSerializedSize (void) const
{
	return 5;
}

TypeId
PLC_PhyFrameControlHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_PhyFrameControlHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator i = start;
	i.WriteU8(m_delimiter_type);
	i.WriteU16(m_payload_symbols);
	i.WriteU8(m_payload_mcs);
	i.WriteU8(m_fccs);
}

uint32_t
PLC_PhyFrameControlHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_delimiter_type 	= i.ReadU8();
	m_payload_symbols 	= i.ReadU16();
	m_payload_mcs 		= i.ReadU8();
	m_fccs 				= i.ReadU8();
	return i.GetDistanceFrom(start);
}

void
PLC_PhyFrameControlHeader::Print (std::ostream &os) const
{
	os << "delimiter type = " << (PLC_PhyFrameControlHeader::DelimiterType) m_delimiter_type;
	os << ", payload symbols = " << (int) m_payload_symbols;
	os << ", payload mcs = " << (ModulationAndCodingType) m_payload_mcs;
	os << ", fccs = " << (int) m_fccs;
}

std::ostream&
operator<<(std::ostream& os, PLC_PhyFrameControlHeader::DelimiterType type)
{
	switch (type)
	{
		case (PLC_PhyFrameControlHeader::DATA):
		{
			os << "DATA";
			break;
		}
		case (PLC_PhyFrameControlHeader::ACK):
		{
			os << "ACK";
			break;
		}
		case (PLC_PhyFrameControlHeader::NACK):
		{
			os << "NACK";
			break;
		}
		default:
		{
			os << "INVALID";
			break;
		}
	}
	return os;
}

//////////////////////// PLC_PhyRatelessFrameControlHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_PhyRatelessFrameControlHeader);

TypeId
PLC_PhyRatelessFrameControlHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_PhyRatelessFrameControlHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_PhyRatelessFrameControlHeader> ();
  return tid;
}

PLC_PhyRatelessFrameControlHeader::PLC_PhyRatelessFrameControlHeader(void)
{
}

PLC_PhyRatelessFrameControlHeader::~PLC_PhyRatelessFrameControlHeader(void)
{
}

uint32_t
PLC_PhyRatelessFrameControlHeader::GetSerializedSize (void) const
{
	return 11;
}

TypeId
PLC_PhyRatelessFrameControlHeader::GetInstanceTypeId (void) const
{
	return GetTypeId ();
}

void
PLC_PhyRatelessFrameControlHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator i = start;
	i.WriteU8(m_delimiter_type);
	i.WriteU16(m_payload_symbols);
	i.WriteU8(m_payload_mcs);
	i.WriteU16(m_prng_seed);
	i.WriteU32(m_num_blocks);
	i.WriteU8(m_fccs);
}

uint32_t
PLC_PhyRatelessFrameControlHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_delimiter_type 	= i.ReadU8();
	m_payload_symbols 	= i.ReadU16();
	m_payload_mcs 		= i.ReadU8();
	m_prng_seed 		= i.ReadU16();
	m_num_blocks 		= i.ReadU32();
	m_fccs 				= i.ReadU8();
	return i.GetDistanceFrom(start);
}

void
PLC_PhyRatelessFrameControlHeader::Print (std::ostream &os) const
{
	os << "delimiter type = " << (PLC_PhyFrameControlHeader::DelimiterType) m_delimiter_type;
	os << ", payload symbols = " << (int) m_payload_symbols;
	os << ", payload mcs = " << (ModulationAndCodingType) m_payload_mcs;
	os << ", Prng seed = " << (int) m_prng_seed;
	os << ", Blocks = " << (int) m_num_blocks;
	os << ", fccs = " << (int) m_fccs;
}

//////////////////////// PLC_MacHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_MacHeader);

TypeId
PLC_MacHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_MacHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_MacHeader> ();
  return tid;
}

PLC_MacHeader::PLC_MacHeader(void)
{
}

PLC_MacHeader::~PLC_MacHeader(void)
{
}

uint32_t
PLC_MacHeader::GetSerializedSize (void) const
{
	return 19;
}

TypeId
PLC_MacHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_MacHeader::Serialize (Buffer::Iterator start) const
{
    Buffer::Iterator i = start;
    WriteTo (i, m_dst_address);
    WriteTo (i, m_src_address);
    i.WriteU8(m_flags);
    i.WriteHtonU16(m_msg_sqn);
	i.WriteHtonU32(m_msg_length);
}

uint32_t
PLC_MacHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	ReadFrom (i, m_dst_address);
	ReadFrom (i, m_src_address);
	m_flags = i.ReadU8();
	m_msg_sqn = i.ReadNtohU16();
	m_msg_length = i.ReadNtohU32();
	return i.GetDistanceFrom(start);
}

void
PLC_MacHeader::Print (std::ostream &os) const
{
	os << "destination address = " << m_dst_address;
	os << ", source address = " << m_src_address;
	os << ", type = " << GetType();
	os << ", sequence number = " << (int) m_msg_sqn;
	os << ", message length = " << (int) m_msg_length;
}

void
PLC_MacHeader::SetDstAddress (Mac48Address addr)
{
	m_dst_address = addr;
}

void
PLC_MacHeader::SetSrcAddress (Mac48Address addr)
{
	m_src_address = addr;
}

void
PLC_MacHeader::SetType (PLC_MacHeader::MacHdrType type)
{
	m_flags = (m_flags & 0xf0) | (0x0f & type);
}

void
PLC_MacHeader::SetSequenceNumber (uint16_t sqn)
{
	m_msg_sqn = sqn;
}

void
PLC_MacHeader::SetMessageLength (uint32_t length)
{
	m_msg_length = length;
}

Mac48Address
PLC_MacHeader::GetDstAddress (void) const
{
	return m_dst_address;
}

Mac48Address
PLC_MacHeader::GetSrcAddress (void) const
{
	return m_src_address;
}

PLC_MacHeader::MacHdrType
PLC_MacHeader::GetType (void) const
{
	return (PLC_MacHeader::MacHdrType)(m_flags & 0x0f);
}

uint16_t
PLC_MacHeader::GetSequenceNumber (void) const
{
	return m_msg_sqn;
}

uint32_t
PLC_MacHeader::GetMessageLength (void) const
{
	return m_msg_length;
}

}
