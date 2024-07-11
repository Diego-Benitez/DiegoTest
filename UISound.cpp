#include "UISound.hpp"
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

UISound::UISound(){
	initiated = false;
	gameOver = false;

	if(!font.loadFromFile("resources/font/font.ttf")){
		cout<<"Error al cargar la fuente resources/font/font.ttf"<<'\n';
	}

	if(!gameOverT.loadFromFile("resources/sprites/gameover2.png")){
		cout<<"Error al cargar la textura resources/sprites/gameover2.png"<<'\n';
	}

	if(!initT.loadFromFile("resources/sprites/message2.png")){
		cout<<"Error al cargar la textura resources/sprites/message2.png"<<'\n';
	}

	if(!pointB.loadFromFile("resources/sounds/point.ogg")){
		cout<<"Error al cargar el sonido resources/sounds/point.ogg"<<'\n';
	}

	if(!jumpB.loadFromFile("resources/sounds/propulsar.ogg")){
		cout<<"Error al cargar el sonido resources/sounds/propulsor.ogg"<<'\n';
	}

	if(!hitB.loadFromFile("resources/sounds/explosion.ogg")){
		cout<<"Error al cargar el sonido resources/sounds/explosion.ogg"<<'\n';
	}

    if(!shootB.loadFromFile("resources/sounds/disparo.ogg")){
		cout<<"Error al cargar el sonido resources/sounds/disparo.ogg"<<'\n';
	}
	if(!killmobB.loadFromFile("resources/sounds/killmob.ogg")){
		cout<<"Error al cargar la textura resources/sounds/killmob.ogg"<<'\n';
	}

	music.openFromFile("resources/sounds/Libera me from hell Tengen Toppa Gurren Lagann Chiptune Instrumental Remix.ogg");
	music.setLoop(true);
	music.play();

	point.setBuffer(pointB);
	jump.setBuffer(jumpB);
	hit.setBuffer(hitB);
	shoot.setBuffer(shootB);
	killmob.setBuffer(killmobB);

	score=0;
	scoreT.setFont(font);
	scoreT.setCharacterSize(40);
	scoreT.setString(to_string(score));
	scoreT.setOrigin(scoreT.getGlobalBounds().width/2,scoreT.getGlobalBounds().height/2);
	scoreT.setPosition(850,700-112);

    nameT.setFont(font);
    nameT.setCharacterSize(40);
    nameT.setString(playerName);
    nameT.setOrigin(nameT.getGlobalBounds().width/2,nameT.getGlobalBounds().height/2);


    LeerScore(0);

	maxScoreT.setFont(font);
	maxScoreT.setCharacterSize(20);
	maxScoreT.setString(to_string(maxScore));
	maxScoreT.setOrigin(maxScoreT.getGlobalBounds().width/2,maxScoreT.getGlobalBounds().height/2);
	maxScoreT.setPosition(900,700-112);

	gameOverS.setTexture(gameOverT);
	gameOverS.setOrigin(gameOverT.getSize().x/2,gameOverT.getSize().y/2);
	gameOverS.setScale(1,1);
	gameOverS.setPosition(500,250);

	initS.setTexture(initT);
	initS.setOrigin(initT.getSize().x/2,initT.getSize().y/2);
	initS.setScale(0.5f,0.5f);
	initS.setPosition(500,250);
}

void UISound::LeerScore(int pos){
    FILE *p = fopen("score", "rb");
    if(p == NULL) { return; }
    fseek(p, pos * sizeof(ScoreRecord), SEEK_SET);
    ScoreRecord record;
    fread(&record, sizeof(record), 1, p);
    fclose(p);

    maxScore = record.score;
    playerName = record.name; // Asigna el nombre del jugador leído
}

void UISound::GrabarRegistroScore(int score, const char* name) {
    FILE *p = fopen("highscore", "ab");
    if (p == NULL) {
        return;
    }

    ScoreRecord record;
    record.score = score;
    strncpy(record.name, name, sizeof(record.name) - 1);
    record.name[sizeof(record.name) - 1] = '\0';
    fwrite(&record, sizeof(record), 1, p);
    fclose(p);
}

void UISound::GrabarScore(int sc, const char* name){
        FILE *p=fopen("score", "w");
        if(p==NULL){return;}

        ScoreRecord record;
        record.score = sc;
        strncpy(record.name, name, sizeof(record.name) - 1);
        record.name[sizeof(record.name) - 1] = '\0';

        fwrite(&record, sizeof (record), 1, p);

        fclose(p);
}

