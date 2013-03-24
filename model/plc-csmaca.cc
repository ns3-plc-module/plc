/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 The Boeing Company
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
 * Author: kwong yin <kwong-sang.yin@boeing.com>
 */

#include "ns3/simulator.h"
#include "ns3/plc-csmaca.h"
#include "ns3/plc-mac.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("PLC_CsmaCa");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (PLC_CsmaCa);

#ifndef MAX
#define MAX(x,y)        (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y)        (((x) < (y)) ? (x) : (y))
#endif

TypeId
PLC_CsmaCa::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_CsmaCa")
    .SetParent<Object> ()
    .AddConstructor<PLC_CsmaCa> ()
  ;
  return tid;
}

PLC_CsmaCa::PLC_CsmaCa ()
{
  // TODO-- make these into ns-3 attributes

  m_isSlotted = false;
  m_macMinBE = 10;
  m_macMaxBE = 5;
  m_macMaxCSMABackoffs = 4;
  m_aUnitBackoffPeriod = 1; //20; //20 symbols
}

PLC_CsmaCa::~PLC_CsmaCa ()
{
}

void
PLC_CsmaCa::DoDispose ()
{
  m_csmaCaMacCallback = MakeNullCallback< void, PLC_CsmaCaState> ();
}

void
PLC_CsmaCa::setSlottedCsmaCa (void)
{
  NS_LOG_FUNCTION (this);
  m_isSlotted = true;
}

void
PLC_CsmaCa::setUnSlottedCsmaCa (void)
{
  NS_LOG_FUNCTION (this);
  m_isSlotted = false;
}

bool
PLC_CsmaCa::isSlottedCsmaCa (void) const
{
  NS_LOG_FUNCTION (this);
  return (m_isSlotted);
}

bool
PLC_CsmaCa::isUnSlottedCsmaCa (void) const
{
  NS_LOG_FUNCTION (this);
  return (!m_isSlotted);
}

void
PLC_CsmaCa::setMacMinBE (uint8_t macMinBE)
{
  NS_LOG_FUNCTION (this << macMinBE);
  m_macMinBE = macMinBE;
}

uint8_t
PLC_CsmaCa::getMacMinBE (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMinBE;
}

void
PLC_CsmaCa::setMacMaxBE (uint8_t macMaxBE)
{
  NS_LOG_FUNCTION (this << macMaxBE);
  m_macMinBE = macMaxBE;
}

uint8_t
PLC_CsmaCa::getMacMaxBE (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMaxBE;
}

void
PLC_CsmaCa::setmacMaxCSMABackoffs (uint8_t macMaxCSMABackoffs)
{
  NS_LOG_FUNCTION (this << macMaxCSMABackoffs);
  m_macMaxCSMABackoffs = macMaxCSMABackoffs;
}

uint8_t
PLC_CsmaCa::getmacMaxCSMABackoffs (void) const
{
  NS_LOG_FUNCTION (this);
  return m_macMaxCSMABackoffs;
}

void
PLC_CsmaCa::setUnitBackoffPeriod (uint64_t unitBackoffPeriod)
{
  NS_LOG_FUNCTION (this << unitBackoffPeriod);
  m_aUnitBackoffPeriod = unitBackoffPeriod;
}

uint64_t
PLC_CsmaCa::getUnitBackoffPeriod (void) const
{
  NS_LOG_FUNCTION (this);
  return m_aUnitBackoffPeriod;
}

//TODO:
uint64_t
PLC_CsmaCa::getTimeToNextSlot (void) const
{
  NS_LOG_FUNCTION (this);
  uint64_t diffT = 0;


  return(diffT);

}

void
PLC_CsmaCa::Start ()

{
  NS_LOG_FUNCTION (this);
  uint64_t backoffBoundary = 0;
  m_NB = 0;
  if (isSlottedCsmaCa ())
    {
      m_CW = 2;
      if (m_BLE)
        {
          m_BE = MIN (2, m_macMinBE);
        }
      else
        {
          m_BE = m_macMinBE;
        }
      //TODO: for slotted, locate backoff period boundary. i.e. delay to the next slot boundary
      backoffBoundary = getTimeToNextSlot ();
      m_backoffEndEvent = Simulator::Schedule (Seconds (backoffBoundary),&PLC_CsmaCa::RandomBackoffDelay,this);
    }
  else
    {
      m_BE = m_macMinBE;
      m_backoffEndEvent = Simulator::ScheduleNow (&PLC_CsmaCa::RandomBackoffDelay,this);
    }

  	m_active = true;

  /*
  *  TODO: If using Backoff.cc (will need to modify Backoff::GetBackoffTime)
  *        Backoff.m_minSlots = 0;
  *        Backoff.m_ceiling = m_BE;
  *        Backoff.ResetBackoffTime(); //m_NB is same as m_numBackoffRetries in Backoff.h
  *        Backoff.m_maxRetries = macMaxCSMABackoffs;
  *        Backoff.m_slotTime = m_backoffPeriod;
  */
}

void
PLC_CsmaCa::Cancel ()
{
	if (!m_csmaCaCcaCancelCallback.IsNull())
	{
		m_csmaCaCcaCancelCallback();
	}
	m_requestCCAEvent.Cancel();
	m_backoffEndEvent.Cancel();
	m_canProceedEvent.Cancel();

	m_active = false;
}


