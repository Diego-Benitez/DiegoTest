#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


struct ScoreRecord {
    int score;
    char name[50];
};

class UISound: public sf::Drawable{
	private:
		sf::SoundBuffer pointB;
		sf::SoundBuffer jumpB;
		sf::SoundBuffer hitB;
		sf::SoundBuffer shootB;
		sf::SoundBuffer killmobB;
		sf::Sound point;
		sf::Sound jump;
		sf::Sound hit;
		sf::Sound shoot;
		sf::Sound killmob;
		sf::Music music;
		sf::Font font;
		sf::Text maxScoreT;
		sf::Text scoreT;
		sf::Text nameT;
		int maxScore=0 ;
		int score;
		bool initiated,gameOver;
		std::string playerName ;
		sf::Texture gameOverT;
		sf::Sprite gameOverS;
		sf::Texture initT;
		sf::Sprite initS;
	public:
		UISound();

		void SetScore(int);
		void Initiated(bool);
		void GameOver();
		void Jump();
		virtual void draw(sf::RenderTarget&,sf::RenderStates) const;
		void Shoot();
		void Explosion();

		void LeerScore(int);
		void GrabarScore(int,const char*);
		void ShowScores();
		void ResetScore();
		void ResetHighScore();

        void GrabarRegistroScore(int score, const char* name);
        void EnterPlayerName(sf::RenderWindow& window); // Captura el nombre del jugador
};

