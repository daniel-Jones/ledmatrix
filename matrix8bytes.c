/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define CIRCLE "◯"
#define BLACKCIRCLE "⬤"
#define BALLS 2

uint64_t matrix;

void
printleds(void)
{
	printf("\0337");
	printf("%s", "\033[8;0F");
	printf("%s", "\033[0J");
	/* loop through each byte of matrix */
	int c = 56;
	uint8_t byte;
	while (c >= 0)
	{
		byte = (matrix >> c) & 0xff;
		printf("%s %s %s %s %s %s %s %s\n",
			(byte & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 1) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 2) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 3) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 4) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 5) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 6) & 0x01) ? BLACKCIRCLE : CIRCLE,
			((byte >> 7) & 0x01) ? BLACKCIRCLE : CIRCLE);
		c -= 8;
	}
	printf("\0338");
}

int
main(void)
{
	printf("\n\n\n\n\n\n\n\n\n");
	srand(time(NULL));
	matrix = 0xff00000000000000;
	while (1)
	{
		matrix>>=8;
		if (matrix == 0)
			matrix = 0xff00000000000000;
		printleds();
		usleep(200000);
	}
	return 0;
}
