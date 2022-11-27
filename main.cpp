#include <iostream>
#include <string>
// #include <redblacktree.h>
// #include <hashmap.h>

void loadCSV()
{
	// open "games.csv"
	// read into each data structure

	// 
}

bool getDataStructure()
{
	while (true)
	{
	std::cout << "Select a data structure to use:\n"
		<< "[1] Red/Black Tree\n"
		<< "[2] Hash Map" << std::endl;
	std::string input;
	std::cin >> input;
	if (input == "1")
		return true;
	if (input == "2")
		return false;
	std::cout << std::endl;
	}
	return true;
}

void printAll(/*example object(s)*/)
{
	// Ask for which data structure
	if (getDataStructure())
		// Call print all for red/black tree
		;
	else
		// Call print all for hash map
		;
}

void searchTitle(/*example object(s)*/)
{
	// Ask for keywords in title
	std::cout << "Enter the keyword(s) of the title to search:" << std::endl;
	std::string input;
	std::cin >> input;
	std::cout << std::endl;
	// Ask for which data structure
	if (getDataStructure())
		// Call searchTitle for red/black tree
		;
	else
		// Call searchTitle for hash map
		;
}

void searchGenre(/*example object(s)*/)
{
	// Ask for a genre
	std::cout << "Enter the genre to search:" << std::endl;
	std::string input;
	std::cin >> input;
	std::cout << std::endl;
	// Ask for which data structure
	if (getDataStructure())
		// Call searchGenre for red/black tree
		;
	else
		// Call searchGenre for hash map
		;
}

void searchCategory(/*example object(s)*/)
{
	while (true)
	{
		// Ask for Single-player or Multi-player
		std::cout << "Select a category to search by:\n"
			<< "[1] Singleplayer\n" << "[2] Multiplayer" << std::endl;
		std::string input;
		std::cin >> input;
		std::cout << std::endl;
		if (input == "1" || input == "2")
			break;			
	}
	// Ask for which data structure
	if (getDataStructure())
		// Call searchCategory for red/black tree
		;
	else
		// Call searchCategory for hash map
		;
}

void searchYear(/*example object(s)*/)
{
	// Ask for year
	std::cout << "Enter the release year to search by:" << std::endl;
	int input;
	std::cin >> input;
	std::cout << std::endl;
	// Ask for which data structure
	if (getDataStructure())
		// Call searchYear for red/black tree
		;
	else
		// Call searchYear for hash map
		;
}



int main()
{
	loadCSV();

	// 2 variables of each data structure

	while (true)
	{
		std::cout << "Welcome to Steamify, please select a command [1-6]" << std::endl;

		std::string command;
		std::cin >> command;
		std::cout << std::endl;
		if (command == "1")
			printAll(/*example object(s)*/);
		else if (command == "2")
			searchTitle(/*example object(s)*/);
		else if (command == "3")
			searchGenre(/*example object(s)*/);
		else if (command == "4")
			searchCategory(/*example object(s)*/);
		else if (command == "5")
			searchYear(/*example object(s)*/);
		else if (command == "6")
			break;
		std::cout << std::endl;
	}

	return 0;
}