#include "twitter.hpp"

int main() {
    Controller* cont = new Controller();
    auto quebrar = [](std::string linha, std::string remover) {
        std::string res{""};
        for (int i{(int) remover.length()}; i < (int) linha.length(); i++)
            res += linha[i];
        return res;
    };
    while(true) {
        std::string line, cmd;
        std::cin >> cmd;
        getline(std::cin, line);
        std::stringstream ss(line);
        try {
            if (cmd == "show")
                std::cout << cont;
            else if (cmd == "end")
                break;
            else if (cmd == "timeline") {
                std::string user;
                ss >> user;
                auto it = cont->getUser(user);
                std::cout << it->getInbox();
            }
            else if (cmd == "follow") {
                std::string us1, us2;
                ss >> us1 >> us2;
                auto it = cont->getUser(us1);
                auto other = cont->getUser(us2);
                it->follow(other);
            }
            else if (cmd == "twittar") {
                std::string user, msg;
                ss >> user;
                msg = quebrar(ss.str(), user + " ");
                cont->sendTweet(user, msg);
            }
            else if (cmd == "unfollow") {
                std::string us1, us2;
                ss >> us1 >> us2;
                auto it = cont->getUser(us1);
                it->unfollow(us2);
            }
            else if (cmd == "like") {
                std::string us1;
                int id;
                ss >> us1 >> id;
                auto it = cont->getUser(us1);
                
                it->like(id);
            }
            else if (cmd == "add") {
                std::string user;
                ss >> user;
                cont->addUser(user);
            }
            else if (cmd == "rm") {
                std::string user;
                ss >> user;
                cont->rmUser(user);
            }
            else if (cmd == "rt") {
                std::string user, msg;
                int id;
                ss >> user >> id;
                msg = quebrar(ss.str(), user + " " + std::to_string(id) + " ");
                cont->sendRt(user, id, msg);
            }
            else   
                throw std::runtime_error("fail: comando invalido");
        } 
        catch (std::runtime_error e) {
            std::cout << e.what() << '\n';
        }
    }
    delete cont;
    return 0;
}