#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include "eVEB.h"



using namespace std;


int main(){
	string line;
	eVEB* tree = new eVEB(256);
	

	ifstream myfile ("test.txt");
	if (myfile.is_open()){
		while (getline(myfile, line)){
			int num;
			string nums;
			for (int i=0; i<line.size()-2; i++){
				nums[i] = line[i+2];
			}
			num = stoi(nums, nullptr, 10);

			if (line[0]=='I'){
				cout << num << endl;
				(*tree).Insert(tree, num);

			}

			if (line[0] == 'S'){
				int sucks;
				sucks = (*tree).Successor(tree, num);
				cout << "The successor of " << num << " is " << sucks << endl;
			}

		}
		myfile.close();
	}

	return 0;

}
