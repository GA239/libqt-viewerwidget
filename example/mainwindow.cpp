#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QListView>

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
    this->viewer->setModel(this->model);

    QListView *listView = new QListView();
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setModel(this->model);

    this->viewer->setSelectionModel(listView->selectionModel());

    QWidget *segBtn = new QWidget(this);
    segBtn->setLayout(new QHBoxLayout);
    segBtn->layout()->setSpacing(0);
    segBtn->layout()->setMargin(0);

    QPushButton *btnUp = this->createPushButton("../resourses/rarrow.png");
    QPushButton *btnZoomIn = this->createPushButton("../resourses/zoomIn.png");
    QPushButton *btnZoomOut = this->createPushButton("../resourses/zoomOut.png");
    QPushButton *btnDown = this->createPushButton("../resourses/larrow.png");

    segBtn->layout()->addWidget(btnDown);
    segBtn->layout()->addWidget(btnZoomIn);
    segBtn->layout()->addWidget(btnZoomOut);
    segBtn->layout()->addWidget(btnUp);
    connect(btnUp,SIGNAL(clicked()), this->viewer, SLOT(showNext()));
    connect(btnDown,SIGNAL(clicked()), this->viewer, SLOT(showPrev()));
    connect(btnZoomIn,SIGNAL(clicked()), this->viewer, SLOT(zoomIn()));
    connect(btnZoomOut,SIGNAL(clicked()), this->viewer, SLOT(zoomOut()));

    QVBoxLayout *verLayout = new QVBoxLayout;
    this->ui->centralWidget->setLayout(verLayout);
    this->ui->centralWidget->layout()->addWidget(segBtn);
    this->ui->centralWidget->layout()->addWidget(this->viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *MainWindow::createPushButton(QString url)
{
    QPushButton *btn = new QPushButton;
    btn->setFixedSize(42, 42);
    btn->setStyleSheet( " background-color: white; " );
    btn->setIcon(QIcon(url));
    btn->setIconSize(QSize(35,35));
    return btn;
}
