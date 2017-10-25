#include "GameManager.h"
#include <thread>

GameManager* gm = new GameManager();
void roadCrossing(){
	gm->start();
	gm->update();
}

int main(){
	resizeConsole(800, 700);

	thread t(roadCrossing);

	while (!gm->game_over()){
		if (_kbhit()){
			char c = _getch();
			if (c == 'd')
				gm->get_player()->move_right();
			if (c == 'a')
				gm->get_player()->move_left();
			if (c == 'w'){
				if (gm->get_player()->get_y() == 1){
					gm->stop();
					continue;
				}
				gm->get_player()->move_up();
			}
			if (c == 's')
				gm->get_player()->move_down();
		}
	}
	t.join();

	return 0;
}