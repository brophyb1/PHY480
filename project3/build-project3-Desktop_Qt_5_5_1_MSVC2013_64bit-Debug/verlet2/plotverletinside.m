A = csvread('sysEarthN200yr250verlet.csv');
B = csvread('sysJupiterN200yr250verlet.csv');
C = csvread('sysSunN200yr250verlet.csv');
D = csvread('sysMarsN200yr250verlet.csv');
E = csvread('sysMercuryN200yr250verlet.csv');
F = csvread('sysNeptuneN200yr250verlet.csv');
G = csvread('sysPlutoN200yr250verlet.csv');
H = csvread('sysSaturnN200yr250verlet.csv');
I = csvread('sysUranusN200yr250verlet.csv');
% J = csvread('sysUranusN100yr300verlet.csv');
J = csvread('sysVenusN200yr250verlet.csv');

% plot(A(:,2),A(:,4),'b')
% plot(B(:,2),B(:,4),'b')
% plot(C(:,2),C(:,4),'b')
% plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r')
plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r',D(:,2),D(:,4),'k',E(:,2),E(:,4),'r',F(:,2),F(:,4),'g',G(:,2),G(:,4),'b',H(:,2),H(:,4),'k',I(:,2),I(:,4),'r',J(:,2),J(:,4),'g')