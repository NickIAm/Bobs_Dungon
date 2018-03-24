#pragma once
#include <string>
using namespace std;

class Item
{
public:

	string name;
	//type 1 is a potion, 2 is a weapon
	int type;
	int healing;
	int damage;

	Item();

	void setHealing(int heal)
	{
		healing = heal;
	}
	void setDamage(int dam)
	{
		damage = dam;
	}
	void setType(int typ)
	{
		type = typ;
	}
	int getHealing()
	{
		return healing;
	}
	int getDamage()
	{
		return damage;
	}
	int getType()
	{
		return type;
	}
	string getName()
	{
		return name;
	}
	void setName(string namee)
	{
		name = namee;
	}
	
};
Item::Item()
{
	name = "Empty";
	damage = NULL;
	type = NULL;
	healing = NULL;
}


class Player
{
public:
	Player();
	~Player();

	void setHealth(int SH)
	{
		health = SH;
	}
	int getHealth()
	{
		return health;
	}
	void setStrength(int SS)
	{
		strength = SS;
	}
	int getStrength()
	{
		return strength;
	}
	void setXp(int XP)
	{
		xp = XP;
	}
	int getXp()
	{
		return xp;
	}
	void setPosX(int px)
	{
		posX = px;
	}
	int getPosX()
	{
		return posX;
	}
	void setPosY(int py)
	{
		posY = py;
	}
	int getPosY()
	{
		return posY;
	}
	void setInventory(Item in, int x)
	{
		inventory[x] = in;
	}
	Item getInventoryName(int x)
	{
		return inventory[x];
	}
	void setName(string namee)
	{
		name = namee;
	}
	string getName()
	{
		return name;
	}
	void setLevel(int lev)
	{
		level = lev;
	}
	int getLevel()
	{
		return level;
	}

	Item inventory[50];
private:
	int health;
	int strength;
	int xp;
	int posX;
	int posY;
	int level;
	string name;
	
};

Player::Player()
{
	health = 15;
	strength = 1;
	xp = 0;
	posX = 4;
	posY = 4;
	for (int i = 0; i < 50; i++)
	{
		Item nullItem;
		inventory[i] = nullItem;
	}
	level = 1;
}

Player::~Player()
{
}



class Enemy
{
private:
	string name = "wolf";
	int strength = 1;
	int hp = 6;
public:

string getName()
{
	return  name;
}
int getStrength()
{
	return strength;
}
int getHP()
{
	return hp;
}

void setStrength(int st)
{
	strength = st;
}

void setHP(int h)
{
	hp =h;
}
void setName(string namee)
{
	name = namee;
}

};
