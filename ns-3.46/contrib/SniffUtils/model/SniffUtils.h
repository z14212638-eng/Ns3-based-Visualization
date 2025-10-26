#ifndef SNIFF_UTILS_H
#define SNIFF_UTILS_H

#include "ns3/ampdu-subframe-header.h"
#include "ns3/mac48-address.h"
#include "ns3/msdu-aggregator.h"
#include "ns3/wifi-mac-header.h"
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
#include "ns3/wifi-phy.h"       
#include "ns3/wifi-ppdu.h"      
#include "ns3/ptr.h"      
#include "ns3/net-device-container.h"      

#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <vector>

namespace ns3 
{
    /**
     * @brief Struct to store information about a PPDU
     * @param frame_type type of the frame ,including CONTROL , MANAGEMENT ,DATA
     * @param sender MAC address of the sender
     * @param receiver MAC address of the receiver
     * @param aggregate number of subframes aggregated in this PPDU
     * @param size_bytes size of the PPDU in bytes
     * @param AccessChannelTime time of the PPDU in the access channel
     * @param StartTxTime start time of the PPDU transmission
     * @param EndTxTime end time of the PPDU transmission
     * @param collision indicates if the PPDU was lost due to collision
     * @param CollisionTime time of the collision
     * @param SNRmargin SNR margin of the PPDU
     * @param SNRgap SNR gap of the PPDU
     * @param decodeState indicates if the PPDU was successfully decoded
     * @param ReasonForDecodeFail reason for the failure of decoding the PPDU
     * @param SuccessDecodeTime time of successful decoding of the PPDU
     * @param TxDuration duration of the PPDU transmission
     * @param mcs modulation and coding scheme of the PPDU
     */
    struct Ppdu_info
    {
        WifiMacType frame_type;
        Mac48Address sender;
        Mac48Address receiver;
        size_t aggregate;         
        uint32_t size_bytes;      
        double AccessChannelTime; 
        Time StartTxTime;         
        Time EndTxTime;           
        bool collision;           
        Time CollisionTime; 
        double SNRmargin;       
        double SNRgap;          
        bool decodeState;        
        uint8_t ReasonForDecodeFail; 
        Time SuccessDecodeTime;     
        Time TxDuration;           
        uint8_t mcs;
    };

    class SniffUtils : public Object
    {
        public:       
        SniffUtils();
        ~SniffUtils() = default;
        static TypeId 
        GetTypeId();
        /**
         * @brief Construct a new sniff utils object
         * @param sender net device of the sender
         * @param receiver net device of the receiver
         * @param SimulationTime simulation time in double
         * 
         */
        bool 
        Initialize(NetDeviceContainer sender,
                   NetDeviceContainer receiver,
                   double SimulationTime);

        /**
         * @brief Sniff all the frames been transmitted
         * @param packet the packet
         * @param frequency frequency of the channel
         * @param txvector txvector of the PPDU
         * @param mpdu_info the information of the PPDU
         * @param sta_id the id of the station
         * 
         */
        void 
        Sniff_tx_packet_begin(Ptr<const Packet> packet,
                          uint16_t frequency,
                          WifiTxVector txvector,
                          MpduInfo mpdu_info,
                          uint16_t sta_id);
        
        /**
         * @brief Sniff all the frames been received
         * @param packet the packet
         * @param frequency of the channel
         * @param txvector txvector of the PPDU
         * @param mpdu_info the information of the PPDU
         * @param noise the noise of the receiver
         * @param sta_id the id of the station
         */
        void 
        Sniff_rx_packet_begin(Ptr<const Packet> packet,
                          uint16_t frequency,
                          WifiTxVector txvector,
                          MpduInfo mpdu_info,
                          SignalNoiseDbm noise,
                          uint16_t sta_id);

        /**
         * @brief Sniff all the frames been dropped
         * 
         * @param packet the packet
         * @param drop_reason the reason of the drop during the reception
         */
        void
        Sniff_drop_packet_phy(Ptr<const Packet> packet, 
                              WifiPhyRxfailureReason drop_reason);                    
        /**
         * @brief Sniff all the frames been dropped
         * @param ppdu the WifiPpdu
         * @param drop_reason the reason of the drop during the reception
         */
        void 
        Sniff_drop_ppdu_phy(Ptr<const WifiPpdu> ppdu, 
                            WifiPhyRxfailureReason drop_reason);
        
        /**
         * @brief Sniff all the frames been transmitted
         * 
         * @param psdu_map the Psdu information is included
         * @param txvector the information of tx
         * @param tx_power the tx power
         */
        void 
        Sniff_tx_psdu_begin(WifiConstPsduMap psdu_map, 
                          WifiTxVector txvector, 
                          double tx_power);
        
        /**
         * @brief Sniff the MAC header of the PPDU
         * 
         * @param wifi_mac_header the MAC header of the PPDU
         * @param tx_vector the tx vector of the PPDU
         * @param time ?
         */
        void 
        Sniff_mac_header(const WifiMacHeader& wifi_mac_header, 
                              const WifiTxVector& tx_vector, 
                              Time time);
        
        /**
         * @brief Sniff all the frames been transmitted
         * @param packet the packet
         * @param frequency of the channel
         * @param txvector txvector of the PPDU
         * @param mpdu_info the information of the PPDU
         * @param sta_id the id of the station
         */
        void 
        Sniff_tx_all_packets(Ptr<const Packet> packet,
                   uint16_t frequency,
                   WifiTxVector txvector,
                   MpduInfo mpdu_info,
                   uint16_t sta_id);
        
        /**
         * @brief Sniff all the ppdu been sent
         * 
         * @param ppdu 
         * @param tx_vector 
         */
        void 
        Sniff_ppdu_begin(Ptr<const WifiPpdu> ppdu, 
                         const WifiTxVector& tx_vector);

        void 
        Set_simulation_time(double simulation_time);
        private:
        bool m_initialized;
        double m_simulation_time;
    };
}
#endif 