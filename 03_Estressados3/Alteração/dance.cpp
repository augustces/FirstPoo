#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}

std::vector<int> dance ( std::vector<int> vetor )
{
    int i{0};
    while ( i < ( (int) vetor.size() - 1 ) )
    {

         if ( abs( vetor[ i ] ) == abs( vetor[ i + 1 ] ) ) {
            vetor.erase( vetor.begin() + i );
            vetor.erase( vetor.begin() + i );
            i = 0;
            continue;
         }
         i++;
    }
    
    return vetor;
}

int main() {
    std::cout << dance( {-2, 3, 6, -2, -8, 8, -9, -3, -4, 9, -2}) << '\n'; // -2, 3, 6, -2, -9, -3, -4, 9, -2

    std::cout << dance( {6, -5, -9, 6, 3, -3, 6, 3, -3, 2, -2} ) << '\n'; // 6, -5, -9

    std::cout << dance( {7, 6, 4, 9, -8, 8, -9, 4, -9, -6, -3, -8, -3} ) << '\n'; // 7, 6, -9, -6, -3, -8, -3

    return 0;
}