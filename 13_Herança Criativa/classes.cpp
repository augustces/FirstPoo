#include <iostream>

class SerVivo {
    protected:
    std::string marca{"Ser Vivo"};
    bool alive {true};
    int age{0};
    public:
    SerVivo(int age) {
        this->age = age;
        std::cout << marca << " esta nascendo\n";
    }
    virtual void respirar() const {
        if (alive)
            std::cout << marca << " esta respirando\n";
    }

    virtual void estaVivo() const {
        if (alive)
            std::cout << marca << " esta vivo(a)\n";
        else 
            std::cout << marca << " esta morto(a)\n";
    }

    virtual void morrer(){
        if (alive)
            std::cout << marca << " morreu\n";
        alive = false;
    }

        friend std::ostream& operator<<(std::ostream& os, SerVivo& viv){
        os << viv.marca << " tem " << viv.age << " anos e ";
        viv.estaVivo();
        return os;
    }

};

class Planta : public SerVivo {
    protected:
    int brotos{0};
    public:
    Planta(int brotos, int age): brotos{brotos}, SerVivo{age} {
        marca = "Planta";
        std::cout << marca << " esta brotando\n";
    }
    virtual void fotossintese() const{
        std::cout << marca << " esta fazendo fotossintese\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Planta& planta){
        os << planta.marca << " tem " << planta.brotos << " brotos\n";
        return os;
    }
};

class Angiosperma : public Planta {
    int flores{0};
    int frutos{0};
    public:
    Angiosperma(int brotos, int flores, int frutos, int age):
    Planta{brotos, age}, flores{flores}, frutos{frutos} {
        marca = "Angiosperma";
        std::cout << marca << " esta brotando\n";
    }

    virtual void florecer() {
        std::cout << marca << " esta florecendo\n";
        flores += 2;
    }

    virtual void frutar() {
        std::cout << marca << " esta produzindo frutos\n";
        frutos += 2;
    }

    friend std::ostream& operator<<(std::ostream& os, const Angiosperma& ang){
        os << ang.marca << " tem " << ang.flores << " flores e " << ang.frutos << " frutos\n";
        return os;
    }

};

int main () {
    Angiosperma angi (3, 0, 7, 10);
    std::cout << angi;
    Planta& planta = angi;
    std::cout << planta;
    SerVivo& ser = angi;
    angi.frutar();
    angi.respirar();
    angi.florecer();
    planta.respirar();
    ser.estaVivo();
    ser.morrer();
    std::cout << angi;
    std::cout << planta;
    std::cout << ser;
    return 0;
}