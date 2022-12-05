#include <string>
#pragma once

using namespace std;

class Game
{
    public:
        Game(std::string title, std::string genre, bool isSingle, bool isMulti, std::string releaseYear);
        std::string title;
        std::string genre;
        bool isSingle;
        bool isMulti;
        std::string releaseYear;
};

Game::Game(std::string title, std::string genre, bool isSingle, bool isMulti, std::string releaseYear)
{
    this->title = title;
    this->genre = genre;
    this->isSingle = isSingle;
    this->isMulti = isMulti;
    this->releaseYear = releaseYear;
}