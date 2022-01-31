#include  <iostream>
#include <vector>

int maiorOcorrencia ( const std::vector<int>& vetor )
{
    int maiorOcorrencia{1};
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        int contador{ 0 };
        for (int k { 0 }; k < (int) vetor.size(); k++ ) {
            if ( abs(vetor[ i ]) == abs( vetor[ k ] ) )
                contador++;
        }
        if ( contador > maiorOcorrencia )
            maiorOcorrencia = contador;
    }
    return maiorOcorrencia;
}

int main() 
{
    std::cout << maiorOcorrencia( {-3, 5, 8, -5, 4, 3, -5, 8}) << '\n'; //3

    std::cout <<  maiorOcorrencia( {-1, 5, -8, 5, -8, 3, 8, 4, 8}) << '\n'; //4

    std::cout <<  maiorOcorrencia( {-5, 6, -9, -8, 6, 8, 4, -3, -4}) << '\n'; //2

    return 0;
}