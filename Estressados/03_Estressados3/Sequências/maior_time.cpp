#include <iostream>
#include <vector>

int maiorTime ( const std::vector<int>& vetor )
{
    int maiorTimePositivo {2};
    int maiorTimeNegativo{2};
    int contadorPositivos{0};
    int contadorNegativo{0};

    for ( int i{ 0 }; i < (int) vetor.size() ; i++ ) {

        if ( vetor[ i ] > 0 ) {
            contadorPositivos++;

            if ( contadorPositivos > maiorTimePositivo )
                maiorTimePositivo = contadorPositivos;
            contadorNegativo = 0;
        }

        else {
            contadorNegativo++;

            if ( contadorNegativo > maiorTimeNegativo )            
                maiorTimeNegativo = contadorNegativo;
            contadorPositivos = 0;
        }
    }
    if (maiorTimeNegativo > maiorTimePositivo )
        return maiorTimeNegativo;
    else 
        return maiorTimePositivo;    
}

int main() {
    std::cout << maiorTime( {2, 3, 6, -2, -8, 5, -9, -3, -4, -9, 2} ) << '\n'; // 4

    std::cout << maiorTime( {6, -5, -9, 6, -3, 6, 5, 3, -8, -2} ) << '\n'; // 3

    std::cout << maiorTime( {7, 6, 5, -9, 8, -9, -4, -9, -6, -3, -8, -3} ) << '\n'; // 7

    return 0;
}