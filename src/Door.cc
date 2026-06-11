#include "Door.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

void Door::collide(Object* other)
{
  if(toID == 0)
    return;
  
  if(dynamic_cast<Player*>(other) != nullptr)
  {
    currentLevel->GoTo(this, toID);
  }
}

sf::Vector2f Door::getPlayerSpawnPos()
{
  
  sf::Vector2f result {getPosition()};
  float offset = 100.f;
  switch(direction)
  {
  case 'N':
    return sf::Vector2f(result.x,result.y+offset);
  case 'E':
    return sf::Vector2f(result.x-offset,result.y);
  case 'S':
    return sf::Vector2f(result.x,result.y-offset);
  case 'W':
    return sf::Vector2f(result.x+offset,result.y);
  default:
    return result;
  }
}

int Door::getToID() {return toID;}

