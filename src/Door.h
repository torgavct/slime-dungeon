#pragma once
#include "Object.h"
#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "ResourceManager.h"

class Door : public Object
{
public:
    
    //! @brief Constructor for creating a new Door-object
    //! @param pos - the position of this door.
    //! @param toId - the id of the room where this door leads to.
    //! @param dir - the direction (NESW) of the door.
    //! @param lvl - the level where this door resides in.
    Door(sf::Vector2f pos, int toID, char dir, Level* lvl) :
        Object(pos, ResourceManager::getSpriteWithName(Tex::Door)), toID{toID}, direction{dir}, currentLevel(lvl)
        {
            setPosition(pos);
            sprite.setPosition(pos);
        }

    //! @brief logic for handling collision with player.
    void collide(Object* other) override;
  
    //! @brief returns the position to move the player when entering this room.
    sf::Vector2f getPlayerSpawnPos();
    //! @brief returns the id of the room of which this room leads to.
    int getToID();
  
private:
    char direction; //!< the direction of the door.
    int toID; //!< the id of the room whre this room leads to.
    Level* currentLevel; //!< ptr to the level of which this door resides in.
};
