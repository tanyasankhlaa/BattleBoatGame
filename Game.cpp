/// @file Game.cpp
/// @brief Implementation file for Game class
/// @author Tanya Sankhla
/// Programming in C++

#include <iostream> 
#include <tuple>    
#include <cmath>    
#include <random>   
#include <ctime>    

#include "Game.h"  

#define DIAG  // macro to enable diagnostic output (not used during ordinary gameplay)


Game::Game() : m_nGridRows(k_nGridRowsDefault), m_nGridColumns(k_nGridColumnsDefault), m_iRowBoat(0), m_iColumnBoat(0), m_nTorpedoes(k_nMaxTorpedoes)/* ?? add initializers for member variables m_iRowBoat, m_iColumnBoat, and m_nTorpedoes. ?? */
{
	// call member function initializeGrid 
	initializeGrid();
}

// Implementation notes on Game::initializeGrid
//
// When the coordinate grid is initialized, all elements of the
// the two dimensional array a_cGrid are set to contain the
// wave character, a tilde: '~'.
//
// When rendered by displayGrid, the initialized grid appears
// as follows:
//
// |~|~|~|~|~|
// |~|~|~|~|~|
// |~|~|~|~|~|
// |~|~|~|~|~|

void Game::initializeGrid()
{

	// Within the inner for loop, assign the array element indexed by iRow and iColumn to the tilde character ~

	for (int iRow = 0; iRow < this->m_nGridRows; ++ iRow)
	{
		//outer for loop that iterates over the rows in the two-dimensional character array a_cGrid.
		for (int iColumn = 0; iColumn < this->m_nGridColumns; ++ iColumn)
		// inner for loop that iterates over the columns in the two-dimensional character array a_cGrid
		{
			a_cGrid[iRow][iColumn] = '~';
		}
	}
	return;
}

// Implementation notes 
// The grid initially contains only tilde characters, '~', ("waves"):
// |~|~|~|~|~|
// |~|~|~|~|~|
// |~|~|~|~|~|
// |~|~|~|~|~|
// Later it may contain asterisks ('*'), "torpedo explosions", the symbol for the target boat, 'V',
// or an 'X' to indicate the target boat was sunk at that location.
// When the player has expended all of their torpedoes (and lost the game), the location of the
// target boat is rendered with a 'V' character.


void Game::displayGrid(bool bShowBoat) {



	for (int iRow = 0; iRow < this->m_nGridRows; ++iRow)
	//outer for loop that iterates over the rows in the two-dimensional character array a_cGrid
	{
		std::cout << "|";
		for (int iColumn = 0; iColumn < this->m_nGridColumns; ++iColumn)
		// inner for loop that iterates over the columns in the two-dimensional character array a_cGrid
		// display the element at the grid coordinate iRow, iColumn. Surround the
		// element with vertial bar characters
		{
			if (this->a_cGrid[iRow][iColumn] == 'V')
			{

				// If the character in a_cGrid at location iRow and iColumn is a 'V'  only display it if the value of parameter bShowBoat is true, otherwise hide it by displaying  ~
				if (bShowBoat == true)
				{
					std::cout << this->a_cGrid[iRow][iColumn] << "|";
				}
				else
			       	{
					std::cout << '~' << "|";
				}
			}
			else
		       	{
				std::cout << this->a_cGrid[iRow][iColumn] << "|";
			}
		}
		std::cout << std::endl;
	}
	return;
}




// Game::fireTorpedo inserts an asterisk at the torpedo aimpoint location
// in the a_cGrid two-dimensional array. It also decremements the
// remaining number of torpedoes member variable this->m_nTorpedoes.

std::tuple<int, int>  Game::fireTorpedo()
// user is promted to enter a row, column location that is the aimpoint
// for their torpedo by calling the promptForGridCoord member function.

// After the torpedo is fired an asterisk  is rendered
// at the location entered by the user. 
{
	int iRow = 0;
	int iColumn = 0;


	this->m_nTorpedoes -= 1;

	std::cout << "Enter grid Coordinates (row, column) of torpedo target grid square" << std::endl;
	std::tie(iRow, iColumn) = promptForGridCoord();


	this->a_cGrid[iRow][iColumn] = '*';
	// Return the coordinates of the torpedo explosion location as a tuple object
	std::tuple<int, int> tupleTorpedoCoord(iRow, iColumn);
	return tupleTorpedoCoord;
}

void Game::placeBoatRandomly()
{
	// use the default random number generator.

	// random Device used to seed the random number generator,
	std::random_device randomDevice;

	std::default_random_engine randomNumbreGenerator(randomDevice());

	std::uniform_int_distribution<int> uniformIntegerDistributionRows(0, (this->m_nGridRows - 1));

	this->m_iRowBoat = uniformIntegerDistributionRows(randomNumbreGenerator);


	std::uniform_int_distribution<int> uniformIntegerDistributionColumns(0, (this->m_nGridColumns - 1));

	this->m_iColumnBoat = uniformIntegerDistributionColumns(randomNumbreGenerator);

	// Assign the boat symbol, a 'V', to the boat's random grid location
	a_cGrid[this->m_iRowBoat][this->m_iColumnBoat] = 'V';


#if defined(DIAG)
	std::cout << "DIAG: Boat location (Row/Column): " << this->m_iRowBoat << "; " << this->m_iColumnBoat << std::endl;
#endif

}



