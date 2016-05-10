A = csvread('test8rk4N100yr256.csv');
B = csvread('test9rk4N100yr512.csv');
C = csvread('test10rk4N100yr1024.csv');
% D = csvread('sysMarsN100yr300verlet.csv');
% E = csvread('sysMercuryN100yr300verlet.csv');
% F = csvread('sysNeptuneN100yr300verlet.csv');
% G = csvread('sysPlutoN100yr300verlet.csv');
% H = csvread('sysSaturnN100yr300verlet.csv');
% I = csvread('sysUranusN100yr300verlet.csv');
% J = csvread('sysVenusN100yr300verlet.csv');

% plot(A(:,2),A(:,4),'b'))
% plot(B(:,2),B(:,4),'b')
% plot(C(:,2),C(:,4),'b')
plot(A(:,2),A(:,4),'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r')
title('Escape velocity simulations')
% plot(A(:,2),A(:,4,'b',B(:,2),B(:,4),'g',C(:,2),C(:,4),'r',D(:,2),D(:,4),'k',E(:,2),E(:,4),'r',F(:,2),F(:,4),'r',G(:,2),G(:,4),'r',H(:,2),H(:,4),'r',I(:,2),I(:,4),'r',J(:,2),J(:,4),'g')