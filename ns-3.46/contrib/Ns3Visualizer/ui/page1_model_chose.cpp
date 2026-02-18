#include "page1_model_chose.h"
#include "ui_page1_model_chose.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QToolBox>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

#include "visualizer_config.h"

Page1_model_chose::Page1_model_chose(QWidget *parent)
    : QWidget(parent), ui(new Ui::Page1_model_chose)
{
    ui->setupUi(this);
    centerWindow(this);

    auto *tb = ui->textBrowser;
    tb->setContentsMargins(0, 0, 0, 0);
    tb->document()->setDocumentMargin(2);

    if (ui->listWidget)
        ui->listWidget->clear();
    if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
        lw2->clear();
    if (auto *lw3 = findChild<QListWidget *>("listWidget_3"))
        lw3->clear();

    ui->listWidget->setCornerWidget(0);
    ui->listWidget->setCurrentRow(0);

    ui->textBrowser_2->document()->setDefaultFont(
    ui->textBrowser_2->font());

    ui->label_3->installEventFilter(this);
    ui->pushButton_5->setText("Select");
    //ui->pushButton->setEnabled(false);

    connect(ui->listWidget, &QListWidget::currentItemChanged, this,
            [=]() { updateMarkdownForSelection(); });
    if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
    {
        connect(lw2, &QListWidget::currentItemChanged, this,
                [=]() { updateMarkdownForSelection(); });
    }
        if (auto *lw3 = findChild<QListWidget *>("listWidget_3"))
        {
        connect(lw3, &QListWidget::currentItemChanged, this,
            [=]() { updateMarkdownForSelection(); });
        }

    if (ui->toolBox)
    {
        connect(ui->toolBox, &QToolBox::currentChanged, this, [=](int) {
            QListWidget *lw = currentSceneList();
            if (lw && lw->currentRow() < 0 && lw->count() > 0)
                lw->setCurrentRow(0);
            updateMarkdownForSelection();
        });
    }
}

void Page1_model_chose::resetPage()
{
    sceneName.clear();
    Scene.clear();   

    refreshModelLists();

    if (ui->toolBox && ui->toolBox->count() > 0)
        ui->toolBox->setCurrentIndex(0);


    if (ui->listWidget)
    {
        ui->listWidget->setCurrentRow(-1);
        if (ui->listWidget->count() > 0)
            ui->listWidget->setCurrentRow(0);
    }

    if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
    {
        lw2->setCurrentRow(-1);
        if (lw2->count() > 0)
            lw2->setCurrentRow(0);
    }

    if (auto *lw3 = findChild<QListWidget *>("listWidget_3"))
    {
        lw3->setCurrentRow(-1);
        if (lw3->count() > 0)
            lw3->setCurrentRow(0);
    }

    ui->textBrowser->clear();
    ui->textBrowser_2->clear();

    ui->label_3->clear();
    ui->label_3->setText("No Preview");
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setScaledContents(false);

    if (ui->textBrowser->verticalScrollBar())
        ui->textBrowser->verticalScrollBar()->setValue(0);

    if (ui->textBrowser_2->verticalScrollBar())
        ui->textBrowser_2->verticalScrollBar()->setValue(0);

    qDebug() << "[Page1_model_chose] resetPage() done";
}

QListWidget *Page1_model_chose::currentSceneList() const
{
    QWidget *page = ui->toolBox->currentWidget();
    if (!page)
        return nullptr;

    QListWidget *lw = page->findChild<QListWidget *>("listWidget");
    if (!lw)
        lw = page->findChild<QListWidget *>("listWidget_2");
    if (!lw)
        lw = page->findChild<QListWidget *>("listWidget_3");

    return lw;
}

QString Page1_model_chose::currentSceneBaseDir() const
{
    QWidget *page = ui->toolBox->currentWidget();
    if (!page)
        return "";

    if (page->findChild<QListWidget *>("listWidget"))
        return ns3Path + "/contrib/Ns3Visualizer/Simulation/Default/Simple";
    if (page->findChild<QListWidget *>("listWidget_2"))
        return ns3Path + "/contrib/Ns3Visualizer/Simulation/Default/Complex";
    if (page->findChild<QListWidget *>("listWidget_3"))
        return ns3Path + "/scratch";

    return "";
}

