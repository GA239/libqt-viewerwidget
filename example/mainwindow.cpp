#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QListView>
#include <qsplitter.h>

#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Viewer Example");
    this->setStyleSheet( " background-color: white; " );
    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() << "../resourses/1.png"
                                             << "../resourses/2.png"
                                             << "../resourses/3.png");

    this->viewer =  new ViewerWidget();
    this->viewer->setModel(this->model);

    QAction *open = this->ui->mainToolBar->addAction(QIcon("../resourses/add.png"), "New File");
    QAction *remove = this->ui->mainToolBar->addAction(QIcon("../resourses/delete.png"), "delete");
    this->ui->mainToolBar->addSeparator();
    QAction *zoomIn = this->ui->mainToolBar->addAction(QIcon("../resourses/zoomIn.png"), "Zoom in File");
    QAction *zoomOut = this->ui->mainToolBar->addAction(QIcon("../resourses/zoomOut.png"), "Zoom out File");
    QAction *fullScreen = this->ui->mainToolBar->addAction(QIcon("../resourses/full.png"), "Full screen");
    this->ui->mainToolBar->addSeparator();
    QAction *previous = this->ui->mainToolBar->addAction(QIcon("../resourses/larrow.png"), "Previous");
    QAction *next = this->ui->mainToolBar->addAction(QIcon("../resourses/rarrow.png"), "Next");

    connect(open, SIGNAL(triggered()), this, SLOT(openNewItem()));
    connect(remove, SIGNAL(triggered()), this, SLOT(deleteCurrentItem()));
    connect(zoomIn, SIGNAL(triggered()), this->viewer, SLOT(zoomIn()));
    connect(zoomOut, SIGNAL(triggered()), this->viewer, SLOT(zoomOut()));
    connect(fullScreen, SIGNAL(triggered()), this->viewer, SLOT(showInFullScreen()));
    connect(previous, SIGNAL(triggered()), this->viewer, SLOT(showPrev()));
    connect(next, SIGNAL(triggered()), this->viewer, SLOT(showNext()));

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    this->ui->centralWidget->setLayout(verticalLayout);
    this->ui->centralWidget->layout()->addWidget(this->viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief opens a dialog to add a new image to the model
 */
void MainWindow::openNewItem()
{
    QString url = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(),
                                               "Images (*.png *.xpm *.jpg);;All files (*.*)");
    if (!url.isEmpty()) {
        if (!this->viewer->addItem(url))
            QMessageBox::information(this, tr("Warning"),tr("Error adding!"));
    }
    return;
}
/**
 * @brief removes the current image from the model
 */
void MainWindow::deleteCurrentItem()
{
    if (this->viewer->currentItem().isValid()) {
        QMessageBox msgBox(QMessageBox::Warning,tr("Warning"),
                           tr("Are you really want to delete this file?"),0, this);
        msgBox.addButton(tr("Yes"),QMessageBox::AcceptRole);
        msgBox.addButton(tr("No"),QMessageBox::RejectRole);

        if (msgBox.exec() == QMessageBox::AcceptRole)
            this->viewer->deleteCurentItem();
    } else {
        QMessageBox::information(this,tr("Warning"), tr("Image not available"));
    }
    return;
}
