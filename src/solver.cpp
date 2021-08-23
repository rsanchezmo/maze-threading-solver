#include "maze_utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> LoadMaze(const std::string& filename)
{
    std::cout << "Reading the maze: " << filename << std::endl;

    std::ifstream source;
    source.open(filename);
    std::vector<std::string> maze;
    std::string line;

    while (std::getline(source, line))
    {
        maze.push_back(line);
    }

    return maze;
}

int main(int argc, char **argv)
{

    bool valid_maze = false;

    std::string filename(argv[1]);

    std::vector<std::string> maze = LoadMaze(filename);

    if (maze.size())
    {
        std::cout << "Succesfully read a playable maze" << std::endl;
        std::cout << "Maze Size [x:" << maze[1].size() << ",y:" << maze.size() << "]" << std::endl;
        valid_maze = true;
    } 
    else
    {
       std::cout << "Not valid maze" << std::endl; 
    }

    if (valid_maze)
    {
        Maze maze_instance(maze);
        maze_instance.DisplayMaze(maze);
        maze_instance.SolveMaze(false); // if true display dynamically
        maze_instance.GetReport();
    }

    return 0;
}