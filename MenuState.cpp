#include "GState.h"
#include "GEngine.h"
#include "UIText.h"

//**********************************************************
//               Menu State Class Definition.
//**********************************************************

MenuSTATE::MenuSTATE( sf::RenderWindow& window, sf::Font& A_font, sf::Font& B_font ) : My_window(window), title_font(A_font), txt_font(B_font) { 
//--Tri initilized----------------------------------------------------

//--------------------------------------------------------------------
//				-->Text initialization
//--------------------------------------------------------------------
	UI.txt_list.push_back( sf::Text("Space Bullet Hell", title_font, 80) );
	UI.txt_list.at(0).setPosition( 40, 0 );
	
	UI.txt_list.push_back( sf::Text("by Evil Tomato", title_font, 40) );
	UI.txt_list.at(1).setPosition( 300, 80 );

	UI.txt_list.push_back( sf::Text("Controls: \n 1. arrows to move. \n 2. space bar to shoot. \n 3. q back to menu", txt_font, 20) );
	UI.txt_list.at(2).setPosition( 200, 200 );

	Start_Button.setString("START");
	Start_Button.setFont( title_font );
	Start_Button.setCharacterSize( 60 );
	Start_Button.setPosition( 220, 300 );
	Start_Button.setButton( 10 );
}

void MenuSTATE::Update( GAME* game ){
	sf::Vector2i mousePOS;
	sf::FloatRect Start_Bounds = Start_Button.getBounds();
	if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
		mousePOS = sf::Mouse::getPosition(My_window);
		if( Start_Bounds.contains( mousePOS.x, mousePOS.y ) ){
			std::unique_ptr<STATE> Play( new PlaySTATE( My_window) );
			this->ChangeState(game, Play);
		}
	}
}

void MenuSTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	My_window.draw( UI );
	My_window.draw( Start_Button );
	My_window.display();
}
