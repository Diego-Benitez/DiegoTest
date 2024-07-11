#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
	private:
		sf::Sprite sprite;
		int vel;
	public:
		Bullet(int x, int y, sf::Texture &texture, int v);
		void Update();
		sf::Vector2f getPosition();
		virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const;
};

class bulletMobs : public sf::Drawable {
	private:
		sf::Sprite spriteM;
		int vel;
	public:
		bulletMobs(int x, int y, sf::Texture &texture, int v);
		void Update();
		sf::Vector2f getPosition();
		virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const;
};
