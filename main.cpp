#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Parallax.hpp"
#include "UISound.hpp"


using namespace std;

int main(){

	sf::Texture backT, bulletT, bulletMobsT, mobsT, ShipT;
	sf::Sprite background;

	if(!bulletT.loadFromFile("resources/sprites/bullet.png")){ ///VER DÓNDE PONERLO EN LAS HPP/CPP
		cout<<"Error al cargar la textura\n";
	}
	if(!bulletMobsT.loadFromFile("resources/sprites/bulletMobs.png")){ ///VER DÓNDE PONERLO EN LAS HPP/CPP
		cout<<"Error al cargar la textura\n";
	}
	if(!mobsT.loadFromFile("resources/sprites/mobs.png")){
            cout<<"Error al cargar la textura resources/sprites/mobs.png"<<'\n';
    }
    if(!backT.loadFromFile("resources/sprites/background.png")){
		std::cout<<"Error al cargar la textura resources/sprites/background.png"<<'\n';
	}

	Mobs mobs(mobsT,150,150);
	vector<Bullet> bulletsPlayer;
	vector<bulletMobs> bulletmobs;

	background.setTexture(backT);
	background.setPosition(0,-15);
	background.setScale(1,1);

	bool initiated;
	bool pressed;

	sf::RenderWindow window(sf::VideoMode(1000,700),"Last Stand"); /// TAMAÑO DE LA VENTANA
	window.setFramerateLimit(60); /// SETEAR EL LIMITE DE FRAMES

	pressed=false;
    UISound uis;

	while(window.isOpen()){ /// BUCLE PRINCIPAL DEL JUEGO

		Ship *ship  = new Ship(110,350,ShipT); /// INICIALIZACIÓN. ASIGNACIÓN DINAMICA DE MEMORIA. ASÍ DESPUÉS ELIMINA DE MEMORIA EL OBJETO SHIP, Y CREA UNO NUEVO.
		Parallax *parallax = new Parallax(); /// INICIALIZACIÓN
		initiated=false; /// INICIALIZACIÓN. TODAVIA NO INICIO.
		uis.Initiated(false); /// INICIALIZACIÓN
		while(true){ /// EJECUCION DEL JUEGO
			sf::Event event; /// DETECTAR EVENTO
			while(window.pollEvent(event)){
				if(event.type==sf::Event::Closed){ /// SI EL EVENTO ES DE TIPO CLOSED
					window.close();
					return 0; /// RETROCEDER
				}
			}

			ship->Update(); /// ES CON FLECHA PORQUE ES UN PUNTERO

            if(ship->Shoot()&&initiated==true&&ship->GetLive()==true&&bulletsPlayer.size()<1){ /// CONDICIONES PARA DISPARAR JUGADOR
                Bullet bullet(ship->GetPosition().x+23,ship->GetPosition().y-50,bulletT,20);
                bulletsPlayer.push_back(bullet);
                uis.Shoot();
            }
            if(mobs.Shoot()&&bulletmobs.size()<6){ /// CONDICIONES PARA DISPARAR MOBS
                bulletMobs bullet(mobs.GetPosition().x-100,mobs.GetPosition().y,bulletMobsT,10);
                bulletmobs.push_back(bullet);
                uis.Shoot();
            }


            for(int i = 0;i < bulletsPlayer.size(); i++){ /// ELIMINA EL PROYECTIL JUGADOR AL TOCAR UN OBST Ó SALGA DE LA PANTALLA.
                sf::IntRect rectShoot(bulletsPlayer[i].getPosition().x,bulletsPlayer[i].getPosition().y,40,10);

                if(parallax->CollisionBullet(rectShoot)){
                    bulletsPlayer.erase(bulletsPlayer.begin()+i);
                }

                if(bulletsPlayer[i].getPosition().x>1000*1.1f){
                    bulletsPlayer.erase(bulletsPlayer.begin()+i);
                }
                if(mobs.CollisionMobs(rectShoot)){ /// ELIMINA EL PROYECTIL AL TOCAR EL MOB
                    bulletsPlayer.erase(bulletsPlayer.begin()+i);
                    parallax->KillScore();
                    uis.Explosion();
                    mobs.Restart();
                }
			}
			for(int i = 0;i < bulletmobs.size(); i++){ /// ELIMINA EL PROYECTIL MOBS AL SALIR DE LA PANTALLA, AL MATAR AL MOB Y AL MATAR AL JUGADOR.
                sf::IntRect rectShoot(bulletmobs[i].getPosition().x,bulletmobs[i].getPosition().y,40,10);
                if(bulletmobs[i].getPosition().x<-100){
                    bulletmobs.erase(bulletmobs.begin()+i);
                }
                /**if(mobs.CollisionMobs(rectShoot)){
                    bulletmobs.erase(bulletmobs.begin()+i);
                    mobs.Restart();
                }*/
                if(ship->CollisionShipMobs(rectShoot)){
                    bulletmobs.clear();
                    bulletsPlayer.clear();
                    ship->Death();
                }
			}


			for(int i = 0;i < (int)bulletsPlayer.size(); i++){ /// MOVIMIENTO DEL PROYECTIL JUGADOR
                bulletsPlayer[i].Update();
			}
			for(int i = 0;i < (int)bulletmobs.size(); i++){ /// MOVIMIENTO DEL PROYECTIL MOBS
                bulletmobs[i].Update();
			}
            if(!ship->GetLive()||initiated==false){ ///QUE VUELVA POS INICIAL
                mobs.Restart();
            }
			if(ship->GetLive()){
				parallax->Update();
				mobs.Update();
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)&&initiated==false){
                uis.ShowScores();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)&&initiated==false){
                uis.ResetScore();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)&&initiated==false){
                uis.ResetHighScore();
                }
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!pressed){ /// SI EL BOTON ES PRESIONADO Y QUE CUENTE SOLO 1 CLICK
					ship->Jump();
					pressed=true; /// YA NO VA A PODER VOLVER A ENTRAR EL CLICK
					uis.Jump();
					if(!initiated){ /// CUANDO DA EL PRIMER SALTO SE PONE EN TRUE
						initiated=true;
						ship->Initiated();
						parallax->Initiated();
						mobs.Initiated();
						uis.Initiated(true);
					}
				}
			}else{
				uis.GameOver();
			}


			if(!ship->GetLive()&&sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!pressed){
				//Reinicio
				pressed=true;
				break; /// ESTE BREAK TERMINA EL WHILE
			}


			sf::IntRect rect(ship->GetPosition().x-23,ship->GetPosition().y-21,44,40);

			if(parallax->Collision(rect)){ /// SI CHOCA CONTRA ALGO, LIMPIA PROYECTILES Y MUERE
                bulletmobs.clear();
                bulletsPlayer.clear();
				ship->Death();
			}

			if(ship->GetPosition().y<0||ship->GetPosition().y>700-136){ /// SI PASA ESTO, MUERE. -136 ES EL TAM DEL SUELO
                bulletmobs.clear();
                bulletsPlayer.clear();
                ship->Death();
            }

			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){ /// SI NO ESTÁ PRESIONANDO, VUELVE A FALSO
				pressed=false;
			}

			uis.SetScore(parallax->Score());

			window.clear(); /// LIMPIAR VENTANA
			window.draw(background);
			window.draw(mobs);
			window.draw(*parallax); /// DRAW https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php#:~:text="window.draw(object)"
			window.draw(*ship);
            for(int i = 0;i<(int)bulletsPlayer.size();i++){
                window.draw(bulletsPlayer[i]);
			}
			for(int i = 0;i<(int)bulletmobs.size();i++){
                window.draw(bulletmobs[i]);
			}
			window.draw(uis);
			window.display();
		}

		delete ship; /// SE ELIMINA DE MEMORIA
		delete parallax; /// SE ELIMINA DE MEMORIA
 	}
	return 0;
}
