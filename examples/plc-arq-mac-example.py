# -*- Mode:Python; -*-
# /*
#  * Copyright (c) 2010 INRIA
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

# Python version of plc-mac-example.cc

import ns.plc
import ns.core
import ns.spectrum
import ns.network

def sendPacket(mac, p, dst):
    mac.Send(p,dst)

def receivedACK():
    print '*** ACK received ***'

def main(dummy_argv):

    ## Enable logging  
    ns.core.LogComponentEnableAll(ns.core.LOG_PREFIX_TIME)
    ns.core.LogComponentEnable('PLC_Mac', ns.core.LOG_LEVEL_FUNCTION)

    ## Enable packet printing
    ns.network.Packet.EnablePrinting()

    ## Define spectrum model
    sm = ns.plc.PLC_SpectrumModelHelper().GetSpectrumModel(0,10e6,100)

    ## Define transmit power spectral density
    txPsd = ns.spectrum.SpectrumValue(sm)
    txPsd += 1e-8

    ## Create cable type
    cable = ns.plc.PLC_NAYY50SE_Cable(sm)

    ## Create nodes
    n1 = ns.plc.PLC_Node()
    n2 = ns.plc.PLC_Node()
    n1.SetPosition(0,0,0)
    n2.SetPosition(1000,0,0)
    n1.SetName('Node1')
    n2.SetName('Node2')
    nodes = [n1,n2]

    ## Link nodes
    ns.plc.PLC_Line(cable,n1,n2)

    ## Setup channel
    channelHelper = ns.plc.PLC_ChannelHelper()
    channelHelper.Install(nodes)
    channel = channelHelper.GetChannel()

    ## Create outlets
    o1 = ns.plc.PLC_Outlet(n1)
    o2 = ns.plc.PLC_Outlet(n2)

    ## Create PHYs
    phy1 = ns.plc.PLC_InformationRatePhy()
    phy2 = ns.plc.PLC_InformationRatePhy()
    phy1.CreateInterfaces(o1,txPsd)
    phy2.CreateInterfaces(o2,txPsd)

    ## Set background noise
    noiseFloor = ns.plc.PLC_ColoredNoiseFloor(-140,38.75,-0.72,sm).GetNoisePsd()
    phy1.SetNoiseFloor(noiseFloor)
    phy2.SetNoiseFloor(noiseFloor)

    ## Set modulation and coding scheme
    phy1.SetHeaderModulationAndCodingScheme(ns.plc.BPSK_1_2)
    phy2.SetHeaderModulationAndCodingScheme(ns.plc.BPSK_1_2)
    phy1.SetPayloadModulationAndCodingScheme(ns.plc.BPSK_RATELESS)
    phy2.SetPayloadModulationAndCodingScheme(ns.plc.BPSK_RATELESS)

    ## Aggregate RX-Interfaces to ns3 nodes
    phy1.GetRxInterface().AggregateObject(ns.network.Node())
    phy2.GetRxInterface().AggregateObject(ns.network.Node())

    ## Create MAC layers
    mac1 = ns.plc.PLC_ArqMac()
    mac2 = ns.plc.PLC_ArqMac()
    mac1.SetPhy(phy1)
    mac2.SetPhy(phy2)
    mac1.SetAddress(ns.network.Mac48Address('00:00:00:00:00:01'))
    mac2.SetAddress(ns.network.Mac48Address('00:00:00:00:00:02'))

    ## Set callback function to be called when ACK is received
    mac1.SetMacAcknowledgementCallback(receivedACK)

    ## Calculate channels
    channel.InitTransmissionChannels()
    channel.CalcTransmissionChannels()

    ## Create packet to send
    p = ns.network.Packet(1024)

    ## Schedule transmission of packet p from phy0 to phy1 to begin at 1s simulation time
    ns.core.Simulator.Schedule(ns.core.Seconds(1), sendPacket, mac1, p, ns.network.Mac48Address('00:00:00:00:00:02'))

    ## Start simulation
    ns.core.Simulator.Run()

    ## Cleanup simulation
    ns.core.Simulator.Destroy()

if __name__ == '__main__':
    import sys
    main(sys.argv)
