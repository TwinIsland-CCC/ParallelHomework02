#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

const int n = 3000;
const int lim = 1;//计数上限

void show(float* a, float** b, float* sum){
    cout<<"a:  "<<endl;
    for(int i = 0; i < n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<"b:  "<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i = 0; i < n; i++){
        cout<<sum[i]<<" ";
    }
    cout<<endl;
}

void normalAlg(float* a, float** b, float* sum){
    for(int i = 0; i < n; i++){
        sum[i] = 0.0;
        for(int j = 0; j < n; j++)
            sum[i] += b[j][i] * a[j];
    }
}

void cacheOptAlg(float* a, float** b, float* sum){
    for(int i = 0; i < n; i++) sum[i] = 0.0;
    for(int j = 0; j < n; j++)
        for(int i = 0; i < n; i++)
            sum[i] += b[j][i] * a[j];
}

int main()
{
    float* a = new float[n];
    float** b = new float*[n];
    float* sum = new float[n];
    int c = 0;//计数
    srand((int)time(0));
    //initial 100以内随机数初始化
    for(int i = 0; i < n; i++) {
        a[i] = rand()%100;
        b[i] = new float[n];
        for(int j = 0; j < n; j++)
            b[i][j] = rand()%100;
    }
    cout<<"问题规模为"<<n<<"，算法的运行次数为"<<lim<<"，使用随机初始值"<<endl;
    long long head, tail1, tail2, freq;
    QueryPerformanceFrequency((LARGE_INTEGER* )&freq);
    //start time
    QueryPerformanceCounter((LARGE_INTEGER* )&head);


    while(c < lim){//normal算法
        normalAlg(a,b,sum);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER* )&tail1);

    cout << "Normal: " << (tail1 - head) * 1000.0 / freq
    << "ms" << endl ;

    c = 0;

    head = tail1;

    while(c < lim){//cache优化算法
        cacheOptAlg(a,b,sum);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER* )&tail2);
    cout << "CacheOpt: " << (tail2 - head) * 1000.0 / freq
    << "ms" << endl ;

    //show(a,b,sum,n);//检查结果正确性

    return 0;
}
