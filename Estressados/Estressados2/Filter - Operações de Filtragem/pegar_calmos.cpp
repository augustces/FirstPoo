#include <iostream>
#include <vector>

std::vector<int> pegarCalmos (const std::vector<int>& vetor)
{
    std::vector<int> lista { };
    for (int i = 0; i < (int) vetor.size(); i++) {
        if ( abs( vetor[ i ] ) < 10 ) 
            lista.push_back(vetor[ i ]);
    }
    return lista;
}

void printar(const std::vector<int>& vetor)
{
    std::cout << "[ ";
    for (int i {0}; i < (int) vetor.size(); i++)
    {
        std::cout << vetor[ i ] << ", ";
    }
    std::cout << "] \n";
}

int main() 
{
    std::vector<int> vetAuxiliar{ {1, 5, -7, 8, -3, 4, -9} }; // 1, 5, -7, 8, -3, 4, -9
    printar(pegarCalmos(vetAuxiliar));

    vetAuxiliar = {3, 16, -2, -17, -9, -2}; // 3, -2, -9, -2
    printar(pegarCalmos(vetAuxiliar));

    vetAuxiliar = {-92, -16, 8, -55, 74, 3}; // 8, 3
    printar(pegarCalmos(vetAuxiliar));

    return 0;
}