#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>



struct Grafite
{

    float calibre;
    std::string dureza;
    int tamanho; // milimetros

    // construtor, funções, métodos
    Grafite(float calibre = 0, std::string dureza = "null", int tamanho = 0) : calibre{calibre}, dureza{dureza}, tamanho{tamanho}
    {
    }

    int desgastePorFolha () {
        if (this->dureza == "HB")
            return 1;
        if (this->dureza == "2B")
            return 2;
        if (this->dureza == "4B")
            return 4;
        if (this->dureza == "6B")
            return 6;
        return 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Grafite &grafite)
{
    os << "Calibre: " << grafite.calibre << " mm, ";
    os << "Dureza: " << grafite.dureza << ", ";
    os << "Tamanho: " << grafite.tamanho << " mm \n";

    return os;
}

};

struct Lapiseira
{

    float calibre{0.0};
    Grafite grafite;

    // construtor, funções e métodos
    Lapiseira(float calibre)
    {
        this->calibre;
    }

    Grafite remover () {
        Grafite auxiliar {this->grafite};
        this->grafite = *new Grafite ();

        return auxiliar;
    }

    void write (int folhas) {
        int contador{0};
        int value = this->grafite.desgastePorFolha();
        while (this->grafite.tamanho !=0 && folhas != 0) {
            
            if (this->grafite.tamanho - value > 0) {
                this->grafite.tamanho -= value;
                folhas--;
                contador++;
            }
            else {
                if (contador > 0)
                    std::cout << "fail: folhas escritas completas: " << contador << '\n';
                std::cout << "warning: grafite acabou\n";
                this->remover();
                break;
            }
        }
    }

    bool inserir (Grafite grafite) {
        
        if (this->grafite.dureza == "null") {

            if((float)this->calibre != grafite.calibre) 
                std::cout << "fail: calibre incompativel\n";
            
            else 
                this->grafite = grafite;    

            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Lapiseira* lapiseira)
{
    os << "Calibre: " << lapiseira->calibre << ", ";

    if (lapiseira->grafite.dureza == "null" ) {
        os << "Grafite: " << lapiseira->grafite.dureza << "\n";
        return os;
    }
    
    os << "Grafite: [" << lapiseira->grafite.calibre << ":";
    os << lapiseira->grafite.dureza << ":";
    os <<  lapiseira->grafite.tamanho << "]\n";

    return os;
}

};

int main()
{
    Lapiseira* lapiseira = new Lapiseira{0};
    
    while ( true ) {
        std::string comando{""};
        std::string linha{""};
        std::stringstream ss;
    
        std::cin >> comando;
        
        getline(std::cin, linha);

        ss << linha;
        if ( comando == "init" ) 
            ss >> lapiseira->calibre;

        else if ( comando == "show" ) 
            std::cout << (lapiseira);

        else if ( comando == "inserir" ) {
            Grafite grafInserido {};
            ss >> grafInserido.calibre;
            ss >> grafInserido.dureza;
            ss >> grafInserido.tamanho;
            if ( !(lapiseira->inserir(grafInserido)) ) 
              std::cout << "fail: ja existe grafite \n";
        }
        else if ( comando == "remover" ) {
            lapiseira->remover();
        }

        else if ( comando == "write" ) {
            int auxiliar {0};
            ss >> auxiliar;
            lapiseira->write(auxiliar);
        }
        
         else if ( comando == "end" )
            break;

        else 
            std::cout << "comando invalido\n";

    }

    delete std::exchange(lapiseira, nullptr);

    return 0;
}