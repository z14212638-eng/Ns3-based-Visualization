#include "ns3/QNs3.h"
#include "ns3/SniffUtils.h"

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

int main(int argc, char* argv[])
{
    Time::SetResolution(Time::NS);

    // ===== Simulation Parameters =====
    uint32_t numAp = 2;
    uint32_t numStaPerAp = 3;
    double simTime = 20.0;        // seconds
    uint32_t intervalMs = 40;     // STA -> AP interval, smaller traffic

    // ===== Node Containers =====
    NodeContainer apNodes;
    apNodes.Create(numAp);

    NodeContainer staNodes;
    staNodes.Create(numAp * numStaPerAp);

    NetDeviceContainer apDevices;
    NetDeviceContainer staDevices;

    // ===== Wi-Fi Setup =====
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211ax);

    WifiMacHelper mac;

    // ===== Install APs and STAs =====
    for (uint32_t i = 0; i < numAp; ++i)
    {
        // 每个 AP 使用独立信道
        YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
        YansWifiPhyHelper phy;
        phy.SetChannel(channel.Create());

        Ssid ssid("ppdu-test-" + std::to_string(i));

        // AP
        mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid), "QosSupported", BooleanValue(true));
        NetDeviceContainer apDev = wifi.Install(phy, mac, apNodes.Get(i));
        apDevices.Add(apDev);

        // STAs
        mac.SetType("ns3::StaWifiMac",
                    "Ssid", SsidValue(ssid),
                    "QosSupported", BooleanValue(true),
                    "ActiveProbing", BooleanValue(false));

        for (uint32_t j = 0; j < numStaPerAp; ++j)
        {
            NetDeviceContainer staDev = wifi.Install(phy, mac, staNodes.Get(i * numStaPerAp + j));
            staDevices.Add(staDev);
        }
    }

    // ===== Mobility =====
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(apNodes);
    mobility.Install(staNodes);

    // ===== Internet Stack =====
    InternetStackHelper stack;
    stack.Install(apNodes);
    stack.Install(staNodes);

    // ===== IPv4 Addresses =====
    Ipv4AddressHelper address;
    for (uint32_t i = 0; i < numAp; ++i)
    {
        std::string base = "10.1." + std::to_string(i + 1) + ".0";
        address.SetBase(Ipv4Address(base.c_str()), "255.255.255.0");

        NetDeviceContainer devs;
        devs.Add(apNodes.Get(i)->GetDevice(0));
        for (uint32_t j = 0; j < numStaPerAp; ++j)
        {
            devs.Add(staNodes.Get(i * numStaPerAp + j)->GetDevice(0));
        }
        address.Assign(devs);
    }

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // ===== Applications (UDP) =====
    // 每个 AP 安装一个 UDP Server
    for (uint32_t i = 0; i < numAp; ++i)
    {
        uint16_t port = 9000 + i;
        UdpServerHelper server(port);
        auto serverApp = server.Install(apNodes.Get(i));
        serverApp.Start(Seconds(0.5));
        serverApp.Stop(Seconds(simTime));
    }

    // STA 客户端轮询 AP，流量稍小且分散
    for (uint32_t i = 0; i < staNodes.GetN(); ++i)
    {
        uint32_t apIdx = i % numAp; // 轮询选择 AP
        Ptr<Node> sta = staNodes.Get(i);
        Ipv4Address apAddr = apNodes.Get(apIdx)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
        uint16_t port = 9000 + apIdx;

        UdpClientHelper client(apAddr, port);
        client.SetAttribute("MaxPackets", UintegerValue(0xFFFFFFFF));
        client.SetAttribute("Interval", TimeValue(MilliSeconds(intervalMs)));
        client.SetAttribute("PacketSize", UintegerValue(1200));

        auto clientApp = client.Install(sta);
        clientApp.Start(Seconds(1.0));
        clientApp.Stop(Seconds(simTime));
    }

    // ===== SniffUtils =====
    using namespace boost::interprocess;
    shared_memory_object::remove("Ns3PpduSharedMemory");
    Ptr<SniffUtils> sniffer = CreateObject<SniffUtils>();
    sniffer->Initialize(staDevices, apDevices, simTime);

    // ===== Run Simulation =====
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
