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

    ui->label_3->installEventFilter(this);
}

void Page1_model_chose::resetPage()
{
    // 1️⃣ 逻辑数据
    sceneName.clear();
    Scene.clear();   // 你头文件里还有一个 Scene，别忘了

    // 2️⃣ ToolBox 回到第一页
    if (ui->toolBox && ui->toolBox->count() > 0)
        ui->toolBox->setCurrentIndex(0);

    // 3️⃣ 主 listWidget
    if (ui->listWidget)
    {
        ui->listWidget->setCurrentRow(-1);
        if (ui->listWidget->count() > 0)
            ui->listWidget->setCurrentRow(0);
    }

    // 4️⃣ 第二个 listWidget（如果存在）
    if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
    {
        lw2->setCurrentRow(-1);
        if (lw2->count() > 0)
            lw2->setCurrentRow(0);
    }

    // 5️⃣ 文本区
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();

    // 6️⃣ 预览区
    ui->label_3->clear();
    ui->label_3->setText("No Preview");
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setScaledContents(false);

    // 7️⃣ 滚动条复位
    if (ui->textBrowser->verticalScrollBar())
        ui->textBrowser->verticalScrollBar()->setValue(0);

    if (ui->textBrowser_2->verticalScrollBar())
        ui->textBrowser_2->verticalScrollBar()->setValue(0);

    qDebug() << "[Page1_model_chose] resetPage() done";
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
        "/home/zk/Visualization/ns-3.46/contrib/SniffUtils/Simulation/Designed/Test_Design_1/PPDU_TIMELINE/picture.png"));
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setScaledContents(true);
}


void Page1_model_chose::on_pushButton_3_clicked()
{
   emit ConfigSimulation();
}


bool Page1_model_chose::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_3 &&
        event->type() == QEvent::MouseButtonDblClick)
    {
        QPixmap pix = ui->label_3->pixmap();
        if (!pix.isNull())
        {
            ImageViewer *viewer = new ImageViewer(pix);
            viewer->setAttribute(Qt::WA_DeleteOnClose);
            viewer->show();
        }
        return true;
    }
    return QWidget::eventFilter(obj, event);
}


void Page1_model_chose::on_pushButton_clicked()
{
    emit ConfigSimulation();
}

