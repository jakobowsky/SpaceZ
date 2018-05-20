#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML\Window.hpp"
#include <math.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Heart.h"
#include "Shield.h"
#include "Star.h"
#include <algorithm>
#include <fstream>

enum GameState
{
	MENU,
	GAME,
	RANKING,
	EXIT
};

GameState GameDisplay(sf::Font font);
GameState MenuDisplay(sf::Font font);
GameState RankingDisplay(sf::Font font, std::ifstream &topPlayersFile);
void CreateTopPlayers(std::ifstream &file);
int MaxValue(int a, int b);

int main()
{
	
	
	GameState state = MENU;
	sf::Font font;
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw ("ERROR WITH FONT");
		state = EXIT;
	}
	//Main menu in game
	while (state != EXIT)
	{
		switch (state)
		{
		case MENU:
		{
			state = MenuDisplay(font);
			continue;
		}
		case GAME:
		{
			state = GameDisplay(font);
			continue;
		}
		case RANKING:
		{
			//first create top players file
			std::ifstream file;
			file.open("RankingNotSorted.txt");
			CreateTopPlayers(file);
			file.close();

			std::ifstream file2;
			file2.open("rankingFile.txt"); // 5 top player on all the time

			state = RankingDisplay(font,file2);

			file2.close();
			continue;
		}
		default:
		{
			state = EXIT;
			continue;
		}
		
		}
	}



	return 0;
}

