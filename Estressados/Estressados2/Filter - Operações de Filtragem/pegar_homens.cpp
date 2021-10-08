#include <iostream>
#include <vector>

std::vector<int> pegarH(const std::vector<int>& vetor)
{
    std::vector<int> lista {};
    for (int i { 0 }; i < (int) vetor.size(); i++) {
        if(vetor[ i ] > 0)
            lista.push_back( vetor[ i ]);
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
    std::vector<int> vetAuxiliar{ {1, 5, -7, 8, -3, 4, -9} }; // 1 5 8 4
    printar(pegarH(vetAuxiliar));

    vetAuxiliar = {3, 6, -2, 7, -9, -2}; // 3 6 7
    printar(pegarH(vetAuxiliar));

    vetAuxiliar = {2, 6, 8, 5, 4, 3}; // 2 6 8 5 4 3
    printar(pegarH(vetAuxiliar));

    return 0;
}