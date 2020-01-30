#include "GEngine.h"
#include "GState.h"

GAME::GAME( sf::RenderWindow& window ) : G_window(window) {
	std::unique_ptr<STATE> init_state( new MenuSTATE(G_window) );
	current_state = std::move( init_state );
 }

void GAME::Update( int in, sf::Time time ){
	G_time = time;
	G_input = in;
	current_state->Update( this );
}

void GAME::Draw(){
	current_state->Draw( this );
}

void GAME::ChangeState( std::unique_ptr<STATE> & state ){
	current_state = std::move( state );
}
