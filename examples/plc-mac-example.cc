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

void
ReceivedACK(void)
{
	NS_LOG_UNCOND(Simulator::Now() << ": ACK received!");
}

int main (int argc, char *argv[])
{
	// Enable logging
	LogComponentEnableAll(LOG_PREFIX_TIME);
	LogComponentEnable("PLC_Mac", LOG_LEVEL_FUNCTION);

	// Enable packet printing
	Packet::EnablePrinting();

	// Define spectrum model
    PLC_SpectrumModelHelper smHelper;
    Ptr<const SpectrumModel> sm;
    sm = smHelper.GetSpectrumModel(0, 10e6, 100);

	// Define transmit power spectral density
    Ptr<SpectrumValue> txPsd = Create<SpectrumValue> (sm);
    (*txPsd) = 1e-8; // -50dBm/Hz

    // Create cable type
	Ptr<PLC_Cable> cable = CreateObject<PLC_NAYY150SE_Cable> (sm);

	// Create nodes
	Ptr<PLC_Node> n1 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n2 = CreateObject<PLC_Node> ();
	n1->SetPosition(0,0,0);
	n2->SetPosition(1000,0,0);
	n1->SetName("Node1");
	n2->SetName("Node2");

	PLC_NodeList nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);

	// Link nodes
	CreateObject<PLC_Line> (cable, n1, n2);

	// Setup channel
	PLC_ChannelHelper channelHelper(sm);
	channelHelper.Install(nodes);
	Ptr<PLC_Channel> channel = channelHelper.GetChannel();

	// Create outlets
	Ptr<PLC_Outlet> o1 = CreateObject<PLC_Outlet> (n1);
	Ptr<PLC_Outlet> o2 = CreateObject<PLC_Outlet> (n2);

	// Create PHYs
	Ptr<PLC_InformationRatePhy> phy1 = CreateObject<PLC_InformationRatePhy> ();
	Ptr<PLC_InformationRatePhy> phy2 = CreateObject<PLC_InformationRatePhy> ();

	phy1->CreateInterfaces(o1, txPsd);
	phy2->CreateInterfaces(o2, txPsd);

	// Set background noise
    Ptr<SpectrumValue> noiseFloor = CreateWorstCaseBgNoise(sm)->GetNoisePsd();
	phy1->SetNoiseFloor(noiseFloor);
	phy2->SetNoiseFloor(noiseFloor);

	// Set modulation and coding scheme
	phy1->SetHeaderModulationAndCodingScheme(BPSK_1_2);
	phy2->SetHeaderModulationAndCodingScheme(BPSK_1_2);
	phy1->SetPayloadModulationAndCodingScheme(BPSK_RATELESS);
	phy2->SetPayloadModulationAndCodingScheme(BPSK_RATELESS);

    // Aggregate RX-Interfaces to ns3 nodes
    phy1->GetRxInterface()->AggregateObject(CreateObject<Node> ());
    phy2->GetRxInterface()->AggregateObject(CreateObject<Node> ());

    // Create MAC layers
    Ptr<PLC_ArqMac> mac1 = CreateObject<PLC_ArqMac> ();
    Ptr<PLC_ArqMac> mac2 = CreateObject<PLC_ArqMac> ();
    mac1->SetPhy(phy1);
    mac2->SetPhy(phy2);
    mac1->SetAddress(Mac48Address("00:00:00:00:00:01"));
    mac2->SetAddress(Mac48Address("00:00:00:00:00:02"));

    // Set callback function to be called when ACK is received
    mac1->SetMacAcknowledgementCallback(MakeCallback(&ReceivedACK));

    // Calculate channels
	channel->InitTransmissionChannels();
	channel->CalcTransmissionChannels();

	// Create packet to send
	Ptr<Packet> p = Create<Packet> (1024);

	// Schedule transmission of packet p from phy0 to phy1 to begin at 1s simulation time
	Simulator::Schedule(Seconds(1), &PLC_Mac::Send, mac1, p, Mac48Address("00:00:00:00:00:02"));

	// Start simulation
	Simulator::Run();

	// Cleanup simulation
	Simulator::Destroy();

	return EXIT_SUCCESS;
}
