/*
 * plc-noise.cc
 *
 *  Created on: 2012-03-21
 *      Author: alexs
 */

#include <math.h>
#include <ns3/log.h>
#include <ns3/type-id.h>
#include <ns3/random-variable.h>
#include <ns3/simulator.h>
#include <ns3/plc-defs.h>
#include <ns3/plc-interface.h>
#include "plc-noise.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Noise");
NS_OBJECT_ENSURE_REGISTERED (PLC_NoiseSource);
NS_OBJECT_ENSURE_REGISTERED (PLC_StaticNoiseSource);
NS_OBJECT_ENSURE_REGISTERED (PLC_ImpulseNoiseSource);
NS_OBJECT_ENSURE_REGISTERED (PLC_ImpulsiveNoiseSource);

/////////////////////////////// PLC_ColoredNoiseFloor ////////////////////////////////////////////

PLC_ColoredNoiseFloor::PLC_ColoredNoiseFloor (double a, double b, double c, Ptr<const SpectrumModel> sm)
{
	this->m_noisePsd = Create<SpectrumValue> (sm);

	Values::iterator v_it;
	Bands::const_iterator b_it;

	v_it = this->m_noisePsd->ValuesBegin ();
	for  (b_it = this->m_noisePsd->ConstBandsBegin ();
		 b_it != this->m_noisePsd->ConstBandsEnd ();
		 b_it++)
	{
		// mW/Hz
		double val = pow (10,  (a + b*pow (fabs (b_it->fc * 1e-6), c))/10);

		// noise floor threshold: -90dBm/Hz
		if  (val < 1e-12)
			*v_it = val;
		else
			*v_it = 1e-12;

		++v_it;
	}
}

Ptr<SpectrumValue> PLC_ColoredNoiseFloor::GetNoisePsd (void)
{
	return this->m_noisePsd;
}

/////////////////////////////// PLC_NoiseSource ////////////////////////////////////////////

TypeId
PLC_NoiseSource::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_NoiseSource")
    		.SetParent<Object>  ()
    	    ;
	return tid;
}

PLC_NoiseSource::PLC_NoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd, NoiseSourceType type)
	: m_noise_source_type (type), m_src_node (src_node), m_noisePsd (noisePsd), m_is_enabled (false), m_is_initialized(false)
{
	this->m_channel = src_node->GetGraph ()->GetChannel ();
}

PLC_NoiseSource::~PLC_NoiseSource (void) {}

void PLC_NoiseSource::Init (void)
{
	m_txInterface = CreateObject<PLC_TxInterface> (m_src_node, m_noisePsd->GetSpectrumModel ());
	this->m_noise_srcId = this->m_channel->AddTxInterface (m_txInterface);
	m_txInterface->SetIdx (m_noise_srcId);
	NS_LOG_DEBUG ("Noise TxIfIdx: " << m_noise_srcId);
	m_is_initialized = true;
}

void PLC_NoiseSource::Enable (void)
{
	this->m_is_enabled = true;
}

void PLC_NoiseSource::Disable (void)
{
	this->m_is_enabled = false;
}

bool PLC_NoiseSource::IsEnabled (void)
{
	return this->m_is_enabled;
}

PLC_NoiseSource::NoiseSourceType PLC_NoiseSource::GetNoiseSourceType (void)
{
	return this->m_noise_source_type;
}

/////////////////////////////// PLC_StaticNoiseSource ////////////////////////////////////////////

TypeId
PLC_StaticNoiseSource::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_StaticNoiseSource")
    		.SetParent<PLC_NoiseSource>  ()
    	    ;
	return tid;
}

PLC_StaticNoiseSource::PLC_StaticNoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd)
	: PLC_NoiseSource (src_node, noisePsd, PLC_NoiseSource::STATIC), m_noisePsd (noisePsd)
{
}

void PLC_StaticNoiseSource::Start (Time duration)
{
	PLC_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_is_initialized, "Noise Source not initialized! Call Init() before starting noise source!");
	PLC_NoiseSource::Enable ();
	m_txInterface->StartTx (NULL, this->m_noisePsd, duration, NULL);
}

/////////////////////////////// PLC_TimeVariantNoiseSource ////////////////////////////////////////////

TypeId
PLC_ImpulseNoiseSource::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_ImpulseNoiseSource")
    		.SetParent<PLC_NoiseSource>  ()
    	    ;
	return tid;
}

PLC_ImpulseNoiseSource::PLC_ImpulseNoiseSource (void)
{
	PLC_LOG_FUNCTION (this);
	m_p = 0;
}


PLC_ImpulseNoiseSource::PLC_ImpulseNoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd, double p)
	: PLC_NoiseSource (src_node, noisePsd, PLC_NoiseSource::IMPULSIVE)
{
	NS_LOG_FUNCTION(this);
	m_p = p;
}

void
PLC_ImpulseNoiseSource::SetProbability (double p)
{
	NS_LOG_FUNCTION(this << p);
	this->m_p = p;
}

double
PLC_ImpulseNoiseSource::GetProbability(void)
{
	NS_LOG_FUNCTION(this);
	return this->m_p;
}

TypeId
PLC_ImpulsiveNoiseSource::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_ImpulsiveNoiseSource")
    		.SetParent<PLC_NoiseSource>  ()
    	    ;
	return tid;
}

PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource ()
{
	PLC_LOG_FUNCTION (this);
	this->m_pulse_len = new UniformVariable (0, MAX_PULSE_NOISE_DURATION);
	this->m_pulse_gap = new UniformVariable (0, MAX_PULSE_GAP_DURATION);
}


PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd)
	: PLC_NoiseSource (src_node, noisePsd, PLC_NoiseSource::IMPULSIVE) //, m_noisePsd (noisePsd)
{
	PLC_LOG_FUNCTION (this);
	this->m_pulse_len = new UniformVariable (0, MAX_PULSE_NOISE_DURATION);
	this->m_pulse_gap = new UniformVariable (0, MAX_PULSE_GAP_DURATION);
}

PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource (Ptr<PLC_Node> src_node, Ptr<SpectrumValue> noisePsd, RandomVariable *pulse_len_gen, RandomVariable *pulse_gap_gen)
	: PLC_NoiseSource (src_node, noisePsd, PLC_NoiseSource::IMPULSIVE)/*, m_noisePsd (noisePsd)*/, m_pulse_len (pulse_len_gen), m_pulse_gap (pulse_gap_gen)
{
	PLC_LOG_FUNCTION (this);
}

void PLC_ImpulsiveNoiseSource::Enable (void)
{
	PLC_NoiseSource::Enable ();
	Time start = Seconds (this->m_pulse_gap->GetValue ());
	Simulator::Schedule (start, &PLC_ImpulsiveNoiseSource::PulseStart, this);
}

void PLC_ImpulsiveNoiseSource::PulseStart (void)
{
	PLC_LOG_FUNCTION (this);
	if  (IsEnabled ()) {
		Time duration = Seconds (this->m_pulse_len->GetValue ());
		m_txInterface->StartTx (NULL, this->m_noisePsd, duration, NULL);
		Simulator::Schedule (duration, &PLC_ImpulsiveNoiseSource::PulseEnd, this);
	}
}

void PLC_ImpulsiveNoiseSource::PulseEnd (void)
{
	PLC_LOG_FUNCTION (this);
	if  (IsEnabled ()) {
		Time pause = Seconds (this->m_pulse_gap->GetValue ());
		Simulator::Schedule (pause, &PLC_ImpulsiveNoiseSource::PulseStart, this);
	}
}

}

