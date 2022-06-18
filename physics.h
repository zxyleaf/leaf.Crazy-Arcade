#ifndef PHYSICS_H
#define PHYSICS_H

#include <map.h>
#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
class Physics : public Component
{
public :
  Physics(int i, int j, map *ma);

  void onAttach() override;
  void onUpdate( float deltaTime ) override;

  void setVelocity(float vx, float vy);

private:
 ImageTransform *transform;
 map *m;
 int pi = 0, pj = 0;
 int id = 0;
 float vx = 0 ,vy = 0;
};

#endif // PHYSICS_H
