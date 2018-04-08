#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "eVEB.h"

#define NIL -3000

using namespace std;

int high(int x, int u){
	int num = x/sqrt(u);
	return num;
}

int low(int x, int u){
	int sq = sqrt(u);
	int res = x%sq;
	return res;
}



eVEB::eVEB(int u2){ //CREATE-NEW-RS-VEB-TREE
	u = u2;
	
	for (int i=0; i<sqrt(u); i++)
	{
		cluster.push_back(nullptr); //cluster will serve as a dynamic hash table
	}
	min = NIL;
	max = NIL;
	summary = nullptr;


	
}


eVEB:: ~eVEB(){
	if (summary != nullptr) delete summary;

		for (int i=0; i< sqrt(u); i++)
			if (cluster[i]) delete cluster[i];
	
	//delete [] cluster;
}

void eVEB:: EmptyTreeInsert(eVEB* Tree, int val){
	(*Tree).min = val;
	(*Tree).max = val;
}



int eVEB::Minimum(eVEB* Tree){
	return (*Tree).min;
}


int eVEB::Maximum(eVEB* Tree){
	return (*Tree).max;
}





void eVEB::Insert(eVEB* Tree, int val){
	if ((*Tree).min == NIL){
		EmptyTreeInsert(Tree, val);
		//cout << "Break 1" << endl;
	}
	else{
		if (val < (*Tree).min){ //swapping Minimum with Current value
			int temp = val;
			val = (*Tree).min;
			(*Tree).min = temp;
		}
		//cout << "val after swap: " << val << endl;
		if ((*Tree).u > 2){
			
			if((*Tree).summary == nullptr){
				//cout << "nullptr summary begin " << val<< endl;
				(*Tree).summary = new eVEB(sqrt((*Tree).u)); 
				//cout << "nullptr summary end "  << val << endl;
			}
			if ((*Tree).cluster[high(val,(*Tree).u)] == nullptr){
			//	(*Tree).summary = new eVEB()//confused here: insert into V.summary with key high(x) what is returned by CREATE−NEW−RD−vEB−TREE(sqrt(V.u))
				//cout << "nllptr cluster begin " << val << endl;
				(*Tree).cluster[high(val, (*Tree).u)] = new eVEB(sqrt((*Tree).u));
			//cout << "nllptr cluster end " << val << endl;
			}
			if ((*Tree).cluster[high(val,(*Tree).u)]->min == NIL){
			//	cout << "nil min begin " << val << endl;
			//	cout << high(val,(*Tree).u) << endl;
				Insert((*Tree).summary, high(val,(*Tree).u));

				EmptyTreeInsert((*Tree).cluster[high(val,(*Tree).u)], low(val,(*Tree).u));
				//cout << "nil min end " << val << endl;
			}
			else{
				//cout << "else " << val << endl;
				Insert((*Tree).cluster[high(val,(*Tree).u)], low(val,(*Tree).u));
			}

		}
		if (val > (*Tree).max){
			(*Tree).max = val;
		}
	}

}





// bool isMember(eVEB* Tree, int val){





// }


int eVEB::Successor(eVEB* Tree, int val){
	if ((*Tree).u == 2){
		if (val == 0 and (*Tree).max == 1){
			return 1;
		}
		else return NIL;
	}
	else if ((*Tree).min != NIL and val <(*Tree).min){
		return (*Tree).min;
	}
	else {
		if ((*Tree).cluster[high(val,(*Tree).u)] == nullptr){
			//insert into V.summary with key high(x) what is returned byCREATE-NEW−RD−vEB−TREE(sqrt(V.u))
			(*Tree).cluster[high(val, (*Tree).u)] = new eVEB(sqrt((*Tree).u));
		}
		int max_low = ((*Tree).cluster[high(val, (*Tree).u)])->max;
		if (max_low != NIL and low(val, (*Tree).u)){
			return high(val, (*Tree).u)*sqrt((*Tree).u) + Successor((*Tree).cluster[high(val,(*Tree).u)],low(val,(*Tree).u));
		}
		else{
			if ((*Tree).summary == nullptr){
				(*Tree).summary = new eVEB(sqrt((*Tree).u)+1);
			}
			int succ_cluster = Successor((*Tree).summary, high(val,(*Tree).u));
			if (succ_cluster == NIL){
				return NIL;
			}
			else {
				return succ_cluster*sqrt((*Tree).u) + ((*Tree).cluster[succ_cluster])->min;
			}
		}
	}

}







