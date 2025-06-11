#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>


// 업데이트, 드로우 계속 반복



int main()
{

	


	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	//데이터형                        //리소스 경로 

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");


	sf::Texture texturebee;
	texturebee.loadFromFile("graphics/bee.png");

	sf::Texture texturecloud;
	texturecloud.loadFromFile("graphics/cloud.png");






	sf::Sprite spriteBackground; //sf::Sprite는 SFML에서 이미지를 화면에 표시할 수 있게 해주는 객체
	spriteBackground.setTexture(textureBackground);


	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition((1920 / 2) - (textureTree.getSize().x / 2), 0); // 스프라이트(Sprite)의 화면 내 위치를 지정하는 함수



	sf::Sprite spritebee;
	spritebee.setTexture(texturebee);
	spritebee.setPosition(0, 900);  
	spritebee.setScale(-1.0f, 1.0f);


	sf::Sprite spritecloud;
	spritecloud.setTexture(texturecloud);
	spritecloud.setPosition(0, 0);
	spritecloud.setScale(-1.0f, 1.0f);

	sf::Sprite spritecloud1;
	spritecloud1.setTexture(texturecloud);
	spritecloud1.setPosition(0, 200);
	spritecloud1.setScale(-1.0f, 1.0f);

	sf::Sprite spritecloud2;
	spritecloud2.setTexture(texturecloud);
	spritecloud2.setPosition(0, 400);
	spritecloud2.setScale(-1.0f, 1.0f);




	sf::Vector2f beedirection = { 1.f,0.f };
	sf::Vector2f clouddirection = { 1.f,0.f };
	sf::Vector2f cloud1direction = { 1.f,0.f };
	sf::Vector2f cloud2direction = { 1.f,0.f };



	float beespeed = rand() % 200 + 100;
	float cloudspeed = rand() % 200 + 100;;
	float cloud1speed = rand() % 200 + 100;
	float cloud2speed = rand() % 200 + 100;
	// Velocity == direction * speed;

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

	srand((int)time(0));
	//현재시간 리턴 

	const int NUM_CLOUDS = 3;

	sf::Sprite clouds[NUM_CLOUDS];
	sf::Vector2f cloudDirections[NUM_CLOUDS];

	float cloudSpeeds[NUM_CLOUDS];
	int cloudHeights[NUM_CLOUDS] = { 0, 200, 400 };
	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		clouds[i].setTexture(texturecloud);
		clouds[i].setPosition(0, cloudHeights[i]);
		clouds[i].setScale(-1.f, 1.f); // 처음엔 왼쪽 → 오른쪽 이동
		cloudDirections[i] = { 1.f, 0.f };
		cloudSpeeds[i] = rand() % 200 + 100;
	}



	while (window.isOpen()) 
	{

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
		pos += beedirection * beespeed * deltaTime;
		spritebee.setPosition(pos);

		if (pos.x < -200 || pos.x > 1920 + 200)
		{
			float random = static_cast<float>(rand()) / RAND_MAX;
			if (random < 0.5f)
			{
				beedirection.x = 1.f;
				spritebee.setScale(-1.f, 1.f);
				spritebee.setPosition(-150, 800);
			}
			else
			{
				beedirection.x = -1.f;
				spritebee.setScale(1.f, 1.f);
				spritebee.setPosition(1920 + 150, 800);
			}
			beespeed = rand() % 200 + 100;
		}


		// cloud 배열 


		for (int i = 0; i < NUM_CLOUDS; ++i)
		{
			// 1. 구름 이동
			sf::Vector2f pos = clouds[i].getPosition();
			pos += cloudDirections[i] * cloudSpeeds[i] * deltaTime;
			clouds[i].setPosition(pos);

			// 2. 화면 밖이면 방향, 속도, 위치 재설정
			if (pos.x < -300 || pos.x > 1920 + 300)
			{
				float random = static_cast<float>(rand()) / RAND_MAX;
				if (random > 0.5f)
				{
					cloudDirections[i].x = 1.f;
					clouds[i].setScale(-1.f, 1.f);
					clouds[i].setPosition(-250, cloudHeights[i]);
				}
				else
				{
					cloudDirections[i].x = -1.f;
					clouds[i].setScale(1.f, 1.f);
					clouds[i].setPosition(1920 + 250, cloudHeights[i]);
				}

				cloudSpeeds[i] = rand() % 200 + 100;
			}
		}

		// 그리기
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteTree);
		for (int i = 0; i < NUM_CLOUDS; i++)
		{
			window.draw(clouds[i]);
		}
		window.draw(spritebee);
		window.display();
	}

	return 0;
}

// 난수  
// 실시간프로그래밍 개념 
// 델타타임 : 프레임 간의 시간 차이 (현재시간 - 반복할때 돌아온 시간) 