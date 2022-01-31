#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

struct Pessoa {
    int idade;
    std::string nome;

    Pessoa(std::string nome = "null", int idade = 0) :
    nome{ nome }, idade{ idade } {
    }

    friend std::ostream &operator<<(std::ostream &os, const Pessoa pessoa)
        {
            os << "Nome: " << pessoa.nome << "\n";

            os << "Idade: " << pessoa.idade << "\n";
            
            return os;
        }

};

struct Moto {
    Pessoa pessoa{"null", 0};
    int potencia{1};
    int tempo{0};

    Moto(int potencia) :
    potencia{ potencia } {
    }

    void buy(int tempo) {
            this->tempo += tempo;
    }

    void drive(int tempo) {

        if (pessoa.idade > 10) {
            std::cout << "fail: muito grande para andar de moto\n";
        }
        else {
            if (this->tempo == 0) {
                std::cout << "fail: tempo zerado\n";
            }
            else {
                if (!(this->vazia())) {
                    if (this->tempo > tempo)
                        this->tempo -= tempo;
                    else 
                        std::cout << "fail: andou " << this->tempo << " min e acabou o tempo\n";
                }
            }
        }
    }

    void honk () {
        if (!(this->vazia()))
            std::cout << "P";
            int i { this->potencia };
            while ( i > 0)
            {
               std::cout << "e";
               i--;
            }
             std::cout << "m\n";
    }

    bool in (Pessoa pessoa) {

        if (this->pessoa.nome == "null") {
            this->pessoa.nome = pessoa.nome;
            this->pessoa.idade = pessoa.idade;
            return true;
        }

       std::cout << "fail: moto ocupada\n";
        return false;
    }

    Pessoa out() {
        if (!(this->vazia())) {
            Pessoa* auxiliar = new Pessoa{"null", 0};
            this->pessoa.nome = auxiliar->nome;
            this->pessoa.idade = auxiliar->idade;
            this->tempo = 0;
        }
        
        return this->pessoa;
    }

    friend std::ostream &operator<<(std::ostream &os, const Moto *moto)
    {
        os << "potencia: " << moto->potencia ;

        os << ", minutos: " << moto->tempo ;

        os << ", pessoa: ";

            if (moto->pessoa.nome == "null")
            {
                os << moto->pessoa.nome << "\n";
            }
            else {
                os << "[" << moto->pessoa.nome << ":";
                os << moto->pessoa.idade << "]\n";
            }
        return os;
    } 

        bool vazia () {
            if (this->pessoa.nome == "null") {
                std::cout << "fail: moto vazia\n";
                return true;
            }
            return false;
        }

};

int main() {
Moto* moto = new Moto{1};

    while (true)
    {
        std::string comando{""};
        std::string linha{""};
        std::stringstream ss;

        std::cin >> comando;

        getline(std::cin, linha);

        ss << linha;
        if (comando == "buy") {
            int tempo;
            ss >> tempo;
            moto->buy(tempo);
        }   

        else if (comando == "init") {
            if (moto->potencia > 1) {
                std::cout << "a moto ja possui uma potencia definida\n";
            }
            else{
                int aux;
                ss >> aux;
                moto->potencia = aux;
            }
        }   

        else if (comando == "show")
            std::cout << (moto);

        else if (comando == "in")
        {
           Pessoa kid;
           ss >> kid.nome >> kid.idade;
           moto->in(kid);
        }

        else if (comando == "out")
        {
            moto->out();
        }

        else if (comando == "honk")
        {
            moto->honk();
        }

        else if (comando == "drive") {
            int tempo;
            ss >> tempo;
            moto->drive(tempo);
        }   

        else if (comando == "end")
            break;

        else
            std::cout << "comando invalido\n";
    }

    return 0;
} 