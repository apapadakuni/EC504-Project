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
	int countmin;
	int countmax;
	eVEB** cluster;
	eVEB *summary;



	eVEB(int u2);
	~eVEB();
	void EmptyTreeInsert(eVEB* Tree, int val, int count);
	int Successor(eVEB* tree, int val);
	eVEB* Dlt(eVEB* tree, int val);
	int Minimum(eVEB* Tree);
	int Maximum(eVEB* Tree);
	void Insert(eVEB* Tree, int val, int count);
	int Search(eVEB* Tree, int val);
	void Update(eVEB* Tree,  int existingval, int newval);
	int ExtractMin(eVEB* Tree);
	bool isEmpty(void);
};

#endif