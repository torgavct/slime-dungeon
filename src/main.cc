#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "States.h"


int main()
{
    sf::RenderWindow window{sf::VideoMode (1024 , 768) , "TDP005", sf::Style::Titlebar | sf::Style::Close};
    window.setFramerateLimit(60);
    ResourceManager::LoadAssets();
    State* state {new MenuState{&window}};
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
	State* nextState{state->handle_input()};
	if(nextState != nullptr)
	{
	    if(dynamic_cast<PauseState*>(nextState) == nullptr)
		delete state;
	    state = nextState;
	    continue;
	}
	state->update();
	state->render();
    }

    delete state;
    
    return 0;
  
}



