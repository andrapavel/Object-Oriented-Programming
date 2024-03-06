#include <iostream>
#include <vector>
#include "Character.h"


//CHARACTER
Character::Character() //: name{"\0"}, health{0}, level{0}
{
    this->name = '\0';
    this->health = 0;
    this->level = 0;
}

Character::Character(std::string name, int health, int level) 
{
    this->name = name;
    this->health = health;
    this->level = level;
}

int Character::getHealth() const 
{
    return this->health;
}

std::string Character::getName() const 
{
    return this->name;
}

int Character::getLevel() const 
{
    return this->level;
}

void Character::setHealth(int h) 
{
    this->health = h;
}

void Character::setName(std::string n) 
{
    this->name = n;
}

void Character::setLevel(int lvl) 
{
    this->level = lvl;
}


// WIZARD
Wizard::Wizard() 
{
    this->name = '\0';
    this->health = 0;
    this->level = 0;
    this->mana = 0;
    this->spells = std::vector<std::string>();
    this->spellPower = 0;

}
Wizard::Wizard(std::string name, int health, int level, int mana, std::vector<std::string> spells, int spellPower) 
{
    this->name = name;
    this->health = health;
    this->level = level;
    this->mana = mana;
    this->spells = spells;
    this->spellPower = spellPower;

}

void Wizard::setMana(int mana) 
{
    this->mana = mana;
}
void Wizard::setSpells(std::vector<std::string> spells) 
{
    this->spells = spells;
}
void Wizard::setSpellPower(int spellPower) 
{
    this->spellPower = spellPower;
}

int Wizard::getMana() const
{
    return this->mana;
}
int Wizard::getSpellPower() const
{
    return this->spellPower;
}
std::vector<std::string> Wizard::getSpells() 
{
    return this->spells;
}

bool Wizard::castSpell(std::string spell) 
{
    int spellIndex = -1;
    for (int i = 0; i < spells.size(); i++) 
    {
        if (spells[i] == spell) 
        {
            spellIndex = i;
            break;
        }
    }
    if (spellIndex == -1 || mana < 10) 
    {
        return false;
    }
    mana = mana - 10;
    return true;
}


//KNIGHT
Knight::Knight() 
{
    this->name = '\0';
    this->health = 0;
    this->level = 0;
    this->armor = 0;
    this->swordDamage = 0;
}

Knight::Knight(std::string name, int health, int level, int armor, int swordDamage) 
{
    this->name = name;
    this->health = health;
    this->level = level;
    this->armor = armor;
    this->swordDamage = swordDamage;
}

void Knight::setArmor(int armor) 
{
    this->armor = armor;
}

int Knight::getArmor() const
{
    return this->armor;
}

void Knight::setSwordDamage(int swordDamage) 
{
    this->swordDamage = swordDamage;
}

int Knight::getSwordDamage() const
{
    return this->swordDamage;
}

void Knight::takeDamage(int damage) 
{
    armor = armor - damage;
    if (armor < 0) 
    {
        health = 0;
        armor = 0;
    }
}