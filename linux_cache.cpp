#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <ctime>

using namespace std;

using std::cin;
using std::cout;
using std::endl;

const int n = 134217728;
const int lim = 1;

void normalAlg(int* a, int& sum) {
    for (int i = 0; i < n; ++i) {
        sum += a[i];

    }
}

void superscalraOptAlg(int* a, int& sum) {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i += 2) {
        sum1 += a[i];
        sum2 += a[i + 1];
    }
    sum = sum1 + sum2;
}

void recursionOptAlg1(int* a, int& sum, int n) {
    if (n == 1) {
        sum = a[0];
        return;
    }
    else {
        for (int i = 0; i < n / 2; ++i) {
            //cout << a[i] << " " << a[n - i - 1] << endl;
            a[i] += a[n - i - 1];
        }
        n /= 2;
        recursionOptAlg1(a, sum, n);
    }
}


void recursionOptAlg2(int* a, int& sum, int n) {
    for (int m = n; m > 1; m /= 2) // log(n)个步骤
        for (int i = 0; i < m / 2; i++)
            a[i] = a[i * 2] + a[i * 2 + 1];// 相邻元素相加连续存储到数组最前面
    // a[0]为最终结果
    sum = a[0];
}

int main() {



    int* a = new int[n];
    int* b = new int[n];
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 100;
        b[i] = a[i];
        //cout << a[i] << " ";
    }


    float time_use=0;
    struct timeval start1, start2, start3, start4;
    struct timeval end1, end2, end3, end4;

    gettimeofday(&start1,NULL); //gettimeofday(&start,&tz);结果一样

    int sum = 0;
    int c = 0;
    while (c < lim) {
        normalAlg(a, sum);
        c++;
    }

    gettimeofday(&end1,NULL);
    time_use=(end1.tv_sec-start1.tv_sec)*1000000+(end1.tv_usec-start1.tv_usec);//微秒
    cout<<"NormalAlg: "<<time_use/1000<<"ms"<<endl;

    c = 0;
    sum = 0;

    gettimeofday(&start2,NULL); //gettimeofday(&start,&tz);结果一样

    while (c < lim) {
        superscalraOptAlg(a, sum);
        c++;
    }
    gettimeofday(&end2,NULL);
    time_use=(end2.tv_sec-start2.tv_sec)*1000000+(end2.tv_usec-start2.tv_usec);//微秒
    cout<<"SuperscalraOptAlg: "<<time_use/1000<<"ms"<<endl;

    c = 0;
    sum = 0;

    gettimeofday(&start3,NULL); //gettimeofday(&start,&tz);结果一样
    while (c < lim) {
        recursionOptAlg1(a, sum, n);
        c++;
    }
    gettimeofday(&end3,NULL);
    time_use=(end3.tv_sec-start3.tv_sec)*1000000+(end3.tv_usec-start3.tv_usec);//微秒
    cout<<"recursionOptAlg1: "<<time_use/1000<<"ms"<<endl;
    c = 0;
    sum = 0;

    gettimeofday(&start4,NULL); //gettimeofday(&start,&tz);结果一样
    while (c < lim) {
        recursionOptAlg2(b, sum, n);
        c++;
    }
    gettimeofday(&end4,NULL);
    time_use=(end4.tv_sec-start4.tv_sec)*1000000+(end4.tv_usec-start4.tv_usec);//微秒
    cout<<"recursionOptAlg2: "<<time_use/1000<<"ms"<<endl;
    //cin >> head;
    return 0;
}