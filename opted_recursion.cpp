#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

using std::cin;
using std::cout;
using std::endl;

const int n = 1024;
const int lim = 1000;

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

void optedRecursionAlg1(int* a, int& sum, int n) {
    if (n == 1) {
        sum = a[0];
        return;
    }
    else {
        for (int i = 0; i < n / 2; i += 2) {
            //cout << a[i] << " " << a[n - i - 1] << endl;
            a[i] += a[n - i - 1];
            a[i + 1] += a[n - i -2];
        }
        n /= 2;
        optedRecursionAlg1(a, sum, n);
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
    cout<<endl;
    int sum = 0;
    long long freq, head, tail1, tail2, tail3, tail4, tail5;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    int c = 0;
    while (c < lim) {
        normalAlg(a, sum);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail1);

    cout << "Normal: " << (tail1 - head) * 1000.0 / freq
         << "ms" << endl;
    //cout << sum << endl;
    head = tail1;
    c = 0;
    sum = 0;

    while (c < lim) {
        superscalraOptAlg(a, sum);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail2);
    cout << "superscalarOpt: " << (tail2 - head) * 1000.0 / freq
         << "ms" << endl;
    //cout << sum << endl;
    head = tail2;
    c = 0;
    sum = 0;

    while (c < lim) {
        optedRecursionAlg1(a, sum, n);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail5);
    cout << "optedRecursionAlg1: " << (tail5 - head) * 1000.0 / freq
         << "ms" << endl;
    //cout << sum << endl;
    head = tail5;
    c = 0;
    sum = 0;


    while (c < lim) {
        recursionOptAlg1(a, sum, n);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail3);
    cout << "recursionOpt1: " << (tail3 - head) * 1000.0 / freq
         << "ms" << endl;
    //cout << sum << endl;
    head = tail3;
    c = 0;
    sum = 0;

    while (c < lim) {
        recursionOptAlg2(b, sum, n);
        c++;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail4);
    cout << "recursionOpt2: " << (tail4 - head) * 1000.0 / freq
         << "ms" << endl;
    //cout << sum;
    //cin >> head;
    return 0;
}
