#include "SimulationGrid.h"
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <fstream>


SimulationGrid::SimulationGrid() 
{
	rows = 0;
	cols = 0;

	// initialize all elements in the grid to nullptr
	for (int r = 0; r < MAX_ROWS; r++)
	{
		for (int c = 0; c < MAX_COLS; c++)
		{
			grid[r][c] = nullptr;
		}
	}
}

SimulationGrid::SimulationGrid(int r, int c)
{
	rows = r;
	cols = c;

	// initialize all elements in the grid to nullptr
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			grid[r][c] = nullptr;
		}
	}
}

SimulationGrid::SimulationGrid(std::string path)
{
	// Open the file for reading
	std::ifstream file(path);

	// Check if the file was successfully opened
	if (!file)
	{
		// If the file could not be opened, print an error message and return
		std::cerr << "Error: Failed to open file \"" << path << "\" for reading." << std::endl;
	}

	SimulationGrid sg;
	file >> sg;

	// Close the file
	file.close();

}

SimulationGrid::SimulationGrid(const SimulationGrid& other)
{
	rows = other.rows;
	cols = other.cols;

	for (int i = 0; i < other.rows; i++)
	{
		for (int j = 0; j < other.cols; j++)
		{
			grid[i][j] = other.grid[i][j];
		}
	}
}

SimulationGrid::~SimulationGrid() 
{
	// Delete all entities in the grid
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (grid[r][c] != nullptr)
			{
				delete grid[r][c];
				grid[r][c] = nullptr;
			}
		}
	}
}

int SimulationGrid::get_rows()
{
	return rows;
}

int SimulationGrid::get_cols()
{
	return cols;
}

Entity* SimulationGrid::get_entity(int row, int col)
{
	if (row >= 0 && row < rows && col >= 0 && col < cols)
	{
		return grid[row][col];
	}
	else
	{
		return nullptr;
	}
}

void SimulationGrid::set_entity(int row, int col, Entity* entity)
{
	if (row >= 0 && row < rows && col >= 0 && col < cols)
	{
		grid[row][col] = entity;
	}
}

std::ostream& operator<<(std::ostream& os, const SimulationGrid& obj)
{
	os << std::setw(3) << obj.rows << " " << obj.cols << std::endl;

	for (int i = 0; i < obj.rows; i++) 
	{
		for (int j = 0; j < obj.cols; j++)
		{
			os << std::setw(3) << obj.grid[i][j]->toString() << " ";
			//std::cout << "AICI" << std::endl;
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, SimulationGrid& obj)
{
	is >> obj.rows >> obj.cols;
	std::string type;

	// Read data from file
	for (int i = 0; i < obj.rows; i++) 
	{
		for (int j = 0; j < obj.cols; j++) 
		{
			is >> type;
			obj.grid[i][j] = obj.createEntity(type);
		}
	}

	return is;
}

SimulationGrid& SimulationGrid::operator=(const SimulationGrid& other)
{
	rows = other.rows;
	cols = other.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (other.grid[i][j])
				grid[i][j] = other.grid[i][j];
			else
				grid[i][j] = nullptr;
		}
	}

	return *this;
}

Entity* SimulationGrid::createEntity(std::string s) const
{
	if (s == "E") 
	{
		return new Empty();
	}
	else if (s == "P") 
	{
		return new Plant();
	}
	else if (s[0] == 'F' && s.length() == 2 && isdigit(s[1])) 
	{
		int age = s[1] - '0';
		return new Fox();
	}
	else if (s[0] == 'G' && s.length() == 2 && isdigit(s[1])) 
	{
		int age = s[1] - '0';
		return new Gopher();
	}
	else 
	{
		return nullptr;
	}
}

void SimulationGrid::randomize()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int r = rand() % 4;
			if (r == 0) 
			{ 
				set_entity(i, j, createEntity("E")); 
			}
			else if (r == 1)
			{
				set_entity(i, j, createEntity("F"));
			}
			else if (r == 2)
			{
				set_entity(i, j, createEntity("G"));
			}
			else if (r == 3)
			{
				set_entity(i, j, createEntity("P"));
			}
		}
	}
}


//----------SIMULATION----------//

void Simulation::promptForGrid(SimulationGrid& g)
{
	int choice;
	std::cout << "How do you want to generate the initial grid?" << std::endl;
	std::cout << "1. Randomly" << std::endl;
	std::cout << "2. From a file" << std::endl;
	std::cin >> choice;

	if (choice == 1)
	{
		std::cout << "Enter the number of rows: ";
		std::cin >> rows;
		std::cout << "Enter the number of columns: ";
		std::cin >> cols;
		even = SimulationGrid(rows, cols);
		even.randomize();
	}
	else if (choice == 2)
	{
		std::string filepath;
		std::cout << "Enter the path to the file: ";
		std::cin >> filepath;

		std::ifstream file(filepath);
		if (!file.is_open())
		{
			std::cout << "Failed to open file " << filepath << std::endl;
			exit(EXIT_FAILURE);
		}

		file >> rows >> cols;
		even = SimulationGrid(rows, cols);

		std::string s;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				file >> s;
				even.set_entity(i, j, g.createEntity(s));
			}
		}

		file.close();
	}
	else
	{
		std::cout << "Invalid choice" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Simulation::Simulation() : rows{ 0 }, cols{ 0 }, numCycles{ 0 }, even{}, odd{}
{

}

void Simulation::run()
{
	SimulationGrid g;
	promptForGrid(g);

	std::cout << "Enter the number of simulation cycles: ";
	std::cin >> numCycles;

	std::cout << "Initial Grid: " << std::endl;
	std::cout << even << std::endl;

	odd = even;

	for (int i = 0; i < numCycles; i++)
	{
		if (i % 2 == 0)
		{
			even = SimulationGrid(rows, cols);
			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < cols; c++)
				{
					even.set_entity(r, c, odd.get_entity(r, c)->next(g));
				}
			}
		}
		else
		{
			odd = SimulationGrid(rows, cols);
			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < cols; c++)
				{
					odd.set_entity(r, c, even.get_entity(r, c)->next(g));
				}
			}
		}
	}

	std::cout << "Final Grid: " << std::endl;
	std::cout << (numCycles % 2 == 0 ? even : odd) << std::endl;
}