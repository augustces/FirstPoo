#include <iostream>
#include <vector>

int quantosTimes ( const std::vector<int>& vetor )
{
    int numTimes{0};
    int contadorPositivos{0};
    int contadorNegativo{0};

    for ( int i{ 0 }; i < (int) vetor.size() ; i++ ) {

        if ( vetor[ i ] > 0 ) {
            contadorPositivos++;

            if ( contadorPositivos == 2 )
                numTimes++;
            contadorNegativo = 0;
        }

        else {
            contadorNegativo++;

            if ( contadorNegativo == 2 )
                numTimes++;
            contadorPositivos = 0;
        }
    }
    return numTimes;
}

int main() {
    std::cout << quantosTimes( {2, 3, 6, -2, -8, 5, -9, -3, -4, 9, 2} ) << '\n'; // 4

    std::cout << quantosTimes( {6, -5, -9, 6, -3, 6, 5, 3, -8, -2} ) << '\n'; // 3

    std::cout << quantosTimes( {7, 6, 5, 9, 8, -9, 4, -9, -6, -3, -8, -3} ) << '\n'; // 2

    return 0;
}