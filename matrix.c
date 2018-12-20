#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define CIRCLE "◯"
#define BLACKCIRCLE "⬤"
#define BALLS 2

struct led
{
	/*
	 * 8x8 matrix, we only need 3 bits for each x/y position
	 * 1 byte per led
	 * 1 bit  -> led on/off
	 * 3 bits -> x pos (0-7)
	 * 3 bits -> y pos (0-7)
	 * 1 bit  -> unused
	*/
	unsigned char enabled:1;
	unsigned char x:3;
	unsigned char y:3;
	unsigned char unused:1;
} matrix[8][8];

struct ball
{
	unsigned char x:3;
	unsigned char y:3;
	unsigned char dirx:1; /* 0 = left, 1 = right */
	unsigned char diry:1; /* 0 = down, 1 = up */
} balls[BALLS];

void
printleds(void)
{
	printf("\0337");
	printf("%s", "\033[8;0F");
	printf("%s", "\033[0J");
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			printf("%s ", (matrix[x][y].enabled) ? BLACKCIRCLE : CIRCLE);
		}
		puts("");
	}
	printf("\0338");
}

void
playball()
{
	for (int i = 0; i < BALLS; i++)
	{
		if (balls[i].x == 0)
			balls[i].dirx = 1;
		else if (balls[i].x == 7)
			balls[i].dirx = 0;
		
		if (balls[i].y == 7)
			balls[i].diry = 1;
		else if (balls[i].y == 0)
			balls[i].diry = 0;

		if (balls[i].dirx == 1)
			balls[i].x++;
		else
			balls[i].x--;

		if (balls[i].diry == 1)
			balls[i].y--;
		else
			balls[i].y++;
	}

}

int
main(void)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			matrix[x][y].enabled = 0;
			matrix[x][y].x = x;
			matrix[x][y].y = y;
		}
	}
	printf("\n\n\n\n\n\n\n\n\n");
	int x, y = 0;
	srand(time(NULL));
	for (int i = 0; i < BALLS; i++)
	{
		balls[i].x = rand() % 7;
		balls[i].y = rand() % 7;
		balls[i].dirx = rand() % 2;
		balls[i].diry = rand() % 2;
	}
	while (1)
	{
		/*
		matrix[0][y].enabled = !matrix[0][y].enabled;
		matrix[2][y].enabled = !matrix[2][y].enabled;
		matrix[4][y].enabled = !matrix[4][y].enabled;
		matrix[6][y].enabled = !matrix[6][y].enabled;
		matrix[8][y].enabled = !matrix[8][y].enabled;
		*/
		for (int i = 0; i < BALLS; i++)
			matrix[balls[i].y][balls[i].x].enabled = 0;
		playball();
		for (int i = 0; i < BALLS; i++)
			matrix[balls[i].y][balls[i].x].enabled = 1;
		printleds();
		x++;
		y++;
		if (x == 8 || y == 8)
		{
			x = 0;
			y = 0;
		}
		usleep(100000);
	}
	return 0;
}
