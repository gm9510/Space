#include "GState.h"
#include "GEngine.h"
#include "SOLID.h"

//**********************************************************
//               Play State Class Definition.
//**********************************************************

PlaySTATE::PlaySTATE( sf::RenderWindow& window ) : My_window(window){ 
	//Bullet Initialized
	Bullet.resize(3);
	Bullet.setPrimitiveType(sf::TriangleStrip);

	Bullet[0].position = sf::Vector2f( 0.f,0.f );
	Bullet[1].position = sf::Vector2f( 10.f,0.f );
	Bullet[2].position = sf::Vector2f( 5.f,-30.f );
	
	Bullet.setPhysics();
	Bullet.Velocity = sf::Vector2f( 0.f,0.f );
	Bullet_draw = true;

	//Player initilized
	Player.resize(4);
	Player.setPrimitiveType(sf::TriangleStrip);
	
	Player[0].position = sf::Vector2f(10.f,590.f);
	Player[1].position = sf::Vector2f(10.f,540.f);
	Player[2].position = sf::Vector2f(60.f,590.f);
	Player[3].position = sf::Vector2f(60.f,540.f);
	for(int i=0; i<4; i++)	Player[i].color = sf::Color::Green;
	
	Player.setPhysics();

	//Enemy initialized
	Enemy.resize(4);
	Enemy.setPrimitiveType(sf::TriangleStrip);
	
	Enemy[0].position = sf::Vector2f(10.f,10.f);
	Enemy[1].position = sf::Vector2f(10.f,60.f);
	Enemy[2].position = sf::Vector2f(60.f,60.f);
	Enemy[3].position = sf::Vector2f(60.f,10.f);

	for(int i=0; i<4; i++)	Enemy[i].color = sf::Color::Red;
	
	Enemy.Velocity = sf::Vector2f( 0.01,0.f );
	Enemy.setPhysics();
	Enemy_draw = true;
}

void PlaySTATE::Update( GAME* game ){
//........................................
//         Change STATE
//........................................
	if(!Enemy_draw) game->G_input=10;

	if(game->G_input == 10 ){
		std::unique_ptr<STATE> Menu( new MenuSTATE( My_window, game->title_font, game->txt_font ) );
		this->ChangeState(game, Menu);
	}
//........................................
//         Player Movement
//........................................

	std::cout<<"time: "<<game->G_time.asMicroseconds()<<std::endl;	
	Player.KeyInputs( game->G_input, Bullet, 0.01*game->G_time.asMicroseconds() );
	if(!InBoundary( Player )){
		Player.resetPOS();
	}

	if(!InBoundary( Bullet )){
		Bullet.putPOS( -300, -300 );
		Bullet.Velocity = sf::Vector2f( 0.f,0.f );
		Bullet_draw = false;
	}
	else{
		Bullet_draw = true;
		Bullet.Velocity = sf::Vector2f( 0.f,-0.025 );
		Bullet.Inertia( game->G_time.asMicroseconds() );
	}
//........................................
//         Enemy Movement
//........................................
	if(Enemy_draw){
		if(!InBoundary( Enemy )){
			Enemy.Velocity = -Enemy.Velocity;
			Enemy.resetPOS();
		}
			else{
			Enemy.Inertia( game->G_time.asMicroseconds() );
		}
	}
//........................................
//         Collisions
//........................................
	
	if(Enemy.getBounds().intersects(Bullet.getBounds())){
		std::cout<< "intersects"<<  std::endl;
		Enemy.putPOS( 0, -100 );
		Bullet.putPOS( -100, -100 );
		Enemy_draw = false;
		Bullet_draw = false;
	}
	else{
		//std::cout<< "do not intersects"<<  std::endl;
	}

}

void PlaySTATE::Draw( GAME* game ){
	My_window.clear(sf::Color::Black);
	if(Bullet_draw) My_window.draw(Bullet);
	if(Enemy_draw) My_window.draw(Enemy);
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
