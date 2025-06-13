#include <SFML/Graphics.hpp>
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
	//sf::Clock clock; // �� �����Ӹ��� ������ ���� �ð�(delta time)�� ���� ����

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

	//
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


	sf::Font font; // ���� ����
	font.loadFromFile("fonts/KOMIKAP_.ttf");




	// 

	sf::Sprite spirteBackground;
	spirteBackground.setTexture(textureBackgroud); // setTexture ��������Ʈ�� �̹����� ������ �� ����ϴ� �Լ�
	sf::Sprite spirteTree;
	spirteTree.setTexture(textureTree);
	//spirteTree.setPosition(1920 * 0.5f - textureTree.getSize().x * 0.5f, 0);
	spirteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
	spirteTree.setPosition(1920 * 0.5f, 0.f);


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

	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setOrigin(textureAxe.getSize().x * 0.5f, textureAxe.getSize().y * 0.5f);



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


	// UI
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString("SCORE: 0"); 
	textScore.setCharacterSize(100); // �ؽ�Ʈ�� ���� ����
	textScore.setFillColor(sf::Color::White); // �ؽ�Ʈ �� ����
	textScore.setPosition(20, 20);


	sf::Text textStart;
	textStart.setFont(font);
	textStart.setCharacterSize(70); // �ؽ�Ʈ�� ���� ����
	textStart.setFillColor(sf::Color::White); // �ؽ�Ʈ �� ����
	textStart.setString("Press Enter to start!");
	textStart.setPosition(1920 * 0.5f - 400,1080 * 0.5f);







	sf::RectangleShape timebar;
	float timeBarWidth = 400;
	float timeBarHeight = 80;
	timebar.setSize({ timeBarWidth, timeBarHeight });
	timebar.setFillColor(sf::Color::Red);


	timebar.setPosition(1920 * 0.5f - timeBarWidth * 0.5f, 1080.f - 100.f);


	// ���� ������
	bool isPlaying = false; // �������϶� True��� �Ҹ�
	int score = 0;
	float remaingTime = 5.f;
	float timeBarSpeed = timeBarWidth / 5.f;   // 5��



	Side sidePlayer = Side::LEFT;
	switch (sidePlayer)
	{
	case Side::LEFT:
		spritePlayer.setScale(-1.f, 1.f);
		spritePlayer.setPosition(spirteTree.getPosition().x - 300.f, 950.f);
		// ������ ���� �տ� ���̱�
		spriteAxe.setPosition(spritePlayer.getPosition().x + 130.f, spritePlayer.getPosition().y - 50.f);
		spritePlayer.setScale(-1.f, 1.f);
		break;
	case Side::RIGHT:
		spritePlayer.setScale(1.f, 1.f);
		spritePlayer.setPosition(spirteTree.getPosition().x + 300.f, 950.f);

		spriteAxe.setPosition(spritePlayer.getPosition().x - 100.f, spritePlayer.getPosition().y - 50.f);
		spritePlayer.setScale(1.f, 1.f);
		break;
	}



	sf::Clock clock;

	bool isLeft = false;
	bool isRight = false;
	bool Axe = true;

	bool stop = false;

	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();

		// �̺�Ʈ ����
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
					Axe = false; // ���� �� ���� ����
					break;
				case sf::Keyboard::Right:
					if (!isRight)
					{
						isRightDown = true;

					}
					isRight = true;
					Axe = false;
					break;


				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					isLeft = false;
					isLeftUp = true;
					Axe = true;

					break;
				case sf::Keyboard::Right:
					isRight = false;
					isRightUp = true;
					Axe = true;

					break;


				case sf::Keyboard::Enter:
					if (isPlaying)
					{
						isPlaying = false;
						textStart.setString("Press Enter to resume!");
					}
					else
					{
						isPlaying = true;
					}

					break;

				}
				break;
			}

		}

		if(isPlaying)
		{ 
			remaingTime -= deltaTime;
			if (remaingTime <= 0.f)
			{
				remaingTime = 5.f; // Ÿ�ӹٰ� �� �Ҹ�Ǿ��� �Ҹ��� �׾��� �Ҹ�
				textStart.setString("Press Enter to restart!");
				isPlaying = false;
			}
			

			timebar.setSize({ timeBarSpeed * remaingTime, timeBarHeight });





			// ������Ʈ
			if (isRightDown || isLeftDown)
			{
				if (isLeftDown)
				{
					sidePlayer = Side::LEFT;
					if (sideBranch[NUM_BRANCHES - 1] == sidePlayer)
					{
						printf("���������� �¾���!\n");
						score = 0;
						textScore.setString("SCORE: " + std::to_string(score));
						isPlaying = false;
						textStart.setString("Press Enter to restart!");
						
					}
					else
					{
						score += 10; //  �浹���� �ʾ����� ������ �����ϱ� F
						textScore.setString("SCORE: " + std::to_string(score));
					}

				}
				if (isRightDown)
				{
					sidePlayer = Side::RIGHT;
					if (sideBranch[NUM_BRANCHES - 1] == sidePlayer)
					{
						printf("���������� �¾���!\n");
						score = 0;
						textScore.setString("SCORE: " + std::to_string(score));
						isPlaying = false;
						textStart.setString("Press Enter to restart!");

					}
					else
					{
						score += 10; //  �浹���� �ʾ����� ������ �����ϱ� 
						textScore.setString("SCORE: " + std::to_string(score));
					}

				}
				updateBranches(sideBranch, NUM_BRANCHES);


			
			}



			for (int i = 0; i < 3; ++i)
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

			sf::Vector2f beePos = spriteBackgroundElement[3].getPosition();
			beePos += directionElement[3] * speedElement[3] * deltaTime;
			spriteBackgroundElement[3].setPosition(beePos);

			// ȭ�� ���̸� ����/��ġ/�ӵ� ���� ����
			if (beePos.x < -200 || beePos.x > 1920 + 200)
			{
				float random = static_cast<float>(rand()) / RAND_MAX;

				if (random < 0.5f)
				{
					directionElement[3].x = 1.f;
					spriteBackgroundElement[3].setScale(-1.f, 1.f);
					spriteBackgroundElement[3].setPosition(-150.f, 800.f); // ���ʿ��� ����
				}
				else
				{
					directionElement[3].x = -1.f;
					spriteBackgroundElement[3].setScale(1.f, 1.f);
					spriteBackgroundElement[3].setPosition(1920.f + 150.f, 800.f); // �����ʿ��� ����
				}

				speedElement[3] = rand() % 200 + 100; // �ӵ� �缳��
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
				spritePlayer.setScale(-1.f, 1.f);
				spritePlayer.setPosition(spirteTree.getPosition().x - 300.f, 950.f);

				//���� ��ġ�� ������Ʈ
				spriteAxe.setPosition(spritePlayer.getPosition().x + 130.f, spritePlayer.getPosition().y - 55.f);
				spriteAxe.setScale(-1.f, 1.f);
				break;
			case Side::RIGHT:
				spritePlayer.setScale(1.f, 1.f);
				spritePlayer.setPosition(spirteTree.getPosition().x + 300.f, 950.f);

				spriteAxe.setPosition(spritePlayer.getPosition().x - 100.f, spritePlayer.getPosition().y - 55.f);
				spriteAxe.setScale(-1.f, 1.f);
				break;
			}


	}

		// �׸���
		window.clear();


		window.draw(spirteBackground);
		for (int i = 0; i < cloudCount; ++i)
		{
			window.draw(spriteBackgroundElement[i]);
		}
		window.draw(spirteTree);
		for (int i = 0; i < NUM_BRANCHES; ++i)
		{
			if (sideBranch[i] != Side::NONE)
			{
				window.draw(spriteBranch[i]);
			}
		}

		for (int i = cloudCount; i < 4; ++i)
		{
			window.draw(spriteBackgroundElement[i]);
		}


		window.draw(spritePlayer);

		if (Axe)
		{
			window.draw(spriteAxe);
		}

		window.draw(textScore);

		if (!isPlaying)
		{
			window.draw(textStart);
		}



		window.draw(timebar);
		window.display();

	}

	return 0;
}