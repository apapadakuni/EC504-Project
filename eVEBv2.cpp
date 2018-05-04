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

int index(int high, int low,  int u){
	return high*(int)sqrt(u)+low;
}



eVEB::eVEB(int u2){ //CREATE-NEW-RS-VEB-TREE
	u = u2;
	
	// for (int i=0; i<sqrt(u); i++)
	// {
	// 	cluster.push_back(nullptr); //cluster will serve as a dynamic hash table
	// }
	min = NIL;
	max = NIL;
	// summary = nullptr;


	
}


eVEB:: ~eVEB(){
	if (summary != nullptr) delete summary;

		for (int i=0; i< sqrt(u); i++){
			if (cluster[i] != nullptr) delete cluster[i];
		}
	
	//delete [] cluster;
}

void eVEB:: EmptyTreeInsert(eVEB* Tree, int val, int count){
	(*Tree).min = val;
	(*Tree).max = val;
	(*Tree).countmin = count; //input val into both min and max
	(*Tree).countmax = count; //so countmin = countmax = 1;
	(*Tree).min = val;
	(*Tree).max = val;
	if((*Tree).u > 2){
            (*Tree).summary = NULL;
            (*Tree).cluster = (eVEB**)calloc(sqrt(u),sizeof(eVEB*));
    }
    else{
       (*Tree).summary = NULL;
        (*Tree).cluster = NULL;
    }

}



int eVEB::Minimum(eVEB* Tree){
	return (*Tree).min;
}


int eVEB::Maximum(eVEB* Tree){
	return (*Tree).max;
}





void eVEB::Insert(eVEB* Tree, int val, int count){
	if ((*Tree).min == NIL){
		// Tree = new eVEB(u);
		EmptyTreeInsert(Tree, val, count);
		
		//cout << "Inserted " << val<<endl;
			

	}
	else if((*Tree).min == val){
		(*Tree).countmin+=count;
		if ((*Tree).max == val){
			(*Tree).countmax = (*Tree).countmin;
		}
	}
	else if ((*Tree).max == val){
		(*Tree).countmax+=count;
	}

	// if (val == (*Tree).min){
	// 	(*Tree).countmin++;
	// }
	// if (val == (*Tree).max){
	// 	(*Tree).countmax++;
	// }

	else{
		if (val < (*Tree).min){ //Next 20 lines of code account for duplicates
			if ((*Tree).min == (*Tree).max){
				(*Tree).min = val;
				(*Tree).countmin = count;
				return;
			}
			int temp = (*Tree).min;
			(*Tree).min = val;
			val = temp;
			int tempcount = (*Tree).countmin;
			(*Tree).countmin = count;
			count = tempcount;

		}
		else if(val > (*Tree).max){
		//	cout << "sup" << endl;
			int temp = (*Tree).max;
			(*Tree).max = val;
			val = temp;

			int tempcount = (*Tree).countmax;
			(*Tree).countmax = count;
			count = tempcount;
			//cout << "here" << endl;
			//cout << (*Tree).min << endl;
			//cout << val << endl;
			if ((*Tree).min == val){
				return ;
			}
		}
		//cout << "val after swap: " << val << endl;
		if ((*Tree).u > 2){
			
			// if((*Tree).summary == nullptr){
			// 	//cout << "nullptr summary begin " << val<< endl;
			// 	(*Tree).summary = new eVEB(sqrt((*Tree).u)); 
			// 	//cout << "nullptr summary end "  << val << endl;
			// }
			if ((*Tree).cluster[high(val, (*Tree).u)] == nullptr){
				if ((*Tree).summary == nullptr)
					(*Tree).summary = new eVEB(sqrt((*Tree).u));

				(*(*Tree).summary).Insert((*Tree).summary, high(val,(*Tree).u),1);
				//(*Tree).cluster[high(val, (*Tree).u)] = new eVEB(sqrt((*Tree).u));
			}
			if ((*Tree).cluster[high(val,(*Tree).u)] == nullptr)
				(*Tree).cluster[high(val,(*Tree).u)] = new eVEB(sqrt((*Tree).u));
			//cout << "About to inser to cluster " << high(val,(*Tree).u) << "the val " << low(val, (*Tree).u) << endl;
			(*(*Tree).cluster[high(val,(*Tree).u)]).Insert((*Tree).cluster[high(val,(*Tree).u)], low(val, (*Tree).u), count); 

		}
		
	}
	//cout << "Just inserted " << val << endl;

}





// bool isMember(eVEB* Tree, int val){





// }


