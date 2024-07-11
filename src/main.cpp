#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <random>
#include "TileMap.h"
#include "ParticleSystem.h"

bool randomBool() {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<> dist(0,1);
    return dist(e2);
}

void quickMathNewQuestion(int &first, int &second, int &result, int &fake, bool &left,
                          sf::Text &question, sf::Text &textFirst, sf::Text &textSecond, sf::Font &font) {
    first = (rand() % 10) + 1;
    second = (rand() % 10 + 1);
    result = first + second;
    int offset = (rand() % 10) + 1;
    bool add = randomBool();
    fake = result;
    if (add) {
        fake += offset;
    } else {
        fake -= offset;
    }
    if (fake < 1) {
        fake = 1;
    }

    left =  randomBool();

    question.setString("What is " + std::to_string(first) + " + " + std::to_string(second) + "?");
    question.setFont(font);
    question.setCharacterSize(48);
    question.setFillColor(sf::Color::Blue);
    question.setStyle(sf::Text::Bold | sf::Text::Underlined);
    question.setPosition(sf::Vector2f(300.f, 100.f));

    if (left) {
        textFirst.setString(std::to_string(result));
    } else {
        textFirst.setString(std::to_string(fake));
    }
    textFirst.setFont(font);
    textFirst.setCharacterSize(48);
    textFirst.setFillColor(sf::Color::Red);
    textFirst.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textFirst.setPosition(sf::Vector2f(400.f, 200.f));

    if (left) {
        textSecond.setString(std::to_string(fake));
    } else {
        textSecond.setString(std::to_string(result));
    }
    textSecond.setFont(font);
    textSecond.setCharacterSize(48);
    textSecond.setFillColor(sf::Color::Red);
    textSecond.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textSecond.setPosition(sf::Vector2f(500.f, 200.f));
}

int quickMath() {
    unsigned int width = 1280;
    unsigned int height = 720;

    auto window = sf::RenderWindow({width, height}, "Quick Math");
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile("Dinofans.ttf")) {
        std::cout << "didn't load font correctly" << std::endl;
        return -1;
    } else {
        std::cout << "loaded font correctly" << std::endl;
    }

    int first = 0;
    int second = 0;
    int result = 0;
    int fake = 0;
    bool left = false;

    sf::Text question;
    sf::Text textFirst;
    sf::Text textSecond;

    quickMathNewQuestion(first, second, result, fake, left, question, textFirst, textSecond, font);


    sf::Text inARowText;
    inARowText.setFont(font);
    inARowText.setCharacterSize(40);
    inARowText.setFillColor(sf::Color::Green);
    inARowText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    inARowText.setPosition(sf::Vector2f(365.f, 300.f));
    inARowText.setString("In A Row: 0");

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(width, height));

    bool clickLock = false;

    int inARow = 0;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        bool leftDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool leftDownFirst = false;
        if (leftDown) {
            if (!clickLock) {
                clickLock = true;
                leftDownFirst = true;
            } else {
                leftDownFirst = false;
            }
        } else {
            clickLock = false;
        }
        if (textFirst.getGlobalBounds().contains(mouse.x, mouse.y)) {
            if (leftDownFirst) {
                textFirst.setFillColor(sf::Color::Blue);
                if (left) {
                    inARow++;
                } else {
                    inARow = 0;
                }
                inARowText.setString("In A Row: " + std::to_string(inARow));
                quickMathNewQuestion(first, second, result, fake, left, question, textFirst, textSecond, font);
            } else {
                textFirst.setFillColor(sf::Color::Green);
            }
        } else {
            textFirst.setFillColor(sf::Color::Red);
        }

        if (textSecond.getGlobalBounds().contains(mouse.x, mouse.y)) {
            if (leftDownFirst) {
                textSecond.setFillColor(sf::Color::Blue);
                if (left) {
                    inARow = 0;
                } else {
                    inARow++;
                }
                inARowText.setString("In A Row: " + std::to_string(inARow));
                quickMathNewQuestion(first, second, result, fake, left, question, textFirst, textSecond, font);
            } else {
                textSecond.setFillColor(sf::Color::Green);
            }
        } else {
            textSecond.setFillColor(sf::Color::Red);
        }

        window.clear();

        window.draw(background);
        window.draw(question);
        window.draw(textFirst);
        window.draw(textSecond);
        window.draw(inARowText);
        window.display();
    }

    return 0;
}

