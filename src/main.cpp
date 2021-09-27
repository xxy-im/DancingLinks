/*
 * @Author: xxy
 * @Date: 2021-09-27 22:55:40
 * @Description: main.cpp
 */
#include "DancingLinks.h"

static int s[M][N] = 
{
	{0, 0, 1, 0, 1, 0, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 1, 0},
	{1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1},
	{0, 0, 0, 1, 1, 0, 1}
};

int main()
{
	DancingLinks dl(s);
	dl.DLX();

	return 0;
}