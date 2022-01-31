#include <iostream>

class Animal {
    protected:
    bool alive{true};
    public:
    Animal() = default;
    void eat () {
        std::cout << "Animal eating\n";
    }
    void die() {
        std::cout << "animal died\n";
        this->alive = false;
    }
    friend std::ostream& operator<<(std::ostream& os, const Animal& animal) {
        os << "Animal is alive " << animal.alive << '\n';
        return os;
    }
};

//Recebe tudo que animal tem, sujeito a alterações
//classe filho - class pai
class Pet : public Animal {
    protected:
    std::string name;
    public:
    Pet(std::string name = "") : name{name} {
        std::cout << this->name << " nascendo\n";
    }

    void eat( ) {
        std::cout << this->name << " is eating\n";
    }
};

//terceira camada das classes
class Cat : public Pet {
    int lives;
public:
    Cat(std::string name, int lives) :
    Pet{name}, lives{lives} {
        std::cout << name << " esta nascendo\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Cat& animal) {
        os << animal.name <<" is alive " << animal.alive << '\n';
        return os;
    }
};

int main () {
    Cat pet("Natasha", 8);
    Animal& pet2 = pet;
    pet2.die();
    std::cout << pet;
    std::cout << pet2;
    
    return 0;
}