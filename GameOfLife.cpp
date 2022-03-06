#include "GameOfLife.h"
#include <iostream>
#include <ostream>
#include <vector>

GameOfLife::GameOfLife(int size_x, int size_y, char enVie, char mort)
{
    m_size_x = size_x;
    m_size_y = size_y;

    m_enVie = enVie;
    m_mort = mort;

    for(int i = 0; i < m_size_x; i++)
    {
        std::vector<bool> row;
        for(int j = 0; j < m_size_y; j++)
            row.push_back(false);
        m_board.push_back(row);
    }
}

void GameOfLife::Setup(std::vector<std::vector<bool>> board)
{
    for(int i = 0; i < m_size_x; i++)
        for(int j = 0; j < m_size_y; j++)
            m_board[i][j] = board[i][j];
}

void GameOfLife::Set(int i, int j, bool value)
{
    m_board[i][j] = value;
}

void GameOfLife::change(int i, int j)
{
    m_board[i][j] = !m_board[i][j];
}

void GameOfLife::random()
{
    srand(time(0));
    for(int i = 0; i < m_size_x; i++)
        for(int j = 0; j < m_size_y; j++)
            m_board[i][j] = rand() % 2;
}

void GameOfLife::clear()
{
    for(int i = 0; i < m_size_x; i++)
        for(int j = 0; j < m_size_y; j++)
            m_board[i][j] = false;
}

void GameOfLife::board(std::vector<std::vector<bool>> & board) const
{
    board = m_board;
}

void GameOfLife::afficher() const
{
    for(int i = 0; i < m_size_x; i++)
    {
        for(int j = 0; j < m_size_y; j++)
        {
            if(m_board[i][j])
                std::cout << m_enVie;
            else
                std::cout << m_mort;
        }
        std::cout << "\n";
    }
}

bool GameOfLife::isAlive(int i, int j)
{
    return m_board[i][j];
}

bool GameOfLife::inboard(int i, int j) const
{
    return (0 <= i && 0 <= j && m_size_x > i && m_size_y > j);
}

bool GameOfLife::willSurvive(int i, int j) const
{
    int nbNeighbour = 0;

    int neighbors[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

    for(int a = 0; a < 8; a++)
        if(inboard(i + neighbors[a][0], j + neighbors[a][1]))
            nbNeighbour += m_board[i + neighbors[a][0]][j + neighbors[a][1]];

    return (m_board[i][j] && (nbNeighbour == 2 || nbNeighbour == 3)) || (!m_board[i][j] && nbNeighbour == 3);
}

void GameOfLife::nextGen()
{
    std::vector<std::vector<bool>> newBoard;

    for(int i = 0; i < m_size_x; i++)
    {
        std::vector<bool> row;
        for(int j = 0; j < m_size_y; j++)
            row.push_back(this->willSurvive(i, j));
        newBoard.push_back(row);
    }

    Setup(newBoard);
}


std::ostream& GameOfLife::SaveToFile(std::ostream& outfile)
{
    outfile << m_board.size() << " ";
    outfile << m_board[0].size() << "\n";

    for (int i = 0; i < int(m_board.size()); i++)
    {
        for(int j = 0; j < int(m_board[0].size()); j++)
        {
            if(m_board[i][j])
                outfile << 'X';
            else
                outfile << 'O';
            outfile << ' ';
        }
        //outfile << "\n";
    }
    return outfile;
}
void GameOfLife::LoadFromFile(std::istream& file)
{
    int rows = 0 , cols = 0;
    file >> rows;
    file >> cols;

    //std::cout << rows << " " << cols;
    for (int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            char a = ' ';
            file >> a;
            if(inboard(i, j))
            {
                if(a == 'O')
                    m_board[i][j] = false;
                else
                    m_board[i][j] = true;
            }
        }
    }
}