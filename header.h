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
	sf::Vertex Masscenter;
	sf::Vertex prev_Masscenter;
};

class GAME{
  private:
	sf::RenderWindow& G_window;
  public:
	GAME( sf::RenderWindow& window );
	bool UpDateStatus(int key_input, sf::Time time, double& vel);
	void DRAW();
	bool InBoundary( SOLID& solid_obj );
	SOLID Player, Enemy;
};

