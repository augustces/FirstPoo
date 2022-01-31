#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void embaralhar ( std::vector<int>& vetor )
{
    std::srand( std::time ( 0 ) );

    for ( int i {0}; i < (int) vetor.size(); i++ ) {
        int aux{ vetor[ i ] };
        int indiceRandom{ rand() % ( (int) vetor.size() - 1 )};
        vetor[ i ] = vetor [ indiceRandom ];
        vetor [ indiceRandom ] = aux;
    }
}

void printar (const std::vector<int>& vetor)
{
    std::cout << "[ " ;
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        std::cout << vetor[ i ]  << ", ";
    }
    std::cout << "]\n";
}

int main( )
{
    std::vector<int> vetAuxiiliar{{1, 44, 6, -83, -9, 6, -7}}; 
    embaralhar(vetAuxiiliar);
    printar(vetAuxiiliar);

    vetAuxiiliar = {4, 2, -8, -6, 11, -98, 6}; 
    embaralhar(vetAuxiiliar);
    printar((vetAuxiiliar));

    vetAuxiiliar = {4, -6, -34, 99, -76, 3}; 
    embaralhar(vetAuxiiliar);
    printar((vetAuxiiliar));

    return 0;
}