#include "SOLID.h"

PLAYER::PLAYER(){
}

void PLAYER::KeyInputs( int input, SOLID& bullet, double P_v ){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		this->MovePOS( -P_v, 0 );
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
	    // move right...
		this->MovePOS( P_v, 0 );
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
	    // move down...
		this->MovePOS( 0, P_v );
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
	    // move up...
		this->MovePOS( 0, -P_v );
	}

	switch( input ){
		case 4: //SPACE
			if( bullet.Masscenter.position.x < 0 || bullet.Masscenter.position.y < 0 )
				bullet.putPOS( this->Masscenter.position );
		break;
	}
}
