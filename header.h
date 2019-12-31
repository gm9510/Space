#include <iostream>
#include <SFML/Graphics.hpp>

class SOLID : public sf::VertexArray{
private:
	
public:
	SOLID();
	SOLID( int nodes );
	void MoveCentre( double dx, double dy );
	void resetPOS();
	void UpdateSOLID();
	void setPhysics();
	sf::Vertex Masscenter;
	sf::Vertex D_Masscenter;
};

class GAME{
  private:
	sf::RenderWindow& G_window;
  public:
	GAME( sf::RenderWindow& window );
	bool UpDateStatus(int key_input, sf::Time time);
	void DRAW();
	bool InBoundary( SOLID& solid_obj );
	SOLID obj;
};

