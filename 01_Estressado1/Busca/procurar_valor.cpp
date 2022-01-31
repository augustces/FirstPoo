#include <iostream>
#include <vector>
#include <algorithm>

int procurar(std::vector<int> vetor, int valor)
{
    for (int i = 0; i < (int) vetor.size(); i++) {
        if (valor == vetor[i])
            return i;
    }
    return -1;
}

int main()
{
    std::cout << procurar({1, 2, 4, 6, 7, -3}, -3) << "\n"; // 5
    
    std::cout << procurar({2, 5, 7, 8, 4, 4}, 4) << "\n"; // 4
    
    std::cout << procurar({2, 5, 6, -9, -3, 6}, -1) << "\n"; // -1
    
    return 0;
}