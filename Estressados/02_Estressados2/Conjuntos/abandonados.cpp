#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> abandonados ( const std::vector<int>& vetor )
{
    std::vector<int> abandonados { };
    std::vector<int> exclusivos {};
    for ( int i { 0 }; i < (int) vetor.size(); i++ ) {
        int contador{ 0 };
        exclusivos.push_back( vetor[ i ] );
        for (int k { 0 }; k < (int) exclusivos.size(); k++) {
            if ( exclusivos[ k ] == vetor[ i ] )
                contador++;
        }
        if (contador > 1)
            while (contador > 1)
            {
                exclusivos.pop_back();
                abandonados.push_back(vetor[ i ]);
                contador--;
            }
    }
    return abandonados;
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
    std::vector<int> vetAuxiliar{ {1, 3, 4, 3, -1, -2, -2} }; //{1, 3, 4, 3, -1, -2, -2} -> {3, -2}
    printar ( abandonados( vetAuxiliar ) );

    vetAuxiliar = {5, -50, 5, -6, -50, -50, 4, 6} ; //{5, -50, 5, -6, -50, -50, 4, 6} -> {5, -50, -50}
    printar ( abandonados( vetAuxiliar ) );

    vetAuxiliar = {93, -52, -6, -52, 3, -6, 4, 35, 92} ; //{93, -52, -6, -52, 3, -6, 4, 35, 92} -> {-52, -6}
    printar ( abandonados( vetAuxiliar ) );

    return 0;
}