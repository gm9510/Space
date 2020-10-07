#include "SOLID.h"

SOLID_ELEMENTS::SOLID_ELEMENTS (){

}

void SOLID_ELEMENTS::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if( !solid_elements.empty() ){
		for( auto i = solid_elements.begin(); i != solid_elements.end(); ++i ){
			target.draw( *i );
		}
	}
}
