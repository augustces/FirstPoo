#include <iostream>
#include <unordered_map>
#include <map>

//unordered map
int main1 () {
    std::unordered_map<int, std::string> cadeiras;
/* faz um calculo para encontrar o valor inteiro*/
    cadeiras[1] = "maria";
    cadeiras[5] = "joao";
    cadeiras[8] = "maria alves";

    //for (std::map<int, std::string> pair : cadeiras) {

//    }
    for (auto [chave, valor] : cadeiras ){
        //desmontando o map
    }

    return 0;
}

//map
int main2() {
    //ordena sempre pela chave
    std::map <std::string, int> idades;
    idades["joao"] = 20;
    idades["maria"] = 40;
//escreve a idade na chave joao que ja foi criada
    idades["joao"] = 50;
}
