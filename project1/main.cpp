#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    cout << "Hellote" << endl;
    int N;
    int i;
    int j;

    double h;
    cin >> N;
    double n = N;
    h = 1/(n+1);
    cout << h << endl;
    double A[100][100];
    // initialize A matrix, diagonal = 2, off diagonal = -1
    for(i=0 ; i < N ; i++) {
        for(j=0 ; j < N ; j++) {
            if (i==j){
                A[i][j] = 2.0;}
            else if ((i+1==j) || (i==1+j) ){
                A[i][j] = -1.0;}
            else
            {
                A[i][j] = 0.0;
            }
        }
    }

    double B[100];
    // initialize B = h^2*f(x) = 100*exp(-10x)
    for(i=0 ; i < N ; i++) {
        B[i]=h*h*100*exp(-10*h*i);
    }

    // forward substitution
    for(i=1 ; i < N ; i++) {
        cout << "A[i-1][i-1]" << A[i-1][i-1] << "A[i][i]" <<A[i][i]<<endl;
        A[i][i]=A[i][i]-(1/A[i-1][i-1]);
        cout << A[i][i]<< endl;

        B[i]=B[i]+B[i-1]/A[i-1][i-1];
    }

    // backward substitution
    double X[100];
    X[N-1] = B[N-1]/A[N-1][N-1];
    for(i=1 ; i < N ; i++) {
        X[N-1-i]=(B[N-1-i]+X[N-i])/A[N-1-i][N-1-i];
    }


    double E[100];
    double u;
    double x;
    for(i=0 ; i < N ; i++) {
        x = i*h;
        u = 1 - (1 - exp(-10))*x - exp(-10*x);
        E[i]= log10(abs((X[i]-u)/u));
    }

    ofstream myfile ("example.txt");
    if (myfile.is_open())
      {
        for(int count = 0; count < N; count ++){
            myfile << X[count] << " "<< E[count] << "\n" ;
        }
        myfile.close();
      }


    return 0;
}
