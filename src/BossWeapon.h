#pragma once
#include "Projectile.h"
#include "Weapon.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>


class BossWeapon : public Weapon
{
public:
    //! @brief constructor for creating a new boss weapon (weapon without cooldown)
    BossWeapon(sf::Vector2f pos);
    
    //! @brief fire a projectile from a position at an angle
    //! @param pos - the postion to fire from
    //! @param angle - the angle to fire at
    Projectile* use(sf::Vector2f pos, float angle) override;
    
    sf::Clock clock; //!< measures the time since the last fired shot
};

