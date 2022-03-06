#include "GameOfLife.h"
#include <iostream>

int main()
{
    GameOfLife test(4,4,'O',' ');

    test.Set(2, 3);
    test.Set(1,1);
    test.Set(1,2);
    test.Set(0,1);

    test.afficher();

    std::cout << "\n\n";

    test.nextGen();

    test.afficher();

    std::cout << "\n\n";

    test.nextGen();

    test.afficher();

    std::cout << "\n\n";

    test.nextGen();

    test.afficher();


    std::cout << "\n\n";

    test.nextGen();

    test.afficher();


    std::cout << "\n\n";

    test.nextGen();

    test.afficher();

    std::cout << true + 8;
}