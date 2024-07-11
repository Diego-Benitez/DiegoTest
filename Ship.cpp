#include "Ship.hpp"

Ship::Ship(int x, int y, sf::Texture &texture){ /// EL CONSTRUCTOR
	initiated=false; /// EL JUEGO NO EMPEZÓ
	live=true; /// DECIRLE QUE INICIALMENTE ESTAMOS VIVOS
	state=0; /// ESTADOS 0 DE LA ANIMACION
	timerState=10; ///
	states.resize(3); /// CARGAR LOS SPRITES DE LOS DIFERENTES ESTADOS
	if(!states[0].loadFromFile("resources/sprites/naveCaida.png")){
		cout<<"Error al cargar la textura resources/sprites/nave.png"<<'\n';
	}
	if(!states[1].loadFromFile("resources/sprites/nave.png")){
		cout<<"Error al cargar la textura resources/sprites/nave.png"<<'\n';
	}
	if(!states[2].loadFromFile("resources/sprites/naveCaida.png")){
		cout<<"Error al cargar la textura resources/sprites/nave.png"<<'\n';
	}
	sprite.setTexture(states[state]); /// SETEAR EL SPRITE DEL ESTADO INICIAL (OSEA 0)
	sprite.setOrigin(states[state].getSize().x/2,states[state].getSize().y/2); /// SETEAR EL ORIGEN AL SPRITE (VER EN UN VIDEO VIEJO POR QUÉ HACE ESO
	sprite.setPosition(x,y); /// ASIGNAR POS X Y
	sprite.setScale(0.7f,0.7f); /// AGRANDAR EL SPRITE
	move=0; /// AL PRINCIPIO NO SE MUEVA PARA ARRIBA NI PARA ABAJO

}

void Ship::Update(){

	if(!live){ /// SI ESTAMOS VIVOS, ESTO ES LA ANIMACION DE MUERTE
        states.resize(1);
        if(!states[0].loadFromFile("resources/sprites/explosion.png")){
        cout<<"Error al cargar la textura resources/sprites/explosion.png"<<'\n'; /// PUEDE TERMINAR CON ENDL
        }
        sprite.setTexture(states[0]);
        sprite.setScale(0.7f,0.7f);

        return; /// FRENA EL SPRITE AL CAER AL PISO
    }

	timerState--;
	if(timerState==0){ /// PARA QUE VAYA INTERCALANDO TEXTURAS/ESTADOS.
		state++;
		state%=(int)states.size();
		sprite.setTexture(states[state]);
		sprite.setOrigin(states[state].getSize().x/2,states[state].getSize().y/2);
		timerState=10;
	}

	if(!initiated) return; /// SI TODAVIA NO INICIO EL JUEGO, RETORNA.

	sprite.move(0,move); /// SI YA INICIO, QUE SE MUEVA
	move+=0.5f; /// GRAVEDAD

	if(move>8&&move<15) sprite.setRotation(sprite.getRotation()+4); /// QUE AL CAER, ROTE EL SPRITE
}
bool Ship::Shoot(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !shoot){
        shoot = true;
        return true;
    }else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        shoot = false;
    }
    return false;
}

void Ship::Jump(){ /// SALTO
	move=-8; /// RESTA A LA GRAVEDAD
	sprite.setRotation(-15); /// ROTACION
}
bool Ship::CollisionShipMobs(sf::IntRect rect){ /// ES UN RECT PERO CON ENTEROS. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php#related:~:text=the%20template%20syntax.-,Usage%20example%3A,-//%20Define%20a%20rectangle
	sf::IntRect rectA(sprite.getPosition().x,sprite.getPosition().y,50,30); /// ARREGLAR MENOS A Y ES SUBIR EL RECTANGULO ARRIBA
	if(rectA.intersects(rect)){ /// SI ALGUNO DE LOS DOS SUFRE UNA COLISION RECT
		return true;
	}
	return false;
}
sf::Vector2f Ship::GetPosition(){ /// METODO GETPOS
	return sprite.getPosition();
}

bool Ship::GetLive(){ /// METODO GETLIVE
	return live;
}

void Ship::Death(){ /// CAMBIA A MUERTO
	live=false;
}

void Ship::Initiated(){ ///
	initiated=true;
}

void Ship::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{ /// DIBUJA UN OBJETO A UN RENDER TARGET. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php#:~:text=Virtual%20destructor.%20More...-,Protected%20Member%20Functions,-virtual%20void%C2%A0
	rt.draw(sprite,rs);
}
