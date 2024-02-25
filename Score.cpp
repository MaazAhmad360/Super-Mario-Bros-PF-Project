#include <fstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#include "global.hpp"
#include "mario.hpp"
#include "Score.hpp"


void updateScore(Mario& fMario) {

	ofstream fout;

	fout.open("LastScore.txt");

	fout << fMario.getKillCount();

	fout.close();


}
void bestScore(Text& text) {

	int cScore;
	int bScore;
	ifstream fin;

	fin.open("LastScore.txt");

	fin >> cScore;

	fin.close();

	fin.open("BestScore.txt");

	fin >> bScore;

	fin.close();

	if (cScore > bScore) {

		ofstream fout;

		fout.open("BestScore.txt");
		fout << cScore;
		fout.close();

		text.setString("Your New Highest Score: " + to_string(cScore));

	}
	else {
		text.setString("Your Score: " + to_string(cScore));
	}

}
void drawText(Text& text, Mario& fMario, RenderWindow& fWindow, int i_viewX) {
	
		RectangleShape overlay;
		overlay.setFillColor(Color(0, 0, 0, 5));
		overlay.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		overlay.setPosition(Vector2f(i_viewX, 0));
		fWindow.draw(overlay);
		fWindow.draw(text);
	
}