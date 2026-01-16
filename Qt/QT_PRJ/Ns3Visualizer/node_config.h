#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H
#include <QMessageBox>
#include <QWidget>
#include "JsonHelper.h"
#include "edca_config.h"
#include "antennas.h"
#include "utils.h"

namespace Ui {
class node_config;
}

class node_config : public QWidget
{
    Q_OBJECT

public:
    explicit node_config(QWidget *parent = nullptr);
    ~node_config();
    JsonHelper *json_helper = new (JsonHelper);
    std::shared_ptr<Sta> one_sta = std::make_shared<Sta>();
    Edca_config *edca_page = new (Edca_config);
    Antenna *antenna_page = new (Antenna);
    QVector<double> Building_range = {0, 0, 0};

    qint8 StaIndex = 0;

signals:
    void Finish_setting_sta();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_2_clicked(bool checked);
    
    void on_checkBox_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    bool Integrity_Check();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::node_config *ui;
    bool pos_set = false;
    bool mobility_set = false;
    bool phymac_set = false;

    bool beacon_set = false;
    bool Rts_Cts_set = false;
    bool Qos_set = false;

    bool Ssid_set = false;
};

#endif // NODE_CONFIG_H
