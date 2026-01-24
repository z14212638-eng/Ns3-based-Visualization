#include "simu_config.h"
#include "ui_simu_config.h"
#include "visualizer_config.h"

Simu_Config::Simu_Config(QWidget *parent)
    : QWidget(parent), ui(new Ui::Simu_Config) {
  ui->setupUi(this);

  centerWindow(this);

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->frame->setObjectName("myFrame");
  QString frameQss = R"(
QFrame#myFrame {
    border: 1px solid #BFBFBF;
    border-radius: 4px;
    background-color: #FFFFFF;
}
    
)";
}

Simu_Config::~Simu_Config() {
  qDebug() << "Destroying Simu_Config";
  delete ui; // 最后 delete UI
}

// Add a Sta
void Simu_Config::on_pushButton_clicked() { emit AddSta(); }

// Add an AP
void Simu_Config::on_pushButton_4_clicked() { emit AddAp(); }

// Draw the frame of the building
void Simu_Config::Write_building_into_config(BuildingConfig &building,
                                             Ap_config &ap, node_config &sta) {
  /*Fill the local data*/
  building_range = {ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value(),
                    ui->doubleSpinBox_3->value()};

  /*load the data in mainwindow*/
  building.m_range[0] = ui->doubleSpinBox->value();
  building.m_range[1] = ui->doubleSpinBox_2->value();
  building.m_range[2] = ui->doubleSpinBox_3->value();
  ap.Building_range = building.m_range;
  sta.Building_range = building.m_range;
  building.m_building_type = ui->comboBox->currentText();
  building.m_wall_type = ui->comboBox_2->currentText();

  /*Draw the building frame*/
  Draw_the_config_map();
}

// Building config checked [Tab 1 Finished]
void Simu_Config::on_pushButton_7_clicked() {
  /*debug*/
  qDebug() << "Scene pointer:" << scene;
  qDebug() << "Scene item count:" << (scene ? scene->items().size() : -1);

  ui->pushButton_7->setEnabled(false);
  ui->pushButton_7->setText("Checked");
  ui->tabWidget->setCurrentIndex(1);

  emit Building_Set();
}

// Draw the building frame
void Simu_Config::Draw_the_config_map() {
  if (!scene) {
    this->scene = new QGraphicsScene(this);
  }
  const auto items = scene->items();
  for (QGraphicsItem *item : items) {
    if (auto *node = dynamic_cast<NodeItem *>(item)) {
      scene->removeItem(node);
      delete node;
    }
  }
  ui->graphicsView->setScene(scene);
  ui->graphicsView->resetTransform();
  // set the axis direction
  ui->graphicsView->scale(1, -1);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);

  // restrict the range and set the scale
  double width = this->building_range[0];
  double height = this->building_range[1];
  double scale = 40;
  // draw the building
  QRect sceneRect(0, 0, width * scale, height * scale);
  scene->setSceneRect(sceneRect);
  QGraphicsRectItem *building = scene->addRect(sceneRect, QPen(Qt::black, 2));
  building->setZValue(0);
}

