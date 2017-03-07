#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>

#include "level.h"

#include "Menu.h"
#include "view.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
//#include "Enemy.h"


using namespace sf;
using namespace std;

Level lvl;
Texture Background;
Music Dinosaur_World_Theme;
SoundBuffer Game_over;

void loadResources()
{
	lvl.LoadFromFile("Map.tmx"); 
	Background.loadFromFile("Data/Images/background.png");
	Dinosaur_World_Theme.openFromFile("Data/Audio/Dinosaur_World_Theme.ogg");
	Game_over.loadFromFile("Data/Audio/Game_over.ogg");
}

void main()
{
	RenderWindow window(VideoMode(1020, 672), "Dinosaur World");
	window.setPosition(Vector2i(160, 10));
	Menu menu;
	view.reset(FloatRect(0, 0, 1020, 672)); /* Размер "вида" камеры при создании объекта вида камеры */

	loadResources();
	Sprite background(Background);
	Sound game_over(Game_over);

	bool playLoseMusic = false, gameStart = false;

	Clock clock; /* Переменная времени, т.е. привязка ко времени, а не загруженности/мощности процессора */

	Object player = lvl.GetObject("Player");
	Player girl("Player.png", player.rect.left, player.rect.top, player.rect.width, player.rect.height, lvl);
	
	//std::list<Enemy> rat;//создаю список, сюда буду кидать объекты врагов
	//std::list<Enemy>::iterator it_rat;//итератор чтобы проходить по эл-там списка
	//std::vector<Object> r = lvl.GetObjects("EasyEnemy");//все объекты врага на tmx карте хранятся в этом векторе
	//for (int i = 0; i < r.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
	//	rat.push_back(Enemy("Enemy.png", r[i].rect.left, r[i].rect.top, r[i].rect.width, r[i].rect.height, lvl));//и закидываем в список всех наших врагов с карты

	list<Bullet*> bullet;//список пуль
	list<Bullet*>::iterator it_bullet;


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close(); 
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					/*gameStart = false; */window.close();
				if (event.key.code == Keyboard::Space && girl.getCanShot())
					bullet.push_back(new Bullet("bullet.png", girl.getX() + 20, girl.getY() + 41, 5, 5, lvl, girl.getSide()));//если выстрелили, то появляется пуля. enum передаем как int 
				break;
			case Event::KeyReleased:
				if (event.key.code == Keyboard::Up && gameStart == false)
					menu.MoveUp();
				if (event.key.code == Keyboard::Down && gameStart == false)
					menu.MoveDown();
				if (event.key.code == Keyboard::Return && gameStart == false)
					switch (menu.GetPressedItem())
					{
					case 0:
						gameStart = true;
						std::cout << "Play button has been pressed" << std::endl;
						break;
					case 1:
						std::cout << "About the program button has been pressed" << std::endl;
						break;
					case 2:
						std::cout << "Settings button has been pressed" << std::endl;
						break;
					case 3:
						window.close();
						break;
					}
				break;
			}
		}


		Time time = clock.getElapsedTime(); /* Задать прошедшее время */
		clock.restart().asMilliseconds(); /* Перезагружает время в микросекундах */
		

		if (girl.getLife())
		{
			if (Dinosaur_World_Theme.getStatus() == false && gameStart) /* Играем фоновую музыку */
				Dinosaur_World_Theme.play();

			girl.update(time.asMilliseconds()); /* Управление персонажем */
			getPlayerCoordinateForView(girl.getPlayerCoordinateX(),
				girl.getPlayerCoordinateY()); /* Передаем координаты игрока в функцию управления камерой */

			//for (it_rat = rat.begin(); it_rat != rat.end();)//говорим что проходимся от начала до конца
			//{
			//	Entity *r = *it_rat;//для удобства, чтобы не писать (*it_rat)->
			//	r->update(time.asMilliseconds());//вызываем ф-цию update для всех врагов

			//	if (r->getLife() == false)//если этот объект мертв	
			//	{
			//		it_rat = rat.erase(it_rat); delete r;//то удаляем его
			//	}
			//	else it_rat++;//и идем итератором к след объекту. так делаем со всеми объектами списка
			//}

			for (it_bullet = bullet.begin(); it_bullet != bullet.end();) {//говорим что проходимся от начала до конца
				Entity *b = *it_bullet;//для удобства, чтобы не писать (*it_bullet)->
				b->update(time.asMilliseconds());

				if (b->getLife() == false) { //если этот объект мертв	
					it_bullet = bullet.erase(it_bullet); delete b;//то удаляем его
				}
				else 
					it_bullet++;//и идем итератором к след объекту. так делаем со всеми объектами списка
			}
		}
		else
		{
			Dinosaur_World_Theme.stop(); /* Останавливаем фоновую музыку */
			if (game_over.getStatus() == false && playLoseMusic == false)
			{
				game_over.play();
				playLoseMusic = true;
			}
		}

	
		/*-------------------- Отрисовка --------------------*/
		window.clear();
		if (!gameStart) {
			menu.draw(window/*, girl.getPlayerCoordinateX()*/);
			window.display();
		}
		if (gameStart) {
			background.setPosition(window.getView().getCenter().x - 510, 0);
			window.draw(background);
			lvl.Draw(window);
			for (it_bullet = bullet.begin(); it_bullet != bullet.end(); it_bullet++)
				window.draw((*it_bullet)->getSprite()); //рисуем entities объекты (сейчас это только враги)
			window.draw(girl.getSprite());
			//for (it_rat = rat.begin(); it_rat != rat.end(); it_rat++)
			//	window.draw((*it_rat)->getSprite()); //рисуем entities объекты (сейчас это только враги)
			window.setView(view);
			window.display();
		}
		/*---------------------------------------------------*/
	}
}