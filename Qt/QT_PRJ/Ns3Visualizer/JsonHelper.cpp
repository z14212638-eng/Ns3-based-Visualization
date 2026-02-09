#include "JsonHelper.h"
#include <QDateTime>


double get_true_random_double(double min, double max)
{
    std::random_device rd;
    std::uniform_real_distribution<> dis(min, max);
    return dis(rd);
}

Standard_MAP get_standard_from_string(const std::string &gi_str)
{
    auto it = standard_map.find(gi_str);
    if (it == standard_map.end())
    {
        return Standard_MAP::k80211ax;
    }
    return it->second;
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

void JsonHelper::ensureRunDirectories()
{
    if (run_dir_initialized)
        return;

    const QString timestamp = QDateTime::currentDateTime().toString("yy_M_d_HHmm");
    Run_dir = Base_dir + "Designed_" + timestamp + "/";

    const QString apDir = Run_dir + "ApConfigJson";
    const QString staDir = Run_dir + "StaConfigJson";
    const QString generalDir = Run_dir + "GeneralJson";

    QDir().mkpath(apDir);
    QDir().mkpath(staDir);
    QDir().mkpath(generalDir);

    Ap_file_path = apDir + "/Ap_";
    Sta_file_path = staDir + "/Sta_";
    General_file_path = generalDir + "/";

    run_dir_initialized = true;
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
    jsonObj["Guard_interval"] = ap->GI;
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
        Flow["Destination"] = flow.Destination;
        Flow["StartTime"] = flow.StartTime;
        Flow["EndTime"] = flow.EndTime;
        Flow["Tos"] = flow.Tos;
        
        // 流量类型
        QString flowTypeStr;
        switch (flow.flowType) {
            case TrafficConfig::OnOff:
            {
                flowTypeStr = "OnOff";
                Flow["DataRate"] = flow.dataRate;
                Flow["PacketSize"] = flow.packetSize;
                Flow["OntimeType"] = flow.ontimeType;
                Flow["OfftimeType"] = flow.offtimeType;
                Flow["MaxBytes"] = flow.maxBytes;
                
                // OnTime 参数
                QJsonObject ontimeParams;
                for (auto it = flow.ontimeParams.begin(); it != flow.ontimeParams.end(); ++it) {
                    ontimeParams[it.key()] = it.value();
                }
                Flow["OntimeParams"] = ontimeParams;
                
                // OffTime 参数
                QJsonObject offtimeParams;
                for (auto it = flow.offtimeParams.begin(); it != flow.offtimeParams.end(); ++it) {
                    offtimeParams[it.key()] = it.value();
                }
                Flow["OfftimeParams"] = offtimeParams;
                break;
            }
                
            case TrafficConfig::CBR:
            {
                flowTypeStr = "CBR";
                Flow["PacketSize"] = flow.packetSize;
                Flow["Interval"] = flow.interval;
                Flow["MaxPackets"] = flow.maxPackets;
                break;
            }
                
            case TrafficConfig::Bulk:
            {
                flowTypeStr = "Bulk";
                Flow["MaxBytes"] = flow.maxBytes;
                break;
            }
        }
        Flow["FlowType"] = flowTypeStr;
        
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
    jsonObj["Guard_interval"] = sta->GI;
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
        Flow["Destination"] = flow.Destination;
        Flow["StartTime"] = flow.StartTime;
        Flow["EndTime"] = flow.EndTime;
        Flow["Tos"] = flow.Tos;
        
        // 流量类型
        QString flowTypeStr;
        switch (flow.flowType) {
            case TrafficConfig::OnOff:
            {
                flowTypeStr = "OnOff";
                Flow["DataRate"] = flow.dataRate;
                Flow["PacketSize"] = flow.packetSize;
                Flow["OntimeType"] = flow.ontimeType;
                Flow["OfftimeType"] = flow.offtimeType;
                Flow["MaxBytes"] = flow.maxBytes;
                
                // OnTime 参数
                QJsonObject ontimeParams;
                for (auto it = flow.ontimeParams.begin(); it != flow.ontimeParams.end(); ++it) {
                    ontimeParams[it.key()] = it.value();
                }
                Flow["OntimeParams"] = ontimeParams;
                
                // OffTime 参数
                QJsonObject offtimeParams;
                for (auto it = flow.offtimeParams.begin(); it != flow.offtimeParams.end(); ++it) {
                    offtimeParams[it.key()] = it.value();
                }
                Flow["OfftimeParams"] = offtimeParams;
                break;
            }
                
            case TrafficConfig::CBR:
            {
                flowTypeStr = "CBR";
                Flow["PacketSize"] = flow.packetSize;
                Flow["Interval"] = flow.interval;
                Flow["MaxPackets"] = flow.maxPackets;
                break;
            }
                
            case TrafficConfig::Bulk:
            {
                flowTypeStr = "Bulk";
                Flow["MaxBytes"] = flow.maxBytes;
                break;
            }
        }
        Flow["FlowType"] = flowTypeStr;
        
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

void JsonHelper::reset()
{
    qDebug() << "[JsonHelper] reset()";

    // 1️⃣ 清空 building json
    m_building_config = QJsonObject();

    // 2️⃣ 释放动态分配的 json（避免泄漏）
    if (m_sta_config)
    {
        delete m_sta_config;
        m_sta_config = nullptr;
    }

    if (m_ap_config)
    {
        delete m_ap_config;
        m_ap_config = nullptr;
    }

    // 3️⃣ 清空配置列表
    m_sta_config_list.clear();
    m_ap_config_list.clear();

    // 4️⃣ 重建 building 配置（而不是 clear）
    m_building.reset();
    m_building = std::make_shared<BuildingConfig>();

    // 5️⃣ （可选）初始化 building json 的基础字段
    m_building_config["Sta_num"] = 0;
    m_building_config["Ap_num"]  = 0;
    m_building_config["Sta_pos_list"] = QJsonArray();
    m_building_config["Ap_pos_list"]  = QJsonArray();

    // 6️⃣ reset run directory (next run will create a new folder)
    run_dir_initialized = false;
    Run_dir.clear();
    Ap_file_path.clear();
    Sta_file_path.clear();
    General_file_path.clear();
    
    // 7️⃣ reset project config
    m_project_config = ProjectConfig();
}

bool JsonHelper::SaveProjectConfig(const QString &projectFilePath, const QString &projectName)
{
    QJsonObject projectObj;
    
    // Basic project info
    projectObj["project_name"] = projectName.isEmpty() ? "Untitled_Project" : projectName;
    projectObj["ns3_directory"] = Base_dir;
    projectObj["run_directory"] = Run_dir;
    
    // Config folders
    projectObj["ap_config_folder"] = Run_dir + "ApConfigJson";
    projectObj["sta_config_folder"] = Run_dir + "StaConfigJson";
    projectObj["general_config_folder"] = Run_dir + "GeneralJson";
    
    // Config files list
    QJsonArray apFiles;
    for (int i = 0; i < m_ap_config_list.size(); ++i) {
        apFiles.append(QString("Ap_%1.json").arg(i));
    }
    projectObj["ap_config_files"] = apFiles;
    
    QJsonArray staFiles;
    for (int i = 0; i < m_sta_config_list.size(); ++i) {
        staFiles.append(QString("Sta_%1.json").arg(i));
    }
    projectObj["sta_config_files"] = staFiles;
    
    projectObj["general_config_file"] = "general.json";
    
    // Timestamps
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    projectObj["created_time"] = currentTime;
    projectObj["last_modified"] = currentTime;
    
    // Statistics
    projectObj["ap_count"] = m_ap_config_list.size();
    projectObj["sta_count"] = m_sta_config_list.size();
    
    // Save to file
    bool success = SaveJsonObjToRoute(projectObj, projectFilePath);
    
    if (success) {
        qDebug() << "Project configuration saved to:" << projectFilePath;
        
        // Update internal project config
        m_project_config.project_name = projectName;
        m_project_config.ns3_directory = Base_dir;
        m_project_config.run_directory = Run_dir;
        m_project_config.ap_config_folder = Run_dir + "ApConfigJson";
        m_project_config.sta_config_folder = Run_dir + "StaConfigJson";
        m_project_config.general_config_folder = Run_dir + "GeneralJson";
        m_project_config.created_time = currentTime;
        m_project_config.last_modified = currentTime;
    }
    
    return success;
}

bool JsonHelper::LoadProjectConfig(const QString &projectFilePath)
{
    QFile file(projectFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open project file:" << projectFilePath;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse project file:" << parseError.errorString();
        return false;
    }
    
    if (!doc.isObject()) {
        qWarning() << "Invalid project file format";
        return false;
    }
    
    QJsonObject projectObj = doc.object();
    
    // Get the project directory (where the .nsproj file is located)
    QFileInfo fileInfo(projectFilePath);
    QString projectDir = fileInfo.absolutePath();
    
    // Load project configuration
    m_project_config.project_name = projectObj["project_name"].toString();
    m_project_config.work_directory = projectObj["work_directory"].toString();
    m_project_config.ns3_directory = projectObj["ns3_directory"].toString();
    m_project_config.run_directory = projectObj["run_directory"].toString();
    
    // Config folders (stored as relative paths, convert to absolute)
    QString apConfigFolderRel = projectObj["ap_config_folder"].toString();
    QString staConfigFolderRel = projectObj["sta_config_folder"].toString();
    QString generalConfigFolderRel = projectObj["general_config_folder"].toString();
    
    m_project_config.ap_config_folder = projectDir + "/" + apConfigFolderRel;
    m_project_config.sta_config_folder = projectDir + "/" + staConfigFolderRel;
    m_project_config.general_config_folder = projectDir + "/" + generalConfigFolderRel;
    m_project_config.general_config_file = projectObj["general_config_file"].toString();
    m_project_config.created_time = projectObj["created_time"].toString();
    m_project_config.last_modified = projectObj["last_modified"].toString();
    
    // Load file lists
    m_project_config.ap_config_files.clear();
    QJsonArray apFiles = projectObj["ap_config_files"].toArray();
    for (const auto &file : apFiles) {
        m_project_config.ap_config_files.append(file.toString());
    }
    
    m_project_config.sta_config_files.clear();
    QJsonArray staFiles = projectObj["sta_config_files"].toArray();
    for (const auto &file : staFiles) {
        m_project_config.sta_config_files.append(file.toString());
    }
    
    // Update internal paths
    Base_dir = m_project_config.ns3_directory;
    Run_dir = projectDir + "/";  // Use project directory as run directory
    Ap_file_path = m_project_config.ap_config_folder + "/Ap_";
    Sta_file_path = m_project_config.sta_config_folder + "/Sta_";
    General_file_path = m_project_config.general_config_folder + "/";
    run_dir_initialized = true;
    
    qDebug() << "Project configuration loaded from:" << projectFilePath;
    qDebug() << "Project directory:" << projectDir;
    qDebug() << "Project name:" << m_project_config.project_name;
    qDebug() << "AP count:" << m_project_config.ap_config_files.size();
    qDebug() << "STA count:" << m_project_config.sta_config_files.size();
    
    // Now load the actual configuration files
    m_ap_config_list.clear();
    m_sta_config_list.clear();
    
    // Load AP configurations
    for (const QString &apFile : m_project_config.ap_config_files) {
        QString fullPath = m_project_config.ap_config_folder + "/" + apFile;
        QFile apFileObj(fullPath);
        if (apFileObj.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument apDoc = QJsonDocument::fromJson(apFileObj.readAll());
            if (apDoc.isObject()) {
                m_ap_config_list.append(apDoc.object());
                qDebug() << "Loaded AP config:" << fullPath;
            }
            apFileObj.close();
        } else {
            qWarning() << "Failed to open AP config file:" << fullPath;
        }
    }
    
    // Load STA configurations
    for (const QString &staFile : m_project_config.sta_config_files) {
        QString fullPath = m_project_config.sta_config_folder + "/" + staFile;
        QFile staFileObj(fullPath);
        if (staFileObj.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument staDoc = QJsonDocument::fromJson(staFileObj.readAll());
            if (staDoc.isObject()) {
                m_sta_config_list.append(staDoc.object());
                qDebug() << "Loaded STA config:" << fullPath;
            }
            staFileObj.close();
        } else {
            qWarning() << "Failed to open STA config file:" << fullPath;
        }
    }
    
    // Load general configuration
    QString generalPath = m_project_config.general_config_folder + "/" + m_project_config.general_config_file;
    QFile generalFile(generalPath);
    if (generalFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument generalDoc = QJsonDocument::fromJson(generalFile.readAll());
        if (generalDoc.isObject()) {
            m_building_config = generalDoc.object();
            qDebug() << "Loaded general config:" << generalPath;
        }
        generalFile.close();
    } else {
        qWarning() << "Failed to open general config file:" << generalPath;
    }
    
    return true;
}

ProjectConfig JsonHelper::GetCurrentProjectConfig() const
{
    return m_project_config;
}
