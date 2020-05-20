#include "olcPixelGameEngine.h"

#include <array>
#include <random>
#include <time.h>

class Game : public olc::PixelGameEngine {
public:
	Game() {
		sAppName = "2048";
	}

	bool OnUserCreate() override {
		topBarSize = SCREENHEIGHT() / 6;
		
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				grid.at(i).at(j) = 0;

		time = 0;
		score = 0;
		hasWon = false;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		gridFirst = grid;
		if (GetKey(olc::Key::UP).bPressed ||
			GetKey(olc::Key::DOWN).bPressed || 
			GetKey(olc::Key::LEFT).bPressed || 
			GetKey(olc::Key::RIGHT).bPressed) {
			Move();
			while(!AddBlock(grid));
		}
		// Update variables
		time += fElapsedTime;

		if (Is2048(grid)) {
			hasWon = true;
		}

		Clear(olc::BLACK);
		DrawGrid();
		DrawHeader();
		return true;
	}
// Fields
	std::array<std::array<int, 4>, 4> grid;
	std::array<std::array<int, 4>, 4> gridFirst;
	int topBarSize;
	int score;
	int highScore;
	int time;
	bool hasWon;
// Methods
	void Move() {
		// Multiple combinations won't happen
		bool combineOnce[4] = { 1, 1, 1, 1 };
		// DONE!!!
		if (GetKey(olc::Key::UP).bPressed) {
			for (int times = 0; times < 4; times++) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (i > 0) {
							// Move blocks
							if (grid[i - 1][j] == 0) {
								grid[i - 1][j] = grid[i][j];
								grid[i][j] = 0;
							}
							// Combine blocks only if column hasn't combined before in Move() method
							if (grid[i - 1][j] == grid[i][j] && combineOnce[j] && grid[i][j] > 0) {
								grid[i - 1][j] = 0;
								grid[i][j] *= 2;
								score += grid[i][j];
								combineOnce[j] = false;
								try {
									if (grid.at(i + 2).at(j) == grid.at(i + 1).at(j)) {
										grid.at(i + 2).at(j) = 0;
										grid.at(i + 1).at(j) *= 2;
										score += grid[i + 1][j];
									}
								}
								catch (const std::out_of_range & e) {

								}
							}
						}
					}
				}
			}
		}
		else if (GetKey(olc::Key::DOWN).bPressed) {
			for (int times = 0; times < 4; times++) {
				for (int i = 3; i >= 0; i--) {
					for (int j = 0; j < 4; j++) {
						if (i < 3) {
							// Move blocks
							if (grid[i + 1][j] == 0) {
								grid[i + 1][j] = grid[i][j];
								grid[i][j] = 0;
							}
							// Combine blocks only if column hasn't combined before in Move() method
							if (grid[i + 1][j] == grid[i][j] && combineOnce[j] && grid[i][j] > 0) {
								grid[i + 1][j] = 0;
								grid[i][j] *= 2;
								score += grid[i][j];
								combineOnce[j] = false;
							}
							
						}
					}
				}
			}
		}
		else if (GetKey(olc::Key::LEFT).bPressed) {
			for (int times = 0; times < 4; times++) {
				for (int j = 0; j < 4; j++) {
					for (int i = 0; i < 4; i++) {
						if (j > 0) {
							if (grid[i][j - 1] == 0) {
								grid[i][j - 1] = grid[i][j];
								grid[i][j] = 0;
							}
							// Combine blocks only if column hasn't combined before in Move() method
							if (grid[i][j - 1] == grid[i][j] && combineOnce[i] && grid[i][j] > 0) {
								grid[i][j - 1] = 0;
								grid[i][j] *= 2;
								score += grid[i][j];
								combineOnce[i] = false;
								try {
									if (grid.at(i).at(j + 2) == grid.at(i).at(j + 1)) {
										grid.at(i).at(j + 2) = 0;
										grid.at(i).at(j + 1) *= 2;
										score += grid[i][j + 1];
									}
								}
								catch (const std::out_of_range & e) {

								}
							}
						}
					}
				}
			}
		}
		else if (GetKey(olc::Key::RIGHT).bPressed) {
			for (int times = 0; times < 4; times++) {
				for (int j = 3; j >= 0; j--) {
					for (int i = 0; i < 4; i++) {
						if (j < 3) {
							if (grid[i][j + 1] == 0) {
								grid[i][j + 1] = grid[i][j];
								grid[i][j] = 0;
							}
							if (grid[i][j + 1] == grid[i][j] && combineOnce[i] && grid[i][j] > 0) {
								grid[i][j + 1] = 0;
								grid[i][j] *= 2;
								score += grid[i][j];
								combineOnce[i] = false;
								try {
									if (grid.at(i).at(j - 2) == grid.at(i).at(j - 1)) {
										grid.at(i).at(j - 2) = 0;
										grid.at(i).at(j - 1) *= 2;
										score += grid[i][j - 1];
									}
								}
								catch (const std::out_of_range & e) {

								}
							}
						}
					}
				}
			}
		}
	}

	bool AddBlock(std::array<std::array<int, 4>, 4>& newGrid) {
		srand(std::time(0));
		short seedmeta1 = rand() % 1000;
		srand(seedmeta1);
		seedmeta1 = rand() % 1000;
		srand(seedmeta1);
		seedmeta1 = rand() % 1000;
		srand(seedmeta1);
		seedmeta1 = rand() % 1000;
		srand(seedmeta1);
		seedmeta1 = rand() % 1000;
		srand(seedmeta1);

		bool allFull;

		short seed = rand() % 16;

		short seedStart = 0;
		int height;
		int width;
		width = height = 0;

		do {
			allFull = true;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (grid[i][j] == 0)
						allFull = false;
				}
			}
			if (newGrid[height][width] == 0 && !allFull) {
				if (width < 3)
					width++;
				else {
					width = 0;
					if (height == 3)
						height = 0;
					else
						height++;
				}
				seedStart++;
			}
			else if (newGrid[height][width] != 0 && !allFull) {
				if (width < 3)
					width++;
				else {
					width = 0;
					if (height == 3)
						height = 0;
					else
						height++;
				}
			}
		} while (seed != seedStart && !allFull);
		
		if (width > 0)
			width--;
		else if (width == 0) {
			width = 3;
			if (height == 0)
				height = 3;
			else
				height--;
		}
		if (newGrid[height][width] == 0) {
			newGrid[height][width] = 2;
			return true;
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (grid[i][j] == 0) {
						std::cout << "Forced to place first block" << std::endl;
						grid[i][j] = 2;
						return true;
					}
				}
			}
			return false;
		}
	}

	void DrawGrid() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// Do Color
				switch (grid.at(i).at(j)) {
				case 0:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(255, 255, 255)); // white
					break;
				case 2:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(245, 245, 66)); // yellow
					break;
				case 4:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(141, 245, 66)); // lime green
					break;
				case 8:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(66, 245, 153)); // greenish blue
					break;
				case 16:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(66, 245, 239)); // cyan
					break;
				case 32:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(66, 135, 245)); // blue
					break;
				case 64:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(129, 66, 245)); // purple
					break;
				case 128:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(209, 66, 245)); // dark purple
					break;
				case 256:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(245, 66, 194)); // pink
					break;
				case 512:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(245, 66, 66)); // red
					break;
				case 1024:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(245, 156, 66)); // orange
					break;
				case 2048:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(255, 102, 102)); // salmon
					break;
				case 4096:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(133, 163, 224)); // periwinkle
					break;
				case 8192:
					FillRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::Pixel(230, 255, 230)); // grass
					break;
				}
				// Do Number
				switch (grid.at(i).at(j)) {
				case 2:
				case 4:
				case 8:
					DrawString((j * (SCREENWIDTH() / 4) + (SCREENWIDTH() / 8) - 4), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4)) + (SCREENWIDTH() / 8) - 4), std::to_string(grid[i][j]), olc::BLACK);
					break;
				case 16:
				case 32:
				case 64:
					DrawString((j * (SCREENWIDTH() / 4) + (SCREENWIDTH() / 8) - 8), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4)) + (SCREENWIDTH() / 8) - 4), std::to_string(grid[i][j]), olc::BLACK);
					break;
				case 128:
				case 256:
				case 512:
					DrawString((j * (SCREENWIDTH() / 4) + (SCREENWIDTH() / 8) - 12), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4)) + (SCREENWIDTH() / 8) - 4), std::to_string(grid[i][j]), olc::BLACK);
					break;
				case 1024:
				case 2048:
				case 4096:
				case 8192:
					DrawString((j * (SCREENWIDTH() / 4) + (SCREENWIDTH() / 8) - 16), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4)) + (SCREENWIDTH() / 8) - 4), std::to_string(grid[i][j]), olc::BLACK);
					break;
				}
				DrawRect((j * (SCREENWIDTH() / 4)), (topBarSize + (i * ((SCREENHEIGHT() - topBarSize) / 4))), (SCREENWIDTH() / 4), (SCREENWIDTH() / 4), olc::BLACK);
			}
		}
	}

	void DrawHeader() {
		std::string stringScore = "SCORE: ";
		stringScore += std::to_string(score);

		DrawString((SCREENWIDTH() / 32), topBarSize / 2 - 12, stringScore, olc::WHITE);
		if (hasWon) {
			DrawString(SCREENWIDTH() * 0.8, topBarSize / 2 - 12, "Win", olc::DARK_MAGENTA);
			DrawString(SCREENWIDTH() * 0.83, topBarSize / 2 - 12 + 8, "is", olc::DARK_MAGENTA);
			DrawString(SCREENWIDTH() * 0.8, topBarSize / 2 - 12 + 16, "you", olc::DARK_MAGENTA);
		}
	}

	bool Is2048(std::array<std::array<int, 4>, 4> grid) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (grid.at(i).at(j) == 2048) {
					return true;
				}
			}
		}
		return false;
	}
}; 

