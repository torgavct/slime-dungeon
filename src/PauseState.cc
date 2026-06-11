#include "ResourceManager.h"
#include "States.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdexcept>
#include <SFML/Graphics/Text.hpp>

PauseState::PauseState(GameState* game)
    : State{game->window}, game{game}, font{},
      background{}, start{}, quit{}
{
    if (!font.loadFromFile("resources/bitmgothic.ttf"))
    {
	throw new std::runtime_error("Font could not be loaded");
    }
    
    game->paused = true;
    background.setTexture({});
    background.setTextureRect({0,0,1024,768});
    background.setColor({0,0,0,180});
    
    start.setTexture({});
    start.setTextureRect({0,0,300,100});
    start.setPosition({365,300});
    
    quit.setTexture({});
    quit.setTextureRect({0,0,300,100});
    quit.setPosition({365,450});

    background.setPosition({0,0});
}

State* PauseState::handle_input() 
{
    sf::Event event;
    
    while (window->pollEvent(event))
    {
	// "close requested" event: we close the window
	if (event.type == sf::Event::Closed)
	    window->close();
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
	    game->paused = false;
	    return game;
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
	    sf::Rect start_rec {start.getGlobalBounds()};
	    sf::Rect quit_rec {quit.getGlobalBounds()};
	    sf::Vector2f m_pos {sf::Mouse::getPosition(*window)};
	    if(start_rec.contains(m_pos.x, m_pos.y))
	    {
		game->paused = false;
		return game;
	    }
	    if(quit_rec.contains(m_pos.x, m_pos.y))
	    {
		delete game;
		return new MenuState{window};
	    }
	}
    }
    return nullptr;
}

void PauseState::update() 
{

}

void PauseState::render()
{
    // window->clear(sf::Color::Black);
    game->render();

    window->draw(background);
    window->draw(start);
    window->draw(quit);
    
    
    sf::Text title;
    title.setFont(font);
    title.setString("Paused");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition({365,10});

    window->draw(title);

    
    sf::Text menu;
    menu.setFont(font);
    menu.setCharacterSize(50);
    menu.setFillColor(sf::Color::Black);

    menu.setString("Continue");
    menu.setPosition({425,315});
    window->draw(menu);

    menu.setString("Exit");
    menu.setPosition({468,465});
    window->draw(menu);

    

    window->display();
}
