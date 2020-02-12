//------------Text class for multiline multiformated drawable text-----------------
#include "UIText.h"

TEXT::TEXT(  ){
	
}

void TEXT::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if( !txt_list.empty() ){
		for( auto i = txt_list.begin(); i != txt_list.end(); ++i ){
			target.draw( *i );
		}
	}
}
