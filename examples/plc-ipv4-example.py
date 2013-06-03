# -*- Mode:Python; -*-
# /*
#  * Copyright (c) 2013 University of Britisch Columbia, Vancouver, Canada
#  *
#  * This program is free software; you can redistribute it and/or modify
#  * it under the terms of the GNU General Public License version 2 as
#  * published by the Free Software Foundation;
#  *
#  * This program is distributed in the hope that it will be useful,
#  * but WITHOUT ANY WARRANTY; without even the implied warranty of
#  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  * GNU General Public License for more details.
#  *
#  * You should have received a copy of the GNU General Public License
#  * along with this program; if not, write to the Free Software
#  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#  *
#  * Authors: Alexander Schloegl <alexander.schloegl@gmx.de>
#  */
# 
# plc-ipv4-example.py

import ns.core
import ns.network
import ns.internet
import ns.spectrum
import ns.plc

def sendPacket (socket,packet):
    socket.Send(packet)

def main(argv):
    ## Enable logging output of MAC layer
    ns.core.LogComponentEnableAll(ns.core.LOG_PREFIX_TIME)
    ns.core.LogComponentEnableAll(ns.core.LOG_PREFIX_NODE)
    ns.core.LogComponentEnable('PLC_Mac', ns.core.LOG_INFO)

    ## Enable packet printing
    ns.network.Packet.EnablePrinting()

    ## Define spectrum model
    sm = ns.plc.PLC_SpectrumModelHelper().GetSpectrumModel(1e6,2e6,100)

    ## Define transmit power spectral density
    txPsd = ns.spectrum.SpectrumValue(sm)
    txPsd += 1e-8 # -50 dBm/Hz

    ## Create cable type
    cable = ns.plc.PLC_NAYY150SE_Cable(sm)

    ## Create nodes
    n1 = ns.plc.PLC_Node()
    n2 = ns.plc.PLC_Node()
    n1.SetPosition(0,0,0)
    n2.SetPosition(500,0,0)
    n1.SetName('A')
    n2.SetName('B')
    nodes = [n1,n2]

    ## Link nodes
    ns.plc.PLC_Line(cable,n1,n2)

    ## Setup channel
    channelHelper = ns.plc.PLC_ChannelHelper()
    channelHelper.Install(nodes)
    channel = channelHelper.GetChannel()

    ## Create net devices
    deviceHelper = ns.plc.PLC_NetDeviceHelper(sm, txPsd, nodes)
    deviceHelper.DefinePhyType(ns.core.TypeId.LookupByName ('ns3::PLC_InformationRatePhy'))
    deviceHelper.DefineMacType(ns.core.TypeId.LookupByName ('ns3::PLC_ArqMac'))
    deviceHelper.SetHeaderModulationAndCodingScheme(ns.plc.ModulationAndCodingScheme(ns.plc.BPSK_1_4,0))
    deviceHelper.SetPayloadModulationAndCodingScheme(ns.plc.ModulationAndCodingScheme(ns.plc.BPSK_1_2,0))
    deviceHelper.Setup()

    ## Calculate channels
    channel.InitTransmissionChannels()
    channel.CalcTransmissionChannels()

    ## Get ns-3 nodes 
    n = deviceHelper.GetNS3Nodes()

    ## Install ipv4 stack on nodes
    inetHelper = ns.internet.InternetStackHelper()
    inetHelper.SetIpv4StackInstall(1)
    inetHelper.Install(n)

    ## Get net devices
    d = deviceHelper.GetNetDevices()
 
    ## Assign IP addresses
    ipv4AddrHelper = ns.internet.Ipv4AddressHelper()
    ipv4AddrHelper.SetBase(ns.network.Ipv4Address('10.10.0.0'), ns.network.Ipv4Mask('255.255.255.0'))
    ifCntr = ipv4AddrHelper.Assign(d) # Ipv4InterfaceContainer

    ## Create UDP sockets
    socketTid = ns.core.TypeId.LookupByName ('ns3::UdpSocketFactory')
    source = ns.network.Socket.CreateSocket (n.Get(0), socketTid)
    sink = ns.network.Socket.CreateSocket (n.Get(1), socketTid)

    ## Setup sockets
    local = ns.network.InetSocketAddress(ns.network.Ipv4Address.GetAny(), 4711)
    remote = ns.network.InetSocketAddress(ifCntr.GetAddress(1), 4711)
    sink.Bind(local)
    sink.Listen()
    source.Connect(remote)

    ## Create packet
    packet = ns.network.Packet(128)

    ## Schedule transmission
    ns.core.Simulator.Schedule(ns.core.Seconds(0), sendPacket, source, packet)

    ## Start simulation
    ns.core.Simulator.Run()

    ## Cleanup simulation
    ns.core.Simulator.Destroy()

if __name__ == '__main__':
    import sys
    main(sys.argv)
