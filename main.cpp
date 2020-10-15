#include "GEngine.h"

using namespace sf;

int main(){

	RenderWindow window(VideoMode(600,600), "Space Bullet Hell");// Window start
//	window.setFramerateLimit(60);
	GAME game(window);
	Clock clock;
	Time time = clock.getElapsedTime();
	int input = -1;
	int loop = 0;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed) window.close();
//----------Update Inputs---------------------------------------------
			else if(event.type == Event::KeyPressed){
				if (event.key.code==Keyboard::Space)	input = 4;
				else if (event.key.code==Keyboard::Q)	input = 10;
				else if (event.key.code==Keyboard::R)	input = 14;
				else input = -1;
			}
			else if(event.type == Event::KeyReleased){
				input = -1;
			}

		}
//------Update Time----------------------------------------------------
		time = clock.getElapsedTime();
		if( time.asMilliseconds() > 16 ){
			loop++;
			game.Update( input, loop, time );
			game.Draw();
			input = -1;
			clock.restart();
		}
		if(loop > 30) loop = 0;
	}
return 0;
}
