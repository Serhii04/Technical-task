#include "TestMazeSolvation.h"


void test_check_if_applicable_for_solving(){
	Matrix m;

	// matrix cant be null-matrix
	m = {};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix shouldn't be null-matrix"));
	}

	// matrix must be square
	m = {{1,1,1},
		 {1,1,1}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must be square"));
	}

	m = {{1,1,1},
		 {1,1,1},
		 {1,1,1},
		 {1,1,1}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must be square"));
	}

	m = {{1,1,1},
		 {1,1},
		 {1,1,1},
		 {1,1,1}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must be square"));
	}

	// matrix lower than can
	m = {{1}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must be 2x2 or greather"));
	}

	// matrix is higer than can

	m = std::vector<std::vector<size_t>>(51, std::vector<size_t>(51, 0));
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must be 50x50 or lower"));
	}

	// min size of matrix
	m = {{1,1},
		 {1,1}};
	check_if_applicable_for_solving(m);

	// max size of matrix
	m = std::vector<std::vector<size_t>>(50, std::vector<size_t>(50, 0));
	check_if_applicable_for_solving(m);

	// some matrix
	m = {{0,0,1,0},
		 {1,1,1,1},
		 {0,0,1,1},
		 {1,1,1,0}};
	check_if_applicable_for_solving(m);

	// incorect consistant
	m = {{0,0,1,0},
		 {1,1,1,2},
		 {0,1,0,1},
		 {1,1,1,0}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must consist of 0 or 1"));
	}

	m = {{199,0,1,0},
		 {1,1,1,0},
		 {0,1,0,1},
		 {1,1,1,0}};
	try{
		check_if_applicable_for_solving(m);
	}catch(std::invalid_argument &err){
		assert(err.what() == std::string("Invalid argument: matrix must consist of 0 or 1"));
	}

	std::cout << "Test: check_if_applicable_for_has_a_way OK" << std::endl;
}

void test_update_roads_at(){
	Matrix current_rm, allowed_roads, answer;

	current_rm = {{0,0,0},
				  {0,0,0},
				  {0,0,0}};
	allowed_roads = {{1,0,1},
					 {1,1,0},
					 {1,1,0}};

	// add one road
	answer = {{0,0,0},
	   		  {1,0,0},
			  {0,0,0}};
	update_roads_at(current_rm, allowed_roads, 0, 0);
	assert(current_rm == answer);


	/// add thre roads
	answer = {{1,0,0},
	   		  {1,1,0},
			  {1,0,0}};
	update_roads_at(current_rm, allowed_roads, 1, 0);
	assert(current_rm == answer);


	// don't add road
	update_roads_at(current_rm, allowed_roads, 0, 0);
	update_roads_at(current_rm, allowed_roads, 0, 0);
	update_roads_at(current_rm, allowed_roads, 0, 0);
	update_roads_at(current_rm, allowed_roads, 0, 0);
	assert(current_rm == answer);

	std::cout << "Test: update_roads_at OK" << std::endl;
}

void test_update_roads(){
	Matrix current_rm, allowed_roads, answer;

	current_rm = {{1,0,0,0},
				  {0,0,0,0},
				  {0,0,1,0},
				  {0,0,0,0}};
	allowed_roads = {{1,0,0,1},
					 {1,1,0,1},
			   		 {0,1,0,1},
					 {1,0,1,1}};

	// testing if works
	answer = {{1,0,0,0},
	   		  {1,1,0,1},
	   		  {0,1,1,1},
			  {0,0,1,1}};
	update_roads(current_rm, allowed_roads);
	assert(current_rm == answer);

	answer = {{1,0,0,1},
		      {1,1,0,1},
		   	  {0,1,1,1},
			  {0,0,1,1}};
	update_roads(current_rm, allowed_roads);
	assert(current_rm == answer);


	// testing if it changes something after algorithm end
	update_roads(current_rm, allowed_roads);
	update_roads(current_rm, allowed_roads);
	update_roads(current_rm, allowed_roads);
	update_roads(current_rm, allowed_roads);
	assert(current_rm == answer);

	std::cout << "Test: update_roads OK" << std::endl;
}

void test_solve_maze(){
	Matrix allowed_roads;

	// Test some excamples
	allowed_roads = {{1,0,1,0,1},
				     {1,0,1,0,1},
				     {1,1,1,0,1},
				     {0,0,1,0,0},
					 {0,0,1,1,1}};
	assert(solve_maze(allowed_roads));

	allowed_roads = {{1,0,1,0,1},
					 {1,0,1,0,1},
					 {1,1,1,0,1},
					 {0,0,1,0,0},
					 {0,0,1,1,0}};
	assert(!solve_maze(allowed_roads));

	allowed_roads = {{1,0,1,1,1,0,0},
					 {1,0,1,0,1,0,1},
					 {1,1,1,0,1,0,0},
					 {0,0,0,0,1,0,0},
					 {1,1,1,1,1,0,0},
					 {1,0,0,0,0,0,0},
					 {1,1,1,1,1,1,1}};
	assert(solve_maze(allowed_roads));

	allowed_roads = {{1,0,1,1,1,0,0},
					 {1,0,1,0,1,0,1},
					 {1,1,1,0,1,0,1},
					 {0,0,1,0,1,0,0},
					 {0,0,1,0,1,1,0},
					 {0,1,1,0,0,0,0},
					 {0,0,0,1,1,1,1}};
	assert(!solve_maze(allowed_roads));

	allowed_roads = {{1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1}};
	assert(solve_maze(allowed_roads));

	std::cout << "Test: solve_maze OK" << std::endl;
}


void test_all(){
	test_check_if_applicable_for_solving();
	test_update_roads_at();
	test_update_roads();
	test_solve_maze();

	std::cout << "Test: all OK" << std::endl;
}
