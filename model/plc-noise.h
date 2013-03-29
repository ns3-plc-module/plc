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

#ifndef PLC_NOISE_H_
#define PLC_NOISE_H_

#include <ns3/simple-ref-count.h>
#include <ns3/random-variable.h>
#include <ns3/spectrum-value.h>

#include "plc-time.h"
#include "plc-channel.h"

namespace ns3 {

#define MAX_PULSE_NOISE_DURATION	1
#define MAX_PULSE_GAP_DURATION		2

/**
 *	Helper class for colored noise generation
 *	with a simple three parameter model proposed in:
 *
 *	"On Noise Modeling for Power Line Communications"
 *	by Luca Di Bert, ..., Andrea M. Tonello
 *	2011 IEEE International Symposium on Power Line
 *	Communications and Its Applications
 *
 *	NoisePsd = a + b|f|^c [dBm/Hz]
 *
 *	with f in Mhz
 */
class PLC_ColoredNoiseFloor : public SimpleRefCount<PLC_ColoredNoiseFloor>
{
public:

	PLC_ColoredNoiseFloor(double a, double b, double c, Ptr<const SpectrumModel> sm);

	Ptr<SpectrumValue> GetNoisePsd(void);

protected:
	Ptr<SpectrumValue> m_noisePsd;
};

/**
 *	\class PLC_NoiseSource
 *
 *	@brief Base class for noise source models
 *
 *	The noise sources act as transmitters in the PLC network.
 *	The noise PSD will therefore experience channel distortion
 *	before received by the receivers as interfering signal. Thus a
 *	a more realistic noise environment can be simulated rather
 *	than using a simple AWGN noise model.
 */

/**
 *	\class PLC_NoiseSource
 *
 *	@brief Base class for noise source models
 *
 *	The noise sources act as transmitters in the PLC network.
 *	The noise PSD will therefore experience channel distortion
 *	before received by the receivers as interfering signal. Thus a
 *	a more realistic noise environment can be simulated rather
 *	than using a simple AWGN noise model.
 */
class PLC_NoiseSource : public Object
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Noise source types
	 *
	 * currently only impulsive noise source is implemented
	 */
	enum NoiseSourceType {
		STATIC,
		TIMEVARIANT,
		IMPULSIVE
	};

	PLC_NoiseSource() {}

	/**
	 * Constructor
	 *
	 * @param src_node The source node where the noise source is originated
	 * @param noisePsd The noise power spectral density
	 * @param type noise source type
	 */
	PLC_NoiseSource(Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd, NoiseSourceType type);
	virtual ~PLC_NoiseSource() = 0;

	/**
	 * Set the noise power spectral density
	 * @param psd The noise power spectral density
	 */
	void SetNoisePsd(Ptr<SpectrumValue> psd) { m_noisePsd = psd; }

	/**
	 * @return The used noise power spectral density
	 */
	Ptr<SpectrumValue> GetNoisePsd(void) { return m_noisePsd; }

	/**
	 * Get noise source type
	 * @return The type of this noise source
	 */
	NoiseSourceType GetNoiseSourceType(void);

	/**
	 * Bind the noise source to a specific PLC_Node
	 *
	 * @param node
	 */
	void SetNode(Ptr<PLC_Node> node) { m_src_node = node; }

	/**
	 * @return PLC_Node the noise source is located on
	 */
	Ptr<PLC_Node> GetNode(void) { return m_src_node; }

	/**
	 * Set the channel the noise source is connected to
	 * @param channel PLC_Channel
	 */
	void SetChannel(Ptr<PLC_Channel> channel) { m_channel = channel; }

	/**
	 * @return PLC_Channel the noise source is connected to
	 */
	Ptr<PLC_Channel> GetChannel(void) { return m_channel; }

	/**
	 * Initialize the noise source, i.e. create the transmit interface
	 * on the bounded node
	 *
	 * @warning To be done before calling PLC_Channel::InitTransmissionChannels(),
	 * otherwise the noise source will not be known by the channel
	 */
	void Init(void);

	/**
	 * Enable the noise source
	 */
	virtual void Enable(void);

	/**
	 * Disable the noise source
	 */
	virtual void Disable(void);

	/**
	 * @return True is noise source is enabled
	 */
	bool IsEnabled(void);

protected:
    // pure virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) = 0;

	NoiseSourceType m_noise_source_type;
	uint32_t m_noise_srcId;
	Ptr<PLC_Node> m_src_node;
	Ptr<SpectrumValue> m_noisePsd;
	Ptr<PLC_Channel> m_channel;
	Ptr<PLC_TxInterface> m_txInterface;
	bool m_is_enabled;
	bool m_is_initialized;
};

class PLC_StaticNoiseSource : public PLC_NoiseSource
{
public:
	static TypeId GetTypeId(void);

	PLC_StaticNoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd);

	void Start (Time duration);

protected:
    // dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:
	Ptr<SpectrumValue> m_noisePsd;
};

class PLC_ImpulseNoiseSource : public PLC_NoiseSource
{
public:
	static TypeId GetTypeId(void);

	PLC_ImpulseNoiseSource();
	PLC_ImpulseNoiseSource(Ptr<PLC_Node> m_src_node, Ptr<SpectrumValue> noisePsd, double p);

	void SetProbability(double p);
	double GetProbability(void);

protected:
    // dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:
	double m_p;
};

/**
 * @class PLC_ImpulsiveNoiseSource
 *
 * \brief Model for impulsive noise sources
 *
 * Impulsive noise sources are modelled by a two random processes which provide values \
 * for the durations the noise source being active and the period between the "pulses",
 * i.e. when the noise source is inactive.
 * Of course there are no transient pulses simulated which would have a great influence on
 * the shape of the noise PSD. Instead the propagated noise PSDs will be switched
 * on and of at the receivers interference model.
 */
class PLC_ImpulsiveNoiseSource : public PLC_NoiseSource
{
public:
	static TypeId GetTypeId(void);

	PLC_ImpulsiveNoiseSource();
	PLC_ImpulsiveNoiseSource(Ptr<PLC_Node> m_src_node, Ptr<SpectrumValue> noisePsd);

	/**
	 * @param src_node PLC_Node the noise source is located on
	 * @param noisePsd Power spectral density of the noise's waveform
	 * @param pulselen_gen RandomVariable for the pulse duration generator
	 * @param pulsegap_gen RandomVariable for the silence duration generator
	 */
	PLC_ImpulsiveNoiseSource(Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd, RandomVariable *pulselen_gen, RandomVariable *pulsegap_gen);

	/**
	 * Enable noise source
	 */
	void Enable(void);

	/**
	 * Emit noise psd if source is still enabled
	 *
	 * Scheduled by PulseEnd() with random variable m_pulsegap_gen
	 */
	void PulseStart(void);

	/**
	 * Stop emitting noise psd
	 *
	 * Scheduled in PulseStart with random variable m_pulselen_gen
	 */
	void PulseEnd(void);

protected:
    // dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}

private:
	RandomVariable		*m_pulse_len;
	RandomVariable		*m_pulse_gap;
};

}

#endif /* PLC_NOISE_H_ */











