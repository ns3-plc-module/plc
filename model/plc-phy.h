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

#ifndef PLC_PHY_H_
#define PLC_PHY_H_

#include <cmath>
#include <vector>
#include <ns3/object.h>
#include <ns3/nstime.h>
#include <ns3/traced-value.h>
#include <ns3/trace-source-accessor.h>
#include "plc-interface.h"
#include "plc-header.h"
#include "plc-outlet.h"
#include "plc-link-performance-model.h"
#include "plc-channel.h"

namespace ns3 {

// Forward declarations
class PLC_TrxMetaInfo;
class PLC_Channel;
class PLC_ChannelTransferImpl;
class PLC_LinkPerformanceModel;

/**
 * Clear channel assessment results
 */
typedef enum
{
	CHANNEL_CLEAR,
	CHANNEL_OCCUPIED
} PLC_PhyCcaResult;

// Callback definitions
typedef Callback<void, Ptr<const Packet> > PhyRxEndOkCallback;
typedef Callback< void > PhyRxEndErrorCallback;
typedef Callback< void, PLC_PhyCcaResult > PLC_PhyCcaConfirmCallback;
typedef Callback<void> PLC_PhyFrameSentCallback;
typedef std::vector<std::pair<Time, Ptr<const SpectrumValue> > > PLC_SinrTrace;

// Helper functions
size_t RequiredSymbols (size_t encoded_bits, ModulationAndCodingType mcs, size_t subbands);
Time CalculateTransmissionDuration(size_t encoded_bits, ModulationAndCodingType mcs, size_t subbands);

/**
 * Abstract base class for PLC PHYs
 *
 */
class PLC_Phy : public Object
{
public:

	virtual ~PLC_Phy ();

	static TypeId GetTypeId (void);

	/**
	 * Start transmitting a packet
	 * @param p Packet
	 * @param txPsd Power Spectral Density of the waveform to be transmitted
	 * @param duration Time the packet needs for transmission
	 * @return True if PHY started transmission
	 */
	bool StartTx (Ptr<Packet> p);

	/**
	* Notify the PLC_Phy instance of an incoming waveform
	*
	* @param p the Packet associated with the incoming waveform
	* @param rxPsd the Power Spectral Density of the incoming
	* @param duration the duration of the incoming waveform
	* @param metaInfo meta information for link performance emulation
	*/
	void StartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

	/**
	 * Notify the PLC_Phy instance that the Power Spectral Density of the incoming waveform transmitted by interface txId
	 * has changed to newRxPsd
	 * @param txId
	 * @param newRxPsd
	 */
	void RxPsdChanged (uint32_t txId, Ptr<SpectrumValue> newRxPsd);

	/**
	 * \brief Set the global symbol duration value for all PHYs
	 *
	 * This method should not be called directly, but
	 * by calling PLC_TimeModel::SetPeriodicityModel,
	 * as the simulations time resolution will be adapted to
	 * symbol granularity
	 *
	 * \param tSymbol Duration of a modulation symbol
	 */
	static void SetSymbolDuration (Time tSymbol);

	/**
	 * \return The global modulation symbol duration
	 */
	static Time GetSymbolDuration (void);

	/**
	 * @return PLC_Node the PHY is attached to
	 */
	Ptr<PLC_Node> GetNode (void) { return m_node; }

	/**
	 * Callback after a successful frame transmission
	 * @param c
	 */
	void SetFrameSentCallback (PLC_PhyFrameSentCallback c);

	/**
	 * Callback for a successful datagram/message reception
	 * @param c
	 */
	void SetReceiveSuccessCallback (PhyRxEndOkCallback c);

	/**
	 * Callback for a failed datagram/message reception
	 * @param c
	 */
	void SetReceiveErrorCallback (PhyRxEndErrorCallback c);

	/**
	 * @return Channel transfer implementation to rxPhy
	 */
	PLC_ChannelTransferImpl *GetChannelTransferImpl (Ptr<PLC_Phy> rxPhy);

	/**
	 * @return Channel transfer vector to rxPhy
	 */
	Ptr<PLC_TransferBase> GetChannelTransferVector(Ptr<PLC_Phy> rxPhy);

