#include "ResourceManager.h"
#include "States.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

MenuState::MenuState(sf::RenderWindow* window)
    : State{window}, font{}, background{ResourceManager::getSpriteWithName(Tex::Background)}, start{}, quit{}
{
    if (!font.loadFromFile("resources/bitmgothic.ttf"))
    {
	throw new std::runtime_error("Font could not be loaded");
    }
        
    start.setTexture({});
    start.setColor({0,0,0,0});
    start.setTextureRect({0,0,300,100});
    start.setPosition({365,300});
    
    quit.setTexture({});
    quit.setColor({0,0,0,0});
    quit.setTextureRect({0,0,300,100});
    quit.setPosition({365,450});
}

State* MenuState::handle_input() 
{
        sf::Event event;
    
    while (window->pollEvent(event))
    {
	// "close requested" event: we close the window
	if (event.type == sf::Event::Closed)
	    window->close();

	if (event.type == sf::Event::MouseButtonPressed)
	{
	    sf::Rect start_rec {start.getGlobalBounds()};
	    sf::Rect quit_rec {quit.getGlobalBounds()};
	    sf::Vector2f m_pos {sf::Mouse::getPosition(*window)};
	    if(start_rec.contains(m_pos.x, m_pos.y))
	    {
		return new GameState{window};
	    }
	    if(quit_rec.contains(m_pos.x, m_pos.y))
	    {
		window->close();
	    }
	}
    }
    return nullptr;
}

void MenuState::update() 
{

}

void MenuState::render() 
{
    window->clear(sf::Color::Black);

    window->draw(background);
    window->draw(start);
    window->draw(quit);
    
    
    sf::Text title;
    title.setFont(font);
    title.setString("Slime Dungeon");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);

    float text_width {title.getGlobalBounds().width};
    
    title.setPosition({384-text_width/4-10,10});

    window->draw(title);

    
    sf::Text menu;
    menu.setFont(font);
    menu.setCharacterSize(50);
    menu.setFillColor(sf::Color::Red);

    menu.setString("Start");
    menu.setPosition({455,315});
    window->draw(menu);

    menu.setString("Exit");
    menu.setPosition({468,465});
    window->draw(menu);

    window->display();
}
