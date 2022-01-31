#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Client {
    std::string fone;
    std::string id;

    public:
    Client (std::string id = "-", std::string fone = "") :
    id { id }, fone { fone } {
    }

    std::string toString () {
        return this->id + ":" + this->fone + " ";
    }

    std::string getFone () {
        return fone;
    }

    std::string getId () {
        return id;
    }

    void setFone(std::string fone) {
        this->fone = fone;
    }

    void setId (std::string id) {
        this->id = id;
    }

};

class Sala {
    std::vector<std::shared_ptr<Client>> cadeiras;

    int procurar(std::string id) {
        for (int i{0}; i < (int) this->cadeiras.size(); i++) {
                if (this->cadeiras[ i ] != nullptr && this->cadeiras[ i ]->getId() == id)
                    return i;
        }
        return -1;
    }

public:

    Sala (int capacidade = 0) {
        this->init(capacidade);
    }

    void init (int capacidade) {
        std::vector<std::shared_ptr<Client>> auxiliar;
        for (int i{0}; i < capacidade; i++) {
            auxiliar.push_back(nullptr);
        }
        this->cadeiras = auxiliar;
    }

    void cancelar (std::string id) {
        int aux = procurar(id);
        if (aux == (-1)) {
            std::cout << "fail: cliente nao esta no cinema\n";
        }
        else
            this->cadeiras[aux] = nullptr;
    }

    bool reservar(std::string id, std::string fone, int ind) {
        if (ind >= this->cadeiras.size()) {
            std::cout << "fail: cadeira invalida\n";
            return false;
        }

        if (procurar(id) != -1) {
            std::cout << "fail: cliente ja esta no cinema\n";
            return false;
        }

        if (this->cadeiras[ind] == nullptr ){
    
            this->cadeiras[ind] = std::make_shared<Client>(id, fone);
            
            return true;
            
        }
        
        std::cout << "fail: cadeira ja esta ocupada\n";
        return false;
    }

    std::string toString () {
        std::string texto;
        for (int i{0}; i < this->cadeiras.size(); i++) {
            if (cadeiras[i] == nullptr)
                texto += "- "    ;
            else
                texto += cadeiras[i]->toString();
        }
        return "[ " + texto + "]\n";
    }

};

int main () {
    std::shared_ptr<Sala> cinema (new Sala ());

    while (true) {
        std::string comando;
        std::cin >> comando;

        std::string linha;
        getline (std::cin, linha);

        std::stringstream ss(linha);

        if (comando == "init") {
            int cap;
            ss >> cap;
            cinema->init(cap);
        }
        else if (comando == "show") {
            std::cout << cinema->toString();
        }
        else if (comando == "reservar") {
            std::string fone;
            std::string id;

            ss >> id;
            ss >> fone;

            int ind;
            ss >> ind;

            cinema->reservar(id, fone, ind);
        }
        else if (comando == "cancelar") {
            std::string auxiliar;
            ss >> auxiliar;
            cinema->cancelar(auxiliar);
        }
        else if (comando == "end")
            break;
        else 
            std::cout << "fail: comando invalido\n";
        }

    return 0;
}