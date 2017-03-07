#pragma once
class Player
	: public Entity
{
private:
	enum { left, right, up, down, stay, jump } status; /* Перечисление состояний игрока */
	enum { leftSide, rightSide } goToSide; /* Перечисление направления игрока */
	bool canShot;

public:
	Player(String, float, float, float, float, Level&);
	void drawAnumation(int, float, int, int, int, int, float);
	void control(float);
	void update(float);
	void checkCollision(float, float);
	int getHealth();
	float getPlayerCoordinateX();
	float getPlayerCoordinateY();
	int getSide();
	bool getCanShot();
};

Player::Player(String F, float X, float Y, float W, float H, Level &lvl) : Entity(F, X, Y, W, H)
{
	status = stay;
	goToSide = rightSide;
	onGround = false;
	speed = 0.45;
	canShot = true;
	obj = lvl.GetAllObjects(); /* Инициализируем. Получаем все объекты для взаимодействия персонажа с картой */
	sprite.setOrigin(48, 0); /* Устанавливаем точку отрисовки */
}

void Player::drawAnumation(int _steps, float _speed, int _x, int _y, int _w, int _h, float _time)
{
	currentFrame += 0.015 * _time;
	if (currentFrame > _steps)
		currentFrame -= _steps;
	sprite.setTextureRect(IntRect(_x * int(currentFrame), _y, _w, _h));
}

void Player::control(float time)
{
	if (life) {
		if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && onGround == true) {
			status = jump; onGround = false;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))) {
			status = left; goToSide = leftSide; canShot = false;
			drawAnumation(8, 0.02, 106, 90, 106, 90, time);
		}
		else if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))) {
			status = right; goToSide = rightSide; canShot = false;
			drawAnumation(8, 0.02, 106, 90, 106, 90, time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space) && canShot) {
			drawAnumation(3, 0.02, 106, 180, 106, 90, time);
		}
		else {
			status = stay; canShot = true;
			drawAnumation(10, 0.02, 106, 0, 106, 90, time);
		}


		if (onGround == false) {
			canShot = false;
			drawAnumation(10, 0.02, 106, 270, 106, 90, time);
		}
	}
}

void Player::update(float time)
{
	control(time);

	switch (status)
	{
	case left:  dx = -speed; dy = 0;      break;
	case right: dx = speed;  dy = 0;      break;
	case up:    dx = 0;      dy = -speed; break;
	case down:  dx = 0;      dy = speed;  break;
	case stay:  dx = 0;      dy = 0;      break;
	case jump:	dy = -13;                 break;
	}

	x += dx*time; /* Ускорение на время получаем смещение координат и как следствие движение */
	checkCollision(dx, 0); /* Обрабатываем столкновение по Х */

	dy += 0.05*time; /* Притяжение к земле */
	y += dy*time;
	checkCollision(0, dy);


	if (goToSide == leftSide) {
		sprite.setScale(-1, 1); /* Отоброжаем спрайт зеркально */
		sprite.setPosition(x + 16, y);
	}
	else {
		sprite.setScale(1, 1);
		sprite.setPosition(x, y);
	}


	if (health <= 0)
		life = false;
}

void Player::checkCollision(float Dx, float Dy) /* Функция взаимодействия с картой */
{
	for (int i = 0; i < obj.size(); i++) /* Проходимся по объектам */
		if (getRect().intersects(obj[i].rect)) /* Проверяем пересечение игрока с объектом */
		{
			if (obj[i].name == "solid")
			{
				if (Dy > 0)	{ y = obj[i].rect.top - h; dy = 0; onGround = true; }
				if (Dy < 0)	{ y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
				if (Dx > 0)	{ x = obj[i].rect.left - w; }
				if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			}
			if (obj[i].name == "water")
			{
				health -= 1;
			}
			if (obj[i].name == "SlopeLeft")
			{
				FloatRect rect = obj[i].rect;

				int y0 = (x + w / 2 - rect.left) * rect.height / rect.width + rect.top - h;

				if (y > y0) {
					if (x + w / 2 > rect.left) {
						y = y0; dy = 0; onGround = true;
					}
				}
			}
			if (obj[i].name == "SlopeRight")
			{
				FloatRect rect = obj[i].rect;

				int y0 = -(x + w / 2 - rect.left) * rect.height / rect.width + rect.top + rect.height - h;

				if (y > y0) {
					if (x + w / 2 < rect.left + rect.width) {
						y = y0; dy = 0; onGround = true;
					}
				}
			}
		}
}

int Player::getHealth()
{
	return health;
}

float Player::getPlayerCoordinateX()
{
	return x;
}

float Player::getPlayerCoordinateY()
{
	return y;
}

int Player::getSide()
{
	return goToSide;
}

bool Player::getCanShot()
{
	return canShot;
}