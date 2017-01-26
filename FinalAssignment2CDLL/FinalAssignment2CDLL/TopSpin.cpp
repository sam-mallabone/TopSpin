#include "TopSpin.h"
#include <iostream>

TopSpin::TopSpin() //default constructor for the game topspin
{
	_spinSize = 4;
	_boardSize = 20;
	//This for loop adds in 20 heads 
	for (int i = _boardSize; i > 0; i--)
	{
		board.addHead(i);
	}

}

TopSpin::TopSpin(unsigned int size, unsigned int spinSize) //regular constructor for the game Topspin. Sets the values of _spinSize and _boardSize
{
	_spinSize = spinSize;
	_boardSize = size;

	for (int i = _boardSize; i > 0; i--)
	{
		board.addHead(i);
	}

}

TopSpin::~TopSpin(){}  //The destructor the TopSpin class

void TopSpin::shiftLeft(unsigned int n) //this function calls the CDLL header to shift the pieces to the left
{
	board.shiftLeft(n);
}

void TopSpin::shiftRight(unsigned int j)  //this function calls the CDLL header to shift the pieces to the right
{
	board.shiftRight(j);
}

void TopSpin::spin()
{
	for (int b = 1; b <= _spinSize / 2; b++) //changing the two far values in the spinner than moving inward
	{

		board.swap(b, _spinSize - b + 1);
		
	}
}

bool TopSpin::isSolved()
{
	return board.isSolved(_boardSize); //sending the isSolved function the size of the board to see if 
}