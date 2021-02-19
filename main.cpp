#include "labyrinthClass.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readLabyrinth(const std::string& filename)
{
    std::cout << "Reading the labyrinth: " << filename << std::endl;

    std::ifstream source;
    source.open(filename);
    std::vector<std::string> laberinto;
    std::string line;
    while (std::getline(source, line))
    {
        laberinto.push_back(line);
    }
    return laberinto;
}

int main(int argc, char **argv)
{
    bool play = false;

    std::string filename(argv[1]);

    std::vector<std::string> laberinto_ = readLabyrinth(filename);

    if (laberinto_.size())
    {
        std::cout << "Succesfully read a playable labyrinth" << std::endl;
        std::cout << "Maze Size [x:" << laberinto_[1].size() << ",y:" << laberinto_.size() << "]" << std::endl;
        play = true;
    } 
    else
    {
       std::cout << "Not valid labyrinth" << std::endl; 
    }

    if (play)
    {
        Labyrinth lab(laberinto_);
        lab.displayLabyrinth(laberinto_);
        lab.play(true); // if true display dynamically
        lab.get_report();
    }

    return 0;
}