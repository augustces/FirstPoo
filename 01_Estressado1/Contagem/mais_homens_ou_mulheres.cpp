#include <iostream>
#include <vector>
#include <algorithm>

std::string maishoum(std::vector<int> vetor)
{
    int contm{0}; // contador para as mulheres
    int conth{0}; // contador para os homens
    for (int i = 0; i < (int) vetor.size(); i++) {
        if (vetor[i] > 0)
            conth++;
        if (vetor[i] < 0)
            contm++;
    }
    if (contm > conth)
        return "mulheres";
    else if (contm == conth)
        return "empate";
    else 
        return "homens";
}

int main()
{
    std::cout << maishoum({-1, 2, 3, -9, -87, 69}) << '\n'; //empate

    std::cout << maishoum({-10, 42, -2, -7, -8, 9}) << '\n'; //mulheres

    std::cout << maishoum({7, 21, 4, -99, -3, 5}) << '\n'; //homens

    return 0;
}