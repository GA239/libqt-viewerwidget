#include "viewerwidget.h"

ViewerWidget::ViewerWidget()
{
    this->imageLabel = new QLabel(this);
    this->imageLabel->setBackgroundRole(QPalette::Base);
    this->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->imageLabel->setScaledContents(true);

    this->setBackgroundRole(QPalette::Dark);
    this->setWidget(this->imageLabel);
}

ViewerWidget::~ViewerWidget()
{
}

