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
int MapMovX = 1;
int PosX = 0;
int PosY = 71;

//Type char

char E_Location[16][12] = {16, 16, 16, 12, 12, 12, 12, 12, 16, 16, 16, 16, 16, 16, 12, 12, 12, 12, 12, 12, 12, 12, 12, 16, 16, 16, 6, 6, 6, 14, 14, 6, 14, 16, 16, 16, 16, 6, 14, 6, 14, 14, 14, 6, 14, 14, 14, 16, 16, 6, 14, 6, 6, 14, 14, 14, 6, 14, 14, 14, 16, 6, 6, 14, 14, 14, 14, 6, 6, 6, 6, 16, 16, 16, 16, 14, 14, 14, 14, 14, 14, 14, 16, 16, 16, 16, 6, 6, 12, 6, 6, 6, 16, 16, 16, 16, 16, 6, 6, 6, 12, 6, 6, 12, 6, 6, 6, 16, 6, 6, 6, 6, 12, 12, 12, 12, 6, 6, 6, 6, 14, 14, 6, 12, 14, 12, 12, 14, 12, 6, 14, 14, 14, 14, 14, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 16, 16, 12, 12, 12, 16, 16, 12, 12, 12, 16, 16, 16, 6, 6, 6, 16, 16, 16, 16, 6, 6, 6, 16, 6, 6, 6, 6, 16, 16, 16, 16, 6, 6, 6, 6};

//Function
void Coloring(int order);
void setup();
void Write();
int MovE(int valueX, int valueY);
void Gravity();
void MovE_Safe(int valueX, int valueY);
int CanIJump();

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
			color[height * WIDTH + width - MapMovX] = (array_high[height][width] == 16 ? 0 : array_high[height][width]) | (array_low[height][width] == 16 ? 0 : array_low[height][width]) << 4;
		}
	}
	for(height = 0;height < 16;height += 2)
	{
		for(width = 0;width < 12;width++)
		{
			if((height / 2 + PosY) * WIDTH + width + PosX - MapMovX >= HEIGHT * WIDTH - 1)
			{
				continue;
			}
			color[(height / 2 + PosY) * WIDTH + width + PosX - MapMovX] = (E_Location[height][width] != 16 ? E_Location[height][width] : array_high[height / 2 + PosY][width + PosX - MapMovX]) | (E_Location[height + 1][width] != 16 ? E_Location[height + 1][width] : array_low[height / 2 + PosY][width + PosX - MapMovX]) << 4;
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
	printf("���ǻ��� : \nCPU ��뷮�� ����� �Ƹ��ٿ� �� �ֽ��ϴ�.\n�̴� �� ���α׷��� ȭ�鿡 ������ִ� �ܼ�ȣ��Ʈ�� �Դ°��Դϴ�.\n\n�ܼ� �۾� ����� 8��Ʈ�� �������ּ���.\n\"���ǻ���\"�� '��'�� �ٷ� ���� \"�������α׷�\" �������� Ŭ�����ּ���.\n�Ӽ�-�۲�-ũ�⸦ 8���� ����\n\n�� ���α׷��� 1920*1080 100������ ����ȭ �Ǿ��ֽ��ϴ�.\n125���������� ȣȯ�Ǵ°��� Ȯ�� �Ͽ����� 100�������� �����ϴ°��� ��õ�帳�ϴ�.\n������Ű-����-�ý���-���÷���-�ؽ�Ʈ, �� �� ��Ÿ �׸��� ũ�� ���� -> 100%���� ����\n\n�ƹ�Ű�� ���� ����ϼ���!");
	_getch();
	system("mode 256, 97");
	_setmode(_fileno(stdout), _O_U16TEXT);
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
	for(height = 0;height < 8;height++)
	{
		for(width = 0;width < 12;width++)
		{
			if(height + PosY - valueY > HEIGHT - 1)
			{
				exit(0);
			}
			if(array_high[height + PosY - valueY][width + PosX + valueX] != 11 || array_low[height + PosY - valueY][width + PosX + valueX] != 11 || height + PosY - valueY < 0 || width + PosX + valueX < 0 || PosX + valueX - MapMovX < 0)
			{
				return 1;
			}
		}
	}
	PosY -= valueY;
	PosX += valueX;
	MapMovX = (PosX + 6 - WIDTH / 2 >= 0 && PosX + 6 - WIDTH / 2 > MapMovX ? PosX + 6 - WIDTH / 2 : MapMovX);
	return 0;
}

void MovE_Safe(int valueX, int valueY)
{
	if(!MovE(valueX, valueY))
	{
		return;
	}
	while(!(valueX == 0 && valueY == 0))
	{
		if(!MovE((valueX > 0 ? --valueX : (valueX < 0 ? ++valueX : valueX)), (valueY > 0 ? --valueY : (valueY < 0 ? ++valueY : valueY))))
		{
			break;
		}
	}
	return;
}

void Input(void *args)
{
	int i = 0, j, tmp = 0;
	while(1)
	{
		if(clock() - i < 15)
		{
			continue;
		}
		i = clock();
		if((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000) && CanIJump() && tmp == -7)
		{
			tmp = 22;
		}
		if(GetAsyncKeyState('A') & 0x8000)
		{
			MovE_Safe(-2, 0);
		}
		if(GetAsyncKeyState('S') & 0x8000)
		{
			//MovE(0, -2);
		}
		if(GetAsyncKeyState('D') & 0x8000)
		{
			//MapMovX++;
			MovE_Safe(2, 0);
		}
		if(tmp > -7)
		{
			tmp--;
			if(tmp > 0)
			{
				if(MovE(0, 2))
				{
					MovE(0, 1);
					tmp = -3;
				}
			}
		}
		else
		{
			Gravity();
		}
	}
}

void Gravity()
{
	MovE_Safe(0, -2);
}

int CanIJump()
{
	if(MovE(0, -1))
	{
		return 1;
	}
	MovE(0, 1);
	return 0;
}