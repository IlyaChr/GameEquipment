#include "item.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDebug>

//resource
const QString Item::PATH_TO_APPLE_IMG = ":/img/assets/img/apple.png";

//name of item
const QString Item::APPLE_NAME = "яблоко";


//id of item
const int Item::APPLE_ID = 1;


//Class for item widget
Item::Item(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( imageLabel = new QLabel(),1 );
    layout->addWidget( textLabel = new QLabel());
    setLayout( layout );

    imageLabel->setAlignment( Qt::AlignVCenter | Qt::AlignHCenter );
    textLabel->setAlignment( Qt::AlignHCenter );


    resize( 300, 300 );
}

/**
 * @brief Item::setPixmap
 * @param pix
 */
void Item::setPixmap(const QPixmap &pix)
{
    if (!pix.isNull()){
        imageLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        return;
    }

    imageLabel->setPixmap(pix);
}


/**
 * @brief Item::getPixmap
 * @return
 */
QPixmap Item::getPixmap() const
{
    return imageLabel->pixmap() ? *imageLabel->pixmap() : QPixmap();
}

/**
 * @brief Item::setText
 * @param text
 */
void Item::setText(const QString &text)
{
    textLabel->setText(text);
}

/**
 * @brief Item::getText
 * @return
 */
QString Item::getText() const
{
    return textLabel->text();
}

/**
 * @brief Item::mousePressEvent
 * @param event
 * save dragstart position
 */
void Item::mousePressEvent(QMouseEvent *event)
{
    dragStart = event->pos();
}

/**
 * @brief Item::mouseMoveEvent
 * @param event
 * implementation of drag event
 * saving transfer data here
 */
void Item::mouseMoveEvent(QMouseEvent *event)
{
    if ( ( event->buttons() & Qt::LeftButton) &&
         !getPixmap().isNull() &&
         QApplication::startDragDistance() <= ( event->pos()- dragStart).manhattanLength()){

        QDrag* drag = new QDrag( this);
        QMimeData* mimeData = new QMimeData;
        mimeData->setImageData( getPixmap().toImage());
        mimeData->setText( getText());

        drag->setMimeData(mimeData);
        drag->setPixmap(getPixmap());

        Qt::DropAction result = drag->exec(Qt::MoveAction);
        Q_UNUSED(result);
        //qDebug() << "Drop action result: " << result;

        //if ( result == Qt::MoveAction){
            //setPixmap( QPixmap());
            //setText("");
        //}

    }


}

QPoint Item::getDragStart() const
{
    return dragStart;
}
