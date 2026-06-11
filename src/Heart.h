#pragma once
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Heart : public Object {

    public:
    //! @brief constructor for Hearth
    //! @param pos - Heart position
        Heart(sf::Vector2f pos);
    //! @brief destructor
        ~Heart();
        void collide(Object* other) override;
        bool isPickedUp; //!< if the heart is picked up
    private:
        const int Health = 1;
        
};
