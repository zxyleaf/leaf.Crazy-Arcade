#include "physics.h"
#include <map.h>
Physics::Physics(int i ,int j,map *ma)
{
    pi = i;
    pj = j;
    id = i * 20 + j;
    m = ma;
}
void Physics:: onAttach ()
{
    transform = this->gameObject->getComponent<ImageTransform>();
    assert(transform != nullptr);
}

void Physics :: onUpdate (float deltaTime)
{

}
void Physics::setVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}
