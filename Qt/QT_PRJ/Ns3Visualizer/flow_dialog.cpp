#include "flow_dialog.h"
#include "ui_flow_dialog.h"
#include "random_variable_dialog.h"

flow_dialog::flow_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::flow_dialog)
{
    ui->setupUi(this);
    setupConnections();
    
    // 初始化默认参数
    m_ontimeParams["Value"] = 1.0;
    m_offtimeParams["Value"] = 1.0;
}

flow_dialog::~flow_dialog()
{
    delete ui;
}

void flow_dialog::setupConnections()
{
    // 连接 OnTime 类型变化信号
    connect(ui->comboBox_ontime_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &flow_dialog::onOntimeTypeChanged);
    
    // 连接 OffTime 类型变化信号
    connect(ui->comboBox_offtime_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &flow_dialog::onOfftimeTypeChanged);
}

void flow_dialog::onOntimeTypeChanged(int index)
{
    QString type = ui->comboBox_ontime_type->currentText();
    showRandomVariableDialog(type, m_ontimeParams, tr("OnTime Random Variable"));
}

void flow_dialog::onOfftimeTypeChanged(int index)
{
    QString type = ui->comboBox_offtime_type->currentText();
    showRandomVariableDialog(type, m_offtimeParams, tr("OffTime Random Variable"));
}

void flow_dialog::showRandomVariableDialog(const QString &type, QMap<QString, double> &params, const QString &title)
{
    RandomVariableDialog dialog(type, this);
    dialog.setWindowTitle(title);
    
    // 如果已有参数，设置到对话框
    if (!params.isEmpty()) {
        dialog.setParameters(params);
    }
    
    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        params = dialog.getParameters();
        
        // 更新显示值（可选：在 lineEdit 中显示参数摘要）
        QString summary;
        for (auto it = params.begin(); it != params.end(); ++it) {
            if (!summary.isEmpty()) summary += ", ";
            summary += QString("%1=%2").arg(it.key()).arg(it.value());
        }
        
        // 根据是 OnTime 还是 OffTime 更新对应的 lineEdit
        if (title.contains("OnTime")) {
            ui->lineEdit_ontime_value->setText(summary);
        } else if (title.contains("OffTime")) {
            ui->lineEdit_offtime_value->setText(summary);
        }
    }
}

FlowConfig flow_dialog::getFlowConfig() const
{
    FlowConfig config;
    
    // 获取当前活动的标签页
    int currentIndex = ui->tabWidget->currentIndex();
    
    if (currentIndex == 0) { // OnOff 页面
        config.flowType = FlowConfig::OnOff;
        config.flowId = ui->lineEdit_flowid_onoff->text();
        config.dataRate = ui->doubleSpinBox_datarate->value();
        config.packetSize = ui->spinBox_packetsize->value();
        config.ontimeType = ui->comboBox_ontime_type->currentText();
        config.ontimeParams = m_ontimeParams;
        config.offtimeType = ui->comboBox_offtime_type->currentText();
        config.offtimeParams = m_offtimeParams;
        config.maxBytes = ui->spinBox_maxbytes->value();
        config.protocol = ui->comboBox_protocol->currentText();
        config.tos = ui->spinBox_tos->value();
        config.startTime = ui->doubleSpinBox_starttime_onoff->value();
        config.endTime = ui->doubleSpinBox_endtime_onoff->value();
        config.destination = ui->comboBox_direction_onoff->currentText();
    }
    else if (currentIndex == 1) { // CBR 页面
        config.flowType = FlowConfig::CBR;
        config.flowId = ui->lineEdit_flowid_cbr->text();
        config.packetSize = ui->spinBox_packetsize_cbr->value();
        config.interval = ui->doubleSpinBox_interval_cbr->value();
        config.maxPackets = ui->spinBox_maxpackets_cbr->value();
        config.protocol = ui->comboBox_protocol_cbr->currentText();
        config.tos = ui->spinBox_tos_cbr->value();
        config.startTime = ui->doubleSpinBox_starttime_cbr->value();
        config.endTime = ui->doubleSpinBox_endtime_cbr->value();
        config.destination = ui->comboBox_direction_cbr->currentText();
    }
    else if (currentIndex == 2) { // Bulk 页面
        config.flowType = FlowConfig::Bulk;
        config.flowId = ui->lineEdit_flowid_bulk->text();
        config.maxBytes = ui->spinBox_maxbytes_bulk->value();
        config.protocol = ui->comboBox_protocol_bulk->currentText();
        config.tos = ui->spinBox_tos_bulk->value();
        config.startTime = ui->doubleSpinBox_starttime_bulk->value();
        config.endTime = ui->doubleSpinBox_endtime_bulk->value();
        config.destination = ui->comboBox_direction_bulk->currentText();
    }
    
    return config;
}

void flow_dialog::setFlowConfig(const FlowConfig &config)
{
    // 根据流量类型切换到对应的标签页
    switch (config.flowType) {
        case FlowConfig::OnOff:
            ui->tabWidget->setCurrentIndex(0);
            ui->lineEdit_flowid_onoff->setText(config.flowId);
            ui->doubleSpinBox_datarate->setValue(config.dataRate);
            ui->spinBox_packetsize->setValue(config.packetSize);
            ui->comboBox_ontime_type->setCurrentText(config.ontimeType);
            m_ontimeParams = config.ontimeParams;
            ui->comboBox_offtime_type->setCurrentText(config.offtimeType);
            m_offtimeParams = config.offtimeParams;
            ui->spinBox_maxbytes->setValue(config.maxBytes);
            ui->comboBox_protocol->setCurrentText(config.protocol);
            ui->spinBox_tos->setValue(config.tos);
            ui->doubleSpinBox_starttime_onoff->setValue(config.startTime);
            ui->doubleSpinBox_endtime_onoff->setValue(config.endTime);
            ui->comboBox_direction_onoff->setCurrentText(config.destination);
            break;
            
        case FlowConfig::CBR:
            ui->tabWidget->setCurrentIndex(1);
            ui->lineEdit_flowid_cbr->setText(config.flowId);
            ui->spinBox_packetsize_cbr->setValue(config.packetSize);
            ui->doubleSpinBox_interval_cbr->setValue(config.interval);
            ui->spinBox_maxpackets_cbr->setValue(config.maxPackets);
            ui->comboBox_protocol_cbr->setCurrentText(config.protocol);
            ui->spinBox_tos_cbr->setValue(config.tos);
            ui->doubleSpinBox_starttime_cbr->setValue(config.startTime);
            ui->doubleSpinBox_endtime_cbr->setValue(config.endTime);
            ui->comboBox_direction_cbr->setCurrentText(config.destination);
            break;
            
        case FlowConfig::Bulk:
            ui->tabWidget->setCurrentIndex(2);
            ui->lineEdit_flowid_bulk->setText(config.flowId);
            ui->spinBox_maxbytes_bulk->setValue(config.maxBytes);
            ui->comboBox_protocol_bulk->setCurrentText(config.protocol);
            ui->spinBox_tos_bulk->setValue(config.tos);
            ui->doubleSpinBox_starttime_bulk->setValue(config.startTime);
            ui->doubleSpinBox_endtime_bulk->setValue(config.endTime);
            ui->comboBox_direction_bulk->setCurrentText(config.destination);
            break;
    }
}
