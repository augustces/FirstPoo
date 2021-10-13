#include <iostream>
#include <vector>
#include <algorithm>

void apagar (std::vector<int>& vetor, std::vector<int>& vetPosicoes)
{
    for ( int k { 0 }; k < 3; k++ ) {
        vetor.erase( vetor.begin() + vetPosicoes[ 2 - k ] );
    }
}

int trio ( std::vector<int> vetor )
{
    int trios{ 0 };
    int contador{ 0 };
    // vetor para ajudar na contagem
    std::vector<int> vetPosicoes{ };
    
    for ( int i{ 0 }; i < (int) vetor.size() ; i++ ) {
        for ( int k { 0 }; k < (int) vetor.size(); k++ ) {
            if ( abs( vetor[ i ] ) == abs( vetor[ k ] ) ) {
                vetPosicoes.push_back( k );
                contador++;
            }
            if ( contador == 3 ) {
                apagar(vetor, vetPosicoes);
                trios++;
                i = -1;
                break;
            }
        }
        contador = 0;
        vetPosicoes.clear();
    }
    return trios;
}

int main() {
    std::cout << trio( {-2, 3, 6, -2, -8, 5, -9, -3, -4, 9, 2} ) << '\n'; // 1

    std::cout << trio( {6, -2, -9, -6, 9, 2, 5, -6, 9, -2} ) << '\n'; // 3

    std::cout << trio( {3, 6, -3, 9, 8, -9, 4, -9, -6, -3, 9, 3} ) << '\n'; // 2

    return 0;
}