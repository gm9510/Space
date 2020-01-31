//------------> Button class for drawable text-buttons actions <-----------------
#include "UIText.h"

BUTTON::BUTTON(){
	B_button.resize(4);
	B_button.setPrimitiveType(sf::Quads);
}

BUTTON::BUTTON(std::string s, sf::Font& font , unsigned int a): B_txt(s , font, a){
}

void BUTTON::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw( B_button, states );
	target.draw( B_txt, states );
}

void BUTTON::setString( std::string s ){
	B_txt.setString( s );
}

void BUTTON::setFont( sf::Font & font ){
	B_txt.setFont( font );
}

void BUTTON::setCharacterSize( unsigned int a ){
	B_txt.setCharacterSize( a );
}

void BUTTON::setPosition( double x , double y ){
	B_txt.setPosition( x , y );
}

void BUTTON::setButton( double padding ){
	sf::FloatRect rect = B_txt.getGlobalBounds();
	
	B_button[0] = sf::Vector2f( rect.left - padding					, rect.top - padding ); 
	B_button[1] = sf::Vector2f( rect.left + rect.width + padding	, rect.top - padding );
	B_button[2] = sf::Vector2f( rect.left + rect.width + padding	, rect.top + rect.height + padding );
	B_button[3] = sf::Vector2f( rect.left - padding 				, rect.top + rect.height + padding );
	for(int i=0; i<4; i++)	B_button[i].color = sf::Color::Red;
}

sf::FloatRect BUTTON::getBounds(){
	return B_button.getBounds();
}
