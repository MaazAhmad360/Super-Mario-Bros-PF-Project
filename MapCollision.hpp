#pragma once

int collision(char mapSketch[][1000], Mario& mario);
char collision(Image& sMap, char mapSketch[][1000], char sketchPerCell[][32], float x, float y, float& horizontalSpeed, float& verticalSpeed);
int decToBin(char collision);
