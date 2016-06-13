#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../src/viewerwidget.h"
#include <QStringListModel>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void openNewItem();
    void deleteCurrentItem();

private:
    Ui::MainWindow *ui;
    ViewerWidget* viewer;
    QStringListModel *model;
};

#endif // MAINWINDOW_H
