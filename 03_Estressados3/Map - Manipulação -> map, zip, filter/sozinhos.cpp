#include  <iostream>
#include <vector>

std::vector<int> sozinhos ( const std::vector<int>& vetor )
{
    std::vector<int> sozinhos{};
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        int contador{ 0 };
        for (int k { 0 }; k < (int) vetor.size(); k++ ) {
            if ( abs(vetor[ i ]) == abs( vetor[ k ] ) )
                contador++;
        }
        if ( contador == 1 )
            sozinhos.push_back( abs( vetor[ i ] ) );
    }
    return sozinhos;
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
    printar( sozinhos( {1, 5, 8, 5, 4, 3, 1, 8})); //4, 3

    printar( sozinhos( {-1, 5, -8, 5, -4, 3, 1, 4, 8})); //3

    printar( sozinhos( {-5, 6, -9, -8, 6, 8, 4, -3, -4})); //5, 9, 3

    return 0;
}