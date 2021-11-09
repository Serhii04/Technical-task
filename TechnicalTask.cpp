#include <iostream>
#include "TestMazeSolvation.h"

using namespace std;


int main() {

	Matrix allowed_roads = {{1,0,1,1,1,0,0},
							{1,0,1,0,1,0,1},
							{1,1,1,0,1,1,1},
							{0,0,1,0,1,0,1},
							{0,0,1,0,1,1,1},
							{0,1,1,0,1,0,1},
							{1,0,1,1,1,0,1}};
		if(has_a_way(allowed_roads)){
			cout << "There is a way" << endl;
		}else{
			cout << "There is no way" << endl;
		}

	return 0;
}
