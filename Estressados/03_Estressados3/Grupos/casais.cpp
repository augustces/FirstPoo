#include <iostream>
#include <vector>
#include <algorithm>

int casais ( std::vector<int> vetor )
{
    int numCasais{ 0 };
    for ( int i{ 0 }; i < (int) vetor.size() ; i++ ) {
        auto auxiliar { std::find( ( vetor.begin() ), vetor.end(), ( ( vetor[ i ] )*( -1 ) ) ) };
        if ( auxiliar != vetor.end()) {
            vetor.erase( auxiliar );
            vetor.erase(  std::find( vetor.begin(), vetor.end(), ( vetor[ i ] ) )  );
            
            numCasais++;
            i = -1;
        }
    }
    return numCasais;
}

int main() {
    std::cout << casais( {-2, 3, 6, -2, -8, 5, -9, -3, -4, 9, 2} ) << '\n'; // 3

    std::cout << casais( {6, -5, -9, -6, 3, 2, 5, -3, 9, -2} ) << '\n'; // 5

    std::cout << casais( {7, 6, 5, 9, 8, -9, 4, -9, -6, -3, -8, 3} ) << '\n'; // 4

    return 0;
}