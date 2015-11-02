/*
Write a program for distance vector algorithm to find suitable path for transmission.
*/

#include <stdio.h>

#define MAX 10
struct node{
	int dist[MAX];
	int from[MAX];
} route[MAX];

int main(){

	int i, j, k, n;
	int source, dest, count;
	int dist_matrix[MAX][MAX];

	printf("Enter number of nodes: ");
	scanf("%d",&n);
	printf("Enter the distance matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			
			scanf("%d",&dist_matrix[i][j]);
			
			//distance of a node to itself is zero
			dist_matrix[i][i]=0;

			//initial routes
			route[i].dist[j]=dist_matrix[i][j];
			route[i].from[j]=j;
		}
	}

	do{
		count = 0;
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				for(k=0; k<n; k++){
					if( route[i].dist[j] > (dist_matrix[i][k] + route[k].dist[j]) ){
						route[i].dist[j] = dist_matrix[i][k] + route[k].dist[j];
						route[i].from[j] = k;
						count ++;
					}
				}
			}
		}
	}while(count);//repeat till no changes

	//output
	printf("Router Information for Routers %d to %d:-\n\n",1,n-1);
	for(i=0; i<n; i++){
		printf("\n\n=======================================\n");
		printf("\tRouter %d\n",i+1);
		printf("=======================================\n");
		printf("Dest\tNext-Hop\tDistance\n");
		for(j=0; j<n; j++){
			printf("%d\t%d\t\t%d\n",j+1,route[i].from[j]+1,route[i].dist[j]);
		}
		printf("---------------------------------------\n\n");
	}
	return 0;
}