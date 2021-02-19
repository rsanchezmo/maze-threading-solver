#ifndef LABYRINTH_HPP
#define LABYRINTH_HPP

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>


class Labyrinth
{
    public:
        Labyrinth(std::vector<std::string> laberinto);
        ~Labyrinth();

        bool play(bool display); // solve the labyrinth
        void get_report(); // statistics of the game solving
        void displayLabyrinth(const std::vector<std::string> maze); // display the loaded labyrinth
        void getInOut(); // get init and final coordinates
        void move(size_t X, size_t Y);
        void whatToDo(bool* currentThread, size_t* nextX, size_t* nextY, size_t newY, size_t newX, std::vector<std::string> maze);
        void displayUpdating();

    private:
        std::vector<std::string> myLab, myPath;

        std::vector<size_t> initCoordinates;
        std::vector<size_t> finCoordinates;

        std::chrono::nanoseconds duration_;

        const char FREE = ' ';
        const char ME = '*';

        bool solved = false;


};


#endif // LABYRINTH_HPP