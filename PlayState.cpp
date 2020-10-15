#include "GState.h"
#include "GEngine.h"
#include "SOLID.h"

//**********************************************************
//               Play State Class Definition.
//**********************************************************

PlaySTATE::PlaySTATE( sf::RenderWindow& window) : My_window(window), Dist(0,8), end_state(false) { 
	//Bullet Initialized
	
	Bullets.list.resize( 9 , SOLID( 3 ) );
	for( auto it = Bullets.list.begin(); it != Bullets.list.end(); ++it ){
		int index = it - Bullets.list.begin();
		it->putPOS(30.f + index*40.f ,-20.f);
		it->Velocity = sf::Vector2f( 0.f,0.8 );
	}
	
	Bullets.list.push_back( SOLID(3) );
	Bullets.list.at(9).putPOS(-300,-300);
	Bullets.list.at(9).Velocity = sf::Vector2f( 0.f,-0.8 );
	
	//Player initilized
	Player.resize(4);
	Player.setPrimitiveType(sf::TriangleStrip);
	
	Player[0].position = sf::Vector2f(10.f,590.f);
	Player[1].position = sf::Vector2f(10.f,540.f);
	Player[2].position = sf::Vector2f(60.f,590.f);
	Player[3].position = sf::Vector2f(60.f,540.f);
	for(int i=0; i<4; i++)	Player[i].color = sf::Color::Green;
	
	Player.setPhysics();
	
	Player.lead = &( Bullets.list.at(9) );
	
	Enemies.list.resize( 9 , SOLID( 8 ) );
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		int index = it - Enemies.list.begin();
		it->putPOS(30.f + index*40.f ,20.f);
		it->Velocity = sf::Vector2f(0.4,0.f);
		it->lead = &( Bullets.list.at(index) );
	}
        leftSideEnemy = Enemies.list.begin();
	rightSideEnemy = Enemies.list.end();
}

void PlaySTATE::Update( GAME* game ){
//........................................
//         Change STATE
//........................................

	if(game->G_input == 10 || end_state ){
//		Player.lead = nullptr;	
		std::unique_ptr<STATE> Menu( new MenuSTATE( My_window, game->title_font, game->txt_font ) );
		this->ChangeState(game, Menu);
	}
//........................................
//         Player Movement
//........................................

	Player.KeyInputs( 0.2*game->G_time.asMilliseconds() );
	if(!InBoundary( Player )){
		Player.resetPOS();
	}
//........................................
//         Random Number Generator
//........................................
	if( game->Gloop == 15 ){
		int rand = Dist(Gen);
		if(Enemies.list.at(rand).draw_me) Enemies.list.at(rand).fire = true;
	}
	
	this->Movement( (double)game->G_time.asMilliseconds() );
//........................................
//         Collisions
//........................................
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		if( Player.lead->draw_me && it->draw_me ){
			if(it->getBounds().intersects(Player.lead->getBounds())){
				it->putPOS( 0, -100 );
				Player.lead->putPOS( -100, -100 );
				it->draw_me = false;
				Player.lead->draw_me = false;
				Player.fire = false;
			}
		}
		if(it->lead->draw_me){
			if(Player.getBounds().intersects(it->lead->getBounds())){
				end_state = true;
			}
		}
	}
}

void PlaySTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	if(Bullets.list.at(0).draw_me) My_window.draw(Bullets.list.at(0));
	My_window.draw( Bullets );
	My_window.draw( Enemies );
	My_window.draw(Player);
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
//........................................
//         Enemy Movement
//........................................
	if( leftSideEnemy == rightSideEnemy ){
		if(leftSideEnemy->draw_me){
			if(!InBoundary( *leftSideEnemy )){
				leftSideEnemy->Velocity = -leftSideEnemy->Velocity;
				leftSideEnemy->resetPOS();
			}
			else leftSideEnemy->Inertia( dt );
		}
		else{
			end_state = true;
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
//........................................
//         Player Bullet Movement
//........................................
	if(Player.fire){
		if( Player.lead->draw_me  ){
			if( InBoundary( *(Player.lead) ) ){
				Player.lead->Inertia( dt );
			}
			else{
				Player.fire = false;
				Player.lead->draw_me = false;
			}
		}
		else{
			Player.lead->putPOS( Player.getPOS() );
			Player.lead->draw_me = true;
		}
	}
	else{
		Player.lead->draw_me = false;
	}
//........................................
//         Enemies Bullet Movement
//........................................
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		
		if(it->fire){
			if( it->lead->draw_me  ){
				if( InBoundary( *(it->lead) ) ){
					it->lead->Inertia( dt );
				}
				else{
					it->fire = false;
					it->lead->draw_me = false;
				}
			}
			else{
				it->lead->putPOS( it->getPOS() );
				it->lead->draw_me = true;
			}
		}
		else{
			it->lead->draw_me = false;
		}
	}

}
