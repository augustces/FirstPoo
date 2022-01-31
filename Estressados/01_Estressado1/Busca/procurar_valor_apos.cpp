#include <iostream>
#include <vector>
#include <algorithm>

//se não encontrar, retorna -1
int procurar (int posicao, std::vector<int> vetor, int valor)
{
    for (int contador = posicao; contador < (int) vetor.size(); contador++)  {
        if (vetor[contador] == valor)
            return contador;
    }
    return -1;
}

int main()
{
    std::cout << procurar(1, {3, 5, 7, 6, 3, 1, -7}, 3) << "\n";  // 4

    std::cout << procurar(4, {3, 5, 7, 6, 3, 1, -7}, 3) << "\n"; // 4

    std::cout << procurar(1, {3, 5, 7, 6, 3, 1, -7}, 2) << "\n"; // -1

    return 0;
}