#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector> 

class SOLID : public sf::VertexArray{
private:
	std::vector<sf::Vertex> Shape;
public:
	SOLID();
	SOLID( int nodes );
	void MovePOS( double dx, double dy );
	void resetPOS();
	void setPhysics();
	void putPOS( double x, double y );
	void putPOS( sf::Vector2f POS );
	sf::Vector2f Velocity;
	sf::Vertex Masscenter;
	sf::Vertex prev_Masscenter;
};

class PLAYER : public SOLID{
  public:
	PLAYER();
//	void shoot( SOLID bullet );
	void KeyInputs( int input, SOLID& bullet, double P_v );
};

class GAME{
  private:
	sf::RenderWindow& G_window;
  public:
	GAME( sf::RenderWindow& window ); //Intialization
 	bool UpDateStatus( int key_input, sf::Time time, double& vel );
	void DRAW();
	bool InBoundary( SOLID& solid_obj );
	bool Enemy_draw, Bullet_draw;
	PLAYER Player;
	SOLID Enemy, Bullet;
};

