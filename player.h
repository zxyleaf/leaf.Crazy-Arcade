#ifndef PLAYER_H
#define PLAYER_H
#include <map.h>
#include <bomb.h>
#include <QVector>
#include <component.h>
#include <gamescene.h>
#include <imagetransform.h>
class Transform;
class Physics;
class Hittable;
class Player: public Component
{
private:
    int idx;
    int idy;
    int id;
    float x;
    float y;
    int dir = 2;
    int bombpower = 1;
    float speed = 1;
    bool scoreflag = 0;
    bool speedflag = 0;
    bool bombnumflag = 0;

    bool bombpowerflag = 0;
    bool pushable = 0;
    int stage = 0;
     QVector<GameObject *> BombList;
     map *m;
public:
     QVector<GameObject *> mainboard;
     bool flagmove = 0;
     bool bombflag = 0;
    int bombnum = 1;
    int live = 3;
    int score = 0;
    void changepush();
    Player(map *ma,float ix, float iy,int idx, int idy, int idd);
    int get_x();
    int get_y();
    int get_idx();
    int get_idy();
    int get_id();
    void set_x(float ix);
    void set_y(float iy);
    void movebomb(int dir);
    const char* getImage(int id, int dir, int sta);
    bool whogetKey(int id, int dir);
    void onAttach() override;
    void onUpdate(float deltaTime) override;
    void GetTool(int i , int j);
    QTimer * gettimer();
protected:
 ImageTransform *collider = nullptr;
 ImageTransform *transform = nullptr;
 Transform *transscore = nullptr;
 Bomb * B = nullptr;
 const float interval = .5;
 float cooldown = interval;
 QTimer *updateTimer = nullptr;


};

#endif // PLAYER_H
