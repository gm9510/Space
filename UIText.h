#ifndef _UIText_CLASS_
#define _UIText_CLASS_

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

class BUTTON : public sf::Drawable {
  private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Text B_txt;
	sf::VertexArray B_button;
  public:
	BUTTON();
	BUTTON( std::string , sf::Font& , unsigned int );
	void setString( std::string );
	void setFont( sf::Font & );
	void setCharacterSize( unsigned int );
	void setPosition( double , double );
	void setButton( double );
	sf::FloatRect getBounds();
};

class TEXT : public sf::Drawable {
  private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  public:
	TEXT( );
	std::vector<sf::Text> txt_list;
};

#endif
