#include "mypushbutton.h"

#include <gameobject.h>
#include <transform.h>

#include <QPropertyAnimation>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
     this->normalImgPath = normalImg;
     this->pressImgPath = pressImg;
    QPixmap pix;
    pix.load(normalImg);
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

}

void MyPushButton::zoom1()
{
    QPropertyAnimation * al = new QPropertyAnimation(this, "geometry");
    al->setDuration(200);
    al->setStartValue(QRect(this->x(),this->y(), this->width(), this->height()));
    al->setEndValue(QRect(this->x(),this->y() + 10, this->width(), this->height()));
    al->setEasingCurve(QEasingCurve::OutBounce);
    al->start();
}
void MyPushButton::zoom2()
{
    QPropertyAnimation * al = new QPropertyAnimation(this, "geometry");
    al->setDuration(200);
    al->setStartValue(QRect(this->x(),this->y() + 10, this->width(), this->height()));
    al->setEndValue(QRect(this->x(),this->y(), this->width(), this->height()));
    al->setEasingCurve(QEasingCurve::OutBounce);
    al->start();
}
