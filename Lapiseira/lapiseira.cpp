#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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

    int desgastePorFolha()
    {
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
    std::vector<Grafite> grafites;
    int capacidade{0};

    // construtor, funções e métodos
    Lapiseira(float calibre)
    {
        this->calibre;
    }

    void remover(int value)
    {
        std::vector<Grafite> copia;
        for ( int k { 0 }; k < (this->capacidade); k++ ) {
            if ( k < value) {
                Grafite auxiliar{this->grafites[k]};
                this->grafites[k] = *new Grafite;
            }
            else {
                copia.push_back( this->grafites[ k ] );
            }            
        }
        for ( int k{ 0 }; k < value; k++) 
            copia.push_back( 0 );
        
        this->grafites = copia;
    }

    void write(int folhas)
    {
        int contador{0};
        for ( int k { 0 }; k < (this->capacidade); k++) {
            if (this->grafites[k].dureza != "null") {
                int value = this->grafites[k].desgastePorFolha();
                
                while (this->grafites[k].tamanho != 0 && folhas != 0)
                {

                    if ((this->grafites[k].tamanho - value) > 0)
                    {
                        this->grafites[k].tamanho -= value;
                        folhas--;
                        contador++;
                    }
                    else if ((this->grafites[k].tamanho - value) == 0) {
                        contador++;
                        this->remover(1);
                    }
                    else
                    {
                        this->remover(1);   
                    } 
                }
            }
            else {
                std::cout << "fail: folhas escritas completas: " << contador << '\n';
                std::cout << "warning: grafite acabou\n";
                break;
            }
        }
    }

    bool inserir(Grafite& grafite)
    {
        for ( int k { 0 }; k < (this->capacidade); k++) {
            if (this->grafites[ k ].dureza == "null")
        {

            if ((float)this->calibre != grafite.calibre)
                std::cout << "fail: calibre incompativel\n";

            else
                this->grafites[ k ] = grafite;

            return true;
        }
        }
        
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Lapiseira *lapiseira)
    {
        os << "Calibre: " << lapiseira->calibre << "\n";

        for ( int k { 0 }; k < (lapiseira->capacidade); k++) {

            if (lapiseira->grafites[k].dureza == "null")
            {
                os << "Grafite: " << lapiseira->grafites[k].dureza << "\n";
            }
            else {
                os << "Grafite: [" << lapiseira->grafites[k].calibre << ":";
                os << lapiseira->grafites[k].dureza << ":";
                os << lapiseira->grafites[k].tamanho << "]\n";
            }
        }
        return os;
    }
};

int main()
{
    Lapiseira *lapiseira = new Lapiseira{0};

    while (true)
    {
        std::string comando{""};
        std::string linha{""};
        std::stringstream ss;

        std::cin >> comando;

        getline(std::cin, linha);

        ss << linha;
        if (comando == "init") {
            if (lapiseira->calibre == 0) {
            ss >> lapiseira->calibre;
            std::cout << "Quantos grafites a lapiseira suporta?\n";
            std::cin >> lapiseira->capacidade;
            for (int k {0}; k < (lapiseira->capacidade); k++)
                lapiseira->grafites.push_back(0);
            }
            else 
                std::cout << "Lapiseira ja existe, use-a! \n";
        }   

        else if (comando == "show")
            std::cout << (lapiseira);

        else if (comando == "inserir")
        {
            Grafite grafInserido{};
            ss >> grafInserido.calibre;
            ss >> grafInserido.dureza;
            ss >> grafInserido.tamanho;
            if (!(lapiseira->inserir(grafInserido)))
                std::cout << "fail: lapiseira cheia\n";
        }
        else if (comando == "remover")
        {
            std::cout << "remover quantos grafites?\n";
            int auxiliar{};
            std::cin >> auxiliar;
            if (auxiliar > lapiseira->capacidade)
                std::cout << "Fail: Não há isso tudo de grafite\n";
            else
                lapiseira->remover(auxiliar);
        }

        else if (comando == "write")
        {
            int auxiliar{0};
            ss >> auxiliar;
            lapiseira->write(auxiliar);
        }

        else if (comando == "end")
            break;

        else
            std::cout << "comando invalido\n";
    }

    delete std::exchange(lapiseira, nullptr);

    return 0;
}