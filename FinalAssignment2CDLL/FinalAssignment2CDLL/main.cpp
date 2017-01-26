#include<iostream>
#include<cstdlib>
#include<ctime>
#include "TopSpin.h"
using namespace std;

int main()
{

	int option = 0;
	int shuffleNum = 0; //the value will be set by the user depending on how many times they wish to shuffle
	srand(time(NULL)); //for the initiliaziation of the game with the number of shuffles. Makes sure rand() is truly random
	TopSpin ts(20, 4);   //creates an instance of TopSpin with a game size of 20 and a spin size of 4
	cout << "Hello! Welcome to TopSpin" << endl;  
	cout << "How many times would you like to randomly shuffle the board? Please enter a positive value: ";
	cin >> shuffleNum; //asks user for number of shuffles they want than inputs it into the variable shuffleNum
	cout << endl;
	while (shuffleNum < 0) //checks that the user inputted a positive number
	{
		cout << "Error: Please enter a positive number of shuffles: ";
		cin >> shuffleNum;
	}

	cout << "You entered " << shuffleNum << " times shuffled" << endl << endl;;
	

		for (int i = 0; i < shuffleNum; i++) //randomly shifts the board a number of times then spins. Goes through this for loop however many times the user inputted
		{
			int num = 0;
			num = rand() % 20;
			ts.shiftLeft(num);
			ts.spin();
		}
	

	cout << "Here is your starting board" << endl;
	cout << ts << endl; //initial board
	

	do {

		//Call a function that prints out the board

		cout << "Please choose from the following options to chose which action you would like to happen:" << endl;
		cout << "1: Shift" << endl;
		cout << "2: Spin" << endl;
		cout << "3: Exit Game" << endl;
		cin >> option;

		while (option > 3 || option < 1) //validates the user inputted a valid number
		{
			cout << "Error: Please enter a valid choice: " << endl;
			cin >> option;
		}
		

		if (option == 1) //for if the user chose to shift the board
		{
			int numShifts = 0, direction = 0;
			cout << "How many shifts would you like?" << endl;
			cin >> numShifts; // how many shifts they wanted

			cout << "Which direction would you like the shifts to go? Please select one of the following choices: " << endl;
			cout << "1. Right" << endl;
			cout << "2. Left" << endl;
			cin >> direction; 

			if (direction == 1)//shift right
			{
				ts.shiftRight(numShifts); //This function passes the number of shifts the user requested to the shiftRight function
				cout << ts << endl;
			}

			if (direction == 2) //shift left
			{
				ts.shiftLeft(numShifts); //This function passes the number of shifts the user requested to the shiftLeft function
				cout << ts << endl;
			}
		}

		if (option == 2)
		{
			ts.spin(); //spins the board inside the size 4 region
			cout << ts << endl;
		}

		
		if (option == 3)
		{
			break;
		}
		//Call a function that checks if the board is solved after the turn
		//If the problem is solved than the value will be 0 and it will exit the do-while loop
		option = ts.isSolved();

	} while (option == 1 || option == 2);

	if (option == 3)//This means the that user selected Exit Game
	{
		cout << "Thank you for playing TopSpin. Have a nice day!" << endl;
	}

	if (option == 0)//This means that the user successfully completed the game
	{
		cout << "CONGRATULATIONS! You succesfully completed the game! Have a nice day!" << endl;
		cout << ts << endl;
	}

	return 0;




}