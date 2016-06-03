#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() <<"../resourses/1.jpg" << "../resourses/1.png");
    this->viewer =  new ViewerWidget();
    this->viewer->setModel(this->model);

    QListView *listView = new QListView();
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setModel(this->model);

    this->viewer->setSelectionModel(listView->selectionModel());

    QVBoxLayout *verLayout = new QVBoxLayout;
    //verLayout->addWidget(this->viewer);
    this->ui->centralWidget->setLayout(verLayout);

    this->ui->centralWidget->layout()->addWidget(this->viewer);

}

MainWindow::~MainWindow()
{
    delete ui;
}
