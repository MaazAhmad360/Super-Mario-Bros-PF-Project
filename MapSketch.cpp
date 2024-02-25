#include <iostream>
#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "MapSketch.hpp"





void fMapSketch(sf::Image& sMap, char mapSketch[][1000], char sketchPerCell[][32], float goombaX[], float goombaY[], int& goombaCount) {
	sf::Sprite mapDraw;

	float map_height = floor(sMap.getSize().y / 3.f);
	int count = 0;

	for (unsigned short b = 0; b < 2 * map_height; b++)
	{
		for (unsigned short a = 0; a < sMap.getSize().x; a++)
		{
			sf::Color pixel = sMap.getPixel(a, b);

			//First we're gonna place the blocks.
			if (b < map_height)
			{
				if (sf::Color(182, 73, 0) == pixel)
				{
					mapSketch[a][b] = 'B';
				}
				else if (sf::Color(0, 182, 0) == pixel)
				{
					mapSketch[a][b] = 'P';
				}
				else if (sf::Color(255, 146, 85) == pixel)
				{
					mapSketch[a][b] = 'Q';
				}
				else if (sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel)
				{
					mapSketch[a][b] = 'W';
				}
				else
				{
					mapSketch[a][b] = 'E';
				}
				
			}
			else //Then we're gonna place the entities.
			{
				if (sf::Color(182, 73, 0) == pixel)
				{
					/*mapSketch[ a][short(b - map_height)] = 'G';*/
					goombaX[goombaCount] = (a * CELL_SIZE);
					goombaY[goombaCount] = (b - map_height) * CELL_SIZE;
					goombaCount++;
					
				}
			}
			
			/*std::cout << mapSketch[a][b];*/
		}
	}

	/*for (unsigned short a = 0; a < sMap.getSize().x; a++)
	{
		for (unsigned short b = 0; b < 2 * map_height; b++) {
			float map_height = floor(sMap.getSize().y / 3.f);*/

			for (unsigned short b = 0; b < 2 * map_height; b++)
			{
				for (unsigned short a = 0; a < sMap.getSize().x; a++)
				{
					sf::Color pixel = sMap.getPixel(a, b);

					//First we're gonna place the blocks.
					if (b < map_height)
					{
						if (sf::Color(182, 73, 0) == pixel)
						{
							sketchPerCell[a][b] = 'B';
						}
						else if (sf::Color(0, 182, 0) == pixel)
						{
							sketchPerCell[a][b] = 'P';
						}
						else if (sf::Color(255, 146, 85) == pixel)
						{
							sketchPerCell[a][b] = 'Q';
						}
						else if (sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel)
						{
							sketchPerCell[a][b] = 'W';
						}
						else
						{
							sketchPerCell[a][b] = 'E';
						}
						
					}
					else //Then we're gonna place the entities.
					{
						if (sf::Color(182, 73, 0) == pixel)
						{
							/*sketchPerCell[short( a / CELL_SIZE )][short((b - map_height) / CELL_SIZE)] = 'G';*/
							/*goombaX[goombaCount] = short(a / CELL_SIZE);
							goombaY[goombaCount] = short((b - map_height) / CELL_SIZE);
							goombaCount++;*/
						}
					}
					
				}
			}

		
	
}