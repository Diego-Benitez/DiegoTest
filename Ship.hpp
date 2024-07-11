#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Ship : public sf::Drawable { /// LA CLASE VA A SER DIBUJABLE: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Drawable.php
	private:
		bool initiated; /// PARA VER SI EL JUEGO COMENZO (NO ESTÁ EN EL MENÚ)
		bool live; /// PARA VER SI ESTÁ VIVO
		int state; /// ESTADO PARA IR CAMBIANDO DE FRAMES CADA CIERTO TIEMPO
		int timerState; /// ESE CIERTO TIEMPO DELIMITADO POR UN TIMER
		vector<sf::Texture> states; /// TODAS LAS TEXTURAS DE CADA UNO DE LOS FRAMES/ANIMACION
		sf::Sprite sprite; /// EL SPRITE
		float move; /// NOS VA A DECIR CUÁNTO NOS TENEMOS QUE MOVER. SIMULA LA GRAVEDAD, NO ES CONSTANTE
        bool shoot = false;
	public:
		Ship(int,int,sf::Texture &texture); /// CONSTRUCTOR NOS PASA LA POS EN Y
		void Update(); ///
		void Jump(); /// QUE NOS DIGA DESDE EL MAIN CUANDO TENEMOS QUE SALTAR
		void Death(); /// QUE NOS DIGA SI TENEMOS QUE MORIR
		bool GetLive(); /// PREGUNTAR SI ESTAMOS VIVOS
		bool Shoot();
		bool CollisionShipMobs(sf::IntRect);
		sf::Vector2f GetPosition(); /// METODO PARA QUE NOS DE LA POS
		void Initiated(); /// QUE NOS DIGA QUE EL JUEGO YA INICIO
		virtual void draw(sf::RenderTarget &,sf::RenderStates) const;
};

