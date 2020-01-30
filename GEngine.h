#ifndef _GAME_ENGINE_
#define _GAME_ENGINE_

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GState.h"

class GAME{
  private:
	sf::RenderWindow& G_window;
	std::unique_ptr<STATE> current_state;
  public:
	int G_input;
	sf::Time G_time;
	GAME( sf::RenderWindow& window );
	void Update( int in, sf::Time time );
	void Draw();
	void ChangeState( std::unique_ptr<STATE> & );
};

#endif
