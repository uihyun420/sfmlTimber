#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

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


	//--------------------------------------�ؽ�ó--------------------------------------------------------------
	sf::Texture textureBackgroud;
	textureBackgroud.loadFromFile("graphics/background.png");
	// sf::Texture �� SFML���� �ؽ�ó�� �ٷ�� Ŭ���� Ÿ��
	// textureBackgroud; ���� �̸�


	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	sf::Texture texturecloud1;
	texturecloud1.loadFromFile("graphics/cloud.png");

	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");


	//--------------------------------------��������Ʈ----------------------------------------------------------
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackgroud);
	// sf::Sprite�� ȭ�鿡 �׸� �� �ִ� �̹��� ��ü
	// ��������Ʈ�� �̹� �ε�� �ؽ�ó�� �����ϴ� �ڵ� 


	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
	spriteTree.setPosition(1920 * 0.5f, 0.f);


	sf::Sprite spriteCloud1;
	spriteCloud1.setTexture(texturecloud1);
	spriteCloud1.setOrigin(0.f, 0.f);
	spriteCloud1.setPosition(0.f, 0.f);
	float cloudSpeed = rand() % 200 + 100; // �����ӵ� ���� �߰�, 100 ~ 299 �� ����


	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setOrigin(0.f, 0.f);
	spriteBee.setPosition(0.f, 850.f);




	//--------------------------------- �̺�Ʈ ���� -------------------------------------------------------------
	while (window.isOpen())
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();


		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}



			//--------------------------------- ������Ʈ -------------------------------------------------------------

			spriteCloud1.move(cloudSpeed * deltaTime, 0.f); // move(x,y) ��������Ʈ�� x�������� y�������� �̵���Ű�� �Լ�
	



			//------------------------------- �׸���--------------------------------------------------------------------
			window.clear();
			window.draw(spriteBackground);
			window.draw(spriteCloud1);
			window.draw(spriteTree);
			window.draw(spriteBee);
			
			window.display();
		}
	}

}