GameState MenuDisplay(sf::Font font)
{
	GameState stateLocal = MENU;
	//First render window
	sf::Sprite back;
	sf::Texture background;
	background.loadFromFile("Textures/menu.png");
	back.setTexture(background);
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SpaceZ!", sf::Style::Default);
	window.setFramerateLimit(60);
	sf::Text menuText[3];
	std::string texts[3];
	texts[0] = "PLAY";
	texts[1] = "RANKING";
	texts[2] = "EXIT";

	for (int i = 0; i < 3; i++)
	{
		menuText[i].setFont(font);
		menuText[i].setCharacterSize(50);
		menuText[i].setString(texts[i]);
		menuText[i].setPosition(1280 / 2 - menuText[i].getGlobalBounds().width / 2, 250 + i * 150);
	}

	while (stateLocal == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				stateLocal = EXIT;
				return stateLocal;
			}
			else if (menuText[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				stateLocal = GAME;
				return stateLocal;
			}
			else if (menuText[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				stateLocal = RANKING;
				return stateLocal;
			}
			else if (menuText[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				stateLocal = EXIT;
				return stateLocal;
			}

		}


		//UPDATE
		for (int i = 0; i < 3; i++)
		{
			if (menuText[i].getGlobalBounds().contains(mouse))
				menuText[i].setFillColor(sf::Color::Magenta);
			else
				menuText[i].setFillColor(sf::Color::White);

		}

		//DRAW

		window.clear();
		window.draw(back);
		for (int i = 0; i < 3; i++)
			window.draw(menuText[i]);
		window.display();
	}

}

GameState GameDisplay(sf::Font font)
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1280, 720), "WORKS!", sf::Style::Default);
	window.setFramerateLimit(60);
	
	////////////Init map/////////////////
	sf::Sprite map;
	sf::Texture mapTexture;
	mapTexture.loadFromFile("Textures/mapv2.png");
	map.setTexture(mapTexture);
	////////////////////////////////////////
	
	//////Init end screen//////
	sf::Sprite end;
	sf::Texture endTexture;
	endTexture.loadFromFile("Textures/end.png");
	end.setTexture(endTexture);


	///////Init player /////////////
	sf::Texture bulletTextureActual;

	sf::Texture Playerbullet[4];
	Playerbullet[0].loadFromFile("Textures/Pbullet1.png");
	Playerbullet[1].loadFromFile("Textures/Pbullet2.png");
	Playerbullet[2].loadFromFile("Textures/Pbullet3.png");
	Playerbullet[3].loadFromFile("Textures/Pbullet4.png");


	int shootTimePlayer = 30;

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Textures/player.png");
	Player player(&playerTexture);
	player.shape.setOrigin(sf::Vector2f(player.shape.getGlobalBounds().width / 2, player.shape.getGlobalBounds().height / 2));
	player.shape.setPosition(sf::Vector2f(map.getGlobalBounds().width / 2, map.getGlobalBounds().height / 2));
	//Vectors for shooting
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	////////////////////////////////



	////// Init enemies and their bullets///////////
	sf::Texture enemyTexture1[3];
	enemyTexture1[0].loadFromFile("Textures/enemy1v1.png");
	enemyTexture1[1].loadFromFile("Textures/enemy1v2.png");
	enemyTexture1[2].loadFromFile("Textures/enemy1v3.png");
	std::vector <Enemy1*> enemies1;
	int spawnTimer1 = 5;
	sf::Texture enemyBulletTexture1[3];
	enemyBulletTexture1[0].loadFromFile("Textures/EnemyBullet2v1.png");
	enemyBulletTexture1[1].loadFromFile("Textures/EnemyBullet2v2.png");
	enemyBulletTexture1[2].loadFromFile("Textures/EnemyBullet2v3.png");
	
	sf::Texture enemyTexture2[3];
	enemyTexture2[0].loadFromFile("Textures/enemy2v1.png");
	enemyTexture2[1].loadFromFile("Textures/enemy2v2.png");
	enemyTexture2[2].loadFromFile("Textures/enemy2v3.png");
	int spawnTimer2 = 5;
	std::vector <Enemy2*> enemies2;

	sf::Texture enemyTexture3[3];
	enemyTexture3[0].loadFromFile("Textures/enemy3v1.png");
	enemyTexture3[1].loadFromFile("Textures/enemy3v2.png");
	enemyTexture3[2].loadFromFile("Textures/enemy3v3.png");
	int spawnTimer3 = 5;
	std::vector <Enemy3*> enemies3;
	sf::Texture enemyBulletTexture3[3];
	enemyBulletTexture3[0].loadFromFile("Textures/EnemyBullet1v1.png");
	enemyBulletTexture3[1].loadFromFile("Textures/EnemyBullet1v2.png");
	enemyBulletTexture3[2].loadFromFile("Textures/EnemyBullet1v3.png");



	////// Init items //////////////
	//hearts
	sf::Texture heartTexture;
	heartTexture.loadFromFile("Textures/heart.png");
	int spawnTimerHeart = 5;
	std::vector <Heart*> hearts;
	//shields
	sf::Texture shieldTexture;
	shieldTexture.loadFromFile("Textures/shield.png");
	int spawnTimerShield = 5;
	std::vector <Shield*> shields;
	//stars
	sf::Texture starTexture;
	starTexture.loadFromFile("Textures/star.png");
	int spawnTimerStar = 5;
	std::vector <Star*> stars;
	
	/////////////////////////////


	/////// Init UI ///////////
	sf::Text textsUI[4];
	std::string textsS[4];
	textsS[0] = "HP: 10/10";
	textsS[1] = "SHIELD: 0";
	textsS[2] = "STARS: 0";
	textsS[3] = "SCORE: 0";
	for (int i = 0; i < 4; i++)
	{
		textsUI[i].setFont(font);
		textsUI[i].setFillColor(sf::Color::Magenta);
		textsUI[i].setCharacterSize(30);
		textsUI[i].setString(textsS[i]);
		textsUI[i].setPosition(20 , 15 + i * 35);
	}
	
	///////////////////////////

	sf::View mainView;
	mainView.setSize(1280, 720);
	std::string NamePlayer = "";
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
				
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				return MENU;
			}

			///// Input players name, necessary to score
			if (player.HP <= 0)
			{	
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
				{
					NamePlayer = "";
				}
					

				else if (event.type == sf::Event::TextEntered)
					if (event.text.unicode != ' ')
					if (event.text.unicode > 31 && event.text.unicode < 128)
					{
						NamePlayer += static_cast<char>(event.text.unicode);
						
					}
						
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && NamePlayer.size() > 0)
				{
					//also add to file
					std::ofstream out;
					out.open("RankingNotSorted.txt", std::ofstream::app);
					out << NamePlayer + " " + std::to_string(player.score) + "\n";
					window.close();
					return MENU;
				}
			}

		}

		std::cout << NamePlayer << std::endl;
		if (player.HP > 0)
		{
			////////////// U P D A T E ////////////////

			////vectors/////
			//playerCenter = sf::Vector2f(mainView.getSize().x / 2, mainView.getSize().y / 2);
			playerCenter = sf::Vector2f(1280 / 2, 720 / 2);
			mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
			aimDir = mousePosWindow - playerCenter;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

			//////player//////

			//Acceleration
			player.direction = sf::Vector2f(0.f, 0.f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.direction.y = -1.f;
				if (player.currentVelocity.y > -player.maxVelocity)
					player.currentVelocity.y += player.acceleration * player.direction.y;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.direction.y = 1.f;
				if (player.currentVelocity.y < player.maxVelocity)
					player.currentVelocity.y += player.acceleration * player.direction.y;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.direction.x = -1.f;
				if (player.currentVelocity.x > -player.maxVelocity)
					player.currentVelocity.x += player.acceleration * player.direction.x;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.direction.x = 1.f;
				if (player.currentVelocity.x < player.maxVelocity)
					player.currentVelocity.x += player.acceleration * player.direction.x;
			}

			//Drag
			if (player.currentVelocity.x > 0.f)
			{
				player.currentVelocity.x -= player.drag;
				if (player.currentVelocity.x < 0.f)
					player.currentVelocity.x = 0.f;
			}
			else if (player.currentVelocity.x < 0.f)
			{
				player.currentVelocity.x += player.drag;
				if (player.currentVelocity.x > 0.f)
					player.currentVelocity.x = 0.f;
			}
			if (player.currentVelocity.y > 0.f)
			{
				player.currentVelocity.y -= player.drag;
				if (player.currentVelocity.y < 0.f)
					player.currentVelocity.y = 0.f;
			}
			else if (player.currentVelocity.y < 0.f)
			{
				player.currentVelocity.y += player.drag;
				if (player.currentVelocity.y > 0.f)
					player.currentVelocity.y = 0.f;
			}
			//final move
			if (player.shape.getPosition().x <= 0)
				player.shape.setPosition(sf::Vector2f(0,player.shape.getPosition().y));
			if (player.shape.getPosition().y <= 0)
				player.shape.setPosition(sf::Vector2f(player.shape.getPosition().x,0.f));
			if (player.shape.getPosition().x + player.shape.getGlobalBounds().width >= 3000)
				player.shape.setPosition(sf::Vector2f(3000-player.shape.getGlobalBounds().width,player.shape.getPosition().y));
			if (player.shape.getPosition().y + player.shape.getGlobalBounds().height >= 3000)
				player.shape.setPosition(sf::Vector2f( player.shape.getPosition().x, 3000 - player.shape.getGlobalBounds().height));
			
			player.shape.move(player.currentVelocity);



			////////// items ////////////

			//hearts
			if (spawnTimerHeart < 500)
				spawnTimerHeart++;
			else
			{
				if (hearts.size() < 5)
				{
					Heart *heart = new Heart(&heartTexture, player.shape.getPosition());
					hearts.push_back(heart);
					spawnTimerHeart = 0;
				}
			}
			//getting heart
			for (int i = 0; i < hearts.size(); i++)
			{
				if (hearts[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					if (player.HP<player.HPMax)
						player.HP++;
					hearts.erase(hearts.begin() + i);
				}
			}


			//shields
			if (spawnTimerShield < 500)
				spawnTimerShield++;
			else
			{
				if (shields.size() < 5)
				{
					Shield *shield = new Shield(&shieldTexture, player.shape.getPosition());
					shields.push_back(shield);
					spawnTimerShield = 0;
				}
			}
			//getting shield
			for (int i = 0; i < shields.size(); i++)
			{
				if (shields[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					player.shield++;
					shields.erase(shields.begin() + i);
				}
			}

			//stars
			if (spawnTimerStar < 500)
				spawnTimerStar++;
			else
			{
				if (stars.size() < 7)
				{
					Star *star = new Star(&starTexture, player.shape.getPosition());
					stars.push_back(star);
					spawnTimerStar = 0;
				}
			}
			//getting star
			for (int i = 0; i < stars.size(); i++)
			{
				if (stars[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{

					player.weaponPoints++;
					stars.erase(stars.begin() + i);
				}
			}

			//checking stars
			if (player.weaponPoints >= 0)
			{
				shootTimePlayer = 25;
				bulletTextureActual = Playerbullet[0];
			}

			if (player.weaponPoints >= 2)
			{
				shootTimePlayer = 20;
				bulletTextureActual = Playerbullet[1];
			}

			if (player.weaponPoints >= 4)
			{
				shootTimePlayer = 10;
				bulletTextureActual = Playerbullet[2];
			}

			if (player.weaponPoints >= 6)
			{
				shootTimePlayer = 5;
				bulletTextureActual = Playerbullet[3];
			}
			if (player.weaponPoints >= 8)
			{
				shootTimePlayer = 2;
				bulletTextureActual = Playerbullet[rand()%3];
			}





			///////  enemies  ////////
			////enemy 1


			if (spawnTimer1 < MaxValue(25, 250 - int(player.score / 2)))
				spawnTimer1++;
			else
			{
				if (enemies1.size() < 3 + int(player.score / 5))
				{
					Enemy1 *enemy1 = new Enemy1(&enemyTexture1[rand()%3], player.shape.getPosition());
					enemies1.push_back(enemy1);
					spawnTimer1 = 0;
				}
			}

			//checking HP and deleting enemies1
			for (int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i]->HP <= 0)
				{
					player.score += enemies1[i]->HPMax;
					enemies1.erase(enemies1.begin() + i);
				}

			}

			//moving enemies1
			for (int i = 0; i < enemies1.size(); i++)
			{
				enemies1[i]->shape.move(enemies1[i]->MoveEnemy(player.shape.getPosition(), sf::Vector2f(3000, 3000)));
			}

			/////enemy 2
			if (spawnTimer2 < MaxValue(25, 250 - int(player.score / 2)))
				spawnTimer2++;
			else
			{
				if (enemies2.size() < 3 + int(player.score / 5))
				{
					Enemy2 *enemy2 = new Enemy2(&enemyTexture2[rand() % 3], player.shape.getPosition());
					enemies2.push_back(enemy2);
					spawnTimer2 = 0;

				}
			}
			//checking HP and deleting enemies2
			for (int i = 0; i < enemies2.size(); i++)
			{
				if (enemies2[i]->HP <= 0)
				{
					player.score += enemies2[i]->HPMax;
					enemies2.erase(enemies2.begin() + i);
				}

			}

			//moving enemeis2 <- also attack if the condition is true
			for (int i = 0; i < enemies2.size(); i++)
			{
				enemies2[i]->shape.move(enemies2[i]->MoveEnemy(player.shape.getPosition(), sf::Vector2f(3000, 3000)));
			}



			/////enemy3
			if (spawnTimer3 < MaxValue(25, 250 - int(player.score / 2)))
				spawnTimer3++;
			else
			{
				if (enemies3.size() < 3 + int(player.score / 5))
				{
					Enemy3 *enemy3 = new Enemy3(&enemyTexture3[rand() % 3], player.shape.getPosition());
					enemies3.push_back(enemy3);
					spawnTimer3 = 0;

				}
			}
			//checking HP and deleting enemies3
			for (int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i]->HP <= 0)
				{
					player.score += enemies3[i]->HPMax;
					enemies3.erase(enemies3.begin() + i);
				}

			}
			//moving enemies 3
			for (int i = 0; i < enemies3.size(); i++)
			{
				enemies3[i]->shape.move(enemies3[i]->MoveEnemy(player.shape.getPosition(), sf::Vector2f(3000, 3000)));
			}


			/////player shooting/////
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (player.shootTimer >= shootTimePlayer)
				{

					player.bullets.push_back(Bullet1(&bulletTextureActual, sf::Vector2f(player.shape.getPosition()), aimDirNorm, 15.f));
					player.shootTimer = 0;
				}
				else
					player.shootTimer++;


			}

			for (int i = 0; i <player.bullets.size(); i++)
			{
				player.bullets[i].shape.rotate(35.f);
				player.bullets[i].shape.move(player.bullets[i].currVelocity);
				bool cond = true;
				//Out of bounds
				if (player.bullets[i].shape.getPosition().x < 0 || player.bullets[i].shape.getPosition().x > 3000
					|| player.bullets[i].shape.getPosition().y < 0 || player.bullets[i].shape.getPosition().y > 3000)
					player.bullets.erase(player.bullets.begin() + i);
				else //Collision with enemy
				{
					for (int k = 0; k < enemies1.size(); k++)
					{

						if (player.bullets[i].shape.getGlobalBounds().intersects(enemies1[k]->shape.getGlobalBounds()))
						{
							player.bullets.erase(player.bullets.begin() + i);
							enemies1[k]->HP--;
							cond = false;
							break;
						}
					}
					if (cond)
					{
						for (int k = 0; k < enemies2.size(); k++)
						{

							if (player.bullets[i].shape.getGlobalBounds().intersects(enemies2[k]->shape.getGlobalBounds()))
							{
								player.bullets.erase(player.bullets.begin() + i);
								enemies2[k]->HP--;
								cond = false;
								break;
							}
						}
					}
					if (cond)
					{
						for (int k = 0; k < enemies3.size(); k++)
						{

							if (player.bullets[i].shape.getGlobalBounds().intersects(enemies3[k]->shape.getGlobalBounds()))
							{
								player.bullets.erase(player.bullets.begin() + i);
								enemies3[k]->HP--;
								cond = false;
								break;
							}
						}
					}



				}
			}



			////enemies shooting/////

			//enemy 1
			//create bullets
			for (int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i]->ifShoot(player.shape.getPosition()) && enemies1[i]->shootTimer >= 150)
				{
					enemies1[i]->shootTimer = 0;
					//std::cout << "shoot!" << std::endl;
					aimDir = player.shape.getPosition() - enemies1[i]->shape.getPosition();
					aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
					enemies1[i]->bullets.push_back(Bullet1(&enemyBulletTexture1[rand()%3], sf::Vector2f(enemies1[i]->shape.getPosition()), aimDirNorm, 7.f));

				}
				else
					enemies1[i]->shootTimer++;
			}
			//movement bullets
			for (int i = 0; i < enemies1.size(); i++)
			{

				for (int j = 0; j < enemies1[i]->bullets.size(); j++)
				{
					
					enemies1[i]->bullets[j].shape.rotate(5.f);
					enemies1[i]->bullets[j].shape.move(enemies1[i]->bullets[j].currVelocity);

					//Out of bounds
					if (enemies1[i]->bullets[j].shape.getPosition().x < 0 || enemies1[i]->bullets[j].shape.getPosition().x > 3000
						|| enemies1[i]->bullets[j].shape.getPosition().y < 0 || enemies1[i]->bullets[j].shape.getPosition().y > 3000)
					{
						enemies1[i]->bullets.erase(enemies1[i]->bullets.begin() + j);
						break;
					}

					else //Collision with  player
					{
						if (enemies1[i]->bullets[j].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
						{
							if (player.shield > 0)
								player.shield--;
							else
								player.HP--;

							enemies1[i]->bullets.erase(enemies1[i]->bullets.begin() + j);
							break;

						}
					}


				}

			}
			//enemy2 <--- this enemy is not shooting


			//enemy3
			for (int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i]->ifShoot(player.shape.getPosition()) && enemies3[i]->shootTimer >= 250)
				{
					enemies3[i]->shootTimer = 0;
					aimDir = player.shape.getPosition() - enemies3[i]->shape.getPosition();
					aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
					//Upgrade this later
					enemies3[i]->bullets.push_back(Bullet1(&enemyBulletTexture3[rand() % 3], sf::Vector2f(enemies3[i]->shape.getPosition()), aimDirNorm, 7.f));
					enemies3[i]->bullets.push_back(Bullet1(&enemyBulletTexture3[rand() % 3], sf::Vector2f(enemies3[i]->shape.getPosition()), sf::Vector2f(aimDirNorm.x + 0.5f, aimDirNorm.y + 0.5f), 7.f));
					enemies3[i]->bullets.push_back(Bullet1(&enemyBulletTexture3[rand() % 3], sf::Vector2f(enemies3[i]->shape.getPosition()), sf::Vector2f(aimDirNorm.x - 0.5f, aimDirNorm.y - 0.5f), 7.f));

				}
				else
					enemies3[i]->shootTimer++;
			}
			//movement of bullets
			for (int i = 0; i < enemies3.size(); i++)
			{

				for (int j = 0; j < enemies3[i]->bullets.size(); j++)
				{
					enemies3[i]->bullets[j].shape.rotate(5.f);
					enemies3[i]->bullets[j].shape.move(enemies3[i]->bullets[j].currVelocity);

					//Out of bounds
					if (enemies3[i]->bullets[j].shape.getPosition().x < 0 || enemies3[i]->bullets[j].shape.getPosition().x > 3000
						|| enemies3[i]->bullets[j].shape.getPosition().y < 0 || enemies3[i]->bullets[j].shape.getPosition().y > 3000)
					{
						enemies3[i]->bullets.erase(enemies3[i]->bullets.begin() + j);
						break;
					}

					else //Collision with  player
					{
						if (enemies3[i]->bullets[j].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
						{

							if (player.shield > 0)
								player.shield--;
							else
								player.HP--;


							enemies3[i]->bullets.erase(enemies3[i]->bullets.begin() + j);
							break;

						}
					}


				}

			}

			//// general collisions player with enemies ////
			for (int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					if (player.shield > 0)
						player.shield--;
					else
						player.HP--;
					enemies1.erase(enemies1.begin() + i);
					break;
				}
			}

			for (int i = 0; i < enemies2.size(); i++)
			{
				if (enemies2[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					if (player.shield > 0)
						player.shield--;
					else
						player.HP--;
					enemies2.erase(enemies2.begin() + i);
					break;
				}
			}

			for (int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i]->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					if (player.shield > 0)
						player.shield--;
					else
						player.HP--;
					enemies3.erase(enemies3.begin() + i);
					break;
				}
			}


			//UPDATE TEXTS
			textsUI[0].setString("HP: " + std::to_string(player.HP) + "/" + std::to_string(player.HPMax));
			textsUI[1].setString("SHIELD: " + std::to_string(player.shield));
			textsUI[2].setString("STARS: " + std::to_string(player.weaponPoints));
			textsUI[3].setString("SCORE: " + std::to_string(player.score));



			//////////////D R A W//////////////
			mainView.setCenter(player.shape.getPosition());
			window.clear();
			window.setView(mainView);
			window.draw(map);
			window.draw(player.shape);


			//enemies
			for (int i = 0; i < enemies1.size(); i++)
				window.draw(enemies1[i]->shape);

			for (int i = 0; i < enemies2.size(); i++)
				window.draw(enemies2[i]->shape);
			for (int i = 0; i < enemies3.size(); i++)
				window.draw(enemies3[i]->shape);

			//items
			for (int i = 0; i < hearts.size(); i++)
				window.draw(hearts[i]->shape);

			for (int i = 0; i < shields.size(); i++)
				window.draw(shields[i]->shape);

			for (int i = 0; i < stars.size(); i++)
				window.draw(stars[i]->shape);

			//bullets player
			for (int i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].shape);
			}
			//buellets enemies
			for (int i = 0; i < enemies1.size(); i++)
			{
				for (int j = 0; j < enemies1[i]->bullets.size(); j++)
				{

					window.draw(enemies1[i]->bullets[j].shape);
				}
			}

			for (int i = 0; i < enemies3.size(); i++)
			{
				for (int j = 0; j < enemies3[i]->bullets.size(); j++)
				{

					window.draw(enemies3[i]->bullets[j].shape);
				}
			}


			//UI
			window.setView(window.getDefaultView());
			for (int i = 0; i < 4; i++)
				window.draw(textsUI[i]);

			std::cout << "HP: " << player.HP << std::endl;
			std::cout << "Score: " << player.score << std::endl;
			std::cout << "Shield: " << player.shield << std::endl;
			std::cout << "Stars: " << player.weaponPoints << std::endl;


			window.display();
		}
		else
		{
			window.clear();
			
			window.draw(end);
			
			sf::Text NamePlayerText;
			NamePlayerText.setString(NamePlayer);
			NamePlayerText.setFont(font);
			NamePlayerText.setCharacterSize(100);
			NamePlayerText.setFillColor(sf::Color::Black);
			NamePlayerText.setPosition(window.getSize().x / 2 - NamePlayerText.getGlobalBounds().width / 2, 450);
			sf::Text finish;
			finish.setString("GAME OVER!");
			finish.setFont(font);
			finish.setCharacterSize(100);
			finish.setFillColor(sf::Color::Black);
			finish.setPosition(window.getSize().x / 2 - finish.getGlobalBounds().width / 2, 100);
			textsUI[3].setCharacterSize(120);
			textsUI[3].setPosition(window.getSize().x / 2 - textsUI[3].getGlobalBounds().width /2, 250);
			window.draw(textsUI[3]);
			window.draw(finish);
			window.draw(NamePlayerText);
			window.display();
		}
		

	}


}

