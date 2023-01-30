/// @file main.cpp
/// @brief main function file for Game
/// @author Tanya Sankhla
/// Programming in C++

#include <iostream>   

#include "Game.h"     

// Main function for Game progam.
// @return 0 in all circumstances
int main()
{
	bool bPlay = true;
	Game game;



	
	while (bPlay == true)
	{
		// Within the while loop, have the Game object, game, call the play() member function.
		// Then, prompt the user if they want to play another game. If so, iterate through the
		// while loop again, otherwise, set bPlay to false (so that the while loop will cease iterating).
		// Consider using logical expressions like ('y' == cPlay) as in earlier assignments to check the
		// user input.

		// invoke play() member function on game object 
		game.play();

		std::cout << std::endl;
		char cPlay = 'n';
		std::cout << "Play another game? (y/n)" << std::endl;
		std::cin >> cPlay;
		if (cPlay == 'n')
		{
			bPlay = false;
		}
	}

	return 0;
}
