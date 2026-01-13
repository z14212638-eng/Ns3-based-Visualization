#include "JsonHelper.h"

double get_true_random_double(double min, double max)
{
    std::random_device rd;
    std::uniform_real_distribution<> dis(min, max);
    return dis(rd);
}

bool JsonHelper::SaveJsonObjToRoute(const QJsonObject jsonObj, const QString filePath)
{

    QJsonDocument jsonDoc(jsonObj);

    QFileInfo fileInfo(filePath);
    qDebug() << "Absolute file path:" << fileInfo.absoluteFilePath();
    QDir parentDir = fileInfo.absoluteDir();
    if (!parentDir.exists())
    {
        if (!parentDir.mkpath("."))
        {
            qWarning() << "Failed to create directory:" << parentDir.path();
            return false;
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool JsonHelper::SetApToJson(const Ap *ap, qint8 id)
{
    QJsonObject jsonObj;

    // Position
    jsonObj["Position"] = QJsonArray{ap->m_position[0],
                                     ap->m_position[1],
                                     ap->m_position[2]};
    jsonObj["Id"] = id;

    // Add it to the building config
    int apNum = m_building_config.value("Ap_num").toInt();
    m_building_config["Ap_num"] = apNum + 1;

    QJsonArray apPosList;
    if (m_building_config.contains("Ap_pos_list") && m_building_config["Ap_pos_list"].isArray())
    {
        apPosList = m_building_config["Ap_pos_list"].toArray();
    }

    QJsonObject apEntry;
    apEntry["id"] = id;

    QJsonArray position;
    position.append(ap->m_position[0]);
    position.append(ap->m_position[1]);
    position.append(ap->m_position[2]);
    apEntry["pos"] = position;

    apPosList.append(apEntry);

    m_building_config["Ap_pos_list"] = apPosList;

    // Mobility configuration
    QJsonObject mobilityObj;
    mobilityObj["set"] = ap->Mobility;
    mobilityObj["model_type"] = ap->Mobility_model;
    mobilityObj["boundaries"] = QJsonArray{ap->boundaries[0],
                                           ap->boundaries[1],
                                           ap->boundaries[2],
                                           ap->boundaries[3]};
    mobilityObj["mode"] = ap->mode;
    mobilityObj["time_change_interval"] = ap->time_change_interval;
    mobilityObj["distance_change_interval"] = ap->distance_change_interval;
    mobilityObj["velocity"] = ap->random_velocity;
    jsonObj["Mobility"] = mobilityObj;

    // Basic network configuration
    jsonObj["Channel_number"] = ap->channel_number;
    jsonObj["Frequency"] = ap->Frequency;
    jsonObj["Bandwidth"] = ap->bandwidth;
    jsonObj["Tx_power"] = ap->TxPower;
    jsonObj["Ssid"] = ap->Ssid;
    jsonObj["Phy_model"] = ap->Phy_model;
    jsonObj["Standard"] = ap->Standard;
    jsonObj["Slot"] = ap->Slot;
    jsonObj["Sifs"] = ap->Sifs;
    jsonObj["RxSensitivity"] = ap->RxSensitivity;
    jsonObj["CcaEdThreshold"] = ap->CcaThreshold;
    jsonObj["CcaSensitivity"] = ap->CcaSensitivity;

    // Beacon configuration
    QJsonObject beaconObj;
    beaconObj["set"] = ap->Beacon;
    beaconObj["BeaconInterval"] = ap->Beacon_interval;
    beaconObj["Beacon_Rate"] = ap->Beacon_Rate;
    beaconObj["EnableBeaconJitter"] = ap->EnableBeaconJitter;
    jsonObj["Beacon"] = beaconObj;

    // RTS/CTS configuration
    QJsonObject rtsCtsObj;
    rtsCtsObj["set"] = ap->RtsCts;
    rtsCtsObj["Threshold"] = ap->RtsCts_Threshold;
    jsonObj["Rts_Cts"] = rtsCtsObj;

    jsonObj["Rate_ctrl_algo"] = ap->Rate_ctr_algo;
    jsonObj["TxQueue"] = ap->TxQueue;

    // QoS configuration
    QJsonObject qosObj;
    qosObj["Qos_support"] = ap->Qos;
    qosObj["Edca_choose"] = ap->Edca;

    // EDCA parameters
    QJsonObject edcaParamsObj;
    QJsonObject acVoObj;
    acVoObj["CWmin"] = ap->AC_VO_cwmin;
    acVoObj["CWmax"] = ap->AC_VO_cwmax;
    acVoObj["AIFSN"] = ap->AC_VO_AIFSN;
    acVoObj["TXOPLimit"] = ap->AC_VO_TXOP_LIMIT;
    edcaParamsObj["AC_VO"] = acVoObj;

    QJsonObject acViObj;
    acViObj["CWmin"] = ap->AC_VI_cwmin;
    acViObj["CWmax"] = ap->AC_VI_cwmax;
    acViObj["AIFSN"] = ap->AC_VI_AIFSN;
    acViObj["TXOPLimit"] = ap->AC_VI_TXOP_LIMIT;
    edcaParamsObj["AC_VI"] = acViObj;

    QJsonObject acBeObj;
    acBeObj["CWmin"] = ap->AC_BE_cwmin;
    acBeObj["CWmax"] = ap->AC_BE_cwmax;
    acBeObj["AIFSN"] = ap->AC_BE_AIFSN;
    acBeObj["TXOPLimit"] = ap->AC_BE_TXOP_LIMIT;
    edcaParamsObj["AC_BE"] = acBeObj;

    QJsonObject acBkObj;
    acBkObj["CWmin"] = ap->AC_BK_cwmin;
    acBkObj["CWmax"] = ap->AC_BK_cwmax;
    acBkObj["AIFSN"] = ap->AC_BK_AIFSN;
    acBkObj["TXOPLimit"] = ap->AC_BK_TXOP_LIMIT;
    edcaParamsObj["AC_BK"] = acBkObj;

    qosObj["Edca_params"] = edcaParamsObj;

    // Traffic Configuration
    QJsonObject Traffic;
    QJsonArray Flows;
    qDebug() << "ap->Traffic_list.size():" << ap->Traffic_list.size();
    for (const auto &flow : ap->Traffic_list)
    {
        QJsonObject Flow;
        Flow["FlowId"] = flow.Flow_id;
        Flow["Protocol"] = flow.Protocol;
        Flow["Direction"] = flow.Direction;
        Flow["StartTime"] = flow.StartTime;
        Flow["EndTime"] = flow.EndTime;
        QJsonArray EDCA_Traffic;

        // AC_VI
        QJsonObject one_edca_vi;
        auto viTraffic = std::dynamic_pointer_cast<AC_VI_Traffic>(flow.m_edca[AcType::VI]);
        one_edca_vi["type"] = viTraffic->Type;
        one_edca_vi["enabled"] = viTraffic->enabled;
        one_edca_vi["trafficType"] = viTraffic->trafficType;
        one_edca_vi["packetSize"] = viTraffic->packetSize;
        one_edca_vi["meanDataRate"] = viTraffic->meanDataRate;
        one_edca_vi["peakDataRate"] = viTraffic->peakDataRate;
        EDCA_Traffic.append(one_edca_vi);

        // AC_VO
        QJsonObject one_edca_vo;
        auto voTraffic = std::dynamic_pointer_cast<AC_VO_Traffic>(flow.m_edca[AcType::VO]);
        one_edca_vo["type"] = voTraffic->Type;
        one_edca_vo["enabled"] = voTraffic->enabled;
        one_edca_vo["trafficType"] = voTraffic->trafficType;
        one_edca_vo["packetSize"] = voTraffic->packetSize;
        one_edca_vo["interval"] = voTraffic->interval;
        EDCA_Traffic.append(one_edca_vo);

        // AC_BE
        QJsonObject one_edca_be;
        auto beTraffic = std::dynamic_pointer_cast<AC_BE_Traffic>(flow.m_edca[AcType::BE]);
        one_edca_be["type"] = beTraffic->Type;
        one_edca_be["enabled"] = beTraffic->enabled;
        one_edca_be["trafficType"] = beTraffic->trafficType;
        one_edca_be["packetSize"] = beTraffic->packetSize;
        one_edca_be["DataRate"] = beTraffic->DataRate;
        EDCA_Traffic.append(one_edca_be);

        // AC_BK
        QJsonObject one_edca_bk;
        auto bkTraffic = std::dynamic_pointer_cast<AC_BK_Traffic>(flow.m_edca[AcType::BK]);
        one_edca_bk["type"] = bkTraffic->Type;
        one_edca_bk["enabled"] = bkTraffic->enabled;
        one_edca_bk["trafficType"] = bkTraffic->trafficType;
        one_edca_bk["packetSize"] = bkTraffic->packetSize;
        one_edca_bk["DataRate"] = bkTraffic->DataRate;
        EDCA_Traffic.append(one_edca_bk);

        Flow["EDCA_Traffic"] = EDCA_Traffic;
        Flows.append(Flow);
    }
    Traffic["Flows"] = Flows;
    jsonObj["Traffic"] = Traffic;

    // MSDU Aggregation
    QJsonObject msduAggObj;
    msduAggObj["set"] = ap->Msdu_aggregation;
    msduAggObj["type"] = ap->AMsdu_type;
    msduAggObj["MaxAmsduSize"] = ap->MaxAMsduSize;
    qosObj["Msdu_Aggregation"] = msduAggObj;

    // MPDU Aggregation
    QJsonObject mpduAggObj;
    mpduAggObj["set"] = ap->Mpdu_aggregation;
    mpduAggObj["type"] = ap->AMpdu_type;
    mpduAggObj["MaxAmpduSize"] = ap->MaxAMpduSize;
    mpduAggObj["Density"] = ap->Density;
    qosObj["Mpdu_Aggregation"] = mpduAggObj;

    jsonObj["Qos"] = qosObj;

    // Antenna configuration
    QJsonObject antennaObj;
    antennaObj["set"] = !ap->Antenna_list.isEmpty();
    QJsonArray antennasArray;
    for (const auto &antenna : ap->Antenna_list)
    {
        if (antenna)
        {
            QJsonObject antennaItem;
            antennaItem["type"] = antenna->Antenna_type;
            antennaItem["MaxGain"] = antenna->MaxGain;
            antennaItem["Beamwidth"] = antenna->Beamwidth;
            antennasArray.append(antennaItem);
        }
    }
    antennaObj["Antennas"] = antennasArray;
    jsonObj["Antenna"] = antennaObj;

    // Store the configuration
    m_ap_config = new QJsonObject(jsonObj);
    m_ap_config_list.append(jsonObj);
    std::cout << "m_ap_config_list  appended  ,number:" << m_ap_config_list.size() << std::endl;
    return true;
}

bool JsonHelper::SetStaToJson(const Sta *sta, qint8 id)
{
    QJsonObject jsonObj;

    // Position
    jsonObj["Position"] = QJsonArray{sta->m_position[0],
                                     sta->m_position[1],
                                     sta->m_position[2]};
    jsonObj["Id"] = id;

    // Add it to the building config
    int staNum = m_building_config.value("Sta_num").toInt();
    m_building_config["Sta_num"] = staNum + 1;

    QJsonArray staPosList;
    if (m_building_config.contains("Sta_pos_list") && m_building_config["Sta_pos_list"].isArray())
    {
        staPosList = m_building_config["Sta_pos_list"].toArray();
    }

    QJsonObject staEntry;
    staEntry["id"] = id;

    QJsonArray position;
    position.append(sta->m_position[0]);
    position.append(sta->m_position[1]);
    position.append(sta->m_position[2]);
    staEntry["pos"] = position;

    staPosList.append(staEntry);

    m_building_config["Sta_pos_list"] = staPosList;

    // Mobility configuration
    QJsonObject mobilityObj;
    mobilityObj["set"] = sta->Mobility;
    mobilityObj["model_type"] = sta->Mobility_model;
    mobilityObj["boundaries"] = QJsonArray{sta->boundaries[0],
                                           sta->boundaries[1],
                                           sta->boundaries[2],
                                           sta->boundaries[3]};
    mobilityObj["mode"] = sta->mode;
    mobilityObj["time_change_interval"] = sta->time_change_interval;
    mobilityObj["distance_change_interval"] = sta->distance_change_interval;
    mobilityObj["velocity"] = sta->random_velocity;
    jsonObj["Mobility"] = mobilityObj;

    // Basic network configuration
    jsonObj["Channel_number"] = sta->channel_number;
    jsonObj["Frequency"] = sta->Frequency;
    jsonObj["Bandwidth"] = sta->bandwidth;
    jsonObj["Tx_power"] = sta->TxPower;
    jsonObj["Ssid"] = sta->Ssid;
    jsonObj["Phy_model"] = sta->Phy_model;
    jsonObj["Standard"] = sta->Standard;
    jsonObj["MaxMissedBeacons"] = sta->MaxMissedBeacons;
    jsonObj["ProbeRequestTimeout"] = sta->ProbeRequestTimeout;
    jsonObj["EnableAssocFailRetry"] = sta->EnableAssocFailRetry;
    jsonObj["ActiveProbing"] = sta->active_probing;  

    // RTS/CTS configuration
    QJsonObject rtsCtsObj;
    rtsCtsObj["set"] = sta->RtsCts;
    rtsCtsObj["Threshold"] = sta->RtsCts_Threshold;
    jsonObj["Rts_Cts"] = rtsCtsObj;

    jsonObj["Rate_ctrl_algo"] = sta->Rate_ctr_algo;
    jsonObj["TxQueue"] = sta->TxQueue;

    // QoS configuration
    QJsonObject qosObj;
    qosObj["Qos_support"] = sta->Qos;
    qosObj["Edca_choose"] = sta->Edca;

    // EDCA parameters
    QJsonObject edcaParamsObj;
    QJsonObject acVoObj;
    acVoObj["CWmin"] = sta->AC_VO_cwmin;
    acVoObj["CWmax"] = sta->AC_VO_cwmax;
    acVoObj["AIFSN"] = sta->AC_VO_AIFSN;
    acVoObj["TXOPLimit"] = sta->AC_VO_TXOP_LIMIT;
    edcaParamsObj["AC_VO"] = acVoObj;

    QJsonObject acViObj;
    acViObj["CWmin"] = sta->AC_VI_cwmin;
    acViObj["CWmax"] = sta->AC_VI_cwmax;
    acViObj["AIFSN"] = sta->AC_VI_AIFSN;
    acViObj["TXOPLimit"] = sta->AC_VI_TXOP_LIMIT;
    edcaParamsObj["AC_VI"] = acViObj;

    QJsonObject acBeObj;
    acBeObj["CWmin"] = sta->AC_BE_cwmin;
    acBeObj["CWmax"] = sta->AC_BE_cwmax;
    acBeObj["AIFSN"] = sta->AC_BE_AIFSN;
    acBeObj["TXOPLimit"] = sta->AC_BE_TXOP_LIMIT;
    edcaParamsObj["AC_BE"] = acBeObj;

    QJsonObject acBkObj;
    acBkObj["CWmin"] = sta->AC_BK_cwmin;
    acBkObj["CWmax"] = sta->AC_BK_cwmax;
    acBkObj["AIFSN"] = sta->AC_BK_AIFSN;
    acBkObj["TXOPLimit"] = sta->AC_BK_TXOP_LIMIT;
    edcaParamsObj["AC_BK"] = acBkObj;

    qosObj["Edca_params"] = edcaParamsObj;

    // Traffic Configuration
    QJsonObject Traffic;
    QJsonArray Flows;
    qDebug() << "sta->Traffic_list.size():" << sta->Traffic_list.size();
    for (const auto &flow : sta->Traffic_list)
    {
        QJsonObject Flow;
        Flow["FlowId"] = flow.Flow_id;
        Flow["Protocol"] = flow.Protocol;
        Flow["Direction"] = flow.Direction;
        Flow["StartTime"] = flow.StartTime;
        Flow["EndTime"] = flow.EndTime;
        QJsonArray EDCA_Traffic;

        // AC_VI
        QJsonObject one_edca_vi;
        auto viTraffic = std::dynamic_pointer_cast<AC_VI_Traffic>(flow.m_edca[AcType::VI]);
        one_edca_vi["type"] = viTraffic->Type;
        one_edca_vi["enabled"] = viTraffic->enabled;
        one_edca_vi["trafficType"] = viTraffic->trafficType;
        one_edca_vi["packetSize"] = viTraffic->packetSize;
        one_edca_vi["meanDataRate"] = viTraffic->meanDataRate;
        one_edca_vi["peakDataRate"] = viTraffic->peakDataRate;
        EDCA_Traffic.append(one_edca_vi);

        // AC_VO
        QJsonObject one_edca_vo;
        auto voTraffic = std::dynamic_pointer_cast<AC_VO_Traffic>(flow.m_edca[AcType::VO]);
        one_edca_vo["type"] = voTraffic->Type;
        one_edca_vo["enabled"] = voTraffic->enabled;
        one_edca_vo["trafficType"] = voTraffic->trafficType;
        one_edca_vo["packetSize"] = voTraffic->packetSize;
        one_edca_vo["interval"] = voTraffic->interval;
        EDCA_Traffic.append(one_edca_vo);

        // AC_BE
        QJsonObject one_edca_be;
        auto beTraffic = std::dynamic_pointer_cast<AC_BE_Traffic>(flow.m_edca[AcType::BE]);
        one_edca_be["type"] = beTraffic->Type;
        one_edca_be["enabled"] = beTraffic->enabled;
        one_edca_be["trafficType"] = beTraffic->trafficType;
        one_edca_be["packetSize"] = beTraffic->packetSize;
        one_edca_be["DataRate"] = beTraffic->DataRate;
        EDCA_Traffic.append(one_edca_be);

        // AC_BK
        QJsonObject one_edca_bk;
        auto bkTraffic = std::dynamic_pointer_cast<AC_BK_Traffic>(flow.m_edca[AcType::BK]);
        one_edca_bk["type"] = bkTraffic->Type;
        one_edca_bk["enabled"] = bkTraffic->enabled;
        one_edca_bk["trafficType"] = bkTraffic->trafficType;
        one_edca_bk["packetSize"] = bkTraffic->packetSize;
        one_edca_bk["DataRate"] = bkTraffic->DataRate;
        EDCA_Traffic.append(one_edca_bk);

        Flow["EDCA_Traffic"] = EDCA_Traffic;
        Flows.append(Flow);
    }
    Traffic["Flows"] = Flows;
    jsonObj["Traffic"] = Traffic;

    // MSDU Aggregation
    QJsonObject msduAggObj;
    msduAggObj["set"] = sta->Msdu_aggregation;
    msduAggObj["type"] = sta->AMsdu_type;
    msduAggObj["MaxAmsduSize"] = sta->MaxAMsduSize;
    qosObj["Msdu_Aggregation"] = msduAggObj;

    // MPDU Aggregation
    QJsonObject mpduAggObj;
    mpduAggObj["set"] = sta->Mpdu_aggregation;
    mpduAggObj["type"] = sta->AMpdu_type;
    mpduAggObj["MaxAmpduSize"] = sta->MaxAMpduSize;
    mpduAggObj["Density"] = sta->Density;
    qosObj["Mpdu_Aggregation"] = mpduAggObj;
    

    jsonObj["Qos"] = qosObj;

    // Antenna configuration
    QJsonObject antennaObj;
    antennaObj["set"] = !sta->Antenna_list.isEmpty();
    QJsonArray antennasArray;
    for (const auto &antenna : sta->Antenna_list)
    {
        if (antenna)
        {
            QJsonObject antennaItem;
            antennaItem["type"] = antenna->Antenna_type;
            antennaItem["MaxGain"] = antenna->MaxGain;
            antennaItem["Beamwidth"] = antenna->Beamwidth;
            antennasArray.append(antennaItem);
        }
    }
    antennaObj["Antennas"] = antennasArray;
    jsonObj["Antenna"] = antennaObj;

    // Store the configuration
    m_sta_config = new QJsonObject(jsonObj);
    m_sta_config_list.append(jsonObj);
    std::cout << "m_sta_config_list  appended  ,number:" << m_sta_config_list.size() << std::endl;
    return true;
}