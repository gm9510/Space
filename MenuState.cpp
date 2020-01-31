#include "GState.h"
#include "GEngine.h"
#include "UIText.h"

//**********************************************************
//               Menu State Class Definition.
//**********************************************************

MenuSTATE::MenuSTATE( sf::RenderWindow& window, sf::Font& G_font ) : My_window(window), font(G_font){ 
//--Tri initilized----------------------------------------------------


//--------------------------------------------------------------------
//				-->Text initialization
//--------------------------------------------------------------------
	Game_title.setString("Space Bullet Hell");
	Game_title.setFont( font );
	Game_title.setCharacterSize( 80 );
	Game_title.setPosition( 40, 0 );

	Start_Button.setString("START");
	Start_Button.setFont( font );
	Start_Button.setCharacterSize( 60 );
	Start_Button.setPosition( 265, 265 );
	Start_Button.setButton( 10 );
}

void MenuSTATE::Update( GAME* game ){
	sf::Vector2i mousePOS;
	sf::FloatRect Start_Bounds = Start_Button.getBounds();
	if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
		mousePOS = sf::Mouse::getPosition(My_window);
		if( Start_Bounds.contains( mousePOS.x, mousePOS.y ) ){
			std::unique_ptr<STATE> Play( new PlaySTATE( My_window ) );
			this->ChangeState(game, Play);
		}
	}
}

void MenuSTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	My_window.draw( Game_title );
	My_window.draw( Start_Button );
	My_window.display();
}
