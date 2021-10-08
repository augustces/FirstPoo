#include <iostream>
#include <vector>

std::vector <int> inverter (const std::vector<int>& vetor)
{
    std::vector<int> auxiliar{ };
    for ( int i { (int) vetor.size() - 1 }; i >= 0; i-- ) {
        auxiliar.push_back( vetor[ i ] );
    }
    return auxiliar;
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
    printar(inverter(vetAuxiiliar));

    vetAuxiiliar = {4, 2, -8, -6, 11, -98, 6}; // 6, -98, 11, -6, -8, 2, 4
    printar(inverter(vetAuxiiliar));

    vetAuxiiliar = {4, -6, -34, 99, -76, 3}; // 3, -76, 99, -34, -6, 4
    printar(inverter(vetAuxiiliar));

    return 0;
}