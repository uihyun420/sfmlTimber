#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    //��������                        //���ҽ� ��θ� ����

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    
     

    while (window.isOpen()) // bool�� ��ȯ�ϹǷ� ���ǽ�
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


//class ��� 
