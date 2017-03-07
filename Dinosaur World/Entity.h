#pragma once
class Entity
{
protected:
	std::vector<Object> obj; /* Вектор объектов карты */
	float x, y, w, h, 
		dx, dy, health, 
		speed, currentFrame;
	bool life, onGround;

	Image image;
	Texture texture;
	Sprite sprite;

public:
	Entity(String File, float X, float Y, float W, float H);
	float getX();
	float getY();
	Sprite getSprite();
	bool getLife();
	void setLife(bool Life);
	float getHealth();
	void setHealth(float Health);
	FloatRect getRect(); /* Функция получения прямоугольника: его координат и размеров */
	virtual void update(float) = 0;
};

Entity::Entity(String File, float X, float Y, float W, float H)
{
	dx = 0; dy = 0; speed = 0; health = 100; life = true, currentFrame = 0; /* Инициализация переменных */
	x = X; y = Y; /* Координата появления спрайта */
	w = W; h = H; /* Высота и ширина */

	image.loadFromFile("Data/Images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

Sprite Entity::getSprite()
{
	return sprite;
}

bool Entity::getLife()
{
	return life;
}

void Entity::setLife(bool Life)
{
	life = Life;
}

float Entity::getHealth()
{
	return health;
}

void Entity::setHealth(float Health)
{
	health = Health;
}

FloatRect Entity::getRect() /* Функция получения прямоугольника: его координат и размеров */
{
	return FloatRect(x, y, w, h); // Эта функция нужна для проверки столкновений 
}