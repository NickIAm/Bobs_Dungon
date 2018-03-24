#include <iostream>
#include <time.h>
#include "classes.h"
#include <cstdlib>

using namespace std;


void printStats(Player &);
void userChoice(Player &);
void printBoard(int, int);
void movePlayer(Player &);
void encounter(Player &);
void npcEncounter(Player &p);
void enemyEncounter(Player &);
void attackEnemy(Player &, Enemy &);
void showInventory(Player &);
void fightBob(Player &);
void evalXP(Player &);

//global variable :-P
bool gameIsRunning = true;
int numOfPotions = 2;
bool foughtBob = false;

int main()
{
	srand(time(NULL));
	Player player1;
	string pName;
	Item potion1;
	potion1.setHealing(10);
	potion1.setName("Ultra Healing");
	potion1.setType(1);
	
	player1.inventory[0] = potion1;
	player1.inventory[1] = potion1;

	cout << "This is our game, Prepare to die!!\n";
	cout << "What is you name? \n";

	

	cin >> pName;
		player1.setName(pName);

		cout << endl << endl << player1.getName() << " has entered the mystical land of Bob.\n"
			<< "Bob is a benevolent ruler, but he has a dark secret.\n"
			<< "Explore the land, gain xp to level up. Once you reach level 3 \n"
			<< "The final boss will find you.\n";


	while (gameIsRunning)
	{
		printBoard(player1.getPosX(), player1.getPosY());
		userChoice(player1);

		//system("pause");
	}
	
	return 0;
}

