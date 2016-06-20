#include <QDebug>
#include <QScrollBar>
#include <QKeyEvent>
#include <QLayout>
#include <QStringListModel>
#include "viewerwidget.h"

/**
 * @brief Default constructor
 * @param parent
 */
ViewerWidget::ViewerWidget(QWidget *parent) : QScrollArea(parent)
{
    this->imageLabel = new QLabel(this);
    this->imageLabel->setBackgroundRole(QPalette::Base);
    this->imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->imageLabel->setScaledContents(true);
    this->imageLabel->setAlignment(Qt::AlignCenter);
    this->imageLabel->setFocus();

    this->setFrameStyle(QFrame::Plain);
    this->setLineWidth(0);
    this->setBackgroundRole(QPalette::Window);
    this->setWidget(this->imageLabel);
    this->setAlignment(Qt::AlignCenter);

    this->itemModel = NULL;
    this->itemSelectionModel = NULL;
    this->scaleMode = this->SCALEMODE_FIT_TO_WINDOW;
    this->scaleFactor = 1.;
    this->modelPathRole = Qt::DisplayRole;
    this->show();
}

/**
 * @brief ViewerWidget::~ViewerWidget
 */
ViewerWidget::~ViewerWidget()
{
}

/**
 * @brief Returns can widget displaying file
 * @param filePath
 * @return
 */
bool ViewerWidget::isFileTypeSuported(QString filePath)
{
    QImage image(filePath);
    if (image.isNull()) {
        return false;
    }
    return true;
}

/**
 * @brief Sets model
 * @param model
 */
void ViewerWidget::setModel(QAbstractItemModel *model)
{
    if(this->itemModel != NULL)
        delete this->itemModel;
    this->itemModel = model;
    if(this->itemSelectionModel != NULL) {
        this->itemSelectionModel = NULL;
    }
    this->setIndex(this->itemModel->index(0, 0, QModelIndex()), this->modelPathRole);
    return;
}

/**
 * @brief Returns current model
 * @return model
 */
QAbstractItemModel *ViewerWidget::model()
{
    return this->itemModel;
}

/**
 * @brief Sets selection model
 * @param selectionModel
 */
void ViewerWidget::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->itemSelectionModel = selectionModel;
    return;
}

/**
 * @brief Returns shown item
 * @return
 */
QModelIndex ViewerWidget::currentItem()
{
    return this->index;
}

/**
 * @brief Sets item to display
 * @param index
 */
void ViewerWidget::setIndex(QModelIndex index, int pathRole)
{
    this->index = index;
    this->modelPathRole = pathRole;
    this->scaleMode = this->SCALEMODE_FIT_TO_WINDOW;
    this->show();

    QItemSelection selection = QItemSelection(this->index, this->index);
    if(this->itemSelectionModel) {
        this->itemSelectionModel->select(selection, QItemSelectionModel::ClearAndSelect);
    }
    return;
}

/**
 * @brief Shows index data
 */
void ViewerWidget::show()
{
    if(this->index.isValid()) {
        QString filePath = this->itemModel->data(this->index, this->modelPathRole).toString();
        QImage image(filePath);
        if (image.isNull()) {
            qDebug() << tr("Cannot load %1.").arg(filePath);
            this->showDefault();
            return;
        }
        this->imageLabel->setPixmap(QPixmap::fromImage(image));
        this->scaleFactor = 1.0;
        this->imageLabel->adjustSize();
        emit this->itemChanged(this->index);
    }
    else{
        this->showDefault();
    }
    return;
}
/**
 * @brief Shows default image
 */
void ViewerWidget::showDefault()
{
    QImage image("../resourses/No.png");
    this->imageLabel->setPixmap(QPixmap::fromImage(image));
    this->scaleFactor = 1.0;
    this->imageLabel->adjustSize();
    return;
}

/**
 * @brief Sets automatic adjustment size mode
 */
void ViewerWidget::autoFit()
{
    QSize scrollSize = this->size();
    QSize labelSize = this->imageLabel->size();
    double scaleWidth = (double)scrollSize.width() / (double)labelSize.width();
    double scaleHeight = (double)scrollSize.height() / (double)labelSize.height();
    if(scaleWidth > scaleHeight) {
        this->scaleImage(scaleHeight);
    } else {
        this->scaleImage(scaleWidth);
    }
    return;
}

/**
 * @brief Sets new scale
 * @param scaleX
 * @param scaleY
 */
void ViewerWidget::scaleImage(double factor)
{
        Q_ASSERT(imageLabel->pixmap());
        this->scaleFactor *= factor;
        imageLabel->resize(this->scaleFactor * imageLabel->pixmap()->size());

        this->adjustScrollBar(this->horizontalScrollBar(), factor);
        this->adjustScrollBar(this->verticalScrollBar(), factor);

        //zoomInAct->setEnabled(scaleFactor < 3.0);
        //zoomOutAct->setEnabled(scaleFactor > 0.333);
}

