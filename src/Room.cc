#include "Room.h"
#include "Entity.h"
#include "Player.h"
#include "Utils.h"
#include "BossEnemy.h"
#include "ResourceManager.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <utility>
#include "Door.h"
#include "Level.h"
#include "Heart.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::Sprite floorTile {ResourceManager::getSpriteWithName(Tex::Floor)};
  sf::Sprite wallTile {ResourceManager::getSpriteWithName(Tex::Wall)};
  sf::Sprite doorTile {ResourceManager::getSpriteWithName(Tex::Door)};

  sf::Vector2u size {ResourceManager::getSize("room")};
	
  int width {static_cast<int>(target.getSize().x/size.x)};
  int height {static_cast<int>(target.getSize().y/size.y)};

  int halfwidth = {int(width/2)};
  int halfheight = {int(height/2)};
  
  for(int h = 0; h < height; h++) 
  {
    for(int w = 0; w < width; w++)
    {
      sf::Sprite newTile {floorTile};
	
      if(h == 0 || w == 0 || w == width-1 || h == height-1)
	newTile = wallTile; 
	
      //draw and assign door objects 
      if(doors[0] != 0 && h == 0 && w == halfwidth)
      {
	target.draw(*doorObjs.at(0), states);
      }
      else if (doors[1] != 0 && w == width-1 && h == halfheight)
      {
	target.draw(*doorObjs.at(1), states);
      }
      else if (doors[2] != 0 && w == halfwidth && h == height-1)
      {
	target.draw(*doorObjs.at(2), states);
      }
      else if (doors[3] != 0 && w == 0 && h == halfheight)
      {
	target.draw(*doorObjs.at(3), states);
      }
      else
      {
	newTile.setPosition(size.x*w,size.y*h);
	target.draw(newTile, states);
      }
    }
  }
}


Room::Room(int doorsin[4], std::vector<Object*> objs, Level* lvl)
    : doors{*doorsin},
      objects{objs},
      id{++globalID},
      doorObjs{}
{
  std::copy(doorsin, doorsin+4, doors);
  
  char directions[4] {'N','E','S','W'};

  //hårdkodade för att fönstret är samma hela tiden
  //om inte fullscreen option finns...
   doorObjs.push_back(new Door{
       sf::Vector2f(512,0),
	  doors[0],
	  directions[0], lvl});

    doorObjs.push_back(new Door{
	sf::Vector2f(960,384),
	  doors[1],
	  directions[1], lvl});

     doorObjs.push_back(new Door{
	 sf::Vector2f(512,704),
	  doors[2],
	  directions[2], lvl});

      doorObjs.push_back(new Door{
	  sf::Vector2f(0,384),
	  doors[3],
	  directions[3], lvl});
}

Room::~Room()
{
  for(auto o : objects)
  {
    delete o;
  }

  for(auto d : doorObjs)
  {
    delete d;
  }
}

void Room::ValidateObjects()
{
    std::vector<Object*> toRemove;
    
    objects.erase(std::remove_if(objects.begin(), objects.end(), [this, &toRemove](Object* obj)
    {
        Entity* ent = dynamic_cast<Entity*>(obj);

        if (ent != nullptr && ent->isDead)
        {
            toRemove.push_back(ent); 
            return true;           
        }
        // else if (dynamic_cast<Weapon*>(obj) != nullptr
        //     && dynamic_cast<Weapon*>(obj)->isPickedUp)
        // {
        //     toRemove.push_back(obj);
        //     return true;
        // }

        // Behåll hjärtan
        if (dynamic_cast<Heart*>(obj)) {
	    bool pickedUp{dynamic_cast<Heart*>(obj)->isPickedUp};
	    if(pickedUp) delete obj;
            return pickedUp;
        }

        return false;

    }), objects.end());

    for (Object* obj : toRemove) {
        Entity* ent = dynamic_cast<Entity*>(obj);
        if (ent) {
	    if(dynamic_cast<BossEnemy*>(ent) != nullptr)
	    {
		win = true;
		continue;
	    }

	    srand(time(NULL));
	    float num {static_cast<float>(rand()) / static_cast<float>(RAND_MAX)};
	    if(num < 0.4)
	    {
		sf::Vector2f spawnPos = ent->get_pos();
		Object* heart = new Heart(spawnPos);
		objects.push_back(heart); // Lägg till hjärtat i vektorn
	    }
            delete ent;               // Radera fienden
        }
    }

}






float Room::generateRandomFloat(float min, float max)
{
  return min
    + static_cast <float> (rand())
    /( static_cast <float> (static_cast<float>(RAND_MAX)/(max-min)));
}


sf::Vector2f Room::GetRandomPos(sf::Vector2f playerpos)
{
  float min_x {65.f};
  float max_x {836.f};

  float min_y {65.f};
  float max_y {644.f};

  float rand_x {generateRandomFloat(min_x, max_x)};
  float rand_y {generateRandomFloat(min_y, max_y)};

  if(rand_x == 0 || rand_y == 0)
  {
    rand_x = generateRandomFloat(min_x, max_x);
    rand_y = generateRandomFloat(min_y, max_y);
  }
  
  return {rand_x, rand_y};
}


void Room::SpawnObjects(sf::Vector2f playerpos)
{
  //the min distance from enemy to player
  float safeDist {175.f};
  
  for (Object* obj : objects)
  {
      
    if(dynamic_cast<Heart*>(obj) != nullptr) continue;
    
    if(dynamic_cast<BossEnemy*>(obj) != nullptr)
    {
      //Boss should spawn in middle (ish)
      obj->moveToPos({445, 154});
      continue;
    }
    
    sf::Vector2f randpos {GetRandomPos(playerpos)};
    obj->moveToPos(randpos);


    while (Utils::GetDistance(playerpos, randpos) < safeDist
	   || randpos == sf::Vector2f(0,0)
	   ||  std::any_of(objects.begin(), objects.end(), [obj](Object* coll)
	   {
	     return obj->get_id() != coll->get_id()
	       && obj->GetGlobalBounds().intersects(coll->GetGlobalBounds());
	   }))
    {
      randpos = GetRandomPos(playerpos);
      obj->moveToPos(randpos);
    }
  }
}



