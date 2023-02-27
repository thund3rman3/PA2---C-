#include "maze.hpp"

int main()
{
    Maze m;
    std::list<Position> path;       // vysledna cesta bludistem jako seznam pozic

    try
    {
        m.loadFromFile("../data/maze2.txt");
    }
    catch ( std::exception &e )
    {
        std::cout << e.what() << std::endl;
    }
    
    m.print();

    try 
    {
        path = m.solve();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    /* todo: Vypis cesty */
    for (auto& x : path)
    {
        std::cout << x << std::endl;
    }
    
    
    // Vypis bludiste s cestou
    m.print();

    return 0;
}