// Enable the json updated
void Simu_Config::update_json(QGraphicsScene *scene,
                              QJsonObject &building_config) {
  qDebug() << "updating json";
  if (!scene)
    return;

  QJsonArray apList = building_config["Ap_pos_list"].toArray();
  QJsonArray staList = building_config["Sta_pos_list"].toArray();

  for (QGraphicsItem *item : scene->items()) {
    auto *node = dynamic_cast<NodeItem *>(item);
    if (!node)
      continue;

    double x = node->pos().x() / 40.0;
    double y = node->pos().y() / 40.0;
    double z = node->z_sim;

    // update the corresponding ap
    if (node->Type == "AP") {
      for (int i = 0; i < apList.size(); ++i) {
        QJsonObject obj = apList[i].toObject();
        if (obj["id"].toInt() == node->m_id) {
          obj["pos"] = QJsonArray{x, y, z};
          apList[i] = obj;
          break;
        }
      }
    }

    // update the corresponding sta
    else if (node->Type == "STA") {
      for (int i = 0; i < staList.size(); ++i) {
        QJsonObject obj = staList[i].toObject();
        if (obj["id"].toInt() == node->m_id) {
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
void Simu_Config::on_pushButton_8_clicked() { emit update(); }

void Simu_Config::Update_json_map(JsonHelper &json_helper) {
  // ===============================
  // 1. 用当前 scene 中的 NodeItem 更新 json
  // ===============================
  update_json(scene, json_helper.m_building_config);

  // ===============================
  // 2. 只删除 NodeItem（AP / STA）
  //    ⚠️ 必须 removeItem + delete
  // ===============================
  if (scene) {
    const auto items = scene->items(); // 拷贝，避免遍历时修改
    for (QGraphicsItem *item : items) {
      if (auto *node = dynamic_cast<NodeItem *>(item)) {
        scene->removeItem(node);
        delete node;
      }
    }
  }

  // ===============================
  // 3. 重建 NodeItem（building 边框不动）
  // ===============================
  double width = building_range[0];
  double height = building_range[1];
  double scale = 40.0;
  QRectF sceneRect(0, 0, width * scale, height * scale);

  // ---------- AP ----------
  QJsonArray apList = json_helper.m_building_config["Ap_pos_list"].toArray();

  for (const auto &val : apList) {
    QJsonObject ap_pos = val.toObject();
    QJsonArray pos = ap_pos["pos"].toArray();
    if (pos.size() < 3)
      continue;

    double x = pos[0].toDouble();
    double y = pos[1].toDouble();
    double z = pos[2].toDouble();

    auto *ap = new NodeItem(sceneRect, scale);
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

    // 同步 ap_config_list
    for (auto &cfg : json_helper.m_ap_config_list) {
      if (cfg["Id"].toInt() == ap->m_id) {
        cfg["Position"] = QJsonArray{x, y, z};
        break;
      }
    }
  }

  // ---------- STA ----------
  QJsonArray staList = json_helper.m_building_config["Sta_pos_list"].toArray();

  for (const auto &val : staList) {
    QJsonObject sta_pos = val.toObject();
    QJsonArray pos = sta_pos["pos"].toArray();
    if (pos.size() < 3)
      continue;

    double x = pos[0].toDouble();
    double y = pos[1].toDouble();
    double z = pos[2].toDouble();

    auto *sta = new NodeItem(sceneRect, scale);
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

    // 同步 sta_config_list
    for (auto &cfg : json_helper.m_sta_config_list) {
      if (cfg["Id"].toInt() == sta->m_id) {
        cfg["Position"] = QJsonArray{x, y, z};
        break;
      }
    }
  }

  // ===============================
  // 4. 更新 LCD
  // ===============================
  ui->lcdNumber->display(static_cast<int>(apList.size()));
  ui->lcdNumber_2->display(static_cast<int>(staList.size()));

  // ===============================
  // 5. 写回 JSON 文件
  // ===============================
  for (const auto &item : json_helper.m_ap_config_list) {
    QString path = json_helper.Ap_file_path +
                   QString::number(item["Id"].toInt() + 1) + ".json";
    json_helper.SaveJsonObjToRoute(item, path);
  }

  for (const auto &item : json_helper.m_sta_config_list) {
    QString path = json_helper.Sta_file_path +
                   QString::number(item["Id"].toInt() + 1) + ".json";
    json_helper.SaveJsonObjToRoute(item, path);
  }
}

void Simu_Config::cleanupAndExit() {
  static bool cleaning = false;
  if (cleaning)
    return;
  cleaning = true;

  qDebug() << "cleanupAndExit()";

  // ===============================
  // 1. 停止 Reader
  // ===============================
  if (m_ppduReader) {
    qDebug() << "Stopping PPDU reader";
    m_ppduReader->stop();
    m_ppduReader->deleteLater();
    m_ppduReader = nullptr;
  }

  if (m_ppduThread) {
    qDebug() << "Stopping PPDU thread";
    m_ppduThread->quit();
    m_ppduThread->wait();
    m_ppduThread->deleteLater();
    m_ppduThread = nullptr;
  }

  // ===============================
  // 2. 停止 ns-3（如果还活着）
  // ===============================
  if (ns3Process) {
    qDebug() << "Killing ns-3";
    ns3Process->kill();
    ns3Process->deleteLater();
    ns3Process = nullptr;
  }

  // ===============================
  // 3. 关闭 Timeline
  // ===============================
  if (m_timelineView) {
    qDebug() << "Closing timeline view";
    m_timelineView->close();
    m_timelineView->deleteLater();
    m_timelineView = nullptr;
  }

  // ===============================
  // 4. Scene：只删 NodeItem
  // ===============================
  if (scene) {
    const auto items = scene->items();
    for (QGraphicsItem *item : items) {
      if (auto *node = dynamic_cast<NodeItem *>(item)) {
        scene->removeItem(node);
        delete node;
      }
    }
  }

  // ===============================
  // 5. 关闭自己
  // ===============================
  close();
}


void Simu_Config::requestCleanup() {
  // 延迟调用 cleanupAndExit，确保事件队列空
  QTimer::singleShot(0, this, &Simu_Config::cleanupAndExit);
}

void Simu_Config::Load_General_Json(JsonHelper &json_helper) {
  QJsonObject Building;
  double x_range = ui->doubleSpinBox->value();
  double y_range = ui->doubleSpinBox_2->value();
  double z_range = ui->doubleSpinBox_3->value();
  QJsonArray range = {x_range, y_range, z_range};

  json_helper.m_building_config["Building"] =
      QJsonObject{{"range", range},
                  {"building_type", ui->comboBox->currentText()},
                  {"wall_type", ui->comboBox_2->currentText()}};
  json_helper.m_building_config["Ap_num"] = ui->lcdNumber->intValue();
  json_helper.m_building_config["Sta_num"] = ui->lcdNumber_2->intValue();
  json_helper.m_building_config["SimulationTime"] =
      ui->doubleSpinBox_4->value();

  QString filepath = json_helper.General_file_path + "General.json";
  json_helper.SaveJsonObjToRoute(json_helper.m_building_config, filepath);
  qDebug() << "Save general config to " << filepath;

  emit CreateAndStartThread();
}

void Simu_Config::Create_And_StartThread() {
  // ===============================
  // 防止重复启动
  // ===============================
  if (ns3Process || m_ppduThread || m_ppduReader) {
    qWarning() << "Simulation already running";
    return;
  }

  // ===============================
  // 1. ns-3 process
  // ===============================
  ns3Process = new QProcess(this);
  ns3Process->setWorkingDirectory("/home/zk/Visualization/ns-3.46");

  connect(ns3Process, &QProcess::started, this, [] {
    qDebug() << "ns-3 started";
  });

  connect(ns3Process,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
          this,
          [this](int code, QProcess::ExitStatus status) {
            qDebug() << "ns-3 finished:" << code << status;

            // 核心：ns-3 结束 ⇒ 触发清理
            requestCleanup();

            ns3Process->deleteLater();
            ns3Process = nullptr;
          });

  ns3Process->start("./ns3", {"run", "timeline_pressure.cc"});

  // ===============================
  // 2. Timeline View
  // ===============================
  if (!m_timelineView) {
    m_timelineView = new PpduTimelineView(this);
    m_timelineView->setWindowTitle("PPDU Timeline");
    m_timelineView->resize(1200, 400);
    m_timelineView->show();

    connect(m_timelineView, &PpduTimelineView::timelineClosed,
            this, &Simu_Config::requestCleanup);
  }

  // ===============================
  // 3. PPDU Reader Thread
  // ===============================
  m_ppduThread = new QThread(this);
  m_ppduReader = new QtPpduReader;

  m_ppduReader->moveToThread(m_ppduThread);

  connect(m_ppduThread, &QThread::started,
          m_ppduReader, &QtPpduReader::run);

  connect(m_ppduReader, &QtPpduReader::ppduReady,
          m_timelineView, &PpduTimelineView::append,
          Qt::QueuedConnection);

  // reader 自己结束时，线程退出
  connect(m_ppduReader, &QtPpduReader::finished, this, [this] {
    if (m_ppduThread) {
      m_ppduThread->quit();
    }
  });

  m_ppduThread->start();
}


// Finnal Check , Run the Simulation , Load the General Json
void Simu_Config::on_pushButton_9_clicked() {
  if (ui->lcdNumber->intValue() != 0 && ui->lcdNumber_2->intValue() != 0) {
    QMessageBox msgBox(QMessageBox::Information, "Attention",
                       "SIMULATION RUNNING ...", QMessageBox::Ok, this);
    msgBox.adjustSize();

    QRect parentRect = this->geometry();
    QPoint center =
        parentRect.center() - QPoint(msgBox.width() / 2, msgBox.height() / 2);

    msgBox.move(center);
    msgBox.exec();
  } else {
    QMessageBox msgBox(QMessageBox::Critical, "Error",
                       "At least one AP and one STA is needed", QMessageBox::Ok,
                       this);
    msgBox.adjustSize();

    QRect parentRect = this->geometry();
    QPoint center =
        parentRect.center() - QPoint(msgBox.width() / 2, msgBox.height() / 2);

    msgBox.move(center);
    msgBox.exec();
    return;
  }
  emit LoadGeneralConfig();
}

void Simu_Config::on_checkBox_checkStateChanged(const Qt::CheckState &state) {
  bool checked = (state == Qt::Checked);

  g_ppduViewConfig.absoluteRate.store(checked);
  g_ppduViewConfig.preciseMode.store(checked);
  g_ppduViewConfig.sampleRate.store(checked ? 1 : 10); // 默认降采样 1/10
}
