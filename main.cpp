#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

void updateBranches(Side* branches, int size)
{
	for (int i = size - 1; i > 0; --i)
	{
		branches[i] = branches[i - 1];
	}

	int r = rand() % 3;
	switch (r)
	{
	case 0:
		branches[0] = Side::LEFT;
		break;
	case 1:
		branches[0] = Side::RIGHT;
		break;
	default:
		branches[0] = Side::NONE;
		break;
	}
}

int main()
{
	srand((int)time(0));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

	// 리소스
	sf::Texture textureBackgroud;
	textureBackgroud.loadFromFile("graphics/background.png");
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");


	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	sf::SoundBuffer bufferChop;
	bufferChop.loadFromFile("sound/chop.wav");
	sf::SoundBuffer bufferDeath;
	bufferDeath.loadFromFile("sound/death.wav");
	sf::SoundBuffer bufferOutOfTime;
	bufferOutOfTime.loadFromFile("sound/out_of_time.wav");

	//
	sf::Sprite spirteBackground;
	spirteBackground.setTexture(textureBackgroud);
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	//spirteTree.setPosition(1920 * 0.5f - textureTree.getSize().x * 0.5f, 0);
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
	spriteTree.setPosition(1920 * 0.5f, 0.f);

	sf::Sprite spriteBackgroundElement[4];
	float speedElement[4];
	sf::Vector2f directionElement[4];

	int cloudCount = 3;

	for (int i = 0; i < 4; ++i)
	{
		if (i < cloudCount)
		{
			spriteBackgroundElement[i].setTexture(textureCloud);
			speedElement[i] = rand() % 200 + 100;
			float random = (float)rand() / RAND_MAX; // 0.f ~ 1.f
			if (random < 0.5f)
			{
				directionElement[i].x = 1.f;
				spriteBackgroundElement[i].setScale(-1.f, 1.f);
				spriteBackgroundElement[i].setPosition(-150, rand() % 300 + 100);
			}
			else
			{
				directionElement[i].x = -1.f;
				spriteBackgroundElement[i].setScale(1.f, 1.f);
				spriteBackgroundElement[i].setPosition(1920 + 150, rand() % 300 + 100);
			}
		}
		else
		{
			spriteBackgroundElement[i].setTexture(textureBee);
			float random = (float)rand() / RAND_MAX; // 0.f ~ 1.f
			if (random < 0.5f)
			{
				directionElement[i].x = 1.f;
				spriteBackgroundElement[i].setScale(-1.f, 1.f);
			}
			else
			{
				directionElement[i].x = -1.f;
				spriteBackgroundElement[i].setScale(1.f, 1.f);
			}
			speedElement[i] = rand() % 200 + 100;
			spriteBackgroundElement[i].setPosition(500, 700);
		}
	}

	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setOrigin(texturePlayer.getSize().x * 0.5f, texturePlayer.getSize().y);
	spritePlayer.setPosition(1920 * 0.5f, 950.f);
	Side sidePlayer = Side::LEFT;
	switch (sidePlayer)
	{
	case Side::LEFT:
	{
		spritePlayer.setScale(-1.f, 1.f);
		spritePlayer.setPosition(spriteTree.getPosition().x - 300.f, 950.f);
	}
	break;
	case Side::RIGHT:
	{
		spritePlayer.setScale(1.f, 1.f);
		spritePlayer.setPosition(spriteTree.getPosition().x + 300.f, 950.f);
	}
	break;
	}
	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);

	const int NUM_BRANCHES = 6;
	sf::Sprite spriteBranch[NUM_BRANCHES];
	Side sideBranch[NUM_BRANCHES];
	for (int i = 0; i < NUM_BRANCHES; ++i)
	{
		spriteBranch[i].setTexture(textureBranch);
		spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);
		spriteBranch[i].setPosition(1920 * 0.5f, i * 150.f);

		int r = rand() % 3;
		switch (r)
		{
		case 0:
			sideBranch[i] = Side::LEFT;
			break;
		case 1:
			sideBranch[i] = Side::RIGHT;
			break;
		default:
			sideBranch[i] = Side::NONE;
			break;
		}
	}
	sideBranch[NUM_BRANCHES - 1] = Side::NONE;
	for (int i = 0; i < NUM_BRANCHES; ++i)
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

	sf::Sprite testLog;
	testLog.setTexture(textureLog);
	testLog.setOrigin(textureLog.getSize().x * 0.5f, textureLog.getSize().y);
	sf::Vector2f logInitPosition = spriteTree.getPosition();
	logInitPosition.y = textureTree.getSize().y;
	testLog.setPosition(logInitPosition);

	bool isActiveTestLog = false;
	sf::Vector2f testLogDirection = { 1.f, -1.f };
	float testLogSpeed = 2000.f;

	sf::Vector2f gravity = { 0.f, 6000.f };
	sf::Vector2f testLogVelocity = testLogDirection * testLogSpeed;







	//새로운 통나무 배열 추가 
	const int MAX_LOGS = 30;

	sf::Sprite flyingLogs[MAX_LOGS];
	sf::Vector2f flyingLogVelocities[MAX_LOGS];
	bool isActiveFlyingLog[MAX_LOGS]; 


	//초기화 , 위치 설정
	for (int i = 0; i < MAX_LOGS; ++i)
	{
		flyingLogs[i].setTexture(textureLog);
		flyingLogs[i].setOrigin(textureLog.getSize().x * 0.5f, textureLog.getSize().y);
		flyingLogs[i].setPosition(logInitPosition);
		isActiveFlyingLog[i] = false;
	}





	// UI
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString("SCORE: 0");
	textScore.setCharacterSize(100);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(20, 20);

	sf::Text textMessage;
	textMessage.setFont(font);
	textMessage.setString("Press Enter to start!");
	textMessage.setCharacterSize(100);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(1920.f * 0.5f, 1080 * 0.5f);
	sf::Vector2f messageOrigin;
	messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
	messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
	textMessage.setOrigin(messageOrigin);

	sf::RectangleShape timeBar;
	float timeBarWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize({ timeBarWidth, timeBarHeight });
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition(1920.f * 0.5f - timeBarWidth * 0.5f, 1080.f - 100.f);

	//
	sf::Sound soundChop;
	soundChop.setBuffer(bufferChop);
	sf::Sound soundDeath;
	soundDeath.setBuffer(bufferDeath);
	sf::Sound soundOutOfTime;
	soundOutOfTime.setBuffer(bufferOutOfTime);

	// 게임 데이터
	bool isPlaying = false;
	int score = 0;
	float remaingTime = 5.f;
	float timeBarWidthPerSecond = timeBarWidth / 5.f;

	sf::Clock clock;

	bool isLeft = false;
	bool isRight = false;
	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();

		// 이벤트 루프
		sf::Event event;
		bool isLeftDown = false;
		bool isLeftUp = false;
		bool isRightDown = false;
		bool isRightUp = false;

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
				case sf::Keyboard::Left:
					if (!isLeft)
					{
						isLeftDown = true;
					}
					isLeft = true;
					break;
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
				case sf::Keyboard::Left:
					isLeft = false;
					isLeftUp = true;
					break;
				case sf::Keyboard::Right:
					isRight = false;
					isRightUp = true;
					break;
				case sf::Keyboard::Return:
					isPlaying = !isPlaying;
					if (!isPlaying)
					{
						textMessage.setString("Press Enter to resume!");
						sf::Vector2f messageOrigin;
						messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
						messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
						textMessage.setOrigin(messageOrigin);
					}
					else
					{
						if (remaingTime == 0.f || sidePlayer == sideBranch[NUM_BRANCHES - 1])
						{
							score = 0;
							textScore.setString("SCORE: " + std::to_string(score));
							remaingTime = 5.f;
							sideBranch[NUM_BRANCHES - 1] = Side::NONE;
						}

					}
					break;
				}
				break;
			}
		}

		if (isPlaying)
		{
			remaingTime -= deltaTime;
			if (remaingTime < 0.f)
			{
				remaingTime = 0.f;
				isPlaying = false;
				textMessage.setString("Press Enter to restart!");
				sf::Vector2f messageOrigin;
				messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
				messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
				textMessage.setOrigin(messageOrigin);
				soundOutOfTime.play();
			}
			timeBar.setSize({ timeBarWidthPerSecond * remaingTime, timeBarHeight });

			// 업데이트
			if (isRightDown || isLeftDown)
			{
				isActiveTestLog = true;
				testLog.setPosition(logInitPosition);
				testLogVelocity = testLogDirection * testLogSpeed;







				if (isLeftDown)
				{
					sidePlayer = Side::LEFT;
				}
				if (isRightDown)
				{
					sidePlayer = Side::RIGHT;
				}







				for (int i = 0; i < MAX_LOGS; ++i)
				{
					if (!isActiveFlyingLog[i])
					{
						flyingLogs[i].setPosition(logInitPosition);
						sf::Vector2f dir = (sidePlayer == Side::LEFT) ? sf::Vector2f(-1.f, -1.f) : sf::Vector2f(1.f, -1.f);
						flyingLogVelocities[i] = dir * testLogSpeed;
						isActiveFlyingLog[i] = true;
						break; // 한 개만 발사
					}
				}







				updateBranches(sideBranch, NUM_BRANCHES);
				soundChop.play();

				if (sidePlayer == sideBranch[NUM_BRANCHES - 1])
				{
					isPlaying = false;
					textMessage.setString("Press Enter to restart!");
					sf::Vector2f messageOrigin;
					messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
					messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
					textMessage.setOrigin(messageOrigin);
					soundDeath.play();
				}
				else
				{
					score += 10;
					textScore.setString("SCORE: " + std::to_string(score));
				}
			}






			for (int i = 0; i < MAX_LOGS; ++i)
			{
				if (isActiveFlyingLog[i])
				{
					flyingLogVelocities[i] += gravity * deltaTime;

					sf::Vector2f pos = flyingLogs[i].getPosition();
					pos += flyingLogVelocities[i] * deltaTime;
					flyingLogs[i].setPosition(pos);

					if (pos.x < -200 || pos.x > 2200 || pos.y > 1200)
					{
						isActiveFlyingLog[i] = false;
					}
				}
			}








			for (int i = 0; i < 4; ++i)
			{
				sf::Vector2f position = spriteBackgroundElement[i].getPosition();
				position += directionElement[i] * speedElement[i] * deltaTime;
				spriteBackgroundElement[i].setPosition(position);
				if (position.x < -200 || position.x > 1920 + 200)
				{
					float random = (float)rand() / RAND_MAX;
					if (random < 0.5f)
					{
						directionElement[i].x = 1.f;
						spriteBackgroundElement[i].setScale(-1.f, 1.f);
						spriteBackgroundElement[i].setPosition(0 - 150, rand() % 300 + 100);
					}
					else
					{
						directionElement[i].x = -1.f;
						spriteBackgroundElement[i].setScale(1.f, 1.f);
						spriteBackgroundElement[i].setPosition(1920 + 150, rand() % 300 + 100);
					}
					speedElement[i] = rand() % 200 + 100;
				}
			}

			for (int i = 0; i < NUM_BRANCHES; ++i)
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

			switch (sidePlayer)
			{
			case Side::LEFT:
			{
				spritePlayer.setScale(-1.f, 1.f);
				spritePlayer.setPosition(spriteTree.getPosition().x - 300.f, 950.f);
				spriteAxe.setScale(1.f, 1.f);

				sf::Vector2f pos = spritePlayer.getPosition();
				pos.x += 50.f;
				pos.y -= 75.f;
				spriteAxe.setPosition(pos);
			}
			break;
			case Side::RIGHT:
			{
				spritePlayer.setScale(1.f, 1.f);
				spritePlayer.setPosition(spriteTree.getPosition().x + 300.f, 950.f);
				spriteAxe.setScale(-1.f, 1.f);
				sf::Vector2f pos = spritePlayer.getPosition();
				pos.x -= 50.f;
				pos.y -= 75.f;
				spriteAxe.setPosition(pos);
			}
			break;
			}

			if (isActiveTestLog)
			{
				testLogVelocity += gravity * deltaTime;

				sf::Vector2f position = testLog.getPosition();
				position += testLogVelocity * deltaTime;
				testLog.setPosition(position);
			}


		}
		// 그리기
		window.clear();

		// WORLD
		window.draw(spirteBackground);
		for (int i = 0; i < cloudCount; ++i)
		{
			window.draw(spriteBackgroundElement[i]);
		}
		window.draw(spriteTree);
		for (int i = 0; i < NUM_BRANCHES; ++i)
		{
			if (sideBranch[i] != Side::NONE)
			{
				window.draw(spriteBranch[i]);
			}
		}

		for (int i = 0; i < MAX_LOGS; ++i)
		{
			if (isActiveFlyingLog[i])
			{
				window.draw(flyingLogs[i]);
			}
		}

		//window.draw(testLog);

		for (int i = cloudCount; i < 4; ++i)
		{
			window.draw(spriteBackgroundElement[i]);
		}

		window.draw(spritePlayer);
		if (isLeft || isRight)
		{
			window.draw(spriteAxe);
		}

		// UI 
		window.draw(textScore);
		window.draw(timeBar);

		if (!isPlaying)
		{
			window.draw(textMessage);
		}
		window.display();
	}

	return 0;
}