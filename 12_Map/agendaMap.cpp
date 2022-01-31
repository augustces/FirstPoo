#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <memory>
#include <vector>

class Fone
{
    std::string id;
    std::string number;

public:
    Fone(std::string id = "", std::string number = "")
    {
        this->id = id;
        this->number = number;
    }

    bool validate(std::string number)
    {
        for (int i{0}; i < (int)number.length(); i++)
        {
            if ((number[i] < 48 || number[i] > 57) && number[i] != '(' && number[i] != ')' && number[i] != '.')
                return false;
        }
        return true;
    }

    std::string getId()
    {
        return this->id;
    }

    std::string getNumber()
    {
        return this->number;
    }

    void setId(std::string id)
    {
        this->id = id;
    }

    void setNumber(std::string number)
    {
        this->number = number;
    }

    std::string toString()
    {
        std::string texto{""};
        texto += ":" + this->getId() + ":" + this->getNumber();
        return texto;
    }
};

class Contact
{
    std::string id;
    std::vector<Fone> fones;

public:
    Contact(std::vector<Fone> fones, std::string id = "")
    {
        this->id = id;
        for (int i{0}; i < (int) fones.size(); i++)
            this->fones.push_back(fones[i]);
    }

    Contact(std::string id = "")
    {
        this->id = id;
    }

    void addFone(Fone fone)
    {
        if (fone.validate(fone.getNumber()))
            this->fones.push_back(fone);
    }

    void rmFone(int index)
    {
        if (fones.size() > index)
            this->fones.erase(fones.begin() + index);
    }

    std::vector<Fone> getFones()
    {
        return this->fones;
    }

    std::string getName()
    {
        return this->id;
    }

    void setName(std::string name)
    {
        this->id = name;
    }

    std::string toString()
    {
        std::string texto = "- " + this->id;
        for (int i{0}; i < (int) fones.size(); i++)
        {
            texto += " [" + std::to_string(i) + fones[i].toString() + "]";
        }
        return texto;
    }
};

class Agenda
{
    std::map<std::string, Contact> contatos;

    std::vector<Fone> removerAux(Contact &contato)
    {
        std::vector<Fone> fone = contato.getFones();
        for (int i{0}; i < (int)fone.size(); i++)
        {
            if (!(fone[i].validate(fone[i].getNumber())))
                fone.erase(fone.begin() + i);
        }
        return fone;
    }

        std::vector<Contact> search(std::string pattern)
    {
        std::vector<Contact> resultado;
        for (auto& pair: contatos) {
            auto text = pair.second.toString();
            if (text.find(pattern) != std::string::npos)
                resultado.push_back(pair.second);
        }
        return resultado;
    }

public:
    Fone quebrar(std::string str)
    {
        std::string id{""};
        std::string num{""};
        for (int i{0}; i < (int)str.length(); i++)
        {
            if (str[i] == ':')
            {
                id = num;
                num = "";
            }
            else
                num += str[i];
        }
        Fone *fone = new Fone(id, num);
        return *fone;
    }

    void addContato(Contact contato)
    {
        auto it = this->contatos.find(contato.getName());
        if (it != contatos.end()) {
            auto cont = contato.getFones();
            for (Fone fone : cont)
                it->second.addFone(fone);
        }
        else {
            contatos[contato.getName()] =  contato;
        }

    }

    Contact *getContact(std::string name)
    {
        auto it = contatos.find(name);
        if (it != contatos.end())
            return &(it->second);

        return nullptr;
    }

    void rmContact(std::string name)
    {
        auto it = contatos.find(name);
        if (it == contatos.end())
            std::cout << "fail: contato nao encontrado\n";
        else
            this->contatos.erase(it);
    }

    void remove(int index, std::string nome)
    {
        auto it = getContact(nome);
        auto contCopy = it->getFones();
        if (contCopy.size() > index)
            it->rmFone(index);
        else
            std::cout << "fail: impossivel remover\n";
    }

    std::string toString()
    {
        std::string texto;
        for (auto& pair : contatos)
        {
            texto += pair.second.toString() + '\n';
        }
        return texto;
    }

    void impress (std::string pattern) {
        std::vector<Contact> contatos = search(pattern);
        for (auto& contato : contatos) {
            std::cout << contato.toString() << '\n';
        }
    }
};

int main()
{
    Agenda *agenda = new Agenda();

    while (true)
    {
        std::string cmd;
        std::cin >> cmd;

        std::string linha;
        getline(std::cin, linha);

        std::stringstream ss(linha);

        if (cmd == "show")
        {
            std::cout << agenda->toString();
        }
        else if (cmd == "end")
        {
            break;
        }
        else if (cmd == "rm")
        {
            std::string nome;
            ss >> nome;
            agenda->rmContact(nome);
        }
        else if (cmd == "rmFone")
        {
            std::string nome;
            int index;
            ss >> nome >> index;
            agenda->remove(index, nome);
        }
        else if (cmd == "add")
        {
            std::string nome;
            std::string foneStr;

            ss >> nome;

            std::vector<Fone> fones;

            while (ss >> foneStr)
            {
                fones.push_back(agenda->quebrar(foneStr));
            }
            Contact *contato = new Contact(fones, nome);

            agenda->addContato(*contato);

            delete contato;
        }
        else if (cmd == "search")
        {
            std::string termo;
            ss >> termo;
            agenda->impress(termo);
        }
        else
        {
            std::cout << "fail: comando invalido\n";
        }
    }

    delete std::exchange(agenda, nullptr);
    return 0;
}