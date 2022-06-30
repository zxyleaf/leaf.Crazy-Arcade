#include "player.h"

#include <QVector>
#include <QTimer>
#include <cstring>
#include <ammo.h>
#include <map.h>
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
#include <transformbuilder.h>
#include <QSoundEffect>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <summondummy.h>
#include <gamescene.h>
#include <physics.h>
#include <bomb.h>
#include <mainwindow.h>

#include "health.h"

Player::Player(map *ma, float ix, float iy, int xi, int yi, int idd)
{
    m = ma;
    x = ix;
    y = iy;
    idx = xi;
    idy = yi;
    id = idd;

}
void Player::changepush()
{
    pushable = 0;
}
void Player::onAttach()
{
    this->transform = this->gameObject->getComponent<ImageTransform>();
    Q_ASSERT(this->transform != nullptr);
}
int Player::get_id()
{
    return id;
}
int Player::get_idx()
{
    return idx;
}
int Player::get_idy()
{
    return idy;
}
int Player::get_x()
{
    return x;
}
int Player::get_y()
{
    return y;
}
void Player::set_x(float ix)
{
    x = ix;
}
void Player::set_y(float iy)
{
    y = iy;
}
const char *Player::getImage(int id, int dir, int sta)
{
    if (id == 1 && dir == 1)
        return ":/res/unit_monster_W.png";
    else if (id == 1 && dir == 2)
        return ":/res/unit_monster_A.png";
    else if (id == 1 && dir == 3)
        return ":/res/unit_monster_S.png";
    else if (id == 1 && dir == 4)
        return ":/res/unit_monster_D.png";
    else if (id == 2 && dir == 1)
    {
        if (sta == 0)
            return ":/res/monster2w1.png";
        else
            return ":/res/monster2w2.png";
    }
    else if (id == 2 && dir == 2)
    {
        if (sta == 0)
            return ":/res/monster2a1.png";
        else
            return ":/res/monster2a2.png";
    }
    else if (id == 2 && dir == 3)
    {
        if (sta == 0)
            return ":/res/monster2s1.png";
        else
            return ":/res/monster2s2.png";
    }
    else if (id == 2 && dir == 4)
    {
        if (sta == 0)
            return ":/res/monster2d1.png";
        else
            return ":/res/monster2d2.png";
    }
    else
        return " ";
}
bool Player::whogetKey(int id, int dir)
{
    if (id == 1 && dir == 1)
        return this->getKey(Qt::Key_W);
    else if (id == 1 && dir == 2)
        return this->getKey(Qt::Key_A);
    else if (id == 1 && dir == 3)
        return this->getKey(Qt::Key_S);
    else if (id == 1 && dir == 4)
        return this->getKey(Qt::Key_D);
    else if (id == 1 && dir == 0)
        return this->getKeyDown(Qt::Key_Space);
    else if (id == 2 && dir == 1)
        return this->getKey(Qt::Key_I);
    else if (id == 2 && dir == 2)
        return this->getKey(Qt::Key_J);
    else if (id == 2 && dir == 3)
        return this->getKey(Qt::Key_K);
    else if (id == 2 && dir == 4)
        return this->getKey(Qt::Key_L);
    else if (id == 2 && dir == 0)
        return this->getKeyDown(Qt::Key_Return);
    return false;
}
QTimer * Player::gettimer()
{
    return updateTimer;
}
void Player::GetTool(int i, int j)
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
        connect(updateTimer, &QTimer::timeout, this, &Player::changepush);
        updateTimer->start();
    }
    if (yes == 1)
    {
        auto musictool = new QSoundEffect;
        musictool->setSource(QUrl::fromLocalFile(":/res/tool.wav"));
        musictool->setVolume(0.15f);
        musictool->play();
    }
    m->MAP[i][j] = 0;
    m->MAPTool[i][j] = 0;
    m->NOWTool[i][j] = 0;
}