void UISound::SetScore(int val){
	if(score!=val) point.play();
	score=val;
	scoreT.setString(to_string(score));
	scoreT.setOrigin(scoreT.getGlobalBounds().width/2,scoreT.getGlobalBounds().height/2);
}

void UISound::Initiated(bool state){
	initiated=state;
	score=0;
	gameOver=false;
	LeerScore(0);
	maxScoreT.setString(to_string(maxScore));
	maxScoreT.setOrigin(maxScoreT.getGlobalBounds().width/2,maxScoreT.getGlobalBounds().height/2);
	scoreT.setString(to_string(score));
	scoreT.setOrigin(scoreT.getGlobalBounds().width/2,scoreT.getGlobalBounds().height/2);
}

void UISound::Jump(){
	jump.play();
}
void UISound::ResetScore(){
    FILE *p=fopen("score", "wb");
    if(p==NULL){return;}
    fclose(p);
}

void UISound::ResetHighScore(){
    FILE *p=fopen("highscore", "wb");
    if(p==NULL){return;}
    fclose(p);
}

void UISound::GameOver(){
if(!gameOver) hit.play();
	if(score>maxScore){
	    ScoreRecord obj;
		maxScore=score;
		sf::RenderWindow window(sf::VideoMode(400, 200), "NEW HIGH SCORE!");
        EnterPlayerName(window);
		GrabarScore(score,playerName.c_str());
        GrabarRegistroScore(score, playerName.c_str());
	}
	gameOver=true;
}

void UISound::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	if(!initiated) rt.draw(initS,rs);
	else{
		rt.draw(scoreT,rs);
		rt.draw(maxScoreT,rs);
		if(gameOver) rt.draw(gameOverS,rs);
	}
}
void UISound::Shoot(){
    shoot.play();
}

void UISound::Explosion(){
    killmob.play();
}

// Captura el nombre del jugador
void UISound::EnterPlayerName(sf::RenderWindow& window) {
    sf::String playerInput;
    sf::Text playerText;
    playerText.setColor(sf::Color::White);
    playerText.setFont(font);
    playerText.setPosition(100, 100); //

    sf::Text promptText;
    promptText.setFont(font);
    promptText.setString("Ingresa tu nombre: ");
    promptText.setCharacterSize(16);
    ///promptText.setFillColor(sf::Color::White);
    promptText.setPosition(100.f, 50.f);

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("New High Score!");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2);
    titleText.setPosition(window.getSize().x / 2, 20.f);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && playerInput.getSize() > 0) {
                    playerInput.erase(playerInput.getSize() - 1, 1);
                } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    playerInput += event.text.unicode;
                }
                playerText.setString(playerInput);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                playerName = playerInput;
                window.close();
            }
        }

        window.clear();
        window.draw(titleText);
        window.draw(promptText);
        window.draw(playerText);
        window.display();
    }
}

bool compareScores(const ScoreRecord& a, const ScoreRecord& b) {
    return a.score > b.score; // Devuelve true si a.score es mayor que b.score
}
// Muestra la tabla de puntajes
void UISound::ShowScores() {

    sf::Texture bg;
    sf::Sprite backg;

    if(!bg.loadFromFile("resources/sprites/backgroundScore.png")){

        std::cout<<"Error al cargar la textura resources/sprites/backgroundScore.png"<<'\n';
    }
    backg.setTexture(bg);
	backg.setPosition(0,-15);
	backg.setScale(1.2,1.2);


    FILE *p = fopen("highscore", "rb");
    if (p == NULL) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    ScoreRecord record;
    std::vector<ScoreRecord> scores;

    while (fread(&record, sizeof(record), 1, p) == 1) {
        record.name[sizeof(record.name) - 1] = '\0';
        scores.push_back(record);

    }

    fclose(p);

    std::sort(scores.begin(), scores.end(), compareScores);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tabla de puntuaciones");
    if (!font.loadFromFile("resources/font/font.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("High Scores");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(window.getSize().x / 2, 50);

    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Press ENTER to return");
    subtitle.setCharacterSize(10);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    subtitle.setPosition((window.getSize().x-100), 80);

    std::vector<sf::Text> textScores;
    for (int i = 0; i < scores.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::string(scores[i].name) + " - " + std::to_string(scores[i].score));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(300.f, 100.f + 50.f * i);
        textScores.push_back(text);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
        }
        window.clear();
        window.draw(backg);
        window.draw(title);
        for (const auto& text : textScores) {
            window.draw(text);
        }
        window.draw(subtitle);
        window.display();
    }
}