int testing() {
    sf::Clock clock1, clock2; // starts the clock

    auto window = sf::RenderWindow{{1280, 720}, "Scooter"};
    window.setFramerateLimit(144);

    sf::Texture texture;
    if (!texture.loadFromFile("mario.png")) {
        std::cout << "didn't load correctly" << std::endl;
        return -1;
    } else {
        std::cout << "loaded file correctly" << std::endl;
    }
    //texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2(300.f, 120.f));
    sprite.setRotation(90.f);
    sprite.setScale(sf::Vector2(0.5f, 2.f));
    sprite.scale(sf::Vector2(1.5f, 3.f));
    sprite.setOrigin(sf::Vector2f(25.f, 25.f));


    sf::Font font;
    if (!font.loadFromFile("Dinofans.ttf")) {
        std::cout << "didn't load font correctly" << std::endl;
    } else {
        std::cout << "loadied font correctly" << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(L"CATCH A RIIIDE יטאח");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));
    shape.setPosition(sf::Vector2(450.f, 250.f));

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setSize(sf::Vector2f(100.f, 100.f));
    rectangle.setPosition(sf::Vector2f(0.f, 150.f));

    sf::CircleShape triangle1(80.f, 3);
    triangle1.setPosition(sf::Vector2(450.f, 0.f));

    sf::RectangleShape line(sf::Vector2f(150.f, 5.f));
    line.setPosition(sf::Vector2f(50.f, 250.f));

    sf::Vertex vertex;
    vertex.position = sf::Vector2f(10.f, 50.f);
    vertex.color = sf::Color::Red;
    vertex.texCoords = sf::Vector2f(100.f, 100.f);

    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(10.f, 510.f);
    triangle[1].position = sf::Vector2f(100.f, 510.f);
    triangle[2].position = sf::Vector2f(100.f, 600.f);
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    sf::Vertex vertices[2] = {
            sf::Vertex(sf::Vector2f(10.f, 50.f), sf::Color::Red, sf::Vector2f(100.f, 100.f)),
            sf::Vertex(sf::Vector2f(100.f, 150.f), sf::Color::Red, sf::Vector2f(100.f, 100.f))
    };

    const int level[] = {
            0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
            0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
            0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
            0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
            2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8, 700, 0)) {
        std::cout << "unable to create tilemap" << std::endl;
        return -1;
    } else {
        std::cout << "loaded tilemap" << std::endl;
    }

    ParticleSystem particles(1000);

    sf::Text hello;
    hello.setFont(font);
    hello.setString("Hello, world!");
    hello.setCharacterSize(64);
    hello.setFillColor(sf::Color::Green);
    hello.setStyle(sf::Text::Bold | sf::Text::Underlined);
    hello.setPosition(sf::Vector2f(200.f, 150.f));
    hello.setRotation(35.f);
    hello.rotate(10.f);
    hello.move(5.f, 5.f);
    hello.setScale(2.f, 2.f);
    hello.scale(0.75f, 0.75f);
    hello.setOrigin(10.f, 20.f);

    while (window.isOpen()) {
        sf::Time elapsed2 = clock2.restart();
        std::cout << elapsed2.asMicroseconds() << std::endl;

        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        sf::Time elapsed1 = clock1.restart();
        particles.update(elapsed1);

        window.clear();

        window.draw(sprite);
        window.draw(text);
        window.draw(shape);
        window.draw(triangle1);
        window.draw(line);
        window.draw(triangle);
        window.draw(map);
        window.draw(vertices, 2, sf::Lines);
        window.draw(particles);
        window.draw(hello);

        window.display();
    }

    return 0;
}



int main() {
    return quickMath();
}