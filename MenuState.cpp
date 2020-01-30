#include "GState.h"
#include "GEngine.h"

//**********************************************************
//               Menu State Class Definition.
//**********************************************************

MenuSTATE::MenuSTATE( sf::RenderWindow& window, sf::Font& G_font ) : My_window(window), font(G_font){ 
//--Tri initilized----------------------------------------------------
	Tri.resize(4);
	Tri.setPrimitiveType(sf::TriangleStrip);
	
	Tri[0].position = sf::Vector2f(275.f,325.f);
	Tri[1].position = sf::Vector2f(275.f,275.f);
	Tri[2].position = sf::Vector2f(325.f,325.f);
	Tri[3].position = sf::Vector2f(325.f,275.f);
	for(int i=0; i<4; i++)	Tri[i].color = sf::Color::Red;

//--------------------------------------------------------------------
//				-->Text initialization
//--------------------------------------------------------------------
	Game_title.setString("Space Bullet Hell");
	Game_title.setFont( font );
	Game_title.setCharacterSize( 80 );
	Game_title.setPosition( 40, 0 );
}

void MenuSTATE::Update( GAME* game ){
	if(game->G_input == 10 ){
		std::unique_ptr<STATE> Play( new PlaySTATE( My_window ) );
		this->ChangeState(game, Play);
	}
}

void MenuSTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	My_window.draw(Tri);
	My_window.draw( Game_title );
	My_window.display();
}