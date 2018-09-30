#include "Header.h"
#include "Actor.h"
#include "Player.h"
#include "ListNode.h"
#include "Enemies.h"
#include "Collision.hpp"
#include <cmath>


using namespace sf;
int randNum(int min, int max) {// creates randome

	int x = rand() % min + max;
	return x;

}
int main()
{

	int flag = 0, randomNum = 0;
	double numberEnemies = 0;
	srand(time(NULL));
	const float FPS = 144.0f; //The desired FPS. (The number of updates each second).
	const float BULLETSPEED = 15; // Bullet speed
	const int SCREENX = 1920;
	const int SCREENY = 1080;
	RenderWindow window(VideoMode(SCREENX, SCREENY, 32), "A Video Game");
	window.setFramerateLimit(FPS);

	sf::Time t1 = sf::seconds(0.1f);
	Int32 milli = t1.asMilliseconds();


	myList * bulletList = new myList();
	std::list <Monster> monsterList;

	Event event;
	bool dKey = false;
	bool aKey = false;
	bool wKey = false;
	bool sKey = false;

	sf::Font font;
	if (!font.loadFromFile("mainFont.ttf"));
	sf::Text text;
	text.setFont(font);


	sf::Texture texture;
	texture.loadFromFile("pikachu.png");
	sf::Texture crosshair;
	crosshair.loadFromFile("crosshair.png");
	sf::Texture bullet1;
	bullet1.loadFromFile("bullet.png");
	sf::Texture monster;
	monster.loadFromFile("uwCoin.png");
	sf::Texture background;
	background.loadFromFile("wsuFlag.png");

	sf::Sprite sprite(texture);// loads sprite for the main player
	sf::Sprite crosshairSprite(crosshair);
	sf::Sprite bulletSprite(bullet1);
	sf::Sprite monsterSprite(monster);
	sf::Sprite back(background);

	//Collision::CreateTextureAndBitmask(texture, "pikachu.png");
	//Collision::CreateTextureAndBitmask(monster, "uwCoin.png");
	
	//Other Corner
	Player mainPlayer(sprite, 1920, 1080);// initializes the main player
	crosshairSprite.setOrigin(10, 10);// set x,y coordinates to the center of the crosshair image
	randomNum = rand() % 14 + 1;
	
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		int shouldSpawn1 = 0;
		int shouldSpawn2 = 0;
		//Random Coords for spawning enemies
		switch (randomNum) {
		case 1:
			shouldSpawn1 = 0;
			shouldSpawn2 = 0;
			break;
		case 2:
			shouldSpawn1 = 0;
			shouldSpawn2 = 480;
			break;
		case 3:
			shouldSpawn1 = 0;
			shouldSpawn2 = 960;
			break;
		case 4:
			shouldSpawn1 = 0;
			shouldSpawn2 = 1440;
			break;
		case 5:
			shouldSpawn1 = 0;
			shouldSpawn2 = 1920;
			break;
		case 6:
			shouldSpawn1 = 360;
			shouldSpawn2 = 1920;
			break;
		case 7:
			shouldSpawn1 = 720;
			shouldSpawn2 = 1920;
			break;
		case 8:
			shouldSpawn1 = 1080;
			shouldSpawn2 = 1920;
			break;
		case 9:
			shouldSpawn1 = 1080;
			shouldSpawn2 = 1440;
			break;
		case 10:
			shouldSpawn1 = 1080;
			shouldSpawn2 = 960;
			break;
		case 11:
			shouldSpawn1 = 1080;
			shouldSpawn2 = 480;
			break;
		case 12:
			shouldSpawn1 = 1080;
			shouldSpawn2 = 0;
			break;
		case 13:
			shouldSpawn1 = 720;
			shouldSpawn2 = 0;
			break;
		case 14:
			shouldSpawn1 = 360;
			shouldSpawn2 = 0;
			break;
		}
	
		/*if (shouldSpawn == 1) {
			Monster testMonster(monsterSprite, 100+shouldSpawn, 100+shouldSpawn);
			monsterList.push_front(testMonster);
		}*/
		

		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		Vector2f playerPosition = mainPlayer.sprite.getPosition();

		//While Player Health is not zero Execute Loop
		//if (mainPlayer.isAlive()) {
		//	//Spawn Enemies
		//	int j = 1;
		//	numberEnemies = j + (0.5 * (pow(2, j)));
		//	ceil(numberEnemies);
		//	++j;
		//	int i = 0;
		//	Monster testMonster(monsterSprite, shouldSpawn1, shouldSpawn2);
		//	monsterList.push_back(testMonster);
		//	if (i < numberEnemies /*&& !testMonster.undead()*/) {
		//		shouldSpawn1 = rand() % 1000 + 1;
		//		shouldSpawn2 = rand() % 1000 + 1;
		//		/*Monster testMonster(monsterSprite, shouldSpawn1, shouldSpawn2);
		//		monsterList.push_back(testMonster);*/
		//		if (monsterSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		//			Monster testMonster(monsterSprite, shouldSpawn1, shouldSpawn2);
		//			monsterList.push_back(testMonster);
		//		}
		//		i++;
		//	}
		//}
		
		//Handle events
		while (window.pollEvent(event))// main game loop
		{
			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::D) {
					dKey = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					aKey = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					sKey = true;
				}
				if (event.key.code == sf::Keyboard::W) {
					wKey = true;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{

				if (event.key.code == sf::Keyboard::D) {
					dKey = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					aKey = false;
				}

				if (event.key.code == sf::Keyboard::S) {
					sKey = false;
				}
				if (event.key.code == sf::Keyboard::W) {
					wKey = false;
				}


			}
			if (event.type == Event::Closed) window.close();



			if (event.type == sf::Event::MouseButtonPressed) {
				
				Vector2f mousePos(mouseX, mouseY);
				Bullet bullet(bulletSprite, playerPosition, mousePos);
				//Monster testMonster(monsterSprite, shouldSpawn,shouldSpawn);
				bulletList->insertAtFront(bullet);
				
			}
		}
		int listLength = bulletList->length;
		if (bulletList->pHead!=NULL) {// checks last bullet in the list to see if it should be destroyed
			ListNode * checker = bulletList->getEndOfList();
			if (checker->bullet.framesAlive > 100) {
				
				bulletList->deleteNode(checker);
			}
		}


		window.clear(Color(0, 0, 0));// clears screen to background color at the moment
							 
		// Update Positions
		
		crosshairSprite.setPosition(mouseX, mouseY);
		if (dKey == true) {// sets key bools to true when key is released
			if (playerPosition.x < SCREENX) {
				mainPlayer.move(5, 0);
			}
		}
		if (aKey == true) {
			if (playerPosition.x > 0) {
				mainPlayer.move(-5, 0);
			}

		}
		if (sKey == true) {
			if (playerPosition.y < SCREENY) {
				mainPlayer.move(0, 5);
			}
			
		}
		if (wKey == true) {
			if (playerPosition.y > 0) {
				mainPlayer.move(0, -5);
			}
		}
		//circle.setPosition(playerPosition.x, playerPosition.y);
		
		
		//window.draw(circle);
		
		listLength = bulletList->length;
		if (listLength >= 1) {
			ListNode * tempP = bulletList->pHead;
			
			while (tempP != NULL) {
				Bullet & tempBullet = tempP->bullet;	// need to use reference so that functions apply to bullets in the list and not a copy of bullet
				/*if (Collision::PixelPerfectTest(mainPlayer.sprite, )) {
	
				}*/
				tempBullet.move(tempBullet.direction.x*BULLETSPEED, tempBullet.direction.y*BULLETSPEED);
				tempBullet.draw(window);
				tempBullet.addFrame();					// adds one to how long the bullet has been alive
				tempP = tempP->next;
			}
		}


		std::list <Monster> ::iterator it;
		if (monsterList.empty() == false) {// iterates through monsterlist and updates evey monster in the list
			for (it = monsterList.begin(); it != monsterList.end(); ++it) {
				Monster & tempMonster = *it;
				if (Collision::PixelPerfectTest(mainPlayer.sprite, monsterSprite)) {
					/*	Monster testMonster(monsterSprite, shouldSpawn1, shouldSpawn2);
					monsterList.push_back(testMonster);*/
					mainPlayer.health -= tempMonster.damage;
					
					if (mainPlayer.health == 0) {
						return 0;
					}
				}
				tempMonster.setDirection(playerPosition);
				tempMonster.move(tempMonster.direction.x, tempMonster.direction.y);
				tempMonster.draw(window);
			}
		}
		//Spawn One Monster
		if (flag == 0) {
			Monster testMonster(monsterSprite, shouldSpawn1, shouldSpawn2);
			monsterList.push_back(testMonster);
			flag++;
		}
		mainPlayer.draw(window);// draws main player
		window.draw(text);
		//window.draw(monsterSprite);//These need to be drawn last
		window.draw(crosshairSprite);// draws crosshair
		window.display();//displays screen
	}
	return 0;
}