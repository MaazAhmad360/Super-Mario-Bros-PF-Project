#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
struct Mario
{
	Sprite sprite;
	Texture texture;
	RectangleShape bounds;
	FloatRect hitbox;
	bool dead;
	bool on_ground;

	float horizontalSpeed;
	float verticalSpeed;
	float x;
	float y;
	int killCount;

	unsigned char jump_timer;

	Mario();

	void update(char mapSketch[][1000], char sketchPerCell[][32], Image& sMap, Sound& jump, Sound& death);

	bool get_dead() const;

	void set_vertical_speed(float i_value);
	sf::FloatRect get_hit_box();
	float get_vertical_speed() const;
	float get_x() const;
	void die(Sound& death);
	void reset(Sound& death);
	int getKillCount();
	void incKillCount();

};

