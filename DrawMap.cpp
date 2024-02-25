#include <SFML/Graphics.hpp>
using namespace sf;

#include "global.hpp"
#include "DrawMap.hpp"


void draw_map(const Image& fSMap, RenderWindow& fWindow, const Texture& fMapText, char mapSketch[][1000]) {
	float map_height = floor(fSMap.getSize().y / 3.f);
	Sprite cell_sprite(fMapText);
	for (short a = 0; a < fSMap.getSize().x; a++) {

		for (short b = 0; b < map_height; b++)
		{
			short sprite_x = 0;
			short sprite_y = 0;

			//Checking the pixel around our cell sprite
			Color pixel = fSMap.getPixel(a, b + 2 * map_height);
			Color pixel_down = Color(0, 0, 0, 0);
			Color pixel_left = Color(0, 0, 0, 0);
			Color pixel_right = Color(0, 0, 0, 0);
			Color pixel_up = Color(0, 0, 0, 0);

			cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);

			//Ignore the empty pixels.
			if (255 == pixel.a)
			{
				//Here we're getting pixels around the pixel we're currently checking.
				if (0 < a)
				{
					pixel_left = fSMap.getPixel(a - 1, b + 2 * map_height);
				}

				if (0 < b)
				{
					pixel_up = fSMap.getPixel(a, b + 2 * map_height - 1);
				}

				if (a < fSMap.getSize().x - 1)
				{
					pixel_right = fSMap.getPixel(1 + a, b + 2 * map_height);
				}

				if (b < map_height - 1)
				{
					pixel_down = fSMap.getPixel(a, 1 + b + 2 * map_height);
				}

				//Nothing complicated here.
				//Just a bunch of if's and else's that determine the position of the tile we're gonna draw.
				//Yeah, I know it's bad.
				if (sf::Color(255, 255, 255) == pixel) //Clouds
				{
					sprite_x = 8;

					if (sf::Color(255, 255, 255) == pixel_up)
					{
						sprite_y = 1;
					}

					if (sf::Color(255, 255, 255) == pixel_left)
					{
						if (sf::Color(255, 255, 255) != pixel_right)
						{
							sprite_x = 9;
						}
					}
					else if (sf::Color(255, 255, 255) == pixel_right)
					{
						sprite_x = 7;
					}
				}
				else if (sf::Color(146, 219, 0) == pixel) //Grass
				{
					sprite_x = 5;

					if (sf::Color(146, 219, 0) == pixel_left)
					{
						if (sf::Color(146, 219, 0) != pixel_right)
						{
							sprite_x = 6;
						}
					}
					else if (sf::Color(146, 219, 0) == pixel_right)
					{
						sprite_x = 4;
					}
				}
				else if (sf::Color(0, 73, 0) == pixel) //Hills outline
				{
					sprite_y = 1;

					if (sf::Color(0, 109, 0) == pixel_left)
					{
						if (sf::Color(0, 109, 0) != pixel_right)
						{
							sprite_x = 2;
						}
					}
					else if (sf::Color(0, 109, 0) == pixel_right)
					{
						sprite_x = 1;
					}
				}
				else if (sf::Color(0, 109, 0) == pixel) //Hills
				{
					sprite_x = 4;
					sprite_y = 1;

					if (sf::Color(0, 73, 0) == pixel_left)
					{
						sprite_x = 3;
					}
					else if (sf::Color(0, 73, 0) == pixel_right)
					{
						sprite_x = 5;
					}
				}
				else if (sf::Color(109, 255, 85) == pixel) //Flagpole
				{
					sprite_x = 12;

					if (sf::Color(109, 255, 85) == pixel_up)
					{
						sprite_y = 1;
					}
				}

				cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));

				fWindow.draw(cell_sprite);
			}


			//Yes, we're drawing the blocks separately from the background tiles.
			if ('E' != mapSketch[a][b])
			{
				if (mapSketch[a][b] == 'P') //Pipes
				{
					if ('P' == mapSketch[a][b - 1])
					{
						sprite_y = 1;
					}
					else
					{
						sprite_y = 0;
					}

					if ('P' == mapSketch[a - 1][b])
					{
						sprite_x = 11;
					}
					else
					{
						sprite_x = 10;
					}
				}
				else if ('Q' == mapSketch[a][b]) //Question blocks
				{
					sprite_x = 1;
					sprite_y = 0;
				}
				else if ('W' == mapSketch[a][b])
				{
					sprite_y = 0;

					if (sf::Color(0, 0, 0) == fSMap.getPixel(a, b)) //Walls
					{
						sprite_x = 2;
					}
					else //Solid blocks
					{
						sprite_x = 3;
					}
				}

				cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));

				fWindow.draw(cell_sprite);
			}
		}

	}
}
