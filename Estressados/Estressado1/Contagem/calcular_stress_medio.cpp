#include <iostream>
#include <vector>
#include <algorithm>

float stressmedio(std::vector<int> vetor)
{
    int i{};
    float media{0};
    for (i = 0; i < (int) vetor.size(); i++) {
        media += abs(vetor[i]);
    }
    return media/(i);
}

int main()
{
    std::cout << stressmedio({-1, 2, 3, -9, -87, 69}) << '\n'; //28.5

    std::cout << stressmedio({-10, 42, 2, -7, -8, 9}) << '\n'; //13

    std::cout << stressmedio({7, 21, 4, -99, -3, 5}) << '\n'; //23.16667

    return 0;
}