#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Personagens {
    int x {0}; //atributos
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Personagens(int x, int y, int step, sf::Texture& texture):
        x {x}, y {y}, step {step}, sprite(texture) {
    }

    void draw(sf::RenderWindow& window) { //métodos
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }
};

struct Fundo {
    int nc {0};
    int nl {0};
    int step {0};//atributos
    sf::Sprite sprite;
    sf::RectangleShape rect;
    //parametros
    Fundo(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }
};

void moverPersonagens(sf::Keyboard::Key key, Personagens& entity, std::vector<sf::Keyboard::Key> move_keys) {
    if (key == move_keys[0])
        entity.x--;
    else if (key == move_keys[1])
        entity.y--;
    else if (key == move_keys[2])
        entity.x++;
    else if (key == move_keys[3])
        entity.y++;
}

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
}

int main() {

    sf::Texture minotauroTex { loadTexture("mino.jpg") };
    sf::Texture teseuTex { loadTexture("teseu.jpg") };
    sf::Texture fundoTex { loadTexture("fundo.jpg") };

    const int STEP {50};


    Personagens mino(1, 1, STEP, minotauroTex);
    Personagens teseu(3, 3, STEP, teseuTex);
    Fundo fundo(7, 5, STEP, fundoTex);

    sf::RenderWindow window(sf::VideoMode(fundo.nc * STEP, fundo.nl * STEP), "Minotauro vs Teseu");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                moverPersonagens(event.key.code, mino, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
                moverPersonagens(event.key.code, teseu, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
            }
        }


    
        window.clear();
        fundo.draw(window);
        mino.draw(window);
        teseu.draw(window);

        if (teseu.x == mino.x && teseu.y == mino.y) {
            window.clear();
            exit(1);
    }
        window.display();
    }

    return 0;
}