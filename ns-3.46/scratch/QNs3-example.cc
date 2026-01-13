#include "ns3/QNs3-helper.h"
#include "ns3/QNs3.h"
#include "ns3/SniffUtils.h"
#include "ns3/applications-module.h"
#include "ns3/buildings-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"

using namespace ns3;

int
main(int argc, char* argv[])
{
    // ========= Config =========
    GeneralConfig helper;
    std::string generalConfigFolder = helper.path + "GeneralJson/";
    std::string staFolder = helper.path + "StaConfigJson/";
    std::string apFolder = helper.path + "ApConfigJson/";

    auto generalConfig = GetGeneralConfig(generalConfigFolder);
    auto stas = GetStaConfigs(staFolder);
    auto aps = GetApConfigs(apFolder);

    double duration = generalConfig.SimulationTime;

    // ========= Building =========
    Ptr<Building> building = CreateObject<Building>();
    building->SetBoundaries(
        Box(0, generalConfig.range[0], 0, generalConfig.range[1], 0, generalConfig.range[2]));

    building->SetBuildingType(QNs3Helper::GetBuildingType(generalConfig));
    building->SetExtWallsType(QNs3Helper::GetBuildingExtWallsType(generalConfig));

    // ========= Nodes =========
    NodeContainer apNodes;
    apNodes.Create(aps.size());

    NodeContainer staNodes;
    staNodes.Create(stas.size());

    // ========= Wi-Fi =========
    WifiHelper wifi;
    wifi.SetStandard(QNs3Helper::Configure_WifiStandard(aps.front().Standard));

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    Ptr<YansWifiChannel> channelPtr = channel.Create();

    YansWifiPhyHelper phy;
    phy.SetChannel(channelPtr);

    WifiMacHelper mac;
    Ssid ssid(aps.front().Ssid);

    // ========= AP =========
    wifi.SetRemoteStationManager(QNs3Helper::Configure_RateCtrlManager(aps.front().Rate_ctrl_algo));

    mac.SetType("ns3::ApWifiMac",
                "Ssid",
                SsidValue(ssid),
                "QosSupported",
                BooleanValue(true),
                "EnableBeaconJitter",
                BooleanValue(aps.front().beacon ? aps.front().beacon->EnableBeaconJitter : false));

    NetDeviceContainer apDevices = wifi.Install(phy, mac, apNodes);

    // ========= STA =========
    wifi.SetRemoteStationManager(
        QNs3Helper::Configure_RateCtrlManager(stas.front().Rate_ctrl_algo));

    mac.SetType("ns3::StaWifiMac",
                "Ssid",
                SsidValue(ssid),
                "QosSupported",
                BooleanValue(true),
                "ActiveProbing",
                BooleanValue(stas.front().ActiveProbing.value_or(true)));

    NetDeviceContainer staDevices = wifi.Install(phy, mac, staNodes);

    // ========= Mobility =========
    QNs3Helper::ConfigureMobility(aps, apNodes);
    QNs3Helper::ConfigureMobility(stas, staNodes);

    // ========= Buildings =========
    BuildingsHelper::Install(apNodes);
    BuildingsHelper::Install(staNodes);

    // ========= PHY / MAC / QoS =========
    QNs3Helper::ApplyDeviceConfigs(aps, apDevices);
    QNs3Helper::ApplyDeviceConfigs(stas, staDevices);

    // ========= Internet =========
    InternetStackHelper stack;
    stack.Install(apNodes);
    stack.Install(staNodes);

    Ipv4AddressHelper address;
    address.SetBase("10.0.0.0", "255.255.255.0");

    auto apIfaces = address.Assign(apDevices);
    auto staIfaces = address.Assign(staDevices);

    // ========= App =========
    uint16_t port = 9000;

    UdpServerHelper server(port);
    auto serverApps = server.Install(apNodes.Get(0));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(duration));

    UdpClientHelper client(staIfaces.GetAddress(0), port);
    client.SetAttribute("MaxPackets", UintegerValue(0));
    client.SetAttribute("Interval", TimeValue(MilliSeconds(10)));
    client.SetAttribute("PacketSize", UintegerValue(512));

    auto clientApps = client.Install(staNodes.Get(0));
    clientApps.Start(Seconds(1.0));
    clientApps.Stop(Seconds(duration));

    //========= Sniff =========
    Ptr<SniffUtils> sniffer = CreateObject<SniffUtils>();
    sniffer->Initialize(staDevices, apDevices, 10);

    // ========= Run =========
    Simulator::Stop(Seconds(duration));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
