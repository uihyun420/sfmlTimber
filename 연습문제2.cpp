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


	//--------------------------------------텍스처--------------------------------------------------------------
	sf::Texture textureBackgroud;
	textureBackgroud.loadFromFile("graphics/background.png");
	// sf::Texture → SFML에서 텍스처를 다루는 클래스 타입
	// textureBackgroud; 변수 이름

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/Bee.png");

	



	//--------------------------------------스프라이트----------------------------------------------------------
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackgroud);
	// sf::Sprite는 화면에 그릴 수 있는 이미지 객체
	// 스프라이트에 이미 로드된 텍스처를 연결하는 코드 

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








	//--------------------------------- 이벤트 루프 -------------------------------------------------------------
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



			//--------------------------------- 업데이트 -------------------------------------------------------------








			//------------------------------- 그리기--------------------------------------------------------------------
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

