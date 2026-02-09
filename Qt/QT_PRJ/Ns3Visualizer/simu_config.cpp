#include "simu_config.h"
#include "ui_simu_config.h"
#include "visualizer_config.h"

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <boost/interprocess/shared_memory_object.hpp>

Simu_Config::Simu_Config(QWidget *parent)
    : QWidget(parent), ui(new Ui::Simu_Config) {
  ui->setupUi(this);

  centerWindow(this);

  ui->tabWidget->setCurrentIndex(0);
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
  json_helper.ensureRunDirectories();

  update_json(scene, json_helper.m_building_config);

  if (scene) {
    const auto items = scene->items(); // 拷贝，避免遍历时修改
    for (QGraphicsItem *item : items) {
      if (auto *node = dynamic_cast<NodeItem *>(item)) {
        scene->removeItem(node);
        delete node;
      }
    }
  }

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

    ap->onPositionCommitted = [this](int id, double nx, double ny, double nz) {
      updateNodePositionInTable(QStringLiteral("AP"), id, nx, ny, nz);
    };

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

    sta->onPositionCommitted = [this](int id, double nx, double ny, double nz) {
      updateNodePositionInTable(QStringLiteral("STA"), id, nx, ny, nz);
    };

    scene->addItem(sta);

    // 同步 sta_config_list
    for (auto &cfg : json_helper.m_sta_config_list) {
      if (cfg["Id"].toInt() == sta->m_id) {
        cfg["Position"] = QJsonArray{x, y, z};
        break;
      }
    }
  }

  ui->lcdNumber->display(static_cast<int>(apList.size()));
  ui->lcdNumber_2->display(static_cast<int>(staList.size()));

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

void Simu_Config::updateNodePositionInTable(const QString &type, int id,
                                            double x, double y, double z) {
  QTableWidget *table = nullptr;
  if (type == QLatin1String("AP")) {
    table = ui->tableWidget_2;
  } else if (type == QLatin1String("STA")) {
    table = ui->tableWidget;
  } else {
    return;
  }

  const QString posText =
      QString("(%1, %2, %3)")
          .arg(x, 0, 'f', 2)
          .arg(y, 0, 'f', 2)
          .arg(z, 0, 'f', 2);

  for (int row = 0; row < table->rowCount(); ++row) {
    auto *idItem = table->item(row, 0);
    if (!idItem)
      continue;

    bool ok = false;
    const int rowId = idItem->text().toInt(&ok);
    if (!ok || rowId != id)
      continue;

    auto *posItem = table->item(row, 1);
    if (!posItem) {
      posItem = new QTableWidgetItem();
      table->setItem(row, 1, posItem);
    }
    posItem->setText(posText);
    break;
  }
}

