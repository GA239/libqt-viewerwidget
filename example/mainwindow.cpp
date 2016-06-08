#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QListView>
#include <qsplitter.h>

#include <QToolBar>
#include <QIcon>
#include <QAction>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Viewer Example");
    this->setStyleSheet( " background-color: white; " );
    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() << "../resourses/1.png" << "../resourses/2.png" << "../resourses/3.png");

    this->viewer =  new ViewerWidget();
    //this->viewer->setModel(this->model);


    QAction *open = this->ui->mainToolBar->addAction(QIcon("../resourses/add.png"), "New File");
    this->ui->mainToolBar->addSeparator();
    QAction *zoomIn = this->ui->mainToolBar->addAction(QIcon("../resourses/zoomIn.png"), "Zoom in File");
    QAction *zoomOut = this->ui->mainToolBar->addAction(QIcon("../resourses/zoomOut.png"), "Zoom out File");
    QAction *full = this->ui->mainToolBar->addAction(QIcon("../resourses/full.png"), "Full screen");
    this->ui->mainToolBar->addSeparator();
    QAction *previous = this->ui->mainToolBar->addAction(QIcon("../resourses/larrow.png"), "Previous");
    QAction *next = this->ui->mainToolBar->addAction(QIcon("../resourses/rarrow.png"), "Next");

    connect(open, SIGNAL(triggered()), this, SLOT(open()));
    connect(zoomIn, SIGNAL(triggered()), this->viewer, SLOT(zoomIn()));
    connect(zoomOut, SIGNAL(triggered()), this->viewer, SLOT(zoomOut()));
    connect(full, SIGNAL(triggered()), this->viewer, SLOT(showInFullScreen()));
    connect(previous, SIGNAL(triggered()), this->viewer, SLOT(showPrev()));
    connect(next, SIGNAL(triggered()), this->viewer, SLOT(showNext()));

    QVBoxLayout *verLayout = new QVBoxLayout;
    this->ui->centralWidget->setLayout(verLayout);
    this->ui->centralWidget->layout()->addWidget(this->viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.png *.xpm *.jpg);;All files (*.*)");
}

