#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
/*
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/
using namespace std;
vector<int> inputstr;
int numframe, len;
int FIFO(){
	queue<int> q;
	int fault=0;
	for(int i=0;i<len;i++){
		int obj = inputstr[i];
		queue<int> tmp = q;
		int inside=0;
		while(!tmp.empty()){
			if(obj==tmp.front()){
				inside=1;
				break;
			}
			tmp.pop();
		}
		if(!inside){
			if(q.size()>=numframe){
				q.pop();
			}
			fault++;
			q.push(obj);
		}
	}
	return fault;
}

int LRU(){
	class Node{
		public:
			Node(){
				prev = NULL;
				next = NULL;
			}
			Node(int k){
				key = k;
				prev = NULL;
				next = NULL;
			}
			Node* prev;
			Node* next;
			int key;
	};
	unordered_map<int,Node*> lrumap;
	Node* head = new Node();
	Node* tail = new Node();
	head->next = tail;
	tail->prev = head;
	int fault=0;
	for(int i=0;i<len;i++){
		int k = inputstr[i];
		//inside cache
		if(lrumap.count(k)>0){
			Node* tmp = head->next;
			Node* tmp2 = lrumap[k]->prev;
			Node* tmp3 = lrumap[k]->next;
			tmp2->next = tmp3;
			tmp3->prev = tmp2;
			head->next = lrumap[k];
			lrumap[k]->prev = head;
			lrumap[k]->next = tmp;
			tmp->prev = lrumap[k];
		}
		else{
			if(lrumap.size()<numframe){
				Node* newnode = new Node(k);
				lrumap[k] = newnode;
				Node* tmp = head->next;
				head->next = lrumap[k];
				lrumap[k]->prev = head;
				lrumap[k]->next = tmp;
				tmp->prev = lrumap[k];
			}
			else{
				//erase
				Node* erase = tail->prev;
				Node* tmp = erase->prev;
				tmp->next = tail;
				tail->prev = tmp;
				lrumap.erase(erase->key);
				//add
				Node* newnode = new Node(k);
				lrumap[k] = newnode;
				Node* tmp2 = head->next;
				head->next = lrumap[k];
				lrumap[k]->prev = head;
				lrumap[k]->next = tmp2;
				tmp2->prev = lrumap[k];
			}
			fault++;
		}
	}
	return fault;
}
//TODO: delete node, list
int LFU(){
	class FreqList;
	class Node{
		public:
			Node(){
				prev = NULL;
				next = NULL;
			}
			Node(int k){
				key = k;
				prev = NULL;
				next = NULL;
			}
			Node* prev;
			Node* next;
			int key;
			FreqList* f;
	};
	class FreqList{
		
		public:
			FreqList(){
				freq = -1;
				head->next = tail;
				tail->prev = head;
			}
			FreqList(int f){
				freq = f;
				head->next = tail;
				tail->prev = head;
			}
			FreqList* prevList;
			FreqList* nextList;
			int freq;
			Node* head = new Node();
			Node* tail = new Node();
	};
	
	unordered_map<int,Node*> lfumap;
	FreqList* highList = new FreqList();
	FreqList* lowList = new FreqList();
	highList->prevList = lowList;
	lowList->nextList = highList;
	int fault=0;
	for(int i=0;i<len;i++){
		int k = inputstr[i];
		cout << "k: " << k << " size: " << lfumap.size() << endl;
		cout << lowList->nextList->freq << " ffffffffffffffffffffffff" << endl;
		if(lfumap.count(k)>0){
			//inside cache
			//remove from cur list
			cout << "inside cache" << endl;
			Node* cur = lfumap[k];
			FreqList* curList = cur->f;
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			
			//move to "head" of upper freq list
			FreqList* moveto;
			if(curList->nextList->freq==curList->freq+1){
				moveto = curList->nextList;
			}
			else{
				cout << "new a new list" << endl;
				moveto = new FreqList(curList->freq+1);
				FreqList* tmpList = curList->nextList;
				curList->nextList = moveto;
				moveto->prevList = curList;
				tmpList->prevList = moveto;
				moveto->nextList = tmpList;
			}
			cur->f = moveto;
			Node* tmp = moveto->head->next;
			moveto->head->next = cur;
			cur->prev = moveto->head;
			cur->next = tmp;
			tmp->prev = cur;
			if(curList->head->next==curList->tail){
				//current list become NULL list
				cout << "become NULL list" << endl;
				curList->nextList->prevList = curList->prevList;
				curList->prevList->nextList = curList->nextList;
			}
		}
		else{
			//not in cache
			
			if(lfumap.size()>=numframe){
				cout << "cache is full-" << endl;
				//cache is full->remove lowList->next's tail
				Node* erase = lowList->nextList->tail->prev;
				cout << "erase: " << erase->key << endl;
				lfumap.erase(erase->key);
				erase->prev->next = erase->next;
				erase->next->prev = erase->prev;
				FreqList* curList = erase->f;
				if(curList->head->next==curList->tail){
					//current list become NULL list
					curList->nextList->prevList = curList->prevList;
					curList->prevList->nextList = curList->nextList;
				}
				//add curnode to freq=0 list's head
			}
			//cache is not full->put to list-freq=0's head
			cout << "put to list-freq=0's head" << endl;
			FreqList* newList;
			if(lowList->nextList->freq!=0){
				newList = new FreqList(0);
				FreqList* tmpList = lowList->nextList;
				lowList->nextList = newList;
				newList->prevList = lowList;
				tmpList->prevList = newList;
				newList->nextList = tmpList;
			}
			else{
				newList = lowList->nextList;

			}
			Node* newnode = new Node(k);
			lfumap[k] = newnode;
			newnode->f = newList;
			Node* tmp = newList->head->next;
			newList->head->next = newnode;
			newnode->prev = newList->head;
			newnode->next = tmp;
			tmp->prev = newnode;
			fault++;
		}
		cout << "fault: " << fault << endl;
		cout << "==================" << endl;
	}
	return fault;
}
int main(){
	
	cin >> numframe >> len;
	for(int i=0;i<len;i++){
		int inp;
		cin >> inp;
		inputstr.push_back(inp);
	}
	cout << FIFO() << endl << LRU() << endl << LFU() << endl;
}
