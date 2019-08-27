#ifndef SUBJECT_H
#define SUBJECT_H

#include <QWidget>

class QLabel;

class Item : public QWidget
{
    Q_OBJECT
public:
    explicit Item(QWidget *parent = nullptr);

    void setPixmap( const QPixmap& pix);
    QPixmap getPixmap() const;

    void setText( const QString& text);
    QString getText() const;

    QPoint getDragStart() const;


    const static QString PATH_TO_APPLE_IMG;
    const static QString APPLE_NAME;

protected:
    void mousePressEvent( QMouseEvent* event) override;
    void mouseMoveEvent( QMouseEvent* event) override;

private:
    QLabel* imageLabel = nullptr;
    QLabel* textLabel = nullptr;
    QPoint dragStart;
};

#endif // SUBJECT_H
