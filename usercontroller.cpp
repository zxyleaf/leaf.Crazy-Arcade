#include "usercontroller.h"
#include <mainwindow.h>
UserController::UserController()
{

}
void UserController::onAttach()
{
  physics = this->gameObject->getComponent<Physics>();
  Q_ASSERT(physics != nullptr);

}

void UserController::onUpdate(float deltaTime)
{
//  float vx = 0 , vy = 0 ;
//  if( getKey (Qt::Key_A) ) vx -= 30;
//  if( getKey (Qt::Key_D) ) vx += 30;
//  if( getKey (Qt::Key_W) ) vy -= 30;
//  if( getKey (Qt::Key_S) ) vy += 30;
  //physics->setVelocity(vx, vy);
}
