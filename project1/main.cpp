using namespace std;

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "time.h"
#include "../../ComputationalPhysicsMSU/doc/Programs/LecturePrograms/programs/cppLibrary/lib.h"

int main()
{
    clock_t start_alg, finish_alg;
    cout << "N?" << endl; //size of matrix
    int N, i, j;
    double h;
    cin >> N;
    double n = N;
    h = 1/(n+1);
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
    // forward substitution
    for(i=1 ; i < N ; i++) {
        A[i]=A[i]-(1/A[i-1]);
        B[i]=B[i]+B[i-1]/A[i-1];
    }

    // backward substitution
    double *X = new double[N];;
    X[N-1] = B[N-1]/A[N-1];
    for(i=1 ; i < N ; i++) {
        X[N-1-i]=(B[N-1-i]+X[N-i])/A[N-1-i];
    }
    finish_alg=clock();

    double *E = new double[N];
    double u, x;
    double maxerror = 0.0;

    //Finding error at each point, and maximum error
    for(i=1 ; i < N ; i++) {
        x = i*h;
        u = 1 - (1 - exp(-10))*x - exp(-10*x);
        E[i]= log10(abs((X[i]-u)/u));
        if (E[i]>maxerror){maxerror = E[i];}
    }

    cout << "Max Error: " << maxerror << endl;

    //write results to output file
    std::string N_str = std::to_string(N);
    std::string filename = "N" + N_str + ".txt";
    ofstream myfile (filename);
    if (myfile.is_open())
      {
        for(int count = 0; count < N; count ++){
            myfile << X[count] << "\n" ;
        }
        myfile.close();
      }

    cout << "Time Alg: " << ((finish_alg-start_alg)/CLOCKS_PER_SEC)<<endl;

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
        for ( j = 0; j < N; j++){
            if (i==j){
                Z[i][j]=2.0;
                        }
            else if (i==j+1 || j == i+1){
                Z[i][j]=-1.0;
            }
            else{
                Z[i][j]=0.0;
            }

        }
    }
    double *b = new double[N];
    // initialize b = h^2*f(x) = 100*exp(-10x)
    for(i=0 ; i < N ; i++) {
        b[i]=h*h*100*exp(-10*h*i);
    }

    clock_t start_LU, finish_LU;
    start_LU = clock();
    // LU decompose the matrix
    ludcmp(Z,N,indx,&d);
    // Then backward substitution
    lubksb(Z, N, indx, b);
    finish_LU = clock();

    cout << "Time LU: " << ((finish_LU-start_LU)/CLOCKS_PER_SEC)<<endl;

    // Free space
    delete [] b;
    for ( i = 0 ; i < N; i++) delete [] Z[i];
    delete [] Z;

    return 0;
}
