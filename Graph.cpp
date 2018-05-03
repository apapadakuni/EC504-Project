//Copyright Andreas Papadakis U40766151 apapadak@bu.edu
//Copyright Andre Gonzaga U29267211 agonzaga@bu.edu


#include "Graph.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

Graph:: Graph (void){
}

int Graph::addVertex(void){
	if (vertices.size()==0){
		vertices.insert(0);
		//cout << "size is 0" << endl;
		return 0;
	}
	else {
		int last = vertices.size()-1;
		//cout << "last is " << last << endl;
		vertices.insert(last+1);
		return last + 1;
	}
}

void Graph::addEdge(directedEdge newEdge, int weight){
	//first we need to check if the vertices are in the graph
	int v1 = newEdge.first;
	int v2 = newEdge.second;
	bool v1correct = false;
	bool v2correct = false;

	for (set<int>::iterator i = vertices.begin(); i != vertices.end(); i++){
		int vertex = *i;
		if (vertex == v1){
			v1correct = true;
		}
		if (vertex == v2){
			v2correct = true;
		}
	}
	//if both vertices exist in our vertices set then:
	if (v1correct && v2correct){
		edges.insert(newEdge);
		weights.insert(pair <directedEdge,int> (newEdge,weight));
	}

}


int Graph::getNumVertices(void){
	int num = vertices.size();
	return num;
}

int Graph::getWeight(directedEdge edge){
	int v1 = edge.first;
	int v2 = edge.second;
	for (map <directedEdge, int>::iterator i = weights.begin(); i!=weights.end();i++){
		int vertex1 = (*i).first.first;
		int vertex2 = (*i).first.second;
		int fat = (*i).second;
		if (v1 == vertex1 && v2 == vertex2){
			return fat;
		}
	}
	return -1;
}


bool Graph::isEdge(directedEdge newEdge){
	int v1 = newEdge.first;
	int v2 = newEdge.second;
	for (set<directedEdge>::iterator i = edges.begin(); i!=edges.end(); i++){
		int vertex1 = (*i).first;
		int vertex2 = (*i).second;
		if (v1 == vertex1 && v2 == vertex2){
			return true;
		}
	}
	return false;

}

void Graph::print(){
	for (set<int>::iterator i = vertices.begin(); i != vertices.end(); i++){
		int vertex = *i;
		cout << vertex << ": ";
		for (set<directedEdge>::iterator j = edges.begin(); j!=edges.end();j++){
			directedEdge edge=*j;
			int v1 = edge.first;
			int v2 = edge.second;
			if (v1 == vertex){
				cout << v2 <<" ";
				for (map <directedEdge, int>::iterator k = weights.begin(); k!=weights.end(); k++){
					pair <directedEdge, int> wat = *k;
					int firstv = wat.first.first;
					int secondv = wat.first.second;
					int printweight = wat.second;
					if (v1 == firstv && v2 == secondv){
						cout << "(" << printweight << ")" << " ";
					}
				}
				
			}

		}
		cout << endl;
	}
}



void Graph::generateGraph(string filename){
	
	string line;
	ifstream file(filename);
	bool firstline = true;


	if (file.is_open()){

		while (getline(file,line)){
				// for (int p=0; p<line.size();p++){
				// 	cout << line[p];
				// }	
				// cout << endl;
			if (firstline==true){

			

				string numofvert;
				int i;
				for (i=0; i<line.size();i++){
					if (line[i] !=' '){
						numofvert.push_back(line[i]);
						//cout << line[i];
					}
					else break;
				}
				int numofvertint;
				stringstream geek(numofvert);
				geek >> numofvertint;
				//cout << "num is " << numofvertint << endl;
				for (int k=0; k<numofvertint; k++){
					//cout << "addingvert\n";
					addVertex();
				}

			}
			else{

				int j;
				string v1;
				string v2;
				string WEEE;
				for (j =0; j<line.size();j++){
					if (line[j]!=' ')
						v1.push_back(line[j]);
					else break;
				}
				for (j=(j+1); j <line.size();j++){
					if (line[j]!=' ')
						v2.push_back(line[j]);
					else break;
				}

				for (j=(j+1); j<line.size();j++){
					WEEE.push_back(line[j]);
				}
				int v1int;
				int v2int;
				int WEEEint;
				stringstream geek1(v1);
				geek1 >> v1int;
				stringstream geek2(v2);
				geek2 >> v2int;
				stringstream geekw(WEEE);
				geekw >> WEEEint;
				directedEdge addingedge;
				addingedge = make_pair(v1int,v2int);
				addEdge(addingedge,WEEEint);
				
			}
			firstline = false;
		}
		file.close();
	}


}


