#include "Level.h"
#include "BossEnemy.h"
#include "Door.h"
#include "MeleeEnemy.h"
#include "Object.h"
#include "RangedEnemy.h"
#include "Room.h"
#include "Weapon.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

Level::Level(Player* player) : player{player}
{
    Room::globalID = 0;
    std::string filepath {"level1.txt"};
    std::ifstream file(filepath);
    std::string line {};
    std::vector<Object*> roomObjs {};
    int roomDoors[4] {};
    bool firstLine {false};
    if(!file.is_open())
        throw std::exception();
    
    while(file >> line)
    {
        char identity{line[0]};
      
        switch(identity)
        {
        case '#':
        {
            continue;
        }
        case '-':
        {
            Room* newRoom {new Room(roomDoors,roomObjs, this)};
            RoomList.emplace(std::pair<int,Room*>(newRoom->getID(),newRoom));
	
            //clear list for next iteration
            roomObjs.clear();
            continue;
        }
        case 'D':
        {
            int index = 0;
            for(int i {0}; i < line.length(); i++)
            {
                if(std::isdigit(line[i]))
                {
                    //convert line[i] to int :o
                    roomDoors[index] = static_cast<int>(line[i]) - 48;
                    index++;
                }
            }
            break;
        }
        case 'O':
        {
            int index = 0;
            for(int i {0}; i < line.length(); ++i)
            {
                if(!std::isdigit(line[i]))
                    continue;
                
                int num =  static_cast<int>(line[i]) - 48;
                // if(index == 3 && num > 0)
                // {
                //     roomObjs.push_back(Weapon::CreateNewFromType(num));
                // }
                
                for(int k{0}; k < num; k++)
                {
                    if(index == 0)
                        roomObjs.push_back(new MeleeEnemy({0,0}));
                    else if(index == 1)
                        roomObjs.push_back(new RangedEnemy({0,0}));
                    else if(index == 2)
                        roomObjs.push_back(new BossEnemy({0,0}));
                    
                }
                index++;
            }
            break;
        }
        }
    }
    // first room player spawns in
    currentRoom = RoomList[1];
    currentRoom->SpawnObjects(player->get_pos());
}

Level::~Level()
{
  for(auto x : RoomList)
  {
    delete x.second;
  }
}

void Level::GoTo(Door *door, int id) {
  //check here if all objects are dead.

  // if(!currentRoom->getObjects().empty())
  //   return;
  
  Room *newRoom = RoomList[id];
  if (newRoom == nullptr)
  {
    throw std::invalid_argument("no room with id: "
				+ std::to_string(id)
				+ " was found.");
  }
  
  //id of the room which we came from
  int oldID = currentRoom->getID();
  
  Door* newDoor{};  
  for (auto x : newRoom->getDoors())
  {
    if(x->getToID() == oldID)
      newDoor = x;
  }
  

  if(newDoor == nullptr)
  {
    std::cout << "null door" << std::endl;
    return;
  }
  currentRoom = newRoom;
  player->moveToPos(newDoor->getPlayerSpawnPos());

  auto proj = &player->get_projectiles();
  for(auto p : *proj)
  {
      delete p;
  }
  proj->erase(proj->begin(), proj->end());
  
  currentRoom->SpawnObjects(player->get_pos());
}
