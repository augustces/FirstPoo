#include <iostream>
#include <vector>

int sozinhos ( const std::vector<int>& vetor )
{
    int sozinhos{0};

    for ( int i{ 0 }; i < ( (int) vetor.size() ); i++ ) {
        if ( i == 0) {
            if ( vetor[ i ] > 0 && vetor[ i + 1 ] < 0 )
                sozinhos++;
            else if ( vetor[ i ] < 0 && vetor[ i + 1 ] > 0 )
                sozinhos++;
        }
        else if ( i == ( (int) vetor.size() - 1 ) ) {
			if ( vetor[ i ] > 0 && vetor[ i - 1 ] < 0 )
                sozinhos++;
            else if ( vetor[ i ] < 0 && vetor[ i - 1 ] > 0 )
                sozinhos++;
        }
        else {
			if ( vetor[ i ] > 0 && vetor[ i + 1 ] < 0 && vetor[ i - 1 ] < 0 )
                sozinhos++;
            else if ( vetor[ i ] < 0 && vetor[ i + 1 ] > 0 && vetor[ i - 1 ] > 0 )
                sozinhos++;
		}
    }
    return sozinhos;
}

int main() {
    std::cout << sozinhos( {2, -3, 6, -2, -8, 5, -9, -3, -4, 9, 2} ) << '\n'; // 4

    std::cout << sozinhos( {6, -5, 3, -9, 6, -3, 6, 5, 3, -8, -2} ) << '\n'; // 6

    std::cout << sozinhos( {7, -6, 5, -9, 8, -9, 4, -9, -6, 3, -8, 3} ) << '\n'; // 10

    return 0;
}
