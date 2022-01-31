#include <iostream>
#include <vector>
#include <algorithm>

int menor (std::vector<int> vetor)
{
    int valor{vetor[0]};
    for (int i = 1; i < (int) vetor.size(); i++) {
        if (valor > vetor[i])
            valor = vetor[i];
    }
    return valor;
}

int main()
{
    std::cout << menor({1, 7, -99, -69, -1, 2}) << "\n"; //-99

    std::cout << menor({-3, -90, 5, 8, 9, 10}) << "\n"; //-90
    
    std::cout << menor({1, 3, 6, 8, 9, 3}) << " \n"; //1
    
    return 0;
}