	/**
	 * Frame sent notification
	 */
	virtual void NotifyFrameSent (void);

protected:
	static Time symbol_duration;

	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual bool DoStartTx (Ptr<Packet> p) = 0;
	virtual void DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo) = 0;
	virtual void DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> newRxPsd) = 0;
	virtual PLC_ChannelTransferImpl *DoGetChannelTransferImpl (Ptr<PLC_Phy> rxPhy) = 0;

	Ptr<PLC_Node> m_node;

	PLC_PhyFrameSentCallback 	m_frame_sent_callback;
	PhyRxEndOkCallback 			m_receive_success_cb;
	PhyRxEndErrorCallback 		m_receive_error_cb;
};

/**
 *	\class PLC_HalfDuplexOfdmPhy
 *
 *	\brief Base class for half duplex OFDM PHY devices
 *
 *  Each half duplex PHY owns both a txInterface for transmitting and a rxInterface
 *  for receiving. Depending on the PHY's state the access impedance of
 *  the device may change, which influences channel transfer functions.
 *  The number of OFDM subbands to be used will be implicitly defined by the SpectrumModel
 *  of the transmit power spectral density.
 *
 *  TODO: masking subbands when not all of them are used (e.g. because of using pilot tones, bad snr)
 *
 * 	The link layer performance between PHY devices is also depends on the Modulation
 * 	and Coding Scheme and the error model used to abstract from real physical devices.
 */
class PLC_HalfDuplexOfdmPhy : public PLC_Phy
{
public:

	/**
	 * Three states of the half duplex phy
	 */
	enum State
	{
		IDLE,
		TX,
		RX,
	};

	static TypeId GetTypeId (void);

	/**
	 * Constructor
	 */
	PLC_HalfDuplexOfdmPhy ();
	virtual ~PLC_HalfDuplexOfdmPhy () = 0;

	static void SetGuardIntervalDuration (Time duration);;
	static Time GetGuardIntervalDuration (void);

	/**
	 * Creates rx and tx interface, respectively, on outlet
	 *
	 * If an impedance has been assigned previously to outlet, the value will be
	 * treated as shunt impedance to the device.
	 * By initializing txPsd the SpectrumModel and the OFDM subbands are defined
	 *
	 * @param outlet
	 * @param txPsd
	 */
	void CreateInterfaces (Ptr<PLC_Outlet> outlet, Ptr<SpectrumValue> txPsd, Ptr<PLC_Impedance> rxImpedance = 0, Ptr<PLC_Impedance> txImpedance = 0);

	/**
	 * @return Outlet the device is attached to
	 */
	Ptr<PLC_Outlet> GetOutlet (void) { return m_outlet; }

	/**
	 * Set the power spectral density to be used for the outgoing waveform
	 * @param txPsd
	 */
	void SetTxPowerSpectralDensity (Ptr<SpectrumValue> txPsd);

	/**
	 * @return PSD used for transmission
	 */
	Ptr<const SpectrumValue> GetTxPowerSpectralDensity (void) { return m_txPsd; }

	/**
	 * @return TX interface of the PHY
	 */
	Ptr<PLC_TxInterface> GetTxInterface (void);

	/**
	 * @return RX interface of the PHY
	 */
	Ptr<PLC_RxInterface> GetRxInterface (void);

	/**
	 * Set shunt impedance to the node the device is located on
	 * @param shuntImpedance
	 */
	void SetShuntImpedance (Ptr<PLC_Impedance> shuntImpedance);

	/**
	 * Set access impedance for the device being in receive state
	 * @param rxImpedance
	 */
	void SetRxImpedance (Ptr<PLC_Impedance> rxImpedance);

	/**
	 * Set access impedance for the device being in transmit state
	 * @param rxImpedance
	 */
	void SetTxImpedance (Ptr<PLC_Impedance> txImpedance);

	/**
	 * @return Shunt impedance of the node the device is located on
	 */
	Ptr<PLC_Impedance> GetShuntImpedance (void) { return m_shuntImpedance; }

	/**
	 * @return Access impedance used while receiving
	 */
	Ptr<PLC_Impedance> GetRxImpedance (void) { return m_rxImpedance; }

	/**
	 * @return Access impedance used while transmitting
	 */
	Ptr<PLC_Impedance> GetTxImpedance (void) { return m_txImpedance; }

	void SetNoiseFloor (Ptr<const SpectrumValue> noiseFloor);

	/**
	 * Clear Channel Assessment request
	 * Typically called by MAC layer
	 */
	void CcaRequest (void);

	/**
	 * Cancel previous CcaRequest
	 */
	void CancelCca (void);

	/**
	 * Clear Channel Assessment listening end
	 */
	void EndCca (void);

