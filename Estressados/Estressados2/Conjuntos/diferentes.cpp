#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> diferentes ( const std::vector<int>& vetor )
{
    std::vector<int> diferentes { };
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        int contador{ 0 };
        diferentes.push_back( abs(vetor[ i ]) );
        for (int k { 0 }; k < (int) diferentes.size(); k++) {
            if ( diferentes[ k ] == abs(vetor[ i ]) )
                contador++;
        }
        if (contador > 1)
            while (contador > 1)
            {
                diferentes.pop_back();
                contador--;
            }
            
    }
    return diferentes;
}

void printar ( const std::vector<int>& vetor )
{
    std::cout << "[ ";
    for ( int i {0}; i < (int) vetor.size(); i++ ) {
        std::cout << vetor[ i ] << ", ";
    }
    std::cout << "]\n";
}

int main() 
{
    std::vector<int> vetAuxiliar{ {1, 3, 4, 3, -1, -2, -2} }; //{1, 3, 4, 3, -1, -2, -2} -> {1, 3, 4, 2}
    printar ( diferentes( vetAuxiliar ) );

    vetAuxiliar = {5, -50, 5, -6, -50, -50, 4, 6} ; //{5, -50, 5, -6, -50, -50, 4, 6} -> {5, 50, 6, 4}
    printar ( diferentes( vetAuxiliar ) );

    vetAuxiliar = {93, -52, -6, -52, 3, -6, 4, 35, 92} ; //{93, -52, -6, -52, 3, -6, 4, 35, 92} -> {93, 52, 6, 3, 4, 35, 92}
    printar ( diferentes( vetAuxiliar ) );

    return 0;
}