#include "SOLID.h"


SOLID::SOLID(){
Masscenter.color = sf::Color::White;
} //Default constructor

SOLID::SOLID( int type ){

	switch( type ){
		case 3:
			this->resize(type);
			this->setPrimitiveType(sf::Triangles);
			std::cout<<this->getVertexCount()<<std::endl;
			(*this)[0].position = sf::Vector2f( 0.f,0.f );
			(*this)[1].position = sf::Vector2f( 5.f,0.f );
			(*this)[2].position = sf::Vector2f( 2.5,-20.f );
			(*this)[0].color = sf::Color::Blue;
			(*this)[1].color = sf::Color::Blue;
			(*this)[2].color = sf::Color::Blue;
		break;
		case 8:
			this->resize(type);
			this->setPrimitiveType(sf::TriangleFan);
			(*this)[0].position = sf::Vector2f(0.f,0.f);
			(*this)[0].color = sf::Color::Red;
			for(int i=1; i<8; i++ ){
				(*this)[i].position = sf::Vector2f(15.f*cos(1.57079633 - i*1.04719755),-15.f*sin(1.57079633 - i*1.04719755));
				(*this)[i].color = sf::Color::Red;
			}
		break;
	}
	Masscenter.color = sf::Color::White;
	this->setPhysics();
}

void SOLID::MovePOS( double dx, double dy ){
	prev_Masscenter.position = Masscenter.position;
	Masscenter.position.x += dx;
	Masscenter.position.y += dy;
// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::MovePOS( sf::Vector2f POS ){// POS -> displacement ( dx, dy )

	prev_Masscenter = Masscenter;
	Masscenter.position += POS;

	// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::resetPOS(){
	this->Masscenter.position = this->prev_Masscenter.position;
// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::putPOS( double x, double y ){
	Masscenter.position = sf::Vector2f( x, y );
// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::putPOS( sf::Vector2f POS ){
	Masscenter.position = POS;
// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::Inertia( double delta_t){
	prev_Masscenter.position = Masscenter.position;
	Masscenter.position.x += Velocity.x*delta_t ;
	Masscenter.position.y += Velocity.y*delta_t ;
// redraw the shape around the mass center
	for(int i=0; i<this->getVertexCount(); i++){
		(*this)[i].position = Shape[i].position + Masscenter.position;
	}
}

void SOLID::setPhysics(){
//------------------------------------------------------------------------------------------
//       Establish the the centre of as function of the drawble vertex array
//------------------------------------------------------------------------------------------
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

	sf::Vector2f buff; // this could be dinamically allocated!
	for(int i=0; i<N; i++){
		buff = (*this)[i].position - Masscenter.position;
		Shape.push_back( sf::Vertex( buff ) );
//		std::cout<<"["<<i<<"] x = "<< Shape[i].position.x << " y = "<< Shape[i].position.y <<std::endl;
	}
}