	/**
	 * Confirmation callback after Clear Channel Assessment request
	 * This is part of the interconnection between MAC and PHY layer
	 * @param c
	 */
	void SetCcaConfirmCallback (PLC_PhyCcaConfirmCallback c);

	/**
	 * Change the PHY's state to newState
	 * @param newState
	 */
	void ChangeState (State newState);

	/**
	 * Get current state of the PHY
	 * @return Current state
	 */
	State GetState (void);

	/**
	 * @return True if PHY is not IDLE
	 */
	bool IsBusy(void) { return m_state != IDLE; }

protected:
	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual void DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor) = 0;
	virtual PLC_ChannelTransferImpl *DoGetChannelTransferImpl (Ptr<PLC_Phy> rxPhy);

	static Time guard_interval_duration;

	void ComputeEquivalentImpedances (void);
	virtual PLC_PhyCcaResult ClearChannelAssessment (void) = 0;

	Time CalculateTxDuration (size_t nSymbols);

	/**
	 * Switch access impedance of the device according to state
	 * @warning will not change the state of the PHY, but only the impedance value;
	 * for a state change call ChangeState ()
	 * @param state
	 */
	void SwitchImpedance (State state);

	Ptr<PLC_Outlet> 		m_outlet;
	Ptr<SpectrumValue> 		m_txPsd;
	Ptr<PLC_TxInterface> 	m_txInterface;
	Ptr<PLC_RxInterface> 	m_rxInterface;
	Ptr<PLC_Impedance> 		m_shuntImpedance;
	Ptr<PLC_Impedance> 		m_txImpedance;
	Ptr<PLC_Impedance> 		m_rxImpedance;
	Ptr<PLC_Impedance> 		m_eqRxImpedance;
	Ptr<PLC_Impedance> 		m_eqTxImpedance;

	size_t		 			m_numSubcarriers;

	uint32_t m_locked_txId;
	Ptr<Packet> m_incoming_packet;

	// The PHY has to be aware of all receive PSDs to
	// update the interference model when a signal changes
	std::map<uint32_t, Ptr<const SpectrumValue> > m_rxNoisePsdMap;

	EventId m_ccaEndEvent;
	PLC_PhyCcaConfirmCallback m_ccaConfirmCallback;

	State m_state;
	TracedCallback<Time, State> m_PhyStateLogger;
};

std::ostream& operator<<(std::ostream& os, PLC_HalfDuplexOfdmPhy::State state);

/**
 * \class PLC_ErrorRatePhy
 *
 * Simple implementation of a half duplex phy using the error rate model
 */
class PLC_ErrorRatePhy : public PLC_HalfDuplexOfdmPhy
{
public:
	static TypeId GetTypeId (void);

	PLC_ErrorRatePhy();

	/**
	 * Define the Modulation and Coding Scheme to be used
	 * @param mcs
	 */
	virtual void SetModulationAndCodingScheme(ModulationAndCodingType mcs);
	ModulationAndCodingType GetModulationAndCodingScheme(void) { return m_mcs; }

	virtual void PreambleDetectionSuccessful (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void EndRx(uint32_t txId);

private:
	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual void DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor);
	virtual bool DoStartTx (Ptr<Packet> p);
	virtual void DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> newRxPsd);

	PLC_PhyCcaResult ClearChannelAssessment (void);
	Time CalculateTxDuration(Ptr<const Packet> p);

	ModulationAndCodingType m_mcs;
	Ptr<const Packet> m_rxPacket;
	Ptr<PLC_ErrorRateModel> m_error_rate_model;
};

/**
 * \class PLC_InformationRatePhy
 *
 * Simple implementation of a half duplex phy using the information rate model
 */
class PLC_InformationRatePhy : public PLC_HalfDuplexOfdmPhy
{
public:
	static TypeId GetTypeId (void);

	PLC_InformationRatePhy (void);

	/**
	 * A second fixed rate modulation and coding scheme has to be defined for the
	 * transmission of control frames and frame header.
	 * Only the payload of data frames can be encoded rateless.
	 * The robustness of control frame and frame header transmission
	 * can be increased by choosing a lower mcs
	 */
	void SetHeaderModulationAndCodingScheme(ModulationAndCodingType mcs);
	ModulationAndCodingType GetHeaderModulationAndCodingScheme(void);

	void SetPayloadModulationAndCodingScheme(ModulationAndCodingType mcs);
	ModulationAndCodingType GetPayloadModulationAndCodingScheme(void);

	/**
	 * Define number of modulation symbols needed to map one code block
	 * @param spb
	 */
	static void SetOfdmSymbolsPerCodeBlock (size_t spb);

