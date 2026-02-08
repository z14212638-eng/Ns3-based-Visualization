#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <qthreadpool.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /*ToolBar*/
  QToolBar *topToolBar = new QToolBar("Top Toolbar", this);
  addToolBar(Qt::TopToolBarArea, topToolBar);
  homeAction = topToolBar->addAction("Home(don't click me[doge])");
  // connect(homeAction, &QAction::triggered, this, [=]() { switchTo(0); });
  QAction *pathAction =
      new QAction(QIcon(":/icons/folder.svg"), tr("NS-3 Path"), this);

  pathAction->setToolTip(tr("Set NS-3 working directory"));
  topToolBar->addAction(pathAction);

  connect(pathAction, &QAction::triggered, this, &MainWindow::onBrowseNs3Dir);
  topToolBar->setIconSize(QSize(24, 24));
  topToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  /*Central Widget*/
  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  QHBoxLayout *mainLayout = new QHBoxLayout(central);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  /*Left Sidebar*/
  QWidget *leftSidebar = new QWidget(central);
  leftSidebar->setFixedWidth(150);

  QVBoxLayout *leftLayout = new QVBoxLayout(leftSidebar);
  leftLayout->addWidget(new QLabel("Left Panel"));
  leftLayout->addStretch();

  /*Right Sidebar*/
  QWidget *rightSidebar = new QWidget(central);
  rightSidebar->setFixedWidth(150);

  QVBoxLayout *rightLayout = new QVBoxLayout(rightSidebar);
  rightLayout->addWidget(new QLabel("Right Panel"));
  rightLayout->addStretch();

  stack = new QStackedWidget(central);

  /*Pages*/
  page1 = new Page1_model_chose(this);
  simuConfig = new Simu_Config(this);
  nodeConfigPage = new node_config(this);
  apConfigPage = new Ap_config(this);
  edcaConfig = new Edca_config(this);
  antenna = new Antenna(this);
  timelineDisplay = new Timeline_Display(this);
  greetingPage = new Greeting(this);

  stack->addWidget(page1);           // index 0
  stack->addWidget(simuConfig);      // index 1
  stack->addWidget(nodeConfigPage);  // index 2
  stack->addWidget(apConfigPage);    // index 3
  stack->addWidget(edcaConfig);      // index 4
  stack->addWidget(antenna);         // index 5
  stack->addWidget(timelineDisplay); // index 6
  stack->addWidget(greetingPage);

  switchTo(stack->indexOf(greetingPage));

  /*Layout Assemble*/
  mainLayout->addWidget(leftSidebar);
  mainLayout->addWidget(stack, 1);
  mainLayout->addWidget(rightSidebar);

  /*Signal & Slot*/

  /*greetingPage*/
  connect(greetingPage, &Greeting::nextPage, this, [=]() {
    const QString currentPath = greetingPage ? greetingPage->ns3Path : QString();
    if (currentPath.isEmpty() || !isValidNs3Directory(currentPath)) {
      QMessageBox::warning(
          this, tr("NS-3"),
          tr("The selected directory is not a valid NS-3 directory."));
      ns3PathValid = false;
      return;
    }
    ns3PathValid = true;
    if (page1)
      page1->ns3Path = currentPath;
    if (page1)
      page1->refreshModelLists();
    if (simuConfig)
      simuConfig->setNs3Path(currentPath);
    if (greetingPage)
      greetingPage->setNs3Path(currentPath);
    switchTo(0);
  });
  /*Page_1_model_chose*/
  connect(page1, &Page1_model_chose::BackToMain, this, [=]() { switchTo(stack->indexOf(greetingPage)); });

  connect(page1, &Page1_model_chose::ConfigSimulation, this,
          [=]() {
            if (simuConfig)
              simuConfig->setSelectedScene(QString());
            simuConfig->resetSimuScene();
            switchTo(1);
          });

  connect(page1, &Page1_model_chose::RunSelectedSimulation, this,
          [=]() {
            if (!ns3PathValid) {
              QMessageBox::warning(
                  this,
                  tr("NS-3 not configured"),
                  tr("Please set the NS-3 directory before starting a simulation."));
              return;
            }
            const QString sceneName = page1->GetSceneName();
            if (sceneName.isEmpty()) {
              QMessageBox::warning(this, tr("No Scene"),
                                   tr("Please select a scene first."));
              return;
            }
            if (simuConfig) {
              simuConfig->setSelectedScene(sceneName);
            }
            if (timelineDisplay)
              timelineDisplay->resetPage();
            simuConfig->Create_And_StartThread();
            switchTo(6);
          });
  /*Simu_Config*/
  connect(simuConfig, &Simu_Config::BackToLastPage, this,
          [=]() { switchTo(0); });

  connect(simuConfig, &Simu_Config::Building_Set, this, [=]() {
    simuConfig->Write_building_into_config(buildingConfig, *apConfigPage,
                                           *nodeConfigPage);
  });

  connect(simuConfig, &Simu_Config::update, this,
          [=]() { simuConfig->Update_json_map(jsonhelper); });

  connect(simuConfig, &Simu_Config::LoadGeneralConfig, this,
          [=]() { simuConfig->Load_General_Json(jsonhelper); });

  connect(simuConfig, &Simu_Config::ns3OutputReady, timelineDisplay,
          &Timeline_Display::appendOutput);
  connect(simuConfig, &Simu_Config::CreateAndStartThread, this, [=]() {
    auto *tv = timelineDisplay->timelineView();
    tv->Num_ap = simuConfig->Num_ap;
    tv->Num_sta = simuConfig->Num_sta;
    if (timelineDisplay)
      timelineDisplay->resetPage();
    simuConfig->Create_And_StartThread();

    switchTo(6);
  });

  connect(simuConfig, &Simu_Config::AddAp, this, [=]() { switchTo(3); });

  connect(simuConfig, &Simu_Config::AddSta, this, [=]() { switchTo(2); });

  /*Ap_Config*/
  connect(apConfigPage, &Ap_config::Finish_setting_ap, this,
          [=]() { switchTo(1); });

  connect(apConfigPage, &Ap_config::Page1, this,
          [=]() { apConfigPage->setPosition(ap_now); });
  connect(apConfigPage, &Ap_config::Page2, this,
          [=]() { apConfigPage->setMobility(ap_now); });
  connect(apConfigPage, &Ap_config::Edca_to_config, this,
          [=]() { switchTo(4); });

  connect(apConfigPage, &Ap_config::Antenna_to_config, this,
          [=]() { switchTo(5); });

  connect(apConfigPage, &Ap_config::Traffic_Set, this,
          [=]() { apConfigPage->Get_Traffic_Config(ap_now); });

  connect(apConfigPage, &Ap_config::RemoveLastTraffic, this, [=]() {
    if (!ap_now.Traffic_list.empty())
      ap_now.Traffic_list.pop_back();
  });

  connect(apConfigPage, &Ap_config::LoadOneApConfig, this, [=]() {
    apConfigPage->Load_One_Config(this->ap_now);
    apConfigPage->Get_Edca_Config(ap_now, *(edcaConfig));
    apConfigPage->Get_Antenna_Config(ap_now, *(antenna));
    jsonhelper.SetApToJson(&ap_now, apConfigPage->ApIndex);
    ap_now.Traffic_list.clear();
    ap_now.Antenna_list.clear();
    emit simuConfig->update();
  });

  /*Sta_Config*/
  connect(nodeConfigPage, &node_config::Finish_setting_sta, this,
          [=]() { switchTo(1); });
  connect(nodeConfigPage, &node_config::Page1, this,
          [=]() { nodeConfigPage->setPosition(sta_now); });
  connect(nodeConfigPage, &node_config::Page2, this,
          [=]() { nodeConfigPage->setMobility(sta_now); });
  connect(nodeConfigPage, &node_config::Edca_to_config, this,
          [=]() { switchTo(4); });
  connect(nodeConfigPage, &node_config::Antenna_to_config, this,
          [=]() { switchTo(5); });
  connect(nodeConfigPage, &node_config::Traffic_Set, this,
          [=]() { nodeConfigPage->Get_Traffic_Config(sta_now); });

  connect(apConfigPage, &Ap_config::RemoveLastTraffic, this, [=]() {
    if (!ap_now.Traffic_list.empty())
      ap_now.Traffic_list.pop_back();
  });

  connect(nodeConfigPage, &node_config::LoadOneStaConfig, this, [=]() {
    nodeConfigPage->Load_One_Config(sta_now);
    nodeConfigPage->Get_Edca_Config(sta_now, *edcaConfig);
    nodeConfigPage->Get_Antenna_Config(sta_now, *antenna);
    jsonhelper.SetStaToJson(&sta_now, nodeConfigPage->StaIndex);
    sta_now.Traffic_list.clear();
    sta_now.Antenna_list.clear();
    emit simuConfig->update();
  });

  /*Edca_Config*/
  connect(edcaConfig, &Edca_config::BackToLastPage, this, [=]() { back(); });

  /*Antenna_Config*/
  connect(antenna, &Antenna::BackToLastPage, this, [=]() { back(); });

  /*Timeline_Display*/
  connect(simuConfig, &Simu_Config::ppduReady, timelineDisplay->timelineView(),
          &PpduTimelineView::append, Qt::QueuedConnection);
  connect(simuConfig, &Simu_Config::ppduReady, timelineDisplay,
          &Timeline_Display::appendPpdu, Qt::QueuedConnection);
    connect(simuConfig, &Simu_Config::sniffFailed, timelineDisplay,
      &Timeline_Display::showSniffFail, Qt::QueuedConnection);
  /*Timeline_Display*/
  connect(timelineDisplay->timelineView(), &PpduTimelineView::quit_simulation,
          this, [=]() {
            qDebug() << "[MainWindow] quit_simulation received";

            if (simuConfig) {
              simuConfig->requestCleanup();
            }
            switchTo(stack->indexOf(greetingPage));
            resetMain();
          });

  /*Status Bar*/
  QStatusBar *status = new QStatusBar(this);
  setStatusBar(status);
  status->showMessage("Ready");

  showMaximized();
}
MainWindow::~MainWindow() {
  qDebug() << "MainWindow destroyed";
  QThreadPool::globalInstance()->clear(); // 取消未开始任务
}

