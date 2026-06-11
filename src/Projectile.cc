#include "Projectile.h"
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "ResourceManager.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f pos, float angle, int speed, bool isEnemyFired)
    : Entity{pos, ResourceManager::getSpriteWithName(Tex::Projectile), 1, speed, {}},
      angle{angle}, isEnemyFired{isEnemyFired}
{
    sprite.setPosition(pos);
}
void Projectile::collide(Object* other)
{
  if(dynamic_cast<Entity*>(other) != nullptr)
  {
    
  }
}
void Projectile::move()
{
  float dx {speed*std::cos(angle)};
  float dy {speed*std::sin(angle)};

  pos.x += dx;
  pos.y += dy;

  sprite.move(dx,dy);
}
