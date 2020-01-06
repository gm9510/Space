#include "header.h"

using namespace sf;

int main(){

	RenderWindow window(VideoMode(600,600), "Space");// Window start
	GAME game(window);
	Clock clock;
	Time time = clock.getElapsedTime();
	int input = -1;
	double vel = 0.01f;
	
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed) window.close();
		   //Update Inputs
			else if(event.type == Event::KeyPressed){
				if (event.key.code==Keyboard::Up)  input = 0;
				else if (event.key.code==Keyboard::Down)  input = 1;
				else if (event.key.code==Keyboard::Left) input = 2;
				else if (event.key.code==Keyboard::Right) input = 3;
				else input = -1;
			}
			else if(event.type == Event::KeyReleased){
				input = -1;
			}

		}
			//Update Time
		time = clock.getElapsedTime();
//		frames = 1.f/ time.asSeconds();
		game.UpDateStatus( input, time, vel);
		game.DRAW();
		clock.restart();
	}
return 0;
}
