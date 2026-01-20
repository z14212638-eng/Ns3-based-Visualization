#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stack = ui->stackedWidget;   
    stack->setCurrentIndex(0);   

    page1 = new Page1_model_chose(this);
    simuConfig = new Simu_Config(this);
    nodeConfig = new node_config(this);
    apConfig = new Ap_config(this);
    edcaConfig = new Edca_config(this);
    antenna = new Antenna(this);

    stack->addWidget(page1);
    stack->addWidget(simuConfig);
    stack->addWidget(nodeConfig);
    stack->addWidget(apConfig);
    stack->addWidget(edcaConfig);
    stack->addWidget(antenna);

    connect(page1, &Page1_model_chose::BackToMain, this, [=]()
            { stack->setCurrentIndex(0); });

    connect(simuConfig, &Simu_Config::BackToLastPage, this, [=]()
            { stack->setCurrentIndex(1); });
    connect(simuConfig, &Simu_Config::AddSta, this, [=]()
            { stack->setCurrentIndex(2); });

    connect(simuConfig, &Simu_Config::AddAp, this, [=]()
            { stack->setCurrentIndex(3); });
    connect(apConfig, &Ap_config::Finish_setting_ap, this, [=]()
            { stack->setCurrentIndex(1); });
    connect(apConfig, &Ap_config::Edca_to_config, this, [=]()
            { stack->setCurrentIndex(4); });
    connect(apConfig, &Ap_config::Antenna_to_config, this, [=]()
            { stack->setCurrentIndex(5); });
    connect(nodeConfig, &node_config::Finish_setting_sta, this, [=]()
            { stack->setCurrentIndex(1); });
    connect(nodeConfig, &node_config::Edca_to_config, this, [=]()
            { stack->setCurrentIndex(4); });
    connect(nodeConfig, &node_config::Antenna_to_config, this, [=]()
            { stack->setCurrentIndex(5); });
    connect(edcaConfig, &Edca_config::BackToLastPage_AP, this, [=]()
            { stack->setCurrentIndex(3); });
    connect(edcaConfig, &Edca_config::BackToLastPage_STA, this, [=]()
            { stack->setCurrentIndex(2); });

    connect(antenna, &Antenna::BackToLastPage_AP, this, [=]()
            { stack->setCurrentIndex(3); });
    connect(antenna, &Antenna::BackToLastPage_STA, this, [=]()
            { stack->setCurrentIndex(2); });

    //tool bar
    QToolBar* topToolBar = new QToolBar("Top Toolbar", this);
    this->addToolBar(Qt::TopToolBarArea, topToolBar);
    topToolBar->addAction("Home");
    topToolBar->addAction("Settings");

    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0,0,0,0);

    QWidget* leftSidebar = new QWidget(central);
    leftSidebar->setFixedWidth(150);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftSidebar);
    leftLayout->addWidget(new QLabel("Left Panel"));
    leftLayout->addStretch();

    QWidget* rightSidebar = new QWidget(central);
    rightSidebar->setFixedWidth(150);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightSidebar);
    rightLayout->addWidget(new QLabel("Right Panel"));
    rightLayout->addStretch();

    stack = new QStackedWidget(central);

    page1 = new Page1_model_chose(this);
    simuConfig = new Simu_Config(this);
    stack->addWidget(page1);
    stack->addWidget(simuConfig);

    mainLayout->addWidget(leftSidebar);
    mainLayout->addWidget(stack, 1);
    mainLayout->addWidget(rightSidebar);

    QStatusBar* status = new QStatusBar(this);
    this->setStatusBar(status);
    status->showMessage("Ready");

    connect(page1, &Page1_model_chose::BackToMain, this, [=](){
        stack->setCurrentIndex(0);
    });

    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}


