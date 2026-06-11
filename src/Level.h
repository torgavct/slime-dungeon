#pragma once
#include <map>
#include "Room.h"
#include "Player.h"

class Level{

public:
    //! @brief Constructor for creating a new Level-object
    Level(Player* player);

    ~Level();

    Room* currentRoom; //!< Ptr to the currentRoom that the player is in.
    //! @brief Function for moving to another room.
    //! @param entry - Ptr to the door that the player collided with.
    //! @param id - the id of the room that the player is moving to.
    void GoTo(Door* entry, int id);
private:
    Player* player; //!< ptr to the player, used for getting the position for calculating enemy spawnpoints
  
    std::map<int, Room*> RoomList {}; //!< The list of all rooms inside the level, first is the id of the room and second is a ptr to the Room-object.
  
};
