A = csvread('sysEarthN1000yr10verlet.csv');
B = csvread('sysJupiterN1000yr10verlet.csv');
C = csvread('sysSunn1000yr10verlet.csv');
plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r')