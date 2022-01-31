#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>

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
    std::vector<Fone> fones;
    std::string name;

public:
    Contact(std::vector<Fone> fones, std::string name = "")
    {
        this->name = name;
        for (int i{0}; i < (int)fones.size(); i++)
        {
            this->fones.push_back(fones[i]);
        }
    }

    Contact(std::string name = "")
    {
        this->name = name;
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
        return this->name;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    std::string toString()
    {
        std::string texto = "- " + this->name;
        for (int i = 0; i < (int)this->fones.size(); i++)
        {
            texto += " [" + std::to_string(i) + this->fones[i].toString() + "]";
        }
        return texto;
    }
};

class Agenda
{
    std::vector<Contact> contatos;

    bool condicao(std::string nome1, std::string nome2)
    {
        int cont{0};
        while (cont < nome1.length() && cont < nome2.length())
        {
            if (nome1[cont] > nome2[cont])
                return true;
            else if (nome1[cont] == nome2[cont]){
            cont++;
            continue;
            }
            else
                return false;
        }
        if (nome1.length() > nome2.length())
            return true;
        return false;
    }

    int ordenar(Contact contato)
    {
        if (this->contatos.size() == 0)
            return 0;
        for (int i{0}; i < (int)this->contatos.size(); i++)
        {
            if (condicao(this->contatos[i].getName(), contato.getName())) {
                return i;
            }
        }
        return -1;
    }

    int findPos(std::string name)
    {
        for (int i{0}; i < (int)this->contatos.size(); i++)
        {
            if (this->contatos[i].getName() == name)
            {
                return i;
            }
        }
        return -1;
    }

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
        std::vector<Fone> aux = removerAux(contato);
        Contact *cont = new Contact(aux, contato.getName());
        auto auxiliar = this->getContact(contato.getName());
        if (auxiliar == nullptr) {
            int x = ordenar(*cont);
            
            if (x != -1)
                this->contatos.insert(this->contatos.begin() + x, *cont);
            else 
                this->contatos.push_back(*cont);
        }
        else
            for (int i{0}; i < (int)(aux.size()); i++)
                auxiliar->addFone(aux[i]);
        delete cont;
    }

    Contact *getContact(std::string name)
    {
        int index = findPos(name);
        if (index != -1)
            return &(this->contatos[index]);

        return nullptr;
    }

    void rmContact(std::string name)
    {
        int aux = findPos(name);
        if (aux == -1)
            std::cout << "fail: contato nao encontrado\n";
        else
            this->contatos.erase(contatos.begin() + aux);
    }

    std::string search(std::string pattern)
    {
        std::string texto{""};
        for (int i{0}; i < (int)this->contatos.size(); i++)
        {
            std::string auxiliar{""};
            auxiliar = this->contatos[i].toString();
            size_t found = auxiliar.find(pattern);
            if (found != std::string::npos)
            {
                texto += auxiliar + '\n';
            }
        }
        return texto;
    }

    void remove(int index, std::string nome)
    {
        int x = findPos(nome);

        if (x != -1 && contatos.size() > x)
            this->contatos[x].rmFone(index);
        else
            std::cout << "fail: impossivel remover\n";
    }

    std::string toString()
    {
        std::string texto;
        for (int i{0}; i < (int)this->contatos.size(); i++)
        {
            texto += this->contatos[i].toString() + '\n';
        }
        return texto;
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
            std::cout << agenda->search(termo) << '\n';
        }
        else
        {
            std::cout << "fail: comando invalido\n";
        }
    }

    delete std::exchange(agenda, nullptr);
    return 0;
}