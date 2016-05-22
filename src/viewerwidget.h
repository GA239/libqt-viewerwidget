#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include "viewerwidgetheaders.h"

class IEWERWIDGET_COMMON_DLLSPEC ViewerWidget : public QScrollArea
{
public:
    ViewerWidget();
    ~ViewerWidget();

private:
    QLabel *imageLabel;
};

#endif // VIEWERWIDGET_H
