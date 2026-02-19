/**
 * Auto-generated NS3 Simulation Script
 * This script is standalone and does not require JSON configuration files
 */

#include "ns3/applications-module.h"
#include "ns3/buildings-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "ns3/SniffUtils.h"
#include <boost/interprocess/shared_memory_object.hpp>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("GeneratedSimulation");

int
main(int argc, char* argv[])
{
    NS_LOG_INFO("Starting simulation...");

    // ========= Simulation Parameters =========
    double duration = 10;

    // ========= Building =========
    Ptr<Building> building = CreateObject<Building>();
    building->SetBoundaries(Box(0, 10, 0, 10, 0, 5));
    building->SetBuildingType(Building::Residential);
    building->SetExtWallsType(Building::ConcreteWithWindows);

    // ========= Nodes =========
    NodeContainer apNodes;
    apNodes.Create(1);

    NodeContainer staNodes;
    staNodes.Create(1);

    // ========= Wi-Fi Configuration =========
    WifiHelper wifi;
    WifiMacHelper mac;

    const uint32_t apCount = 1;
    std::vector<YansWifiPhyHelper> phys;
    phys.reserve(apCount);

    // Create independent channels for each AP
    for (uint32_t i = 0; i < apCount; ++i)
    {
        YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
        Ptr<YansWifiChannel> channelPtr = channel.Create();

        YansWifiPhyHelper phy;
        phy.SetChannel(channelPtr);
        phys.push_back(phy);
    }

    NetDeviceContainer apDevices;
    NetDeviceContainer staDevices;

    // Configure APs
    // AP 0 (Ns3WiFi)
    {
        wifi.SetStandard(WIFI_STANDARD_80211ax);
        wifi.SetRemoteStationManager("ns3::IdealWifiManager");

        Ssid ssid("Ns3WiFi");
        mac.SetType("ns3::ApWifiMac",
                    "Ssid", SsidValue(ssid),
                    "QosSupported", BooleanValue(true));

        phys[0].Set("TxPowerStart", DoubleValue(20));
        phys[0].Set("TxPowerEnd", DoubleValue(20));
        phys[0].Set("ChannelSettings", StringValue("{0, 40, BAND_5GHZ, 0}"));

        NetDeviceContainer apDev = wifi.Install(phys[0], mac, apNodes.Get(0));
        apDevices.Add(apDev);
    }

    // Configure STAs
    // STA 0
    {
        wifi.SetStandard(WIFI_STANDARD_80211ax);
        wifi.SetRemoteStationManager("ns3::IdealWifiManager");

        Ssid ssid("Ns3WiFi");
        mac.SetType("ns3::StaWifiMac",
                    "Ssid", SsidValue(ssid),
                    "QosSupported", BooleanValue(true),
                    "ActiveProbing", BooleanValue(true));

        phys[0].Set("TxPowerStart", DoubleValue(20));
        phys[0].Set("TxPowerEnd", DoubleValue(20));

        NetDeviceContainer staDev = wifi.Install(phys[0], mac, staNodes.Get(0));
        staDevices.Add(staDev);
    }


    // ========= Mobility =========
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

    // AP Positions
    mobility.Install(apNodes);
    apNodes.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(1.87292, 2.56642, 0.323015));

    // STA Positions
    mobility.Install(staNodes);
    staNodes.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(5.88144, 4.88754, 1.44235));


    // ========= Buildings =========
    BuildingsHelper::Install(apNodes);
    BuildingsHelper::Install(staNodes);

    // ========= Internet =========
    InternetStackHelper stack;
    stack.Install(apNodes);
    stack.Install(staNodes);

    Ipv4AddressHelper address;
    Ipv4InterfaceContainer apIfaces;
    Ipv4InterfaceContainer staIfaces;
    std::vector<Ipv4Address> staAddrs(staNodes.GetN());

    for (uint32_t i = 0; i < apCount; ++i)
    {
        std::string base = "10.1." + std::to_string(i + 1) + ".0";
        address.SetBase(Ipv4Address(base.c_str()), "255.255.255.0");

        NetDeviceContainer devs;
        devs.Add(apDevices.Get(i));

        std::vector<uint32_t> staIndices;
        for (uint32_t j = 0; j < staNodes.GetN(); ++j)
        {
            if (apCount != 0 && (j % apCount) == i)
            {
                devs.Add(staDevices.Get(j));
                staIndices.push_back(j);
            }
        }

        auto ifaces = address.Assign(devs);
        apIfaces.Add(ifaces.Get(0));
        for (uint32_t k = 0; k < staIndices.size(); ++k)
        {
            staIfaces.Add(ifaces.Get(k + 1));
            staAddrs[staIndices[k]] = ifaces.GetAddress(k + 1);
        }
    }

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // ========= Applications (Traffic Flows) =========
    const uint16_t basePort = 9000;

    // Create packet sinks (servers)
    // Server on AP_1
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 1));
        ApplicationContainer serverApps = sink.Install(apNodes.Get(0));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Server on STA_1
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 0));
        ApplicationContainer serverApps = sink.Install(staNodes.Get(0));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Create traffic sources
    // Flow 1: AP_0 -> STA_1 (OnOff)
    {
        OnOffHelper onoff("ns3::UdpSocketFactory", Address(InetSocketAddress(staAddrs[0], basePort + 0)));
        onoff.SetAttribute("PacketSize", UintegerValue(1500));
        onoff.SetAttribute("DataRate", DataRateValue(DataRate("100Mbps")));
        onoff.SetAttribute("MaxBytes", UintegerValue(0));
        onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1.000000]"));
        onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0.000000]"));
        
        ApplicationContainer clientApps = onoff.Install(apNodes.Get(0));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }

    // Flow 2: STA_0 -> AP_1 (OnOff)
    {
        OnOffHelper onoff("ns3::UdpSocketFactory", Address(InetSocketAddress(apIfaces.GetAddress(0), basePort + 1)));
        onoff.SetAttribute("PacketSize", UintegerValue(512));
        onoff.SetAttribute("DataRate", DataRateValue(DataRate("0Mbps")));
        onoff.SetAttribute("MaxBytes", UintegerValue(0));
        onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=0.000000]"));
        onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=1.000000]"));
        
        ApplicationContainer clientApps = onoff.Install(staNodes.Get(0));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }


    // ========= Packet Sniffing =========
    using namespace boost::interprocess;
    shared_memory_object::remove("Ns3PpduSharedMemory");

    Ptr<SniffUtils> Sniff_Utils = CreateObject<SniffUtils>();
    NetDeviceContainer allDevices;
    allDevices.Add(apDevices);
    allDevices.Add(staDevices);
    Sniff_Utils->Initialize(allDevices,allDevices, duration);
    // ========= Run Simulation =========
    NS_LOG_INFO("Starting simulation for " << duration << " seconds");
    Simulator::Stop(Seconds(duration));
    Simulator::Run();
    NS_LOG_INFO("Simulation finished");
    Simulator::Destroy();

    return 0;
}
