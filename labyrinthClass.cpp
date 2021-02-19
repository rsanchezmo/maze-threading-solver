#include "labyrinthClass.hpp"

Labyrinth::Labyrinth(std::vector<std::string> laberinto)
{
    myLab = laberinto;
    myPath = myLab;
    getInOut();
}

Labyrinth::~Labyrinth()
{

}

bool Labyrinth::play(bool display)
{
    std::cout << "          LET'S SOLVE THE MAZE!             " << std::endl;
    auto initTime = std::chrono::high_resolution_clock::now();

    if (display)
    {
        std::thread disp(std::bind(&Labyrinth::displayUpdating,this));
        disp.detach();
    }


    std::thread iterator_(std::bind(&Labyrinth::move,this,initCoordinates[0],initCoordinates[1]));
    iterator_.detach();

    while(!solved);

    auto finTime = std::chrono::high_resolution_clock::now();

    duration_ = std::chrono::duration_cast<std::chrono::nanoseconds>(finTime - initTime);

    return true;
}

void Labyrinth::get_report()
{
    displayLabyrinth(myPath);
    std::cout << "******************** Statistics of the labyrinth solving ********************" << std::endl;
    std::cout << "Elapsed time: " << duration_.count() << " ns" << std::endl;
    std::cout << "Initial Coords: [" << initCoordinates[0] << "," << initCoordinates[1] << "]" << std::endl;
    std::cout << "Final Coords: [" << finCoordinates[0] << "," << finCoordinates[1] << "]" << std::endl;
    std::cout << "*****************************************************************************" << std::endl;
}

void Labyrinth::displayLabyrinth(const std::vector<std::string> maze)
{
    for (size_t i = 0; i < maze.size(); i++)
    {
        std::cout << maze[i] << std::endl;
    }

    std::cout << std::endl;
}

void Labyrinth::getInOut()
{
    for (size_t i = 0; i < myLab.size(); ++i)
    {
        for (size_t j = 0; j < myLab[i].size(); ++j) 
        {

            if (myLab[i][j] == 'I')
            {
                initCoordinates.push_back(j);
                initCoordinates.push_back(i);
                myPath[i][j] = ' ';
            }
                
            if (myLab[i][j] == 'O')
            {
                finCoordinates.push_back(j);
                finCoordinates.push_back(i);
                myPath[i][j] = ' ';
            }
        }
    }
}

void Labyrinth::move(size_t X, size_t Y)
{
    
    if((X == finCoordinates[0]) && (Y == finCoordinates[1]))
    {
        solved = true;
    }
    
    myPath[Y][X] = ME;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    bool continueThread = false;
    size_t nextX, nextY;

    size_t xlimit = myLab[0].size();
    size_t ylimit = myLab.size();

    if (X > 0)
    {
        whatToDo(&continueThread, &nextX, &nextY, Y, X - 1, myPath);
    }
    if ((X + 1) < xlimit)
    {
        whatToDo(&continueThread, &nextX, &nextY, Y, X + 1, myPath);
    }
    if (Y > 0)
    {
        whatToDo(&continueThread, &nextX, &nextY, Y - 1, X, myPath);
    }
    if ((Y + 1) < ylimit)
    {
        whatToDo(&continueThread, &nextX, &nextY, Y + 1, X, myPath);
    }

    if (continueThread)
    {
        move(nextX, nextY);
    }
    
}


void Labyrinth::whatToDo(bool* continueThread, size_t* nextX, size_t* nextY, size_t newY, size_t newX, std::vector<std::string> maze)
{

    if (maze[newY][newX] == FREE || ((newY == finCoordinates[1]) && (newX == finCoordinates[0])))
    {
        if(!continueThread)
        {
            *continueThread = true;
            *nextX = newX;
            *nextY = newY;
        } else
        {

            std::thread newWay(std::bind(&Labyrinth::move,this,newX, newY));
            newWay.detach();
        }
    }
}

void Labyrinth::displayUpdating()
{
    while(!solved)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        displayLabyrinth(myPath);
    }
}
