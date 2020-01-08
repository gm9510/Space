#include "header.h"

PLAYER::PLAYER(){
}

void PLAYER::KeyInputs( int input, SOLID& bullet, double P_v ){

	switch( input ){
		case 0: //UP
			this->MovePOS( 0, -P_v );
		break;
		case 1: //DOWN
			this->MovePOS( 0, P_v );
		break;
		case 2: //LEFT
			this->MovePOS( -P_v, 0 );
		break;
		case 3: //RIGHT
			this->MovePOS( P_v, 0 );
		break;
		case 4: //SPACE
			if( bullet.Masscenter.position.x < 0 || bullet.Masscenter.position.y < 0 )
				bullet.putPOS( this->Masscenter.position );
		break;
	}
}