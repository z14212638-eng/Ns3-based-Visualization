#ifndef AP_CONFIG_H
#define AP_CONFIG_H
#include "JsonHelper.h"
#include "edca_config.h"
#include "antennas.h"
#include "utils.h"
#include <QMessageBox>
#include <QWidget>

namespace Ui
{
    class Ap_config;
}

class Ap_config : public QWidget
{
    Q_OBJECT

public:
    explicit Ap_config(QWidget *parent = nullptr);
    ~Ap_config();
    JsonHelper *json_helper = new (JsonHelper);
    std::shared_ptr<Ap> one_ap = std::make_shared<Ap>();
    Edca_config *edca_page = new (Edca_config);
    Antenna *antenna_page = new (Antenna);
    QVector<double> Building_range = {0, 0, 0};

    qint8 ApIndex = 0;

    private slots : 
    
    //Ap_Position_set
    void on_pushButton_clicked();
    //Mobility_finished
    void on_pushButton_4_clicked();
    //Random_Position_set
    void on_checkBox_4_clicked(bool checked);
    //Ap_Mobility_set
    void on_checkBox_3_clicked(bool checked);
    //Beacons_set
    void on_checkBox_clicked(bool checked);
    //Rts_Cts_set
    void on_checkBox_5_clicked(bool checked);
    //Qos_set
    void on_checkBox_6_clicked(bool checked);
    //edca_config
    void on_pushButton_8_clicked();
    //antenna_config
    void on_pushButton_9_clicked();
    //Save_config(one ap configuration finished)
    void on_pushButton_6_clicked();
    //Remained to be done
    bool Integrity_Check();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void Finish_setting_ap();

private:
    Ui::Ap_config *ui;
    bool pos_set = false;
    bool mobility_set = false;
    bool phymac_set = false;

    bool beacon_set = false;
    bool Rts_Cts_set = false;
    bool Qos_set = false;

    bool Ssid_set = false;
};

#endif // AP_CONFIG_H
