#include "simu_config.h"
#include "ui_simu_config.h"

Simu_Config::Simu_Config(QWidget *parent)
    : QWidget(parent), ui(new Ui::Simu_Config)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(this->node_config_page, &node_config::Finish_setting_sta, this, [=]()
            {
        ui->tabWidget->setCurrentIndex(2);
        this->node_config_page->close();
        on_pushButton_8_clicked();
        this->show(); });

    connect(this->ap_config_page, &Ap_config::Finish_setting_ap, this, [=]()
            {
        ui->tabWidget->setCurrentIndex(1);
        this->ap_config_page->close();
        on_pushButton_8_clicked();
        this->show(); });

    jsonHelper = new JsonHelper();
}

Simu_Config::~Simu_Config()
{
    delete ui;
}

// Add a Sta
void Simu_Config::on_pushButton_clicked()
{
    this->node_config_page->show();
}

// Add an AP
void Simu_Config::on_pushButton_4_clicked()
{
    this->ap_config_page->show();
}

// Draw the frame of the building
void Simu_Config::Write_building_into_config()
{
    jsonHelper->m_building->m_range[0] = ui->doubleSpinBox->value();
    jsonHelper->m_building->m_range[1] = ui->doubleSpinBox_2->value();
    jsonHelper->m_building->m_range[2] = ui->doubleSpinBox_3->value();

    jsonHelper->m_building->m_building_type = ui->comboBox->currentText();
    jsonHelper->m_building->m_wall_type = ui->comboBox_2->currentText();

    this->ap_config_page->Building_range = {jsonHelper->m_building->m_range[0], jsonHelper->m_building->m_range[1], jsonHelper->m_building->m_range[2]};
    this->node_config_page->Building_range = {jsonHelper->m_building->m_range[0], jsonHelper->m_building->m_range[1], jsonHelper->m_building->m_range[2]};

    QJsonObject building_config;
    building_config["range"] = QJsonArray({jsonHelper->m_building->m_range[0], jsonHelper->m_building->m_range[1], jsonHelper->m_building->m_range[2]});
    building_config["building_type"] = jsonHelper->m_building->m_building_type;
    building_config["wall_type"] = jsonHelper->m_building->m_wall_type;
    jsonHelper->m_building_config["Building"] = building_config;

    Draw_the_config_map();
}

// Building config checked
void Simu_Config::on_pushButton_7_clicked()
{
    qDebug() << "Scene pointer:" << scene;
    qDebug() << "Scene item count:" << (scene ? scene->items().size() : -1);
    this->Write_building_into_config();
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_7->setText("Checked");
    ui->tabWidget->setCurrentIndex(1);
}

// Draw the building frame
void Simu_Config::Draw_the_config_map()
{
    if (!scene)
    {
        this->scene = new QGraphicsScene(this);
    }
    else
    {
        scene->clear();
    }
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resetTransform();
    // set the axis direction
    ui->graphicsView->scale(1, -1);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // restrict the range and set the scale
    double width = this->ap_config_page->Building_range[0];
    double height = this->ap_config_page->Building_range[1];
    double scale = 40;
    // draw the building
    QRect sceneRect(0, 0, width * scale, height * scale);
    scene->setSceneRect(sceneRect);
    QGraphicsRectItem *building = scene->addRect(sceneRect, QPen(Qt::black, 2));
    building->setZValue(0);
}

// Enable the building map and the json be updated
void Simu_Config::update_json(QGraphicsScene *scene,
                              QJsonObject &building_config)
{
    if (!scene)
        return;

    QJsonArray apList = building_config["Ap_pos_list"].toArray();
    QJsonArray staList = building_config["Sta_pos_list"].toArray();

    for (QGraphicsItem *item : scene->items())
    {
        auto *node = dynamic_cast<NodeItem *>(item);
        if (!node)
            continue;

        double x = node->pos().x() / 40.0;
        double y = node->pos().y() / 40.0;
        double z = node->z_sim;

        // update the corresponding ap
        if (node->Type == "AP")
        {
            for (int i = 0; i < apList.size(); ++i)
            {
                QJsonObject obj = apList[i].toObject();
                if (obj["id"].toInt() == node->m_id)
                {
                    obj["pos"] = QJsonArray{x, y, z};
                    apList[i] = obj;
                    break;
                }
            }
        }

        // update the corresponding sta
        else if (node->Type == "STA")
        {
            for (int i = 0; i < staList.size(); ++i)
            {
                QJsonObject obj = staList[i].toObject();
                if (obj["id"].toInt() == node->m_id)
                {
                    obj["pos"] = QJsonArray{x, y, z};
                    staList[i] = obj;
                    break;
                }
            }
        }
    }

    building_config["Ap_pos_list"] = apList;
    building_config["Sta_pos_list"] = staList;
}

