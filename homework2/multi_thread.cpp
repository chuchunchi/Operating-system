#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
# define MAX 500
# define THNUM 20
int matA[MAX][MAX];
int matB[MAX][MAX];
long long int sumC[THNUM];
long long int sumD[THNUM];
int K=MAX/THNUM;
void* th_fun(void* tid){
    int id = *(int *) &tid;
    //int K = MAX/THNUM;
    long long sumc = 0;
    long long sumd = 0;
    int i = id;
    for(int k=0;k<=K;k++){
        if(i<MAX){
            for(int j=0;j<MAX;j++){
                sumc += matA[i][j] + matB[i][j];
                for (int l = 0; l < MAX; l++) {
                    sumd += matA[i][l] * matB[l][j];
                }
            }
        }
        else{
            break;
        }
        i += THNUM;
    }
    sumC[id] = sumc;
    sumD[id] = sumd;
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
    long long sum_D = 0;
    for(int i=0;i<THNUM;i++){
        pthread_create(&th[i], NULL, th_fun, (void *) i);
    }
    for(int i=0;i<THNUM;i++){
        pthread_join(th[i], NULL);
    }
    for(int i=0;i<THNUM;i++){
        sum_C += sumC[i];
        sum_D += sumD[i];
    }
    cout << sum_C << '\n' << sum_D;
    return 0;
}
