#pragma once
#include "EntityType.h"
#include "SimulationGrid.h"

class Entity
{
public:
	// TODO make pure abstract method

	Entity();
	Entity(int r, int c);

	virtual int get_row();
	virtual int get_col();

	void set_row(int r);
	void set_col(int c);


	virtual std::string toString() const = 0;

	virtual EntityType what() = 0;

	virtual Entity* next(const SimulationGrid& g) = 0;

	void demographics(unsigned int population[], const SimulationGrid& g);

protected:
	 int row;
	 int col;
	
};


//--------------- SUBCLASSES ---------------//

class Empty : public Entity 
{
public:

	Empty();

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Entity& obj);
};

class Plant : public Entity 
{
public:

	Plant();

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Plant& obj);
};


class Animal : public Entity 
{
protected:
	int age;

public:

	int get_age();
	void set_age(int a);

};

class Fox : public Animal
{
public:

	Fox();

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Fox& obj);
};

class Gopher : public Animal
{
public:

	Gopher();
	
	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Gopher& obj);
};