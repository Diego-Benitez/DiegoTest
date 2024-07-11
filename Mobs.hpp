#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;

class Mobs: public sf::Drawable {
    private:
        bool initiated;
///		bool live; /// PARA VER SI ESTÁ VIVO
///		int state; /// ESTADO PARA IR CAMBIANDO DE FRAMES CADA CIERTO TIEMPO
///		int timerState; /// ESE CIERTO TIEMPO DELIMITADO POR UN TIMER
///		vector<sf::Texture> states; /// TODAS LAS TEXTURAS DE CADA UNO DE LOS FRAMES/ANIMACION
		sf::Sprite spriteA; /// 1er Sprite
        bool shoot = false;
///     vector<Bullet> bulletsMobs;
    public:
        Mobs(sf::Texture&,int,int); /// CONSTRUCTOR NOS PASA LA POS EN Y
		void Update(); ///
/**		void Death(); /// QUE NOS DIGA SI TENEMOS QUE MORIR
		bool GetLive();*/ /// PREGUNTAR SI ESTAMOS VIVOS
		bool Shoot();
        void Restart();
		bool CollisionMobs(sf::IntRect);
		void Initiated();
		sf::Vector2f GetPosition(); /// METODO PARA QUE NOS DE LA POS
		virtual void draw(sf::RenderTarget &,sf::RenderStates) const;
};