bool compare(pair<int,int> i , pair<int,int> j){
	return i.second < j.second;
}





//In order to find the shortest distance from the source to every vertex, I just used Dijkstra's algorithm.
//In order to find the number of shortest paths, i just created another vector of integers "numofpaths"
//and when i test for d[v]> d[u]+weight(u,v) i also check for d[v] == d[u]+weight(u,v)
//so if they are equal, that means that there is another way to get to that node using another vertex
//and so i just increment numofpaths[v] by 1 each time that might happen and print them in the end 

void Graph::modifiedDijkstra(int source){
	vector <int> d(getNumVertices(), 32767); //since int, then inf =  32767;
	d[source] = 0;
	vector <int> PI(getNumVertices(),0);
	PI[source] = -20000; //equivalent of NULL
	// for (int i=0; i< PI.size(); i++){
	// 	cout << d[i];
	// }
	vector <pair<int, int> > Q(getNumVertices());
	for (int i=0; i< getNumVertices(); i++){
		Q[i] = make_pair(i, d[i]);
	}
	// for (int i=0; i<Q.size(); i++){
	// 	cout << Q[i].first << " " << Q[i].second << endl;
	// }

	vector <int> numofpaths(getNumVertices(),1);

	while (Q.size()>0){
		// cout << "Q "<<endl;
		// for (int i=0; i<Q.size(); i++){
		// 	cout << Q[i].first << " " << Q[i].second << endl;
		// }
		

		pair <int,int> min = *min_element(Q.begin(), Q.end(), compare);
	
		vector <pair <int, int> >::iterator minindex;
		minindex = find(Q.begin(), Q.end(), min);
		Q.erase(minindex);

		int u = min.first;
		map <directedEdge, int>::iterator weightind;

		for (weightind = weights.begin(); weightind != weights.end(); weightind++){
		//	cout << "EDGES: " << (*weightind).first.first << " " << (*weightind).first.second<<endl;
			if ((*weightind).first.first == u){ //meaning that the first edge is equal to the our u edge
				//cout << u << " " << (*weightind).first.second << endl;
				int v = (*weightind).first.second;
				int weightuv = (*weightind).second;
			//	cout << "BEFORE: v is "<<v<<" and u is "<<u<<endl;
				if (d[v]==(d[u]+weightuv)){
					// cout << "d[v] is " << d[v] <<endl;
					// cout << "v is " << v << " and u is " << u << endl;
					numofpaths[v]++;

				}
				if (d[v]>(d[u]+weightuv)){    //tried to put this into a function but call by referencing became complicated
					//cout <<"change: "<< "v is " << v << " and u is " << u << endl;
					d[v]=d[u]+weightuv;
					PI[v]=u;
					for (int in=0; in<Q.size(); in++){
						if (Q[in].first == v){ //change the key of v in our Q, so we can properly extract the minimum in our next iteration
							Q[in]=make_pair(v,d[v]);
						}
					}
					
					//cout << "CHANGE: w(u,v) is " << weightuv; 
					//cout << " v is " << v << " and u is " << u << endl;
				}
				

			}
	
		}
	}

	//while (Q.size())
	
	



	cout << "Shortest paths from node " << source << ":" << endl;
	for (int j=0; j< d.size(); j++){
		if (source == j) {
			j++;
		}
		cout << "Distance to vertex " << j << " is ";
		if (d[j]==32767){
			cout << "INF";
		}
		else cout <<  d[j];
	
		cout << " and there are " <<  numofpaths[j] << " shortest paths" <<endl;
	}
}




