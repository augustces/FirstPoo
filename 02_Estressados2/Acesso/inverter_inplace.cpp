#include <iostream>
#include <vector>

void inverter ( std::vector<int>& vetor )
{
    int size {(int) vetor.size()};
    for ( int i {0}; i < (int) size/2; i++ ) {
        int aux{ vetor[ size - 1 - i ] };
        vetor[ size - 1 - i ] = vetor [ i ];
        vetor [ i ] = aux;
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
    std::vector<int> vetAuxiiliar{{1, 44, 6, -83, -9, 6, -7}}; // -7, 6, -9, -83, 6, 44, 1
    inverter(vetAuxiiliar);
    printar(vetAuxiiliar);

    vetAuxiiliar = {4, 2, -8, -6, 11, -98, 6}; // 6, -98, 11, -6, -8, 2, 4
    inverter(vetAuxiiliar);
    printar((vetAuxiiliar));

    vetAuxiiliar = {4, -6, -34, 99, -76, 3}; // 3, -76, 99, -34, -6, 4
    inverter(vetAuxiiliar);
    printar((vetAuxiiliar));

    return 0;
}