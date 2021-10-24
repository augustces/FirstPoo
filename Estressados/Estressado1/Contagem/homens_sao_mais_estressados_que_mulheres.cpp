#include <iostream>
#include <vector>
#include <algorithm>

std::string maishoum(std::vector<int> vetor)
{
    float somam{0.0}; // soma para as mulheres
    float somah{0.0}; // soma para os homens

    int contm{0}; // contador para mulheres
    int conth{0}; // contador para homens

    for (int i = 0; i < (int)vetor.size(); i++)
    {
        if (vetor[i] > 0)
            somah += vetor[i];
        conth++;
        if (vetor[i] < 0)
            somam += abs(vetor[i]);
        contm++;
    }

    if ((somam / contm) >= (somah / conth) || vetor.empty() == true )
        return "não";
    else
        return "sim";
}

int main()
{
    std::cout << maishoum({-1, 92, 3, -9, -87, -69}) << '\n'; //não

    std::cout << maishoum({-10, 42, -2, -7, -8, 9}) << '\n'; //sim

    std::cout << maishoum({}) << '\n'; //não

    return 0;
}
