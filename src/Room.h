#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>
#include <SFML/System/Vector2.hpp>
#include "Object.h"
#include "ResourceManager.h"

class Level;
class Door;

class Room : public sf::Drawable
{
public:
    //! @brief Constructor for creating a new room
    //! @param doors - array describing which doors that exists, a non-zero value means a door is on that specific wall.
    //! @param objs - vector of all objects (enemies/loot) that is in the room.
    //! @param lvl - ptr to the level where the room resides.
    Room(int doors[4], std::vector<Object*> objs, Level* lvl);
    ~Room();
    
    inline static int globalID {0}; //!< a static int used for assigning unique ids to rooms.
    
    //! @brief Function for spawning all enemies and loot when the player enters.
    void SpawnObjects(sf::Vector2f playerpos);
    
    //! @brief Function for validating which objects should exist and which that should be deleted/removed.
    void ValidateObjects();

    
    //! @brief returns the id of the room.
    int getID() {return id;}
    //! @brief returns the vector with all the objects currently in the room.
    std::vector<Object*> getObjects() {return objects;}

    //! @brief returns the vector with all Door-objects in the room.
    std::vector<Door*> getDoors() {return doorObjs;}

    bool win {false}; //!< boolean describing if the player has the defeated the boss that may be inside the room.
private:
    std::vector<Object*> objects; //!< a vector containing ptr to all objects currently in the room.
    int id; //!< the unique id of the room, used when moving between rooms.
    int doors[4]; //!< an array containing ids of rooms which connects to this one. Each index describes a wall in the room: 0 = N, 1 = E, 2 = S, 3 = W. A zero means no rooms connect on that wall and therefore, no door should exist there.
    std::vector<Door*> doorObjs; //!< a vector containing all Door-objects.

    
    //! @brief function returning a random position inside the room with a certain distance from the player.
    //! @param playerpos- the position of the player-
    sf::Vector2f GetRandomPos(sf::Vector2f playerpos);
    //! @brief returns a random float between min and max exclusivly.
    //! @param min - the lower bound.
    //! @param max - the upper bound.
    float generateRandomFloat(float min, float max);

    //! @brief implements custom functionality for drawing a room by calling window.draw(Room)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
};
