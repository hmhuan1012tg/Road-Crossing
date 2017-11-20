#include "GameManager.h"

int main(){
	resizeConsole(800, 700);
	fixConsoleWindow();
	hideCursor();

	GameManager* gm = new GameManager();
	gm->run();

	cin.get();

	delete gm;
	
	return 0;
}