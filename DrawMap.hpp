#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

void draw_map(const Image& fSMap, RenderWindow& fWindow, const Texture& fMapText, char mapSketch[][1000]);