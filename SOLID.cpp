#include "header.h"


SOLID::SOLID(){
Masscenter.color = sf::Color::White;
} //Default constructor
SOLID::SOLID( int nodes ): VertexArray( sf::TriangleStrip, nodes ){
Masscenter.color = sf::Color::White;
}

void SOLID::MoveCentre( double dx, double dy ){
	D_Masscenter.position.x = dx;
	D_Masscenter.position.y = dy;
	Masscenter.position.x += dx;
	Masscenter.position.y += dy;
	
}

void SOLID::resetPOS(){
	D_Masscenter.position = -D_Masscenter.position;
	Masscenter.position.x += D_Masscenter.position.x;
	Masscenter.position.y += D_Masscenter.position.y;
}

void SOLID::UpdateSOLID(){
	
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position.x += D_Masscenter.position.x;
		(*this)[i].position.y += D_Masscenter.position.y;
	}
}

void SOLID::setPhysics(){
	double Tx=0;
	double Ty=0;
	int N = this->getVertexCount();
	for(int i=0; i<(N-2); i++){
		Tx=0;
		Ty=0;
		for(int j=0; j<3; j++){
			Tx += ( (*this)[i+j].position.x )*0.333333;
			Ty += ( (*this)[i+j].position.y )*0.333333;
		}
		Masscenter.position.x += Tx/(N-2);
		Masscenter.position.y += Ty/(N-2);
	}
}
