A = csvread('sysEarthN100yr10verlet.csv');
B = csvread('sysJupiterN100yr10verlet.csv');
C = csvread('sysSunN100yr10verlet.csv');
D = csvread('sysMarsN100yr10verlet.csv');
E = csvread('sysMercuryN100yr10verlet.csv');
F = csvread('sysNeptuneN100yr10verlet.csv');
G = csvread('sysPlutoN100yr10verlet.csv');
H = csvread('sysSaturnN100yr10verlet.csv');
I = csvread('sysUranusN100yr10verlet.csv');
% J = csvread('sysUranusN100yr300verlet.csv');
J = csvread('sysVenusN100yr10verlet.csv');

% plot(A(:,2),A(:,4),'b')
% plot(B(:,2),B(:,4),'b')
% plot(C(:,2),C(:,4),'b')
% plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r')
plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r',D(:,2),D(:,4),'k',E(:,2),E(:,4),'r',F(:,2),F(:,4),'r',G(:,2),G(:,4),'r',H(:,2),H(:,4),'r',I(:,2),I(:,4),'r',J(:,2),J(:,4),'g')