// update the config_map
void Simu_Config::on_pushButton_8_clicked()
{
    // Draw_the_config_map();
    update_json(scene, this->ap_config_page->json_helper->m_building_config);
    update_json(scene, this->node_config_page->json_helper->m_building_config);

    for (QGraphicsItem *item : scene->items())
    {
        NodeItem *node = dynamic_cast<NodeItem *>(item);
        if (node)
        {
            scene->removeItem(node);
            delete node;
        }
    }

    double width = this->ap_config_page->Building_range[0];
    double height = this->ap_config_page->Building_range[1];
    double scale = 40;
    QRect sceneRect(0, 0, width * scale, height * scale);

    std::cout << "update the config_map" << std::endl;
    jsonHelper->m_building_config = this->ap_config_page->json_helper->m_building_config;

    // std::cout << this->ap_config_page->json_helper->m_building_config["Ap_num"].toInt() << std::endl;
    // std::cout <<jsonHelper->m_building_config["Ap_pos_list"].toArray().size() << std::endl;
    // std::cout <<this->ap_config_page->json_helper->m_building_config["Ap_pos_list"].toArray()[0].toObject()["pos"].toArray()[0].toDouble() << std::endl;
    QJsonArray json_ap_pos_list =
        this->ap_config_page->json_helper->m_building_config["Ap_pos_list"].toArray();

    // Update the json of ap
    for (int i = 0; i < json_ap_pos_list.size(); ++i)
    {
        QJsonObject ap_pos = json_ap_pos_list[i].toObject();
        qint8 id = ap_pos["id"].toInt();
        QJsonArray pos = ap_pos["pos"].toArray();
        if (pos.size() < 2)
            continue;

        double x = pos[0].toDouble();
        double y = pos[1].toDouble();
        double z = pos[2].toDouble();

        NodeItem *ap = new NodeItem(sceneRect, scale);
        ap->m_id = ap_pos["id"].toInt();
        ap->Type = "AP";
        ap->x_sim = x;
        ap->y_sim = y;
        ap->z_sim = z;

        ap->setBrush(Qt::red);
        ap->setZValue(10);
        ap->setPos(x * scale, y * scale);

        ap->finishInit();

        scene->addItem(ap);

        for (auto &item : this->ap_config_page->json_helper->m_ap_config_list)
        {
            if (item["Id"].toInt() == ap->m_id)
            {
                item["Position"] = QJsonArray{x, y, z};
                std::cout << "update ap position" << std::endl;
                break;
            }
        }
    }

    qDebug() << "AP size ="
             << this->ap_config_page->json_helper
                    ->m_building_config["Ap_pos_list"]
                    .toArray()
                    .size()
             << "the size of the ap_config_list:"
             << this->ap_config_page->json_helper->m_ap_config_list.size();

    // Update the json of sta
    jsonHelper->m_building_config = this->node_config_page->json_helper->m_building_config;
    QJsonArray json_sta_pos_list =
        this->node_config_page->json_helper->m_building_config["Sta_pos_list"].toArray();

    for (int i = 0; i < json_sta_pos_list.size(); ++i)
    {
        QJsonObject sta_pos = json_sta_pos_list[i].toObject();
        QJsonArray pos = sta_pos["pos"].toArray();
        if (pos.size() < 2)
            continue;

        double x = pos[0].toDouble();
        double y = pos[1].toDouble();
        double z = pos[2].toDouble();

        NodeItem *sta = new NodeItem(sceneRect, scale);
        sta->m_id = sta_pos["id"].toInt();
        sta->Type = "STA";
        sta->x_sim = x;
        sta->y_sim = y;
        sta->z_sim = z;

        sta->setBrush(Qt::blue);
        sta->setZValue(10);
        sta->setPos(x * scale, y * scale);

        sta->finishInit();

        scene->addItem(sta);

        for (auto &item : this->node_config_page->json_helper->m_sta_config_list)
        {
            if (item["Id"].toInt() == sta->m_id)
            {
                item["Position"] = QJsonArray{x, y, z};
                std::cout << "update sta position" << std::endl;
                break;
            }
        }
    }

    // Display the lcd module
    qint16 ap_totol = this->ap_config_page->json_helper
                          ->m_building_config["Ap_pos_list"]
                          .toArray()
                          .size();
    qint16 sta_totol = this->node_config_page->json_helper
                           ->m_building_config["Sta_pos_list"]
                           .toArray()
                           .size();

    ui->lcdNumber->setStyleSheet("color:red");
    ui->lcdNumber_2->setStyleSheet("color:blue");
    ui->lcdNumber->display(ap_totol);
    ui->lcdNumber_2->display(sta_totol);

    // Save the config to json file
    for (auto item : this->ap_config_page->json_helper->m_ap_config_list)
    {
        QString filepath = jsonHelper->Ap_file_path + QString::number(item["Id"].toInt()) + ".json";
        jsonHelper->SaveJsonObjToRoute(item, filepath);
        qDebug() << "Save ap config to " << filepath.toStdString();
    }

    for (auto item : this->node_config_page->json_helper->m_sta_config_list)
    {
        QString filepath = jsonHelper->Sta_file_path + QString::number(item["Id"].toInt()) + ".json";
        jsonHelper->SaveJsonObjToRoute(item, filepath);
        qDebug() << "Save sta config to " << filepath.toStdString();
    }
}

