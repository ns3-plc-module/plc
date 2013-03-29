/*
 * plc-header.h
 *
 *  Created on: 2012-05-25
 *      Author: deadlock
 */

#ifndef PLC_HEADER_H_
#define PLC_HEADER_H_

#include <limits>

#include <ns3/mac48-address.h>
#include <ns3/header.h>
#include <ns3/tag.h>
#include <ns3/nstime.h>

#include "plc-defs.h"

namespace ns3 {

#define MAX_NUM_BLOCKS std::numeric_limits<uint32_t>::max()

class PLC_PhyPacketTag : public Tag
{
public:
	  static TypeId GetTypeId (void);
	  virtual TypeId GetInstanceTypeId (void) const;

	  void SetPayloadMcs(ModulationAndCodingType mcs) { m_payload_mcs = mcs; }
	  ModulationAndCodingType GetPayloadMcs(void) const { return m_payload_mcs; }
	  void SetPayloadDuration(Time duration) { m_duration = duration; }
	  Time GetPayloadDuration(void) const { return m_duration; }
	  void SetUncodedHeaderBits(uint16_t bits) { m_uncoded_header_bits = bits; }
	  uint16_t GetUncodedHeaderBits(void) { return m_uncoded_header_bits; }
	  void SetUncodedPayloadBits(uint16_t bits) { m_uncoded_payload_bits = bits; }
	  uint16_t GetUncodedPayloadBits(void) { return m_uncoded_payload_bits; }

	  virtual uint32_t GetSerializedSize (void) const;
	  virtual void Serialize (TagBuffer i) const;
	  virtual void Deserialize (TagBuffer i);
	  virtual void Print (std::ostream &os) const;

private:
	  ModulationAndCodingType m_payload_mcs;
	  Time m_duration;
	  uint16_t m_uncoded_header_bits;
	  uint32_t m_uncoded_payload_bits;
};

class PLC_PhyHeader : public Header
{
public:
	enum DelimiterType
	{
		NoResponseExpected,
		ResponseExpected,
		ACK,
		NACK
	};

	static TypeId GetTypeId (void);

	PLC_PhyHeader(void);
	~PLC_PhyHeader(void);

	void SetDelimiterType(DelimiterType type);
	DelimiterType GetDelimiterType(void);
	void SetFrameId(uint32_t id);
	uint32_t GetFrameId(void);
	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

private:
	uint8_t m_preamble;
	uint8_t m_delimiter_type;
	uint32_t m_frame_id;
};

class PLC_RatelessPhyHeader : public Header
{
public:
	static TypeId GetTypeId (void);

	PLC_RatelessPhyHeader(void);
	~PLC_RatelessPhyHeader(void);

	void SetPrngSeed(uint16_t seed);
	void SetFirstChunkSqn(uint8_t sqn);
	void SetDatagramId(uint16_t id);
	void SetNumBlocks(uint32_t length);
	void SetControlFrame(bool a);

	bool IsControlFrame(void) const;
	uint16_t GetPrngSeed(void) const;
	uint16_t GetDatagramId(void) const;
	uint32_t GetNumBlocks(void) const;
	uint8_t GetFirstChunkSqn(void) const;

	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

private:
	uint8_t m_flags;
	uint16_t m_prng_seed;
	uint16_t m_datagram_id;
	uint8_t m_first_chunk_sqn;
	uint32_t m_num_blocks;
	uint8_t m_crc;
};

class PLC_MacHeader : public Header
{
public:

	enum MacHdrType {
		DATA,
		ACK,
		NACK
	};

	static TypeId GetTypeId (void);

	PLC_MacHeader(void);
	~PLC_MacHeader(void);

	void SetDstAddress(Mac48Address addr);
	void SetSrcAddress(Mac48Address addr);
	void SetType(MacHdrType type);
	void SetSequenceNumber(uint16_t sqn);
	void SetMessageLength(uint32_t length);

	Mac48Address GetDstAddress(void) const;
	Mac48Address GetSrcAddress(void) const;
	MacHdrType GetType(void) const;
	uint16_t GetSequenceNumber(void) const;
	uint32_t GetMessageLength(void) const;

	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

	bool operator==(PLC_MacHeader& hdr)
	{
		return (hdr.m_dst_address == m_dst_address && hdr.m_src_address == m_src_address && hdr.m_msg_sqn == m_msg_sqn);
	}

private:
	Mac48Address m_dst_address;
	Mac48Address m_src_address;
	uint8_t m_flags;
	uint16_t m_msg_sqn;
	uint32_t m_msg_length;
};

}

#endif /* PLC_HEADER_H_ */
