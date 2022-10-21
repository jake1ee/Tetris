#include <iostream>
#include <Windows.h>

using namespace std;

wstring tetromino[7];

int nFeildWidth = 12;
int nFeildHeight = 18;

int nScreenWidth = 80;	//Console Screen Size X
int nScreenHeight = 30;	//Console Screen Size Y

unsigned char* pFeild = nullptr;

int Rotate(int px, int py, int r)
{

	int pi = 0;
	switch (r % 4)
	{
	case 0: 
		pi = py * 4 + px;// 0 degree Rotation
		break;
	case 1: 
		pi = 12 + py - (px * 4);	// 90 degree Rotation
		break;
	case 2: 
		pi =  15 - (py * 4) - px;	// 180 degree Rotation
		break;
	case 3: 
		pi = 3 - py + (px * 4);	// 270 degree Rotation
		break;
	}
	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	// All Field cells > 0 are occupied
	for (int Px = 0; Px < 4; Px++)
		for (int Py = 0; Py < 4; Py++)
		{

			// Get Index Piece
			int pi = (Rotate(Px, Py, nRotation));

			//Get Index Field
			int fi = (nPosY + Py) * nFeildWidth + (nPosX + Px);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
			if (nPosX + Px >= 0 && nPosX + Px < nFeildWidth)
			{
				if (nPosY + Py >= 0 && nPosY + Py < nFeildWidth)
				{
					// In Bounds so do collision check
					if (tetromino[nTetromino][pi] == L'X' && pFeild[fi] != 0)
					return false;
				}
			}
		}

	return true;
}

int main()
{

	//Tetromino 
	tetromino[0].append(L"..X...X...X...X.");
	tetromino[1].append(L"..X..XX..X......");
	tetromino[2].append(L".X...XX...X.....");
	tetromino[3].append(L".....XX..XX.....");
	tetromino[4].append(L"..X..XX...X.....");
	tetromino[5].append(L"......X...X..XX.");
	tetromino[6].append(L".....X...X...XX.");

	// Create Screen Buffer	
	wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenHeight * nScreenWidth; i++) screen[i] = L' ';
	HANDLE hconsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hconsole);
	DWORD dwByteswritten = 0;

	// Create Play Field Buffer
	pFeild = new unsigned char[nFeildHeight * nFeildWidth];

	// Board Boundary 
	for (int x = 0; x < nFeildWidth; x++)
	{
		for (int y = 0; y < nFeildHeight; y++)
		{
			pFeild[y * nFeildWidth + x] = (x == 0 || x == nFeildWidth - 1 || y == nFeildHeight - 1) ? 9 : 0;
		}
	}

	// Game Logic
	bool bGameOver = false;

	int nCurrentPiece = 0,
		nCurrentRotation = 0,
		nCurrentX = nFeildWidth / 2,
		nCurrentY = 0;


	while (!bGameOver)
	{

		//Draw Field
		for (int x = 0; x < nFeildWidth; x++)
		{
			for (int y = 0; y < nFeildHeight; y++)
			{
			/*	screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pFeild[y * nFeildWidth + x]];*/
			}
		}

		//Draw Current Piece
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (tetromino[nCurrentPiece][Rotate(x, y, nCurrentRotation)] == L'X')
					screen[(nCurrentY + y + 2) * nScreenWidth + (nCurrentX + x + 2)] = nCurrentPiece + 65;
			}
		}

		//Display Fram
		WriteConsoleOutputCharacter(hconsole, screen, nScreenWidth * nScreenHeight, { 0,0 },&dwByteswritten);
	}
}