//#pragma once
//class Enemy
//	: public Entity
//{
//private:
//	float moveTimer;
//public:
//	Enemy(String F, float X, float Y, float W, float H, Level &lvl) : Entity(F, X, Y, W, H)//Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
//	{
//		moveTimer = 0;
//		dx = -0.06;//даем скорость.этот объект всегда двигается
//		obj = lvl.GetObjects("solidForEnemy");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
//	}
//
//	void update(float time)
//	{
//		currentFrame += 0.015 * time; //служит для прохождения по "кадрам"
//		if (currentFrame > 7) currentFrame -= 7; //проходимся по кадрам
//		sprite.setTextureRect(IntRect(81 * int(currentFrame), 0, 81, 76));
//
//		x += dx*time;
//		checkCollision(dx, 0);//обрабатываем столкновение по Х
//
//
//		sprite.setPosition(x, y); //задаем позицию спрайта в место его центра
//
//		if (health <= 0) {
//			dx = 0;
//			currentFrame += 0.00000005 * time; //служит для прохождения по "кадрам"
//			sprite.setTextureRect(IntRect(103 * int(currentFrame), 82, 103, 76));
//
//			if (currentFrame > 6)
//				life = false;
//		}
//	}
//
//	void checkCollision(float Dx, float Dy)//ф-ция взаимодействия с картой
//	{
//		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
//			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
//			{
//				if (obj[i].name == "solidForEnemy")//если встретили препятствие
//				{
//					if (Dx > 0)	{ x = obj[i].rect.left - w;					dx = -0.06; sprite.scale(-1, 1); }
//					if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.06;  sprite.scale(-1, 1); }
//				}
//			}
//	}
//};