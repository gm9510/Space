#include "SOLID.h"

SOLID_ELEMENTS::SOLID_ELEMENTS (){

}

void SOLID_ELEMENTS::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if( !list.empty() ){
		for( auto i = list.begin(); i != list.end(); ++i ){
			if( i->draw_me ) target.draw( *i );
		}
	}
}
