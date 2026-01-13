#include "QNs3-helper.h"

namespace ns3
{

WifiStandard
QNs3Helper::Configure_WifiStandard(const std::string& standard)
{
    static const std::unordered_map<std::string, WifiStandard> standard_map = {
        {"802.11n-5GHz", WIFI_STANDARD_80211n},
        {"802.11n-2.4GHz", WIFI_STANDARD_80211n},
        {"802.11ac", WIFI_STANDARD_80211ac},
        {"802.11ax", WIFI_STANDARD_80211ax},
        {"802.11g", WIFI_STANDARD_80211g},
        {"802.11a", WIFI_STANDARD_80211a},
    };

    const auto it = standard_map.find(standard);
    if (it == standard_map.end())
    {
        NS_FATAL_ERROR("Unsupported Wifi standard: " << standard);
        return WIFI_STANDARD_80211n;
    }
    return it->second;
}

std::string
QNs3Helper::Configure_RateCtrlManager(std::optional<std::string> rate_ctrl_manager)
{
    static const std::unordered_map<std::string, std::string> manager_map = {
        {"Aarf", "ns3::AarfWifiManager"},
        {"Aarfcd", "ns3::AarfcdWifiManager"},
        {"Aminstrel", "ns3::AminstrelWifiManager"},
        {"Minstrel", "ns3::MinstrelWifiManager"},
        {"MinstrelHt", "ns3::MinstrelHtWifiManager"},
        {"Ideal", "ns3::IdealWifiManager"},
        {"Arf", "ns3::ArfWifiManager"},
        {"Onoe", "ns3::OnoeWifiManager"},
        {"ConstantRate", "ns3::ConstantRateWifiManager"},
    };

    if (rate_ctrl_manager.has_value())
    {
        const auto it = manager_map.find(*rate_ctrl_manager);
        if (it == manager_map.end())
        {
            NS_FATAL_ERROR("Unsupported rate control manager: " << *rate_ctrl_manager
                                                                << ".Defaulting to Aarf");
            return "ns3::AarfWifiManager";
        }
        return it->second;
    }
    else
    {
        return "ns3::AarfWifiManager";
    }
}

std::string
QNs3Helper::BuildChannelSettings(const NodeConfig& cfg)
{
    const auto band = (cfg.Frequency <= 3.0) ? "BAND_2_4GHZ" : "BAND_5GHZ";
    std::cout<<(cfg.Frequency >= 3.0) <<std::endl;
    std::ostringstream oss;
    oss << "{"<<cfg.Channel_number << ", " << cfg.Bandwidth << ", " << band << ", 0}";
    std::cout<<oss.str()<<std::endl;
    return oss.str();
}

WifiPhyBand
Determine_Band(const double& frequency)
{
    if (frequency >= 5900 && frequency <= 6500)
    {
        return WIFI_PHY_BAND_6GHZ;
    }
    else if (frequency >= 5600 && frequency <= 5900)
    {
        if (frequency >= 5000 && frequency <= 5900)
        {
            return WIFI_PHY_BAND_5GHZ;
        }
        else if (frequency >= 2400 && frequency <= 2500)
        {
            return WIFI_PHY_BAND_2_4GHZ;
        }
    }
    return WIFI_PHY_BAND_UNSPECIFIED;
}

WifiChannelConfig
QNs3Helper::Configure_BandChannel(const NodeConfig& node)
{
    WifiChannelConfig channel_config;
    WifiPhyBand band = Determine_Band(node.Frequency);
    WifiChannelConfig::Segment segment(static_cast<uint8_t>(node.Channel_number),
                                       MHz_u{static_cast<double>(node.Bandwidth)},
                                       band,
                                       0);
    return WifiChannelConfig(segment);
}

AcIndex
ToAcIndex(const std::string& ac)
{
    static const std::unordered_map<std::string, AcIndex> kAcMap{
        {"AC_BE", AC_BE},
        {"AC_BK", AC_BK},
        {"AC_VI", AC_VI},
        {"AC_VO", AC_VO},
    };
    const auto it = kAcMap.find(ac);
    if (it == kAcMap.end())
    {
        NS_ABORT_MSG("Unknown access class: " << ac);
    }
    return it->second;
}

void
QNs3Helper::ConfigurePhy(const NodeConfig& cfg, const Ptr<WifiNetDevice>& device)
{
    auto phy = device->GetPhy();
    phy->SetOperatingChannel(Configure_BandChannel(cfg));
    phy->SetTxPowerStart(cfg.Tx_power);
    phy->SetTxPowerEnd(cfg.Tx_power);
    if (cfg.Slot)
    {
        phy->SetSlot(MicroSeconds(*cfg.Slot));
    }
    if (cfg.Sifs)
    {
        phy->SetSifs(MicroSeconds(*cfg.Sifs));
    }
    if (cfg.RxSensitivity)
    {
        phy->SetRxSensitivity(*cfg.RxSensitivity);
    }
    if (cfg.CcaEdThreshold)
    {
        phy->SetCcaEdThreshold(*cfg.CcaEdThreshold);
    }
    if (cfg.CcaSensitivity)
    {
        phy->SetCcaSensitivityThreshold(*cfg.CcaSensitivity);
    }
}

void
QNs3Helper::ConfigureRtsCts(const NodeConfig& cfg, const Ptr<WifiNetDevice>& device)
{
    auto manager = device->GetRemoteStationManager();
    manager->SetRtsCtsThreshold(cfg.Rts_Cts.Threshold);
    manager->SetFragmentationThreshold(2200);
}

void
QNs3Helper::ConfigureQos(const NodeConfig& cfg, Ptr<WifiMac> mac)
{
    if (!mac || !mac->GetQosSupported())
        return;

    for (const auto& kv : cfg.qos.Edca_params)
    {
        AcIndex ac = ToAcIndex(kv.first);

        Ptr<QosTxop> txop = mac->GetQosTxop(ac);
        if (!txop)
            continue; 

        const auto& params = kv.second;
        txop->SetMinCw(params.CWmin);
        txop->SetMaxCw(params.CWmax);
        txop->SetAifsn(params.AIFSN);

        uint32_t txop32 = (params.TXOPLimit + 31) / 32 * 32;
        txop->SetTxopLimit(MicroSeconds(txop32));
    }
}

void
QNs3Helper::ConfigureApMac(const NodeConfig& cfg, const Ptr<WifiNetDevice>& device)
{
    auto mac = DynamicCast<ApWifiMac>(device->GetMac());
    if (!mac)
    {
        return;
    }

    ConfigureQos(cfg, device->GetMac());

    if (cfg.beacon)
    {
        const auto& beacon = *cfg.beacon;

        uint32_t interval_tu = static_cast<uint32_t>(beacon.BeaconInterval * 1000.0 / 1024.0 + 0.5);
        interval_tu = std::max(1u, interval_tu);
        mac->SetBeaconInterval(MicroSeconds(interval_tu * 1024));

        mac->SetAttribute("BeaconGeneration", BooleanValue(beacon.set));
        mac->SetAttribute("EnableBeaconJitter", BooleanValue(beacon.EnableBeaconJitter));
    }
}


void
QNs3Helper::ConfigureStaMac(const NodeConfig& cfg, const Ptr<WifiNetDevice>& device)
{
    auto mac = DynamicCast<StaWifiMac>(device->GetMac());
    if (!mac)
    {
        return;
    }
    ConfigureQos(cfg, DynamicCast<WifiMac>(mac));
    if (cfg.ActiveProbing)
    {
        mac->SetAttribute("ActiveProbing", BooleanValue(*cfg.ActiveProbing));
        // mac->SetActiveProbing(*cfg.ActiveProbing);
    }
    if (cfg.MaxMissedBeacons)
    {
        mac->SetAttribute("MaxMissedBeacons", UintegerValue(*cfg.MaxMissedBeacons));
        // mac->SetMaxMissedBeacons(*cfg.MaxMissedBeacons);
    }
    if (cfg.ProbeRequestTimeout)
    {
        mac->SetAttribute("ProbeRequestTimeout", TimeValue(MilliSeconds(*cfg.ProbeRequestTimeout)));
        // mac->SetProbeRequestTimeout(MilliSeconds(*cfg.ProbeRequestTimeout));
    }
}

void
QNs3Helper::ConfigureMobility(const std::vector<NodeConfig>& configs, const NodeContainer& container)
{
    Ptr<ListPositionAllocator> allocator = CreateObject<ListPositionAllocator>();
    for (const auto& cfg : configs)
    {
        const double x = cfg.Position.size() > 0 ? cfg.Position[0] : 0.0;
        const double y = cfg.Position.size() > 1 ? cfg.Position[1] : 0.0;
        const double z = cfg.Position.size() > 2 ? cfg.Position[2] : 0.0;
        allocator->Add(Vector(x, y, z));
    }
    MobilityHelper mobility;
    mobility.SetPositionAllocator(allocator);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(container);
}

void
QNs3Helper::ApplyDeviceConfigs(const std::vector<NodeConfig>& configs, const NetDeviceContainer& devices)
{
    const std::size_t count = std::min<std::size_t>(configs.size(), devices.GetN());
    for (std::size_t i = 0; i < count; ++i)
    {
        auto wifiDev = DynamicCast<WifiNetDevice>(devices.Get(i));
        if (!wifiDev)
        {
            continue;
        }
        ConfigurePhy(configs[i], wifiDev);
        ConfigureRtsCts(configs[i], wifiDev);
        if (configs[i].NodeType == "AP")
        {
            ConfigureApMac(configs[i], wifiDev);
        }
        else
        {
            ConfigureStaMac(configs[i], wifiDev);
        }
    }
}

Building::BuildingType_t
QNs3Helper::GetBuildingType(const GeneralConfig& cfg)
{
    if (cfg.BuildingType == "Residential")
    {
        return Building::Residential;
    }
    else if (cfg.BuildingType == "Office")
    {
        return Building::Office;
    }
    else if (cfg.BuildingType == "Commercial")
    {
        return Building::Commercial;
    }
    else
    {
        return Building::Residential;
    }
}

Building::ExtWallsType_t
QNs3Helper::GetBuildingExtWallsType(const GeneralConfig& cfg)
{
    if (cfg.WallType == "Wood")
    {
        return Building::Wood;
    }
    else if (cfg.WallType == "ConcreteWithWindows")
    {
        return Building::ConcreteWithWindows;
    }
    else if (cfg.WallType == "ConcreteWithoutWindows")
    {
        return Building::ConcreteWithoutWindows;
    }
    else if (cfg.WallType == "StoneBlocks")
    {
        return Building::StoneBlocks;
    }
    else
    {
        return Building::Wood;
    }
}

} // namespace ns3
