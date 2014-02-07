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

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

#include <ns3/core-module.h>
#include <ns3/nstime.h>
#include <ns3/simulator.h>
#include <ns3/output-stream-wrapper.h>
#include "ns3/plc.h"

using namespace ns3;

int main (int argc, char *argv[])
{
	// Define spectrum model
    PLC_SpectrumModelHelper smHelper;
    Ptr<const SpectrumModel> sm, sm1;
    sm = smHelper.GetSpectrumModel(0, 10e6, 100);

    // Create cable types
	Ptr<PLC_Cable> cable = CreateObject<PLC_NAYY150SE_Cable> (sm);

	// Create nodes
	Ptr<PLC_Node> n1 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n2 = CreateObject<PLC_Node> ();
	n1->SetPosition(0,0,0);
	n2->SetPosition(1000,0,0);

	PLC_NodeList nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);

	// Link nodes
	CreateObject<PLC_Line> (cable, n1, n2);

	// Set up channel
	PLC_ChannelHelper channelHelper(sm);
	channelHelper.Install(nodes);
	Ptr<PLC_Channel> channel = channelHelper.GetChannel();

	// Create interfaces (usually done by the device helper)
	Ptr<PLC_TxInterface> txIf = CreateObject<PLC_TxInterface> (n1, sm);
	Ptr<PLC_RxInterface> rxIf = CreateObject<PLC_RxInterface> (n2, sm);

	// Add interfaces to the channel (usually done by the device helper)
	channel->AddTxInterface(txIf);
	channel->AddRxInterface(rxIf);

	channel->InitTransmissionChannels();
	channel->CalcTransmissionChannels();

	// Define transmit power spectral density
    Ptr<SpectrumValue> txPsd = Create<SpectrumValue> (sm);
    (*txPsd) = 1e-8; // -50dBm/Hz

    // The receive power spectral density computation is done by the channel
    // transfer implementation from TX interface to RX interface
	Ptr<PLC_ChannelTransferImpl> chImpl = txIf->GetChannelTransferImpl(PeekPointer(rxIf));
	NS_ASSERT(chImpl);
	Ptr<SpectrumValue> rxPsd = chImpl->CalculateRxPowerSpectralDensity(txPsd);

	// SINR is calculated by PLC_Interference (member of PLC_Phy)
	//PLC_NoiseSource N1;
	//N1.SetNoisePsd(sm1);
	PLC_Interference interference;
	//sm1 = smHelper.GetSpectrumModel(0, 10e6, 100);
	//PLC_ColoredNoiseFloor nf;
	//nf.PLC_ColoredNoiseFloor(2,3,4,sm1);
	Ptr<SpectrumValue> noiseFloor= Create<SpectrumValue> (sm);
	(*noiseFloor) = 1e-9;
	interference.SetNoiseFloor(noiseFloor);
	interference.InitializeRx(rxPsd);

	Ptr<const SpectrumValue> sinr = interference.GetSinr();

	NS_LOG_UNCOND("Transmit power spectral density:\n" << *txPsd << "\n");
	NS_LOG_UNCOND("Receive power spectral density:\n" << *rxPsd << "\n");
	NS_LOG_UNCOND("Noise power spectral density:\n" << *noiseFloor << "\n");
	NS_LOG_UNCOND("Signal to interference and noise ratio:\n" << *sinr);

	return EXIT_SUCCESS;
}
