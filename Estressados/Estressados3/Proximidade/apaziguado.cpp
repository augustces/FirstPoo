#include <iostream>
#include <vector>

std::vector<int> apaziguados ( const std::vector<int>& vetor) 
{
    std::vector<int> posicaoApaziguados {};
    for ( int i { 0 }; i < (int) vetor.size() ; i++ ) {
        if ( i ==0 ) {
            if ( abs( vetor[ i ] ) > 80 && ( abs( vetor[ i + 1 ] ) < 10 ) )
            posicaoApaziguados.push_back(i);
        }
        else if ( i == ((int) vetor.size() -1 ) ) {
            if ( abs( vetor[ i ] ) > 80 && ( abs( vetor[ i - 1 ] ) < 10) )
            posicaoApaziguados.push_back(i);
        }
        else {
            if ( abs( vetor[ i ] ) > 80  && ( abs( vetor[ i - 1 ]  )< 10 || abs( vetor[ i + 1 ] ) < 10 ) )
            posicaoApaziguados.push_back(i);
         }
        }
        
    return posicaoApaziguados;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}

int main()
{
    std::cout << apaziguados( {99, 9, -45, 3, -98, 35, -52} ) << '\n'; //0, 4

    std::cout << apaziguados( {-95, 50, 6, -72, 46, 5, -85} ) << '\n'; //6

    std::cout << apaziguados( {99, -2, 5, 81, -1, 7, -90} ) << '\n'; //0, 3, 6

    return 0;
}