#include "MazeSolvation.h"

// Throw exception if input matrix isn't correct
void check_if_applicable_for_solving(const Matrix &m){
	// check if it is a null matrix
	if(m.size() == 0) throw std::invalid_argument("Invalid argument: matrix shouldn't be null-matrix");

	// check if it is a square matrix
	for(const auto &row : m){
		if(row.size() != m.size()){
			throw  std::invalid_argument("Invalid argument: matrix must be square");
		}
	}

	// check for corect matrix size
	if(m.size() < 2) throw std::invalid_argument("Invalid argument: matrix must be 2x2 or greather");
	if(m.size() > 50) throw std::invalid_argument("Invalid argument: matrix must be 50x50 or lower");


	// check for corect content
	for(const auto &i: m){
		for(const auto &j : i){
			if(j != 0 && j != 1){
				throw std::invalid_argument("Invalid argument: matrix must consist of 0 or 1");
			}
		}
	}
}

// Add points, that we can reach from the current point(row, column)
void update_roads_at(Matrix &current_rm, const Matrix &allowed_paths, const size_t &row,const size_t &column){
	if(row > 0 && allowed_paths.at(row - 1).at(column) == 1){
		current_rm[row - 1][column] = 1;
	}

	if(row < allowed_paths.size()-1 && allowed_paths.at(row + 1).at(column) == 1){
		current_rm[row + 1][column] = 1;
	}

	if(column > 0 && allowed_paths.at(row).at(column - 1) == 1){
		current_rm[row][column - 1] = 1;
	}

	if(column < allowed_paths.size()-1 && allowed_paths.at(row).at(column + 1) == 1){
		current_rm[row][column + 1] = 1;
	}
}

// Add points that we can reach from all points that we have
void update_roads(Matrix &curent_rm, const Matrix &allowed_paths){
	for(size_t i = 0; i < curent_rm.size(); ++i){
		for(size_t j = 0; j < curent_rm.size(); ++j){
			if(curent_rm[i][j] == 1){
				update_roads_at(curent_rm, allowed_paths, i, j);
			}
		}
	}
}

// Find all points that we can reach from point(0, 0). Point(i, j) is accessible if curent_rm[i][j] == 1.
bool solve_maze(const Matrix &allowed_paths){
	// curent_rm is reachability matrix that used for finding if the point(x, y) is rechable from point(0, 0)
	// before_rm is curent_rm on previous iteration and used to check for end of algorithm;
	Matrix curent_rm(allowed_paths.size(), std::vector<size_t>(allowed_paths.size(), 0)),
		   before_rm(allowed_paths.size(), std::vector<size_t>(allowed_paths.size(), 0));

	curent_rm[0][0] = 1;

	while (curent_rm != before_rm){
		before_rm = curent_rm;
		update_roads(curent_rm, allowed_paths);
	}

	return curent_rm.at(allowed_paths.size()-1).at(allowed_paths.size()-1);
}


// Check if Matrix is applicable for algorithm and then execute it
bool has_a_way(const Matrix &allowed_paths){
	try{
		check_if_applicable_for_solving(allowed_paths);
	}catch(const std::invalid_argument &err){
		std::cerr << err.what() <<  std::endl;
		exit(1);
	}


	return solve_maze(allowed_paths);
}
