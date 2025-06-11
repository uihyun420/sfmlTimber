#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>




int main()
{

    srand((int)time(0));
    //����ð� ���� 

    // printf("%d\n\n", RAND_MAX); ������ �ѹ��� n�� �̰ڴ�

    //�����ð� �̾ƺ���
    //for (int i = 0; i < 10; ++i)
    //{
     //   printf("%d\n", rand()) ;
    //}
  
    


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    //��������                        //���ҽ� ��θ� 

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");


    sf::Texture texturebee;
    texturebee.loadFromFile("graphics/bee.png");


    sf::Texture texturecloud;
    texturecloud.loadFromFile("graphics/cloud.png");










    sf::Sprite spriteBackground; 
    spriteBackground.setTexture(textureBackground);
    
   

    
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition((1920 / 2) -(textureTree.getSize().x / 2), 0);
                             //      x��ġ                           y��ġ
    //spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
    //spriteTree.setPosition(1920 * 0.5f, 0.f); ��ġ �����ϴ� �ٸ����


    sf::Sprite spritebee;
    spritebee.setTexture(texturebee);
    spritebee.setPosition(0, 900);



    // ���� �迭

    /*int cloud[10];
    int size = sizeof(cloud) / sizeof(cloud[0]);
    {
        for(int i =0; i<size;i++)
    }
    */


    sf::Sprite spritecloud;
    spritecloud.setTexture(texturecloud);
    spritecloud.setPosition(0, 0);
   
    sf::Sprite spritecloud1;
    spritecloud1.setTexture(texturecloud);
    spritecloud1.setPosition(0, 200);

    sf::Sprite spritecloud2;
    spritecloud2.setTexture(texturecloud);
    spritecloud2.setPosition(0, 400);





    sf::Clock clock; 
    //sf::Vector2f v = { 200.f,0.f };
    
    
    // ���� �ʱ�ȭ
    srand(static_cast<unsigned int>(time(0)));  // �ӵ� ���� ���� (X�� �ӵ���, �� : 50 ~ 250�ȼ�/��)

    //�ӵ� ���� ����
    float minspeed = 50.f;
    float maxspeed = 250.f;
     
    // �� ������Ʈ�� ���� �ӵ� ���� ����
    sf::Vector2f beeVelocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloudVelocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloud1Velocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloud2Velocity(static_cast<float>(rand() % 200 + 50), 0.f);

    while (window.isOpen()) // bool�� ��ȯ�ϹǷ� ���ǽ�
    {

        // clock.restart();
        sf::Time time = clock.restart();  // �ٽ� �ð��� ��
        float deltaTime = time.asSeconds(); // �ʸ� �Ǽ��� ��ȯ���ִ� �Լ�

        printf("%f\n", deltaTime);




        // �̺�Ʈ ����
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //������Ʈ
    

        sf::Vector2f pos = spritebee.getPosition();

        pos += beeVelocity * deltaTime;
        spritebee.setPosition(pos); // ���� �����̴� �ڵ�

        
        sf::Vector2f pos1 = spritecloud.getPosition();

        pos1 += cloudVelocity * deltaTime;
        spritecloud.setPosition(pos1);


        sf::Vector2f pos2 = spritecloud1.getPosition();

        pos2 += cloud1Velocity * deltaTime;
        spritecloud1.setPosition(pos2);


        sf::Vector2f pos3 = spritecloud2.getPosition();

        pos3 += cloud2Velocity * deltaTime;
        spritecloud2.setPosition(pos3);





        // �׸���
        window.clear();   
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spritecloud);
        window.draw(spritecloud1);
        window.draw(spritecloud2);
        window.draw(spritebee);
        window.display();
    }

    return 0;
}


//class ��� 

// ����  
// �ǽð����α׷��� ���� 
// ��ŸŸ�� : ������ ���� �ð� ���� (����ð� - �ݺ��Ҷ� ���ƿ� �ð�) 