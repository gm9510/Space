#include "GState.h"
#include "GEngine.h"
//**********************************************************
//               Virtual State Class Definition.
//**********************************************************

STATE::STATE(){}

void STATE::ChangeState( GAME* game, std::unique_ptr<STATE> & state ){
	game->ChangeState( state );
}

