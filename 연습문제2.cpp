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

	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/Bee.png");

	



	//--------------------------------------��������Ʈ----------------------------------------------------------
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackgroud);
	// sf::Sprite�� ȭ�鿡 �׸� �� �ִ� �̹��� ��ü
	// ��������Ʈ�� �̹� �ε�� �ؽ�ó�� �����ϴ� �ڵ� 

	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.0f);
	spriteTree.setPosition(1920 * 0.5f, 0.0f);

	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);
	spriteBee.setPosition(100.f, 850.f);

	sf::Sprite spriteCloud1;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud1.setOrigin(textureCloud.getSize().x * 0.5f, textureCloud.getSize().y * 0.5f);
	spriteCloud1.setPosition(200.f, 100.f);

	sf::Sprite spriteCloud2;
	spriteCloud2.setTexture(textureCloud);
	spriteCloud2.setOrigin(textureCloud.getSize().x * 0.5f, textureCloud.getSize().y * 0.5f);
	spriteCloud2.setPosition(200.f, 300.f);

	sf::Sprite spriteCloud3;
	spriteCloud3.setTexture(textureCloud);
	spriteCloud3.setOrigin(textureCloud.getSize().x * 0.5f, textureCloud.getSize().y * 0.5f);
	spriteCloud3.setPosition(200.f, 500.f);








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








			//------------------------------- �׸���--------------------------------------------------------------------
			window.clear();
			window.draw(spriteBackground);
			window.draw(spriteCloud1);
			window.draw(spriteCloud2);
			window.draw(spriteCloud3);
			window.draw(spriteTree);
			window.draw(spriteBee);


			window.display();
		}
	}

}

