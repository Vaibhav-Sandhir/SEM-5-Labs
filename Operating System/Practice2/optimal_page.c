#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ind = 0;

int isPresent(int m, int frames[m], int page){
	for(int i = 0; i < m; i++){
		if(frames[i] == page){
			return 1;
		}
	}
	return 0;
}

int indexOf(int m, int frames[m], int page){
	for(int i = 0; i < m; i++){
		if(frames[i] == page){
			return i;
		}
	}
}

int mostFar(int m, int n, int start, int frames[m], int arr[n]){
	int max_dist = 0;
	int max_page = -1;
	int dist = 0;
	
	for(int i = 0; i < m; i++){
		int flag = 0;
		for(int j = start + 1; j < n; j++){
			if(arr[j] == frames[i]){
				flag = 1;
				dist = j - start;
				break;
			}
		}
		if(flag == 0){
			return indexOf(m, frames, frames[i]);
		}
		if(dist > max_dist){
			printf("\nPage %d far %d start was %d", frames[i], dist, start);
			max_page = frames[i];
			max_dist = dist;
		}
	}
	return indexOf(m, frames, max_page);
}

void display(int m, int frames[m]){
	printf("\n----------\n");
	for(int i = 0; i < m; i++){
		printf("%d\n", frames[i]);
	}
	printf("\n----------");
}

void optimal(int m, int n, int frames[m], int arr[n]){
	for(int i = 0; i < n; i++){
		if(ind < 3){
			frames[ind++] = arr[i];
			display(m, frames);
		}
		
		else if(isPresent(m, frames, arr[i])){
			printf("\nPage hit for %d ", arr[i]);
		}
		else{
			int k = mostFar(m, n, i, frames, arr);
			frames[k] = arr[i];
			display(m, frames);
		}
	}
}

void main(){
	int n = 20;
	int reference_string[20] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	int m = 3;
	int frames[3] = {-1, -1, -1};
	optimal(m, n, frames, reference_string);
}
