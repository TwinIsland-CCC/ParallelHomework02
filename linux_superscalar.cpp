#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

const int n = 1000;
const int lim = 10;//计数上限

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
    float time_use=0;
    struct timeval start1, start2;
    struct timeval end1, end2;
    gettimeofday(&start1,NULL);


    while(c < lim){//normal算法
        normalAlg(a,b,sum);
        c++;
    }
    gettimeofday(&end1,NULL);
    time_use=(end1.tv_sec-start1.tv_sec)*1000000+(end1.tv_usec-start1.tv_usec);//微秒
    cout<<"NormalAlg: "<<time_use/1000<<"ms"<<endl;

    c = 0;

    gettimeofday(&start2,NULL);

    while(c < lim){//cache优化算法
        cacheOptAlg(a,b,sum);
        c++;
    }
    gettimeofday(&end2,NULL);
    time_use=(end2.tv_sec-start2.tv_sec)*1000000+(end2.tv_usec-start2.tv_usec);//微秒
    cout<<"CacheOptAlg: "<<time_use/1000<<"ms"<<endl;

    //show(a,b,sum,n);//检查结果正确性

    return 0;
}