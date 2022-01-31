#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <ctime>
#include <vector>

struct Pincel {
    sf::Font fonte;
    sf::Text texto;
    sf::RenderWindow& window;

    Pincel (sf::RenderWindow& window):
    window(window) {
        if( !(fonte.loadFromFile("Oswald-Stencil.ttf")) )
            std::cout << "Erro no carregamento da fonte\n";
        texto.setFont(fonte);
    }

    void write (std::string str, int x, int y, int tamanho, sf::Color cor, bool gameover = false) {
        if ( gameover ) {
            sf::Vector2f vet = sf::Vector2f(texto.getLocalBounds().width, texto.getLocalBounds().height);
            texto.setOrigin(vet.x/2, vet.y/2);
        }
        
        texto.setString(str);
        texto.setCharacterSize(tamanho);
        texto.setPosition(x,y);
        texto.setFillColor(cor);
        window.draw(texto);
    }

};


struct Bolhas {
    int x;
    int y;
    char letra;
    int velocidade;

    bool viva {true};
    static const int raio{20};

    Bolhas (int x, int y, char letra, int velocidade) {
        this->x = x;
        this->y = y;
        this->velocidade = velocidade;
        this->letra = letra;
    }

    void atualizar() {
        this->y += this->velocidade;
    }

    void desenhar (sf::RenderWindow& window) {
        static Pincel pincel (window);
        sf::CircleShape bolhinha (Bolhas::raio);
        bolhinha.setPosition(x, y);
        bolhinha.setFillColor(sf::Color::White);
        window.draw(bolhinha);
        pincel.write(std::string(1, letra), x + 0.5 * Bolhas::raio, y + 0.3 * Bolhas::raio, Bolhas::raio, sf::Color::Blue);
        
    }
};

struct Fundo {
    sf::Texture fundoTex;
    sf::RenderWindow& window;

    Fundo (sf::RenderWindow& window) : window{ window } {
    }

    void draw () {
        if ( !(fundoTex.loadFromFile("fundo.png")) ) {
            std::cout << "Erro ao carregar a textura \n";
            exit(1);
        }
        static sf::Sprite fundo (fundoTex);
        fundo.setPosition(0, 0);
        sf::FloatRect rect = fundo.getLocalBounds();
        fundo.setScale((float) window.getSize().x / rect.width, (float) window.getSize().y / rect.height);
        this->window.draw(fundo);
    }
};

struct Quadro {
    sf::RenderWindow& window;
    std::vector<Bolhas> bolhas;
    
    Pincel pincel;
    int acertos{0};
    int erros{0};
    
    Quadro (sf::RenderWindow& window) :
    window{ window }, pincel { window } {        
    }

    bool checarNovaBolha () {
        static const int novaBolhaFim {20};
        static int novaBolhaTimer{0};
        novaBolhaTimer--;

        if (novaBolhaTimer <= 0) {
            novaBolhaTimer = novaBolhaFim;
            return true;
        }
        return false;
    }

    void addNovaBolha () {
        int x = rand() % ((int) this->window.getSize().x - 2 * Bolhas::raio);
        int y = (-2) * Bolhas::raio;
        int velocidade = rand() % 6 + 2;
        char letra = rand() % 26 + 'A';
        Bolhas bubble ( x, y, letra, velocidade );
        bolhas.push_back( bubble );
    }

    void atualizarQuadro () {
        if (this->checarNovaBolha()) 
            this->addNovaBolha();
        
        for (Bolhas& bolha : bolhas) {
            bolha.atualizar();
        }
        
        this->bolhasFugitivas();
        this->removerBolhas();
    }

    void bolhasFugitivas () {
        for (Bolhas& bolha : bolhas) {
            if (bolha.y + 2 * Bolhas::raio > (int) this->window.getSize().y) {
                if (bolha.viva) {
                    bolha.viva = false;
                    this->erros++;
                }
            }
        }
    }

    void removerBolhas ( ) {

        std::vector<Bolhas> vivas;

        for (Bolhas& bolha : bolhas) {
            if (bolha.viva) 
                vivas.push_back(bolha);
        }
        this->bolhas = vivas;
    }

    void acertosBolhas (char letra) {
        for (Bolhas& bolha : bolhas) {
            if (bolha.letra == letra) {
                bolha.viva = false;
                this->acertos++;
                break;
            }
        }
    }

    void desenhar () {
        static Fundo fundo(this->window);
        fundo.draw();
        pincel.write("ACERTOS: " + std::to_string(this->acertos), 10, 10, 20, sf::Color::White);
        pincel.write("Vidas: " + std::to_string(10 - this->erros), 10, 30, 20, sf::Color::White);
        pincel.write("Bolhas Vivas: " + std::to_string(this->bolhas.size()), 10, 50, 20, sf::Color::White);
        
        for (Bolhas& bolha : bolhas) {
            bolha.desenhar(window);
        }

        this->atualizarQuadro();
    }

};

struct Game {
    Quadro quadro;
    sf::RenderWindow window;
    std::function<void()> atualizacoes;

    Game () :
    window ( sf:: VideoMode (800, 600), "Bubble Sort"), quadro {window} {
        this->atualizacoes = [&] () {
            this->jogo();
        };
        window.setFramerateLimit(20);
    }
 
    void processoDeEventos (sf::RenderWindow& window) {
        sf::Event evento;
        while(window.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                window.close();
            } else if (evento.type == sf::Event::TextEntered) {
                char cod = static_cast<char> (evento.text.unicode);
                cod = toupper(cod);
                quadro.acertosBolhas(cod);
            }
        }
}

    void desenhar () {
        
        window.clear();
        
        
        static Pincel pincel (window);
      
        window.display();
    }

    void loop () {
        while (window.isOpen()) {
            processoDeEventos(window);
            atualizacoes();
        }
    }

    void jogo() {
        window.clear();
        
        this->quadro.desenhar();
        window.display();
        if ( this->quadro.erros > 9 ) {
            this->atualizacoes = [&] () {
                this->fim();
            };
        }
    }

    void fim() {
        static Pincel pincel (window);
        
        window.clear();
        static Fundo fundo(this->window);
        fundo.draw();
        pincel.write("GAME OVER", (window.getSize().x)/2, (window.getSize().y)/2, 100, sf::Color::White, true);
        
        window.display();
    }

};

int main() {
    Game game;

    game.loop();

    return 0;
}