// Finnal Check , Run the Simulation , Load the General Json
void Simu_Config::on_pushButton_9_clicked()
{
    if (ui->lcdNumber->intValue() != 0 && ui->lcdNumber_2->intValue() != 0)
    {
        QMessageBox::information(this, "Attention", "SIMULATION RUNNING ...");
    }
    else
    {
        QMessageBox::critical(this, "Error", "At least one AP and one STA is needed");
        return;
    }

    QJsonObject Building;
    double x_range = ui->doubleSpinBox->value();
    double y_range = ui->doubleSpinBox_2->value();
    double z_range = ui->doubleSpinBox_3->value();
    QJsonArray range = {x_range, y_range, z_range};
    Building["range"] = range;
    Building["building_type"] = ui->comboBox->currentText();
    Building["wall_type"] = ui->comboBox_2->currentText();
    this->jsonHelper->m_building_config["Building"] = Building;
    this->jsonHelper->m_building_config["Ap_num"] = ui->lcdNumber->intValue();
    this->jsonHelper->m_building_config["Sta_num"] = ui->lcdNumber_2->intValue();
    this->jsonHelper->m_building_config["Ap_pos_list"] = this->ap_config_page->json_helper->m_building_config["Ap_pos_list"].toArray();
    this->jsonHelper->m_building_config["Sta_pos_list"] = this->node_config_page->json_helper->m_building_config["Sta_pos_list"].toArray();
    this->jsonHelper->m_building_config["SimulationTime"] = ui->doubleSpinBox_4->value();

    QString filepath = this->jsonHelper->General_file_path + "General.json";
    this->jsonHelper->SaveJsonObjToRoute(this->jsonHelper->m_building_config, filepath);
    qDebug() << "Save general config to " << filepath.toStdString();

    if (ns3Process)
    {
        ns3Process->kill();
        delete ns3Process;
    }

    ns3Process = new QProcess(this);

    // ns-3 working directory
    ns3Process->setWorkingDirectory("/home/zk/Visualization/ns-3.46");

    QString program = "./ns3";
    QStringList arguments;
    arguments << "run" << "timeline_test.cc";

    connect(ns3Process, &QProcess::started, this, []
            { qDebug() << "ns-3 started"; });

    connect(ns3Process, &QProcess::errorOccurred, this,
            [](QProcess::ProcessError e)
            {
                qDebug() << "ns-3 error:" << e;
            });

    ns3Process->start(program, arguments);

    // ==============================
    // 1. create the timeline view
    // ==============================
    if (!m_timelineView)
    {
        m_timelineView = new PpduTimelineView;
        m_timelineView->setWindowTitle("PPDU Timeline");
        m_timelineView->resize(1200, 400);
        m_timelineView->show();
    }

    // ===============================
    // 2. create the ppdu reader
    // ===============================
    m_ppduThread = new QThread(this);
    m_ppduReader = new QtPpduReader;

    m_ppduReader->moveToThread(m_ppduThread);

    // load  → reader.run()
    connect(m_ppduThread, &QThread::started,
            m_ppduReader, &QtPpduReader::run);

    // Reader → Timeline
    connect(m_ppduReader, &QtPpduReader::ppduReady,
            m_timelineView, &PpduTimelineView::append,
            Qt::QueuedConnection);

    // recycle the thread
    connect(qApp, &QCoreApplication::aboutToQuit, [=]
            {
        m_ppduReader->stop();
        m_ppduThread->quit();
        m_ppduThread->wait();
        m_ppduReader->deleteLater(); });

    m_ppduThread->start();
}