/*
 * Delay for backoff period in the range 0 to 2^BE -1 units
 * TODO: If using Backoff.cc (Backoff::GetBackoffTime) will need to be slightly modified
 */
void
PLC_CsmaCa::RandomBackoffDelay ()
{
  NS_LOG_FUNCTION (this);

//  SeedManager::SetSeed (100);
  UniformVariable uniformVar;
  uint64_t upperBound = (uint64_t) pow (2, m_BE) - 1;
  uint64_t backoffPeriod;
  Time randomBackoff;

  uniformVar = UniformVariable (0, upperBound);
  backoffPeriod = (uint64_t)uniformVar.GetValue (); //num backoff periods
  NS_LOG_LOGIC("Backoff periods: " << backoffPeriod);

  randomBackoff = MicroSeconds (backoffPeriod * getUnitBackoffPeriod () * PLC_Phy::GetSymbolDuration().GetMicroSeconds());

  if (isUnSlottedCsmaCa ())
    {
      NS_LOG_LOGIC ("Unslotted:  requesting CCA after backoff of " << randomBackoff.GetMicroSeconds () << " us");
      m_requestCCAEvent = Simulator::Schedule (randomBackoff,&PLC_CsmaCa::RequestCCA,this);
    }
  else
    {
      NS_LOG_LOGIC ("Slotted:  proceeding after backoff of " << randomBackoff.GetMicroSeconds () << " us");
      m_canProceedEvent = Simulator::Schedule (randomBackoff,&PLC_CsmaCa::CanProceed,this);
    }
}

// TODO : Determine if transmission can be completed before end of CAP for the slotted csmaca
//        If not delay to the next CAP
void
PLC_CsmaCa::CanProceed ()
{
  NS_LOG_FUNCTION (this);
  uint64_t backoffBoundary = 0;
  uint8_t nextCap = 0;
  bool canProceed = true;

  if (m_BLE)
    {
    }
  else
    {
    }

  if (canProceed)
    {
      // TODO: For slotted, Perform CCA on backoff period boundary i.e. delay to next slot boundary
      backoffBoundary = getTimeToNextSlot ();
      Simulator::Schedule (Seconds (backoffBoundary),&PLC_CsmaCa::RequestCCA,this);
    }
  else
    {
      Simulator::Schedule (Seconds (nextCap),&PLC_CsmaCa::RandomBackoffDelay,this);
    }
}

void
PLC_CsmaCa::RequestCCA ()
{
  NS_LOG_FUNCTION (this);

  if (!m_csmaCaCcaRequestCallback.IsNull())
  {
	  m_csmaCaCcaRequestCallback();
  }
}

/*
 * This function is called when the phy calls back after completing a PlmeCcaRequest
 */
void
PLC_CsmaCa::CcaConfirm (PLC_PhyCcaResult status)
{
  NS_LOG_FUNCTION (this << status);

  if (status == CHANNEL_CLEAR)
    {
	  m_active = false;

      if (isSlottedCsmaCa ())
        {
          m_CW--;
          if (m_CW == 0)
            {
              // inform MAC channel is idle
              if (!m_csmaCaMacCallback.IsNull ())
                {
                  NS_LOG_LOGIC ("Notifying MAC of idle channel");
                  m_csmaCaMacCallback (CHANNEL_IDLE);
                }
            }
          else
            {
              NS_LOG_LOGIC ("Perform CCA again, m_CW = " << m_CW);
              Simulator::ScheduleNow (&PLC_CsmaCa::RequestCCA,this); // Perform CCA again
            }
        }
      else
        {
          // inform MAC, channel is idle
          if (!m_csmaCaMacCallback.IsNull ())
            {
              NS_LOG_LOGIC ("Notifying MAC of idle channel");
              m_csmaCaMacCallback (CHANNEL_IDLE);
            }
        }
    }
  else
    {
      if (isSlottedCsmaCa ())
        {
          m_CW = 2;
        }
      m_BE = MIN (m_BE + 1, m_macMaxBE);
      m_NB++;
      if (m_NB > m_macMaxCSMABackoffs)
        {
          // no channel found so cannot send pkt
          NS_LOG_DEBUG ("Channel access failure");
          if (!m_csmaCaMacCallback.IsNull ())
            {
              NS_LOG_LOGIC ("Notifying MAC of Channel access failure");
              m_csmaCaMacCallback (CHANNEL_ACCESS_FAILURE);
            }
          return;
        }
      else
        {
          NS_LOG_DEBUG ("Perform another backoff; m_NB = " << static_cast<uint16_t> (m_NB));
          Simulator::ScheduleNow (&PLC_CsmaCa::RandomBackoffDelay,this); //Perform another backoff (step 2)
        }
    }
}

void
PLC_CsmaCa::SetCcaRequestCallback (PLC_CsmaCaCcaRequestCallback c)
{
	NS_LOG_FUNCTION (this);
	m_csmaCaCcaRequestCallback = c;
}

void
PLC_CsmaCa::SetCcaCancelCallback (PLC_CsmaCaCcaCancelCallback c)
{
	NS_LOG_FUNCTION (this);
	m_csmaCaCcaCancelCallback = c;
}

void
PLC_CsmaCa::SetCsmaCaMacCallback (PLC_CsmaCaMacCallback c)
{
  NS_LOG_FUNCTION (this);
  m_csmaCaMacCallback = c;
}

} //namespace ns3
