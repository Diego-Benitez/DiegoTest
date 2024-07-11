#include "Obstacle.hpp"

Obstacle::Obstacle(sf::Texture &texture, int x,int y){ /// CONSTRUCTOR
	upSprite.setTexture(texture);
	downSprite.setTexture(texture);

	upSprite.setOrigin(texture.getSize().x,0); /// EL ORIGEN
	upSprite.setRotation(180); /// ROTACION

	upSprite.setPosition(x,y);
	downSprite.setPosition(x,y+150); /// +150 Para que haya un espacio entre ambas tuberias

	upSprite.setScale(1.5f,1.5f); /// Para agrandar las texturas
	downSprite.setScale(1.5f,1.5f); ///
}

void Obstacle::Update(){ /// MOVIMIENTO
	upSprite.move(-2.5f, 0); /// En X e Y
	downSprite.move(-2.5f,0); ///
}

bool Obstacle::Collision(sf::IntRect rect){ /// ES UN RECT PERO CON ENTEROS. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php#related:~:text=the%20template%20syntax.-,Usage%20example%3A,-//%20Define%20a%20rectangle
	sf::IntRect rectUp(upSprite.getPosition().x+2,upSprite.getPosition().y-70,55,50); /// ARREGLAR MENOS A Y ES SUBIR EL RECTANGULO ARRIBA
	sf::IntRect rectDown(downSprite.getPosition().x+2,downSprite.getPosition().y,55,50);
	if(rectUp.intersects(rect)||rectDown.intersects(rect)){ /// SI ALGUNO DE LOS DOS SUFRE UNA COLISION RECT
		return true;
	}
	return false;
}
bool Obstacle::CollisionBullet(sf::IntRect rect){ /// ES UN RECT PERO CON ENTEROS. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php#related:~:text=the%20template%20syntax.-,Usage%20example%3A,-//%20Define%20a%20rectangle
	sf::IntRect rectUp(upSprite.getPosition().x+2,upSprite.getPosition().y-140,55,60); /// ARREGLAR MENOS A Y ES SUBIR EL RECTANGULO ARRIBA
	sf::IntRect rectDown(downSprite.getPosition().x+2,downSprite.getPosition().y-20,55,60);
	if(rectUp.intersects(rect)||rectDown.intersects(rect)){ /// SI ALGUNO DE LOS DOS SUFRE UNA COLISION RECT
		return true;
	}
	return false;
}

sf::Vector2f Obstacle::GetPosition(){ /// PARA CONSULTAR LA POS
	return upSprite.getPosition();
}

void Obstacle::draw(sf::RenderTarget &rt,sf::RenderStates rs) const{
	rt.draw(upSprite,rs);
	rt.draw(downSprite,rs);
}


