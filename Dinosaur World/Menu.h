#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 4

using namespace sf;

class Menu
{
private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Texture Button, BackgroundMenu;
	Sprite button[MAX_NUMBER_OF_ITEMS], backgroundMenu;

public:
	Menu();
	void loadResources();
	/*void setPositionMenu(float);*/
	void draw(RenderWindow&/*, float*/);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
};

void Menu::loadResources()
{
	font.loadFromFile("Data/Fonts/Jurassic.ttf");
	Button.loadFromFile("Data/Images/Menu/Button.png");
	BackgroundMenu.loadFromFile("Data/Images/Menu/Background Menu.png");
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		button[i].setTexture(Button);
	}
	backgroundMenu.setTexture(BackgroundMenu);
}

Menu::Menu()
{
	loadResources();

	menu[0].setFont(font);
	menu[0].setColor(Color(186, 0, 1));
	menu[0].setString("Play");
	menu[0].setPosition(100, 405);
	button[0].setPosition(30, 400);

	menu[1].setFont(font);
	menu[1].setColor(Color(250, 250, 65));
	menu[1].setString("About");
	menu[1].setPosition(80, 465);
	button[1].setPosition(30, 460);

	menu[2].setFont(font);
	menu[2].setColor(Color(250, 250, 65));
	menu[2].setString("Settings");
	menu[2].setPosition(65, 525);
	button[2].setPosition(30, 520);

	menu[3].setFont(font);
	menu[3].setColor(Color(250, 250, 65));
	menu[3].setString("Exit");
	menu[3].setPosition(100, 585);
	button[3].setPosition(30, 580);

	backgroundMenu.setPosition(0, 0);
	selectedItemIndex = 0;
}

//void Menu::setPositionMenu(float x)
//{
//	menu[0].setPosition(x + 100 - 510, 400);
//	button[0].setPosition(x + 30 - 510, 400);
//	menu[1].setPosition(x + 90 - 510, 460);
//	button[1].setPosition(x + 30 - 510, 460);
//	menu[2].setPosition(x + 80 - 510, 520);
//	button[2].setPosition(x + 30 - 510, 520);
//	menu[3].setPosition(x + 110 - 510, 580);
//	button[3].setPosition(x + 30 - 510, 580);
//	backgroundMenu.setPosition(x - 510, 0);
//}

void Menu::draw(RenderWindow &window/*, float x*/)
{
	//setPositionMenu(x);

	window.draw(backgroundMenu);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(button[i]);
		window.draw(menu[i]);
	}	
}

void Menu::MoveUp()
{
	if (selectedItemIndex-1 >= 0) {
		menu[selectedItemIndex].setColor(Color(250, 250, 65));
		menu[selectedItemIndex].setPosition(menu[selectedItemIndex].getPosition().x, menu[selectedItemIndex].getPosition().y - 2);
		button[selectedItemIndex].setPosition(button[selectedItemIndex].getPosition().x, button[selectedItemIndex].getPosition().y - 2);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(Color(186, 0, 1));
		menu[selectedItemIndex].setPosition(menu[selectedItemIndex].getPosition().x, menu[selectedItemIndex].getPosition().y + 2);
		button[selectedItemIndex].setPosition(button[selectedItemIndex].getPosition().x, button[selectedItemIndex].getPosition().y + 2);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex+1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(Color(250, 250, 65));
		menu[selectedItemIndex].setPosition(menu[selectedItemIndex].getPosition().x, menu[selectedItemIndex].getPosition().y - 2);
		button[selectedItemIndex].setPosition(button[selectedItemIndex].getPosition().x, button[selectedItemIndex].getPosition().y - 2);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(Color(186, 0, 1));
		menu[selectedItemIndex].setPosition(menu[selectedItemIndex].getPosition().x, menu[selectedItemIndex].getPosition().y + 2);
		button[selectedItemIndex].setPosition(button[selectedItemIndex].getPosition().x, button[selectedItemIndex].getPosition().y + 2);
	}
}

int Menu::GetPressedItem() 
{ 
	return selectedItemIndex; 
}