void Player::movebomb(int dir)
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
void Player::onUpdate(float deltaTime)
{
    QVector<GameObject *>::Iterator it;
    QVector<GameObject *> temp;

    for (int i = 0; i < mainboard.size();)
    {
        auto tr = mainboard[i]->getComponent<Transform>();
        if ((speedflag == 1 && tr->type() == 11 )||( bombpowerflag == 1 && tr->type() == 12 )|| (bombnumflag == 1 && tr->type() == 13 )|| (scoreflag == 1 && tr->type() == 15) || (tr->type() == 14&& live < 0))
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
    if (live < 0)
    {
        bk->stop();
        Mainone->begin = 0;
        auto musictool = new QSoundEffect;
        musictool->setSource(QUrl::fromLocalFile(":/res/vec.wav"));
        musictool->setVolume(0.15f);
        musictool->play();


        auto map = new GameObject();
        if (id == 1)
        {
            ImageTransformBuilder()
                    .setPos(QPointF(-1, -1))
                    .setImage(":/res/P1DIED.png")
                    .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
                    .addToGameObject(map);
        }
        else
        {
            ImageTransformBuilder()
                    .setPos(QPointF(-1, -1))
                    .setImage(":/res/P2DEID.png")
                    .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
                    .addToGameObject(map);
        }
        this->attachGameObject(map);
        auto map2 = new GameObject();

            qDebug() << "innnnnnnnnnnn";
            ImageTransformBuilder()
                    .setPos(QPointF(40, 20))
                    .setImage(":/res/GAMEOVER.png")
                    .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
                    .addToGameObject(map2);
            this->attachGameObject(map2);

        this->gameObject->getParentGameScene()->getUpdateTimer()->stop();
        nowtime->stop();
    }
    float vx = 0, vy = 0, half = 0, bvx = 135, bvy = 135;
    QPointF velocity;
    if (this->whogetKey(id, 1) && flagmove == 0 && live == 3)
    {
        half = (idx + 1) * 50 - 10;
        //qDebug() << "上" << transform->pos() << idy << idx;
        flagmove = 1;
        float uphalf = idy * 50 + 10;
        if ((y - 1 * speed) < 50)
            return;
        if ((y - 1 * speed) / 50 >= idy + 1 && x >= half && x <= half + 50)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 1, stage));
            transform->setPos(QPointF(x, y - 1 * speed)), y = y - 1 * speed;
        }
        else if ((y - 1 * speed) / 50 < idy + 1 && (m->MAP[idy - 1][idx] == 0 || (m->MAP[idy - 1][idx] == 10 && pushable == 1)) && x >= half && x <= half + 50)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 1, stage));
            transform->setPos(QPointF(x, y - 1 * speed)), y = y - 1 * speed, idy--;
            if (y - 1 * speed > uphalf)
                idy++;
            else
                this->movebomb(1);
        }
    }
    else if (this->whogetKey(id, 2) && flagmove == 0 && live == 3)
    {
        half = idy * 50 + 35;
        float lefthalf = idx * 50 + 25;
        //qDebug() << "左" << transform->pos() << idy << idx;
        flagmove = 1;
        if ((x - 1 * speed) < 50)
            return;
        if ((x - 1 * speed) / 50 >= idx + 1 && y >= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 2, stage));
            transform->setPos(QPointF(x - 1 * speed, y)), x = x - 1 * speed;
        }
        else if ((x - 1 * speed) / 50 < idx + 1 && (m->MAP[idy][idx - 1] == 0 || (m->MAP[idy][idx - 1] == 10 && pushable == 1)) && y >= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 2, stage));
            transform->setPos(QPointF(x - 1 * speed, y)), x = x - 1 * speed, idx--;
            if (x - 1 * speed > lefthalf)
                idx++;
            else
                this->movebomb(3);
        }
    }
    else if (this->whogetKey(id, 3) && flagmove == 0 && live == 3)
    {
        half = (idx + 1) * 50 + 15;
        //qDebug() << "下" << transform->pos() << idy + 1 << idx << id << m->MAP[idy + 1][idx];
        flagmove = 1;
        float downhalf = (idy + 2) * 50 - 25;
        vy += 62.5 * speed;
        if ((y + 1 * speed) > 750)
            return;
        if ((y + 1 * speed) / 50 <= idy + 1 && x <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 3, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), y = y + 1 * speed;
        }
        else if ((y + 1 * speed) / 50 > idy + 1 && (m->MAP[idy + 1][idx] == 0 || (m->MAP[idy + 1][idx] == 10 && pushable == 1))&& x <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 3, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), y = y + 1 * speed, idy++;
            if (y + 1 * speed < downhalf)
                idy--;
            else
               this->movebomb(2);
        }
        else if ((y + 1 * speed) / 50 + 1 > idy + 1 && fmod(y + 1 * speed, 10) == 0 && x <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 3, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), y++;
            if (y + 1 * speed < downhalf)
                idy--;
        }
    }
    else if (this->whogetKey(id, 4) && flagmove == 0 && live == 3)
    {
        half = (idy + 1) * 50 + 15;
        //qDebug() << "右" << transform->pos() << idy << idx << m->MAP[idy][idx + 1];
        float righthalf = (idx + 2) * 50 - 25;
        flagmove = 1;
        vx += 62.5 * speed;
        if ((x +  1 * speed) > 1000)
            return;
        if ((x + 1 * speed) / 50 < idx + 1 && y <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 4, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), x = x + 1 * speed;
        }
        else if ((x + 1 * speed) / 50 + 1 >= idx + 1 && (m->MAP[idy][idx + 1] == 0 || (m->MAP[idy][idx + 1] == 10 && pushable == 1)) && y <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 4, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), x = x + 1 * speed, idx++;
            if (x + 1 * speed <= righthalf)
                idx--;
            else
                this->movebomb(4);
        }
        else if ((x + 1 * speed) / 50 + 1 >= idx + 1 && fmod(x + 1 * speed, 10) == 0 && y <= half)
        {
            stage = (stage + 1) % 13;
            if (stage % 7 == 0)
                transform->setImage(getImage(id, 4, stage));
            transform->moveBy(deltaTime * vx, deltaTime * vy), x = x + 1 * speed;
            if (x + 1 * speed < righthalf)
                idx--;
        }
    }
    flagmove = 0;
    if (this->whogetKey(id, 0) && bombflag == 0 && bombnum > 0 && live == 3)
    {
        bombflag = 1;
        m->MAP[idy][idx] = 10;
        qDebug() << idy << idx;
        bombnum--;
        bombnumflag = 1;
        float curx = (idx + 1) * 50;
        float cury = (idy + 1) * 50;
        auto bomb = new GameObject();
        bomb->addComponent(ImageTransformBuilder()
                               .setPos(QPointF(curx, cury))
                               .setImage(":/res/custom_bubble3.png")
                               .setAlignment(Qt::AlignHCenter)
                               .setAlignment(Qt::AlignVCenter)
                               .build());
        bomb->addComponent(new Bomb(m, curx, cury, idx, idy, id, 1));
        BombList.emplace_back(bomb);
        m->Bomblist.emplace_back(bomb);
        this->attachGameObject(bomb);
        for (auto b : BombList)
            b->getComponent<Bomb>()->changepower(bombpower);
    }
    bombflag = 0;
    if (!BombList.empty())
    {
        for (auto b : BombList)
        {
            if (b->getComponent<Bomb>()->interval < -1)
            {
                 qDebug() <<"debomb" << b->getComponent<Bomb>()->get_x() << b->getComponent<Bomb>()->get_y();
                if (b->getComponent<Bomb>()->curscore != 0)
                    score += b->getComponent<Bomb>()->curscore, scoreflag = 1;
                score += b->getComponent<Bomb>()->bombplayer;
                for (int i = (-1) * bombpower; i <= bombpower; i++)
                {
                    if (b->getComponent<Bomb>()->get_y() + i < 0 || b->getComponent<Bomb>()->get_y() + i >= 20|| b->getComponent<Bomb>()->get_x() + i < 0 || b->getComponent<Bomb>()->get_x() + i >= 15)
                          continue;
                    qDebug() << i << "de" << b->getComponent<Bomb>()->get_x() << b->getComponent<Bomb>()->get_y();
                    m->NOWBomb[b->getComponent<Bomb>()->get_x() + i][b->getComponent<Bomb>()->get_y()] = 0;
                    m->NOWBomb[b->getComponent<Bomb>()->get_x()][b->getComponent<Bomb>()->get_y() + i] = 0;
                }
                m->MAP[b->getComponent<Bomb>()->get_x()][b->getComponent<Bomb>()->get_y()] = 0;
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
                bombnum++;
                bombnumflag= 1;
            }
        }
    }
}
