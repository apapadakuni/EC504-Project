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
				(*tree).Insert(tree, num);
				cout << "Inserted " << num << endl;
			}

			if (line[0] == 'S'){
				int sucks;
				sucks = (*tree).Successor(tree, num);
				if (sucks == -3000){
					cout << num << " does not have a successor"<<endl;
				}
				else
					cout << "The successor of " << num << " is " << sucks << endl;
			}
			if (line[0]=='D'){
				(*tree).Dlt(tree,num);
				cout << "Deleted " << num << endl;
			}

		}
		myfile.close();
	}
	cout << (*tree).Search(tree, 13) << endl;
	cout << (*tree).Successor(tree, 154) << endl;

	return 0;

}
