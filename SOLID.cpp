#include "header.h"


SOLID::SOLID(){} //Defoult constructor
SOLID::SOLID( int nodes ): VertexArray( sf::TriangleStrip, nodes ){
}

void SOLID::MoveIt( double dx, double dy ){
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position.x += dx;
		(*this)[i].position.y += dy;
	}
}