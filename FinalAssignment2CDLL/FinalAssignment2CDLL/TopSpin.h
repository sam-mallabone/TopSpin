#pragma once
#include <iostream>
#include "CircularDoublyLinkedList.h"
#include <ostream>

class TopSpinADT {
public:
	// shifts the pieces a given number of times to the left
	virtual void shiftLeft(unsigned int n) = 0;
	//shifts the pieces a given number of times to the right
	virtual void shiftRight(unsigned int j) = 0;
	//reverses the pieces in the spin mechanism, IE if the 4 in the mechanism
	//are 1,4,3,6 we will have 6,3,4,1
		virtual void spin() = 0;
	//checks to see if the puzzle is solved that is to say the pieces are in
	//numerical order 1 - 20
		virtual bool isSolved() = 0;
};
class TopSpin : public TopSpinADT //new class publicly inherits from the TopSpinADT class
{
public: 
	virtual void shiftLeft(unsigned int n); //These functions are declared to overide the pure virtual functions in the TopSpinADT class
	virtual void shiftRight(unsigned int j);
	virtual void spin();
	virtual bool isSolved();
	TopSpin(); //other function prototypes
	TopSpin(unsigned int size, unsigned int spinSize); //a constructor
	~TopSpin(); //destructor
	

private:
	int _spinSize; //member variable of the TopSpin game
	int _boardSize;
	CircularDoublyLinkedList<int> board; //an instance of CDLL is one of the member variables

public:
	inline friend std::ostream& operator<< (std::ostream&, const TopSpin&); //function prototype of the operator overloader

};


std::ostream& operator<< (std::ostream& os, const TopSpin& ts) //the function definition of overloading the << operator
{

	os << "( "; //these brackets are for printing which numbers are within the "spinner"
	for (int j = 1; j < 5; j++)
	{
		std::cout << ts.board.retrieve(j) << " ";
	}
	os << ") ";

	//printing the rest of the numbers in the game
	for (int i = 5; i < ts.board.m_size+1; i++) 
	{


		os << ts.board.retrieve(i) << " ";
	}

	return os;
}