	/**
	 * @return Modulation symbols needed to map one code block
	 */
	size_t GetOfdmSymbolsPerCodeBlock (void);

	/**
	 * Define the minimal overhead induced by rateless encoding.
	 * default: 0.2
	 *
	 * TODO: non static estimation with respect to message length
	 * and claimed decoding propability
	 *
	 * @param overhead (1 = 100%)
	 */
	static void SetRatelessCodingOverhead (double overhead);
	static double GetRatelessCodingOverhead (void) { return rateless_coding_overhead; }

	virtual void EndRxHeader(Ptr<SpectrumValue>& rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo);
	void ReceptionFailure(void);

	void SendFrame (Ptr<Packet> p, Ptr<PLC_TrxMetaInfo> metaInfo);
	virtual bool SendRedundancy (void);

	virtual void PreambleDetectionSuccessful (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

protected:
	static size_t modulation_symbols_per_code_block;
	static double rateless_coding_overhead;

	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual void DoSetNoiseFloor (Ptr<const SpectrumValue> noiseFloor);
	virtual bool DoStartTx (Ptr<Packet> p);
	virtual void DoStartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void DoUpdateRxPsd (uint32_t txId, Ptr<SpectrumValue> newRxPsd);

	virtual void StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void NotifySuccessfulReception (void);

	Ptr<Packet> CreateEncodedPacket (Ptr<PLC_TrxMetaInfo> metaInfo);
	Ptr<Packet> CreateFixedRateEncodedFrame (Ptr<PLC_TrxMetaInfo> metaInfo);
	Ptr<Packet> CreateRatelessEncodedFrame (Ptr<PLC_TrxMetaInfo> metaInfo);

	PLC_PhyCcaResult ClearChannelAssessment (void);

	size_t RequiredChunks (size_t num_blocks);
	size_t ChunksInByte (size_t num_chunks, size_t raw_bits_per_symbol);

	Ptr<PLC_InformationRateModel> m_information_rate_model;

	ModulationAndCodingType m_header_mcs;
	ModulationAndCodingType m_payload_mcs;
};

/**
 *
 */
class PLC_ChaseCombiningPhy : public PLC_InformationRatePhy
{
public:
	static TypeId GetTypeId (void);

	PLC_ChaseCombiningPhy(void);

	void UpdateSinrBase (Ptr<const SpectrumValue> newSinrBase);
	void TraceSinr(Time t, Ptr<const SpectrumValue> sinr);

	virtual bool SendRedundancy (void);

protected:
	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual bool DoStartTx (Ptr<Packet> p);

	virtual void StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void NotifySuccessfulReception (void);

private:
	Ptr<Packet> m_txPacket;
	Ptr<PLC_TrxMetaInfo> m_txMetaInfo;

	Time m_rxStartTime;
	Ptr<const Packet> m_rxPacketRef;

	PLC_SinrTrace m_sinrBaseTrace;
};

/**
 *
 */
class PLC_IncrementalRedundancyPhy : public PLC_InformationRatePhy
{
public:
	static TypeId GetTypeId (void);

	PLC_IncrementalRedundancyPhy (void);

	static void SetReceptionFailureTimeout (Time timeout);
	static Time GetReceptionFailureTimeout (void);

	void SetRedundancyFrameChunks (size_t chunks) { m_redundancy_chunks = chunks; }
	size_t GetRedundancyFrameChunks (void) { return m_redundancy_chunks; }

	virtual void EndRxHeader(Ptr<SpectrumValue>& rxPsd, Ptr<const PLC_TrxMetaInfo> metaInfo);
	virtual void EndRxPayload(Ptr<const PLC_TrxMetaInfo> metaInfo);

	void ReceptionFailureTimeout (void);

	virtual bool SendRedundancy (void);

protected:
	virtual void DoStart (void);
	virtual void DoDispose (void);
	virtual bool DoStartTx (Ptr<Packet> p);

	virtual void StartReception (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

private:
	static Time reception_failure_timeout;

	Ptr<Packet> CreateRedundancyFrame (size_t chunks, Ptr<PLC_TrxMetaInfo> metaInfo);

	bool m_awaiting_redundancy;
	Ptr<const Packet> m_uncoded_msg;
	size_t m_remaining_bits;
	size_t m_redundancy_chunks;

	EventId m_receptionFailureTimeoutEvent;
};

}

#endif /* PLC_PHY_H_ */
