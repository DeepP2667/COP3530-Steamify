// using std::count [https://en.cppreference.com/w/cpp/algorithm/count]

#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "RBTree.h"
#include "HashMap.h"
#include "Game.h"

void loadCSV(HashMap& hash, RBTree& tree)
{
	// open "games.csv"
	// read into each data structure
	int counter = 0;
	std::ifstream inFile("games.csv");
	if (inFile.is_open())
	{
		std::string lineFromFile;
		while (getline(inFile, lineFromFile))
		{
			std::istringstream stream(lineFromFile);
			std::string line = stream.str();
			std::string::difference_type n = std::count(line.begin(), line.end(), ',');
			bool released = (line.find("Coming soon") == std::string::npos);
			std::string title;
			if ( (n > 4 && !released) || (n > 5 && released) )
			{
				// there is at least 1 extra comma in the name section
				int extraComs = 0;
				if (released)
					extraComs = n - 5;
				else
					extraComs = n - 4;

				for (int i = 0; i <= extraComs; i++)
				{
					std::string tempTitle;
					getline(stream, tempTitle, ',');
					title = title + tempTitle;
					if (i != extraComs)
						title = title + ",";
				}
			}
			else
			{
				// normal structure for name
				getline(stream, title, ',');
			}

			// genre
			std::string genre;
			getline(stream, genre, ',');
			genre = genre.substr(1);

			// singleplayer bool
			bool single = false;
			std::string tempbool1;
			getline(stream, tempbool1, ',');
			if (tempbool1.substr(1) == "True")
				single = true;

			// multiplayer bool
			bool multi = false;
			std::string tempbool2;
			getline(stream, tempbool2, ',');
			if (tempbool2.substr(1) == "True")
				multi = true;

			// date
			std::string date;
			getline(stream, date);
			date = date.substr(1);

			// insert into data structures
			counter++;
			Game* game = new Game(title, genre, single, multi, date);
			hash.insert(title, game);
			tree.Insert(title, game);
		}
	}
}

bool getDataStructure()
{
	while (true)
	{
	std::cout << "Select a data structure to use:\n"
		<< "[1] Red/Black Tree\n"
		<< "[2] Hash Map" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << std::endl;
	if (input == "1")
		return true;
	if (input == "2")
		return false;
	}
	std::cout << std::endl;
	return true;
}

void printAll(HashMap& hash, RBTree& tree)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call print all for red/black tree
		tree.PrintInOrder();
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call print all for hash map
		hash.printAll();
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchTitle(HashMap& hash, RBTree& tree)
{
	std::cout << "Enter the title of the game to search:" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << std::endl;
	
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchTitle for red/black tree
		tree.SearchByTitle(input);
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();

		hash.getByTitle(input);

		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchGenre(HashMap& hash, RBTree& tree)
{
	// Ask for a genre
	std::cout << "Enter the genre to search:" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchGenre for red/black tree
		tree.SearchByGenre(input);
		stop = std::chrono::high_resolution_clock::now();
	}
		
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchGenre for hash map
		hash.getByGenre(input);
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchCategory(HashMap& hash, RBTree& tree)
{
	std::string input;
	std::string category;
	while (true)
	{
		// Ask for Single-player or Multi-player
		input = "";
		std::cout << "Select a category to search by:\n"
			<< "[1] Singleplayer\n" << "[2] Multiplayer" << std::endl;
		std::getline(std::cin, input);
		std::cout << std::endl;
		if (input == "1" || input == "2")
			break;			
	}
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure

	category = (input == "1") ? "Singleplayer" : "Multiplayer";

	bool single = (input == "1") ? true : false;
	bool multi = (input == "2") ? true : false;
	
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchCategory for red/black tree
		tree.SearchBySingleMulti(single, multi);
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchCategory for hash map
		hash.getByCategory(category);
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchYear(HashMap& hash, RBTree& tree)
{
	std::cout << "Enter the release date to search by:" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchYear for red/black tree
		tree.SearchByRelease(input);
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchYear for hash map
		hash.getByRelease(input);
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

int main()
{

	// 2 variables of each data structure
	HashMap hash = HashMap();
	RBTree tree = RBTree();
	
	loadCSV(hash, tree);
	while (true)
	{
		std::string command;
		std::cout << "Welcome to Steamify, please select a command [1-6]" << std::endl;
		std::cout << "[1] Print all games\n" << "[2] Search by Title\n" << "[3] Search by Genre\n"
			<< "[4] Search by Single/Multiplayer\n" << "[5] Search by Release Year\n"
			<< "[6] Exit" << std::endl;
			
		std::getline(std::cin, command);
		std::cout << std::endl;
		if (command == "1")
			printAll(hash, tree);
		else if (command == "2")
			searchTitle(hash, tree);
		else if (command == "3")
			searchGenre(hash, tree);
		else if (command == "4")
			searchCategory(hash, tree);
		else if (command == "5")
			searchYear(hash, tree);
		else if (command == "6")
			break;
		std::cout << std::endl;
	}

	return 0;
}