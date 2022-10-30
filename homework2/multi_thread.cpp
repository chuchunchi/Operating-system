#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;\
# define MAX 500
#define THNUM = 3
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
long long int sum[THNUM]
long long int th_fun(void* tid){
    int id = int(tid);
    int K = MAX/THNUM;
    for(int k=0;k<=K;k++){
        int i = id + k * THNUM;
        if(i<=MAX){
            for(int j=0;j<MAX;j++){
                sum[id] += matA[i][j] + matB[i][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }
    pthread_t th[THNUM];
    long long sum_C = 0;
    for(int i=0;i<THNUM;i++){
        sum[i] = 0;
        pthread_create(&th[i], NULL, th_fun, (void *) i);
    }
    for(int i=0;i<THNUM;i++){
        pthread_join(th[i], NULL);
        sum_C += sum[i];
    }
    cout << sum_C << endl;

    return 0;
}