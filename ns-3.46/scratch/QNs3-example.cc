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
    std::string ns3Path;
    for (int i = 1; i + 1 < argc; ++i)
    {
        if (std::string(argv[i]) == "--ns3path")
        {
            ns3Path = argv[i + 1];
            break;
        }
    }

    if (!ns3Path.empty() && ns3Path.back() != '/')
    {
        ns3Path.push_back('/');
    }

    helper.ns3Path = ns3Path;
    helper.path = helper.ns3Path + helper.jsonPath;

    std::string basePath = helper.path;
    if (argc > 1 && argv[1] != nullptr)
    {
        const std::string arg1 = argv[1];
        if (!arg1.empty() && arg1 != "--" && arg1.rfind("--", 0) != 0)
        {
            basePath = arg1;
            if (!basePath.empty() && basePath.back() != '/')
            {
                basePath.push_back('/');
            }
        }
    }

    std::string generalConfigFolder = basePath + "GeneralJson/";
    std::string staFolder = basePath + "StaConfigJson/";
    std::string apFolder = basePath + "ApConfigJson/";

    auto generalConfig = GetGeneralConfig(generalConfigFolder);
    auto stas = GetStaConfigs(staFolder);
    auto aps = GetApConfigs(apFolder);

    // PrintNodeConfig(aps.front(), std::cout);
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
    WifiMacHelper mac;

    const uint32_t apCount = apNodes.GetN();
    std::vector<YansWifiPhyHelper> phys;
    phys.reserve(apCount);

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

    for (uint32_t i = 0; i < apCount; ++i)
    {
        const auto &apCfg = aps[i];
        wifi.SetStandard(QNs3Helper::Configure_WifiStandard(apCfg.Standard));
        wifi.SetRemoteStationManager(
            QNs3Helper::Configure_RateCtrlManager(apCfg.Rate_ctrl_algo, apCfg.Standard));

        Ssid ssid(apCfg.Ssid);
        mac.SetType("ns3::ApWifiMac",
                    "Ssid",
                    SsidValue(ssid),
                    "QosSupported",
                    BooleanValue(true),
                    "EnableBeaconJitter",
                    BooleanValue(apCfg.beacon ? apCfg.beacon->EnableBeaconJitter : false));

        NetDeviceContainer apDev = wifi.Install(phys[i], mac, apNodes.Get(i));
        apDevices.Add(apDev);
    }

    for (uint32_t i = 0; i < staNodes.GetN(); ++i)
    {
        const uint32_t apIdx = apCount == 0 ? 0 : (i % apCount);
        const auto &apCfg = aps[apIdx];
        const auto &staCfg = stas[i];

        wifi.SetStandard(QNs3Helper::Configure_WifiStandard(apCfg.Standard));
        wifi.SetRemoteStationManager(
            QNs3Helper::Configure_RateCtrlManager(staCfg.Rate_ctrl_algo, staCfg.Standard));

        Ssid ssid(apCfg.Ssid);
        mac.SetType("ns3::StaWifiMac",
                    "Ssid",
                    SsidValue(ssid),
                    "QosSupported",
                    BooleanValue(true),
                    "ActiveProbing",
                    BooleanValue(staCfg.ActiveProbing.value_or(true)));

        NetDeviceContainer staDev = wifi.Install(phys[apIdx], mac, staNodes.Get(i));
        staDevices.Add(staDev);
    }

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
    Ipv4InterfaceContainer apIfaces;
    Ipv4InterfaceContainer staIfaces;

    for (uint32_t i = 0; i < apCount; ++i)
    {
        std::string base = "10.1." + std::to_string(i + 1) + ".0";
        address.SetBase(Ipv4Address(base.c_str()), "255.255.255.0");

        NetDeviceContainer devs;
        devs.Add(apDevices.Get(i));
        for (uint32_t j = 0; j < staNodes.GetN(); ++j)
        {
            if (apCount != 0 && (j % apCount) == i)
            {
                devs.Add(staDevices.Get(j));
            }
        }

        auto ifaces = address.Assign(devs);
        apIfaces.Add(ifaces.Get(0));
        for (uint32_t k = 1; k < ifaces.GetN(); ++k)
        {
            staIfaces.Add(ifaces.Get(k));
        }
    }

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // ========= App =========
    const uint16_t basePort = 9000;

    // One server per AP
    for (uint32_t i = 0; i < apNodes.GetN(); ++i)
    {
        const uint16_t port = basePort + i;
        UdpServerHelper server(port);
        auto serverApps = server.Install(apNodes.Get(i));
        serverApps.Start(Seconds(0.5));
        serverApps.Stop(Seconds(duration));
    }

    // STAs generate traffic toward APs (round-robin) with varied load
    for (uint32_t i = 0; i < staNodes.GetN(); ++i)
    {
        const uint32_t apIdx = apNodes.GetN() == 0 ? 0 : (i % apNodes.GetN());
        const uint16_t port = basePort + apIdx;
        const Ipv4Address apAddr = apIfaces.GetAddress(apIdx);

        UdpClientHelper client(apAddr, port);
        client.SetAttribute("MaxPackets", UintegerValue(0xFFFFFFFF));

        const uint32_t profile = i % 3;
        if (profile == 0)
        {
            client.SetAttribute("Interval", TimeValue(MilliSeconds(10)));
            client.SetAttribute("PacketSize", UintegerValue(512));
        }
        else if (profile == 1)
        {
            client.SetAttribute("Interval", TimeValue(MilliSeconds(20)));
            client.SetAttribute("PacketSize", UintegerValue(1200));
        }
        else
        {
            client.SetAttribute("Interval", TimeValue(MilliSeconds(40)));
            client.SetAttribute("PacketSize", UintegerValue(800));
        }

        auto clientApps = client.Install(staNodes.Get(i));
        clientApps.Start(Seconds(1.0));
        clientApps.Stop(Seconds(duration));
    }

    //========= Sniff =========
    using namespace boost::interprocess;
    shared_memory_object::remove("Ns3PpduSharedMemory");

    Ptr<SniffUtils> sniffer = CreateObject<SniffUtils>();
    sniffer->Initialize(staDevices, apDevices, duration);

    // ========= Run =========
    Simulator::Stop(Seconds(duration));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
