#include "Bullet.hpp"
#include "Obstacle.hpp"
///--------------------------CLASE BULLET-------------------------------
Bullet::Bullet(int x, int y, sf::Texture &texture, int v){
	sprite.setTexture(texture);
//	sprite.setTextureRect(intRect);
	sprite.setPosition(x,y);
	sprite.setScale(0.1f,0.1f);
	vel=v;
}

void Bullet::Update(){
	sprite.move(vel,0);
}

sf::Vector2f Bullet::getPosition(){
	return sprite.getPosition();
}

void Bullet::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	rt.draw(sprite,rs);
}
///-------------------------CLASE BULLETMOBS-------------------------------
bulletMobs::bulletMobs(int x, int y, sf::Texture &texture, int v){

	spriteM.setTexture(texture);
//	sprite.setTextureRect(intRect);
	spriteM.setPosition(x,y);
	spriteM.setScale(1,1);
	vel=v;
}

void bulletMobs::Update(){
	spriteM.move(-vel,0);
}

sf::Vector2f bulletMobs::getPosition(){
	return spriteM.getPosition();
}

void bulletMobs::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	rt.draw(spriteM,rs);
}
