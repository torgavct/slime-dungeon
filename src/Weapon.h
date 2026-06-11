#pragma once
#include "Object.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

class Projectile;

class Weapon : public Object
{
public:
    //! @
    Weapon();
    //! @brief creates a new weapon, ex: type 2 or 3.
    //! @param creates the weapon type
    static Weapon* CreateNewFromType(int type);
    //! @brief weapon stats and position
    //! @param Pos- takes in the postion where it's spawned, sprite - texture of weapon,    frequency- spawned weapons frequency, speed - speed of the weapon, isEnemy - statement for if its a ranged or boss type 
    Weapon(sf::Vector2f pos, sf::Sprite sprite, int frequency, float speed, bool isEnemyGun);
    //! @brief logic for projectiles collide
    void collide(Object* other);
    //! @brief shoot the projectile from a position to a angle
    //! @param pos - position, angle - angle
    virtual Projectile* use(sf::Vector2f pos, float angle);
    sf::Clock clock; //!< measures how long since the last projectile was shot
    bool isPickedUp; //!< if weapon is picked up
protected:
    bool isEnemyGun; //!< if the weapon is from ranged or boss

    int frequency; //!< shooting frequency for the current weapon 
    float speed; //!< projectile speed
private:
};
