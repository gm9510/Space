#include "GEngine.h"

using namespace sf;

int main(){

	RenderWindow window(VideoMode(600,600), "Space Bullet Hell");// Window start
//	window.setFramerateLimit(60);
	GAME game(window);
	Clock clock;
	Time time = clock.getElapsedTime();
	int input = -1;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed) window.close();
//----------Update Inputs---------------------------------------------
			else if(event.type == Event::KeyPressed){
				if (event.key.code==Keyboard::Space)	input = 4;
				else if (event.key.code==Keyboard::Q)	input = 10;
				else input = -1;
			}
			else if(event.type == Event::KeyReleased){
				input = -1;
			}

		}
//------Update Time----------------------------------------------------
		time = clock.getElapsedTime();
		game.Update( input, time );
		game.Draw();
		input = -1;
		clock.restart();
	}
return 0;
}
