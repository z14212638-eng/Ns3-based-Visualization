#include "ns3/QNs3-helper.h"
#include "ns3/core-module.h"
#inlcude "ns3/QNs3.h"

/**
 * @file
 *
 * Explain here what the example does.
 */

using namespace ns3;

int
main(int argc, char* argv[])
{
    auto generalConfig = ns3::GetGeneralConfig(generalConfigFolder);
    auto stas = ns3::GetApConfigs(staFolder);
    auto aps = ns3::GetApConfigs(apFolder);

    Ptr<Building> building;
    building = CreateObject<Building>();
    building->SetBoundaries(Box(0,generalConfig.range[0],0,generalConfig.range[1],0,generalConfig.range[2]));
    building->SetBuildingType(generalConfig.buildingType);
    building->SetExtWallsType(generalConfig.WallType);
    double durations = generalConfig.SimulationTime;    

    NodeContainer apNodes;
    apNodes.Create(apConfigs.size());
    NodeContainer staNodes;
    staNodes.Create(staConfigs.size());

    uint16_t duration = generalConfig.SimulationTime;

    WifiHelper wifi;
    wifi.SetStandard(Configure_WifiStandard(apConfigs.front().Standard));

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    auto channelPtr = channel.Create();

    YansWifiPhyHelper phy;
    phy.SetChannel(channelPtr);
    phy.Set("ChannelSettings", StringValue(Configure_BandChannel(apConfigs.front())));

    WifiMacHelper mac;
    Ssid ssid(apConfigs.front().Ssid);

    wifi.SetRemoteStationManager(Configure_RateCtrlManager(apConfigs.front().Rate_ctr_algo));
    mac.SetType("ns3::ApWifiMac",
                "Ssid",
                SsidValue(ssid),
                "EnableBeaconJitter",
                BooleanValue(apConfigs.front().beacon ? apConfigs.front().beacon->EnableBeaconJitter
                                                      : false));
    NetDeviceContainer apDevices = wifi.Install(phy, mac, apNodes);

    ConfigureMobility(apConfigs, apNodes);
    ConfigureMobility(staConfigs, staNodes);

    ApplyDeviceConfigs(apConfigs, apDevices);
    ApplyDeviceConfigs(staConfigs, staDevices);

    InternetStackHelper stack;
    stack.Install(apNodes);
    stack.Install(staNodes);

    Ipv4AddressHelper address;
    address.SetBase("10.0.0.0", "255.255.255.0");
    auto apIfaces = address.Assign(apDevices);
    auto staIfaces = address.Assign(staDevices);

    uint16_t port = 9000;
    UdpServerHelper server(port);
    ApplicationContainer serverApps = server.Install(apNodes.Get(0));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(duration));

    UdpClientHelper client(staIfaces.GetAddress(0), port);
    client.SetAttribute("MaxPackets", UintegerValue(0));
    client.SetAttribute("Interval", TimeValue(MilliSeconds(10)));
    client.SetAttribute("PacketSize", UintegerValue(512));
    ApplicationContainer clientApps = client.Install(staNodes.Get(0));
    clientApps.Start(Seconds(1.0));
    clientApps.Stop(Seconds(duration));

    Simulator::Stop(Seconds(duration));

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
