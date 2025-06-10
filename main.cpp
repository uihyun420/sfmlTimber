#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    //데이터형                        //리소스 경로를 받음

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    
     

    while (window.isOpen()) // bool형 반환하므로 조건식
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();   


        window.draw(spriteBackground);


        window.display();
    }

    return 0;
}


//class 사용 
