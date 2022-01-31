#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <iomanip>

class Account {
    protected:
    float balance{0.00};
    std::string clientId;
    int id;
    std::string type{""};
    public:
    Account (int id = 0, std::string clientId = ""): id {id}, clientId{clientId} {}

    //gets
    float getBalance() const {
        return balance;
    }

    std::string getClient() const {
        return clientId;
    }

    int getId() {
        return id;
    }

    std::string getType() const {
        return type;
    }

    //métodos
    virtual void deposit(float value) {
        balance += value;
    }

    virtual void monthlyUpdate() {}

    virtual void transfer(Account& other, float value) {
        if (this->balance >= value) {
            this->balance -= value;
            other.balance += value;
        } else
            throw std::runtime_error("saldo insuficiente");

    }

    virtual void withdraw (float value) {
        if (balance >= value)
            balance -= value;
        else 
            throw std::runtime_error("saldo insuficiente");
    }

    friend std::ostream& operator<<(std::ostream& os, Account* account) {
        os << account->getId() << ':' << account->getClient() << ':';
        os << std::fixed << std::setprecision(2) << account->getBalance() ;
        os << ':' << account->getType() << '\n';
        return os;
    }
};

class SavingsAccount : public Account {
    public:
    SavingsAccount(int id = 0, std::string clientId = ""): Account(id, clientId) {
        type = "CP";
    }

    virtual void monthlyUpdate() {
        balance += balance/100;
    }
};

class CheckingAccount : public Account {
    public:
    CheckingAccount(int id = 0, std::string clientId = ""): Account(id, clientId) {
        type = "CC";
    }

    virtual void monthlyUpdate() {
        balance -= 20;
    }
};

class Client {
    std::vector<std::shared_ptr<Account>> accounts;
    std::string clientId;
    public:
    Client (std::string clientId = "", int id = 0): clientId{clientId} {

        this->addAccount( std::make_shared<CheckingAccount>( id, clientId ));
        this->addAccount( std::make_shared<SavingsAccount>( (id+1), clientId ));
    }

    //métodos
    void addAccount (std::shared_ptr<Account> account) {
        accounts.push_back(account);
    }

    friend std::ostream& operator<<(std::ostream& os, Client* client) {
        auto contas = client->getAccounts();
        os << client->clientId << " [" ;
        for (int i {0}; i < (int) contas.size(); i++) {
            if (i != (int) (contas.size() - 1))
                os << contas[i]->getId() << ", ";
            else 
                os << contas[i]->getId() << "]\n";
        }
        return os;
    }

    //gets e sets
    std::vector<std::shared_ptr<Account>> getAccounts () const {
        return accounts;
    }

    std::string getClient() const {
        return clientId;
    }

    void setAccount(std::vector<std::shared_ptr<Account>> accounts) {
        this->accounts = accounts;
    }

    void setClientId (std::string clientId) {
        this->clientId = clientId;
    }
};

class BankAgency {
    std::map<int, std::shared_ptr<Account>> accounts;
    std::map<std::string, std::shared_ptr<Client>> clients;
    

    Account* getAccount(int id) {
        return this->accounts[id].get();
    }

    void existe (int conta) {
        if ((int) this->accounts.size() <= conta )
            throw std::runtime_error("conta nao encontrada");
    }

    public:
    BankAgency() {}

    //métodos
    void addClient (std::string clientId) {
        for (auto conta : clients) {
            if (conta.first == clientId)
                throw std::runtime_error("ja existe conta");
        }

        int size { (int) accounts.size()};

        auto client {std::make_shared<Client>(clientId, size)};
        clients.insert({clientId, client});
        
        auto contas = client->getAccounts();
        for (int i{0}; i < (int) contas.size(); i++) {
            accounts.insert({size, contas[i]});
            size++;
        }
        
    }

    void deposit (int idConta, float value) {
        auto conta = getAccount(idConta);
        if ((int) this->accounts.size() <= idConta)
            throw std::runtime_error("conta nao encontrada");
        else
            conta->deposit(value);
    }

    void monthlyUpdate() {
        for (auto conta : accounts) {
            conta.second->monthlyUpdate();
        }
    }

    void transfer (int contaDe, int contaPara, float value) {
        existe(contaDe);
        existe(contaPara);
        auto conta = getAccount(contaDe);
        
        conta->transfer( *(this->accounts[contaPara]), value );
    }

    void withdraw(int idConta, float value) {
        existe(idConta);
        auto conta = getAccount(idConta);

        conta->withdraw(value);
    }

    friend std::ostream& operator<<(std::ostream& os, BankAgency* bank) {
        os << "Clients:\n";
        
        for (auto client : bank->clients) {
            os << "- " << (client.second) << '\n';
        }
        os << "Accounts:\n";
        for (auto conta : bank->accounts) {
            int i{0};
            os << (conta.second) << '\n';
            i++;
        }
        return os;
    }

};

int main () {
    BankAgency* banco = new BankAgency();
    while (true){
        std::string line, cmd;
        std::cin >> cmd;
        getline(std::cin, line);
        std::stringstream ss(line);

        try{
            if (cmd == "end")
                break;
            else if (cmd == "show")
                std::cout << banco;
            else if (cmd == "update")
                banco->monthlyUpdate();
            else if (cmd == "addCli") {
                std::string nome;
                ss >> nome;
                banco->addClient(nome);
            }
            else if (cmd == "saque") {
                int conta;
                float value;
                ss >> conta >> value;
                banco->withdraw(conta, value);
            }
            else if (cmd == "deposito") {
                int conta;
                float valor;
                ss >> conta >> valor;
                banco->deposit(conta, valor);
            }
            else if (cmd == "transf") {
                int envio, remetente;
                float value;
                ss >> envio >> remetente >> value;
                banco->transfer(envio, remetente, value);
            }
            else
                std::cout << "fail: comando invalido\n";
        } catch (std::runtime_error e) {
            std::cout << "fail: " << e.what() << '\n';
        } catch (std::exception e) {
            std::cout << e.what();
        }
    }
    
    delete banco;
    
    return 0;
}