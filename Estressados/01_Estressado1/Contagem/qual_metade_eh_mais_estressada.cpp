#include <iostream>
#include <vector>
#include <algorithm>

std::string qualmetade(std::vector<int> vetor)
{
    int sep{(int) (vetor.size()/2)}; //separador do vetor
    int prim{0}; //soma da primeira parte
    int seg{0}; //soma da segunda parte
    for (int i = 0; i < sep; i++) {
        prim += abs(vetor[i]);
        seg += abs(vetor[(int) vetor.size() - 1 - i ]);
    }
    if (prim > seg)
        return "primeira";
    else if (seg > prim)
        return "segunda";
    else 
        return "empate";
}

int main()
{
    std::cout << qualmetade({-1, 2, 3, -9, -87, 69}) << '\n'; //segunda

    std::cout << qualmetade({-10, 42, 2, -7, -8, 9}) << '\n'; //primeira

    std::cout << qualmetade({70, 29, 4, -99, -3, 1}) << '\n'; //empate

    return 0;
}