void printBoard(int userX, int userY)
{
	
	for (int y = 0; y < 10; y++)
	{
		for (int i = 0; i < 60; i++)
		{
			cout << "-";
		}
		cout << endl;
		for (int x = 0; x < 10; x++)
		{
			if (x == userX && y == userY)
			{
				cout << "  x  |";
			}
			else
			{
				cout << "     |";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < 60; i++)
	{
		cout << "-";
	}
	cout << endl;
}

void userChoice(Player &player1)
{
	int userInput;

	cout << "Choose an option:\n";
	cout << "1. View Stats.\n";
	cout << "2. View Inventory.\n";
	cout << "3. Move.\n";
	cin >> userInput;

	switch (userInput)
	{
	case 1:
		printStats(player1);
		break;
	case 2:
		showInventory(player1);
		break;
	case 3:
		movePlayer(player1);
		encounter(player1);
		break;
	default:
		cout << "Invalid Input.\n";

		break;
	}
}

void printStats(Player &p)
{
	cout << "\n\n" << p.getName() <<  "'s Stats\n";
	cout << "-------------";
	cout << "\nStrength : " << p.getStrength() << endl;
	cout << "Health: " << p.getHealth() << endl;
	cout << "XP " << p.getXp() << endl;
	cout << "Level: " << p.getLevel() << endl;
}

void movePlayer(Player &p)
{
	char choice;
	cout << "Which direction to move??\n";
	cout << "n e s w\n";
	cin >> choice;

	switch (choice)
	{
	case 'n':
		p.setPosY(  p.getPosY() - 1);
			break;
	case 's':
		p.setPosY( p.getPosY() + 1);
			break;
	case 'e':
		p.setPosX( p.getPosX() + 1);
			break;
	case 'w' :
		p.setPosX( p.getPosX() - 1);
			break;
	default:
		cout << "Enter a direction you loser\n";
		break;
		}
	if (p.getPosX() == 10 || p.getPosX() == -1 || p.getPosY() == 10 || p.getPosY() == -1)
	{
		cout << "You fell off the map,  oh no! you are dead!\n";
		system("pause");
		gameIsRunning = false;
		exit(1);
	}

}
void encounter(Player &p)
{
	int randNum;
		randNum = rand() % 4;
		if (randNum == 1)
		{
			npcEncounter(p);
		}
		else if (randNum == 2)
		{
			enemyEncounter(p);
		}
		else if (randNum == 3)
		{
			enemyEncounter(p);
		}
		else
		{
			cout << "Nothing Happened!! YAY!\n\a";
		}
}

void enemyEncounter(Player &p)
{
	int choice;
	bool end = false;
	cout << p.getName() << " has encountered an enemy.\n";
	Enemy one;
	cout << "It is a " << one.getName() << "\n";
	cout << "What will "<< p.getName() << "  do?, 1) Attack 2) Run\n";

	cin >> choice;
	switch (choice)
	{
	case 1:
		attackEnemy(p,one);
		break;
	case 2:
		cout << p.getName() << " ran away!\n";
		break;

		}
	}

void npcEncounter(Player &p)
{
	int randNum = 0;
	char choice;
	cout << p.getName() << " encountered an NPC, his name is Bob\n";
	randNum = (rand() % 2) + 1;

	if (randNum == 1)
	{
		cout << "Bob does a silly dance.\n";
	}
	if (randNum == 2)
	{
		Item bobItem;
		cout << "Bob gives " << p.getName() << " a healing potion.\n";
		bobItem.setName("Healing Potion");
		bobItem.setDamage(0);
		bobItem.setHealing(5);
		cout << "Do you want this item? y/n \n";
		
		cin >> choice;
		if (choice == 'y'	)
		{

			p.inventory[numOfPotions] = bobItem;
			cout << "The item has been added to slot 1\n";
			numOfPotions++;
		}
		else if (choice == 'n')
		{
			cout << p.getName() << "  deleted the item\n";
		}

	}
}

void attackEnemy(Player &p, Enemy &one)
	{
		int choice;
		bool end = false;

		do
		{
		//This is for the player to choose to attack or run
			cout << "Attack, Run, View Inventory: [1] [2] [3]";
			cin >> choice;
			if (choice == 1)
			{
				//set the enemy and player health according to the attack
				one.setHP(one.getHP() - p.getStrength());
				cout << "You hit for " << p.getStrength() << " damage.\n";
				cout << one.getName() << " has  " << one.getHP() << " HP left\n";
				p.setHealth(p.getHealth() - one.getStrength());
				cout << "The " << one.getName() << " hit you for " << one.getStrength() << endl;
				cout << "You have " << p.getHealth() << " health left! Oh NO!!:\n";

				//check if the player or enemy is dead and exit loop
				if (p.getHealth() <= 0)

				{
					cout << "Oh dear you are dead!" << endl;
					end = true;
				}
				else if (one.getHP() <= 0)
				{
					cout << "You killed the " << one.getName() << endl;
					p.setXp(p.getXp() + 1);
					cout << "You earned 1 xp!\n";
					end = true;
				}
			}
			if (choice == 2)
			{
				end = true;
			}
			if (choice == 3)
			{
				showInventory(p);
			}
		
	
	} while (end == false);
	if (foughtBob == false)
	{
		evalXP(p);
	}

}

void showInventory(Player &p)
	{
	char choice;
		cout << "Your inventory contains" << endl;
		for (int i = 0; i < 50; i++)
		{
			if (p.inventory[i].getName() == "Empty")
			{

			}
			else
			{
				cout << "Item " << i  << endl << "Name : " << p.inventory[i].getName() << endl
					<< "Strength Bonus : " << p.inventory[i].getDamage() << endl
					<< "Healing Bonus : "  << p.inventory[i].getHealing() << endl
					<< endl << endl;

			}
		}
		cout << "Do you want to use an item? y/n \n";
		cin >> choice;
		if (choice == 'y')	
		{
			int userin;
			cout << "What item do you want to use? Enter an item number \n";
			cin >> userin;
			Item inHand = p.inventory[userin];
			p.setHealth(p.getHealth() + inHand.healing);
			cout << p.getName() << " has been healed to " << p.getHealth() << endl;
			p.inventory[userin].name = "Empty";
			p.inventory[userin].healing = 0;
		}
	}

void evalXP(Player &p)
{
	if (p.getXp() >= 3)
	{
		cout << p.getName() << " leveled up! WOOOOO!!!!";
		p.setLevel(p.getLevel() + 1);
		p.setXp(0);
		p.setHealth(p.getHealth() + 5);
		p.setStrength(p.getStrength() + 5);
	}
	if (p.getLevel() == 3)
	{
		cout << "You get to fight the BOB" << endl;
		fightBob(p);
	}
}
void fightBob(Player &p)
{
	Enemy bob;
	bob.setHP(20);
	bob.setStrength(5);
	bob.setName("Bob");
	foughtBob = true;
	attackEnemy(p, bob);
	cout << "You win\n";
	system("pause");
	exit(1);

}