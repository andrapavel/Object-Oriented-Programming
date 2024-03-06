#include <cassert>
#include <iostream>

#include "Entity.h"
#include "SimulationGrid.h"

class TestEmpty
{
public:
	static void runTests()
	{
		test_default_constructor_empty();
		test_what_empty();
		test_next_empty();
		test_toString_empty();

		std::cout << "All EMPTY tests passed!";
	}
	
private:
	static void test_default_constructor_empty()
	{
		Empty e;
		assert(e.get_row() == 0);
		assert(e.get_col() == 0);
	}

	static void test_what_empty()
	{
		Empty e;
		EntityType et = e.what();
		assert(et == EntityType::EMPTY);
	}

	static void test_next_empty()
	{
		SimulationGrid g;
		Empty e;
		Entity* nextEntity;
		assert(nextEntity != nullptr);
	}

	static void test_toString_empty()
	{
		Empty e;
		std::string str = e.toString();
		assert(str == "E");
	}

};

class TestPlant
{
	static void runTests()
	{
		test_default_constructor_plant();
		test_what_plant();
		test_next_plant();
		test_toString_plant();

		std::cout << "All PLANT tests passed!";
	}

private:
	static void test_default_constructor_plant()
	{
		Plant p;
		assert(p.get_row() == 0);
		assert(p.get_col() == 0);
	}

	static void test_what_plant()
	{
		Plant p;
		EntityType et = p.what();
		assert(et == EntityType::PLANT);
	}

	static void test_next_plant()
	{
		SimulationGrid g;
		Plant p;
		Entity* nextEntity;
		assert(nextEntity != nullptr);
	}

	static void test_toString_plant()
	{
		Plant p;
		std::string str = p.toString();
		assert(str == "P");
	}

};

class TestGopher
{
	static void runTests()
	{
		test_default_constructor_gopher();
		test_what_gopher();
		test_next_gopher();
		test_toString_gopher();

		std::cout << "All GOPHER tests passed!";
	}

private:
	static void test_default_constructor_gopher()
	{
		Gopher g;
		assert(g.get_row() == 0);
		assert(g.get_col() == 0);
	}

	static void test_what_gopher()
	{
		Gopher g;
		EntityType et = g.what();
		assert(et == EntityType::GOPHER);
	}

	static void test_next_gopher()
	{
		SimulationGrid sg;
		Gopher g;
		Entity* nextEntity;
		assert(nextEntity != nullptr);
	}

	static void test_toString_gopher()
	{
		Gopher g;
		std::string str = g.toString();
		assert(str == "G");
	}
};

class TestFox
{
	static void runTests()
	{
		test_default_constructor_fox();
		test_what_fox();
		test_next_fox();
		test_toString_fox();

		std::cout << "All FOX tests passed!";
	}

private:
	static void test_default_constructor_fox()
	{
		Fox f;
		assert(f.get_row() == 0);
		assert(f.get_col() == 0);
	}

	static void test_what_fox()
	{
		Fox f;
		EntityType et = f.what();
		assert(et == EntityType::FOX);
	}

	static void test_next_fox()
	{
		SimulationGrid g;
		Fox f;
		Entity* nextEntity;
		assert(nextEntity != nullptr);
	}

	static void test_toString_fox()
	{
		Fox f;
		std::string str = f.toString();
		assert(str == "F");
	}
};

class TestSimulationGrid
{
	static void runTests()
	{
		test_default_constructor();
		test_parameterized_constructor();
		test_path_constructor();
		test_copy_constructor();
		test_destructor();
		test_get_entity();
		test_create_entity();
		test_randomize();
		test_set_entity();
		test_operator_assign();


		std::cout << "All tests passed!";
	}

private:
	static void test_default_constructor()
	{
		SimulationGrid g;
		assert(g.get_rows() == 0);
		assert(g.get_cols() == 0);
	}

	static void test_parameterized_constructor()
	{
		// Create a 3x3 grid
		SimulationGrid grid(3, 3);

		// Verify that all elements are initialized to nullptr
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				assert(grid.grid[r][c] == nullptr);
			}
		}
	}

	static void test_path_constructor()
	{
		
	}

	static void test_copy_constructor()
	{
		
	}

	static void test_destructor()
	{

	}

	static void test_get_entity()
	{

	}

	static void test_create_entity()
	{

	}

	static void test_randomize()
	{

	}

	static void test_set_entity()
	{
		Entity* e;
		SimulationGrid g("Read.txt");
		e = g.createEntity("G");
		g.set_entity(0, 0, e);
		//assert(g.get_entity(0, 0)->toString() = e->toString());
	}

	static void test_operator_assign()
	{

	}

};