#include "maze_utils.hpp"

Maze::Maze(std::vector<std::string> maze)
    : m_maze(maze), m_path(maze)
{
    GetMazeCoords();
}

Maze::~Maze()
{

}

bool Maze::SolveMaze(bool display)
{
    std::cout << "          LET'S SOLVE THE MAZE!             " << std::endl;
    auto initTime = std::chrono::high_resolution_clock::now();

    if (display)
    {
        std::thread display_thread(std::bind(&Maze::DisplayUpdating,this));
        display_thread.detach(); // this is beeing displade until m_solved is set to true
    }


    std::thread first_thread(std::bind(&Maze::Move,this,m_initial_coords[0],m_initial_coords[1]));
    first_thread.detach(); // will stop when the function finishes

    while(!m_solved);

    auto finTime = std::chrono::high_resolution_clock::now();

    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finTime - initTime);

    return true;
}

void Maze::GetReport()
{
    DisplayMaze(m_path);
    std::cout << "******************** Statistics of the Maze solving ********************" << std::endl;
    std::cout << "Elapsed time: " << m_duration.count()/1e6 << " ms" << std::endl;
    std::cout << "Initial Coords: [" << m_initial_coords[0] << "," << m_initial_coords[1] << "]" << std::endl;
    std::cout << "Final Coords: [" << m_final_coords[0] << "," << m_final_coords[1] << "]" << std::endl;
    std::cout << "*****************************************************************************" << std::endl;
}

void Maze::DisplayMaze(const std::vector<std::string>& maze)
{
    for (size_t i = 0; i < maze.size(); i++)
    {
        std::cout << maze[i] << std::endl;
    }

    std::cout << std::endl;
}

void Maze::GetMazeCoords()
{
    for (size_t i = 0; i < m_maze.size(); ++i)
    {
        for (size_t j = 0; j < m_maze[i].size(); ++j) 
        {

            if (m_maze[i][j] == 'I')
            {
                m_initial_coords.push_back(j);
                m_initial_coords.push_back(i);
                m_path[i][j] = ' ';
            }
                
            if (m_maze[i][j] == 'O')
            {
                m_final_coords.push_back(j);
                m_final_coords.push_back(i);
                m_path[i][j] = ' ';
            }
        }
    }
}

static std::mutex s_mutex;
void Maze::Move(size_t X, size_t Y)
{   
    std::lock_guard<std::mutex> lock(s_mutex); // we block the function as we do not want to modify the variable at the same time
    
    if((X == m_final_coords[0]) && (Y == m_final_coords[1]))
    {
        m_solved = true; // the maze is solved
    }
    
    m_path[Y][X] = ME;

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    bool keep_thread = false;
    size_t nextX, nextY;

    size_t xlimit = m_maze[0].size();
    size_t ylimit = m_maze.size();

    if (X > 0)
    {
        WhatToDo(&keep_thread, &nextX, &nextY, Y, X - 1, m_path);
    }
    if ((X + 1) < xlimit)
    {
        WhatToDo(&keep_thread, &nextX, &nextY, Y, X + 1, m_path);
    }
    if (Y > 0)
    {
        WhatToDo(&keep_thread, &nextX, &nextY, Y - 1, X, m_path);
    }
    if ((Y + 1) < ylimit)
    {
        WhatToDo(&keep_thread, &nextX, &nextY, Y + 1, X, m_path);
    }

    if (keep_thread)
    {
        Move(nextX, nextY);
    }
    
}


void Maze::WhatToDo(bool* keep_thread, size_t* nextX, size_t* nextY, size_t newY, size_t newX, std::vector<std::string> maze)
{

    if (maze[newY][newX] == FREE || ((newY == m_final_coords[1]) && (newX == m_final_coords[0])))
    {
        if(!keep_thread)
        {
            *keep_thread = true;
            *nextX = newX;
            *nextY = newY;
        } else
        {

            std::thread new_thread(std::bind(&Maze::Move,this,newX, newY));
            new_thread.detach();
        }
    }
}

void Maze::DisplayUpdating()
{
    while(!m_solved)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        DisplayMaze(m_path);
    }
}
