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

	return true;
}

int main() {
	// Now we create the screen buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Tetronimos 4x4
	tetromino[0].append(L"..X...X...X...X."); 
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	// Game algorithm
	bool bKey[4];
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;
	int nSpeed = 20;
	int nSpeedCount = 0;
	int bForceDown = false;
	int bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	while (!bGameOver) {
		// Timer
		this_thread::sleep_for(50ms);
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// Gamer input
		for(int k = 0; k < 4; k++)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

		// Player movements
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotate, but latch to stop wild spinning of the piece
		if (bKey[3])
		{
			nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
			bRotateHold = true;

		// Now we force the piece down the field it's the timer is up
		if(bForceDown) {
			// Up the level every fifty pieces, more tetrominos! wiii! yay!
			nSpeedCount = 0;
			nPieceCount++;
			if (nPieceCount % 50 == 0)
				if (nSpeed >= 10) nSpeed--;

			// Testing the piece for latching down, if not keep going
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++; // There is not latching, keep going my friend!
			else {
				// Can't keep going, lock the piece and shoot to trill!!
				for(int px = 0; px < 4; px++)
					for(int py = 0; py < 4; py++)

			}
		}

	}
}