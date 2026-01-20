#include "page1_model_chose.h"
#include "ui_page1_model_chose.h"

Page1_model_chose::Page1_model_chose(QWidget *parent)
    : QWidget(parent), ui(new Ui::Page1_model_chose)
{
    ui->setupUi(this);
    centerWindow(this);

    auto *tb = ui->textBrowser;
    tb->setContentsMargins(0, 0, 0, 0);
    tb->document()->setDocumentMargin(2);

    ui->listWidget->setCornerWidget(0);
    ui->listWidget->setCurrentRow(0);

    ui->textBrowser_2->document()->setDefaultFont(
    ui->textBrowser_2->font());

}

QString Page1_model_chose::GetSceneName()
{
    this->sceneName.clear();

    QWidget *page = ui->toolBox->currentWidget();
    if (!page)
        return "";

    QListWidget *lw = page->findChild<QListWidget *>("listWidget");
    if (!lw)
        lw = page->findChild<QListWidget *>("listWidget_2");

    if (!lw)
        return "";

    QListWidgetItem *item = lw->currentItem();
    if (!item)
        return "";

    this->sceneName = item->text();
    return this->sceneName;
}


Page1_model_chose::~Page1_model_chose()
{
    delete ui;
}

void Page1_model_chose::on_pushButton_4_clicked()
{
    emit BackToMain();
}

void Page1_model_chose::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();

    QString name = GetSceneName();

    if (name.isEmpty())
        ui->textBrowser->append("No scene selected.");
    else
        ui->textBrowser->append(name);

    ui->label_3->setPixmap(QPixmap(
        "/home/zk/Visualization/ns-3.46/contrib/SniffUtils/Simulation/Designed/Test_Design_1/PPDU_TIMELINE/ppdu_timeline.png"));
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setScaledContents(true);
}


void Page1_model_chose::on_pushButton_3_clicked()
{
    if (ui->checkBox->isChecked())
    {
        this->close();
        this->simu_config->showMaximized();
        ;
    }
    else
    {
        ;
    }
}

void Page1_model_chose::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==Qt::Checked)
    {
        this->hide();
        this->simu_config->showMaximized();
    }
}

