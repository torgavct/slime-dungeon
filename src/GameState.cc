#include "Heart.h"
#include "States.h"
#include "Object.h"
#include "ResourceManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Projectile.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include "Door.h"
#include <cstdlib>
#include <iostream>

GameState::GameState(sf::RenderWindow* window)
    : State{window}, font{}, paused{false}, player{{445,154}}, currentLevel{&player}
{
    if (!font.loadFromFile("resources/bitmgothic.ttf"))
    {
	throw new std::runtime_error("Font could not be loaded");
    }
}

State* GameState::handle_input()
{
    sf::Event event;
    State* nextState {nullptr};

    if(player.isDead)
	return new MenuState(window);
    
    while (window->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window->close();
	

	if (event.type == sf::Event::KeyPressed)
	{
	    if (event.key.code == sf::Keyboard::Escape)
	    {
		nextState = new PauseState{this};
	    }
	}
    }

    sf::Vector2f mouse_pos {sf::Mouse::getPosition(*window)};
    sf::Vector2f diff { mouse_pos - player.get_pos() };

    static int diff_sign {1};
    int new_sign {(diff.x >= 0) ? 1 : -1};

    if(new_sign != diff_sign)
    {
	sf::Sprite& spr {player.get_sprite()};
	sf::FloatRect size {spr.getTextureRect()};

	diff_sign = new_sign;
	size.width = abs(size.width);
	
	spr.setTextureRect(sf::IntRect(
			       (new_sign == -1) ? size.width : 0, 
			       0,                                 
			       new_sign * size.width,             
			       size.height                        
			       ));
    }
   

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        float angle {std::atan(diff.y/diff.x)};
        if(diff.x < 0) angle = angle - 3.1415;

        player.shoot(angle);
    }

    
    player.handle_input();
    return nextState;
}

void GameState::update()
{
    std::vector<Object*> objs {};
    std::vector<Object*> roomObjs {currentLevel.currentRoom->getObjects()};
    objs.insert(objs.end(), roomObjs.begin(), roomObjs.end());
    objs.push_back(&player);

    for (Object* obj : objs)
    {
        Entity* entity {dynamic_cast<Entity*>(obj)};
        if(entity != nullptr)
        {
            entity->move(player.get_pos());
            for(Projectile* p : entity->get_projectiles())
            {
                p->move();
            }

            //player shoots when he wants to!
            if(dynamic_cast<Player*>(entity) != nullptr)
                continue;
            
            //shooty shoot shoot
            sf::Vector2f diff { player.get_pos() - entity->get_pos() };
            float angle {std::atan(diff.y/diff.x)};
            
            if(diff.x < 0) angle = angle - 3.1415;
	    
            entity->shoot(angle);
            
        }
    }
        
    checkCollisions();
}

void GameState::render()
{
    window->clear(sf::Color::Black);

    Room* currentRoom {currentLevel.currentRoom};
    window->draw(*currentRoom);

    sf::Sprite heart {ResourceManager::getSpriteWithName(Tex::Heart)};
    heart.scale({0.5f,0.5f});
    
    // draw hearts
    for(int i {0}; i < player.get_hp(); i++)
    {
        window->draw(heart);
        heart.move({32,0});
    }

    for (Object* obj : currentRoom->getObjects())
    {
        window->draw(*obj);
    }

    window->draw(player);

    if(currentRoom->win)
    {
        sf::Text title;
        title.setFont(font);
        title.setString("You win!");
        title.setCharacterSize(100);
        title.setFillColor(sf::Color::White);
        title.setPosition({335,40});
	
        window->draw(title);
    }
    

    if(!paused)
        window->display();
}

void GameState::checkCollisions()
{
    std::vector<Object*> allObjects
        {
            currentLevel.currentRoom->getObjects(),
        };
    allObjects.push_back(&player);

    //add room doors
    for (Door* door : currentLevel.currentRoom->getDoors())
    {
        if(dynamic_cast<Object*>(door) != nullptr)
            allObjects.emplace_back(door);
    }

    for (auto a { allObjects.begin () }; a != allObjects.end (); ++a)
    {
        std::vector<Projectile*> proj;
        if(dynamic_cast<Entity*>(*a) != nullptr)
        {
            Entity* e = dynamic_cast<Entity*>(*a);
            proj = e->get_projectiles();

            float x = (*a)->get_pos().x;
            float y = (*a)->get_pos().y;

            int w = window->getSize().x;
            int h = window->getSize().y;

            int sw = e->get_sprite().getTexture()->getSize().x*2;
            int sh = e->get_sprite().getTexture()->getSize().y*2;

            // TODO: variabler för tile storlek
            if(x < 60 || x > w-sw-60 || y < 60 || y > h-sh-60)
                e->goto_old_pos();
        }

        auto a_rec = (*a)->GetGlobalBounds();
        for (auto b {allObjects.begin()}; b != allObjects.end (); ++b)
        {
            if((*a)->get_id() == (*b)->get_id()) continue;
            auto b_rec = (*b)->GetGlobalBounds();
            if(a_rec.intersects(b_rec))
            {
                (*a)->collide(*b);
                (*b)->collide(*a);
            }

            for(Projectile* p : proj)
            {
                auto p_rec = p->GetGlobalBounds();
                if(b_rec.intersects(p_rec))
                {
		    if(dynamic_cast<Heart*>(*b) != nullptr) continue;
                    (*b)->collide(p);
                    p->collide((*b));
                    Entity* e = dynamic_cast<Entity*>(*a);
                    proj.erase(std::remove_if(proj.begin(), proj.end(),
                                              [&p](Projectile* pr)
                                                  {
                                                      return p->get_id() == pr->get_id();
                                                  }), proj.end());
                    e->remove_projectile(p);
                }
                else
                {
                    //kolla inte här
                    float x = p->get_pos().x;
                    float y = p->get_pos().y;

                    int w = window->getSize().x;
                    int h = window->getSize().y;

                    int sw = p->get_sprite().getTexture()->getSize().x*2;
                    int sh = p->get_sprite().getTexture()->getSize().y*2;

                    if(x < 60 || x > w-sw-60 || y < 60 || y > h-sh-60)
                    {
                        Entity* e = dynamic_cast<Entity*>(*a);
                        proj.erase(std::remove_if(proj.begin(), proj.end(),
                                                  [&p](Projectile* pr)
                                                      {
                                                          return p->get_id() == pr->get_id();
                                                      }), proj.end());
                        e->remove_projectile(p);
                    }
                }
            }
        }
    }

    //check for deaths & remove
    currentLevel.currentRoom->ValidateObjects();
  
}
