#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

int main()
{
	sf::Clock clock;
	srand((int)time(0));
	/*
	난수를 설정하기 위해 사용
	srand(...) : rand() 함수가 생성할 난수의 시작점을 설정

	time(0)또는 time(NULL) : 현재 시간을 초 단위로 변환

	(int) : time() 함수가 반환하는 값을 int형으로 형변환
	*/

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");


	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");


	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");


	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	bool isPlayerAxeLeft = false;








	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);

	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
	spriteTree.setPosition(1920 * 0.5f, 0.f);


	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setOrigin(0.f, 0.f);
	spriteBee.setPosition(50, 850);
	
	sf::Vector2f Beedirection;
	float spriteSpeedBee;

	float randomDirectionBee = (float)rand() / RAND_MAX;
	spriteSpeedBee = 1.f;

	if (randomDirectionBee < 0.5f)
	{
		Beedirection.x = -1.f; // 왼쪽으로
		spriteBee.setScale(1.f, 1.f); // 방향 유지
		spriteBee.setPosition(1920 + 150, 850);
	}
	else
	{
		Beedirection.x = 1.f; // 오른쪽으로
		spriteBee.setScale(-1.f, 1.f); // 좌우반전
		spriteBee.setPosition(-150, 850);
	}




	sf::Sprite spriteBackgroundElement[3];   // 구름 3개 	
	sf::Vector2f directionElement[3];  // 각 배열의 요소들의 방향
	float speedElement[3]; // 각 배열의 요소의 속도



	for (int i = 0; i < 3; i++)
	{
		spriteBackgroundElement[i].setTexture(textureCloud);
		speedElement[i] = rand() % 15 + 0.5f; // 1 ~ 3 사이의 속도를 각 요소에 설정
		float random = (float)rand() / RAND_MAX; // 이동방향과 시작 위치 설정 / 0.0에서 1.0 사이의 실수값을 생성하는 코드
		// 즉 random = 0.0에서 1.0 사이의 실수값을 생성 

		if (random < 0.5f)     // < 50퍼센트 
		{
			directionElement[i].x = 1.f;  // 구름을 x축 오른쪽 으로 이동
			spriteBackgroundElement[i].setOrigin(-150, 0.f);
			spriteBackgroundElement[i].setScale(1.f, 1.f);
			// 구름 이미지가 이동 방향에 자연스럽게 맞게 보이도록 시각효과 조정,   x = -1.f 좌우반전
			spriteBackgroundElement[i].setPosition(0.f, rand() % 580 + 10);
			// -150은 왼쪽 화면 밖에서부터 서서히 들어오는 효과를 줌. 
			// rand() % 300 + 100은 y축 위치를 100 ~ 399 범위에서 랜덤하게 선택
		}

		else    // > 50퍼센트
		{
			directionElement[i].x = -1.f;
			spriteBackgroundElement[i].setOrigin(0.f, 0.f);
			spriteBackgroundElement[i].setScale(1.f, 1.f);
			spriteBackgroundElement[i].setPosition(1920 + 150, rand() % 580 + 10);
			// 오른쪽 화면 밖 150픽셀에서부터 서서히 왼쪽으로 들어옴
		}

	}


	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setOrigin(texturePlayer.getSize().x * 0.5f, texturePlayer.getSize().y * 0.5f);
	spritePlayer.setPosition(1920 * 0.5f, 950);



	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setOrigin(textureAxe.getSize().x * 0.5f, textureAxe.getSize().y * 0.5f);
	spriteAxe.setPosition(spritePlayer.getPosition().x + texturePlayer.getSize().x * 0.5f - 50.f, spritePlayer.getPosition().y);    
	// 도끼가 플레이어를 따라다니도록, setposition = 캐릭터 오른쪽 끝




	//--------------------------------- 이벤트 루프 -------------------------------------------------------------




		while (window.isOpen())
		{
			sf::Time time = clock.restart();
			float deltaTime = time.asSeconds();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}





			//---------------------------------------- 업데이트 ----------------------------------------------------------------------------
			for (int i = 0; i < 3; i++)
			{
				sf::Vector2f position = spriteBackgroundElement[i].getPosition();
				// Vector2f 위치, 방향, 속도 등 표현하는 타입
				// 변수이름(position) 선언,  getPosition(); 구름의 현재 위치를 가져옴

				position += directionElement[i] * speedElement[i] * deltaTime;
				// 구름의 위치를 시간에 따라 자연스럽게 이동시킴 / 한 프레임에서 다음 프레임까지의 시간
				// 방향 x 속도 x 시간 = 이동 거리
				// 즉 position은 현재 구름의 포지션에 이동 거리를 할당하는 것.

				spriteBackgroundElement[i].setPosition(position);
				// i번째 구름을 position 좌표로 이동시켜라. 라는 의미 

				if (position.x < -200 || position.x>1920 + 200)
					// 화면 해상도가 1920*1080이기 때문에 -200은 화면 밖, 2120은 화면 오른쪽 밖
					// 화면 밖으로 나갔는지의 가정
				{
					float random = (float)rand() / RAND_MAX;  // 0.0 ~ 1.0 사이의 난수 설정 
					if (random < 0.5f)
					{
						directionElement[i].x = 1.f; // 오른쪽 이동
						spriteBackgroundElement[i].setScale(-1.f, 1.f); // 좌우 반전
						spriteBackgroundElement[i].setPosition(-150, rand() % 580 + 10);
					}
					else
					{
						directionElement[i].x = -1.f; // 왼쪽으로 이동
						spriteBackgroundElement[i].setScale(1.f, 1.f);
						spriteBackgroundElement[i].setPosition(1920 + 200, rand() % 580 + 10);
					}
				}

				speedElement[i] = rand() % 15 + 0.5f;


			}
			sf::Vector2f beePosition = spriteBee.getPosition(); // 벌의 현재 위치
			beePosition += Beedirection * spriteSpeedBee * deltaTime;
			spriteBee.setPosition(beePosition);


			if (beePosition.x < -200 || beePosition.x> 1920 + 200)
			{
				spriteSpeedBee = rand() % 5 + 5;

				float randomDirectionBee = (float)rand() / RAND_MAX;

				if (randomDirectionBee < 0.5f)
				{
					Beedirection.x = -1.f;
					spriteBee.setScale(1.f, 1.f);
					spriteBee.setPosition(1920 + 150, 850);
				}
				else
				{
					Beedirection.x = 1.f;
					spriteBee.setScale(-1.f, 1.f);
					spriteBee.setPosition(-150, 850);
				}
			}
			

			if (isPlayerAxeLeft)
			{
				spriteAxe.setPosition(spritePlayer.getPosition().x - texturePlayer.getSize().x * 0.5f + 50.f, spritePlayer.getPosition().y);
				spriteAxe.setScale(-1.f, 1.f);
			}
			else
			{
				spriteAxe.setPosition(spritePlayer.getPosition().x + texturePlayer.getSize().x * 0.5f + 50.f, spritePlayer.getPosition().y);
				spriteAxe.setScale(1.f, 1.f);
			}


			window.clear();
			window.draw(spriteBackground);

			for (int i = 0; i < 3; i++)
			{
				window.draw(spriteBackgroundElement[i]);
			}

			window.draw(spriteTree);
			window.draw(spriteBee);
			window.draw(spritePlayer);
			window.draw(spriteAxe);

			window.display();
		}
	}

