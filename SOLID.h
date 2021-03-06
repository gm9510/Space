#ifndef _SOLID_CLASS_
#define _SOLID_CLASS_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class SOLID : public sf::VertexArray{
private:
	std::vector<sf::Vertex> Shape;
	sf::Vertex Masscenter;
	sf::Vertex prev_Masscenter;
public:
	SOLID();
	SOLID( int type );
	SOLID* lead;
	bool draw_me;
	bool fire;
	void MovePOS( double dx, double dy );
	void MovePOS( sf::Vector2f POS );
	void resetPOS();
	void setPhysics();
	void putPOS( double x, double y );
	void putPOS( sf::Vector2f POS );
	void Inertia( double delta_t ); //Lineal inertial movement
	sf::Vector2f getPOS();
	sf::Vector2f Velocity;
};

class SOLID_ELEMENTS : public sf::Drawable {
  private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
  public:
	SOLID_ELEMENTS();
	std::vector<SOLID> list;
};

class PLAYER : public SOLID{
  public:
	PLAYER();
	void KeyInputs( double );
};

#endif
