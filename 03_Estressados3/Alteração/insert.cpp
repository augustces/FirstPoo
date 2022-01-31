#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}

std::vector<int> insert ( std::vector<int> vetor, int x, int y )
{
    for ( int i{ 0}; i < (int) vetor.size() ; i++ ) {

        if ( i == y ) 
            vetor.insert( vetor.begin() + i, x );

    }
    return vetor;
}

int main() {
    std::cout << insert( {-2, 3, 6, -2, -8, 5, -9, -3, -4, 9, -2}, -92, 2 ) << '\n'; // -2, 3, -92, 6, -2, -8, 5, -9, -3, -4, 9, -2

    std::cout << insert( {6, -5, -9, 6, -3, 6, 5, -3, -8, -2}, -73, 4 ) << '\n'; // 6, -5, -9, 6, -73, -3, 6, 5, -3, -8, -2

    std::cout << insert( {7, 6, 5, 9, 8, -9, 4, -9, -6, -3, -8, -3}, 84, 3 ) << '\n'; // 7, 6, 5, 84, 9, 8, -9, 4, -9, -6, -3, -8, -3

    return 0;
}