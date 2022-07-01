#include "robot.h"
#include <QTime>
#include <QTimer>
#include <QQueue>
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
void Robot::changepush()
{
    pushable = 0;
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
void Robot::GetTool(int i, int j)
{
    bool yes = 0;
    if (m->MAPTool[i][j] == 1)
        m->Maplist[i * 20 + j]->getComponent<ImageTransform>()->setImage(" "), speed = speed + 1, speedflag = 1, score++, yes = 1;
    if (m->MAPTool[i][j] == 2)
        m->Maplist[i * 20 + j]->getComponent<ImageTransform>()->setImage(" "), bombnum++, bombnumflag = 1, score++, yes = 1;
    if (m->MAPTool[i][j] == 3)
        m->Maplist[i * 20 + j]->getComponent<ImageTransform>()->setImage(" "), bombpower++, bombpowerflag = 1, score++, yes = 1;
    if (m->MAPTool[i][j] == 4)
    {
        m->Maplist[i * 20 + j]->getComponent<ImageTransform>()->setImage(" "), pushable = 1, score++, yes = 1;
        updateTimer = new QTimer(this);
        updateTimer->setInterval(40000);
        connect(updateTimer, &QTimer::timeout, this, &Robot::changepush);
        updateTimer->start();
    }
    if (yes == 1)
    {
        auto musictool = new QSoundEffect;
        musictool->setSource(QUrl::fromLocalFile(":/res/tool.wav"));
        musictool->setVolume(0.15f);
        musictool->play();
    }
    target = 0;
    m->MAP[i][j] = 0;
    m->MAPTool[i][j] = 0;
    m->NOWTool[i][j] = 0;
}
void Robot::up()
{
    stage = (stage + 1) % 4;
    if (stage == 0)
        stage++;
    float half = (idx + 1) * 50 - 10;
    float uphalf = idy * 50 + 10;
    if ((y - 1 * speed) < 50)
        return;
    if ((y - 1 * speed) / 50 >= idy + 1 && x >= half && x <= half + 50)
    {
        transform->setPos(QPointF(x, y - 1 * speed)), y = y - 1 * speed, walk = 2;
        if (cnt % 8 == 0)
           transform->setImage(getImage(id, 1, stage));
    }
    else if ((y - 1 * speed) / 50 < idy + 1 && idy - 1 >= 0 && m->MAP[idy - 1][idx] == 0 && m->NOWBomb[idy - 1][idx] != 10 && x >= half && x <= half + 50)
    {
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 1, stage));
        transform->setPos(QPointF(x, y - 1 * speed)), y = y - 1 * speed, idy--, walk = 2;
        if (y - 1 * speed > uphalf)
            idy++;
        else
            this->movebomb(1);
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
        edge = 1;
        qDebug() << "edge!!!";

    }
}
void Robot::down()
{
    stage = (stage + 1) % 4;
    if (stage == 0)
        stage++;
    float half = (idx + 1) * 50 + 15;
    //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
    float downhalf = (idy + 2) * 50 - 25;
    if ((y + 1 * speed) / 50 <= idy + 1 && x <= half)
    {
        //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
        transform->setPos(QPointF(x, y + 1 * speed)), y = y + 1 * speed, walk = 1;
        if (cnt % 8 == 0)
        transform->setImage(getImage(id, 2, stage));
    }
    else if ((y + 1 * speed) / 50 > idy + 1  && idy + 1 < 15 && m->MAP[idy + 1][idx] == 0 && m->NOWBomb[idy + 1][idx] != 10 && x <= half)
    {
        //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 2, stage));
        transform->setPos(QPointF(x, y + 1 * speed)), y = y + 1 * speed, idy++, walk = 1;
        if (y + 1 * speed < downhalf)
            idy--;
        else
           this->movebomb(2);
    }
    else if ((y + 1 * speed) / 50 + 1 > idy + 1 && fmod(y + 1, 10) == 0 && x <= half)
    {
        //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 2, stage));
        transform->setPos(QPointF(x, y + 1 * speed)), y = y + 1 * speed, walk = 1;
        if (y + 1 * speed < downhalf)
            idy--;
        else
           this->movebomb(2);
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
        edge = 1;
        qDebug() << "edge!!!";
    }
}
void Robot::right()
{
    stage = (stage + 1) % 4;
    if (stage == 0)
        stage++;
    float half = (idy + 1) * 50 + 15;
    //qDebug() << "右" << transform->pos() << idy << idx << m->MAP[idy][idx + 1] << m->NOWBomb[idy][idx + 1];
    float righthalf = (idx + 2) * 50 - 25;
    if ((x + 1 * speed) / 50 < idx + 1 && y <= half)
    {
        transform->setPos(QPointF(x + 1 * speed, y)), x = x + 1 * speed, walk = 3;
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 4, stage));
    }
    else if ((x + 1 * speed) / 50 + 1 >= idx + 1 && idx + 1 < 20 && m->NOWBomb[idy][idx + 1] != 10 && m->MAP[idy][idx + 1] == 0 && y <= half)
    {
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 4 ,stage));
        transform->setPos(QPointF(x + 1, y)), x = x + 1 * speed, idx++, walk = 3;
        if (x + 1 * speed <= righthalf)
            idx--;
        else
            this->movebomb(4);
    }
    else if ((x + 1 * speed) / 50 + 1 >= idx + 1 && fmod(x + 1 * speed, 10) == 0 && y <= half)
    {
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 4, stage));
        transform->setPos(QPointF(x + 1, y)), x = x + 1 * speed, walk = 3;
        if (x + 1 * speed< righthalf)
            idx--;
        else
            this->movebomb(4);
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
        edge = 1;
        qDebug() << "edge!!!";
    }
}
void Robot::left()
{
    stage = (stage + 1) % 4;
    if (stage == 0)
        stage++;
    float half = idy * 50 + 35;
    float lefthalf = idx * 50 + 25;
    //qDebug() << "左" << transform->pos() << idy << idx;
    if ((x - 1 * speed) / 50 >= idx + 1 && y >= half)
    {
        transform->setPos(QPointF(x - 1 * speed, y)), x = x - 1 * speed, walk = 4;
        if (cnt % 8 == 0)
        transform->setImage(getImage(id, 3, stage));
    }
    else if ((x - 1 * speed) / 50 < idx + 1 && idx - 1 >= 0 && m->NOWBomb[idy][idx - 1] != 10 && m->MAP[idy][idx - 1] == 0 && y >= half)
    {
        if (cnt % 8 == 0)
            transform->setImage(getImage(id, 3, stage));
        transform->setPos(QPointF(x - 1 * speed, y)), x = x - 1 * speed, idx--, walk = 4;
        if (x - 1 * speed > lefthalf)
            idx++;
        else
           this->movebomb(3);

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
        edge = 1;
        qDebug() << "edge!!!";
    }
}

