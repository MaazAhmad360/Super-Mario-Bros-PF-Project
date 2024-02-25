#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#include <iostream>

#include "mario.hpp"
#include "MapCollision.hpp"
#include "global.hpp"

Mario::Mario() {
	dead = 0;
	on_ground = 0;
	horizontalSpeed = 0;
	verticalSpeed = 0;
	x = 15;
	y = 20;
	killCount = 0;
	texture.loadFromFile("Resources/MarioIdle.png");
	sprite.setTexture(texture);
	bounds.setSize(Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT));
}

void Mario::update(char mapSketch[][1000], char sketchPerCell[][32], Image& sMap, Sound& jump, Sound& death) {
	bool moving = 0;

	unsigned char horizontal_collision;
	unsigned char vertical_collision;
	unsigned int binary;

	on_ground = 0;
	if (dead == 0) {

		if (0 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moving = 1;
			if (horizontalSpeed < -MAX_HOR_SPEED) {
				horizontalSpeed = horizontalSpeed - ACCELARATION;

			}
			else {
				horizontalSpeed = -MAX_HOR_SPEED;
			}

		}

		if (0 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moving = 1;
			if (horizontalSpeed < MAX_HOR_SPEED) {
				horizontalSpeed = horizontalSpeed + ACCELARATION;

			}
			else {
				horizontalSpeed = MAX_HOR_SPEED;
			}

		}

		if (moving == 0) {

			if (horizontalSpeed > 0) {
				if (horizontalSpeed - ACCELARATION > 0) {
					horizontalSpeed -= ACCELARATION;
				}
				else {
					horizontalSpeed = 0;
				}

			}
			else if (horizontalSpeed < 0) {
				if (horizontalSpeed + ACCELARATION < 0) {
					horizontalSpeed += ACCELARATION;
				}
				else {
					horizontalSpeed = 0;
				}
			}

		}

		horizontal_collision = collision(sMap, mapSketch, sketchPerCell, x + horizontalSpeed, y, horizontalSpeed, verticalSpeed);
		binary = decToBin(horizontal_collision);

		if (((binary / 10) % 100 == 1) && ((binary / 1000) == 1)
			|| ((binary % 10) == 1) && ((binary / 100) % 10 == 1)
			|| ((binary / 10 == 111)))
		{
			moving = 0;

			//Here we're rounding Mario's position to the nearest cell.
			//5  - 0101 - left collision
			//10 - 1010 - right collision
			if (((binary / 10) % 100 == 1) && ((binary / 1000) == 1) || ((binary / 10) == 111))
			{
				std::cout << x << " - " << x / CELL_SIZE << ", ";
				/*x = CELL_SIZE * (ceil((horizontalSpeed + x) / (CELL_SIZE)) - 1.8);*/

				x = (-horizontalSpeed + x);
				horizontalSpeed = 0;
				
			}
			else if (((binary % 10) == 1) && ((binary / 100) % 10 == 1))
			{

				x = CELL_SIZE * (1 + floor((horizontalSpeed + x) / CELL_SIZE));
				horizontalSpeed = 0;
			}


		}
		else
		{
			x += horizontalSpeed;
		}
		//horizontal_collision = collision(mapSketch, *this);
		//if (0 < horizontal_collision)
		//{
		//	moving = 0;

		//	//Here we're rounding Mario's position to the nearest cell.
		//	//5  - 0101 - left collision
		//	//10 - 1010 - right collision
		//	if (1 == horizontal_collision )
		//	{
		//		x = CELL_SIZE * (ceil((horizontalSpeed + x) / CELL_SIZE) - 1);
		//	}
		//	else if (2 == horizontal_collision)
		//	{
		//		x = CELL_SIZE * (1 + floor((horizontalSpeed + x) / CELL_SIZE));
		//	}

		//	horizontalSpeed = 0;
		//}
		//else
		//{
		//	x += horizontalSpeed;
		//}

		vertical_collision = collision(sMap, mapSketch, sketchPerCell, x, y + 1, horizontalSpeed, verticalSpeed);

		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (0 == verticalSpeed && 0 < vertical_collision)
			{
				verticalSpeed = MARIO_JUMP_SPEED;

				jump_timer = MARIO_JUMP_TIMER;
				jump.play();
			}
			else if (0 < jump_timer) //This will make Mario jump higher the longer we press the jump key.
			{
				verticalSpeed = MARIO_JUMP_SPEED;

				jump_timer--;
			}
			else
			{
				verticalSpeed = std::min(GRAVITY + verticalSpeed, MAX_VERTICAL_SPEED);
			}
		}
		else
		{
			verticalSpeed = std::min(GRAVITY + verticalSpeed, MAX_VERTICAL_SPEED);

			jump_timer = 0;
		}

		vertical_collision = collision(sMap, mapSketch, sketchPerCell, x, y + verticalSpeed, horizontalSpeed, verticalSpeed);
		if (0 < vertical_collision)
		{
			//3  - 0011 - top collision
			//12 - 1100 - bottom collision
			if (3 == vertical_collision && 12 != vertical_collision)
			{
				y = CELL_SIZE * (1 + floor((verticalSpeed + y) / CELL_SIZE));
				
			}
			else if (12 == vertical_collision && 3 != vertical_collision)
			{

				y = CELL_SIZE * (ceil((verticalSpeed + y) / CELL_SIZE) - 1);
			}


			verticalSpeed = 0;
		}
		else
		{

			y += verticalSpeed;
		}

		vertical_collision = collision(sMap, mapSketch, sketchPerCell, x, y + 1, horizontalSpeed, verticalSpeed);

		if (0 < vertical_collision)
		{
			on_ground = 1;
		}


		/*if (Keyboard::isKeyPressed(Keyboard::Down)) {
			verticalSpeed = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			verticalSpeed = -2;
		}
		else
			verticalSpeed = 0;*/

	}
	else
	{
		
		
			verticalSpeed = std::min(GRAVITY + verticalSpeed, MAX_VERTICAL_SPEED);
			y += verticalSpeed;
		
		
	}
	
	if (SCREEN_HEIGHT <= y)
	{
		if (dead == 0) {
			die(death);
		}
		


	}
}
bool Mario::get_dead() const
{
	return dead;
}

float Mario::get_vertical_speed() const
{
	return verticalSpeed;
}

float Mario::get_x() const
{
	return x;
}

void Mario::die(Sound& death)
{
	dead = 1;
	death.play();
	
	
}

void Mario::reset(Sound& death)
{
	dead = 0;
	on_ground = 0;
	killCount = 0;

	horizontalSpeed = 0;
	verticalSpeed = 0;
	x = 0;
	y = 0;

	jump_timer = 0;


	texture.loadFromFile("Resources/MarioIdle.png");

	sprite.setTexture(texture);
	if (death.Playing) {
		death.stop();
	}

}
sf::FloatRect Mario::get_hit_box() 
{
	
	hitbox.top = y;
	hitbox.left = x;
	hitbox.height = CELL_SIZE;
	hitbox.width = CELL_SIZE;
	return hitbox;
}
void Mario::set_vertical_speed(float i_value)
{
	verticalSpeed = i_value;
}
int Mario::getKillCount() {

	return killCount;
}
void Mario::incKillCount() {
	killCount++;
}