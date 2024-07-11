#include "Parallax.hpp"
using namespace std;

Parallax::Parallax(){ /// PARALLAX ES LA TECNICA QUE SE MUEVE EL FONDO MÁS NO EL PERSONAJE
	last=-1;
	initiated=false;
	score=0;
	if(!obsT.loadFromFile("resources/sprites/rock.png")){
		cout<<"Error al cargar la textura resources/sprites/rock.png"<<'\n';
	}
	if(!baseT.loadFromFile("resources/sprites/base.png")){
		cout<<"Error al cargar la textura resources/sprites/base.png"<<'\n';
	}

	srand(time(NULL)); /// SEMILLA. SRAND NECESITA UN ARGUMENTO QUE LE DE UNA SEMILLA PARA UNA SECUENCIA DE N° ALEATORIOS. TIME ES EL TIEMPO DEL 01/01/70 HASTA HOY. SIEMPRE CAMBIA CUANDO INICIA

	obstacles.push_back(Obstacle(obsT,500,100+rand()%250)); ///EL PRIMER PAR DE OBSTACULOS. POSICION EN Y 100+ UN NUMERO ENTRE 250.
	obstacles.push_back(Obstacle(obsT,850,100+rand()%250)); /// 2° """""""
	obstacles.push_back(Obstacle(obsT,1200,100+rand()%250)); /// 3° """""""

	sf::Sprite spriteBase;
	spriteBase.setTexture(baseT);
	spriteBase.setPosition(0,700-112); /// POSICION COMIENZO. 1ERA BASE
	spriteBase.setScale(1.5f,2); /// ESCALA
	bases.push_back(spriteBase);
	spriteBase.setPosition(336*1.5f,700-112); /// GENERA LA SEGUNDA BASE EN ESA POS
	bases.push_back(spriteBase);
	spriteBase.setPosition(336*1.5f*2,700-112); /// GENERA LA 3RA EN ESA POSICION. CONTIGUA A LA 2DA
    bases.push_back(spriteBase);
}

void Parallax::Update(){
	for(int i = 0; i < (int)bases.size(); i++){
		if(bases[i].getPosition().x<-(336*1.5f)){ /// SI LA POSICION DE LA BASE SALE DE LA PANTALLA...
			sf::Sprite spriteBase=bases[(int)bases.size()-1]; /// UN OBJETO SPRITE QUE COPIA EL ULTIMO ELEMENTO DEL VECTOR BASES
			spriteBase.setPosition(spriteBase.getPosition().x+336*1.5f,700-112); ///LO UBICA DETRÁS DEL ULTIMO ELEMENTO
			bases.push_back(spriteBase); /// LO MANDA AL FONDO DEL VECTOR.
			bases.erase(bases.begin()+i); ///DESTRUYE LA BASE i/LA PRIMERA
		}
	}

	for(int i = 0; i < (int)bases.size(); i++){ /// MOVIMIENTO DE LA BASE A LA IZQ
		bases[i].move(-2.5f,0);
	}

	if(!initiated) return; /// SI NO ESTÁ INICIADO TERMINA UPDATE, SINO SIGUE ABAJO

	int ult = (int)obstacles.size()-1;
	for(int i = 0; i < (int)obstacles.size(); i++){

		if(obstacles[i].GetPosition().x<100&&i>last){
			last=i;
			score++;
		}

		if(obstacles[i].GetPosition().x<=-100) last--,obstacles.erase(obstacles.begin()+i),obstacles.push_back(Obstacle(obsT,obstacles[ult].GetPosition().x+350,100+rand()%250));
	}

	for(int i = 0; i < (int)obstacles.size(); i++){
		obstacles[i].Update();
	}
}


bool Parallax::Collision(sf::IntRect rect){
	for(int i = 0; i < (int)obstacles.size(); i++){
		if(obstacles[i].Collision(rect)) return true;
	}
	return false;
}
bool Parallax::CollisionBullet(sf::IntRect rect){
	for(int i = 0; i < (int)obstacles.size(); i++){
		if(obstacles[i].CollisionBullet(rect)) return true;
	}
	return false;
}

/**void Parallax::SetScore(int &score){
    score+=5;
}*/

int Parallax::Score(){
	return score;
}
void Parallax::KillScore(){
    score+=5;
}

void Parallax::Initiated(){
	initiated=true;
}

void Parallax::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	for(int i = 0; i < (int)obstacles.size(); i++) rt.draw(obstacles[i],rs);
	for(int i = 0; i < (int)bases.size(); i++) rt.draw(bases[i],rs);
}


