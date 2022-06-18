#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);

signals:

};

#endif // MYLABEL_H
