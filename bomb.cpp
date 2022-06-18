#include "bomb.h"

#include <map.h>
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
#include <transformbuilder.h>
#include <QGraphicsRectItem>
#include <QSoundEffect>
#include <QGraphicsSimpleTextItem>
#include <gamescene.h>
#include <player.h>
#include <robot.h>
#include <physics.h>
#include "health.h"
Bomb::Bomb(map *ma, float ix, float iy, int xi, int yi, int idd, int po) : Component()
{
    m = ma;
    x = ix;
    y = iy;
    idx = xi;
    idy = yi;
    id = idd;
    power = po;
}
int Bomb::get_x()
{
    return idy;
}
int Bomb::get_y()
{
    return idx;
}
float Bomb::get_ix()
{
    return x;
}
float Bomb::get_iy()
{
    return y;
}
int Bomb::get_power()
{
    return power;
}
void Bomb::changepower(int num)
{
    power = num;
    //qDebug() << "change" << power;
}
const char *Bomb::getdiedImage2(int stage, int ty,int id, int c)
{
    //qDebug()<<"c=" << c << "stage" << stage;
    if ((c == 63 && stage < 3)  ||(c <= 53 && stage <= 1) )
    {
        if (ty == 100)
            if (id == 1)
                return ":/res/monster1died.png";
            else
                return ":/res/monster2died.png";
        else if (ty == 110)
            if (id == 1)
            {
                bombplayer = 5;
                return ":/res/robotdead.png";}
            else
            {
                bombplayer = 5;
                return ":/res/robot1dead.png";}
        else
            return " ";
    }
    if (stage == 3)
    {
        if (ty == 100)
            if (id == 1)
                return ":/res/monster1die.png";
            else
                return ":/res/monster2die.png";
        else if (ty == 110)
            if (id == 1)
                return ":/res/robotdie.png";
            else
                return ":/res/robot1die.png";
        else
            return " ";
    }
    if (stage == 2)
    {
        if (ty == 100)
            if (id == 1)
               return ":/res/monster1dying.png";
            else
                return ":/res/monster2dying.png";
        else if (ty == 110)
            if (id == 1)
                return ":/res/robotdying.png";
            else
            {
                bombplayer = 5;
                return ":/res/robot1dying.png";}
        else
            return " ";
    }
    if (stage == 1)
    {
        if (ty == 100)
            if (id == 1)
                return ":/res/monster1dead.png";
            else
                return ":/res/monster2dead.png";
        else if (ty == 110)
            if (id == 1)
                return ":/res/robotdied.png";
            else
                return ":/res/robot1died.png";
        else
            return " ";
    }
    return " ";
}
const char *Bomb::getImage2(int i, int j)
{
    if (m->MAPTool[i][j] == 1)
    {
        m->NOWTool[i][j] = 1;
        return ":/res/tool1.png";
    }
    if (m->MAPTool[i][j] == 3)
    {
        m->NOWTool[i][j] = 1;
        return ":/res/tool2.png";
    }
    if (m->MAPTool[i][j] == 2)
    {
        m->NOWTool[i][j] = 1;
        return ":/res/tool3.png";
    }
    if (m->MAPTool[i][j] == 4)
    {
        m->NOWTool[i][j] = 1;
        return ":/res/tool4.png";
    }
    else
        return " ";
    m->MAP[i][j] = 0;
}

