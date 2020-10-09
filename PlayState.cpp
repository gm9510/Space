#include "GState.h"
#include "GEngine.h"
#include "SOLID.h"

//**********************************************************
//               Play State Class Definition.
//**********************************************************

PlaySTATE::PlaySTATE( sf::RenderWindow& window) : My_window(window), White(3) { 
	//Bullet Initialized
	Bullet.resize(3);
	Bullet.setPrimitiveType(sf::TriangleStrip);

	Bullet[0].position = sf::Vector2f( 0.f,0.f );
	Bullet[1].position = sf::Vector2f( 10.f,0.f );
	Bullet[2].position = sf::Vector2f( 5.f,-30.f );
	
	Bullet.setPhysics();
	Bullet.Velocity = sf::Vector2f( 0.f,0.f );
	
	White.putPOS(300,300);
	std::cout<<White.getVertexCount()<<std::endl;
	//Player initilized
	Player.resize(4);
	Player.setPrimitiveType(sf::TriangleStrip);
	
	Player[0].position = sf::Vector2f(10.f,590.f);
	Player[1].position = sf::Vector2f(10.f,540.f);
	Player[2].position = sf::Vector2f(60.f,590.f);
	Player[3].position = sf::Vector2f(60.f,540.f);
	for(int i=0; i<4; i++)	Player[i].color = sf::Color::Green;
	
	Player.setPhysics();
	
	Enemies.list.resize( 3 , SOLID( 8 ) );
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		int index = it - Enemies.list.begin();
		it->putPOS(100.f + index*50.f ,20.f + index*40.f);
		it->Velocity = sf::Vector2f(0.0075,0.f);
	}
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

	Player.KeyInputs( game->G_input, White, 0.01*game->G_time.asMicroseconds() );
	if(!InBoundary( Player )){
		Player.resetPOS();
	}

	if(!InBoundary( Bullet )){
		Bullet.putPOS( -300, -300 );
		Bullet.Velocity = sf::Vector2f( 0.f,0.f );
		Bullet.draw_me = false;
	}
	else{
		Bullet.draw_me = true;
		Bullet.Velocity = sf::Vector2f( 0.f,-0.025 );
		Bullet.Inertia( game->G_time.asMicroseconds() );
	}
//........................................
//         Enemy Movement
//........................................

	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		if(it->draw_me){
			if(!InBoundary( *it )){
				it->Velocity = -it->Velocity;
				it->resetPOS();
			}
				else{
				it->Inertia( game->G_time.asMicroseconds() );
			}
		}
	}
//........................................
//         Collisions
//........................................
	for( auto it = Enemies.list.begin(); it != Enemies.list.end(); ++it ){
		if(it->getBounds().intersects(Bullet.getBounds())){
			it->putPOS( 0, -100 );
			Bullet.putPOS( -100, -100 );
			it->draw_me = false;
			Bullet.draw_me = false;
		}
		else{
			//std::cout<< "do not intersects"<<  std::endl;
		}
	}
}

void PlaySTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	if(Bullet.draw_me) My_window.draw(Bullet);
	My_window.draw( Enemies );
	My_window.draw(Player);
	My_window.draw( White );
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
