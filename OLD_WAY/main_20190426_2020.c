#include <stdio.h>
#include <fcntl.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <io.h>
#include <process.h>

#define WIDTH 256
#define HEIGHT 96
#define FULL_WIDTH 3584

//1 Block = 16

//Type WORDd
WORD color[HEIGHT * WIDTH];

//Type int
int MapMovX = 0;
int CanIJump = 0;

//Type char
char E_Location[192][3584] = {0};


//Function
void Coloring(int order);
void setup();
void Write();
int MovE(int valueX, int valueY);
void Gravity();

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
		calcfps1++;
		if(MapMovX + WIDTH > FULL_WIDTH)
		{
			return -1;
		}
		if(clock() - i > 1000)
		{
			cat[0] = '\0';
			itoa((calcfps1 - calcfps2), c, 10);
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

//height 79 (158) -> floor 
void Coloring(int order)
{
	int width, height, i, j;
	for(height = 0;height < HEIGHT;height++)
	{
		for(width = 0 + MapMovX;width < MapMovX + WIDTH;width++)
		{
			color[height * WIDTH + width - MapMovX] = (E_Location[height * 2][width] != 0 ? E_Location[height * 2][width] : (array_high[height][width] == 16 ? 0 : array_high[height][width])) | (E_Location[height * 2 + 1][width] != 0 ? E_Location[height * 2 + 1][width] : (array_low[height][width] == 16 ? 0 : array_low[height][width])) << 4;
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
	printf("���ǻ��� : \n\CPU ��뷮�� ����� �Ƹ��ٿ� �� �ֽ��ϴ�.\n�̴� �� ���α׷��� ȭ�鿡 ������ִ� �ܼ�ȣ��Ʈ�� �Դ°��Դϴ�.\n\n�ܼ� �۾� ����� 8��Ʈ�� �������ּ���.\n\"���ǻ���\"�� '��'�� �ٷ� ���� \"�������α׷�\" �������� Ŭ�����ּ���.\n�Ӽ�-�۲�-ũ�⸦ 8���� ����\n\n�� ���α׷��� 1920*1080 100������ ����ȭ �Ǿ��ֽ��ϴ�.\n125���������� ȣȯ�Ǵ°��� Ȯ�� �Ͽ����� 100�������� �����ϴ°��� ��õ�帳�ϴ�.\n������Ű-����-�ý���-���÷���-�ؽ�Ʈ, �� �� ��Ÿ �׸��� ũ�� ���� -> 100%���� ����\n\n�ƹ�Ű�� ���� ����ϼ���!");
	_getch();
	system("mode 256, 97");
	_setmode(_fileno(stdout), _O_U16TEXT);
	for(height = 144;height <= 159;height++)
	{
		for(width = 0;width <= 11;width++)
		{
			E_Location[height][width] = 1;
		}
	}
	E_Location[144][0] = 15;
	for(height = 0;height < HEIGHT;height++)
	{
		for(width = 0;width < WIDTH;width++)
		{
			wprintf(L"\u2580");
		}
		wprintf(L"\n");
	}
}

int MovE(int valueX, int valueY)
{
	int width, height;
	char E_Location_B[192][3584] = {0};
	//Overwrite
	for(height = 0;height < HEIGHT * 2;height++)
	{
		for(width = 0;width < FULL_WIDTH;width++)
		{
			E_Location_B[height][width] = E_Location[height][width];
		}
	}
	if(valueX > 0)
	{
		for(height = 0;height < HEIGHT * 2;height++)
		{
			for(width = FULL_WIDTH - 1;width >= 0;width--)
			{
				if(E_Location_B[height][width] != 0)
				{
					E_Location_B[height][width + valueX] = E_Location_B[height][width];
					E_Location_B[height][width] = 0;
				}
			}
		}
	}
	else if(valueX < 0)
	{
		for(height = 0;height < HEIGHT * 2;height++)
		{
			for(width = 0;width < FULL_WIDTH;width++)
			{
				if(E_Location_B[height][width] != 0)
				{
					if(width <= MapMovX)
					{
						return 1;
					}
					E_Location_B[height][width + valueX] = E_Location_B[height][width];
					E_Location_B[height][width] = 0;
				}
			}
		}
	}
	if(valueY > 0)
	{
		for(height = 0;height < HEIGHT * 2;height++)
		{
			for(width = 0;width < FULL_WIDTH; width++)
			{
				if(E_Location_B[height][width] != 0)
				{
					if(height - valueY < 1)
					{
						return 1;
					}
					E_Location_B[height - valueY][width] = E_Location_B[height][width];
					E_Location_B[height][width] = 0;
				}
			}
		}
	}
	else if(valueY < 0)
	{
		for(height = HEIGHT * 2 - 1;height >= 0;height--)
		{
			for(width = 0;width < FULL_WIDTH; width++)
			{
				if(E_Location_B[height][width] != 0)
				{
					E_Location_B[height - valueY][width] = E_Location_B[height][width];
					E_Location_B[height][width] = 0;
				}
			}
		}
	}
	//Block
	for(height = 0;height < HEIGHT * 2;height++)
	{
		for(width = 0;width < FULL_WIDTH;width++)
		{
			if(E_Location_B[height][width] == 1 && array_high[height / 2][width] != 11 && height & 1 == 0)
			{
				return 1;
			}
			else if(E_Location_B[height][width] == 1 && array_low[height / 2][width] != 11 && height & 1 == 1)
			{
				return 1;
			}
		}
	}
	//Overwrite
	for(height = 0;height < HEIGHT * 2;height++)
	{
		for(width = 0;width < FULL_WIDTH;width++)
		{
			E_Location[height][width] = E_Location_B[height][width];
		}
	}
	//MapMove
	for(height = 0;height < HEIGHT * 2;height++)
	{
		for(width = 0;width < FULL_WIDTH;width++)
		{
			if(E_Location[height][width] == 1)
			{
				if(width - MapMovX > WIDTH / 2)
				{
					MapMovX++;
				}
			}
		}
	}
	return 0;
}

void Input(void *args)
{
	int i, j, tmp = 0;
	while(1)
	{
		i = clock();
		if((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000) && CanIJump)
		{
			tmp += 13;
			MovE(0, -6);
			CanIJump = MovE(0, 6);
		}
		if(GetAsyncKeyState('A') & 0x8000)
		{
			MovE(-5, 0);
		}
		if(GetAsyncKeyState('S') & 0x8000)
		{
			//MovE(0, -2);
		}
		if(GetAsyncKeyState('D') & 0x8000)
		{
			//MapMovX++;
			MovE(5, 0);
		}
		if(tmp > 0)
		{
			tmp--;
			if(MovE(0, 6))
			{
				tmp = 0;
			}
		}
		else
		{
			Gravity();
		}
		while(clock() - i < 30)
		{
			Sleep(1);
		}
	}
}

void Gravity()
{
	CanIJump = MovE(0, -6);
}