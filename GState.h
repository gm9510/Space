#ifndef _GAME_STATE_
#define _GAME_STATE_

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SOLID.h"
#include "UIText.h"

//Forward Declaration---------------------------------
class GAME;

class STATE{ 
  public:
	virtual void Update(GAME* game) = 0;
	virtual void Draw(GAME* game) = 0;
	void ChangeState( GAME* game, std::unique_ptr<STATE> & state );
  protected:
	STATE();
};

class MenuSTATE : public STATE{
  private:
	sf::RenderWindow& My_window;
	sf::VertexArray Tri;
	sf::Font title_font;
	sf::Font txt_font;
	BUTTON Start_Button;
	TEXT UI;
  public:
	MenuSTATE( sf::RenderWindow& window, sf::Font&, sf::Font& );
	void Update(GAME* game);
	void Draw(GAME* game);
};

class PlaySTATE : public STATE{
  private:
	sf::RenderWindow& My_window;
	sf::VertexArray Tri;
  public:
	PlaySTATE( sf::RenderWindow& window );
	void Update(GAME* game);
	void Draw(GAME* game);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool InBoundary( SOLID& solid_obj );
	bool Enemy_draw, Bullet_draw;
	PLAYER Player;
	SOLID Enemy, Bullet;
};

#endif
