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
	void MovePOS( sf::Vector2f POS );
	void resetPOS();
	void setPhysics();
	void putPOS( double x, double y );
	void putPOS( sf::Vector2f POS );
	void Inertia( double delta_t ); //Lineal inertial movement
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

class SPACE{
  private:
	sf::RenderWindow& G_window;
  public:
	SPACE( sf::RenderWindow& window ); //Intialization
	void ChangeState();
 	bool Update( int key_input, sf::Time time );
	void Draw();
	bool InBoundary( SOLID& solid_obj );
	bool Enemy_draw, Bullet_draw;
	PLAYER Player;
	SOLID Enemy, Bullet;
};

class MENU{
  public:
	MENU();
	void ChangeState();
	void Update();
	void Draw();
};

class GAME{
  private:
	sf::RenderWindow& G_window;
//	MENU MenuState;
	SPACE SpaceState;
  public:
	GAME( sf::RenderWindow& window );
	void ChangeState();
	void Update( int key_input, sf::Time time );
	void Draw();
};