GameState RankingDisplay(sf::Font font,std::ifstream &topPlayersFile)
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "WORKS!", sf::Style::Default);
	window.setFramerateLimit(60);

	sf::Sprite back;
	sf::Texture background;
	background.loadFromFile("Textures/score.png");
	back.setTexture(background);

	////Init text////
	sf::Text topPlayersText[5];
	std::string topPlayers[5];
	for (int i = 0; i < 5; i++)
		topPlayers[i] = "";
	std::string input1, input2; // those are for reading the file
	int it = 0;
	while (topPlayersFile >> input1 >> input2)
	{
		topPlayers[it] = std::to_string(it + 1) + ". " + input1 + "   score: " + input2;
		it++;
	}

	for (int i = 0; i < 5; i++)
	{	
		topPlayersText[i].setFont(font);
		topPlayersText[i].setFillColor(sf::Color::White);
		topPlayersText[i].setCharacterSize(60);
		topPlayersText[i].setString(topPlayers[i]);
		topPlayersText[i].setPosition(1280 / 2 - topPlayersText[i].getGlobalBounds().width / 2, 150 + i * 90);
	}

	/////////////////

	////Init background///



	///////////////////


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				return MENU;
			}
		}

		window.clear();
		window.draw(back);
		for (int i = 0; i < 5; i++)
			window.draw(topPlayersText[i]);

		window.display();
	}

	
}

void CreateTopPlayers(std::ifstream &file) 
{
	struct Pair
	{
		std::string nameOfPlayer;
		int scoreOfPlayer;
	};


	std::vector <Pair> players;
	Pair actPlayer;
	while (file >> actPlayer.nameOfPlayer >> actPlayer.scoreOfPlayer)
	{
		players.push_back(actPlayer);
	}

	std::ofstream rankingFile;
	rankingFile.open("rankingFile.txt");

	sort(players.begin(), players.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs.scoreOfPlayer > rhs.scoreOfPlayer;
	});

	for (int i = 0; i < players.size(); i++)
	{
		rankingFile << players[i].nameOfPlayer + " " + std::to_string(players[i].scoreOfPlayer) + "\n";
		if (i == 4)
			break;
	}
		
	rankingFile.close();


}

int MaxValue(int a, int b)
{
	if (a > b) return a;
	return b;
}
