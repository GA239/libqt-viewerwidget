#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../viewer/viewerwidget.h"
#include <QStringListModel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ViewerWidget* viewer;
    QStringListModel *model;

    QPushButton* createPushButton(QString url);
};

#endif // MAINWINDOW_H
