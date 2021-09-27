#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/InfoAssembling.h"

#include <QFileDialog>
#include <QTextCodec>


const std::string strOpendriveFilters = "*.xodr";
const std::string strWindowTitle = "导入OpenDRIVE";
const std::string strFindPath = "查找路径：";
const std::string strFileName = "文件名：";
const std::string strFileType = "文件类型：";
const std::string strCancel = "取消";
const std::string strOpen = "打开";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
    initPtr();
    initSignalSlots();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_pXodr;
}

void MainWindow::initUI()
{
    initWindow();
    initCenterView();
}

void MainWindow::initWindow()
{
    this->showMaximized();
}

void MainWindow::initCenterView()
{
    m_pScene = new QGraphicsScene(-860000, -540000, 1920000, 1080000);

    ui->mainwindowView->setScene(m_pScene);
}

void MainWindow::initPtr()
{
    m_pXodr = new xodr();
}

void MainWindow::initSignalSlots()
{
    connect(this, &MainWindow::sigChangeMap, this, &MainWindow::slotChangeMap);
}

void MainWindow::on_actionOpen_triggered()
{
    if(nullptr != __INFOASSEMBLE->getRoadMapItem())
    {
       __INFOASSEMBLE->roadMapItemReset();
    }

    m_pScene->clear();

    QFileDialog *pQFileDlg = new QFileDialog(this);
    pQFileDlg->setAcceptMode(QFileDialog::AcceptOpen);
    pQFileDlg->setLabelText(QFileDialog::LookIn, strFindPath.c_str());
    pQFileDlg->setLabelText(QFileDialog::FileName, strFileName.c_str());
    pQFileDlg->setLabelText(QFileDialog::FileType, strFileType.c_str());
    pQFileDlg->setLabelText(QFileDialog::Accept, strOpen.c_str());
    pQFileDlg->setLabelText(QFileDialog::Reject, strCancel.c_str());
    pQFileDlg->setWindowTitle(strWindowTitle.c_str());
//    pQFileDlg->setWindowFlag(Qt::WindowContextHelpButtonHint, false);//禁用帮助按钮
//    pQFileDlg->setWindowFlag(Qt::WindowMaximizeButtonHint, false);//禁用最大/小化按钮
    pQFileDlg->setOption(QFileDialog::DontUseNativeDialog, true);//不使用默认对话框
    pQFileDlg->activateWindow();

    QStringList filters;
    filters << strOpendriveFilters.c_str();
    pQFileDlg->setNameFilters(filters);
//    pQFileDlg->setDirectory(QDir(Getpath::getInstance()->getPath())); // TODO application
    pQFileDlg->setSizeGripEnabled(false);

    if(pQFileDlg->exec() != QDialog::Accepted)
    {
        return;
    }

    if(0 == pQFileDlg->selectedFiles().size())
    {
        return;
    }

    std::string  strFileName = pQFileDlg->selectedFiles()[0].toStdString();
    // TODO 做后缀检测

    if(strFileName.empty())
    {
        return;
    }

    emit sigChangeMap(strFileName);
}

bool MainWindow::slotChangeMap(std::string strOpendriveFilePath)
{
    if(strOpendriveFilePath.empty())
    {
        return false;
    }

    std::string strPath;

#ifdef WIN32
    strPath = QTextCodec::codecForName("GBK")->fromUnicode(strPath.c_str()).data();
#else
    strPath = QTextCodec::codecForName("UTF-8")->fromUnicode(strOpendriveFilePath.c_str()).data();
#endif

    std::cout << "Loading filename ... " << strPath << std::endl;

    m_pXodr->load(strPath);
    m_pXodr->parse();

    __MAPDATA->setLaneOffsetOpposite(m_pXodr->m_OpenDRIVE->m_roads);
    __MAPDATA->setSGeometryOpposite(m_pXodr->m_OpenDRIVE->m_roads);

    __INFOASSEMBLE->transferRoadMapInfo(m_pXodr->m_OpenDRIVE->m_roads);
    m_pScene->addItem(const_cast<RoadMapItem*>(__INFOASSEMBLE->getRoadMapItem()));
    ui->mainwindowView->centerOn(__INFOASSEMBLE->getRoadMapItem());

    return true;
}
