#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>




enum  class Side { LEFT, RIGHT, NONE }; // ������(enum) 



void updateBranches(Side* Branches, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		Branches[i] = Branches[i - 1];  // ���� �迭�� �� ĭ�� �ڷ� �б�
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
	������ �����ϱ� ���� ���
	srand(...) : rand() �Լ��� ������ ������ �������� ����

	time(0)�Ǵ� time(NULL) : ���� �ð��� �� ������ ��ȯ

	(int) : time() �Լ��� ��ȯ�ϴ� ���� int������ ����ȯ
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
		Beedirection.x = -1.f; // ��������
		spriteBee.setScale(1.f, 1.f); // ���� ����
		spriteBee.setPosition(1920 + 150, 850);
	}
	else
	{
		Beedirection.x = 1.f; // ����������
		spriteBee.setScale(-1.f, 1.f); // �¿����
		spriteBee.setPosition(-150, 850);
	}




	sf::Sprite spriteBackgroundElement[3];   // ���� 3�� 	
	sf::Vector2f directionElement[3];  // �� �迭�� ��ҵ��� ����
	float speedElement[3]; // �� �迭�� ����� �ӵ�



	for (int i = 0; i < 3; i++)
	{
		spriteBackgroundElement[i].setTexture(textureCloud);
		speedElement[i] = rand() % 15 + 0.5f; // 1 ~ 3 ������ �ӵ��� �� ��ҿ� ����
		float random = (float)rand() / RAND_MAX; // �̵������ ���� ��ġ ���� / 0.0���� 1.0 ������ �Ǽ����� �����ϴ� �ڵ�
		// �� random = 0.0���� 1.0 ������ �Ǽ����� ���� 

		if (random < 0.5f)     // < 50�ۼ�Ʈ 
		{
			directionElement[i].x = 1.f;  // ������ x�� ������ ���� �̵�
			spriteBackgroundElement[i].setOrigin(-150, 0.f);
			spriteBackgroundElement[i].setScale(1.f, 1.f);
			// ���� �̹����� �̵� ���⿡ �ڿ������� �°� ���̵��� �ð�ȿ�� ����,   x = -1.f �¿����
			spriteBackgroundElement[i].setPosition(0.f, rand() % 580 + 10);
			// -150�� ���� ȭ�� �ۿ������� ������ ������ ȿ���� ��. 
			// rand() % 300 + 100�� y�� ��ġ�� 100 ~ 399 �������� �����ϰ� ����
		}

		else    // > 50�ۼ�Ʈ
		{
			directionElement[i].x = -1.f;
			spriteBackgroundElement[i].setOrigin(0.f, 0.f);
			spriteBackgroundElement[i].setScale(1.f, 1.f);
			spriteBackgroundElement[i].setPosition(1920 + 150, rand() % 580 + 10);
			// ������ ȭ�� �� 150�ȼ��������� ������ �������� ����
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
	// ������ �÷��̾ ����ٴϵ���, setposition = ĳ���� ������ ��







	const int NUM_BRANCHES = 6;   // const int �� ��������� ���� 
	sf::Sprite spriteBranch[NUM_BRANCHES];
	Side sideBranch[NUM_BRANCHES];



	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		spriteBranch[i].setTexture(textureBranch);
		spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);  // ������ ���̱� ���� �߽� ���� 
		spriteBranch[i].setPosition(1920 * 0.5f, 150.f); // y�� ���� ��ġ 

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

	sideBranch[NUM_BRANCHES - 1] = Side::NONE;   // ���� ���� ����(�� ������ �ε���)�� ����δ� �ڵ� , ������ ����⿡�� ������ ���� �ϰų�, ���� ���� �� �浹 ���� ������ ��밡��
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
	textScore.setCharacterSize(100); // ��Ʈ ũ�� ����
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(20, 20);

	sf::Text textMessage;
	textMessage.setFont(font);
	textMessage.setString("Press Enter to start!");
	textMessage.setCharacterSize(100);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(1920.f * 0.5f, 1080 * 0.5f);

	sf::Vector2f messageOrigin;   // �ؽ�Ʈ�� �ʺ�� ������ ������ �������� �߽����� ��� 
	messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;     
	messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
	textMessage.setOrigin(messageOrigin); // ����� �߽����� ���� �ؽ�Ʈ�� ���������� ����



	sf::RectangleShape timeBar;      // �簢�� ���� 
	float timeBarWidth = 400;        // ���� 400px
	float timeBarHeight = 80;        // ���� 80px
	timeBar.setSize({ timeBarWidth, timeBarHeight }); 
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition(1920.f * 0.5f - timeBarWidth * 0.5f, 1080.f - 100.f); // Ÿ�ӹ��� ���� ����(200px)�� ���� ��Ȯ�� �߾ӿ� �����մϴ�.	�� ��, Ÿ�ӹ��� ����� ȭ�� �߾ӿ� ���� ��.

	float remaingTime = 5.f;        // ���� �ð��� ��Ÿ���� ���� 5�� 
	float timeBarWidthPerSecond = timeBarWidth / 5.f;   // timeBarwidth�� �ʱ� ���� �ʺ�� 400px �̰� 5�� ���� �ٿ��� �ϹǷ� 1�ʿ� �پ��� ���� = 400 / 5 = 80px


	// Ű���� �߰��� �� ����
	bool isLeft = false;       // ���� Ű�� ���� ��������
	bool isRight = false;      // ������ Ű�� ���� ��������



	// ���� ������ 
	bool isPlaying = false;
	int score = 0; // ���ھ� ���� 0���� �ʱ�ȭ
	Side sidePlayer = Side::LEFT;  // �÷��̾��� ���� ��ġ 


	//--------------------------------- �̺�Ʈ ���� -------------------------------------------------------------




	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();


		bool isLeftDown = false;   // ���� Ű�� ���� ���� �� ���� �����ϱ� ���� �÷���            ���� ����Ű�� �� �� �� ���� �������� true
		bool isRightDown = false;  // ������ Ű�� ���� ���� �� ���� �����ϱ� ���� �÷���		 ������ ����Ű�� �� �� �� ���� �������� true

		bool isLeftUp = false;     // ���� Ű�� ������ ���� �� ���� �����ϱ� ���� �÷���          ���� ����Ű�� �� �� �� �� �������� true
		bool isRightUp = false;    // ������ Ű�� ������ ���� �� ���� �����ϱ� ���� �÷���       ������ ����Ű�� �� �� �� �� �������� true 


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
				case sf::Keyboard::Left:         // ���� ����Ű�� ������ �� 
					if (!isLeft)                 // ���� ���� ���� ����Ű�� ������ �ʾҴٸ�
					{
						isLeftDown = true;       // ���� Ű�� ó�� ���� �������� ǥ�� 
					}
					isLeft = true;               // ���� Ű�� �����ִ� �������� ǥ��
					break;

					
					if (!isPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						// ���� ���� �Ǵ� �����
						isPlaying = true;
						score = 0;
						textScore.setString("SCORE: 0");
						remaingTime = 5.f;

						textMessage.setString(" ");

						// ���� �ʱ�ȭ
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
				case sf::Keyboard::Left:       // ���� ����Ű�� �������� ��
					isLeft = false;            // ���� Ű�� ������ ���� �������� ǥ��
					isLeftUp = true;           // ���� Ű�� ������ ���� ���� ǥ�� 
					break;

				case sf::Keyboard::Right:
					isRight = false;
					isRightUp = true;
					break;
				}
				break;
			}


		}





		//---------------------------------------- ������Ʈ ----------------------------------------------------------------------------



		if (isPlaying)
		{
			remaingTime -= deltaTime;
			if (remaingTime < 0.f) // �ð��� 0���� �۾������� Ȯ��
			{
				remaingTime = 0.f; // ������ ���� �ʰ� 0���� ����
				isPlaying = false; // ������ �Ͻ����� �Ǵ� ���� ���·� �ٲ�
				textMessage.setString("Press Enter to restart!");
				sf::Vector2f messageOrigin;  
				messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
				messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
				textMessage.setOrigin(messageOrigin);
			}
			timeBar.setSize({ timeBarWidthPerSecond * remaingTime, timeBarHeight });

			if (sidePlayer == sideBranch[NUM_BRANCHES - 1]) // �÷��̾�� ���������� �浹���� ��
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
				textScore.setString("SCORE: " + std::to_string(score));  // std::to_string(score)�� ���� ������ ���ڿ��� ��ȯ�Ͽ� "SCORE: 10", "SCORE: 20" ������ ��µǰ� �մϴ�.
			}

			for (int i = 0; i < 3; i++)
			{
				sf::Vector2f position = spriteBackgroundElement[i].getPosition();
				// Vector2f ��ġ, ����, �ӵ� �� ǥ���ϴ� Ÿ��
				// �����̸�(position) ����,  getPosition(); ������ ���� ��ġ�� ������

				position += directionElement[i] * speedElement[i] * deltaTime;
				// ������ ��ġ�� �ð��� ���� �ڿ������� �̵���Ŵ / �� �����ӿ��� ���� �����ӱ����� �ð�
				// ���� x �ӵ� x �ð� = �̵� �Ÿ�
				// �� position�� ���� ������ �����ǿ� �̵� �Ÿ��� �Ҵ��ϴ� ��.

				spriteBackgroundElement[i].setPosition(position);
				// i��° ������ position ��ǥ�� �̵����Ѷ�. ��� �ǹ� 

				if (position.x < -200 || position.x>1920 + 200)
					// ȭ�� �ػ󵵰� 1920*1080�̱� ������ -200�� ȭ�� ��, 2120�� ȭ�� ������ ��
					// ȭ�� ������ ���������� ����
				{
					float random = (float)rand() / RAND_MAX;  // 0.0 ~ 1.0 ������ ���� ���� 
					if (random < 0.5f)
					{
						directionElement[i].x = 1.f; // ������ �̵�
						spriteBackgroundElement[i].setScale(-1.f, 1.f); // �¿� ����
						spriteBackgroundElement[i].setPosition(-150, rand() % 580 + 10);
					}
					else
					{
						directionElement[i].x = -1.f; // �������� �̵�
						spriteBackgroundElement[i].setScale(1.f, 1.f);
						spriteBackgroundElement[i].setPosition(1920 + 200, rand() % 580 + 10);
					}
				}

				speedElement[i] = rand() % 15 + 0.5f;


			}
			sf::Vector2f beePosition = spriteBee.getPosition(); // ���� ���� ��ġ
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
				spritePlayer.setPosition(1920 * 0.5f - 200, 950);        // �÷��̾ �߾ӿ��� �������� �̵� 
				sidePlayer = Side::LEFT;
				isPlayerAxeLeft = true;                                  // �̶� ������ ���ʿ� �־�� �ϹǷ� ���� ����
				updateBranches(sideBranch, NUM_BRANCHES);
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float y = i * 150.f; // ���� ���� ����, 150px �������� ���� �ö�
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
				spritePlayer.setPosition(1920 * 0.5f + 200, 950);        // �÷��̾ �߾ӿ��� ���������� �̵� 
				sidePlayer = Side::RIGHT;
				isPlayerAxeLeft = false;                                  // �̶� ������ �����ʿ� �־�� �ϹǷ� ���� ����
				updateBranches(sideBranch, NUM_BRANCHES);
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float y = i * 150.f; // ���� ���� ����, 150px �������� ���� �ö�
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
					// ���� ���� �Ǵ� �����
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



		// �׸���
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

