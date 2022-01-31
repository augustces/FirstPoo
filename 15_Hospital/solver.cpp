#include "hospital.hpp"

int main() {
    Hospital* hospital = new Hospital ();
    while(true) {
        std::string cmd;
        std::cin >> cmd;

        std::string linha;
        getline(std::cin, linha);
        std::stringstream ss(linha);
        auto quebrar = [](std::string str) {
            std::string nome, diag;
            for (int i {0}; i < (int) str.length(); i++) {
                if (str[i] == '-') {
                    nome = diag;
                    diag = "";
                    continue;
                }
                diag += str[i];
            }
            return std::make_pair(nome, diag);
        };
        try {
            if (cmd == "show") {
                std::cout << hospital;
            }
            else if (cmd == "tie") {
                std::string med, pac;
                ss >> med;
                while (ss >> pac) {
                    hospital->vincular(med, pac);
                }
            }
            else if (cmd == "end")
                break;
            else if (cmd == "addPacs") {
                std::string str, nome, diag;
                while (ss >> str) {
                    auto aux = quebrar(str);
                    nome = aux.first;
                    diag = aux.second;
                    hospital->addPaciente(std::make_shared<Paciente>(nome, diag));
                }
            }
            else if (cmd == "addMeds") {
                std::string str, nome, esp;
                while (ss >> str) {
                    auto aux = quebrar(str);
                    nome = aux.first;
                    esp = aux.second;
                    hospital->addMedico(std::make_shared<Medico>(nome, esp));
                }
            }
            else
                std::cout << "fail: comando invalido\n";
        }
        catch (std::runtime_error e) {
            std::cout << e.what() << '\n';
        }
    }
    delete hospital;
    return 0;
}