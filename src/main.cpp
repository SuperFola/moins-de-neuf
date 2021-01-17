#include <iostream>  // std::cout, std::endl
#include <exception>

#include <Referee.hpp>

int main(int argc, char **argv)
{
    std::cout   << "Moins de neuf\n"
                << "=============\n";

    try
    {
        Referee r;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        throw;
    }

    return 0;
}