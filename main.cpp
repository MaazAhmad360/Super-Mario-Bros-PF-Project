#include <iostream>
#include <string>
using namespace std;

#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#include "global.hpp"
#include "mario.hpp"
#include "MapSketch.hpp"
#include "DrawMap.hpp"
#include "MapCollision.hpp"
#include "Goombas.hpp"




int main() {

	
	char mapSketch[4000][1000];
	char sketchPerCell[500][32];
	float goombaX[50], goombaY[50];
	int goombaCount = 0;
	
	Mario mario;
	

	Texture map_sketch;
	Texture mapText;
	Image sMap;
	map_sketch.loadFromFile("Resources/MapSketch1.png");
	mapText.loadFromFile("Resources/Map1.png");
	sMap.loadFromFile("Resources/MapSketch1.png");

	bool collision_flag;

	//SFML/Graphics Declaration
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Super Mario Bros", Style::Close);

	View view(FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//converting Map Sketch into array
	fMapSketch(sMap, mapSketch, sketchPerCell, goombaX, goombaY, goombaCount);

	Goomba goomba[32];
	for (int i = 0; i < goombaCount; i++) {
		goomba[i].initGoomba(goombaX[i], goombaY[i]);
	}

	Font font;
	font.loadFromFile("Resources/SuperMario256.ttf");
	Text text;
	text.setFont(font);

	// set the string to display
	text.setPosition(Vector2f(0.8 * SCREEN_WIDTH, 10));

	// set the character size
	text.setCharacterSize(24);

	// set the color
	
	text.setString("Kill Count 0");

	Text headline;
	headline.setFont(font);
	headline.setString("\t\tMamam Mia!\nLets Play the Best Game of 1st Semester");
	headline.setPosition(Vector2f(0.5 * SCREEN_WIDTH, 50));
	headline.setCharacterSize(24);
	headline.setFillColor(sf::Color(255, 214, 10));
	headline.setOutlineColor(Color::Black);
	headline.setOutlineThickness(2.f);

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color(255, 214, 10));
	scoreText.setOutlineColor(Color::Black);
	scoreText.setOutlineThickness(2.f);


	//Jump decalration
	SoundBuffer jumpBuffer;
	Sound jump;
	jumpBuffer.loadFromFile("Resources/jump.wav");
	jump.setBuffer(jumpBuffer);
	jump.setVolume(10.f);
	
	//Death
	SoundBuffer deathBuffer;
	Sound death;
	deathBuffer.loadFromFile("Resources/death.wav");
	death.setBuffer(deathBuffer);
	death.setVolume(10.f);



	while (window.isOpen()) {

		window.setVerticalSyncEnabled(true);
		Event event;

		while (window.pollEvent(event)) {

			if (Keyboard::isKeyPressed(Keyboard::Escape) || (event.type == Event::Closed)) {
				window.close();

			}
			if (Event::KeyPressed) 
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Enter:
				{
					
					

					mario.reset(death);
					goombaCount = 0;
					fMapSketch(sMap, mapSketch, sketchPerCell, goombaX, goombaY, goombaCount);
					for (int i = 0; i < goombaCount; i++) {
						goomba[i].initGoomba(goombaX[i], goombaY[i]);
						
					}
					
				}
				}
			}
			

		}
		
		window.setView(view);
		mario.update(mapSketch, sketchPerCell, sMap, jump, death);
		/*collision_flag = collision(mapSketch, mario);*/
		
		/*mario.x += mario.horizontalSpeed;*/
		/*mario.y += mario.verticalSpeed;*/
		mario.sprite.setPosition(round(mario.x), round(mario.y));
		mario.bounds.setPosition(round(mario.x), round(mario.y));
		mario.hitbox = mario.bounds.getGlobalBounds();
		int view_x = clamp<int>(round(mario.x) - 0.5f * (SCREEN_WIDTH - CELL_SIZE), 0, CELL_SIZE * sMap.getSize().x - SCREEN_WIDTH);

		for (int i = 0; i < goombaCount; i++) {
			goomba[i].update(view_x, goomba, mapSketch, sketchPerCell, mario, sMap, text, death, scoreText, window);

		}
		text.setPosition(Vector2f( view_x, 10));
		
		scoreText.setPosition(Vector2f(view_x + (SCREEN_WIDTH / 4), SCREEN_HEIGHT / 3));

		view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		window.clear(Color::Blue);
		//Render code starts Here
		
		

		draw_map(sMap, window, mapText, mapSketch);

		window.draw(headline);
		window.draw(text);

		window.draw(mario.sprite);
		for (int i = 0; i < goombaCount; i++) {
			goomba[i].draw(view_x, window, scoreText, mario);
		}
		
		
		
		
		//Render Code Ends Here
		window.display();
		
	}
	return 0;
}