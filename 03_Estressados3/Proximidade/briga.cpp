#include <iostream>
#include <vector>

int briga ( const std::vector<int>& vetor) 
{
    int contador{ 0 };
    for ( int i { 1 }; i < ((int) vetor.size() - 1 ); i++ ) {
        if ( vetor[ i ] > 50 && vetor[ i - 1 ] > 30 && vetor[ i + 1 ] > 30 )
            contador++;
    }
    return contador;
}

int main()
{
    std::cout << briga( {99, 63, 45, 63, 78, 35, 52} ) << '\n'; //3

    std::cout << briga( {95, 50, 36, 72, 46, 35, 70} ) << '\n'; //1

    std::cout << briga( {99, 32, 25, 71, 12, 47, 33} ) << '\n'; //0

    return 0;
}