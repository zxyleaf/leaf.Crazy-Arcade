#include "robot.h"
#include <QTime>
#include <QRandomGenerator>
#include <QtGlobal>
#include <QVector>
#include <cstring>
#include <ammo.h>
#include <map.h>
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
#include <transformbuilder.h>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <gamescene.h>
#include <mainwindow.h>
#include <physics.h>
#include <bomb.h>
#include "health.h"
Robot::Robot(map *ma, float ix, float iy, int xi, int yi, int idd)
{
    m = ma;
    x = ix;
    y = iy;
    idx = xi;
    idy = yi;
    id = idd;
}
void Robot::onAttach() {
  this->transform = this->gameObject->getComponent<ImageTransform>();
  Q_ASSERT(this->transform != nullptr);
}
const char* Robot::getImage(int id, int dir, int stage)
{
    if (id == 1 && dir == 1 && stage == 0)
        return ":/res/robotW.png";
    else if (id == 1 && dir == 1 && stage == 1)
        return ":/res/robotW1.png";
    else if (id == 1 && dir == 1 && stage == 2)
        return ":/res/robotW2.png";
    else if (id == 1 && dir == 1 && stage == 3)
        return ":/res/robotW3.png";
    else if (id == 1 && dir == 1 && stage == 4)
        return ":/res/robotW4.png";
    else if (id == 1 && dir == 2 && stage == 0)
            return ":/res/robotS.png";
    else if (id == 1 && dir == 2 && stage == 1)
        return ":/res/robotS1.png";
    else if (id == 1 && dir == 2 && stage == 2)
        return ":/res/robotS2.png";
    else if (id == 1 && dir == 2 && stage == 3)
        return ":/res/robotS3.png";
    else if (id == 1 && dir == 2 && stage == 4)
        return ":/res/robotS4.png";
    else if (id == 1 && dir == 3 && stage == 0)
        return ":/res/robotA.png";
    else if (id == 1 && dir == 3 && stage == 1)
        return ":/res/robotA1.png";
    else if (id == 1 && dir == 3 && stage == 2)
        return ":/res/robotA2.png";
    else if (id == 1 && dir == 3 && stage == 3)
        return ":/res/robotA3.png";
    else if (id == 1 && dir == 3 && stage == 4)
        return ":/res/robotA4.png";
    else if (id == 1 && dir == 4 && stage == 0)
        return ":/res/robotD.png";
    else if (id == 1 && dir == 4 && stage == 1)
        return ":/res/robotD1.png";
    else if (id == 1 && dir == 4 && stage == 2)
        return ":/res/robotD2.png";
    else if (id == 1 && dir == 4 && stage == 3)
        return ":/res/robotD3.png";
    else if (id == 1 && dir == 4 && stage == 4)
        return ":/res/robotD4.png";
    else if (id == 2 && dir == 1 && stage == 0)
        return ":/res/robot1w.png";
    else if (id == 2 && dir == 1 && stage == 1)
        return ":/res/robot1w1.png";
    else if (id == 2 && dir == 1 && stage == 2)
        return ":/res/robot1w2.png";
    else if (id == 2 && dir == 1 && stage == 3)
        return ":/res/robot1w3.png";
    else if (id == 2 && dir == 1 && stage == 4)
        return ":/res/robot1w4.png";
    else if (id == 2 && dir == 2 && stage == 0)
            return ":/res/robot1s.png";
    else if (id == 2 && dir == 2 && stage == 1)
        return ":/res/robot1s1.png";
    else if (id == 2 && dir == 2 && stage == 2)
        return ":/res/robot1s2.png";
    else if (id == 2 && dir == 2 && stage == 3)
        return ":/res/robot1s3.png";
    else if (id == 2 && dir == 2 && stage == 4)
        return ":/res/robot1s4.png";
    else if (id == 2 && dir == 3 && stage == 0)
        return ":/res/robot1a.png";
    else if (id == 2 && dir == 3 && stage == 1)
        return ":/res/robot1a1.png";
    else if (id == 2 && dir == 3 && stage == 2)
        return ":/res/robot1a2.png";
    else if (id == 2 && dir == 3 && stage == 3)
        return ":/res/robot1a3.png";
    else if (id == 2 && dir == 3 && stage == 4)
        return ":/res/robot1a4.png";
    else if (id == 2 && dir == 4 && stage == 0)
        return ":/res/robot1d.png";
    else if (id == 2 && dir == 4 && stage == 1)
        return ":/res/robot1d1.png";
    else if (id == 2 && dir == 4 && stage == 2)
        return ":/res/robot1d2.png";
    else if (id == 2 && dir == 4 && stage == 3)
        return ":/res/robot1d3.png";
    else if (id == 2 && dir == 4 && stage == 4)
        return ":/res/robot1d4.png";
    return " ";
}
int Robot::get_id()
{
    return id;
}
int Robot::get_idx()
{
    return idx;
}
int Robot::get_idy()
{
    return idy;
}
void Robot::onUpdate(float deltaTime) {
    QVector<GameObject *>::Iterator it;
    QVector<GameObject *> temp;

    for (int i = 0; i < mainboard.size();)
    {
        auto tr = mainboard[i]->getComponent<Transform>();
        if ((liveflag == 1 && tr->type() == 14 )|| (scoreflag == 1 && tr->type() == 15))
        {
            //qDebug() << mainboard.size() << "!!!" <<bombnumflag << bombnum << tr->type() <<tr->pos();
            auto boardTransform = new Transform(tr->pos());
            boardTransform->setType(tr->type());
            auto text = new QGraphicsSimpleTextItem(boardTransform);
            this->detachGameObject(mainboard[i]);
            mainboard.erase(mainboard.begin() + i);
            auto obj = new GameObject();
            obj->addComponent(boardTransform);
            if (liveflag == true && tr->type() == 14)
                text->setText("0"), liveflag = 0;
            else if (scoreflag == true && tr->type() == 15)
                text->setText(QString::number(score)), scoreflag = 0;
            text->setBrush(Qt::black);
            QFont f;
            f.setWeight(QFont::Black);
            f.setFamily(QStringLiteral("黑体"));
            f.setPointSize(14);
            text->setFont(f);
            temp.emplace_back(obj);
            this->attachGameObject(obj);
        }
        else
            i++;
    }

    for (it = temp.begin(); it != temp.end();it++)
        mainboard.emplace_back(*it);

    if (!BombList.empty())
    {
        for (auto b : BombList)
        {
            if (b->getComponent<Bomb>()->interval < -1)
            {
                if (b->getComponent<Bomb>()->curscore != 0)
                    score += b->getComponent<Bomb>()->curscore, scoreflag = 1;

                m->MAP[b->getComponent<Bomb>()->get_x()][b->getComponent<Bomb>()->get_y()] = 0;
                score += b->getComponent<Bomb>()->curscore;
                scoreflag = 1;
                int st = 0;
                for (auto it : m->Bomblist)
                {
                    if (it->getComponent<Bomb>()->get_x() == b->getComponent<Bomb>()->get_x() && it->getComponent<Bomb>()->get_y() == b->getComponent<Bomb>()->get_y())
                    {
                        m->Bomblist.remove(st);
                        break;
                    }
                    st++;
                }
                BombList.remove(0);
                b->removeComponent(b->getComponent<Bomb>());
                this->detachGameObject(b);
            }
        }
    }
    cnt++;
    cooltime -= deltaTime * 5;
    bombtime -= deltaTime;
    if (cooltime >= 0)
        return;
    if (live < 1)
    {
        //qDebug() << "live" << live;
        live = live - 1;
        liveflag = 1;
        if (live < -180)
        {
            liveflag = 0, live = 3;
            dir = 0;
            stage = 3, predir = 0;
            walk = 0, walkdir = 0;
            flag = 0, scoreflag = 0;
            stopflag = 0;
            returnflag = 0, returntime = 0;
            if (id == 1)
            {
                x = y = 250;
                idx = idy = 4;
                transform->setPos(QPointF(250, 250));
                transform->setImage(getImage(id, 2, 0));
            }
            else if (id == 2)
            {
                x = 800;
                y = 550;
                idx = 15;
                idy = 10;
                transform->setPos(QPointF(800, 550));
                transform->setImage(getImage(id, 2, 0));
            }
        }
        else
            return;
    }
    if (live < 3)
        return;
    cooltime = 0.16;
    if(returnflag == 1)
    {
        returntime++;
        if (returntime == 60)
            returntime = 0, returnflag = 0, stopflag = 0;
        else
            return;
    }


    int n = QRandomGenerator::global()->generate() % 4 + 1;
    while (n == walk)
        n = rand() % 4 + 1;
    if (dir == 0 || (dir == 1 && y - 1 < 50) || (dir == 2 && y + 1 > 750) || (dir == 3 && x - 1 < 50) || (dir == 4 && x + 1 > 1000))
    {
        dir = n;
        if (dir == predir)
        {
            while (n == predir)
              n = rand() % 4 + 1;
            dir = n;
        }
    }
    float half = 0;
    if (dir == 1)
    {
        stage = (stage + 1) % 4;
        if (stage == 0)
            stage++;
        half = (idx + 1) * 50 - 10;
        //qDebug() << "上" << transform->pos() << idy << idx;
        float uphalf = idy * 50 + 10;
        if ((y - 1) / 50 >= idy + 1 && x >= half && x <= half + 50)
        {
            //qDebug() << "上" << transform->pos() << idy << idx;
            transform->setPos(QPointF(x, y - 1)), y = y - 1, walk = 2;
            if (cnt % 8 == 0)
               transform->setImage(getImage(id, 1, stage));
        }
        else if ((y - 1) / 50 < idy + 1 && idy - 1 >= 0 && m->MAP[idy - 1][idx] == 0 && x >= half && x <= half + 50)
        {
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 1, stage));
            transform->setPos(QPointF(x, y - 1)), y = y - 1, idy--, walk = 2;
            if (y - 1 > uphalf)
                idy++;
        }
        else
        {
            if ((predir == 3 || predir == 4) && stopflag == 1){
               returnflag = 1;
            }
            transform->setImage(getImage(id, 1, 0)), stage = 0, dir = 0;
            if (m->MAP[idy][idx - 1] != 0 && m->MAP[idy][idx + 1] != 0)
                dir = 2;
            else if (m->MAP[idy][idx - 1] != 0)
                dir = 4;
            else if (m->MAP[idy][idx + 1] != 0)
                dir = 3;
        }
    }
    else if (dir == 2)
    {
        stage = (stage + 1) % 4;
        if (stage == 0)
            stage++;
        half = (idx + 1) * 50 + 15;
        //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
        float downhalf = (idy + 2) * 50 - 25;
        if ((y + 1) / 50 <= idy + 1 && x <= half)
        {
            //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
            transform->setPos(QPointF(x, y + 1)), y = y + 1, walk = 1;
            if (cnt % 8 == 0)
            transform->setImage(getImage(id, 2, stage));
        }
        else if ((y + 1) / 50 > idy + 1  && idy + 1 < 15 && m->MAP[idy + 1][idx] == 0 && x <= half)
        {
            //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 2, stage));
            transform->setPos(QPointF(x, y + 1)), y = y + 1, idy++, walk = 1;
            if (y + 1< downhalf)
                idy--;
        }
        else if ((y + 1) / 50 + 1 > idy + 1 && fmod(y + 1, 10) == 0 && x <= half)
        {
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 2, stage));
            transform->setPos(QPointF(x, y + 1)), y++, walk = 1;
            if (y + 1< downhalf)
                idy--;
        }
        else
        {
            if ((predir == 3 || predir == 4) && stopflag == 1){
               returnflag = 1;
            }
            transform->setImage(getImage(id, 1, stage)), stage = 0, dir = 0;
            if (m->MAP[idy][idx - 1] != 0 && m->MAP[idy][idx + 1] != 0)
                dir = 1;
            else if (m->MAP[idy][idx - 1] != 0)
                dir = 4;
            else if (m->MAP[idy][idx + 1] != 0)
                dir = 3;
        }
    }
    else if (dir == 3 )
    {
        stage = (stage + 1) % 4;
        if (stage == 0)
            stage++;
        half = idy * 50 + 35;
        float lefthalf = idx * 50 + 25;
        //qDebug() << "左" << transform->pos() << idy << idx;
        if ((x - 1) / 50 >= idx + 1 && y >= half)
        {
            transform->setPos(QPointF(x - 1, y)), x = x - 1, walk = 4;
            if (cnt % 8 == 0)
            transform->setImage(getImage(id, 3, stage));
        }
        else if ((x - 1) / 50 < idx + 1 && idx - 1 >= 0 && m->MAP[idy][idx - 1] == 0 && y >= half)
        {
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 3, stage));
            transform->setPos(QPointF(x - 1, y)), x = x - 1, idx--, walk = 4;
            if (x - 1 > lefthalf)
                idx++;
        }
        else
        {
            if ((predir == 1 || predir == 2) && stopflag == 1){
               returnflag = 1;
            }
            transform->setImage(getImage(id, 3, stage)), stage = 0, dir = 0;
            if (m->MAP[idy - 1][idx] != 0 && m->MAP[idy + 1][idx] != 0)
                dir = 4;
            else if (m->MAP[idy - 1][idx] != 0)
                dir = 2;
            else if (m->MAP[idy + 1][idx] != 0)
                dir = 1;
        }

    }
    else if (dir == 4 )
    {
        stage = (stage + 1) % 4;
        if (stage == 0)
            stage++;
        half = (idy + 1) * 50 + 15;
        //qDebug() << "右" << transform->pos() << idy << idx << m->MAP[idy][idx + 1];
        float righthalf = (idx + 2) * 50 - 25;
        if ((x + 1) / 50 < idx + 1 && y <= half)
        {
            transform->setPos(QPointF(x + 1, y)), x = x + 1, walk = 3;
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 4, stage));
        }
        else if ((x + 1) / 50 + 1 >= idx + 1 && idx + 1 < 20 && m->MAP[idy][idx + 1] == 0 && y <= half)
        {
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 4 ,stage));
            transform->setPos(QPointF(x + 1, y)), x = x + 1, idx++, walk = 3;
            if (x + 1 <= righthalf)
                idx--;
        }
        else if ((x + 1) / 50 + 1 >= idx + 1 && fmod(x + 1, 10) == 0 && y <= half)
        {
            if (cnt % 8 == 0)
                transform->setImage(getImage(id, 4, stage));
            transform->setPos(QPointF(x + 1, y)), x = x + 1, walk = 3;
            if (x + 1< righthalf)
                idx--;
        }
        else
        {
            if ((predir == 1 || predir == 2) && stopflag == 1){
               returnflag = 1;
            }
            transform->setImage(getImage(id, 4, stage)), stage = 0, dir = 0;
            if (m->MAP[idy - 1][idx] != 0 && m->MAP[idy + 1][idx] != 0)
                dir = 3;
            else if (m->MAP[idy - 1][idx] != 0)
                dir = 2;
            else if (m->MAP[idy + 1][idx] != 0)
                dir = 1;
        }
    }
    if (bombtime >= 0)
        return;
    bombtime = 13.2;
    if ((dir == 1 && idy - 1 >= 0) && m->MAP[idy - 1][idx] == 0 && (m->MAP[idy - 1][idx + 1] == 0 || m->MAP[idy - 1][idx - 1] == 0 || (idy - 2 >= 0 && m->MAP[idy - 2][idx] == 0)))
    {
        predir = 2, walk = 0;
        dir = 1;
    }
    else if ((dir == 2 && idy + 1 < 15) && m->MAP[idy + 1][idx] == 0 && (m->MAP[idy + 1][idx + 1] == 0 || m->MAP[idy + 1][idx - 1] == 0 || (idy + 2 < 15 && m->MAP[idy + 2][idx] == 0)))
    {
        predir = 1, walk = 0;
        dir = 2;
    }
    else if ((dir == 3 && idx - 1 >= 0) && m->MAP[idy][idx - 1] == 0 && (m->MAP[idy + 1][idx - 1] == 0 || m->MAP[idy - 1][idx - 1] == 0|| (idx - 2 >= 0 && m->MAP[idy][idx - 2] == 0)))
    {
        predir = 4, walk = 0;
        dir = 3;
    }
    else if ((dir == 4 && idx + 1 < 20) && m->MAP[idy][idx + 1] == 0 && (m->MAP[idy + 1][idx + 1] == 0 || m->MAP[idy - 1][idx + 1] == 0 || (idx + 2 <20 && m->MAP[idy][idx + 2] == 0)))
    {
        predir = 3, walk = 0;
        dir = 4;
    }
    else
        return;
    walkdir = 0;
    stopflag = 1;
    m->MAP[idy][idx] = 10;
    float curx = (idx + 1) * 50;
    float cury = (idy + 1) * 50;
    auto bomb = new GameObject();
    bomb->addComponent(ImageTransformBuilder()
                           .setPos(QPointF(curx, cury))
                           .setImage(":/res/custom_bubble3.png")
                           .setAlignment(Qt::AlignHCenter)
                           .setAlignment(Qt::AlignVCenter)
                           .build());
    bomb->addComponent(new Bomb(m, curx, cury, idx, idy, 3, 1));
    BombList.emplace_back(bomb);
    m->Bomblist.emplace_back(bomb);
    this->attachGameObject(bomb);
    for (auto b : BombList)
        b->getComponent<Bomb>()->changepower(1);

}
