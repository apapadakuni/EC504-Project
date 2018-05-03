//
//  main.cpp
//  Dijkstra
//
//  Created by Tali Moreshet
//  Copyright © 2017 Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <list>
#include <chrono>
#include <vector>
#include "Graph.h"
#include "FibHeapNew.h"


#define NEG 1000000


int main() {


    
    
    
    Graph graph;
    // for part (a)
    graph.generateGraph("biggraph.txt");
   // graph.print();

    // for part (b)
    //graph.modifiedDijkstra(0);
    auto begin = chrono::high_resolution_clock::now();

    int n = graph.getNumVertices();
   // list <int> example (1,NEG);

    vector <list <int> > d(10000);

 //    vector <int> d(n, 32767); //since int, then inf =  32767;
	// d[source] = 0;


    int source = 0;




	vector <int> PI(n,0);
	PI[source] = -20000; //equivalent of NULL
	list <int> zero (1,0);
	d[0].push_back(source);
	vector <int> keys(n);
	keys[0]=0;
	//eVEB* tree = new eVEB(256);

	FibHeap<int> fh;
	FibHeap<int>::FibNode* nodezero = new FibHeap<int>::FibNode(0,nullptr);
	fh.insert(nodezero);

	// (*tree).insert(tree, 0);
	// map <directedEdge, int>::iterator weightind;
	// for (weightind = graph.weights.begin(); weightind != graph.weights.end(); weightind++){
	// 	if ((*weightind).first.first == 0){ //meaning we have found source
	// 		keys[(*weightind).first.second] = (*weightind).second;
	// 		(*tree).Insert(tree, (*weightind).second); //insert weight into Tree
	// 		d[(*weightind).second].push_back((*weightind).first.second); //push_back Vertices at that Distance
	// 	}
	// }
	vector <FibHeap<int>::FibNode*> vec(n);
	vec[0]=nullptr;
	//(*tree).Insert(tree,0);
	for (int i=1; i<n; i++){
		//(*tree).Insert(tree, i+200);
		FibHeap<int>::FibNode* node = new FibHeap<int>::FibNode(i+15500,nullptr);
		fh.insert(node);
		vec[i]=node;
		keys[i] = i+15500;
	}
	// cout << (*tree).isEmpty() << endl;
	int counter =0;
	while (fh.n!=0){
		
		FibHeap<int>::FibNode* node = fh.extract_min();


		int minkey = (*node).key;
		//cout << "minkey is " << minkey << endl;
		int u = d[minkey].front();

		//cout << "U is " << u << endl;
		
		map <directedEdge, int>::iterator weightind;

		for (weightind = graph.weights.begin(); weightind != graph.weights.end(); weightind++){
		//	cout << "EDGES: " << (*weightind).first.first << " " << (*weightind).first.second<<endl;
			if ((*weightind).first.first == u){ //meaning that the first edge is equal to the our u edge
				//cout << u << " " << (*weightind).first.second << endl;
				int v = (*weightind).first.second;
				int weightuv = (*weightind).second;
				// cout << "v is " << v << endl;
				// cout << "keys v and u are " << keys[v] <<" "<< keys[u] << endl;
				if (keys[v]>(keys[u]+weightuv)){  
					//cout << "Relaxing and updating tree of " <<  keys[v] <<" " << keys[u]+weightuv << endl;  
					//cout << (*tree).Search(tree, keys[v]) ;
					fh.decrease_key(vec[v], keys[u]+weightuv);
					//(*tree).Update(tree, vec[v], keys[u]+weightuv);
					keys[v]=keys[u]+weightuv;
					
					d[keys[v]].push_back(v);
					PI[v]=u;

				}
				

			}

	
		}
		//cout << "KEYS: "<< endl;
			// for (int i=0; i<keys.size(); i++){
			// 	cout << keys[i] << endl;
			// }
		counter ++;
		cout << counter << endl;
		if (counter >600){
			break;
		}
	}


	auto end = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << endl;
	



	cout << "Shortest paths from node " << source << ":" << endl;
	for (int j=0; j< keys.size(); j++){
		if (source == j) {
			j++;
		}
		cout << "Distance to vertex " << j << " is ";
		if (keys[j]==NEG){
			cout << "INF";
		}
		else cout <<  keys[j];
	
		cout << endl;
	}
    
    return 0;
}
