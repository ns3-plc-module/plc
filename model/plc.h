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

/**
 * Common Includes for PLC simulations
 */

#ifndef PLC_H_
#define PLC_H_

// stl includes
#include <iostream>
#include <vector>

// ns-3 includes
#include <ns3/log.h>
#include <ns3/spectrum-value.h>
#include <ns3/spectrum-model.h>

// plc model includes
#include "ns3/plc-defs.h"
#include "ns3/plc-time.h"
#include "ns3/plc-value.h"
#include "ns3/plc-cable.h"
#include "ns3/plc-edge.h"
#include "ns3/plc-node.h"
#include "ns3/plc-graph.h"
#include "ns3/plc-channel.h"
#include "ns3/plc-backbone.h"
#include "ns3/plc-outlet.h"
#include "ns3/plc-noise.h"
#include "ns3/plc-phy.h"
#include "ns3/plc-mac.h"
#include "ns3/plc-net-device.h"

// plc helper includes
#include "ns3/plc-helper.h"
#include "ns3/plc-device-helper.h"
#include "ns3/plc-spectrum-helper.h"

#endif /* PLC_H_ */
