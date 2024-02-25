#pragma once


struct Goomba
{
	bool dead;

	float horizontal_speed;
	float vertical_speed;
	float x;
	float y;

	//As soon as this timer reaches 0, we remove this goomba.
	unsigned short death_timer;

	sf::Sprite sprite;

	sf::Texture texture;

public:
	Goomba();
	void initGoomba(float i_x, float i_y);

	bool get_dead() const;

	unsigned short get_death_timer() const;

	//This sounds so dark.
	void die();
	void draw(unsigned i_view_x, sf::RenderWindow& i_window,Text& scoreText, Mario& i_mario);
	void update(unsigned i_view_x, Goomba i_goombas[], char mapSketch[][1000], char sketchPerCell[][32], Mario& i_mario, Image& sMap, Text& text, Sound& death, Text& scoreText, RenderWindow& fWindow);

	sf::FloatRect get_hit_box() const;
};
