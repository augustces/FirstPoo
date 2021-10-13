#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}

std::vector<int> remove ( std::vector<int> vetor, int x )
{
    for ( int i{ 0}; i < (int) vetor.size() ; i++ ) {

        if ( vetor[ i ] == x ) 
            vetor.erase( vetor.begin() + i );

    }
    return vetor;
}

int main() {
    std::cout << remove( {-2, 3, 6, -2, -8, 5, -9, -3, -4, 9, -2}, -2 ) << '\n'; // 3, 6, -8, 5, -9, -3, -4, 9

    std::cout << remove( {6, -5, -9, 6, -3, 6, 5, -3, -8, -2}, -3 ) << '\n'; // 6, -5, -9, 6, 6, 5, -8, -2

    std::cout << remove( {7, 6, 5, 9, 8, -9, 4, -9, -6, -3, -8, -3}, 4 ) << '\n'; // 7, 6, 5, 9, 8, -9, -9, -6, -3, -8, -3

    return 0;
}