void Simu_Config::cleanupAndExit() {
  static bool cleaning = false;
  if (cleaning)
    return;
  cleaning = true;

  qDebug() << "cleanupAndExit()";

  // 停止 Reader

  if (m_ppduReader) {
    qDebug() << "Stopping PPDU reader";
    m_ppduReader->clearBuffer();
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

  // 停止 ns-3（如果还活着）
  if (ns3Process) {
    qDebug() << "Killing ns-3";
    ns3Process->kill();
    ns3Process->deleteLater();
    ns3Process = nullptr;
  }

  if (!m_copiedScratchPath.isEmpty()) {
    if (QFile::exists(m_copiedScratchPath))
      QFile::remove(m_copiedScratchPath);
    m_copiedScratchPath.clear();
  } else if (!m_selectedScene.isEmpty() && !m_ns3Path.isEmpty()) {
    const QString scratchPath =
        m_ns3Path + "/scratch/" + m_selectedScene + ".cc";
    if (QFile::exists(scratchPath))
      QFile::remove(scratchPath);
  }

  close();
  cleaning = false;
}

void Simu_Config::resetPage() {
  qDebug() << "[Simu_Config] resetPage()";

  if (m_ppduReader) {
    m_ppduReader->clearBuffer();
    m_ppduReader->stop();
    m_ppduReader->deleteLater();
    m_ppduReader = nullptr;
  }

  if (m_ppduThread) {
    m_ppduThread->quit();
    m_ppduThread->wait();
    m_ppduThread->deleteLater();
    m_ppduThread = nullptr;
  }

  if (ns3Process) {
    ns3Process->kill();
    ns3Process->deleteLater();
    ns3Process = nullptr;
  }

  if (scene) {
    const auto items = scene->items();
    for (QGraphicsItem *item : items) {
      scene->removeItem(item);
      delete item;
    }
    scene->clear();
  }

  ui->tabWidget->setCurrentIndex(0);

  ui->doubleSpinBox->setValue(10);
  ui->doubleSpinBox_2->setValue(10);
  ui->doubleSpinBox_3->setValue(5);
  ui->doubleSpinBox_4->setValue(0);

  ui->comboBox->setCurrentIndex(0);
  ui->comboBox_2->setCurrentIndex(0);

  ui->tableWidget->setRowCount(0);
  ui->tableWidget_2->setRowCount(0);
  ui->lcdNumber->display(0);
  ui->lcdNumber_2->display(0);

  ui->pushButton_7->setEnabled(true);
  ui->pushButton_7->setText("Check");

  Num_ap = 0;
  Num_sta = 0;
  building_range = {0, 0, 0};
  m_hasPpdu.store(false);
  m_selectedScene.clear();

  ui->graphicsView->resetTransform();
  ui->graphicsView->setScene(scene);

  // rebuildScene();
  qDebug() << "[Simu_Config] resetPage() done";
}

void Simu_Config::setNs3Path(const QString &path) { m_ns3Path = path; }

void Simu_Config::setSelectedScene(const QString &sceneName) {
  m_selectedScene = sceneName;
}

void Simu_Config::resetSimuScene() { m_selectedScene.clear(); }

void Simu_Config::rebuildScene() {
  if (!scene)
    scene = new QGraphicsScene(this);

  scene->clear();

  if (building_range[0] <= 0 || building_range[1] <= 0) {
    qDebug() << "[Simu_Config] skip draw building (invalid range)";
    return;
  }

  Draw_the_config_map();
}

void Simu_Config::requestCleanup() {
  QTimer::singleShot(0, this, &Simu_Config::cleanupAndExit);
}

void Simu_Config::Load_General_Json(JsonHelper &json_helper) {
  json_helper.ensureRunDirectories();
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

  this->Num_ap = ui->lcdNumber->intValue();
  this->Num_sta = ui->lcdNumber_2->intValue();

  emit CreateAndStartThread();
}

void Simu_Config::Create_And_StartThread() {

  if (m_ppduReader) {
    m_ppduReader->stop();
    m_ppduReader->clearBuffer();
    m_ppduReader->deleteLater();
    m_ppduReader = nullptr;
  }

  if (ns3Process || m_ppduThread || m_ppduReader) {
    qWarning() << "Simulation already running";
    return;
  }

  if (m_ns3Path.isEmpty()) {
    qWarning() << "NS-3 path not set";
    return;
  }

  // DIY 模式暂时硬编码为 timeline_crossing.cc
  // 自适应场景选择逻辑先保留，待后续启用
  // if (m_selectedScene.isEmpty()) {
  //   qWarning() << "No scene selected";
  //   return;
  // }

  m_hasPpdu.store(false);

  m_copiedScratchPath.clear();

  if (!m_selectedScene.isEmpty()) {
    const QString scratchPath =
        m_ns3Path + "/scratch/" + m_selectedScene + ".cc";
    if (!QFile::exists(scratchPath)) {
      const QString simplePath =
          m_ns3Path + "/contrib/SniffUtils/Simulation/Default/Simple/" +
          m_selectedScene + "/" + m_selectedScene + ".cc";
      const QString complexPath =
          m_ns3Path + "/contrib/SniffUtils/Simulation/Default/Complex/" +
          m_selectedScene + "/" + m_selectedScene + ".cc";

      QString sourcePath;
      if (QFile::exists(simplePath)) {
        sourcePath = simplePath;
      } else if (QFile::exists(complexPath)) {
        sourcePath = complexPath;
      }

      if (sourcePath.isEmpty()) {
        qWarning() << "Scene source not found in Default folders:"
                   << m_selectedScene;
        return;
      }

      if (!QFile::copy(sourcePath, scratchPath)) {
        qWarning() << "Failed to copy scene to scratch:" << scratchPath;
        return;
      }

      m_copiedScratchPath = scratchPath;
    }
  }

  ns3Process = new QProcess(this);
  ns3Process->setWorkingDirectory(m_ns3Path);

  connect(ns3Process, &QProcess::started, this,
          [] { qDebug() << "ns-3 started"; });

  connect(ns3Process,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          [this](int code, QProcess::ExitStatus status) {
            qDebug() << "ns-3 finished:" << code << status;
            ns3Process->deleteLater();
            ns3Process = nullptr;
            if (m_ppduReader)
              m_ppduReader->stop();

            if (!m_copiedScratchPath.isEmpty()) {
              if (QFile::exists(m_copiedScratchPath))
                QFile::remove(m_copiedScratchPath);
              m_copiedScratchPath.clear();
            }

            if (!m_hasPpdu.load())
              emit sniffFailed();
          });

  m_ppduThread = new QThread(this);
  m_ppduReader = new QtPpduReader;

  m_ppduReader->moveToThread(m_ppduThread);

  connect(m_ppduThread, &QThread::started, m_ppduReader, &QtPpduReader::run);

  connect(
      m_ppduReader, &QtPpduReader::ppduReady, this,
      [this](const PpduVisualItem &item) {
        m_hasPpdu.store(true);
        emit ppduReady(item);
      },
      Qt::DirectConnection);

  // reader 自己结束时，线程退出
  connect(m_ppduReader, &QtPpduReader::finished, this, [this] {
    if (m_ppduThread) {
      m_ppduReader->clearBuffer();
      m_ppduThread->quit();
    }
  });

  m_ppduThread->start();

  // 先清理共享内存，避免残留数据
  boost::interprocess::shared_memory_object::remove("Ns3PpduSharedMemory");

  const bool isDiy = m_selectedScene.isEmpty();
  const QString sceneToRun =
      isDiy ? QStringLiteral("QNs3-example.cc") : (m_selectedScene + ".cc");
  QStringList args = {"run", sceneToRun};
  if (isDiy) {
    args << "--" << "--ns3path" << m_ns3Path;
  }
  {
    QProcess buildProcess;
    buildProcess.setWorkingDirectory(m_ns3Path);
    QStringList buildArgs = {"build"};
    if (!isDiy) {
      buildArgs << ("scratch/" + m_selectedScene);
    }

    buildProcess.start("./ns3", buildArgs);
    if (!buildProcess.waitForFinished(-1)) {
      qWarning() << "ns-3 build did not finish";
      return;
    }

    const QByteArray buildOut = buildProcess.readAllStandardOutput();
    if (!buildOut.isEmpty()) {
      emit ns3OutputReady(QString::fromUtf8(buildOut));
    }

    const QByteArray buildErr = buildProcess.readAllStandardError();
    if (!buildErr.isEmpty()) {
      emit ns3OutputReady(QString::fromUtf8(buildErr));
    }

    const int exitCode = buildProcess.exitCode();
    if (exitCode != 0) {
      qWarning() << "ns-3 build failed with code" << exitCode;
      return;
    }
  }
  ns3Process->start("./ns3", args);

  /*LINK the Terminal */
  connect(ns3Process, &QProcess::readyReadStandardOutput, this, [this]() {
    QByteArray out = ns3Process->readAllStandardOutput();
    emit ns3OutputReady(QString::fromUtf8(out));
  });

  connect(ns3Process, &QProcess::readyReadStandardError, this, [this]() {
    QByteArray out = ns3Process->readAllStandardError();
    emit ns3OutputReady(QString::fromUtf8(out));
  });

  // ===============================
  // 2. Timeline View
  // ===============================
  // if (!m_timelineView) {
  //   m_timelineView = new PpduTimelineView(this);
  //   m_timelineView->Num_ap = this->Num_ap;
  //   m_timelineView->Num_sta = this->Num_sta;
  //   m_timelineView->setWindowTitle("PPDU Timeline");
  //   m_timelineView->resize(1200, 400);
  //   m_timelineView->show();

  //   connect(m_timelineView, &PpduTimelineView::timelineClosed,
  //           this, &Simu_Config::requestCleanup);
}

// Finnal Check , Run the Simulation , Load the General Json
void Simu_Config::on_pushButton_9_clicked() {
  if (ui->lcdNumber->intValue() != 0 && ui->lcdNumber_2->intValue() != 0) {
    QMessageBox msgBox(QMessageBox::Information, "Attention",
                       "SIMULATION RUNNING ...", QMessageBox::Ok, this);

    msgBox.setWindowModality(Qt::WindowModal);

    // 在窗口真正 show 之后再 move
    QTimer::singleShot(0, this, [this, &msgBox]() {
      QRect parentRect = this->frameGeometry();
      QRect boxRect = msgBox.frameGeometry();

      QPoint center = parentRect.center() - boxRect.center();

      msgBox.move(center);
    });

    msgBox.exec();
  } else {
    QMessageBox msgBox(QMessageBox::Critical, "Error",
                       "At least one AP and one STA is needed", QMessageBox::Ok,
                       this);

    msgBox.setWindowModality(Qt::WindowModal);

    QTimer::singleShot(0, this, [this, &msgBox]() {
      QRect parentRect = this->frameGeometry();
      QRect boxRect = msgBox.frameGeometry();

      QPoint center = parentRect.center() - boxRect.center();

      msgBox.move(center);
    });

    msgBox.exec();
    return;
  }

  QDialog dialog(this);
  dialog.setWindowTitle(tr("PPDU Settings"));
  dialog.setModal(true);

  QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

  QLabel *title =
      new QLabel(tr("Choose precise mode and sampling rate"), &dialog);
  mainLayout->addWidget(title);

  QCheckBox *preciseCheck = new QCheckBox(tr("Enable precise mode"), &dialog);
  preciseCheck->setChecked(g_ppduViewConfig.preciseMode.load());
  mainLayout->addWidget(preciseCheck);

  QFormLayout *formLayout = new QFormLayout();
  QSpinBox *sampleSpin = new QSpinBox(&dialog);
  sampleSpin->setRange(1, 1000);
  const int currentRate = g_ppduViewConfig.sampleRate.load();
  sampleSpin->setValue(currentRate > 0 ? currentRate : 10);
  formLayout->addRow(tr("Sample rate (1/N)"), sampleSpin);
  mainLayout->addLayout(formLayout);

  auto updateSampleEnabled = [=](bool precise) {
    sampleSpin->setEnabled(!precise);
  };
  updateSampleEnabled(preciseCheck->isChecked());
  connect(preciseCheck, &QCheckBox::toggled, this, updateSampleEnabled);

  QDialogButtonBox *buttons = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
  mainLayout->addWidget(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() != QDialog::Accepted)
    return;

  const bool precise = preciseCheck->isChecked();
  g_ppduViewConfig.preciseMode.store(precise);
  g_ppduViewConfig.absoluteRate.store(precise);
  g_ppduViewConfig.sampleRate.store(precise ? 1 : sampleSpin->value());

  emit LoadGeneralConfig();
}

//嗯嗯这个按钮没有必要复活了,因为采样专门有弹窗了
void Simu_Config::on_checkBox_checkStateChanged(const Qt::CheckState &state) {
  bool checked = (state == Qt::Checked);

  g_ppduViewConfig.absoluteRate.store(checked);
  g_ppduViewConfig.preciseMode.store(checked);
  g_ppduViewConfig.sampleRate.store(checked ? 1 : 10); // 默认降采样 1/10
}

void Simu_Config::addApToTable(int id, const QVector<double> &pos, bool mobility) {
  int row = ui->tableWidget_2->rowCount();
  ui->tableWidget_2->insertRow(row);
  
  ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
  ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(
    QString("(%1, %2, %3)").arg(pos[0], 0, 'f', 2).arg(pos[1], 0, 'f', 2).arg(pos[2], 0, 'f', 2)));
  ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(mobility ? "Yes" : "No"));
  
  updateLcdNumbers();
}

void Simu_Config::addStaToTable(int id, const QVector<double> &pos, bool mobility) {
  int row = ui->tableWidget->rowCount();
  ui->tableWidget->insertRow(row);
  
  ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
  ui->tableWidget->setItem(row, 1, new QTableWidgetItem(
    QString("(%1, %2, %3)").arg(pos[0], 0, 'f', 2).arg(pos[1], 0, 'f', 2).arg(pos[2], 0, 'f', 2)));
  ui->tableWidget->setItem(row, 2, new QTableWidgetItem(mobility ? "Yes" : "No"));
  
  updateLcdNumbers();
}

void Simu_Config::updateLcdNumbers() {
  ui->lcdNumber->display(ui->tableWidget_2->rowCount());
  ui->lcdNumber_2->display(ui->tableWidget->rowCount());
}
