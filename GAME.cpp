#include "header.h"

GAME::GAME( sf::RenderWindow& window ) : G_window(window), SpaceState(window)  {
}

void GAME::Update( int key_input, sf::Time time ){
	SpaceState.Update( key_input, time );
}
void GAME::Draw(){
	SpaceState.Draw();
}