/**
 * @brief Sets scroll bar size and position
 * @param scrollBar
 * @param factor
 */
void ViewerWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
/**
 * @brief returnes validity of the model
 */
bool ViewerWidget::isModelAvailable()
{
    if(this->itemModel != NULL)
        return true;
    return false;
}

bool ViewerWidget::addItem(QString url)
{
    this->itemModel->insertRows(this->itemModel->rowCount(), 1, QModelIndex());
    QModelIndex idx = this->itemModel->index(this->itemModel->rowCount() - 1, 0, QModelIndex());
    if(this->itemModel->setData(idx, url)){
        this->setIndex(idx, this->modelPathRole);
        this->show();
        return true;
    }
    return false;
}

/**
 * @brief Shows preview document
 */
void ViewerWidget::showPrev()
{
    if(this->index.isValid()) {
        QModelIndex prevIndex;
        int row = this->index.row();
        //while(this->index.internalId() != prevIndex.internalId()) {
        while(1){
            if(row != 0) {
                row--;
            } else {
                row = this->itemModel->rowCount() - 1;
            }
            prevIndex = this->itemModel->index(row, 0, QModelIndex());
            if(prevIndex.isValid()) {
                QString path = prevIndex.data(this->modelPathRole).toString();
                if(this->isFileTypeSuported(path)) {
                    this->setIndex(prevIndex, this->modelPathRole);
                    break;
                }
            }
        }
    }
    return;
}

/**
 * @brief Shows next document
 */
void ViewerWidget::showNext()
{
    if(this->index.isValid()) {
        QModelIndex nextIndex;
        int row = this->index.row();
        int a = this->index.internalId();
        int b = nextIndex.internalId();
        //  while(this->index.internalId() != nextIndex.internalId()) {
        while(1) {
            if(row != this->itemModel->rowCount() - 1) {
                row++;
            } else {
                row = 0;
            }
            nextIndex = this->itemModel->index(row, 0, QModelIndex());
            if(nextIndex.isValid()) {
                QString path = nextIndex.data(this->modelPathRole).toString();
                if(this->isFileTypeSuported(path)) {
                    this->setIndex(nextIndex, this->modelPathRole);

                    break;
                }
            }
        }
    }
    return;
}

/**
 * @brief Shows document in full screen mode
 */
void ViewerWidget::showInFullScreen()
{
    this->winFlags = this->windowFlags();
    this->parentWidget()->layout()->removeWidget(this);
    this->setWindowFlags(Qt::Window);
    this->scaleMode = this->SCALEMODE_FIT_TO_WINDOW;
    this->showFullScreen();
    return;
}

/**
 * @brief Shows document in normal mode (in window)
 */
void ViewerWidget::showInWindow()
{
    this->setWindowFlags(this->winFlags);
    this->parentWidget()->layout()->addWidget(this);
    return;
}

/**
 * @brief Zoom in document content
 */
void ViewerWidget::zoomIn()
{
    this->scaleMode = this->SCALEMODE_SCALE;
    scaleImage(1.25);
}

/**
 * @brief Zoom out document content
 */
void ViewerWidget::zoomOut()
{
    this->scaleMode = this->SCALEMODE_SCALE;
    scaleImage(0.8);
}

/**
 * @brief Sets normal size
 */
void ViewerWidget::zoomToWindow()
{
    this->scaleMode = this->SCALEMODE_FIT_TO_WINDOW;
    this->autoFit();
    return;
}

/**
 * @brief Delete document
 */
void ViewerWidget::deleteCurentItem()
{
    this->itemModel->removeRow(this->index.row(), QModelIndex());
    if(this->itemModel->rowCount() != 0)
        this->showPrev();
    else
        this->setIndex(QModelIndex(),this->modelPathRole);
    return;
}

/**
 * @brief Action is called when resize widget event ocurs
 * @param event
 */
void ViewerWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(this->scaleMode == this->SCALEMODE_FIT_TO_WINDOW)
        this->autoFit();
}

/**
 * @brief Action is called when key press widget event ocurs
 * @param event
 */
void ViewerWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape: {
            this->showInWindow();
        } break;
        case Qt::Key_Space:
        case Qt::Key_PageUp: {
            this->showNext();
        } break;
        case Qt::Key_PageDown: {
            this->showPrev();
        } break;
        default: break;
    }
}

/**
 * @brief Action is called when mouse wheel widget event ocurs
 * @param event
 */
void ViewerWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0) {
        this->showNext();
    } else {
        this->showPrev();
    }
    return;
}

/**
 * @brief Action is called when mouse double click widget event ocurs
 * @param event
 */
void ViewerWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(this->isFullScreen()) {
        this->showInWindow();
    } else {
        this->showInFullScreen();
    }
    QScrollArea::mouseDoubleClickEvent(event);        // emit parent's handler
    return;
}

