#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

int sortear ( const std::vector<int>& vetor )
{
    std::srand ( std::time(0) );
    return vetor[ rand() % ((int) vetor.size() - 1) ];
}

int main( )
{
    std::cout << sortear( {1, 44, 6, -83, -9, 6, -7} ) << '\n';

    std::cout << sortear( {4, 2, -8, -6, 11, -98, 6} ) << '\n';
    
    std::cout << sortear( {4, -6, -34, 99, -76, 3} ) << '\n';
        
    return 0;
}