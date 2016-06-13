#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include "viewerwidgetheaders.h"

class VIEWERWIDGET_COMMON_DLLSPEC ViewerWidget : public QScrollArea
{
    Q_OBJECT

public:
    ViewerWidget(QWidget *parent = 0);
    ~ViewerWidget();

    static bool isFileTypeSuported(QString filePath);
    void setModel(QAbstractItemModel *model);
    QAbstractItemModel* model(void);
    void setSelectionModel(QItemSelectionModel *selectionModel);
    QModelIndex currentItem(void);
    void setIndex(QModelIndex index, int modelathRole);
    void show(void);
    void showDefault(void);
    void autoFit(void);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    bool isModelAvailable();
    bool addItem(QString url);

signals:
    void itemChanged(QModelIndex index);

public slots:
    void showPrev();
    void showNext();
    void showInFullScreen();
    void showInWindow();
    void zoomIn();
    void zoomOut();
    void zoomToWindow();
    void deleteCurentItem();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QLabel *imageLabel;

    QAbstractItemModel *itemModel;
    QItemSelectionModel *itemSelectionModel;
    QModelIndex index;
    int scaleMode;
    int modelPathRole;
    double scaleFactor;
    Qt::WindowFlags winFlags;

    const static int SCALEMODE_FIT_TO_WINDOW    = 1;
    const static int SCALEMODE_SCALE            = 2;
};

#endif // VIEWERWIDGET_H
