// Write a program for distance vector algorithm to find suitable path for transmission.
#include <iostream>
#include <cstdio>
#define MAX 5

using namespace std;

/* Structure for storing distance vectors routes*/
struct node {
	int dist[MAX];
	int from[MAX];
} route[MAX];

int main(){
	int n;
	int dm[MAX][MAX]; //distance matrix
	int count; //variable to determine when algorithm stops

	cout << "Enter number of nodes: ";
	cin >> n;
	cout << "Enter distance matrix(99 for infinity):\n";
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> dm[i][j];

			//initial routes of 1 hop each
			route[i].dist[j] = dm[i][j];
			route[i].from[j] = j;
		}
		// Set distance of a node to itself as 0
		dm[i][i]=0;
	}

	//distance vector algorithm
	do {
		count=0;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					if( route[i].dist[j] > dm[i][k] + route[k].dist[j] ){
						route[i].dist[j] = dm[i][k] + route[k].dist[j];
						route[i].from[j] = k;
						count++;
					}
				}
			}
		}
	}while(count); //stop when count remains 0

	// Display the routing tables
	cout << "Routing Information for Routers 1 to " << n << ":-\n\n";
	for(int i=0; i<n; i++){
		cout << "\n\n=======================================\n";
		cout << "\t\t Router " << i+1 << "\n";
		cout << "=======================================\n";
		cout << "Dest\tNext-Hop\tDistance\n";
		for(int j=0; j<n; j++){
			printf("%d\t%d\t\t%d\n",j+1,route[i].from[j]+1,route[i].dist[j]);
			cout << "---------------------------------------\n\n" ;
		}
	}

	return 0;
}