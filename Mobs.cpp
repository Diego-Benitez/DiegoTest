#include "Mobs.hpp"

Mobs::Mobs(sf::Texture &texture,int x, int y){ /// EL CONSTRUCTOR
    initiated=false;

    srand(time(NULL));

    spriteA.setTexture(texture);
    spriteA.setPosition(900,-500); /// ASIGNAR POS X Y
    spriteA.setScale(1,1); /// AGRANDAR EL SPRITE


///	move=0; /// AL PRINCIPIO NO SE MUEVA PARA ARRIBA NI PARA ABAJO

}

void Mobs::Update(){

    if(spriteA.getPosition().y<600){ /// MOVIMIENTO DE LA BASE A LA IZQ
    spriteA.move(0,2.5);
    }else{
    spriteA.setPosition(900,-200);
    }


}

bool Mobs::Shoot(){
    if((spriteA.getPosition().y==rand()%10*25||spriteA.getPosition().y==rand()%10*25+50||spriteA.getPosition().y==rand()%10*25+100||spriteA.getPosition().y==rand()%10*25+150||spriteA.getPosition().y==rand()%10*25+200||spriteA.getPosition().y==rand()%10*25+250||spriteA.getPosition().y==rand()%10*25+300) && !shoot){
        shoot = true;
        return true;
    }else{
        shoot = false;
    }
    return false;
}

bool Mobs::CollisionMobs(sf::IntRect rect){ /// ES UN RECT PERO CON ENTEROS. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php#related:~:text=the%20template%20syntax.-,Usage%20example%3A,-//%20Define%20a%20rectangle
	sf::IntRect rectA(spriteA.getPosition().x+60,spriteA.getPosition().y-40,100,64); /// ARREGLAR MENOS A Y ES SUBIR EL RECTANGULO ARRIBA
	if(rectA.intersects(rect)){ /// SI ALGUNO DE LOS DOS SUFRE UNA COLISION RECT
		return true;
	}
	return false;
}

void Mobs::Restart(){
    spriteA.setPosition(900,-500);
    }

void Mobs::Initiated(){
	initiated=true;
}

sf::Vector2f Mobs::GetPosition(){ /// METODO GETPOS
		return spriteA.getPosition();
}


/**bool Mobs::GetLive(){ /// METODO GETLIVE
	return live;
}

void Mobs::Death(){ /// CAMBIA A MUERTO
	live=false;
}*/



void Mobs::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{ /// DIBUJA UN OBJETO A UN RENDER TARGET. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php#:~:text=Virtual%20destructor.%20More...-,Protected%20Member%20Functions,-virtual%20void%C2%A0
    rt.draw(spriteA,rs);
}

