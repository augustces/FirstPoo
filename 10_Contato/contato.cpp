#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Fone {
    std::string id;
    std::string number;

    public:
    Fone (std::string id, std::string number) {
        this->id = id;
        this->number = number;
    }

    bool validate (std::string number) {
        for (int i{0}; i < (int) number.length(); i++){
            if ((number[i] < 48 || number[i] > 57) && number[i] != '(' && number[i] != ')' && number[i] != '.')
                return false;
        }
        return true;
    }

    std::string toString () {
        std::string texto;
        texto += ":" + this->id + ":" + this->number;

        return texto;
    }

    std::string getId() {
        return id;
    }

    std::string getNumber () {
        return number;
    }

    void setId (std::string id) {
        this->id = id;
    }

    void setNumber (std::string number) {
        this->number = number;
    }
};

class Contact {
    std::string prefix;
    std::string name;
    std::vector<Fone> fones {};

   public:
    Contact ( std::string name = "" ) {
        this->name = name;
    }

    void addFone (Fone fone) {
        if ( fone.validate( fone.getNumber()) )
            this->fones.push_back(fone);
        else
            std::cout << "fail: invalid number\n";
    }

    void novo () {
        fones.clear();
    }

    void rmFone (int index = (-1)) {

            if ((index >= 0 && index < (int) this->fones.size()) && (int) this->fones.size() > 0)
            this->fones.erase(this->fones.begin() + index);
        else {
            std::cout << "nao foi possivel remover\n";
        }
    }

    std::string toString () {
        std::string texto;
        for (int i{0}; i < (int) fones.size(); i++) {
            texto += " [" + std::to_string(i) + fones[i].toString() + "]";
        }

        return "- " + this->name + texto + "\n";
    }

    std::vector<Fone> getFones () {
        return fones;
    }

    std::string getName () {
        return name;
    }

    void setName (std::string name) {
        this->name = name;
    }
};

int main() {
    Contact *contato = new Contact();

    while (true) {
        std::string cmd;
        std::string linha;
        std::cin >> cmd;
        getline (std::cin, linha);
        std::stringstream ss(linha);

        if (cmd == "init") {
            std::string nome;
            
            if ( !(linha.empty()) )
                ss >> nome;
            else
                continue;
            if (contato->getName() == "")
                contato->setName(nome);
            else {
                contato->setName(nome);
                contato->novo();
            }
        }
        else if (cmd == "show") {
            std::cout << contato->toString();
        }
        else if (cmd == "add") {
            std::string op;
            std::string num;
            ss >> op >> num;
            Fone fone(op, num);
            contato->addFone(fone);
        }
        else if (cmd == "rm") {
            char index;
            ss >> index;
            contato->rmFone(index - 48);
        }
        else if (cmd == "end")
            break;
        else 
            std::cout << "fail: comando invalido\n";
    }

    return 0;
}