void MainWindow::switchTo(int index) {
  history.push(stack->currentIndex());
  stack->setCurrentIndex(index);
}

void MainWindow::back() {
  if (!history.isEmpty())
    stack->setCurrentIndex(history.pop());
}

void MainWindow::closeEvent(QCloseEvent *event) {
  qDebug() << "MainWindow closeEvent";

  // 取消未开始的线程任务
  QThreadPool::globalInstance()->clear();

  event->accept();
}

void MainWindow::resetMain() {
  qDebug() << "[MainWindow] resetMain()";

  // ===============================
  // 1️⃣ 清空导航历史
  // ===============================ap
  history.clear();

  // ===============================
  // 2️⃣ 停止 & reset 仿真核心页
  // ===============================
  if (simuConfig) {
    simuConfig->resetPage();
  }

  // ===============================
  // 3️⃣ reset 所有页面（UI 状态）
  // ===============================
  if (page1)
    page1->resetPage();
  if (nodeConfigPage)
    nodeConfigPage->resetPage();
  if (apConfigPage)
    apConfigPage->resetPage();
  if (edcaConfig)
    edcaConfig->resetPage();
  if (antenna)
    antenna->resetPage();
  if (timelineDisplay)
    timelineDisplay->resetPage();
  if (greetingPage)
    greetingPage->resetPage();

  // ===============================
  // 4️⃣ 清空运行期数据结构
  // ===============================
  ap_now = Ap{};
  sta_now = Sta{};
  buildingConfig = BuildingConfig{};
  jsonhelper.reset();
  // ===============================
  // 5️⃣ 回到首页
  // ===============================
  stack->setCurrentIndex(stack->indexOf(greetingPage));

  qDebug() << "[MainWindow] resetAll() done";
}

void MainWindow::onBrowseNs3Dir() {
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Select NS-3 Directory"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (dir.isEmpty())
    return;

  if (isValidNs3Directory(dir)) {
    ns3PathValid = true;
    this->greetingPage->ns3Path = dir;
    this->page1->ns3Path = dir;
    this->page1->refreshModelLists();
    if (simuConfig)
      simuConfig->setNs3Path(dir);
    greetingPage->setNs3Path(dir);
    // QMessageBox::information(this, tr("NS-3"),
    //                          tr("Valid NS-3 directory selected."));
  } else {
    QMessageBox::warning(
        this, tr("NS-3"),
        tr("The selected directory is not a valid NS-3 directory."));
        ns3PathValid = false;
  }
}

bool MainWindow::isValidNs3Directory(const QString &path) {
  QDir dir(path);

  if (!dir.exists())
    return false;

  return dir.exists("src") && dir.exists("scratch");
}
