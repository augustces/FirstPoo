#include <iostream>
#include <vector>
#include <algorithm>

int contar (std::vector<int> vetor, int valor)
{
    int contador=0;
    for (int i = 0; i < (int) vetor.size(); i++)
    {
        if (valor == vetor[i])
            contador ++;
    }
    return contador;
}

int main()
{
    std::cout << contar({2, 4, 9, 7, 4, 5, 6, 4 }, 4) << '\n'; // 3

    std::cout << contar({2, 4, 9, 6, 16, 5, 3, 11 }, 12) << '\n'; // 0
    
    return 0;
}