#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <component.h>
#include <QPushButton>
#include <QEnterEvent>
#include <QLabel>
#include <QWidget>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg, QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;
    void zoom1();
    void zoom2();


signals:

};

#endif // MYPUSHBUTTON_H
