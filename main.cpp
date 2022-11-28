#include <iostream>
#include <string>
#include <chrono>
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
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call print all for red/black tree

		//std::string one = "asfjasdklfjakljfkladfjklasfadlfjtestljkjflkajfklajdlfjadflk";
		//int count = one.find("test");
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call print all for hash map
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchTitle(/*example object(s)*/)
{
	// Ask for keywords in title
	std::cout << "Enter the keyword(s) of the title to search:" << std::endl;
	std::string input;
	std::cin >> input;
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchTitle for red/black tree
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchTitle for hash map
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchGenre(/*example object(s)*/)
{
	// Ask for a genre
	std::cout << "Enter the genre to search:" << std::endl;
	std::string input;
	std::cin >> input;
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchGenre for red/black tree
		stop = std::chrono::high_resolution_clock::now();
	}
		
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchGenre for hash map
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
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
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchCategory for red/black tree
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchCategory for hash map
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}

void searchYear(/*example object(s)*/)
{
	// Ask for year
	std::cout << "Enter the release year to search by:" << std::endl;
	int input;
	std::cin >> input;
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = start;
	// Ask for which data structure
	if (getDataStructure())
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchYear for red/black tree
		stop = std::chrono::high_resolution_clock::now();
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		// Call searchYear for hash map
		stop = std::chrono::high_resolution_clock::now();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}



int main()
{
	loadCSV();

	// 2 variables of each data structure

	while (true)
	{
		std::cout << "Welcome to Steamify, please select a command [1-6]" << std::endl;
		std::cout << "[1] Print all games\n" << "[2] Search by Title\n" << "[3] Search by Genre\n"
			<< "[4] Search by Single/Multiplayer\n" << "[5] Search by Release Year\n"
			<< "[6] Exit" << std::endl;
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