#include "header.h"

GAME::GAME( sf::RenderWindow& window ) : G_window(window) {
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
	
	Enemy.setPhysics();
	Enemy_draw = true;
}

bool GAME::UpDateStatus( int key_input, sf::Time time, double&  vel){
//........................................
//         Player Movement
//........................................
	switch(key_input){
			case 0: //UP
				Player.MovePOS( 0, -0.01*time.asMicroseconds() );
			break;
            case 1: //DOWN
				Player.MovePOS( 0, 0.01*time.asMicroseconds() );
			break;
			case 2: //LEFT
				Player.MovePOS( -0.01*time.asMicroseconds(), 0 );
			break;
			case 3: //RIGHT
				Player.MovePOS( 0.01*time.asMicroseconds(), 0 );
			break;	
		}
	if(!InBoundary( Player )){
		Player.resetPOS();
	}
//........................................
//         Enemy Movement
//........................................
	if(Enemy_draw){
		if(!InBoundary( Enemy )){
			vel = -vel;
			Enemy.resetPOS();
		}
		else{
			Enemy.MovePOS( vel*time.asMicroseconds(), 0 );
		}
	}
//........................................
//         Collisions
//........................................
	
	if(Player.getBounds().intersects(Enemy.getBounds())){
		std::cout<< "intersects"<<  std::endl;
		Enemy.MovePOS( 0, -300 );
		Enemy_draw = false;
		Player.resetPOS();
	}
	else{
		//std::cout<< "do not intersects"<<  std::endl;
	}

}

void GAME::DRAW(){
	G_window.clear(sf::Color::Black);
	G_window.draw(Enemy);
	G_window.draw(Player);
	G_window.display();
}

bool GAME::InBoundary( SOLID& solid_obj ){

	for(int i=0; i<solid_obj.getVertexCount(); i++){
		if( solid_obj[i].position.x < 0 || solid_obj[i].position.x > 600 )
			return 0;
		else if( solid_obj[i].position.y < 0 || solid_obj[i].position.y > 600 ) 
			return 0;
	}
return 1;
}