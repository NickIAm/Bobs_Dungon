#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
#include "classes.h"
using namespace std;

//These are all the function declerations
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
void generateMonstor(Enemy &);

//global variable :-P Please remove enentually
bool gameIsRunning = true;
int numOfPotions = 2;
bool foughtBob = false;
string monsterNames[10] = {"Wolf","Dragon","Spider","Skeleton","Butterfly","Squirtle","Charmander","Bob's Uncle","SpiderMan","Thor"};
int main()
{
	//Seed the random number generator with the system time
	srand(time(NULL));

	//create the player object
	Player player1;

	//variable to set the players name
	string pName;

	//create a potion and give 2 to start
	Item potion1;
	potion1.setHealing(10);
	potion1.setName("Ultra Healing");
	potion1.setType(1);	
	player1.inventory[0] = potion1;
	player1.inventory[1] = potion1;

	//set the players name
	cout << "This is our game, Prepare to die!!\n";
	cout << "What is you name? \n";
	cin >> pName;
	player1.setName(pName);

	//some lore
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
			break;
	default:
		cout << "Invalid Input.\n";
			break;
	}
}
//print the stats of the player
void printStats(Player &p)
{
	cout << "\n\n" << p.getName() <<  "'s Stats\n";
	cout << "-------------";
	cout << "\nStrength : " << p.getStrength() << endl;
	cout << "Health: " << p.getHealth() << endl;
	cout << "XP " << p.getXp() << endl;
	cout << "Level: " << p.getLevel() << endl;
}
//move the player on the map
void movePlayer(Player &p)
{
	char choice;
	cout << "Which direction to move??\n";
	cout << "w a s d\n";
	cin >> choice;

	switch (choice)
	{
	case 'w':
		p.setPosY(  p.getPosY() - 1);
		printBoard(p.getPosX(), p.getPosY());
		encounter(p);
			break;
	case 's':
		p.setPosY( p.getPosY() + 1);
		printBoard(p.getPosX(), p.getPosY());
		encounter(p);
			break;
	case 'a':
		p.setPosX( p.getPosX() + 1);
		printBoard(p.getPosX(), p.getPosY());
		encounter(p);
			break;
	case 'd' :
		p.setPosX( p.getPosX() - 1);
		printBoard(p.getPosX(), p.getPosY());
		encounter(p);
			break;

	//default to catch invalid input
	default:
		cout << "Enter a direction you loser\n";
			break;
		}

	//Check if the player is on the map after moving
	if (p.getPosX() == 10 || p.getPosX() == -1 || p.getPosY() == 10 || p.getPosY() == -1)
	{
		cout << "You fell off the map,  oh no! you are dead!\n";
		system("pause");
		gameIsRunning = false;
		exit(1);
	}
}
//decide what the player encounters
void encounter(Player &p)
{
	int randNum;
		randNum = (rand() % 3) +1;
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
	}

void enemyEncounter(Player &p)
{
	int choice;
	bool end = false;
	cout << p.getName() << " has encountered an enemy.\n";

	//create an enemy object, This can be generated later
	Enemy one;
	generateMonstor(one);

	cout << "It is a " << one.getName() << "\n";
	cout << "The " << one.getName() << " has the following stats\n" << "Health: " << one.getHP() << endl;
	cout << "Strength: " << one.getStrength() << endl;

	//call the attack enemy function, needs the player and enemy to be passed
	attackEnemy(p,one);
}

void npcEncounter(Player &p)
{
	int randNum;
	char choice;
	cout << p.getName() << " encountered an NPC, his name is Bob\n";
	randNum = (rand() % 2) + 1;

	if (randNum == 1)
	{
		//npc gives some dialog
		cout << "Bob does a silly dance.\n";
	}
	if (randNum == 2)
		//npc gives you an item
	{
		//create an item and assign it stats
		Item bobItem;
		cout << "Bob gives " << p.getName() << " a healing potion.\n";
		bobItem.setName("Healing Potion");
		bobItem.setDamage(0);
		bobItem.setHealing(5);

		//let the player decide to keep the item
		cout << "Do you want this item? y/n \n";
		cin >> choice;
		if (choice == 'y')
		{
			p.inventory[numOfPotions] = bobItem;
			cout << "The item has been added to slot " << numOfPotions << endl;
			numOfPotions++;
		}
		else if (choice == 'n')
		{
			cout << p.getName() << "  deleted the item\n";
		}

	}
}
//the attack sequence for the enemy
void attackEnemy(Player &p, Enemy &one)
	{
		//Store the player decision
		int choice;

		//Variable to exit the loop
		bool endCombat = false;
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
					endCombat = true;
				}
				else if (one.getHP() <= 0)
				{
					cout << "You killed the " << one.getName() << endl;
					p.setXp(p.getXp() + 1);
					cout << "You earned 1 xp!\n";
					endCombat = true;
				}
			}
			if (choice == 2)
			{
				//Run away and exit the loop
				//May want to move the player in a random direction after running, or not let them run sometimes
				endCombat = true;
			}
			if (choice == 3)
			{
				//Show the inventory and let the player use an item
				showInventory(p);
			}	
	} while (endCombat == false);

	if (foughtBob == false)
	{
		evalXP(p);
	}
}
//Show the inventory, and ask if you want to use an item.
void showInventory(Player &p)
	{

		//store the player choice
	char choice;

	//Count for number of inventory items
	int itemCount = 0;
		cout << "Your inventory contains" << endl;
		for (int i = 0; i < 50; i++)
		{
			if (p.inventory[i].getName() == "Empty")
			{
				
			}
			else
			{
				itemCount++;
				cout << "Item " << i  << endl << "Name : " << p.inventory[i].getName() << endl
					<< "Strength Bonus : " << p.inventory[i].getDamage() << endl
					<< "Healing Bonus : "  << p.inventory[i].getHealing() << endl
					<< endl << endl;
			}
		}

		//Check if the inventory is empty
		if (itemCount == 0)
		{
				cout << "Inventory is empty\n";
		}
		else
		{

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

		//This should probably be it's own function
	
	}
//Check the player's xp amount after fighting a monster, and level up if 3 xp is earned
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
//This function determins if the player is ready to fight bob
//the player gets to fight bob if his level is at least 3
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

//basic function to generate a monster. 
void generateMonstor(Enemy &newEnemy)
{
	int name;
	int damage;
	int health;

	name = rand() % 10;
	damage = rand() % 15;
	health = rand() % 8;

	newEnemy.setHP(health);
	newEnemy.setStrength(damage);
	newEnemy.setName(monsterNames[name]);
}