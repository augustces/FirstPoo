#include <iostream>
#include <vector>

std::vector<int> clone(const std::vector<int>& vetor)
{
    std::vector<int> clone{ };
    clone = vetor;
    return clone;
}

void printar(const std::vector<int>& vetor)
{
    std::cout << "[ ";
    for (int i {0}; i < (int) vetor.size(); i++)
    {
        std::cout << vetor[ i ] << ", ";
    }
    std::cout << "] \n";
}

int main()
{
    std::vector<int> vetclone{ {1, 5, 7, 8, 3, 4, 9} };
    printar(clone(vetclone));

    vetclone = {3, 6, 2, 7, 9, 2};
    printar(clone(vetclone));

    vetclone = {2, 6, 8, 5, 4, 3};
    printar(clone(vetclone));

    return 0;
}