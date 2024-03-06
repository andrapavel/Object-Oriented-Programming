#include "Entity.h"
#include "EntityType.h"
#include <algorithm> // for std::fill
#include <sstream>
#include <iostream>
#include <iomanip>


//----------ENTITY----------//

Entity::Entity() : row{ 0 }, col{ 0 }
{

}

Entity::Entity(int r, int c)
{
	this->row = r;
	this->col = c;
}

int Entity::get_row()
{
	return this->row;
}

int Entity::get_col()
{
	return this->col;
}

void Entity::set_row(int r)
{
	row = r;
}

void Entity::set_col(int c)
{
	col = c;
}

void Entity::demographics(unsigned int population[], const SimulationGrid& g) 
{
	// set the population array to 0; we have 4 types of elements : Empty, Fox, Gopher, Plant
	std::fill(population, population + 4, 0);

	// offsets for the neighbors' coordinates
	int dx[]{ 0, 0, 1, 1, 1, -1, -1, -1 };
	int dy[]{ 1, -1, -1, 0, 1,  -1, 0, 1 };

	// row : row+1, row-1
	// col: col+0, col+0
	unsigned int numNeigh{ sizeof(dy) / sizeof(dy[0]) };

	for (unsigned int i{ 0 }; i < numNeigh; ++i)
	{
		int r{ row + dy[i] };
		int c{ col + dx[i] };

		//checks thet r and c are inside bounderies
		for (int i = 0; i < numNeigh; ++i)
		{
			int r{ row + dy[i] };
			int c{ col + dx[i] };
			// check that r and c are within bounds
			if (r >= 0 && r < g.rows && c >= 0 && c < g.cols)
			{
				EntityType et = g.grid[r][c]->what();
				// convert the enum class to int, you can use to_underlying
				population[to_underlying(et)]++;
			}
		}

	}
}


//----------EMPTY----------//

Empty::Empty()
{
	row = 0;
	col = 0;
}

EntityType Empty::what()
{
	return EntityType::EMPTY;
}

Entity* Empty::next(const SimulationGrid& g)
{
	unsigned int population[4];
	demographics(population, g);

	if (population[2] > 1)
	{
		//GOPHER
		return g.createEntity("G");
	}
	else if (population[1] > 1)
	{
		//FOX
		return g.createEntity("F");
	}
	else if (population[3] >= 1)
	{
		//PLANT
		return g.createEntity("P");
	}
	else
	{
		//EMPTY
		return g.createEntity("E");
	}

}

std::string Empty::toString() const
{
	return "E";
}

std::ostream& operator<<(std::ostream& os, const Entity& obj)
{
	os << obj.toString();
	return os;
}


//----------PLANT----------//

Plant::Plant()
{
	row = 0;
	col = 0;
}

EntityType Plant::what()
{
	return EntityType::PLANT;
}

Entity* Plant::next(const SimulationGrid& g)
{
	unsigned int population[4];
	demographics(population, g);

	if (2 * population[2] == population[3])
	{
		//EMPTY
		return g.createEntity("E");
	}
	else if (population[2] >= 3)
	{
		//GOPHER
		return g.createEntity("G");
	}
	else
	{
		//PLANT
		return g.createEntity("P");
	}
}

std::string Plant::toString() const
{
	return "P";
}

std::ostream& operator<<(std::ostream& os, const Plant& obj)
{
	os << obj.toString();
	return os;
}


//----------ANIMAL----------//

int Animal::get_age()
{ 
	return age; 
}

void Animal::set_age(int a) 
{ 
	age = a; 
}


//----------FOX----------//

Fox::Fox()
{
	row = 0;
	col = 0;
	set_age(0);
}

EntityType Fox::what()
{
	return EntityType::FOX;
}

Entity* Fox::next(const SimulationGrid& g)
{
	unsigned int population[4];
	demographics(population, g);

	if (get_age() >= 5 || population[2] == 0)
	{
		//EMPTY
		return g.createEntity("E");
	}
	else
	{
		//FOX
		return g.createEntity("F");
		int age = get_age();
		set_age(age + 1);
	}
}

std::string Fox::toString() const
{
	return "F";
}

std::ostream& operator<<(std::ostream& os, const Fox& obj)
{
	os << obj.toString();
	return os;
}


//----------GOPHER----------//

Gopher::Gopher()
{
	row = 0;
	col = 0;
	set_age(0);
}

EntityType Gopher::what()
{
	return EntityType::GOPHER;
}

Entity* Gopher::next(const SimulationGrid& g)
{
	unsigned int population[4];
	demographics(population, g);

	if (get_age() == 4 || population[3] == 0)
	{
		//EMPTY
		return g.createEntity("E");
	}
	else if (population[1] >= population[2])
	{
		//FOX
		return g.createEntity("F");
	}
	else
	{
		//GOPHER
		return g.createEntity("G");
		int age = get_age();
		set_age(age + 1);
	}
}

std::string Gopher::toString() const
{
	return "G";
}

std::ostream& operator<<(std::ostream& os, const Gopher& obj)
{
	os << obj.toString();
	return os;
}