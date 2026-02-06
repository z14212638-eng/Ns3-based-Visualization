#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <iostream>
#include <random>
#include <memory>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QJsonParseError>
#include <QLoggingCategory>
#include <QObject>

// This class is used to save the configuration of the network to a JSON file.

enum class AcType
{
    BE,
    BK,
    VI,
    VO
};

enum class Standard_MAP
{
    k80211a,
    k80211b,
    k80211g,
    k80211n,
    k80211ac,
    k80211ax
};

static const std::map<std::string, Standard_MAP> standard_map = {
    {"802.11a", Standard_MAP::k80211a},
    {"802.11b", Standard_MAP::k80211b},
    {"802.11g", Standard_MAP::k80211g},
    {"802.11n", Standard_MAP::k80211n},
    {"802.11ac", Standard_MAP::k80211ac},
    {"802.11ax", Standard_MAP::k80211ax}
};

Standard_MAP get_standard_from_string(const std::string &);

struct Antenna_Config
{
    inline Antenna_Config() = default;
    inline Antenna_Config(QString type = "Isotropic", qint16 maxgain = 20, qint16 beamwidth = 30)
    {
        Antenna_type = type;
        MaxGain = maxgain;
        Beamwidth = beamwidth;
    }
    QString Antenna_type = "Isotropic";
    qint16 MaxGain = 20;
    qint16 Beamwidth = 30;
};

class EDCA_Traffic_Config
{
public:
    EDCA_Traffic_Config() = default;
    virtual ~EDCA_Traffic_Config() = default;
};

class AC_VI_Traffic : public EDCA_Traffic_Config
{
public:
    AC_VI_Traffic() = default;
    ~AC_VI_Traffic() = default;
    QString Type = "AC_VI";
    bool enabled = false;
    QString trafficType = "CBR";
    qint32 packetSize = 1200;
    qint32 meanDataRate = 0;
    qint32 peakDataRate = 0;
};

class AC_VO_Traffic : public EDCA_Traffic_Config
{
public:
    AC_VO_Traffic() = default;
    ~AC_VO_Traffic() = default;
    QString Type = "AC_VO";
    bool enabled = false;
    QString trafficType = "CBR";
    qint32 packetSize = 0;
    double interval = 20;
};

class AC_BE_Traffic : public EDCA_Traffic_Config
{
public:
    AC_BE_Traffic() = default;
    ~AC_BE_Traffic() = default;
    QString Type = "AC_BE";
    bool enabled = false;
    QString trafficType = "CBR";
    qint32 packetSize = 0;
    qint32 DataRate = 0;
};

class AC_BK_Traffic : public EDCA_Traffic_Config
{
public:
    AC_BK_Traffic() = default;
    ~AC_BK_Traffic() = default;
    QString Type = "AC_BK";
    bool enabled = false;
    QString trafficType = "CBR";
    qint32 packetSize = 0;
    qint32 DataRate = 0;
};

class TrafficConfig
{
public:
    TrafficConfig()
    {
        m_edca[AcType::BE] = std::make_shared<AC_BE_Traffic>();
        m_edca[AcType::BK] = std::make_shared<AC_BK_Traffic>();
        m_edca[AcType::VI] = std::make_shared<AC_VI_Traffic>();
        m_edca[AcType::VO] = std::make_shared<AC_VO_Traffic>();
    }
    ~TrafficConfig() = default;
    QString Flow_id = "";
    QString Protocol = "UDP";
    QString Direction = "uplink";
    qint32 StartTime = 0;
    qint32 EndTime = 0;
    QMap<AcType, std::shared_ptr<EDCA_Traffic_Config>> m_edca;
};

class Ap
{
public:
    Ap() = default;
    ~Ap() = default;
    QVector<double> m_position = {0, 0, 0};
    qint16 Id = 0;
    // Mobility
    bool Mobility = false;
    QString Mobility_model = "Random Mobility Model";
    QVector<double> boundaries = {0, 0, 0, 0};
    QString mode = "Time";
    double time_change_interval = 2;
    double distance_change_interval = 2;
    double random_velocity = 1;

    qint16 channel_number = 30;
    double Frequency = 5180;
    qint16 bandwidth = 20;
    double TxPower = 20;
    QString Ssid = "";
    QString Phy_model = "Yans";
    QString Standard = "802.11ax";
    qint16 GI = 800;
    double Slot = 0;
    double Sifs = 0;
    double RxSensitivity = -101;
    double CcaSensitivity = -82;
    double CcaThreshold = -62;

    // Beacon
    bool Beacon = true;
    qint16 Beacon_interval = 100;
    qint16 Beacon_Rate = 1;
    bool EnableBeaconJitter = true;

    // Rts/Cts
    bool RtsCts = false;
    qint16 RtsCts_Threshold = 65535;

    QString Rate_ctr_algo = "Aarf";
    QString TxQueue = "DropTail";

    // Qos
    bool Qos = false;

    QString Edca = "AC_BE";

    qint16 AC_VO_cwmin = 3;
    qint16 AC_VO_cwmax = 7;
    qint16 AC_VO_AIFSN = 2;
    qint16 AC_VO_TXOP_LIMIT = 47;

    qint16 AC_VI_cwmin = 7;
    qint16 AC_VI_cwmax = 15;
    qint16 AC_VI_AIFSN = 2;
    qint16 AC_VI_TXOP_LIMIT = 94;

