#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable{
	private:
		sf::Sprite upSprite; /// SPRITE DE ARRIBA
		sf::Sprite downSprite; /// SPRITE DE ABAJO
	public:
		Obstacle(sf::Texture&,int,int); ///
		void Update(); ///
		bool Collision(sf::IntRect); ///
		bool CollisionBullet(sf::IntRect);
		sf::Vector2f GetPosition(); /// QUE PREGUNTE LA POS
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

