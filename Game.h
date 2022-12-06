#pragma once
#include <string>

using namespace std;

class Game {
    private:
        string title;
        string genre;
        bool singleplayer;
        bool multiplayer;
        string releaseDate;
    public:
        Game(string t, string g, bool s, bool m, string r) : title(t), genre(g), singleplayer(s), multiplayer(m), releaseDate(r) {}
        Game() :title(""), genre(""), singleplayer(false), multiplayer (false), releaseDate("") {}
        string GetTitle() { return title; }
        string GetGenre() { return genre; }
        bool IsMulti() { return multiplayer; }
        bool IsSingle() { return singleplayer; }
        string GetYear() { return releaseDate; }
        void PrintInfo() {
            cout << "Title:\t\t" << title << endl;
            cout << "Genre:\t\t" << genre << endl;
            if (singleplayer)
                cout << "Type:\t\t" << "Singleplayer" << endl;
            else
                cout << "Type:\t\t" << "Multiplayer" << endl;
            cout << "Release Date:\t" << releaseDate << endl<<endl;
        }
};