    qint16 AC_BE_cwmin = 15;
    qint16 AC_BE_cwmax = 1023;
    qint16 AC_BE_AIFSN = 3;
    qint16 AC_BE_TXOP_LIMIT = 0;

    qint16 AC_BK_cwmin = 15;
    qint16 AC_BK_cwmax = 1023;
    qint16 AC_BK_AIFSN = 7;
    qint16 AC_BK_TXOP_LIMIT = 0;

    bool Msdu_aggregation = true;
    QString AMsdu_type = "AC_BE";
    qint16 MaxAMsduSize = 65535;

    bool Mpdu_aggregation = true;
    QString AMpdu_type = "AC_BE";
    qint16 MaxAMpduSize = 65;
    qint32 Density = 40;

    // Antenna
    QVector<std::shared_ptr<Antenna_Config>> Antenna_list = {};
    // Traffic
    QVector<TrafficConfig> Traffic_list = {};

    inline void integrity_checked() { integrity_check = true; }

private:
    bool integrity_check = false;
};

class Sta
{
public:
    Sta() = default;
    ~Sta() = default;
    QVector<double> m_position = {0, 0, 0};
    qint16 Id = 0;
    // Mobility
    bool Mobility = false;
    QString Mobility_model = "Random Mobility Model";
    QVector<double> boundaries = {0, 0, 0, 0};
    QString mode = "Time";
    double time_change_interval = 2;
    double distance_change_interval = 2;
    double random_velocity = 1;

    bool active_probing = false;
    qint16 channel_number = 30;
    double Frequency = 5180;
    qint16 bandwidth = 20;
    double TxPower = 20;
    QString Ssid = "";
    QString Phy_model = "Yans";
    QString Standard = "802.11ax";
    qint16 GI = 800;
    qint16 MaxMissedBeacons = 10;
    qint16 ProbeRequestTimeout = 500;
    bool EnableAssocFailRetry = true;

    // Rts/Cts
    bool RtsCts = false;
    qint16 RtsCts_Threshold = 65535;

    QString Rate_ctr_algo = "Aarf";
    QString TxQueue = "DropTail";

    // Qos
    bool Qos = false;
    QString Edca = "AC_BE";

    qint16 AC_VO_cwmin = 3;
    qint16 AC_VO_cwmax = 7;
    qint16 AC_VO_AIFSN = 2;
    qint16 AC_VO_TXOP_LIMIT = 47;

    qint16 AC_VI_cwmin = 7;
    qint16 AC_VI_cwmax = 15;
    qint16 AC_VI_AIFSN = 2;
    qint16 AC_VI_TXOP_LIMIT = 94;

    qint16 AC_BE_cwmin = 15;
    qint16 AC_BE_cwmax = 1023;
    qint16 AC_BE_AIFSN = 3;
    qint16 AC_BE_TXOP_LIMIT = 0;

    qint16 AC_BK_cwmin = 15;
    qint16 AC_BK_cwmax = 1023;
    qint16 AC_BK_AIFSN = 7;
    qint16 AC_BK_TXOP_LIMIT = 0;

    bool Msdu_aggregation = true;
    QString AMsdu_type = "AC_BE";
    qint16 MaxAMsduSize = 65535;

    bool Mpdu_aggregation = true;
    QString AMpdu_type = "AC_BE";
    qint16 MaxAMpduSize = 65;
    qint32 Density = 40;

    // Antenna
    QVector<std::shared_ptr<Antenna_Config>> Antenna_list = {};
    // Traffic
    QVector<TrafficConfig> Traffic_list = {};

    inline void integrity_checked() { integrity_check = true; }

private:
    bool integrity_check = false;
};

class BuildingConfig
{
public:
    BuildingConfig() = default;
    ~BuildingConfig() = default;
    QVector<double> m_range = {0, 0, 0};
    QString m_building_type = "Residential";
    QString m_wall_type = "ConcreteWithoutWindows";
    size_t Sta_num = 0;
    size_t Ap_num = 0;
    QVector<QVector<double>> Sta_pos_list = {};
    QVector<QVector<double>> Ap_pos_list = {};
    QVector<std::shared_ptr<Sta>> Ap_list = {};
    QVector<std::shared_ptr<Ap>> Sta_list = {};
};

class JsonHelper
{
public:
    JsonHelper() = default;
    ~JsonHelper() = default;

    bool SetBuildingToJson(const BuildingConfig *);
    bool SetStaToJson(const Sta *, qint8);
    bool SetApToJson(const Ap *, qint8);
    bool SaveJsonObjToRoute(const QJsonObject, const QString);
    void ensureRunDirectories();
    void reset();

    QJsonObject m_building_config;
    QJsonObject *m_sta_config = nullptr;
    QJsonObject *m_ap_config = nullptr;
    std::shared_ptr<BuildingConfig> m_building = std::make_shared<BuildingConfig>();
    QString Base_dir = "/home/zk/Visualization/ns-3.46/contrib/SniffUtils/Simulation/Designed/";
    QString Run_dir = "";
    QString Ap_file_path = "";
    QString Sta_file_path = "";
    QString General_file_path = "";

    QVector<QJsonObject> m_sta_config_list = {};
    QVector<QJsonObject> m_ap_config_list = {};

private:
    bool run_dir_initialized = false;
};

double get_true_random_double(double, double);

#endif // JSONHELPER_H
