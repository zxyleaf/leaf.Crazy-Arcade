#include "ammo.h"

#include <QBrush>
#include <QPropertyAnimation>
#include <QGraphicsEllipseItem>
#include <gamescene.h>
#include <imagetransform.h>
#include "hitable.h"

Ammo::Ammo(map *ma, int ty, int ix, int iy) : Component()
{
  m = ma;
  type = ty;
  idy = iy;
  idx = ix;
  x = (iy + 1) * 50;
  y = (ix + 1) * 50;
}

void Ammo::onAttach()
{
  this->transform = this->gameObject->getComponent<ImageTransform>();
  Q_ASSERT(this->transform != nullptr);
}
const char *Ammo::getImage(int type, int i, int j)
{

  return "";
}
void Ammo::onUpdate(float deltaTime)
{
  interval -= deltaTime;

  if (interval > 0)
      return;
  interval = 1;
  if (m->NOWTool[idy][idx] != 0)
  {
      if (stage == 1)
         transform->moveBy(0, -3), y = y - 3, stage++;
      else if (stage == 2)
         transform->moveBy(0, 7), y = y + 7, stage++;
      else
          transform->moveBy(0, -7), y = y - 7, stage = 2;
  }
  else
  {
      if (y % 50 != 0)
          transform->setPos(QPointF(50 * (idx + 1), 50 * (1 + idy))), y = (idx + 1) * 50;
  }
}