bool Robot::Find_Tool(int i, int j, int dir)
{
//    while (i != idy || j != idx)
//    {
//        if (dir == 3)
//        {
//            if (m->MAP[i - 1][j] == 0 && m->MAP[i][j - 1] != 0)
//            {
//                if (Find_Tool(i - 1, j, 3))
//                {
//                    tempDiraction.emplace_back(2);
//                    tempLocation.emplace_back(qMakePair(i - 1, j));
//                }
//            }
//            else if (m->MAP[i][j - 1] == 0 && m->MAP[i - 1][j] != 0)
//            {
//                if (Find_Tool(i, j - 1, 3))
//                {
//                    tempDiraction.emplace_back(4);
//                    tempLocation.emplace_back(qMakePair(i, j - 1));
//                }
//            }
//        }
//    }
//    return true;
    int length = abs(idx - j);
    int wide = abs(idy - i);
    struct node
    {
        int x;
        int y;
        int dir;
        int id;
        QPair<int, int> parent;
        node(int a,int b,int c, int d)
        {
            y = a;
            x = b;
            dir = c;
            id = d;
            //parent = qMakePair(y, x);
        }
    };
    QPair<int, int> path[400];
    int pathdir[400];
    int vy[5] = {1,0,-1,0};   //vx  vy用来计算一个节点周围上下左右4个节点
    int vx[5] = {0,1,0,-1};
    bool vis[20][20];     //判断某节点是否已经被访问过
        memset(vis, 0, sizeof(vis));
        memset(path, 0, sizeof(path));
        QQueue<node> q;
        node v = node(idy, idx, 0, idy * 20 + idx);
        v.parent = qMakePair(0, 0);
        //qDebug() << idy << idx;
        q.enqueue(v);
        vis[idy][idx] = 1;
        while(!q.empty())
        {
            auto u = q.front();
            q.dequeue();
            path[u.id]=u.parent;
            pathdir[u.id]  = u.dir;
            //qDebug() << path[u.id] << pathdir[u.id];
            bool in = 0;
            for(int i = 0; i < 4; i++)
            {
                int tx=u.x+vx[i];
                int ty=u.y+vy[i];
                //qDebug() << ty << tx;
                int dirac = 0;
                if (i == 0)
                    dirac = 2;
                else if (i == 1)
                    dirac = 4;
                else if (i == 2)
                    dirac = 1;
                else if (i == 3)
                    dirac = 3;
                if (tx < 0 || ty < 0 || tx >= 20 || ty >= 15)
                    continue;
                if(m->MAP[ty][tx] == 0 && !vis[ty][tx])
                {
                    qDebug() << "next" << ty << tx;
                    in = 1;
                    vis[ty][tx] = 1;
                    node v = node(ty, tx, dirac, ty * 20 + tx);
                    v.parent = qMakePair(u.y, u.x);
                    q.enqueue(v);
                }
            }

        }
        QVector<int> ans;
        QPair<int, int>  p = qMakePair(i, j);

        while(p != qMakePair(0, 0))
        {
            //qDebug() << "rout" << p;
            tempLocation.push_front(p);
            tempDiraction.push_front(pathdir[p.first * 20 + p.second]);
            p = path[p.first * 20 + p.second];
        }
        return true;


}
void Robot::put_bomb()
{
    bombflag = 1;
    m->MAP[idy][idx] = 10;
    bombnum--;
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
        b->getComponent<Bomb>()->changepower(bombpower);
}
void Robot::movebomb(int dir)
{
    if (m->MAP[idy][idx] == 10 && pushable == 1)
    {
        for (auto item : m->Bomblist)
        {
            if (item->getComponent<Bomb>()->get_x() == idy && item->getComponent<Bomb>()->get_y() == idx && item->getComponent<Bomb>()->hit == 0)
            {
                //qDebug() << "inbomb" << idy << idx;
                auto musictool = new QSoundEffect;
                musictool->setSource(QUrl::fromLocalFile(":/res/movebomb.wav"));
                musictool->setVolume(0.15f);
                musictool->play();
                item->getComponent<Bomb>()->hit = dir;
                break;
            }
        }
    }
    else
        GetTool(idy, idx);
}
void Robot::onUpdate(float deltaTime) {
    QVector<GameObject *>::Iterator it;
    QVector<GameObject *> temp;

    for (int i = 0; i < mainboard.size();)
    {
        auto tr = mainboard[i]->getComponent<Transform>();
        if ((speedflag == 1 && tr->type() == 11 )||( bombpowerflag == 1 && tr->type() == 12 )|| (bombnumflag == 1 && tr->type() == 13 )|| (scoreflag == 1 && tr->type() == 15) || (liveflag == 1 && tr->type() == 14 ))
        {
            //qDebug() << mainboard.size() << "!!!" <<bombnumflag << bombnum << tr->type() <<tr->pos();
            auto boardTransform = new Transform(tr->pos());
            boardTransform->setType(tr->type());
            auto text = new QGraphicsSimpleTextItem(boardTransform);
            this->detachGameObject(mainboard[i]);
            mainboard.erase(mainboard.begin() + i);
            auto obj = new GameObject();
            obj->addComponent(boardTransform);
            if (speedflag == true && tr->type() == 11)
                text->setText(QString::number(speed)),speedflag = 0;
            else if (bombpowerflag == true && tr->type() == 12)
                text->setText(QString::number(bombpower)), bombpowerflag = 0;
            else if (bombnumflag == true && tr->type() == 13)
                text->setText(QString::number(bombnum)), bombnumflag = 0;
            else if (tr->type() == 14 && live < 0)
                text->setText("0");
            else if (scoreflag == true && tr->type() == 15)
                text->setText(QString::number(score)), scoreflag = 0;
            if (liveflag == true && tr->type() == 14)
                text->setText("0"), liveflag = 0;
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
                for (int i = (-1) * bombpower; i <= bombpower; i++)
                {

                    if (b->getComponent<Bomb>()->get_y() + i < 0 || b->getComponent<Bomb>()->get_y() + i >= 20|| b->getComponent<Bomb>()->get_x() + i < 0 || b->getComponent<Bomb>()->get_x() + i >= 15)
                          continue;
                    m->NOWBomb[b->getComponent<Bomb>()->get_x() + i][b->getComponent<Bomb>()->get_y()] = 0;
                    m->NOWBomb[b->getComponent<Bomb>()->get_x()][b->getComponent<Bomb>()->get_y() + i] = 0;
                }
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
                bombnum++;
                bombnumflag = 1;
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
        qDebug() << "live" << live;
        live = live - 1;
        liveflag = 1;
        if (live < -180)
        {
            liveflag = 1, live = 3;
            dir = 0;
            stage = 3, predir = 0;
            walk = 0, walkdir = 0;
            flag = 0, scoreflag = 0;
            stopflag = 0;
            Diraction.clear();
            Location.clear();
            target = 0;
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
        if (returntime == 60 * speed)
            returntime = 0, returnflag = 0, stopflag = 0;
        else
            return;
    }
    float half = 0;
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
    if (!Diraction.empty())
    {
        qDebug() << "follow";
        int temp = Diraction[0];
        if (temp == 1 && (Location[0].first + 1) * 50 < y)
            up();
        else if (temp == 1 && (Location[0].first + 1) * 50 >= y)
        {
            up();
            Location.removeFirst();
            Diraction.removeFirst();
            if (Diraction.empty() == 1 && bombflag == 1)
                returnflag = 1, bombflag = 0;
        }
        else if (temp == 2 && (Location[0].first + 1) * 50 > y)
            down();
        else if (temp == 2 && (Location[0].first + 1) * 50 <= y)
        {
            down();
            Location.removeFirst();
            Diraction.removeFirst();
            if (Diraction.empty() == 1 && bombflag == 1)
                returnflag = 1, bombflag = 0;
        }
        else if (temp == 3 && (Location[0].second + 1) * 50 < x)
            left();
        else if (temp == 3 && (Location[0].second + 1) * 50 >= x)
        {
            left();
            Location.removeFirst();
            Diraction.removeFirst();
            if (Diraction.empty() == 1 && bombflag == 1)
                returnflag = 1, bombflag = 0;
        }
        else if (temp == 4 && (Location[0].second + 1) * 50 > x)
            right();
        else if (temp == 4 && (Location[0].second + 1) * 50 <= x)
        {
            right();
            Location.removeFirst();
            Diraction.removeFirst();
            if (Diraction.empty() == 1 && bombflag == 1)
                returnflag = 1, bombflag = 0;
        }
        return;
    }
    if (target == 0)
    {
    for (int i = -4; i <= 4; i++)
    {
        for (int j = -4; j <= 4; j++)
        {
            if (i + idy >= 15 || i + idy < 0 || j + idx >= 20 || j + idx < 0)
                continue;
            if (m->NOWTool[i + idy][j + idx] != 0)
            {
                qDebug() << "find" << i << j << i + idy << j + idx;
                if (Find_Tool(i + idy, j + idx, 0))
                {
                    target = 1;
                    qDebug() << "find yes"<< i << j;
                    for (auto it : tempDiraction)
                        Diraction.emplace_back(it);

                    for (auto it : tempLocation)
                        Location.emplace_back(it);

                    tempDiraction.clear();
                    tempLocation.clear();
                    Diraction.pop_front();
                    Location.pop_front();
                    qDebug() << "len" << Diraction.length();
                    return;
                }
            }
        }
    }
    }
    if (dir == 1)
    {
        up();
        if (edge == 1 && bombnum >= 1)
        {
            if (m->MAP[idy - 1][idx] != 0 && m->MAP[idy][idx - 1] != 0 && m->MAP[idy][idx + 1] != 0)
            {
                if (bombpower == 1)
                {
                    qDebug() << "shang put";
                    put_bomb();
                }
            }
        }
        edge = 0;
    }
    else if (dir == 2)
    {
        down();
        if (edge == 1 && bombnum >= 1)
        {
            if (m->MAP[idy + 1][idx] != 0 && m->MAP[idy][idx - 1] != 0 && m->MAP[idy][idx + 1] != 0)
            {
                if (bombpower == 1)
                {
                    qDebug() << "xia put";
                    put_bomb();
                }
            }
        }
        edge = 0;
    }
    else if (dir == 3)
    {
        left();
        if (edge == 1 && bombnum >= 1)
        {
            if (m->MAP[idy][idx - 1] != 0 && m->MAP[idy + 1][idx] != 0 && m->MAP[idy - 1][idx] != 0)
            {
                if (bombpower == 1)
                {
                    qDebug() << "zuo put";
                    put_bomb();

                }
            }
        }
        edge = 0;
    }
    else if (dir == 4)
    {
        right();
        if (edge == 1 && bombnum >= 1)
        {
            if (m->MAP[idy][idx + 1] != 0 && m->MAP[idy + 1][idx] != 0 && m->MAP[idy - 1][idx] != 0)
            {
                if (bombpower == 1)
                {
                    qDebug() << "you put";
                    put_bomb();
                }
            }
        }
        edge = 0;
    }

    if (bombtime >= 0 || bombnum <= 0)
        return;
    bombtime = 13.2;
    qDebug() << dir <<  " !!!!!!!!!" << idy << idx - 1;
    if ((dir == 1 && idy - 1 >= 0) && m->MAP[idy - 1][idx] == 0 && ((m->NOWBomb[idy - 1][idx + 1] == 0 && m->MAP[idy - 1][idx + 1] == 0) || (m->NOWBomb[idy - 1][idx - 1] == 0 && m->MAP[idy - 1][idx - 1] == 0)))
    {
        if (idx + 1 < 20 && m->MAP[idy - 1][idx + 1] == 0)
        {
            Diraction.emplace_back(1);
            Location.emplace_back(qMakePair(idy - 1,idx));
            Diraction.emplace_back(4);
            Location.emplace_back(qMakePair(idy - 1,idx + 1));
        }
        else if (idx - 1 >= 0 && m->MAP[idy - 1][idx - 1] == 0)
        {
            Diraction.emplace_back(1);
            Location.emplace_back(qMakePair(idy - 1,idx));
            Diraction.emplace_back(3);
            Location.emplace_back(qMakePair(idy - 1,idx - 1));
        }
        predir = 2, walk = 0;
        dir = 1;
    }
    else if ((dir == 2 && idy + 1 < 15) && m->MAP[idy + 1][idx] == 0 && (m->MAP[idy + 1][idx + 1] == 0 || m->MAP[idy + 1][idx - 1] == 0))
    {
        qDebug() << "xia!!!!!!" << idy << idx;
        if (idx + 1 < 20 && m->MAP[idy + 1][idx + 1] == 0)
        {
            Diraction.emplace_back(2);
            Location.emplace_back(qMakePair(idy + 1,idx));
            Diraction.emplace_back(4);
            Location.emplace_back(qMakePair(idy + 1,idx + 1));
        }
        else if (idx - 1 >= 0 && m->MAP[idy + 1][idx - 1] == 0)
        {
            Diraction.emplace_back(2);
            Location.emplace_back(qMakePair(idy + 1,idx));
            Diraction.emplace_back(3);
            Location.emplace_back(qMakePair(idy + 1,idx - 1));
        }
        predir = 1, walk = 0;
        dir = 2;
    }
    else if ((dir == 3 && idx - 1 >= 0) && m->MAP[idy][idx - 1] == 0 && (m->MAP[idy + 1][idx - 1] == 0 || m->MAP[idy - 1][idx - 1] == 0))
    {
        if (idy + 1 < 15 && m->MAP[idy + 1][idx - 1] == 0)
        {
            //qDebug() << "!!!!!!!!!" << idy << idx - 1;
            Diraction.emplace_back(3);
            Location.emplace_back(qMakePair(idy,idx - 1));
            Diraction.emplace_back(2);
            Location.emplace_back(qMakePair(idy + 1,idx - 1));
        }
        else if (idy - 1 >= 0 && m->MAP[idy - 1][idx - 1] == 0)
        {
            //qDebug() << "!!!!!!!!!" << idy << idx - 1;
            Diraction.emplace_back(3);
            Location.emplace_back(qMakePair(idy,idx - 1));
            Diraction.emplace_back(1);
            Location.emplace_back(qMakePair(idy - 1,idx - 1));
        }
        predir = 4, walk = 0;
        dir = 3;
    }
    else if ((dir == 4 && idx + 1 < 20) && m->MAP[idy][idx + 1] == 0 && (m->MAP[idy + 1][idx + 1] == 0 || m->MAP[idy - 1][idx + 1] == 0))
    {
        if (idy + 1 < 15 && m->MAP[idy + 1][idx + 1] == 0)
        {
            qDebug() << "!!!!!!!!!" << idy << idx + 1;
            Diraction.emplace_back(4);
            Location.emplace_back(qMakePair(idy,idx + 1));
            Diraction.emplace_back(2);
            Location.emplace_back(qMakePair(idy + 1,idx + 1));
        }
        else if (idy - 1 >= 0 && m->MAP[idy - 1][idx + 1] == 0)
        {
            Diraction.emplace_back(4);
            Location.emplace_back(qMakePair(idy,idx + 1));
            Diraction.emplace_back(1);
            Location.emplace_back(qMakePair(idy - 1,idx + 1));
        }
        predir = 3, walk = 0;
        dir = 4;
    }
    else
        return;
    walkdir = 0;
    stopflag = 1;
    put_bomb();
}
