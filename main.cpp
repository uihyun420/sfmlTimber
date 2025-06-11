#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>


// ������Ʈ, ��ο� ��� �ݺ�



int main()
{

	


	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");


	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	//��������                        //���ҽ� ��� 

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");


	sf::Texture texturebee;
	texturebee.loadFromFile("graphics/bee.png");

	sf::Texture texturecloud;
	texturecloud.loadFromFile("graphics/cloud.png");






	sf::Sprite spriteBackground; //sf::Sprite�� SFML���� �̹����� ȭ�鿡 ǥ���� �� �ְ� ���ִ� ��ü
	spriteBackground.setTexture(textureBackground);


	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition((1920 / 2) - (textureTree.getSize().x / 2), 0); // ��������Ʈ(Sprite)�� ȭ�� �� ��ġ�� �����ϴ� �Լ�



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

	srand((int)time(0));
	//����ð� ���� 

	const int NUM_CLOUDS = 3;

	sf::Sprite clouds[NUM_CLOUDS];
	sf::Vector2f cloudDirections[NUM_CLOUDS];

	float cloudSpeeds[NUM_CLOUDS];
	int cloudHeights[NUM_CLOUDS] = { 0, 200, 400 };
	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		clouds[i].setTexture(texturecloud);
		clouds[i].setPosition(0, cloudHeights[i]);
		clouds[i].setScale(-1.f, 1.f); // ó���� ���� �� ������ �̵�
		cloudDirections[i] = { 1.f, 0.f };
		cloudSpeeds[i] = rand() % 200 + 100;
	}



	while (window.isOpen()) 
	{

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


		// cloud �迭 


		for (int i = 0; i < NUM_CLOUDS; ++i)
		{
			// 1. ���� �̵�
			sf::Vector2f pos = clouds[i].getPosition();
			pos += cloudDirections[i] * cloudSpeeds[i] * deltaTime;
			clouds[i].setPosition(pos);

			// 2. ȭ�� ���̸� ����, �ӵ�, ��ġ �缳��
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

		// �׸���
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

// ����  
// �ǽð����α׷��� ���� 
// ��ŸŸ�� : ������ ���� �ð� ���� (����ð� - �ݺ��Ҷ� ���ƿ� �ð�) 