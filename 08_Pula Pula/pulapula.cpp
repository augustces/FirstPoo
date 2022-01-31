#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <string>

class Kid {
    int idade;
    std::string nome;

public:
    Kid (std::string nome = "", int idade = 0) :
    idade { idade }, nome { nome } {
    }

    void setNome(std::string nome) {
        this->nome = nome;
    }

    void setIdade (int idade) {
        this->idade = idade;
    }

    int getIdade () {
        return this->idade;
    }

    std::string getNome() {
        return this->nome;
    }

    std::string toString  () {
        std::string texto {this->nome + ":" + std::to_string(this->idade)};
        
        return texto;
    }
};

class Trampolim {
    std::list <std::shared_ptr<Kid>> dentro;
    std::list<std::shared_ptr<Kid>> fila;

    static bool vazia(std::list<std::shared_ptr<Kid>> fila) {
        if (fila.empty())
            return true;
        return false;
    }

    static int procurar (std::string nome, std::list<std::shared_ptr<Kid>>& vet) {
        int i{0};
        for (auto& it : vet) {
            
            if (it->getNome() == nome) {
                return i;
            }
            i++;
        }
        return (-1);
    }

    static std::string montarString (std::list<std::shared_ptr<Kid>> vet) {
        std::string texto;
         if (!(vazia(vet)))
            for (int it {(int)vet.size() - 1}; it >= 0; it--) {
                auto x = std::next(vet.begin(), it);
                texto += (*x)->toString() + " ";
            }
        return texto;
    }

public:

    Trampolim () {
    }

    void arrive(std::shared_ptr<Kid> kid) {
        fila.push_back(kid);
    }

    void in() {
        if (vazia(this->fila)) {
            std::cout << "fail: nao ha ninguem na fila\n";
        }
        else {
            this->dentro.push_back(*(this->fila.begin()));
            this->fila.pop_front();
        }
    }

    void out() {
        if (vazia(this->dentro)) {
            std::cout << "fail: nao ha ninguem no pula pula\n";
        }
        else {
            this->fila.push_back(*(this->dentro.begin()));
            this->dentro.pop_front();
        }
    }

    std::shared_ptr<Kid> remove (std::string nome) {
        int x = procurar(nome, this->fila);
        int y = procurar(nome, this->dentro);

        if (x != -1) {
            auto aux = std::next(fila.begin(), x);
            fila.erase(std::next(fila.begin(), x));
            return (*aux);
        }
        else if (y != -1) {
            auto aux = std::next(dentro.begin(), y);
            dentro.erase(std::next(dentro.begin(), y));
            return (*aux);
        }
       return nullptr;
    }

    void fechar() {
        fila.clear();
        dentro.clear();
    }

    std::string toString  () {
        std::string texto {"=> "};
       
       texto += montarString(this->fila);

        texto += "=> [ ";

        texto += montarString(this->dentro);

        texto += "]\n";

        return texto;
    }

};

int main() {
    std::shared_ptr<Trampolim> pula (new Trampolim ());

    while (true)
    {
        std::string comando{""};
        std::string linha{""};

        std::cin >> comando;
        getline(std::cin, linha);

        std::stringstream ss(linha);

        if (comando == "arrive") {
            
            std::string nome;
            int idade;
            ss >> nome;
            ss >> idade;
            std::shared_ptr<Kid> auxiliar ( new Kid(nome, idade));

            pula->arrive(auxiliar);
        }
        else if (comando == "in") {
            pula->in();
        }
        else if(comando == "out") {
            pula->out();
        }
        else if(comando == "show") {
            std::cout << pula->toString();
        } 
        else if (comando == "remove") {
            std::string nome;
            ss >> nome;
            pula->remove(nome);
        }
        else if (comando == "fechar") {
            pula->fechar();
        }
        else if (comando == "end")
            break;
        else 
            std::cout << "fail: comando invalido\n";
    }
    
    return 0;
}