void Game::placeBoat()
{
	int iRow = 0;
	int iColumn = 0;

	std::cout << "Enter the grid square coordinates  (row, column) of target boat" << std::endl;

	std::tie(iRow, iColumn) = promptForGridCoord();


	this->a_cGrid[iRow][iColumn] = 'V';
	this->m_iRowBoat = iRow;
	this->m_iColumnBoat = iColumn;
	return;
}


bool Game::isOnTarget(int iRow, int iColumn)
{
	bool bHit = false; // true if target boat has been hit

	if ((iRow == this->m_iRowBoat) && (iColumn == this->m_iColumnBoat))
	{
		bHit = true;
	}

	return bHit;
}



bool Game::isCloseToTarget(int iRow, int iColumn)
{
	bool bClose = false;

	if ((std::abs(iRow - this->m_iRowBoat) <= 1) && (std::abs(iColumn - this->m_iColumnBoat) <= 1) )
	{
		bClose = true;
	}

	return bClose;
}


void Game::showSunk()
{

	this->a_cGrid[this->m_iRowBoat][this->m_iColumnBoat] = 'X';
	return;
}


std::tuple<int, int> Game::promptForGridCoord()
{
	int iRow = 0;
	int iColumn = 0;

	// get coordinates from user
	std::cout << "Please enter grid row number: " << std::endl;
	std::cin >> iRow;
	std::cout << "Please enter grid column number: " << std::endl;
	std::cin >> iColumn;

	// Create a tuple holding the iRow and iColumn integer values and return the tuple
	std::tuple<int, int> tupleCoord = std::make_tuple(iRow, iColumn);

	return tupleCoord;
}


void Game::play()
{
	int iRow = 0;
	int iColumn = 0;

	this->reset();            // Reset member variables for a new game.
	this->displayGrid(false); // Display the grid but hide the location of the target boat
	std::cout << "Magazine: " << this->m_nTorpedoes << " torpedoes" << std::endl;
	std::cout << std::endl;

	// Execute a sequence of turns within a while loop. Each turn is an interation
	// of the file loop. Within a turn, the user fires a torpedo and checks are
	// performed to see if the torpedo hit the target (i.e. the user selected the
	// exact grid square in which the target boat is placed), if the torpedo was
	// "close" to the target 
	// If neither a hit (isOnTarget is true) or a close miss (isCloseToTarget is true)
	// the torpedo is a miss. The while loop iterates until either the target boat
	// is hit, in which case the player wins, or all torpedoes have
	// been expended, and the target boat survives, in which case the computer wins.
	bool bSunk = false;
	while ((!bSunk) && (this->m_nTorpedoes > 0))
	{
		std::cout << std::endl;
		// Accept input from user as to grid location where torpedo is fired
		// Return location as a tuple and extract the row and column values
		// from the tuple into iRow and iColumn, respectively.
		std::tie(iRow, iColumn) = this->fireTorpedo();

		if (this->isOnTarget(iRow, iColumn))
		{
			this->showSunk();
			this->displayGrid(false);
			std::cout << "Hit!  Kaboom!" << std::endl;
			std::cout << "Victory!" << std::endl;
			bSunk = true;
		}
		else if (this->isCloseToTarget(iRow, iColumn))
		{
			this->displayGrid(false);
			std::cout << "Location row: " << iRow << "; column: " << iColumn << " is close!" << std::endl;
		}
		else
		{
			this->displayGrid(false);
			std::cout << "Location row: " << iRow << "; column: " << iColumn << " is a miss." << std::endl;
		}

		// If the target boat has not been sunk (bSunk is false), display the remaining number of torpedoes
		if (bSunk == false)
		{
			std::cout << "Magazine: " << this->m_nTorpedoes << " torpedoes" << std::endl;
		}

		// If the number of torpedoes (which is held in member variable this->m_nTorpedoes) is 0 and the
		// target boat has not been sunk: call the displayGrid member function with the bShowBoat parameter set to true.

		if ((this->m_nTorpedoes == 0) && (bSunk == false))
		{
			// Display grid shown boat's location
			bool bShowBoat = true;

			displayGrid(bShowBoat);
			std::cout << "Torpedoes expended" << std::endl;
			std::cout << "Game over" << std::endl;
		}
	}
}


void Game::reset()
{
	this->initializeGrid();
#if defined TEST
	// Place the target boat at a specified location for testing
	this->placeBoat();
#else
	// The target boat is placed at a random location on the grid; this is used for
	// normal gameplay.
	this->placeBoatRandomly();
#endif
	this->m_nTorpedoes = Game::k_nMaxTorpedoes;
}
