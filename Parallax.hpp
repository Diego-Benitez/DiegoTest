#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Obstacle.hpp"
#include "Mobs.hpp"

using namespace std;

class Parallax : public sf::Drawable{ /// PARALLAX ES LA TECNICA QUE SE MUEVE EL FONDO MÁS NO EL PERSONAJE
	private:
		int last;
		int score; /// PUNTAJE
		bool initiated; /// SI INICIO
		sf::Texture obsT; /// TEXTURA DEL OBSTÁCULO
		sf::Texture baseT;
		vector<sf::Sprite> bases; /// VECTOR BASES
		vector<Obstacle> obstacles; /// VECTOR DEsetPosition OBSTÁCULOS


	public:
		Parallax();
		void Update();
		bool Collision(sf::IntRect); /// PARA CHEQUEAR LA COLISION. LLAMAR POR C/ OBST AL METODO COLLISION DE C/ OBJ OBST. INTERMEDIARIO ENTRE MAIN Y OBJ OBST
		bool CollisionBullet(sf::IntRect);
		void Initiated(); /// SI INICIO
		///void SetScore(int);
		int Score(); /// CONSULTAR PUNTAJE
		void KillScore();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};

