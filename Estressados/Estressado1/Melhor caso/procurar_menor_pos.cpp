#include <iostream>
#include <vector>
#include <algorithm>

int posmenor (std::vector<int> vetor)
{
    int pos{};
    int valor{vetor[0]};
    for (int i = 0; i < (int) vetor.size(); i++) {
        if (valor > vetor[i]){
            pos = i;
            valor=vetor[i];
        }
    }
    return pos;
}

int main()
{
   std::cout << posmenor({1, 7, -99, -69, -1, 2}) << "\n"; //2

   std::cout << posmenor({8, 3, 9, 69, -9, 4}) << "\n"; //4

   std::cout << posmenor({2, 5, -8, -9, 1, -2}) << "\n"; //3
    
    return 0;
}