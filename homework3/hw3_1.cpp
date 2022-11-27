#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
using namespace std;
//SRTF
// testcase: 3 0 2 4 6 3 1
int main(){
	int N;
	cin >> N;
	vector<int> arrival(N);
	vector<int> burst(N);
	for(int i=0;i<N;i++){
		cin >> arrival[i];
	}
	for(int i=0;i<N;i++){
		cin >> burst[i];
	}
	priority_queue< pair<int,int>, vector<pair<int,int> >, greater<pair<int,int>> > pq;
	int t = 0;
	//vector<int> starttime(N,-1);
	vector<int> endtime(N,-1);
	while(1){
		for(int i=0;i<N;i++){
			if(t==arrival[i]){
				pq.push(make_pair(burst[i],i));
			}
		}
		if(pq.empty()){
			t++;
		}
		else{
			break;
		}
	}
	
	while(!pq.empty()){
		int curburst = pq.top().first;
		int curprocess = pq.top().second;
		/*if(starttime[curprocess]==-1){
			starttime[curprocess] = t;
		}*/
		pq.pop();
		curburst--;
		t++;
		if(curburst!=0){
			pq.push(make_pair(curburst,curprocess));
			
		}
		else{
			endtime[curprocess] = t;
		}
		for(int i=0;i<N;i++){
			if(t==arrival[i]){
				pq.push(make_pair(burst[i],i));
			}
		}
	}
	//output
	int totalwait = 0;
	int totaltat = 0;
	for(int i=0;i<N;i++){
		cout << endtime[i]-arrival[i]-burst[i] << " " << endtime[i]-arrival[i] << endl;
		totalwait += endtime[i]-arrival[i]-burst[i];
		totaltat += endtime[i]-arrival[i];
	}
	cout << totalwait << endl << totaltat << endl;
}
