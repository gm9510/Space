#include "GEngine.h"
#include "GState.h"

GAME::GAME( sf::RenderWindow& window ) : G_window(window) {
	
	title_font.loadFromFile("Fonts/Star Trek Enterprise Future.ttf");
	txt_font.loadFromFile("Fonts/data-unifon.ttf");
	
	std::unique_ptr<STATE> init_state( new MenuSTATE(G_window, title_font, txt_font) );
	current_state = std::move( init_state );
 }

void GAME::Update( int in, int loop ,sf::Time time ){
	G_time = time;
	G_input = in;
	Gloop = loop;
	current_state->Update( this );
}

void GAME::Draw(){
	current_state->Draw( this );
}

void GAME::ChangeState( std::unique_ptr<STATE> & state ){
	current_state = std::move( state );
}
