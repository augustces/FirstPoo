#include  <iostream>
#include <vector>

//testar se o valor ja está dentro do vetor, para evitar repetição
bool verificar( const std::vector<int>& vetor, int valor ) {
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        if ( valor == vetor[ i ])
            return true;
    }
    return false;
}

std::vector<int> recorrentes ( const std::vector<int>& vetor )
{
    std::vector<int> recorrentes{};
    int maiorOcorrencia{1};
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        int contador{ 0 };
        for (int k { 0 }; k < (int) vetor.size(); k++ ) {
            if ( abs(vetor[ i ]) == abs( vetor[ k ] ) )
                contador++;
        }

        if ( contador > maiorOcorrencia ) {
            maiorOcorrencia = contador;
            recorrentes.clear();
        }

        if ( contador == maiorOcorrencia ) {
            if ( verificar( recorrentes, abs( vetor[ i ] ) ) == false || recorrentes.empty() == true )
                recorrentes.push_back( abs( vetor[ i ] ) );  

        }                     
    }
    return recorrentes;
}

void printar (const std::vector<int>& vetor) {
    std::cout << "[";
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        std::cout << vetor[i] << ", ";
    }
    std::cout << "]\n";
}

int main() 
{
    printar( recorrentes( {-3, 5, 8, -5, 4, 3, -5, 8}) ); //5

    printar( recorrentes( {-1, 5, -8, 5, -8, 3, 8, 4, 8}) ); //8

    printar( recorrentes( {-5, 6, -9, -8, 6, 8, 4, -3, -4}) ); //6, 8, 4

    return 0;
}