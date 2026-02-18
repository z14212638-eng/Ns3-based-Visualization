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
    apNodes.Create(2);

    NodeContainer staNodes;
    staNodes.Create(2);

    // ========= Wi-Fi Configuration =========
    WifiHelper wifi;
    WifiMacHelper mac;

    const uint32_t apCount = 2;
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
        wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");

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

    // AP 1 (Ns3WiFi2)
    {
        wifi.SetStandard(WIFI_STANDARD_80211ax);
        wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");

        Ssid ssid("Ns3WiFi2");
        mac.SetType("ns3::ApWifiMac",
                    "Ssid", SsidValue(ssid),
                    "QosSupported", BooleanValue(true));

        phys[1].Set("TxPowerStart", DoubleValue(20));
        phys[1].Set("TxPowerEnd", DoubleValue(20));
        phys[1].Set("ChannelSettings", StringValue("{0, 40, BAND_5GHZ, 0}"));

        NetDeviceContainer apDev = wifi.Install(phys[1], mac, apNodes.Get(1));
        apDevices.Add(apDev);
    }

    // Configure STAs
    // STA 0
    {
        wifi.SetStandard(WIFI_STANDARD_80211ax);
        wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");

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

    // STA 1
    {
        wifi.SetStandard(WIFI_STANDARD_80211ax);
        wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");

        Ssid ssid("Ns3WiFi2");
        mac.SetType("ns3::StaWifiMac",
                    "Ssid", SsidValue(ssid),
                    "QosSupported", BooleanValue(true),
                    "ActiveProbing", BooleanValue(true));

        phys[1].Set("TxPowerStart", DoubleValue(20));
        phys[1].Set("TxPowerEnd", DoubleValue(20));

        NetDeviceContainer staDev = wifi.Install(phys[1], mac, staNodes.Get(1));
        staDevices.Add(staDev);
    }


    // ========= Mobility =========
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

    // AP Positions
    mobility.Install(apNodes);
    apNodes.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(6.77271, 3.1627, 2.64605));
    apNodes.Get(1)->GetObject<MobilityModel>()->SetPosition(Vector(6.05916, 2.4272, 2.64605));

    // STA Positions
    mobility.Install(staNodes);
    staNodes.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(8.32953, 2.55456, 4.99825));
    staNodes.Get(1)->GetObject<MobilityModel>()->SetPosition(Vector(7.31959, 1.97275, 4.99825));


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
    // Server on AP_0
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 2));
        ApplicationContainer serverApps = sink.Install(apNodes.Get(0));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Server on AP_1
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 3));
        ApplicationContainer serverApps = sink.Install(apNodes.Get(1));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Server on STA_0
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 0));
        ApplicationContainer serverApps = sink.Install(staNodes.Get(0));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Server on STA_1
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), basePort + 1));
        ApplicationContainer serverApps = sink.Install(staNodes.Get(1));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // Create traffic sources
    // Flow 1: AP_0 -> STA_0 (OnOff)
    {
        OnOffHelper onoff("ns3::UdpSocketFactory", Address(InetSocketAddress(staAddrs[0], basePort + 0)));
        onoff.SetAttribute("PacketSize", UintegerValue(512));
        onoff.SetAttribute("DataRate", DataRateValue(DataRate("1Mbps")));
        onoff.SetAttribute("MaxBytes", UintegerValue(0));
        onoff.SetAttribute("OnTime", StringValue("ns3::UniformRandomVariable[Min=0.000000|Max=1.000000]"));
        onoff.SetAttribute("OffTime", StringValue("ns3::ExponentialRandomVariable[Mean=1.000000]"));
        
        ApplicationContainer clientApps = onoff.Install(apNodes.Get(0));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }

    // Flow 2: AP_1 -> STA_1 (CBR)
    {
        UdpClientHelper client(staAddrs[1], basePort + 1);
        client.SetAttribute("MaxPackets", UintegerValue(4294967295));
        client.SetAttribute("Interval", TimeValue(Seconds(0.001)));
        client.SetAttribute("PacketSize", UintegerValue(512));
        
        ApplicationContainer clientApps = client.Install(apNodes.Get(1));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }

    // Flow 3: AP_1 -> STA_1 (CBR)
    {
        UdpClientHelper client(staAddrs[1], basePort + 1);
        client.SetAttribute("MaxPackets", UintegerValue(4294967295));
        client.SetAttribute("Interval", TimeValue(Seconds(0.001)));
        client.SetAttribute("PacketSize", UintegerValue(512));
        
        ApplicationContainer clientApps = client.Install(apNodes.Get(1));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }

    // Flow 4: STA_0 -> AP_0 (Bulk)
    {
        BulkSendHelper bulk("ns3::TcpSocketFactory", Address(InetSocketAddress(apIfaces.GetAddress(0), basePort + 2)));
        bulk.SetAttribute("SendSize", UintegerValue(512));
        bulk.SetAttribute("MaxBytes", UintegerValue(0));
        
        ApplicationContainer clientApps = bulk.Install(staNodes.Get(0));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }

    // Flow 5: STA_1 -> AP_1 (OnOff)
    {
        OnOffHelper onoff("ns3::UdpSocketFactory", Address(InetSocketAddress(apIfaces.GetAddress(1), basePort + 3)));
        onoff.SetAttribute("PacketSize", UintegerValue(512));
        onoff.SetAttribute("DataRate", DataRateValue(DataRate("1Mbps")));
        onoff.SetAttribute("MaxBytes", UintegerValue(0));
        onoff.SetAttribute("OnTime", StringValue("ns3::NormalRandomVariable[Mean=0.000000|Variance=1.000000|Bound=0.000000]"));
        onoff.SetAttribute("OffTime", StringValue("ns3::UniformRandomVariable[Min=0.000000|Max=1.000000]"));
        
        ApplicationContainer clientApps = onoff.Install(staNodes.Get(1));
        clientApps.Start(Seconds(0));
        clientApps.Stop(Seconds(10.000000));
    }


    // ========= Packet Sniffing =========
    using namespace boost::interprocess;
    shared_memory_object::remove("Ns3PpduSharedMemory");

    Ptr<SniffUtils> Sniff_Utils = CreateObject<SniffUtils>();
    Sniff_Utils->Initialize(staDevices, apDevices, duration);
    // ========= Run Simulation =========
    NS_LOG_INFO("Starting simulation for " << duration << " seconds");
    Simulator::Stop(Seconds(duration));
    Simulator::Run();
    NS_LOG_INFO("Simulation finished");
    Simulator::Destroy();

    return 0;
}
