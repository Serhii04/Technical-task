#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using Matrix = std::vector<std::vector<size_t>>;

void check_if_applicable_for_solving(const Matrix &m);
void update_roads_at(Matrix &current_rm, const Matrix &allowed_paths, const size_t &row,const size_t &column);
void update_roads(Matrix &curent_rm, const Matrix &allowed_paths);
bool solve_maze(const Matrix &allowed_paths);

// function for use
bool has_a_way(const Matrix &allowed_paths);



