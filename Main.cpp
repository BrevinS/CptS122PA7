#include "Header.h"
#include "Actor.h"
#include "Player.h"
#include "ListNode.h"
#include "Enemies.h"
#include "Menu.h"
#include "Andy.h"
#include <math.h>
#include <chrono>
//PROGRAMMERS: Leonard Brkanac
//			   Marco Ares
//			   Brevin Simon

using namespace sf;

int randNum(int min, int max) {// creates random
	int x = rand() % (max - min + 1);
	return x;
}
int main()
{
	srand(time(NULL));
	const float FPS = 144.0f; //The desired FPS. (The number of updates each second).
	const float BULLETSPEED = 15; // Bullet speed
	const int SCREENX = 1920;
	const int SCREENY = 1080;

	RenderWindow window(VideoMode(SCREENX, SCREENY, 32), "Cat Invaders.exe");
	window.setFramerateLimit(FPS);

	CircleShape circle(10.0f);
	circle.setOrigin(0, 0);
	circle.setPosition(0, 0);

	myList<Bullet> * bulletList = new myList<Bullet>();
	myList<Monster> * monsterList = new myList<Monster>();
	//myList<Andy> * andyList = new myList<Andy>();

	sf::Event event;
	bool dKey = false;
	bool aKey = false;
	bool wKey = false;
	bool sKey = false;
	bool upKey = false;
	bool downKey = false;
	bool enterKEy = false;

	sf::Font font;
	//font.loadFromFile("Antonio-Bold.ttf");
	if (!font.loadFromFile("mainFont.ttf")) {
		OutputDebugStringA("Error");
	}
	
	

	sf::Text text;
	text.setFont(font);
	sf::Text text2;
	text2.setFont(font);

	sf::Texture texture;
	sf::Texture crosshair;
	sf::Texture bullet1;
	sf::Texture monster;
	sf::Texture andy;
	texture.loadFromFile("mainCharacter.png");
	crosshair.loadFromFile("crosshair.png");
	bullet1.loadFromFile("bullet.png");
	monster.loadFromFile("creatureCharacter.png");
	//andy.loadFromFile("finalBoss.png");
	sf::Sprite sprite(texture);// loads sprite for the main player
	sf::Sprite crosshairSprite(crosshair);
	sf::Sprite bulletSprite(bullet1);
	sf::Sprite monsterSprite(monster);
	//sf::Sprite andySprite(andy);

	Player mainPlayer(sprite, 1000, 500);// initializes the main player
	Monster testMonster(monsterSprite, 0, 0); // intitializes the enemy

	crosshairSprite.setOrigin(10, 10);// set x,y coordinates to the center of the cross-hair image

	window.setMouseCursorVisible(false);
	int flag = 0;
	int flag1 = 0;
	int round = 1;
	int numberEnemies = 0;
	int spawnLocation = 0;
	int shouldSpawn1 = 0;
	int shouldSpawn2 = 0;
	
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		//Main Game Loop
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		Vector2f playerPosition = mainPlayer.sprite.getPosition();

		//std::string temp999 = std::to_string(mouseX) + "\n";
		//OutputDebugStringA(temp999.c_str());
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
				if (event.key.code == sf::Keyboard::Up) {
					upKey = true;
				}
				if (event.key.code == sf::Keyboard::Down) {
					downKey = true;
				}
				if (event.key.code == sf::Keyboard::Return) {
					enterKEy = true;
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
				if (event.key.code == sf::Keyboard::Up) {
					upKey = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					downKey = false;
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					enterKEy = false;
				}
			}
			if (event.type == Event::Closed) 
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				Vector2f mousePos(mouseX, mouseY);
				Bullet bullet(bulletSprite, playerPosition, mousePos);
				Monster testMonster(monsterSprite, mouseX, mouseY);
				//Andy finalBoss(andySprite, mouseX, mouseY);
				//std::cout << "Hello";
				bulletList->insertAtFront(bullet);
				//monsterList->insertAtFront(testMonster);
				//monsterList.push_front(testMonster);

				//text.setString(int 1);
			}
		}
		int listLength = bulletList->length;
		if (bulletList->pHead != NULL) {// checks last bullet in the list to see if it should be destroyed based on how long its been present in the scene
			ListNode<Bullet> * checker = bulletList->getEndOfList();
			if (checker->object.framesAlive > 150) {
				bulletList->deleteLastNode();
			}
		}

		ListNode<Bullet> * tempBulletCollision = bulletList->pHead;// this block of code checks if a bullet intersects with an enemy and deletes the bullet, 
		while (tempBulletCollision != NULL) {					   //while also applying damage to the enemy and deleting it if its health is at or below 0
			FloatRect bulletBoundingBox = tempBulletCollision->object.sprite.getGlobalBounds();
			ListNode<Monster> * tempMonsterCollision = monsterList->pHead;
			while (tempMonsterCollision != NULL) {
				FloatRect monsterBoundingBox = tempMonsterCollision->object.sprite.getGlobalBounds();
				if (bulletBoundingBox.intersects(monsterBoundingBox)) {
					bulletList->deleteNode(tempBulletCollision);
					tempBulletCollision = bulletList->pHead;

					tempMonsterCollision->object.health -= mainPlayer.damage;

					if (tempMonsterCollision->object.health <= 0) {
						monsterList->deleteNode(tempMonsterCollision);
						break;										// don't continue loop if monster was deleted
					}
					break;											// don't continue loop if bullet was deleted
				}
				//COLLISION WITH ENEMY AKA TAKE DAMAGE

				tempMonsterCollision = tempMonsterCollision->next;
			}

			//code for final boss
			/*ListNode<Andy> * andyCollision = andyList->pHead;
			while (andyCollision != NULL) {
				FloatRect bossBoundingBox = andyCollision->object.sprite.getGlobalBounds();
				if (bulletBoundingBox.intersects(bossBoundingBox)) {
					bulletList->deleteNode(tempBulletCollision);
					tempBulletCollision = bulletList->pHead;

					andyCollision->object.health -= mainPlayer.damage;

					if (andyCollision->object.health <= 0) {
						andyList->deleteNode(andyCollision);
						break;
					}
					break;
				}
			}*/
			if (tempBulletCollision != NULL) {
				tempBulletCollision = tempBulletCollision->next;
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

		if (bulletList->length > 0) {// updates and draws every bullet
			ListNode <Bullet> * tempP = bulletList->pHead;
			while (tempP != NULL) {
				Bullet & tempBullet = tempP->object;// need to use reference so that functions apply to bullets in the list and not a copy of bullet
				tempBullet.move(tempBullet.direction.x*BULLETSPEED, tempBullet.direction.y*BULLETSPEED);
				tempBullet.draw(window);
				tempBullet.addFrame();
				tempP = tempP->next;
			}
		}

		if (monsterList->length > 0) {//updates and draws every monster
			ListNode<Monster>* tempForIteration = monsterList->pHead;
			while (tempForIteration != NULL) {
				Monster & tempMonster = tempForIteration->object;
				tempMonster.setDirection(playerPosition);
				tempMonster.move(tempMonster.direction.x, tempMonster.direction.y);
				tempMonster.draw(window);
				tempForIteration = tempForIteration->next;
			}
		}

		//code for final boss
		/*if (andyList->length > 0) {
			ListNode<Andy>* tempAndy = andyList->pHead;
			Andy & tempFinalBoss = tempAndy->object;
			tempFinalBoss.setDirection(playerPosition);
			tempFinalBoss.move(tempFinalBoss.direction.x, tempFinalBoss.direction.y);
			tempFinalBoss.draw(window);
			tempAndy = tempAndy->next;
		}*/

		std::string newString2 = "\0";
		newString2 = "Health :" + std::to_string(int(trunc(mainPlayer.health)));
		text.setString(newString2);
		text.setPosition(40.f, 40.f);
		text.setFillColor(sf::Color::Red);
		std::string newString = "\0";
		newString = "Round: " + std::to_string(round);
		text2.setString(newString);
		text2.setPosition(1600.f, 40.f);
		text2.setFillColor(sf::Color::Red);


		ListNode<Monster> * tempMonsterCollision = monsterList->pHead;
		while (tempMonsterCollision != NULL) {
			FloatRect monsterBoundingBox = tempMonsterCollision->object.sprite.getGlobalBounds();
			if (monsterBoundingBox.intersects(mainPlayer.sprite.getGlobalBounds())) {
				mainPlayer.health -= .5;
			}
			tempMonsterCollision = tempMonsterCollision->next;
		}

		//code for final boss
		/*ListNode<Andy> * finalBossCollision = andyList->pHead;
		while (finalBossCollision != NULL) {
			FloatRect monsterBoundingBox = finalBossCollision->object.sprite.getGlobalBounds();
			if (monsterBoundingBox.intersects(mainPlayer.sprite.getGlobalBounds())) {
				mainPlayer.health -= .5;
			}

			finalBossCollision = finalBossCollision->next;
		}*/

		if (flag == 0) {
			Monster testMonster(monsterSprite, shouldSpawn2, shouldSpawn1);
			monsterList->insertAtFront(testMonster);
			flag++;
		}
		if (monsterList->pHead == NULL) {
			do {
				//BREVIN: ANOTHER ROUND
				round++; //Initialized at zero

						 //BREVIN: STRING AND ADDING THE ROUND


						 //BREVIN: EXPONENTIALLY RAISE ENEMIES
				numberEnemies = round + (0.05 * pow(2, round));
				ceil(numberEnemies);
				flag = 0;
				while (flag < numberEnemies) {
					spawnLocation = rand() % 14 + 1;

					switch (spawnLocation) {
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
					Monster testMonster(monsterSprite, shouldSpawn2, shouldSpawn1);
					monsterList->insertAtFront(testMonster);
					flag++;
				}
				if (round == 5)
				{
					break;
				}
			} while (mainPlayer.health != 0 && monsterList->pHead == NULL);
		}

		if (mainPlayer.health <= 0)
		{
			int toExit = 0;
			while (toExit < 500) {
				window.clear(Color(0, 0, 0));
				std::string newString2 = "GAME OVER";
				text.setPosition(SCREENX / 2 - 20, SCREENY / 2);
				text.setString(newString2);
				window.draw(text);
				window.display();
				++toExit;
			}
			break;
		}
		mainPlayer.draw(window);// draws main player
								//window.draw(text);
								//////These need to be drawn last
		window.draw(crosshairSprite);// draws cross hair
		//menu.draw(window); // for the main menu
						   //window.draw(text);
		window.draw(text);
		window.draw(text2);
		window.display();//displays screen
			
	}
	return 0;
}