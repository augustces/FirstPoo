#include <iostream>
#include <vector>

void ordenar ( std::vector<int>& vetor )
{
    for ( int i {0}; i < (int) vetor.size(); i++ ) {
        for (int k {0}; k < (int) vetor.size(); k++) {
            if (vetor[ k ] > vetor[ i ]) {
                int auxiliar{vetor [ k ]};
                vetor [ k ] = vetor [ i ];
                vetor [ i ] = auxiliar;

            }
        }
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
    std::vector<int> vetAuxiiliar{{1, 44, 6, -83, -9, 6, -7}}; // -83, -9, -7, 1, 6, 6, 44
    ordenar(vetAuxiiliar);
    printar(vetAuxiiliar);

    vetAuxiiliar = {4, 2, -8, -6, 11, -98, 6}; // -98, -8, -6, 2, 4, 6, 11
    ordenar(vetAuxiiliar);
    printar((vetAuxiiliar));

    vetAuxiiliar = {4, -6, -34, 99, -76, 3}; // -76, -34, -6, 3, 4, 99
    ordenar(vetAuxiiliar);
    printar((vetAuxiiliar));

    return 0;
}