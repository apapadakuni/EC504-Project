#ifndef eVEB_H
#define eVEB_H

#include <iostream>
#include <vector>
#include <math.h>



using namespace std;

class eVEB{
public:
	int u;
	int min;
	int max;
	vector <eVEB*> cluster;
	eVEB *summary;



	eVEB(int u2);
	~eVEB();
	void EmptyTreeInsert(eVEB* Tree, int val);
	int Successor(eVEB* tree, int val);
	//int Predecessor(eVEB* tree, int val);
	//void Dlt(eVEB* tree, int val);
	
	int Minimum(eVEB* Tree);
	int Maximum(eVEB* Tree);
	void Insert(eVEB* Tree, int val);
	//bool isMember(eVEB* Tree, int val);



};

#endif