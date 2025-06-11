#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>


// 업데이트, 드로우 계속 반복



int main()
{

	srand((int)time(0));
	//현재시간 리턴 



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
	spriteTree.setPosition((1920 / 2) - (textureTree.getSize().x / 2), 0);
	//                               x                                 y



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



		// --- Cloud 0 Update ---
		sf::Vector2f posCloud = spritecloud.getPosition();
		posCloud += clouddirection * cloudspeed * deltaTime;
		spritecloud.setPosition(posCloud);

		if (posCloud.x < -300 || posCloud.x > 1920 + 300)
		{
			float random = static_cast<float>(rand()) / RAND_MAX;
			if (random < 0.5f)
			{
				clouddirection.x = 1.f;
				spritecloud.setScale(-1.f, 1.f);
				spritecloud.setPosition(-250, 0);
			}
			else
			{
				clouddirection.x = -1.f;
				spritecloud.setScale(1.f, 1.f);
				spritecloud.setPosition(1920 + 250, 0);
			}
			cloudspeed = rand() % 200 + 100;
		}




		// --- Cloud 1 Update ---
		sf::Vector2f posCloud1 = spritecloud1.getPosition();
		posCloud1 += cloud1direction * cloud1speed * deltaTime;
		spritecloud1.setPosition(posCloud1);

		if (posCloud1.x < -300 || posCloud1.x > 1920 + 300)
		{
			float random = static_cast<float>(rand()) / RAND_MAX;
			if (random < 0.5f)
			{
				cloud1direction.x = 1.f;
				spritecloud1.setScale(-1.f, 1.f);
				spritecloud1.setPosition(-250, 200);
			}
			else
			{
				cloud1direction.x = -1.f;
				spritecloud1.setScale(1.f, 1.f);
				spritecloud1.setPosition(1920 + 250, 200);
			}
			cloud1speed = rand() % 200 + 100;
		}





		// --- Cloud 2 Update ---
		sf::Vector2f posCloud2 = spritecloud2.getPosition();
		posCloud2 += cloud2direction * cloud2speed * deltaTime;
		spritecloud2.setPosition(posCloud2);

		if (posCloud2.x < -300 || posCloud2.x > 1920 + 300)
		{
			float random = static_cast<float>(rand()) / RAND_MAX;
			if (random < 0.5f)
			{
				cloud2direction.x = 1.f;
				spritecloud2.setScale(-1.f, 1.f);
				spritecloud2.setPosition(-250, 400);
			}
			else
			{
				cloud2direction.x = -1.f;
				spritecloud2.setScale(1.f, 1.f);
				spritecloud2.setPosition(1920 + 250, 400);
			}
			cloud2speed = rand() % 200 + 100;
		}



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

// 난수  
// 실시간프로그래밍 개념 
// 델타타임 : 프레임 간의 시간 차이 (현재시간 - 반복할때 돌아온 시간) 