#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "mario.hpp"
#include "Goombas.hpp"
#include "MapCollision.hpp"
#include "Score.hpp"

#include <iostream>


Goomba::Goomba() {
	

}
void Goomba::initGoomba(float i_x, float i_y) {
	dead = 0;
	horizontal_speed = (-GOOMBA_SPEED);
	vertical_speed = (0);
	x = (i_x);
	y = (i_y);
	/*death_timer = (GOOMBA_DEATH_DURATION);*/
	sf::IntRect textureRect;
	textureRect.height = CELL_SIZE;
	textureRect.width = CELL_SIZE;
	texture.loadFromFile("Resources/GoombaWalk.png", textureRect);
	sprite.setTexture(texture);
}

void Goomba::draw(unsigned i_view_x, sf::RenderWindow& i_window, Text& scoreText, Mario& i_mario)
{
	//OPTIMIZATION!
	//We'll only draw goomba if it's visible on the screen.
	if (-CELL_SIZE < round(y) && round(x) > static_cast<int>(i_view_x) - CELL_SIZE && round(x) < SCREEN_WIDTH + i_view_x && round(y) < SCREEN_HEIGHT)
	{
	
		if (!dead) {
			sprite.setPosition(round(x), round(y));
			sprite.setTexture(texture);

			i_window.draw(sprite);
		}
	
	}
	if (i_mario.get_dead()) {
		drawText(scoreText, i_mario, i_window, i_view_x);
	}
}
bool Goomba::get_dead() const
{
	return dead;
}

unsigned short Goomba::get_death_timer() const
{
	return death_timer;
}

void Goomba::die()
{
	dead = 1;
	y += 32;

}

void Goomba::update(unsigned i_view_x, Goomba i_goombas[], char mapSketch[][1000], char sketchPerCell[][32], Mario& i_mario, Image& sMap, Text& text, Sound& death, Text& scoreText, RenderWindow& fWindow)
{
	//OPTIMIZATION!
	//We'll only update goomba if it's visible on the screen.
	if (-CELL_SIZE < y && x >= static_cast<int>(i_view_x) - CELL_SIZE - ENTITY_UPDATE_AREA && x < ENTITY_UPDATE_AREA + SCREEN_WIDTH + i_view_x && y < SCREEN_HEIGHT)
	{
		//I already explained this in "Mario.cpp".
		unsigned char vertical_collision;
		int binary;

		vertical_speed = std::min(GRAVITY + vertical_speed, MAX_VERTICAL_SPEED);

		sf::FloatRect vertical_hit_box(x, vertical_speed + y, CELL_SIZE, CELL_SIZE);

		vertical_collision = collision(sMap, mapSketch, sketchPerCell, x, vertical_speed + y, horizontal_speed, vertical_speed);

		if (0 < vertical_collision)
		{
			if (3 & vertical_collision && 12 & ~vertical_collision)
			{
				y = CELL_SIZE * (1 + floor((vertical_speed + y) / CELL_SIZE));
			}
			else if (3 & ~vertical_collision && 12 & vertical_collision)
			{
				y = CELL_SIZE * (ceil((vertical_speed + y) / CELL_SIZE) - 1);
			}

			vertical_speed = 0;
		}
		else
		{
			y += vertical_speed;
		}

		if (0 == dead)
		{
			unsigned char horizontal_collision;

			sf::FloatRect horizontal_hit_box(horizontal_speed + x, y, CELL_SIZE, CELL_SIZE);

			horizontal_collision = collision(sMap, mapSketch, sketchPerCell, horizontal_speed + x, y, horizontal_speed, vertical_speed);
			binary = decToBin(horizontal_collision);

			if (((binary / 10) % 100 == 1) && ((binary / 1000) == 1)
				|| ((binary % 10) == 1) && ((binary / 100) % 10 == 1)
				|| ((binary / 10 == 111)))
			{
				if (((binary / 10) % 100 == 1) && ((binary / 1000) == 1) || ((binary / 10) == 111))
				{
					x = CELL_SIZE * (ceil((horizontal_speed + x) / CELL_SIZE) - 1);
				}
				else if (((binary % 10) == 1) && ((binary / 100) % 10 == 1))
				{
					x = CELL_SIZE * (1 + floor((horizontal_speed + x) / CELL_SIZE));
				}

				horizontal_speed *= -1;
			}
			else
			{
				bool changed = 0;

				//for (const Goomba& goomba : i_goombas)
				//{
				//	//Making sure the goombas don't walk through each other.
				//	//I USED POINTERS!
				//	//        |
				//	//        |
				//	//       \/
				//	if (this != &goomba && 0 == goomba.get_dead() && 1 == horizontal_hit_box.intersects(goomba.get_hit_box()))
				//	{
				//		changed = 1;

				//		horizontal_speed *= -1;

				//		break;
				//	}
				//}

				if (0 == changed)
				{
					x += horizontal_speed;
				}
			}

			if (0 == i_mario.get_dead() && (1 == horizontal_hit_box.intersects(i_mario.get_hit_box()) || 1 == vertical_hit_box.intersects(i_mario.get_hit_box())))
			{
				//If Mario's vertical speed is greater than 0, that means he's falling.
				//Therefore, if Mario touches the goomba while falling, the goomba will die.
				if (0 < i_mario.get_vertical_speed())
				{
					i_mario.set_vertical_speed(0.5f * MARIO_JUMP_SPEED);
					i_mario.incKillCount();					
					text.setString("Kill Count " + std::to_string(i_mario.getKillCount()));
					die();
				}
				else
				{
					i_mario.die(death);
					updateScore(i_mario);

					bestScore(scoreText);
					/*drawText(scoreText, i_mario, fWindow);*/
					text.setString("Kill Count 0");
				}
			}

			
		}
		else
		{
			dead = 0;
		}
	}

	//If goomba falls outside the map, it'll be removed.
	if (SCREEN_HEIGHT <= y)
	{
		dead = 1;


	}
}