#include <stdio.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <io.h>
#include <process.h>

#define WIDTH 256
#define HEIGHT 96
#define FULL_WIDTH 3584

//1 Block = 16

//Type WORD
WORD color[HEIGHT * WIDTH];

//Type int
int MapMovX = 0;

//Type char



//Function
void Coloring(int order);
void setup();
void Write();

//Thread & HANDLE
void Input(void *args);

int main()
{
	int i, j = 0, delay = 30, calcfps1 = 0, calcfps2 = 0;
	char c[10], text[20] = "title FPS : ", cat[20];
	setup();
	_beginthread(Input, 0, (void*)0);
	i = clock();
	j = clock();
	while(1)
	{
		Coloring(0);
		Write();
		//MapMovX++;
		calcfps1++;
		if(MapMovX + WIDTH > FULL_WIDTH)
		{
			return 0;
		}
		if(clock() - i > 500)
		{
			cat[0] = '\0';
			itoa((calcfps1 - calcfps2) * 2, c, 10);
			if(calcfps1 - calcfps2 > 16)
			{
				delay++;
			}
			else if(calcfps1 - calcfps2 < 15)
			{
				delay--;
			}
			calcfps2 = calcfps1;
			strcat(cat, text);
			strcat(cat, c);
			system(cat);
			i += 500;
		}
		while(clock() - j < delay)
		{
			Sleep(1);
		}
		j = clock();
	}
	
}

//height 79 -> floor 
void Coloring(int order)
{
	int width, height, i, j;
	for(height = 0;height < HEIGHT;height++)
	{
		for(width = 0 + MapMovX;width < MapMovX + WIDTH;width++)
		{
			
			color[height * WIDTH + width - MapMovX] = array_high[height][width] | array_low[height][width] * 16;
		}
	}
}

void Write()
{
	COORD coord = {0, 0};
	DWORD written[HEIGHT * WIDTH];
	WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color, WIDTH * HEIGHT, coord, written);
}

void setup()
{
	int width, height, x, y;
	_getch();
	_setmode(_fileno(stdout), _O_U16TEXT);
	system("mode 256, 97");
	
	for(height = 0;height < HEIGHT;height++)
	{
		for(width = 0;width < WIDTH;width++)
		{
			wprintf(L"\u2580");
		}
		wprintf(L"\n");
	}
}

void Input(void *args)
{
	int i;
	while(1)
	{
		i = clock();
		if(GetAsyncKeyState('W') & 0x8000)
		{
			
		}
		if(GetAsyncKeyState('A') & 0x8000)
		{
			MapMovX = (MapMovX <= 0 ? MapMovX : MapMovX - 1);
		}
		if(GetAsyncKeyState('S') & 0x8000)
		{
			
		}
		if(GetAsyncKeyState('D') & 0x8000)
		{
			MapMovX++;
		}
		while(clock() - i <= 3)
		{
			Sleep(1);
		}
	}
}