int eVEB::Successor(eVEB* Tree, int val){
	if ((*Tree).u == 2){
		if (val == 0 && (*Tree).max == 1){
			return 1;
		}
		else return NIL;
	}
	else if ((*Tree).min != NIL && val <(*Tree).min){
		return (*Tree).min;
	}
	else {
		if ((*Tree).cluster[high(val,(*Tree).u)] == nullptr){
			//insert into V.summary with key high(x) what is returned byCREATE-NEW−RD−vEB−TREE(sqrt(V.u))
			(*Tree).cluster[high(val, (*Tree).u)] = new eVEB(sqrt((*Tree).u));
		}
		int max_low = ((*Tree).cluster[high(val, (*Tree).u)])->max;
		if (max_low != NIL and low(val, (*Tree).u) < max_low){
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





eVEB* eVEB::Dlt(eVEB *Tree, int val){
    if(Tree->min == Tree->max){
        if(Tree->countmin > 1){
            Tree->countmin--;
            Tree->countmax--;
        }
        else{
            free(Tree);
            return nullptr;
        }
    }
    else if(Tree->u == 2){
        if(val == 0){
            if(!--Tree->countmin){
                Tree->min = 1;
                Tree->countmin = Tree->countmax;
            }
        }
        else{
            if(!--Tree->countmax){
                Tree->max = 0;
                Tree->countmax = Tree->countmin;
            }
        }
    }
    else{
       
        if(val == Tree->min){
   
            if(!--Tree->countmin){
                if(Tree->summary){
                    int first_cluster = Minimum(Tree->summary);
                    int new_min = Minimum(Tree->cluster[first_cluster]);
                    
                    Tree->min = first_cluster * (int)sqrt(Tree->u) + new_min;
                    
                    Tree->countmin = Tree->cluster[first_cluster]->countmin;
                    (Tree->cluster[first_cluster])->countmin = 1;
                    if((Tree->cluster[first_cluster])->min == (Tree->cluster[first_cluster])->max)
                        (Tree->cluster[first_cluster])->countmax = 1;
                    Tree->cluster[first_cluster] = Dlt(Tree->cluster[first_cluster], new_min);
                    if(Tree->cluster[first_cluster] == nullptr)
                        Tree->summary = Dlt(Tree->summary, first_cluster);
                }
                else{
                    Tree->min = Tree->max;
                    Tree->countmin = Tree->countmax;
                }
            }
        }
        else if(val == Tree->max){
            if(!--Tree->countmax){
                if(Tree->summary){
                    int last_cluster = Maximum(Tree->summary);
                    int new_max = Maximum(Tree->cluster[last_cluster]);
                    Tree->max = last_cluster * (int)sqrt(Tree->u) + new_max;
                    Tree->countmax = Tree->cluster[last_cluster]->countmax;
                    (Tree->cluster[last_cluster])->countmax = 1;
                    if((Tree->cluster[last_cluster])->min == (Tree->cluster[last_cluster])->max)
                        (Tree->cluster[last_cluster])->countmin = 1;
                    Tree->cluster[last_cluster] = Dlt(Tree->cluster[last_cluster], new_max);
                    if(Tree->cluster[last_cluster] == nullptr)
                        Tree->summary = Dlt(Tree->summary, last_cluster);
                }
            }
        }
        else{
            Tree->cluster[high(val, Tree->u)] = Dlt(Tree->cluster[high(val, Tree->u)], low(val, Tree->u));
            if(Tree->cluster[high(val, Tree->u)] == nullptr)
                Tree->summary = Dlt(Tree->summary, high(val, Tree->u));
        }
    }
    return Tree;
}



int eVEB::Search(eVEB* Tree, int val){ //will return the quanitity of that number

	if (Tree==nullptr)
	{	
	//	cout << "yep" << endl;
		return 0;
	}
	else if((*Tree).min == val){
		return (*Tree).countmin;
	}
	else if ((*Tree).max == val){
		return (*Tree).countmax;
	}
	else {

		if ((*Tree).cluster != nullptr){ //meaning our cluster has something
		//	cout << "About to search cluster  " << high(val,(*Tree).u) << " with the value of " << low(val,(*Tree).u) << endl;
			return Search((*Tree).cluster[high(val,(*Tree).u)], low(val,(*Tree).u));
		}
		else
			return 0;
	}
}



int eVEB::ExtractMin(eVEB* Tree){
	int val = min;
	//cout << "val is "<<val;
	Dlt(Tree, min);
	return val;
}

void eVEB::Update(eVEB* Tree, int existingval, int newval){
	Dlt(Tree, existingval);
	Insert(Tree, newval,1);
}

bool eVEB::isEmpty(void){
	if (this == nullptr){
		return true;
	}
	else return false;
}






