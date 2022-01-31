#include <iostream>
#include <vector>
#include <algorithm>

bool existe (std::vector<int> vetor, int valor)
{
    for (int i = 0; i < (int) vetor.size(); i++) {
        if (valor == vetor[i])
            return true;
    }
    return false;
}

int main()
{
    //se true, então printa 1
    // se false, então printa 0
    std::cout << existe({3, 7, 9, 80, 7}, 3) << '\n'; //true
    
    std::cout << existe({3, 7, 9, 80, 7}, 4) << '\n'; //false

    return 0;
}