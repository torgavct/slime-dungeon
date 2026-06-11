#include "Entity.h"
#include "Object.h"
#include "Weapon.h"
#include "Projectile.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include "Utils.h"
#include <iostream>
#include "SFML/Graphics/Texture.hpp"

Entity::Entity(sf::Vector2f pos, sf::Sprite sprite, int max_health, int speed, Weapon* weapon)
    : Object{pos, sprite}, hp{max_health}, max_health{max_health}, speed{speed}, weapon{weapon}, projectiles{}, old_pos{}, isDead{false}, isPushed{false}, time{0}, targetPos{0,0}
{
    
}

Entity::~Entity()
{
  for (auto p : projectiles)
    delete p;

  projectiles.clear();

  if(weapon != nullptr)
    delete weapon;
}

int Entity::get_hp()
{
    return hp;
}

void Entity::change_hp(int diff)
{
    hp += diff;
    if(hp > max_health)
        hp = max_health;

    else if(hp <= 0)
    {
        hp = 0;
        isDead = true;
    }
}

void Entity::shoot(float angle)
{
    if(weapon == nullptr)
        return;
    
    Projectile* p {weapon->use(pos, angle)};

    if(p != nullptr)
        projectiles.push_back(p);
}    
    
std::vector<Projectile*>& Entity::get_projectiles()
{
    return projectiles;
}

void Entity::remove_projectile(Projectile* p)
{
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
				   [&p](Projectile* pr)
				       {
					   return p->get_id() == pr->get_id();
				       }), projectiles.end());
    delete p;
}

void Entity::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    for(Projectile* p : projectiles)
    {
        target.draw(p->sprite, states);
    }
}

void Entity::goto_old_pos()
{
    if(isPushed)
        return;
    
    pos = old_pos;
    sprite.setPosition(old_pos);
}

void Entity::collide(Object *other)
{
    if (dynamic_cast<Entity*>(other) != nullptr
        && dynamic_cast<Projectile*>(other) == nullptr)
    {
        if(!isPushed)
        {
            //collision with fellow enemy
            //direction should be away from "other"
            sf::Vector2f dir {Utils::GetNormalizedDirection(pos, other->get_pos())};
            isPushed = true;
            
            //force decides how much forceful the push is
            //in other cooler games this would be decided by mass of "other"
            float force {20.f};
            targetPos = {pos.x + (dir.x * float(speed) * force), pos.y + (dir.y * float(speed) * force)};
            }
    }
}

void Entity::pushback()
{
    //change this to make the push faster
    float duration = 0.5f;
    if(time < duration)
    {
        sf::Vector2f newPos {Utils::VectorLerp(pos, targetPos, time)};

	int sw = sprite.getTexture()->getSize().x*2;
	int sh = sprite.getTexture()->getSize().y*2;
	float x = get_pos().x;
	float y = get_pos().y;
	int w = 1024;
	int h = 768;
	
	if(x < 60 || x > w-sw-60 || y < 60 || y > h-sh-60)
	{
	    goto_old_pos();
	    isPushed = false;
	    time = 0;
	    targetPos = {0,0};
	    return;
	}
	
	old_pos = pos;
        moveToPos(newPos);
        time += Utils::GetDeltaTime();
    }
    else
    {
        isPushed = false;
        time = 0;
        targetPos = {0,0};
    }
}
