#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>




int main()
{

    srand((int)time(0));
    //현재시간 리턴 

    // printf("%d\n\n", RAND_MAX); 랜덤한 넘버를 n개 뽑겠다

    //랜덤시간 뽑아보기
    //for (int i = 0; i < 10; ++i)
    //{
     //   printf("%d\n", rand()) ;
    //}
  
    


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    //데이터형                        //리소스 경로를 

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
                             //      x위치                           y위치
    //spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
    //spriteTree.setPosition(1920 * 0.5f, 0.f); 위치 지정하는 다른방법


    sf::Sprite spritebee;
    spritebee.setTexture(texturebee);
    spritebee.setPosition(0, 900);



    // 구름 배열

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
    
    
    // 난수 초기화
    srand(static_cast<unsigned int>(time(0)));  // 속도 범위 설정 (X축 속도만, 예 : 50 ~ 250픽셀/초)

    //속도 범위 설정
    float minspeed = 50.f;
    float maxspeed = 250.f;
     
    // 각 오브젝트의 랜덤 속도 벡터 생성
    sf::Vector2f beeVelocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloudVelocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloud1Velocity(static_cast<float>(rand() % 200 + 50), 0.f);
    sf::Vector2f cloud2Velocity(static_cast<float>(rand() % 200 + 50), 0.f);

    while (window.isOpen()) // bool형 반환하므로 조건식
    {

        // clock.restart();
        sf::Time time = clock.restart();  // 다시 시간을 잼
        float deltaTime = time.asSeconds(); // 초를 실수로 반환해주는 함수

        printf("%f\n", deltaTime);




        // 이벤트 루프
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //업데이트
    

        sf::Vector2f pos = spritebee.getPosition();

        pos += beeVelocity * deltaTime;
        spritebee.setPosition(pos); // 벌이 움직이는 코드

        
        sf::Vector2f pos1 = spritecloud.getPosition();

        pos1 += cloudVelocity * deltaTime;
        spritecloud.setPosition(pos1);


        sf::Vector2f pos2 = spritecloud1.getPosition();

        pos2 += cloud1Velocity * deltaTime;
        spritecloud1.setPosition(pos2);


        sf::Vector2f pos3 = spritecloud2.getPosition();

        pos3 += cloud2Velocity * deltaTime;
        spritecloud2.setPosition(pos3);





        // 그리기
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


//class 사용 

// 난수  
// 실시간프로그래밍 개념 
// 델타타임 : 프레임 간의 시간 차이 (현재시간 - 반복할때 돌아온 시간) 