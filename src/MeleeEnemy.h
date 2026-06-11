#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "Weapon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class MeleeEnemy : public Entity
{
public:
    //! @brief the constructor for creating a new melee enemy
    //! @param pos - the initial position of the enemy
    MeleeEnemy(sf::Vector2f pos);
    void collide(Object* other) override;
    void move(sf::Vector2f playerpos) override;
};