const char *Bomb::getImage(int c, int dir, bool edg, int i, int j)
{
    if (c == 1 && dir == 0)
        return ":/res/bomb1.png";
    else if (c == 1 && dir == 1 && edg == 0)
        return ":/res/bomb1w.png";
    else if (c == 1 && dir == 1 && edg == 1)
        return ":/res/bombw1.png";
    else if (c == 1 && dir == 2 && edg == 0)
        return ":/res/bomb1s.png";
    else if (c == 1 && dir == 2 && edg == 1)
        return ":/res/bombs1.png";
    else if (c == 1 && dir == 3 && edg == 0)
        return ":/res/bomb1a.png";
    else if (c == 1 && dir == 3 && edg == 1)
        return ":/res/bomba1.png";
    else if (c == 1 && dir == 4 && edg == 0)
        return ":/res/bomb1d.png";
    else if (c == 1 && dir == 4 && edg == 1)
        return ":/res/bombd1.png";
    else if (c == 23 && dir == 0)
        return ":/res/bomb2.png";
    else if (c == 23 && dir == 1)
        return ":/res/bombw11.png";
    else if (c == 23 && dir == 2)
        return ":/res/bombs11.png";
    else if (c == 23 && dir == 3)
        return ":/res/bomba11.png";
    else if (c == 23 && dir == 4)
        return ":/res/bombd11.png";
    else if (c == 38 && dir == 1)
        return ":/res/bombw12.png";
    else if (c == 38 && dir == 2)
        return ":/res/bombs12.png";
    else if (c == 38 && dir == 3)
        return ":/res/bomba12.png";
    else if (c == 38 && dir == 4)
        return ":/res/bombd12.png";
    else if (c == 38 && dir == 0)
        return ":/res/bomb3.png";
    else if (c == 53 && dir == 1)
        return ":/res/bombw13.png";
    else if (c == 53 && dir == 2)
        return ":/res/bombs13.png";
    else if (c == 53 && dir == 3)
        return ":/res/bomba13.png";
    else if (c == 53 && dir == 4)
        return ":/res/bombd13.png";
    else if (c == 63 && dir == 1)
    {
        m->MAP[i][j] = 0;
        return getImage2(i, j);
    }
    else if (c == 63 && dir == 2)
    {
        m->MAP[i][j] = 0;
        return getImage2(i, j);
    }
    else if (c == 63 && dir == 3)
    {
        m->MAP[i][j] = 0;
        return getImage2(i, j);
    }
    else if (c == 63 && dir == 4)
    {
        m->MAP[i][j] = 0;
        return getImage2(i, j);
    }
    return nullptr;
}
void Bomb::onAttach()
{
    this->transform = this->gameObject->getComponent<ImageTransform>();
    Q_ASSERT(this->transform != nullptr);
}
void Bomb::bombing(int c)
{
    m->MAP[idy][idx] = 0;
    bool dirflag = 0;
    if (c == 1 || c == 23 || c == 38 || c == 53 || c == 63)
    {
        if (m->MAPTool[idy][idx] != 0 && c == 63)
        {

            if ((int)m->Maplist[(idy)*20 + idx]->getComponent<ImageTransform>()->y() % 50 != 0)
                m->Maplist[(idy)*20 + idx]->getComponent<ImageTransform>()->setPos(QPointF(50 * (idx + 1), 50 * (1 + idy)));
            m->Maplist[(idy)*20 + idx]->getComponent<ImageTransform>()->setImage(getImage2(idy, idx));
        }
        else
        {
            auto tr = m->Maplist[(idy)*20 + idx]->getComponent<ImageTransform>();

            for (auto item : tr->collidingItems())
            {
                auto trans = dynamic_cast<ImageTransform *>(item);
                if (trans->type() == 100)
                {
                    int live = trans->getParentGameObject()->getComponent<Player>()->live;
                    int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                    int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                    int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                    if (curidy == idy && curidx == idx)
                    {
                        trans->getParentGameObject()->getComponent<Player>()->live--;
                        trans->setImage(getdiedImage2(live, trans->type(), id, c));
                    }
                }
                else if (trans->type() == 110)
                {
                    //bombplayer = 5;
                    int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                    int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                    int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                    int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                    if (live == 3 && c >= 53)
                        break;
                    if (curidy == idy && curidx == idx)
                    {
                        trans->getParentGameObject()->getComponent<Robot>()->live--;
                        trans->setImage(getdiedImage2(live, trans->type(), id, c));
                    }
                }
            }
            if ((int)tr->y() % 50 != 0)
                tr->setPos(QPointF(50 * (idx + 1), 50 * (1 + idy)));
           tr->setImage(getImage(c, 0, 0, idy, idx));
        }
        for (int i = 1; i <= power; i++)
        {
            if (idy - i < 0)
                break;
            if (m->MAP[idy - i][idx] == 11 ||  m->MAP[idy - i][idx] == 7 || m->MAP[idy - i][idx] == 30 || m->MAP[idy - i][idx] == 1 || m->MAP[idy - i][idx] == 4 || m->MAP[idy - i][idx] == 5)
                break;
            else if (m->MAP[idy - i][idx] == 10 || m->MAP[idy - i][idx] == 8 || m->MAP[idy - i][idx] == 3 || m->MAP[idy - i][idx] == 6 || m->MAP[idy - i][idx] == 2 || (i == power && m->MAP[idy - i][idx] == 0) || (idy - i - 1 >= 0 && (m->MAP[idy - i - 1][idx] == 1 || m->MAP[idy - i - 1][idx] == 4 || m->MAP[idy - i - 1][idx] == 5 || m->MAP[idy - i - 1][idx] == 7 || m->MAP[idy - i - 1][idx] == 11 || m->MAP[idy - i - 1][idx] == 30)))
            {
                    auto tr = m->Maplist[(idy - i) * 20 + idx]->getComponent<ImageTransform>();
                    if ((tr->type() == 2 || tr->type() == 3 || tr->type() == 6 || tr->type() == 8) && c == 63)
                        curscore++;
                    for (auto item : tr->collidingItems())
                    {
                        auto trans = dynamic_cast<ImageTransform *>(item);
                        if (trans->type() == 100)
                        {
                            int live = trans->getParentGameObject()->getComponent<Player>()->live;
                            int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                            int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                            int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                            if (curidy == idy - i && curidx == idx)
                            {
                                trans->getParentGameObject()->getComponent<Player>()->live--;

                                trans->setImage(getdiedImage2(live, trans->type(), id ,c));
                            }
                        }
                        else if (trans->type() == 110)
                        {

                            int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                            int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                            int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                            int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                            if (live == 3 && c >= 53)
                                break;
                            if (curidy == idy - i && curidx == idx)
                            {

                                trans->getParentGameObject()->getComponent<Robot>()->live--;
                                trans->setImage(getdiedImage2(live, trans->type(), id, c));
                            }
                        }
                    }
                    if ((int)tr->y() % 50 != 0)
                        tr->setPos(QPointF(50 * (idx + 1), 50 * (1 - i + idy)));
                    tr->setImage(getImage(c, 1, 1, idy - i, idx));
                    break;
              }
              else if (m->MAP[idy - i][idx] == 10 || m->MAP[idy - i][idx] == 0 || m->MAP[idy - i][idx] == 8 || m->MAP[idy - i][idx] == 3 || m->MAP[idy - i][idx] == 6 || m->MAP[idy - i][idx] == 2)
              {
                   auto tr = m->Maplist[(idy - i)*20 + idx]->getComponent<ImageTransform>();
                   for (auto item : tr->collidingItems())
                   {
                       auto trans = dynamic_cast<ImageTransform *>(item);
                       if (trans->type() == 100)
                       {
                            int live = trans->getParentGameObject()->getComponent<Player>()->live;
                            int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                            int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                            int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                            if (curidy == idy - i && curidx == idx)
                            {

                                 trans->getParentGameObject()->getComponent<Player>()->live--;
                                trans->setImage(getdiedImage2(live, trans->type(), id, c));
                            }
                        }
                       else if (trans->type() == 110)
                       {
                           //bombplayer = 5;
                           int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                           int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                           int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                           int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                           if (live == 3 && c >= 53)
                               break;
                           if (curidy == idy - i && curidx == idx)
                           {
                               trans->getParentGameObject()->getComponent<Robot>()->live--;
                               trans->setImage(getdiedImage2(live, trans->type(), id, c));
                           }
                       }
                    }
                   if ((int)tr->y() % 50 != 0)
                       tr->setPos(QPointF(50 * (idx + 1), 50 * (1 + idy - i)));
                   tr->setImage(getImage(c, 1, 0, idy - i, idx));
               }
        }
        for (int i = 1; i <= power; i++)
        {
            if (idy + i >= 15)
                break;
            if (m->MAP[idy + i][idx] == 30 || m->MAP[idy + i][idx] == 7 ||m->MAP[idy + i][idx] == 11 || m->MAP[idy + i][idx] == 1 || m->MAP[idy + i][idx] == 4 || m->MAP[idy + i][idx] == 5)
                break;
            else if (m->MAP[idy + i][idx] == 8 || m->MAP[idy + i][idx] == 3 || m->MAP[idy + i][idx] == 6 || m->MAP[idy + i][idx] == 2 || (i == power && m->MAP[idy + i][idx] == 0) || (idy + i + 1 < 15 && (m->MAP[idy + i + 1][idx] == 1 || m->MAP[idy + i + 1][idx] == 4 || m->MAP[idy + i + 1][idx] == 5 || m->MAP[idy + i + 1][idx] == 7 || m->MAP[idy + i + 1][idx] == 30 || m->MAP[idy + i + 1][idx] == 11)))
            {
                auto tr =m->Maplist[(idy + i) * 20 + idx]->getComponent<ImageTransform>();
                if ((tr->type() == 2 || tr->type() == 3 || tr->type() == 6 || tr->type() == 8) && c == 63)
                    curscore++;
                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);
                    if (trans->type() == 100)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                        if (curidy == idy + i && curidx == idx)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                     }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;
                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy + i && curidx == idx)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                 }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx + 1), 50 * (1 + i + idy)));
                 tr->setImage(getImage(c, 2, 1, idy + i, idx));
                 break;
            }
            else if (m->MAP[idy + i][idx] == 10 || m->MAP[idy + i][idx] == 0 || m->MAP[idy + i][idx] == 8 || m->MAP[idy + i][idx] == 3 || m->MAP[idy + i][idx] == 6 || m->MAP[idy + i][idx] == 2)
            {
                auto tr =m->Maplist[(idy + i) * 20 + idx]->getComponent<ImageTransform>();

                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);
                    if (trans->type() == 100)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();

                        if (curidy == idy + i && curidx == idx)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;

                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy + i && curidx == idx)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx + 1), 50 * (1 + idy+ i )));
               tr->setImage(getImage(c, 2, 0, idy + i, idx));
            }
        }
        for (int i = 1; i <= power; i++)
        {
            //qDebug() << "power" << power << "i=" << i<< m->MAP[idy][idx + i];
            if (idx + i >= 20)
                break;
            if (m->MAP[idy][idx + i] == 11 || m->MAP[idy][idx + i] == 30 || m->MAP[idy][idx + i] == 7 || m->MAP[idy][idx + i] == 1 || m->MAP[idy][idx + i] == 4 || m->MAP[idy][idx + i] == 5 || m->MAP[idy][idx + i] == 7)
                break;
            else if (m->MAP[idy][idx + i] == 8 || m->MAP[idy][idx + i] == 3 || m->MAP[idy][idx + i] == 6 || m->MAP[idy][idx + i] == 2 || (i == power && m->MAP[idy][idx + i] == 0) || (idx + i + 1 < 20 && (m->MAP[idy][idx + i + 1] == 1 || m->MAP[idy][idx + i + 1] == 4|| m->MAP[idy][idx + i + 1] == 5 || m->MAP[idy][idx + i + 1] == 7 || m->MAP[idy][idx + i + 1] == 11 || m->MAP[idy][idx + i + 1] == 30)))
            {
                auto tr = m->Maplist[idy * 20 + idx + i]->getComponent<ImageTransform>();
                if ((tr->type() == 2 || tr->type() == 3 || tr->type() == 6 || tr->type() == 8) && c == 63)
                    curscore++;
                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);
                    if (trans->type() == 100)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();

                        if (curidy == idy && curidx == idx + i)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;
                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy && curidx == idx + i && live < 2)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx + i  + 1), 50 * (1 + idy)));
               tr->setImage(getImage(c, 4, 1, idy, idx + i));
               break;
            }
            else if (m->MAP[idy][idx + i] == 10 || m->MAP[idy][idx + i] == 0 || m->MAP[idy][idx + i] == 8 || m->MAP[idy][idx + i] == 3 || m->MAP[idy][idx + i] == 6 || m->MAP[idy][idx + i] == 2)
            {
                auto tr = m->Maplist[idy * 20 + idx + i]->getComponent<ImageTransform>();
                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);
                    if (trans->type() == 100)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy && curidx == idx + i)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;
                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy && curidx == idx + i)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx + i + 1), 50 * (1 + idy)));
               tr->setImage(getImage(c, 4, 0, idy, idx + i));

            }
        }
        for (int i = 1; i <= power; i++)
        {
            if (idx - i < 0)
                break;
            if (m->MAP[idy][idx - i] == 11 || m->MAP[idy][idx - i] == 30 || m->MAP[idy][idx - i] == 1 || m->MAP[idy][idx - i] == 4 || m->MAP[idy][idx - i] == 5 || m->MAP[idy][idx - i] == 7)
                break;
            else if (m->MAP[idy][idx - i] == 10 || m->MAP[idy][idx - i] == 8 || m->MAP[idy][idx - i] == 3 || m->MAP[idy][idx - i] == 6 || m->MAP[idy][idx - i] == 2 || (i == power && m->MAP[idy][idx - i] == 0) || (idx - i - 1 >= 0 && (m->MAP[idy][idx - i - 1] == 1 || m->MAP[idy][idx - i - 1] == 4 || m->MAP[idy][idx - i - 1] == 5 || m->MAP[idy][idx - i - 1] == 7 || m->MAP[idy][idx - i - 1] == 30 || m->MAP[idy][idx - i - 1] == 11)))
            {
                auto tr = m->Maplist[(idy)*20 + idx - i]->getComponent<ImageTransform>();
                if ((tr->type() == 2 || tr->type() == 3 || tr->type() == 6 || tr->type() == 8 )&& c == 63)
                    curscore++;
                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);
                    if (trans->type() == 100)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();
                        if (curidy == idy && curidx == idx - i)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;
                        qDebug() << "2c=" << c << idy << idx;
                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy && curidx == idx - i)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx - i + 1), 50 * (1 + idy)));
               tr->setImage(getImage(c, 3, 1, idy, idx - i));
               break;
            }
            else if (m->MAP[idy][idx - i] == 10 || m->MAP[idy][idx - i] == 0 || m->MAP[idy][idx - i] == 3 || m->MAP[idy][idx - i] == 6 || m->MAP[idy][idx - i] == 2)
            {
                auto tr = m->Maplist[(idy)*20 + idx - i]->getComponent<ImageTransform>();
                for (auto item : tr->collidingItems())
                {
                    auto trans = dynamic_cast<ImageTransform *>(item);

                    if (trans->type() == 100 && trans->getParentGameObject()->getComponent<Player>()->live > 0)
                    {
                        int live = trans->getParentGameObject()->getComponent<Player>()->live;
                        int id = trans->getParentGameObject()->getComponent<Player>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Player>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Player>()->get_idy();

                        if (curidy == idy && curidx == idx - i)
                        {

                            trans->getParentGameObject()->getComponent<Player>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                    else if (trans->type() == 110)
                    {
                        //bombplayer = 5;
                        //qDebug() << "c=" << c << idy << idx - i;
                        int live = trans->getParentGameObject()->getComponent<Robot>()->live;
                        int id = trans->getParentGameObject()->getComponent<Robot>()->get_id();
                        int curidx = trans->getParentGameObject()->getComponent<Robot>()->get_idx();
                        int curidy = trans->getParentGameObject()->getComponent<Robot>()->get_idy();
                        if (live == 3 && c >= 53)
                            break;
                        if (curidy == idy && curidx == idx - i)
                        {
                            trans->getParentGameObject()->getComponent<Robot>()->live--;
                            trans->setImage(getdiedImage2(live, trans->type(), id, c));
                        }
                    }
                }
                if ((int)tr->y() % 50 != 0)
                    tr->setPos(QPointF(50 * (idx - i + 1), 50 * (1 + idy)));
               tr->setImage(getImage(c, 3, 0, idy, idx - i));
            }
        }
    }
}
void Bomb::onUpdate(float deltaTime)
{
    cnt++;
    interval -= deltaTime;
    float bvx = 0, bvy = 0;
    if (hit != 0 && interval >= 0)
    {
        m->MAP[idy][idx] = 0;
        if ((hit == 1 && y - 8 >= 40) && ((y - 8) / 50 >= idy + 1 || ((y - 8) / 50 < idy + 1 && m->MAP[get_x() - 1][get_y()] == 0)))
        {
            bvy -= 500;
            y = y - 8;
            if (y <= idy * 50)
                idy--;
            transform->moveBy(deltaTime * bvx, deltaTime * bvy);
        }
        else if ((hit == 2 && y + 8 <= 750) && ((y + 8) / 50 <= idy + 1 || ((y + 8) / 50 > idy + 1 && m->MAP[get_x() + 1][get_y()] == 0)))
        {
            bvy += 500;
            y = y + 8;
            if (y >= (idy + 2) * 50)
                idy++;
            transform->moveBy(deltaTime * bvx, deltaTime * bvy);
        }
        else if ((hit == 3 && x - 8 >= 50) && ((x - 8) / 50 >= idx + 1 || ((x - 8) / 50 < idx + 1 && m->MAP[get_x()][get_y() - 1] == 0)))
        {
            bvx -= 500;
            x = x - 8;
            if (x - 8 < idx * 50)
                idx--;
            transform->moveBy(deltaTime * bvx, deltaTime * bvy);
        }
        else if ((hit == 4 && x + 8 < 1000) && ((x + 8) / 50 < idx + 1 || ((x + 8) / 50 >= idx + 1 && m->MAP[get_x()][get_y() + 1] == 0)))
        {
            bvx += 500;
            x = x + 8;
            if (x + 8 >= (idx + 2) * 50)
                idx++;
            transform->moveBy(deltaTime * bvx, deltaTime * bvy);
        }
        else
        {
            transform->setImage(nullptr);
            count++;
            if (interval  > 0)
                interval = 0;
            this->bombing(count);
        }
    }
    if (interval >= 0 && cnt == 40 || cnt == 100 || cnt == 160)
        transform->setImage(":/res/custom_bubble1.png");
    else if (interval >= 0 && (cnt == 50 || cnt == 110 || cnt == 170))
        transform->setImage(":/res/custom_bubble2.png");
    else if (cnt == 60 || cnt == 120 || cnt == 180)
        transform->setImage(":/res/custom_bubble3.png");
    if (interval < 0)
    {
        if (mu == 0)
        {
            auto musictool = new QSoundEffect;
            musictool->setSource(QUrl::fromLocalFile(":/res/battle_ef_002.wav"));
            musictool->setVolume(0.15f);
            musictool->play();
            mu = 1;
        }
        transform->setImage(nullptr);
        count++;
        this->bombing(count);

    }
}
