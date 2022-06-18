#include "mylabel.h"

#include <QDebug>
myLabel::myLabel(QWidget *parent)
    : QLabel{parent}
{

}
void myLabel::enterEvent(QEnterEvent *event)
{
    qDebug() <<"enterrr";
}
void myLabel::leaveEvent(QEvent *event)
{
    qDebug() <<"leaveee";
}
