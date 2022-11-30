#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
using namespace std;
//SRTF
// testcase: 3 0 2 8 7 4 1 3
int main(){
	int N, Q;
	cin >> N;
	vector<int> arrival(N);
	vector<int> burst(N);
	for(int i=0;i<N;i++){
		cin >> arrival[i];
	}
	for(int i=0;i<N;i++){
		cin >> burst[i];
	}
	cin >> Q; 
	queue<int> que;
	queue<int> FCFSq;
	int t = 0;
	//vector<int> starttime(N,-1);
	vector<int> endtime(N,-1);
	while(1){
		for(int i=0;i<N;i++){
			if(t==arrival[i]){
				que.push(i);
			}
		}
		if(que.empty()){
			t++;
		}
		else{
			break;
		}
	}
	int lastt = arrival[N-1];
	vector<int> qleft(N,Q);
	vector<int> tleft = burst;
	int sw = 0;
	while(1){
		if(!que.empty()){
			if(sw==-1 && !FCFSq.empty()){
				int tmp = FCFSq.front();
				FCFSq.pop();
				FCFSq.push(tmp);
				sw = 1;
			}
			int curprocess = que.front();
			qleft[curprocess]--;
			tleft[curprocess]--;
			t++;
			for(int i=0;i<N;i++){
				if(t==arrival[i]){
					que.push(i);
				}
			}
			if(tleft[curprocess]==0){
				endtime[curprocess] = t;
				que.pop();
			}
			else if(qleft[curprocess]==0){
				que.pop();
				FCFSq.push(curprocess);
			}
		}
		else{
			sw = -1;
			if(FCFSq.empty() && lastt<t){
				break;
			}
			else if(FCFSq.empty()){
				t++;
				for(int i=0;i<N;i++){
					if(t==arrival[i]){
						que.push(i);
					}
				}
				continue;
			}
			int curp = FCFSq.front();
			tleft[curp]--;
			t++;
			if(tleft[curp]==0){
				FCFSq.pop();
				endtime[curp] = t;
			}
			for(int i=0;i<N;i++){
				if(t==arrival[i]){
					que.push(i);
				}
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
