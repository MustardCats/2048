#define OLC_PGE_APPLICATION
#include "OlcMain.h"

int main() {

	Game game;
	if (game.Construct(150, 175, 4, 4)) {
		game.Start();
	}

	return 0;
}