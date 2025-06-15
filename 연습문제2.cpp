#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>




enum  class Side { LEFT, RIGHT, NONE }; // 열거형(enum) 



void updateBranches(Side* Branches, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		Branches[i] = Branches[i - 1];  // 가지 배열을 한 칸씩 뒤로 밀기
	}

	int r = rand() % 3;
	switch (r)
	{
	case 0:
		Branches[0] = Side::LEFT;
		break;

	case 1:
		Branches[0] = Side::RIGHT;
		break;

	case 2:
		Branches[0] = Side::NONE;
		break;
	}
}



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


	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");


	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");







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







	const int NUM_BRANCHES = 6;   // const int 란 상수값으로 지정 
	sf::Sprite spriteBranch[NUM_BRANCHES];
	Side sideBranch[NUM_BRANCHES];



	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		spriteBranch[i].setTexture(textureBranch);
		spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);  // 나무에 붙이기 위한 중심 설정 
		spriteBranch[i].setPosition(1920 * 0.5f, 150.f); // y는 층별 위치 

		int r = rand() % 3;
		switch (r)
		{
		case 0:
			sideBranch[i] = Side::LEFT;
			break;

		case 1:
			sideBranch[i] = Side::RIGHT;
			break;

		case 2:
			sideBranch[i] = Side::NONE;
			break;
		}

	}

	sideBranch[NUM_BRANCHES - 1] = Side::NONE;   // 가장 위쪽 가지(맨 마지막 인덱스)를 비워두는 코드 , 나무의 꼭대기에는 가지가 없게 하거나, 게임 시작 시 충돌 방지 등으로 사용가능
	{
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			switch (sideBranch[i])
			{
			case Side::LEFT:
				spriteBranch[i].setScale(-1.f, 1.f);
				break;

			case Side::RIGHT:
				spriteBranch[i].setScale(1.f, 1.f);
				break;
			}
		}
	}



	// UI
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString("SCORE: 0");
	textScore.setCharacterSize(100); // 폰트 크기 조절
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(20, 20);

	sf::Text textMessage;
	textMessage.setFont(font);
	textMessage.setString("Press Enter to start!");
	textMessage.setCharacterSize(100);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(1920.f * 0.5f, 1080 * 0.5f);

	sf::Vector2f messageOrigin;   // 텍스트의 너비와 높이의 절반을 기준으로 중심점을 계산 
	messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;     
	messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
	textMessage.setOrigin(messageOrigin); // 계산한 중심점을 실제 텍스트의 기준점으로 설정



	sf::RectangleShape timeBar;      // 사각형 도형 
	float timeBarWidth = 400;        // 가로 400px
	float timeBarHeight = 80;        // 세로 80px
	timeBar.setSize({ timeBarWidth, timeBarHeight }); 
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition(1920.f * 0.5f - timeBarWidth * 0.5f, 1080.f - 100.f); // 타임바의 절반 길이(200px)를 빼서 정확히 중앙에 정렬합니다.	→ 즉, 타임바의 가운데가 화면 중앙에 오게 함.

	float remaingTime = 5.f;        // 남은 시간을 나타내는 변수 5초 
	float timeBarWidthPerSecond = timeBarWidth / 5.f;   // timeBarwidth는 초기 바의 너비로 400px 이걸 5초 동안 줄여야 하므로 1초에 줄어드는 길이 = 400 / 5 = 80px


	// 키보드 추가할 때 선언
	bool isLeft = false;       // 왼쪽 키가 눌린 상태인지
	bool isRight = false;      // 오른쪽 키가 눌린 상태인지



	// 게임 데이터 
	bool isPlaying = false;
	int score = 0; // 스코어 점수 0으로 초기화
	Side sidePlayer = Side::LEFT;  // 플레이어의 현재 위치 


	//--------------------------------- 이벤트 루프 -------------------------------------------------------------




	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();


		bool isLeftDown = false;   // 왼쪽 키가 눌린 순간 한 번만 반응하기 위한 플래그            왼쪽 방향키가 딱 한 번 눌린 순간에만 true
		bool isRightDown = false;  // 오른쪽 키가 눌린 순간 한 번만 반응하기 위한 플래그		 오른쪽 방향키가 딱 한 번 눌린 순간에만 true

		bool isLeftUp = false;     // 왼쪽 키가 떼어진 순간 한 번만 반응하기 위한 플래그          왼쪽 방향키를 딱 한 번 뗀 순간에만 true
		bool isRightUp = false;    // 오른쪽 키가 떼어진 순간 한 번만 반응하기 위한 플래그       오른쪽 방향키를 딱 한 번 뗀 순간에만 true 


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:         // 왼쪽 방향키가 눌렸을 때 
					if (!isLeft)                 // 만약 이전 왼쪽 방향키가 눌리지 않았다면
					{
						isLeftDown = true;       // 왼쪽 키가 처음 눌린 순간임을 표시 
					}
					isLeft = true;               // 왼쪽 키가 눌려있는 상태임을 표시
					break;

					
					if (!isPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						// 게임 시작 또는 재시작
						isPlaying = true;
						score = 0;
						textScore.setString("SCORE: 0");
						remaingTime = 5.f;

						textMessage.setString(" ");

						// 가지 초기화
						for (int i = 0; i < NUM_BRANCHES; i++)
						{
							sideBranch[i] = Side::NONE;
							spriteBranch[i].setScale(1.f, 1.f);
						}
					}



				case sf::Keyboard::Right:
					if (!isRight)
					{
						isRightDown = true;
					}
					isRight = true;
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:       // 왼쪽 방향키가 떼어졌을 때
					isLeft = false;            // 왼쪽 키가 눌리지 않은 상태임을 표시
					isLeftUp = true;           // 왼쪽 키가 떼어진 순간 임을 표시 
					break;

				case sf::Keyboard::Right:
					isRight = false;
					isRightUp = true;
					break;
				}
				break;
			}


		}





		//---------------------------------------- 업데이트 ----------------------------------------------------------------------------



		if (isPlaying)
		{
			remaingTime -= deltaTime;
			if (remaingTime < 0.f) // 시간이 0보다 작아졌는지 확인
			{
				remaingTime = 0.f; // 음수로 하지 않고 0으로 고정
				isPlaying = false; // 게임을 일시정지 또는 종료 상태로 바꿈
				textMessage.setString("Press Enter to restart!");
				sf::Vector2f messageOrigin;  
				messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
				messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
				textMessage.setOrigin(messageOrigin);
			}
			timeBar.setSize({ timeBarWidthPerSecond * remaingTime, timeBarHeight });

			if (sidePlayer == sideBranch[NUM_BRANCHES - 1]) // 플레이어와 나뭇가지가 충돌했을 때
			{
				isPlaying = false;
				textMessage.setString("Press Enter to restart!");
				sf::Vector2f messageOrigin;
				messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
				messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
				textMessage.setOrigin(messageOrigin);
			}
			else
			{
				score += 10;
				textScore.setString("SCORE: " + std::to_string(score));  // std::to_string(score)로 현재 점수를 문자열로 변환하여 "SCORE: 10", "SCORE: 20" 등으로 출력되게 합니다.
			}

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



			if (isLeftDown)
			{
				spritePlayer.setPosition(1920 * 0.5f - 200, 950);        // 플레이어가 중앙에서 왼쪽으로 이동 
				sidePlayer = Side::LEFT;
				isPlayerAxeLeft = true;                                  // 이때 도끼는 왼쪽에 있어야 하므로 상태 저장
				updateBranches(sideBranch, NUM_BRANCHES);
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float y = i * 150.f; // 가지 층별 간격, 150px 간격으로 위로 올라감
					spriteBranch[i].setPosition(1920 * 0.5f, y);

					switch (sideBranch[i])
					{
					case Side::LEFT:
						spriteBranch[i].setScale(-1.f, 1.f);
						spriteBranch[i].setPosition(1920 * 0.5f, 150.f * i);
						break;


					case Side::RIGHT:
						spriteBranch[i].setScale(1.f, 1.f);
						spriteBranch[i].setPosition(1920 * 0.5f, 150.f * i);
						break;

					}
				}

				
			}
			else if (isRightDown)
			{
				spritePlayer.setPosition(1920 * 0.5f + 200, 950);        // 플레이어가 중앙에서 오른쪽으로 이동 
				sidePlayer = Side::RIGHT;
				isPlayerAxeLeft = false;                                  // 이때 도끼는 오른쪽에 있어야 하므로 상태 저장
				updateBranches(sideBranch, NUM_BRANCHES);
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float y = i * 150.f; // 가지 층별 간격, 150px 간격으로 위로 올라감
					spriteBranch[i].setPosition(1920 * 0.5f, y);

					switch (sideBranch[i])
					{
					case Side::LEFT:
						spriteBranch[i].setScale(1.f, 1.f);
						spriteBranch[i].setPosition(1920 * 0.5f, 150.f * i);
						break;


					case Side::RIGHT:
						spriteBranch[i].setScale(1.f, 1.f);
						spriteBranch[i].setPosition(1920 * 0.5f, 150.f * i);
						break;

					}
				}

			}

			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					// 게임 시작 또는 재시작
					isPlaying = true;
					score = 0;
					remaingTime = 5.f;
					textScore.setString("SCORE: 0");
					textMessage.setString("");
					sidePlayer = Side::LEFT;
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



		}



		// 그리기
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

		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			if (sideBranch[i] != Side::NONE)
			{
				window.draw(spriteBranch[i]);
			}
		}

		window.draw(textScore);
		window.draw(timeBar);

		if (!isPlaying)
		{
			window.draw(textMessage);
		}

		window.display();
	}
}

