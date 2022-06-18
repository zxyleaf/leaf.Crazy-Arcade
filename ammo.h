#ifndef AMMO_H_
#define AMMO_H_

#include <map.h>
#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include <gamescene.h>
#include <imagetransform.h>
class Ammo : public Component {
 private:
    int type;
    int idx;
    int idy;
    int x;
    int y;
    map *m;
 public:
  explicit Ammo(map *ma, int type, int ix, int iy);
  int stage = 0;
  bool flagup = 0;
  float interval = 0.5;
  void onAttach() override;
  void onUpdate(float deltaTime) override;
  const char* getImage(int type, int i, int j);
 protected:
  ImageTransform *transform = nullptr;
  QGraphicsItem *collider = nullptr;


  QPointF velocity;
};

#endif  // AMMO_H_
