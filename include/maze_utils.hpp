#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <mutex>

class Maze
{
    public:
        Maze(std::vector<std::string> maze);
        ~Maze();

        bool SolveMaze(bool display); // solve the Maze
        void GetReport(); // statistics of the game solving
        void DisplayMaze(const std::vector<std::string>& maze); // display the loaded Maze
        void GetMazeCoords(); // get init and final coordinates
        void Move(size_t X, size_t Y);
        void WhatToDo(bool* currentThread, size_t* nextX, size_t* nextY, size_t newY, size_t newX, std::vector<std::string> maze);
        void DisplayUpdating();

    private:
        std::vector<std::string> m_maze, m_path;

        std::vector<size_t> m_initial_coords;
        std::vector<size_t> m_final_coords;

        std::chrono::nanoseconds m_duration;

        const char FREE = ' ';
        const char ME = '*';

        bool m_solved = false;



};


#endif // MAZE_HPP