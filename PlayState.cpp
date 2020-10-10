#include "GState.h"
#include "GEngine.h"
#include "SOLID.h"

//**********************************************************
//               Play State Class Definition.
//**********************************************************

PlaySTATE::PlaySTATE( sf::RenderWindow& window) : My_window(window) { 
	//Bullet Initialized
	
	Bullets.list.push_back( SOLID(3) );
	Bullets.list.at(0).putPOS(-300,-300);
	
	
	//Player initilized
	Player.resize(4);
	Player.setPrimitiveType(sf::TriangleStrip);
	
	Player[0].position = sf::Vector2f(10.f,590.f);
	Player[1].position = sf::Vector2f(10.f,540.f);
	Player[2].position = sf::Vector2f(60.f,590.f);
	Player[3].position = sf::Vector2f(60.f,540.f);
	for(int i=0; i<4; i++)	Player[i].color = sf::Color::Green;
	
	Player.setPhysics();
	
	Enemies.list.resize( 9 , SOLID( 8 ) );
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		int index = it - Enemies.list.begin();
		it->putPOS(30.f + index*40.f ,20.f);
		it->Velocity = sf::Vector2f(0.0075,0.f);
	}
        leftSideEnemy = Enemies.list.begin();
	rightSideEnemy = Enemies.list.end();
}

void PlaySTATE::Update( GAME* game ){
//........................................
//         Change STATE
//........................................

	if(game->G_input == 10 ){
		std::unique_ptr<STATE> Menu( new MenuSTATE( My_window, game->title_font, game->txt_font ) );
		this->ChangeState(game, Menu);
	}
//........................................
//         Player Movement
//........................................

	Player.KeyInputs( game->G_input, Bullets.list.at(0), 0.01*game->G_time.asMicroseconds() );
	if(!InBoundary( Player )){
		Player.resetPOS();
	}

	if(!InBoundary( Bullets.list.at(0) )){
		Bullets.list.at(0).putPOS( -300, -300 );
		Bullets.list.at(0).Velocity = sf::Vector2f( 0.f,0.f );
		Bullets.list.at(0).draw_me = false;
	}
	else{
		Bullets.list.at(0).draw_me = true;
		Bullets.list.at(0).Velocity = sf::Vector2f( 0.f,-0.025 );
		Bullets.list.at(0).Inertia( game->G_time.asMicroseconds() );
	}
//........................................
//         Enemy Movement
//........................................
	this->Movement( (double)game->G_time.asMicroseconds() );
//........................................
//         Collisions
//........................................
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		if(it->getBounds().intersects(Bullets.list.at(0).getBounds())){
			it->putPOS( 0, -100 );
			Bullets.list.at(0).putPOS( -100, -100 );
			it->draw_me = false;
			Bullets.list.at(0).draw_me = false;
		}
		else{
			//std::cout<< "do not intersects"<<  std::endl;
		}
	}
}

void PlaySTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	if(Bullets.list.at(0).draw_me) My_window.draw(Bullets.list.at(0));
	My_window.draw( Enemies );
	My_window.draw(Player);
	My_window.draw( Bullets );
	My_window.display();
}

bool PlaySTATE::InBoundary( SOLID& solid_obj ){

	for(int i=0; i<solid_obj.getVertexCount(); i++){
		if( solid_obj[i].position.x < 0 || solid_obj[i].position.x > 600 )
			return 0;
		else if( solid_obj[i].position.y < 0 || solid_obj[i].position.y > 600 ) 
			return 0;
	}
return 1;
}

void PlaySTATE::Movement( double dt ){
	if( leftSideEnemy == rightSideEnemy ){
		if(leftSideEnemy->draw_me){
			if(!InBoundary( *leftSideEnemy )){
				leftSideEnemy->Velocity = -leftSideEnemy->Velocity;
				leftSideEnemy->resetPOS();
			}
			else leftSideEnemy->Inertia( dt );
		}
		else{
		// End Game
		}
	}
	else{
		while( !leftSideEnemy->draw_me ){
			if(leftSideEnemy == rightSideEnemy) break;
			else leftSideEnemy++;
		}
		while( !rightSideEnemy->draw_me ){
			if(rightSideEnemy == leftSideEnemy) break;
			else rightSideEnemy--;
		}
	
		if(!InBoundary( *leftSideEnemy ) || !InBoundary( *rightSideEnemy )){
			for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
				it->Velocity = -it->Velocity;
				it->resetPOS();
			}
		}
		else{
			for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it )
				it->Inertia( dt );
		}
	}
}
