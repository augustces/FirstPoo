#include <iostream>
#include <vector>
#include <algorithm>

int procurar_melhor(std::vector<int> vetor)
{
    int pos{-1};
    int valor{99};
    for (int i = 0; i < (int)vetor.size(); i++)
    {
        if (valor > vetor[i] && vetor[i]>=0)
        {
            pos = i;
            valor = vetor[i];
        }
    }
    return pos;
}

int main()
{
    std::cout << procurar_melhor({1, 7, -99, -69, -1, 2}) << "\n"; //0

    std::cout << procurar_melhor({8, -13, 9, 69, -9, 4}) << "\n"; //5

    std::cout << procurar_melhor({2, 5, -8, -9, 1, -2}) << "\n"; //4

    return 0;
}
