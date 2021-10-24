#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.1415

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "asteroids");
  //sf::RectangleShape shape(sf::Vector2f(100, 100));
  sf::Texture triangle;
  triangle.loadFromFile("C:\\Users\\carlo\\Downloads\\sfml-vscode-boilerplate-master\\src\\triangulo.png");
  forma.setTexture(&triangle);

  sf::Sprite spr(triangle);
  //spr.setOrigin(sf::Vector2f(50,50));
  spr.setPosition(100,100);


  while (window.isOpen()) {
    sf::Event evnt;

    while (window.pollEvent(evnt)) {
      if (evnt.type == evnt.Closed) {
        window.close();
      }
    }
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::left)) {
      sf::Vector2f mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f playerPos = spr.getPosition();
      float sideX = mousePos.x - playerPos.x;
      float sideY = mousePos.y - playerPos.y;
      float hypt = sqrt(pow(sideX, 2)+pow(sideY, 2));
      float angle = (asin(sideX / hypt) * 180.0) / PI;
      float curRotation = spr.getRotation();
      if(curRotation != angle) {
        spr.rotate(angle - curRotation);
      }
      float pMax = (playerPos.x > playerPos.y)? playerPos.x : playerPos.y;
      sf::Vector2f newPos(playerPos.x / pMax, playerPos.y / pMax);
      spr.move(newPos);
      
    }
    
    window.clear();
    window.draw(spr);
    window.display();
    

  }

  return 0;
}

