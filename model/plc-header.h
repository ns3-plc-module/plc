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

#define MAX_PPDU_SYMBOLS std::numeric_limits<uint16_t>::max()

class PLC_Preamble : public Header
{
public:
	static TypeId GetTypeId (void);

	PLC_Preamble(void);
	~PLC_Preamble(void);

	static void SetDuration (Time duration);
	static Time GetDuration (void);

	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

private:
	static Time preamble_duration;
};

class PLC_PhyFrameControlHeader : public Header
{
public:
	enum DelimiterType
	{
		DATA,
		ACK,
		NACK
	};

	static TypeId GetTypeId (void);

	PLC_PhyFrameControlHeader (void);
	~PLC_PhyFrameControlHeader (void);

	void SetDelimiterType (DelimiterType type) { m_delimiter_type = (uint8_t) type; }
	DelimiterType GetDelimiterType (void) { return (DelimiterType) m_delimiter_type; }
	void SetPayloadSymbols (uint16_t symbols) { m_payload_symbols = symbols; }
	uint16_t GetPayloadSymbols (void) { return m_payload_symbols; }
	void SetPayloadMcs (ModulationAndCodingType mcs) { m_payload_mcs = mcs; }
	ModulationAndCodingType GetPayloadMcs (void) { return (ModulationAndCodingType) m_payload_mcs; }
	void SetFccs (uint8_t fccs) { m_fccs = fccs; }
	uint8_t GetFccs (void) { return m_fccs; }

	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

private:
	uint8_t m_delimiter_type;
	uint16_t m_payload_symbols;
	uint8_t m_payload_mcs;
	uint8_t m_fccs; // frame control check sequence
};

std::ostream& operator<<(std::ostream& os, PLC_PhyFrameControlHeader::DelimiterType type);

class PLC_PhyRatelessFrameControlHeader : public Header
{
public:
	enum DelimiterType
	{
		DATA,
		ACK,
		NACK
	};

	static TypeId GetTypeId (void);

	PLC_PhyRatelessFrameControlHeader (void);
	~PLC_PhyRatelessFrameControlHeader (void);

	void SetDelimiterType (DelimiterType type) { m_delimiter_type = (uint8_t) type; }
	DelimiterType GetDelimiterType (void) { return (DelimiterType) m_delimiter_type; }
	void SetPayloadSymbols (uint16_t symbols) { m_payload_symbols = symbols; }
	uint16_t GetPayloadSymbols (void) { return m_payload_symbols; }
	void SetPayloadMcs (ModulationAndCodingType mcs) { m_payload_mcs = mcs; }
	ModulationAndCodingType GetPayloadMcs (void) { return (ModulationAndCodingType) m_payload_mcs; }
	void SetFccs (uint8_t fccs) { m_fccs = fccs; }
	uint8_t GetFccs (void) { return m_fccs; }
	void SetPrngSeed (uint16_t prng_seed) { m_prng_seed = prng_seed; }
	uint16_t GetPrngSeed (void) { return m_prng_seed; }
	void SetNumBlocks (uint32_t num_blocks) { m_num_blocks = num_blocks; }
	uint32_t GetNumBlocks (void) { return m_num_blocks; }

	virtual uint32_t GetSerializedSize (void) const;
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);
	virtual void Print (std::ostream &os) const;

private:
	uint8_t m_delimiter_type;
	uint16_t m_payload_symbols;
	uint8_t m_payload_mcs;
	uint16_t m_prng_seed;
	uint32_t m_num_blocks;
	uint8_t m_fccs; // frame control check sequence
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
