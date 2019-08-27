#include "inventoryitem.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QSound>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QDebug>

const QString InventoryItem::DELIMITER = ":";
const QString InventoryItem::APPLE_SOUND_PATH = ":/sounds/assets/sounds/apple_sound.wav";

/**
 * @brief InventoryItem::InventoryItem
 * @param parent
 * @param width
 * @param hight
 * widgets item class for inventory cells
 */
InventoryItem::InventoryItem(QWidget *parent, int width, int hight):
    Item (parent)
{
    setAcceptDrops(true);

    resize( width, hight );
}

/**
 * @brief InventoryItem::dragEnterEvent
 * @param event
 * check for acceptProposedAction
 */
void InventoryItem::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList formats = event->mimeData()->formats();
    //qDebug() <<formats;

    if ( formats.contains("application/x-qt-image") &&
         formats.contains("text/plain")){

        event->acceptProposedAction();
    }

}

/**
 * @brief InventoryItem::dropEvent
 * @param event
 * when successful drop set image and text
 */
void InventoryItem::dropEvent(QDropEvent *event)
{
    setPixmap(QPixmap::fromImage(event->mimeData()->imageData().value<QImage>()));
    quantityItems++;
    setText(event->mimeData()->text() + DELIMITER + QString::number(quantityItems));
    event->acceptProposedAction();

}

/**
 * @brief InventoryItem::mouseMoveEvent
 * @param event
 * implementation of drag event
 * saving transfer data here
 */
void InventoryItem::mouseMoveEvent(QMouseEvent *event)
{
    if ( ( event->buttons() & Qt::LeftButton) &&
         !getPixmap().isNull() &&
         QApplication::startDragDistance() <= ( event->pos()- getDragStart()).manhattanLength()){

        QDrag* drag = new QDrag( this);
        QMimeData* mimeData = new QMimeData;
        mimeData->setImageData( getPixmap().toImage());
        mimeData->setText( getText().split(DELIMITER).value(0));

        drag->setMimeData(mimeData);
        drag->setPixmap(getPixmap());

        Qt::DropAction result = drag->exec(Qt::MoveAction);
        //qDebug() << "Drop action result: " << result;

        if ( result == Qt::MoveAction){
            quantityItems--;
            if (quantityItems > 0){
                setText(getText().split(DELIMITER).value(0)+DELIMITER+QString::number(quantityItems));
            }else {
                setPixmap( QPixmap());
                setText("");
            }
        }

    }
}

/**
 * @brief InventoryItem::mousePressEvent
 * @param event
 * for removing items from cells
 * and play apple bite sound
 */
void InventoryItem::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() & Qt::RightButton) &&
            !getPixmap().isNull()){

        QSound::play(APPLE_SOUND_PATH);

        quantityItems--;
        if (quantityItems > 0){
            setText(getText().split(DELIMITER).value(0)+DELIMITER+ QString::number(quantityItems));
        }else {
            setPixmap( QPixmap());
            setText("");
        }
    }
}

