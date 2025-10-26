#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/net-device-container.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ampdu-subframe-header.h"
#include "ns3/mac48-address.h"
#include "ns3/msdu-aggregator.h"
#include "ns3/wifi-mac-header.h"
#include "SniffUtils.h"
#include "ns3/wifi-phy.h"       
#include "ns3/wifi-ppdu.h"      
#include "ns3/ptr.h"      
#include "ns3/net-device-container.h"    

#include <ns3/callback.h>
#include <ns3/log-macros-disabled.h>
#include <ns3/log.h>
#include <ns3/object-base.h>
#include <ns3/qos-txop.h>
#include <ns3/simulator.h>
#include <ns3/trace-source-accessor.h>
#include <ns3/wifi-mac-queue.h>
#include <ns3/wifi-mac.h>
#include <ns3/wifi-net-device.h>


namespace ns3
{

    static const double SimulationTime = 0.0;
    NS_LOG_COMPONENT_DEFINE("SniffUtils");
    NS_OBJECT_ENSURE_REGISTERED(SniffUtils);

    TypeId
    SniffUtils::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::SniffUtils")
                               .SetParent<ns3::Object>()
                               .SetGroupName("Wifi")
                               .AddConstructor<SniffUtils>();
        return tid;
    }

    SniffUtils::SniffUtils()
    {
        NS_LOG_FUNCTION(this);
        m_initialized = false;
    }

    bool 
    SniffUtils::Initialize(NetDeviceContainer sender, 
                           NetDeviceContainer receiver, 
                           double simulationTime)
    {
        this->Set_simulation_time(simulationTime);

        for (auto senderNetDevice = sender.Begin(); senderNetDevice != sender.End(); senderNetDevice++)
        {
            Ptr<WifiNetDevice> senderDevice = DynamicCast<WifiNetDevice>(*senderNetDevice);
            Ptr<WifiPhy> phy = senderDevice->GetPhy();
            phy->TraceConnectWithoutContext("PhyTxBegin", 
                                            MakeCallback(&SniffUtils::Sniff_ppdu_begin,this));
        }
        return true;
    }

    void 
    SniffUtils::Sniff_tx_packet_begin(Ptr<const Packet> packet,
                          uint16_t frequency,
                          WifiTxVector txvector,
                          MpduInfo mpdu_info,
                          uint16_t sta_id)
    {
        ;
    }

    void 
    SniffUtils::Sniff_rx_packet_begin(Ptr<const Packet> packet,
                          uint16_t frequency,
                          WifiTxVector txvector,
                          MpduInfo mpdu_info,
                          SignalNoiseDbm noise,
                          uint16_t sta_id)
    {
        ;
    }

    void 
    SniffUtils::Sniff_drop_packet_phy(Ptr<const Packet> packet, 
                          WifiPhyRxfailureReason drop_reason)
    {
        ;
    }

    void 
    SniffUtils::Sniff_drop_ppdu_phy(Ptr<const WifiPpdu> ppdu, 
                        WifiPhyRxfailureReason drop_reason)
    {
        ;
    }
    
    void 
    SniffUtils::Sniff_tx_psdu_begin(WifiConstPsduMap psdu_map, 
                          WifiTxVector txvector, 
                          double tx_power)
    {
        ;
    }

    void 
    SniffUtils::Sniff_mac_header(const WifiMacHeader& wifi_mac_header, 
                              const WifiTxVector& tx_vector, 
                              Time time)
    {
        ;
    }

    void 
    SniffUtils::Sniff_tx_all_packets(Ptr<const Packet> packet,
                   uint16_t frequency,
                   WifiTxVector txvector,
                   MpduInfo mpdu_info,
                   uint16_t sta_id)
    {
        ;
    }

    void 
    SniffUtils::Sniff_ppdu_begin(Ptr<const WifiPpdu> ppdu, 
                     const WifiTxVector& tx_vector)
    {
        Ptr<const WifiPsdu> psdu = ppdu->GetPsdu();
        if (psdu)
        {
            WifiMacHeader mac_header = psdu->GetHeader(0);
            NS_LOG_UNCOND(mac_header.GetTypeString());
        }
        
    }

    void 
    SniffUtils::Set_simulation_time(double simulation_time)
    {
        ;
    }
}

