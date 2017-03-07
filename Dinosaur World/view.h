#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y) /* Функция для считывания координат игрока */
{
	float tempX = x; float tempY = y; /* Считываем координаты игрока */

	view.setCenter(tempX, 336); /* Следим за игроком, передавая его координаты */
}