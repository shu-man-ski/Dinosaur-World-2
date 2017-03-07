#pragma once
class Bullet
	: public Entity
{
private:
	int direction;

public:
	Bullet(String F, float X, float Y, float W, float H, Level &lvl, int dir);
	void update(float);
	void checkCollision();
};

Bullet::Bullet(String F, float X, float Y, float W, float H, Level &lvl, int dir) : Entity(F, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	direction = dir;
	speed = 1;
}

void Bullet::update(float time)
{
	switch (direction)
	{
	case 0: dx = -speed; dy = 0; break;
	case 1: dx = speed; dy = 0;  break;
	}

	x += dx*time;
	y += dy*time;

	checkCollision();

	sprite.setPosition(x, y);

	if (health <= 0)
		life = false;
}

void Bullet::checkCollision()
{
	if (x <= 0)
		x = 1; /* Задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки */
	if (y <= 0)
		y = 1;

	for (int i = 0; i < obj.size(); i++) /* Проход по объектам solid */
		if (getRect().intersects(obj[i].rect))
			life = false;
}