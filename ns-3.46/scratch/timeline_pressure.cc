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

    // ===== Nodes =====
    NodeContainer apNode;
    apNode.Create(1);

    NodeContainer staNodes;
    staNodes.Create(1);

    // ===== Wi-Fi (IMPORTANT: Yans) =====
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211ax);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    Ssid ssid("ppdu-test");

    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid),
                "QosSupported", BooleanValue(true));

    NetDeviceContainer apDevices =
        wifi.Install(phy, mac, apNode);

    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "QosSupported", BooleanValue(true),
                "ActiveProbing", BooleanValue(false));

    NetDeviceContainer staDevices =
        wifi.Install(phy, mac, staNodes);

    // ===== Mobility =====
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(apNode);
    mobility.Install(staNodes);

    // ===== Internet =====
    InternetStackHelper stack;
    stack.Install(apNode);
    stack.Install(staNodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    address.Assign(apDevices);
    address.Assign(staDevices);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // =====================================================
    // ===== High-Load Traffic (ONLY CHANGE IS HERE) =======
    // =====================================================

    uint16_t portSta = 9000;
    uint16_t portAp  = 9001;

    // --- STA: UDP Server ---
    UdpServerHelper staServer(portSta);
    auto staServerApp = staServer.Install(staNodes.Get(0));
    staServerApp.Start(Seconds(0.5));
    staServerApp.Stop(Seconds(10.0));

    // --- AP: UDP Server ---
    UdpServerHelper apServer(portAp);
    auto apServerApp = apServer.Install(apNode.Get(0));
    apServerApp.Start(Seconds(0.5));
    apServerApp.Stop(Seconds(10.0));

    // --- STA -> AP (高强度) ---
    UdpClientHelper staToAp(
        apNode.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),
        portAp);

    staToAp.SetAttribute("MaxPackets", UintegerValue(0xFFFFFFFF));
    staToAp.SetAttribute("Interval", TimeValue(MicroSeconds(100))); // 高强度
    staToAp.SetAttribute("PacketSize", UintegerValue(1472));

    auto staClientApp = staToAp.Install(staNodes.Get(0));
    staClientApp.Start(Seconds(1.0));
    staClientApp.Stop(Seconds(10.0));

    // --- AP -> STA (高强度，制造碰撞) ---
    UdpClientHelper apToSta(
        staNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),
        portSta);

    apToSta.SetAttribute("MaxPackets", UintegerValue(0xFFFFFFFF));
    apToSta.SetAttribute("Interval", TimeValue(MicroSeconds(100))); // 同级别竞争
    apToSta.SetAttribute("PacketSize", UintegerValue(1472));

    auto apClientApp = apToSta.Install(apNode.Get(0));
    apClientApp.Start(Seconds(1.0));
    apClientApp.Stop(Seconds(10.0));

    // ===== SniffUtils =====
    using namespace boost::interprocess;
    shared_memory_object::remove("Ns3PpduSharedMemory");

    Ptr<SniffUtils> sniffer = CreateObject<SniffUtils>();
    sniffer->Initialize(staDevices, apDevices, 10);

    // ===== Run =====
    Simulator::Stop(Seconds(10));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
