#pragma once

#include "Entity.h"
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Player : public Entity
{
public:
    
    //! @brief Constructor, should only be called ONCE during the entire game loop.
    Player(sf::Vector2f pos);
    
    //! @brief empty implementation since movement is handled by handle_input() and the keyboard.
    void move(sf::Vector2f pos) override {};
    
    //! @brief behaviour for collision between certain objects.
    void collide(Object* other) override;
    
    //! @brief handles the keyboard input and resulting movement.
    void handle_input();

private:
    sf::Clock clock; //!< a clock handling the time between damage from collison to ensure only that only 1 HP is taken away per collision.
};
