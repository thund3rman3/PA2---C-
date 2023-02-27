#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>


// novy typ pro 2D souradnici
typedef std::pair<size_t, size_t> Position;

// mozne typy policek v bludisti
enum Tile 
{
    FREE, WALL, START, END, PATH
};

// vypis pozice do streamu
std::ostream& operator<<(std::ostream&os, const Position& p)
{
    return os << p.first << ':' << p.second;
}


// trida pro bludiste
class Maze
{
private:
    std::vector< std::vector<Tile> > maze;
    Position start, end;

    void moveTo(const Position &p, const Position &from, std::map<Position, Position> &visited, std::queue<Position>& q)
    {
        if (p.second >= maze.size()) return;
        if (p.first >= maze[p.second].size()) return;
        if (maze[p.second][p.first] == WALL) return;

        if (visited.find(p) == visited.end())
        {
            visited.insert( std::make_pair(p, from) );
            //maze[p.second][p.first] = PATH;
            q.push(p);
        }
    }

        public : void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file.is_open()) throw std::runtime_error("Cannot open file!");

        char c;
        size_t row = 0;
        size_t s = 0;
        size_t e = 0;

        while (file.get(c))
        {
            maze.resize(row + 1);

            switch (c)
            {
            case '#':
                maze[row].push_back(WALL);
                break;
            case '.':
                maze[row].push_back(FREE);
                break;
            case 'S':
                maze[row].push_back(START);
                s++;
                start.first = maze[row].size()-1;
                start.second = row;
                break;
            case 'E':
                maze[row].push_back(END);
                e++;
                end.first = maze[row].size() - 1;
                end.second = row;
                break;
            case '\n':
                row++;
                break;

            default:
                throw std::runtime_error("File format error, invalid char!");
                break;
            }
        }
        if (s != 1)
            throw std::runtime_error("Error, Start");
        if (e != 1)
            throw std::runtime_error("Error, End");
    }

    std::list<Position> solve()
    {        
        std::map< Position, Position > visited;
        std::queue<Position> q;
        std::list<Position> path;

        Position p;

        q.push(start);

        while (!q.empty())
        {
            p = q.front();
            q.pop();

            if ( p == end ) break;

            moveTo(Position(p.first + 1, p.second), p, visited, q);
            moveTo(Position(p.first - 1, p.second), p, visited, q);
            moveTo(Position(p.first, p.second + 1), p, visited, q);
            moveTo(Position(p.first, p.second - 1), p, visited, q);
        }

        if ( p != end ) throw std::runtime_error("Path not found!");

        p = visited[end];
        do 
        {
            path.push_front(p);
            maze[p.second][p.first] = PATH;
            p = visited[p];
        } while (p != start);

        return path; 
    }

    // print do console
    void print()
    {
        for ( auto& v : maze )
        {
            for ( auto& tile : v)
            {
                switch (tile)
                {
                case WALL:
                    std::cout << '#';
                    break;
                case FREE:
                    std::cout << '.';
                    break;
                case START:
                    std::cout << 'S';
                    break;
                case END:
                    std::cout << 'E';
                    break;
                case PATH:
                    std::cout << '*';
                    break;

                default:
                    break;
                }
            }
            std::cout << std::endl;
        }
    }
        
};

#endif