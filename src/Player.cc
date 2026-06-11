#include "Player.h"
#include "Entity.h"
#include "MeleeEnemy.h"
#include "ResourceManager.h"
#include "Weapon.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <iostream>
#include "Projectile.h"
#include "Heart.h"


Player::Player(sf::Vector2f pos)
    : Entity{pos, ResourceManager::getSpriteWithName(Tex::Player),
             5, 4, new Weapon{pos, ResourceManager::getSpriteWithName(Tex::Watergun), 2, 5 , false}}, clock{}
{}

void Player::collide(Object* other) 
{
    if(dynamic_cast<Heart*>(other) != nullptr)
    {
        Heart* heart = dynamic_cast<Heart*>(other);
        if(!heart->isPickedUp)
        {
            heart->isPickedUp = true;
            // no ouchie
            change_hp(1);
            return;
        }
    }
    else if(dynamic_cast<Weapon*>(other) != nullptr)
    {
        weapon->isPickedUp = true;
        weapon = {dynamic_cast<Weapon*>(other)};
        
        //move to where player is 
        //weapon->moveToPos(pos);
        return;
    }
    else if(dynamic_cast<Entity*>(other) != nullptr)
    {
        goto_old_pos();

        //cooldown for taking damage
        if(clock.getElapsedTime().asSeconds() > 1.f/static_cast<float>(2))
        {
            clock.restart();

            //ouchie!
            change_hp(-1);
        }
    }
    else if (dynamic_cast<Projectile*>(other) != nullptr
             && dynamic_cast<Projectile*>(other)->isEnemyFired
             && std::any_of(projectiles.begin(), projectiles.end(), [other](Projectile* p)
                 {
                     return other->get_id() == p->get_id();
                 }))
             
    {
        change_hp(-1);

    }

    Entity::collide(other);
}

void Player::handle_input()
{
    if(isPushed)
    {
        pushback();
        return;
    }


    
    old_pos = pos;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
	pos.x -= 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
	pos.x += 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
	pos.y -= 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
	pos.y += 3;
    }
    sprite.setPosition(pos);
    weapon->get_sprite().setPosition(pos);
    weapon->get_pos() = pos;
}
