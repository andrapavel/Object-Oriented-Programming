#pragma once

#include<string>
#include <vector>


class Character 
{

public:
    Character();
    Character(std::string name, int health, int level);

    //SETTERS
    int getHealth() const;
    int getLevel() const;
    std::string getName() const;

    //GETTERS
    void setHealth(int h);
    void setName(std::string n);
    void setLevel(int lvl);


protected:

    int health;
    int level;
    std::string name;

    //friend class CharacterTest;
};

//--------------------------- WIZARD

class Wizard : public Character 
{
public:
    Wizard();
    Wizard(std::string name, int health, int level, int mana, std::vector<std::string> spells, int spellPower);

    bool castSpell(std::string spell);

    //GETTERS
    void setMana(int mana);
    void setSpells(std::vector<std::string> spells);
    void setSpellPower(int spellPower);

    //SETTERS
    int getMana() const;
    int getSpellPower() const;
    std::vector<std::string> getSpells();

protected:
    int mana; //mana unchanged if the wizard does not know the requested spell
    std::vector<std::string>spells; //each requests 10 mana
    int spellPower;

    //friend class WizardTest;

};

//--------------------------- KNIGHT

class Knight : public Character 
{
public:
    Knight();
    Knight(std::string name, int health, int level, int armor, int swordDamage);
    void takeDamage(int damage); //reduces armor by the specified amount

    //GETTERS
    void setArmor(int armor);
    void setSwordDamage(int swordDamage);

    //SETTERS
    int getSwordDamage() const;
    int getArmor() const;

protected:
    int armor; // between [0,1]
    int swordDamage;

    //friend class KnightTest;

};