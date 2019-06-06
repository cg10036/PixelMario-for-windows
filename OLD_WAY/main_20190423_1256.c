#include <stdio.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <io.h>

#define NUM 2
#define WIDTH 256
#define HEIGHT 96
#define FULL_WIDTH 3584
#define THREAD 1

static HANDLE hBuffer[NUM];
wchar_t array[HEIGHT][FULL_WIDTH];

WORD color[HEIGHT * WIDTH];

int TEMP = 0;


void Threading(int order);
void setup();
void Write();

int main()
{
	int i;
	char c[10];
	_setmode(_fileno(stdout), _O_U16TEXT);
	_getch();
	system("mode 256, 97");
	setup();
	i = clock();
	while(1)
	{
		Threading(0);
		//Threading(1);
		Write();
		TEMP++;
		if(TEMP + WIDTH > FULL_WIDTH)
		{
			return 0;
		}
		/*if(clock() - i > 1000)
		{
			itoa(TEMP, c, 10);
			MessageBox(NULL, c, "TEST", MB_OK); // Frame Per Second
		}*/
	}
	
}

void Threading(int order)
{
	int width, height;
	for(height = (HEIGHT / THREAD) * order;height < (THREAD == (order + 1) ? HEIGHT : (HEIGHT / THREAD) * (order + 1));height++)
	{
		for(width = 0 + TEMP;width < TEMP + WIDTH;width++)
		{
			color[height * WIDTH + width - TEMP] = array_high[height][width] | array_low[height][width] * 16;
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
	int width, height;
	for(height = 0;height < HEIGHT;height++)
	{
		for(width = 0;width < WIDTH;width++)
		{
			wprintf(L"\u2580");
		}
		wprintf(L"\n");
	}
}