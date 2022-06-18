#include "shooter.h"

#include <ammo.h>
#include <gameobject.h>
#include <transform.h>
#include <mainwindow.h>
#include <QGraphicsRectItem>

Shooter::Shooter() : Component() {}

void Shooter::onAttach() {
  this->transform = this->gameObject->getComponent<Transform>();
  Q_ASSERT(this->transform != nullptr);
  auto rect = new QGraphicsRectItem(this->transform);
  rect->setRect(QRectF(-30, -30, 60, 60));
}

void Shooter::onUpdate(float deltaTime) {
//  cooldown -= deltaTime;
//  if (cooldown > 0) return;
//  cooldown = interval;


}