void Page1_model_chose::refreshModelLists()
{
    if (ui->listWidget)
        ui->listWidget->clear();

    if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
        lw2->clear();
    if (auto *lw3 = findChild<QListWidget *>("listWidget_3"))
        lw3->clear();

    if (ns3Path.isEmpty())
        return;

    QDir simpleDir(ns3Path + "/contrib/Ns3Visualizer/Simulation/Default/Simple");
    if (simpleDir.exists() && ui->listWidget)
    {
        QStringList dirs = simpleDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot,
                                               QDir::Name);
        for (const QString &name : dirs)
            ui->listWidget->addItem(name);
        if (ui->listWidget->count() > 0)
            ui->listWidget->setCurrentRow(0);
    }

    QDir complexDir(ns3Path + "/contrib/Ns3Visualizer/Simulation/Default/Complex");
    if (complexDir.exists())
    {
        if (auto *lw2 = findChild<QListWidget *>("listWidget_2"))
        {
            QStringList dirs = complexDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot,
                                                    QDir::Name);
            for (const QString &name : dirs)
                lw2->addItem(name);
            if (lw2->count() > 0)
                lw2->setCurrentRow(0);
        }
    }

    QDir scratchDir(ns3Path + "/scratch");
    if (scratchDir.exists())
    {
        if (auto *lw3 = findChild<QListWidget *>("listWidget_3"))
        {
            QStringList files = scratchDir.entryList(QStringList() << "*.cc",
                                                     QDir::Files | QDir::Readable,
                                                     QDir::Name);
            for (const QString &file : files)
            {
                QString name = file;
                if (name.endsWith(".cc"))
                    name.chop(3);
                lw3->addItem(name);
            }
            if (lw3->count() > 0)
                lw3->setCurrentRow(0);
        }
    }
}

void Page1_model_chose::updateMarkdownForSelection()
{
    QListWidget *lw = currentSceneList();
    if (!lw || !lw->currentItem())
    {
        ui->textBrowser_2->clear();
        return;
    }

    if (lw->objectName() == "listWidget_3")
    {
        ui->textBrowser_2->clear();
        ui->label_3->clear();
        ui->label_3->setText("No Preview");
        ui->label_3->setAlignment(Qt::AlignCenter);
        ui->label_3->setScaledContents(false);
        return;
    }

    const QString baseDir = currentSceneBaseDir();
    if (baseDir.isEmpty())
    {
        ui->textBrowser_2->clear();
        return;
    }

    const QString sceneName = lw->currentItem()->text();
    const QString mdPath = baseDir + "/" + sceneName + "/info.md";

    QFile mdFile(mdPath);
    if (!mdFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->textBrowser_2->clear();
        return;
    }

    QTextStream in(&mdFile);
    const QString content = in.readAll();
    ui->textBrowser_2->document()->setMarkdown(content);
}



QString Page1_model_chose::GetSceneName()
{
    this->sceneName.clear();

    QListWidget *lw = currentSceneList();
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

    const QString baseDir = currentSceneBaseDir();
    if (!baseDir.isEmpty() && !name.isEmpty())
    {
        QListWidget *lw = currentSceneList();
        if (lw && lw->objectName() == "listWidget_3")
        {
            ui->label_3->clear();
            ui->label_3->setText("No Preview");
            ui->label_3->setAlignment(Qt::AlignCenter);
            ui->label_3->setScaledContents(false);
            return;
        }

        const QString sceneDir = baseDir + "/" + name;

        const QString ccPath = sceneDir + "/" + name + ".cc";
        const QString scratchPath = ns3Path + "/scratch/" + name + ".cc";
        if (QFile::exists(ccPath))
        {
            if (QFile::exists(scratchPath))
                QFile::remove(scratchPath);
            QFile::copy(ccPath, scratchPath);
        }

        const QString jpgPath = sceneDir + "/" + name + ".jpg";
        QPixmap pix(jpgPath);
        if (!pix.isNull())
        {
            ui->label_3->setPixmap(pix);
            ui->label_3->setAlignment(Qt::AlignCenter);
            ui->label_3->setScaledContents(true);
        }
        else
        {
            ui->label_3->clear();
            ui->label_3->setText("No Preview");
            ui->label_3->setAlignment(Qt::AlignCenter);
            ui->label_3->setScaledContents(false);
        }
    }
}


void Page1_model_chose::on_pushButton_3_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("PPDU Settings"));
    dialog.setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *title = new QLabel(tr("Choose precise mode and sampling rate"), &dialog);
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

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                                     Qt::Horizontal, &dialog);
    mainLayout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return;

    const bool precise = preciseCheck->isChecked();
    g_ppduViewConfig.preciseMode.store(precise);
    g_ppduViewConfig.absoluteRate.store(precise);
    g_ppduViewConfig.sampleRate.store(precise ? 1 : sampleSpin->value());

    emit RunSelectedSimulation();
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

void Page1_model_chose::setJsonHelper(JsonHelper *helper) {
    m_jsonHelper = helper;
}

void Page1_model_chose::on_load_button_clicked() {
    // Ask user to select a project file
    QString openFilePath = QFileDialog::getOpenFileName(
        this,
        tr("Load Project File"),
        QDir::homePath(),
        tr("NS3 Project Files (*.nsproj);;All Files (*)"));

    if (openFilePath.isEmpty()) {
        return;  // User cancelled
    }

    // Emit signal to let MainWindow handle the loading with its jsonHelper
    emit LoadProjectRequested(openFilePath);
}

