// Calling main libraries
#include <iostream>
#include <thread>
#include <vector>

// Calling namespace
using namespace std;

// Calling extra libraries
#include <stdio.h>
#include <windows.h>

// Defining the screen to 80*30
int nScreenWidth = 80;
int nScreenWidth = 30;

wstring tetromino[7];

int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

int Rotate(int px, int py, int r) {
	int pi = 0;
	switch (r % 4) {
		// 0 degrees
		case 0:
			pi = py * 4 + px;
			break;
		case 1:
			pi = 12 + py - (px * 4);
			break;
		case 2:
			pi = 15 - (py * 4);
			break;
		case 3:
			pi = 3 - py + (px * 4);
			break;
	}

	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {
	// Let's check if every cell is full
	for (int py = 0; py < 4; py++) {
		for (int py = 0; py < 4; py++) {
			// Input index into de piece
			int pi = Rotate(px, py, nRotation);

			if (nPosX + px >= 0 && nPosX + px < nFieldHeight) {
				if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
					return false;
			}
		}
	}
}