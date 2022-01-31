#include <iostream>
#include <vector>
#include <algorithm>

int procurar_inicio(std::vector<int> vetor, int inicio)
{
    int pos{inicio};
    int valor{vetor[inicio]};
    for (int i = inicio; i < (int)vetor.size(); i++)
    {
        if (valor > vetor[i])
        {
            pos = i;
            valor = vetor[i];
        }
    }
    return pos;
}

int main()
{
    std::cout << procurar_inicio({1, 7, -99, -69, -1, 2}, 5) << "\n"; //5

    std::cout << procurar_inicio({8, -13, 9, 69, -9, 4}, 3) << "\n"; //4

    std::cout << procurar_inicio({2, 5, -8, -9, 1, -2}, 4) << "\n"; //5

    return 0;
}