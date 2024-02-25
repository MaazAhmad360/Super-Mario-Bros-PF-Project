#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"
#include "mario.hpp"
#include "MapCollision.hpp"
using namespace sf;


char collision(Image& sMap, char mapSketch[][1000], char sketchPerCell[][32], float x, float y, float& horizontalSpeed, float& verticalSpeed) {
	short cell_x = x / CELL_SIZE;
	short cell_y = y / CELL_SIZE;
	
	int horizontalCollision = 0;
	unsigned char output = 0;
	//if (horizontalSpeed < 0 && verticalSpeed == 0) {
	//	if (sketchPerCell[i_y][i_x] == 'Q' || sketchPerCell[i_y][i_x] == 'P' || sketchPerCell[i_y][i_x] == 'W' || sketchPerCell[i_y][i_x] == 'B') {
	//		horizontalCollision = 1;
	//		horizontalSpeed = 0;
	//		std::cout << x << " " << y << " - ";
	//		std::cout << mapSketch[short(y)][short(x)] << " - " << sketchPerCell[i_y][i_x] << ". ";
	//		return 1;
	//	}
	//
	//}
	//else if (horizontalSpeed > 0 && verticalSpeed == 0) {
	//	if (sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] == 'Q' || sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] == 'P' || sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] == 'W' || sketchPerCell[i_y][i_x] == 'B') {
	//		horizontalCollision = 1;
	//		horizontalSpeed = 0;
	//		std::cout << x << " " << y << " - ";
	//		std::cout << mapSketch[short(y)][short(x + SPRITE_WIDTH)] << " - " << sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] << ". ";
	//		return 1;
	//	}
	//
	//}

	for (unsigned char a = 0; a < 4; a++)
	{
		short i_x;
		short i_y;

		switch (a)
		{
			case 0: //Top left cell
			{
				
				/*i_x = floor(cell_x);
				i_y = floor(cell_y);*/
				i_x = round(cell_x);
				/*i_x = floor(cell_x);*/
				i_y = round(cell_y) ;

				break;
			}
			case 1: //Top right cell
			{
				i_x = round(cell_x+ 1) ;
				/*i_x = ceil(cell_x);*/
				i_y = round(cell_y);

				break;
			}
			case 2: //Bottom left cell
			{
				i_x = round(cell_x);
				/*i_x = floor(cell_x);*/
				i_y = round(cell_y + 1);

				break;
			}
			case 3: //Bottom right cell
			{
				i_x = round(cell_x+ 1) ;
				/*i_x = ceil(cell_x);*/
				i_y = round(cell_y+ 1) ;
			}
		}
		/*i_x = x;
		i_y = y;*/

		/*std::cout << x << "  " << y << "-";
		std::cout << x / CELL_SIZE << "  " << y / CELL_SIZE << "-";
		std::cout << i_x << "  " << i_y << "-";*/
		if (0 <= x && i_x >= 0)
		{
			if (0 <= y && i_y >= 0)
			{
					//Checking if the cell's type is one of the cell types we need to check.
					if (sketchPerCell[i_x][i_y] == 'Q' || sketchPerCell[i_x][i_y] == 'P' || sketchPerCell[i_x][i_y] == 'W' || sketchPerCell[i_x][i_y] == 'B') {
						horizontalCollision = 1;
						//In binary this will be 0001, 0010, 0100 or 1000.
						output += pow(2, a);
						/*horizontalSpeed = 0;*/
						/*std::cout << x << " " << y << " - ";
						std::cout << mapSketch[short(y)][short(x)] << " - " << sketchPerCell[i_x][i_y] << "\n";*/
						
					
					}
					//if (mapSketch[i_x][i_y] == 'Q' || mapSketch[i_x][i_y] == 'P' || mapSketch[i_x][i_y] == 'W' || mapSketch[i_x][i_y] == 'B') {
					//	horizontalCollision = 1;
					//	//In binary this will be 0001, 0010, 0100 or 1000.
					//	output += pow(2, a);
					//	/*horizontalSpeed = 0;*/
					//	/*std::cout << x << " " << y << " - ";
					//	std::cout << mapSketch[short(y)][short(x)] << " - " << sketchPerCell[i_x][i_y] << "\n";*/
					//	
					//
					//}
				
			}
		}
		else{
				if (sketchPerCell[short(i_x)][i_y] == 'W') {
					horizontalCollision = 1;
					//In binary this will be 0001, 0010, 0100 or 1000.
					output += pow(2, a);
						
					/*horizontalSpeed = 0;*/
					/*std::cout << x << " " << y << " - ";
					std::cout << mapSketch[short(y)][short(x)] << " - " << sketchPerCell[short(i_x + SPRITE_WIDTH)][i_y] << "\n";*/
					/*horizontalSpeed = 0;
					std::cout << x << " " << y << " - ";
					std::cout << mapSketch[short(y)][short(x + SPRITE_WIDTH)] << " - " << sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] << ". ";
					return 1;*/
				}
				//if (mapSketch[short(i_x + SPRITE_WIDTH)][i_y] == 'W') {
				//	horizontalCollision = 1;
				//	//In binary this will be 0001, 0010, 0100 or 1000.
				//	output += pow(2, a);
				//		
				//	/*horizontalSpeed = 0;*/
				//	/*std::cout << x << " " << y << " - ";
				//	std::cout << mapSketch[short(y)][short(x)] << " - " << sketchPerCell[short(i_x + SPRITE_WIDTH)][i_y] << "\n";*/
				//	/*horizontalSpeed = 0;
				//	std::cout << x << " " << y << " - ";
				//	std::cout << mapSketch[short(y)][short(x + SPRITE_WIDTH)] << " - " << sketchPerCell[i_y][short(i_x + SPRITE_WIDTH)] << ". ";
				//	return 1;*/
				//}
		}


	}
	return output;
	//Color pixel;
	//if (horizontalSpeed < 0 && verticalSpeed == 0) {
	//	pixel = sMap.getPixel(x, y);
	//	if (sf::Color(182, 73, 0) == pixel || Color(0, 182, 0) == pixel || Color(255, 146, 85) == pixel || sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel) {
	//		horizontalCollision = 1;
	//		horizontalSpeed = 0;
	//		std::cout << x << " " << y << " - ";
	//		std::cout << mapSketch[short(y)][short(x)] << " - " /*<< sketchPerCell[i_y][i_x] << ". "*/;
	//		return 1;
	//	}


	//}
	//else if (horizontalSpeed > 0 && verticalSpeed == 0) {
	//	pixel = sMap.getPixel(x + SPRITE_WIDTH, y + SPRITE_HEIGHT);
	//	
	//	if (sf::Color(182, 73, 0) == pixel || Color(0, 182, 0) == pixel || Color(255, 146, 85) == pixel || sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel) {
	//		horizontalCollision = 1;
	//		horizontalSpeed = 0;
	//		std::cout << x << " " << y << " - ";
	//		std::cout << mapSketch[short(y)][short(x)] << " - " /*<< sketchPerCell[i_y][i_x] << ". "*/;
	//		return 1;
	//	}
	//}

}
int collision(char mapSketch[][1000], Mario& mario) {
	
	short i_x = mario.x;
	short i_y = mario.y;
	short nextPosX = mario.x + mario.horizontalSpeed;
	short nextPosY = mario.y + mario.verticalSpeed;

	int horizontalCollision = 0;

	if (mario.horizontalSpeed < 0) {
		for (short i = i_y; i <= i_y + SPRITE_HEIGHT; i++) {
			if (mapSketch[nextPosX][i] == 'Q' || mapSketch[nextPosX][i] == 'P'  || mapSketch[nextPosX][i] == 'W' || mapSketch[nextPosX][i] == 'B') {
				horizontalCollision = 1;
				/*mario.horizontalSpeed = 0;*/
				/*std::cout << mario.x << " " << mario.y << ". ";
				std::cout << nextPosX;
				std::cout << mapSketch[nextPosX][i];*/

				return 1;
			}
		}
	}
	else if (mario.horizontalSpeed > 0) {
		for (short i = i_y; i <= i_y + SPRITE_HEIGHT; i++) {
			if (mapSketch[short(nextPosX + SPRITE_WIDTH)][i] == 'Q' || mapSketch[short(nextPosX + SPRITE_WIDTH)][i] == 'P'  || mapSketch[short(nextPosX + SPRITE_WIDTH)][i] == 'W' || mapSketch[short(nextPosX + SPRITE_WIDTH)][i] == 'B') {
				horizontalCollision = 1;
				/*mario.horizontalSpeed = 0;*/
				std::cout << mario.x << " " << mario.y << ". ";
				std::cout << nextPosX + SPRITE_WIDTH;
				std::cout << mapSketch[nextPosX][i];
				std::cout << mapSketch[short(nextPosX + SPRITE_WIDTH)][i];
				return 2;
			}
		}
	}
	else
		return 0;
}

int decToBin(char collision) {
	int temp = collision;
	int binary = 0;
	int mult = 10;
	binary += (temp % 2);
	temp = temp / 2;
	while (temp > 0) {
		binary += (temp % 2) * mult;
		mult *= 10;
		temp /= 2;
	}
	return binary;
}