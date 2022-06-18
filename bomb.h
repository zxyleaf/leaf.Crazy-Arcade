#ifndef BOMB_H
#define BOMB_H

#include <map.h>
#include <QTime>
#include <component.h>
#include <gamescene.h>
#include <imagetransform.h>
class Bomb : public Component
{
private:
    int idx;
    int idy;
    int id;
    float x;
    float y;
     map *m;
    int power;

public:
    int hit = 0;
    bool mu = 0;
    int count = 0;
     float interval = 3;
     int curscore = 0;
     int bombplayer = 0;
     int get_x();
     int get_y();
     float get_ix();
     float get_iy();
     int get_power();
     void bombing(int c);
     void changepower(int num);
     const char* getImage(int c, int dir, bool edg, int i, int j);
     const char* getImage2(int i, int j);
     const char* getdiedImage2(int stage, int ty, int id, int c);
    Bomb(map *ma,float ix, float iy,int idx, int idy, int idd, int po);
    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    ImageTransform *transform = nullptr;
    QTime *Tim;
    int cnt = 0;
};

#endif // BOMB_H
