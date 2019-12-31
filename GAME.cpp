#include "header.h"

GAME::GAME( sf::RenderWindow& window ) : G_window(window) {	
	obj.resize(4);
	obj.setPrimitiveType(sf::TriangleStrip);
	
	obj[0].position = sf::Vector2f(10.f,590.f);
	obj[1].position = sf::Vector2f(22.f,540.f);
	obj[2].position = sf::Vector2f(60.f,590.f);
	obj[3].position = sf::Vector2f(48.f,540.f);
	for(int i=0; i<4; i++)	obj[i].color = sf::Color::Green;
}

bool GAME::UpDateStatus( int key_input, sf::Time time ){
	switch(key_input){
//			case 1: //DOWN
	
//			break;
			case 2: //LEFT
//				std::cout<< time.asMicroseconds() << std::endl;
				obj.MoveIt( -0.05*time.asMicroseconds(), 0 );
			break;
			case 3: //RIGHT
//				std::cout<< time.asMicroseconds() << std::endl;
				obj.MoveIt( 0.05*time.asMicroseconds(), 0 );
			break;
		}
}

void GAME::DRAW(){
	G_window.clear(sf::Color::Black);
	G_window.draw(obj);
	G_window.display();
}

bool GAME::InBoundary( SOLID& solid_obj ){

	for(int i=0; i<solid_obj.getVertexCount(); i++){
		if( solid_obj[i].position.x < 0 || solid_obj[i].position.x > 600 )
			return 0;
		else if( solid_obj[i].position.x < 0 || solid_obj[i].position.x > 600 ) 
			return 0;
		else return 1;

	}
}