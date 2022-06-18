#include "summondummy.h"


#include <QVector>
#include <cstring>
#include <ammo.h>
#include <QTimer>
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
#include <transformbuilder.h>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsEllipseItem>
#include <mainwindow.h>
#include <gamescene.h>
#include <physics.h>
#include <bomb.h>
#include <map.h>
#include <QDialog>
#include "health.h"

SummonDummy::SummonDummy() {}

void SummonDummy::onAttach() {
  transform = this->gameObject->getComponent<Transform>();
  Q_ASSERT(transform != nullptr);
  transform->setFiltersChildEvents(true);
}

void SummonDummy::onClick(QGraphicsSceneMouseEvent *ev) {
    //qDebug() << transform->type();
    if (transform->type() == 80)
    {
        //qDebug() << "stopppppp";
        if (end == 0)
        {
            this->gameObject->getParentGameScene()->getUpdateTimer()->stop(),end = 1;
            nowtime->stop();
    }
    else if (end == 1)
    {
        end = 0;
        this->gameObject->getParentGameScene()->getUpdateTimer()->start();
        nowtime->start();
        }
    }
    else if (transform->type() == 1)
    {
        QTimer::singleShot(50, this,[=]()mutable{
      //      this->hide();

            if (nowtime != nullptr)
              nowtime->stop();
            Mainone->disconnect(nowtime,0,0,0);
            auto game2 = new GameScene();
      //      auto gameScene2 = new GameScene();
            Mainone->gameScene = game2;
            Mainone->gameScene->setParent(Mainone);
            view->setScene(game2);
            view->setFrameStyle(QFrame::NoFrame);
            view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            page = 2;
            auto boardTransform = new Transform(QPointF(1270, 620));
            auto text = new QGraphicsSimpleTextItem(boardTransform);
            QFont f;
            f.setWeight(QFont::Black);
            f.setFamily(QStringLiteral("楷体"));
            f.setPointSize(14);
            text->setFont(f);
            text->setText("1000");
            text->setBrush(Qt::black);
            auto text1 = new GameObject();
            text1->addComponent(boardTransform);
            Mainone->timelist = text1;
            Mainone->gameScene->attachGameObject(Mainone->timelist);
            Mainone->loadScene(game2);

        });
    }
    else if (transform->type() == 3 ||transform->type() == 2  ||transform->type() == 4 ||transform->type() == 5)
    {
        //qDebug() <<"lookhowtoplay";
        QTimer::singleShot(50, this,[=]()mutable{
            auto game2 = new GameScene();
            Mainone->gameScene = game2;
            Mainone->gameScene->setParent(Mainone);
            view->setScene(game2);
            view->setFrameStyle(QFrame::NoFrame);
            view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            if (transform->type() == 2 || transform->type() == 5)
               page = 3, Mainone->loadScene2(game2);
            else if (transform->type() == 3)
               page = 1, Mainone->loadScene1(game2), s->show(), t->show(),b->show();
            else if (transform->type() == 4)
               page = 4, Mainone->loadScenetool(game2);

         });
    }
    else if (transform->type() == 70)
    {
        //qDebug() <<"instoop";
        if (m == 0)
            bk->stop(), m = 1;
        else
            bk->play(), m = 0;
    }
}
