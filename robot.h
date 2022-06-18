#ifndef ROBOT_H
#define ROBOT_H
#include <map.h>
#include <bomb.h>
#include <QVector>
#include <component.h>
#include <gamescene.h>
#include <imagetransform.h>
class Transform;
class Physics;
class Hittable;

class Robot : public Component
{
private:
    int idx;
    int idy;
    int id;
    float x;
    float y;
    int dir = 0;
    int stage = 3;
    int predir = 0;
    int walk = 0;
    int walkdir = 0;
    bool liveflag = 0;
    bool flag = 0;
    bool scoreflag = 0;
    bool stopflag = 0;
    bool returnflag = 0;
    float returntime = 0;
    int cnt = 0;
    QVector<GameObject *> BombList;
    map *m;
public:
    int live = 3;
    int score = 0;
    Robot(map *ma,float ix, float iy,int idx, int idy, int idd);
    QVector<GameObject *> mainboard;
    int get_id();
    int get_idx();
    int get_idy();
    void onAttach() override;
    void onUpdate(float deltaTime) override;
    const char* getImage(int id, int dir, int stage);
protected:
 ImageTransform *transform = nullptr;
 Bomb * B = nullptr;
 float cooltime = 0.16;
 float bombtime = 13.2;
};

#endif // ROBOT_H
