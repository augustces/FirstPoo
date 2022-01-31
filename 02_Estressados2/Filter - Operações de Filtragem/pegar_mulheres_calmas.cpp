#include <iostream>
#include <vector>

std::vector<int> pegarMcalma (const std::vector<int>& vetor)
{
    std::vector<int> lista { };
    for (int i = 0; i < (int) vetor.size(); i++) {
        if (vetor[ i ] > -10 && vetor[ i ] < 0) 
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
    std::vector<int> vetAuxiliar{ {1, 5, -7, 8, -3, 4, -9} }; // -7, -3, -9
    printar(pegarMcalma(vetAuxiliar));

    vetAuxiliar = {3, 16, -2, -17, -9, -2}; // -2, -9, -2
    printar(pegarMcalma(vetAuxiliar));

    vetAuxiliar = {-2, -16, 8, -5, 4, 3}; // -2, -5
    printar(pegarMcalma(vetAuxiliar));

    return 0;
}