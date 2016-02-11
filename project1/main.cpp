using namespace std;

#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "time.h"
#include <new>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "lib.h"


int main()
{
    clock_t start_alg, finish_alg;
    cout << "Hellote" << endl;
    int N;
    int i;
    int j;

    double h;
    cin >> N;
    double n = N;
    h = 1/(n+1);
    cout << h << endl;
    double *A = new double[N];
    // initialize A array, representing diagonal of A, all elements = 2
    for(i=0 ; i < N ; i++) {
        A[i] = 2.0;}

    double *B = new double[N];
    // initialize B = h^2*f(x) = 100*exp(-10x)
    for(i=0 ; i < N ; i++) {
        B[i]=h*h*100*exp(-10*h*i);
    }

    start_alg=clock();
    cout << "Start" << clock() << endl;
    // forward substitution
    for(i=1 ; i < N ; i++) {
        //cout << "A[i-1]" << A[i-1] << "A[i]" <<A[i]<<endl;
        A[i]=A[i]-(1/A[i-1]);
        //cout << A[i]<< endl;

        B[i]=B[i]+B[i-1]/A[i-1];
    }

    // backward substitution
    double *X = new double[N];;
    X[N-1] = B[N-1]/A[N-1];
    for(i=1 ; i < N ; i++) {
        X[N-1-i]=(B[N-1-i]+X[N-i])/A[N-1-i];
    }
    finish_alg=clock();
    cout << "Finish" << clock() << endl;

    double *E = new double[N];
    double u;
    double x;
    double maxerror = 0.0;
    for(i=1 ; i < N ; i++) {
        x = i*h;
        u = 1 - (1 - exp(-10))*x - exp(-10*x);
        E[i]= log10(abs((X[i]-u)/u));
        if (E[i]>maxerror){maxerror = E[i];}
    }

    cout << "Max Error" << maxerror << endl;

    ofstream myfile ("example.txt");
    if (myfile.is_open())
      {
        for(int count = 0; count < N; count ++){
            myfile << X[count] << " " << E[count] << "\n" ;
        }
        myfile.close();
      }

    cout << "time" << ((finish_alg-start_alg)/CLOCKS_PER_SEC)<<endl;

    delete [] A; delete [] B; delete [] X; delete [] E;

    int *indx;
    indx = new int[N];
    double d;
    double **Z;
    Z=new double*[N];
    for ( i = 0; i < N; i++){
            Z[i] = new double[N];
    }
    for ( i = 0; i < N; i++){
        for ( j = 0; i < N; i++){
            if (i==j){
                Z[i][j]=2;
                        }
            else if (i==j+1 || i+1==j){
                Z[i][j]=-1;
            }
            else{
                Z[i][j]=0;
            }

        }
    }

    ludcmp(Z,N,indx,&d);


    return 0;
}
