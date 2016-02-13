N10 = csvread('N10.txt');
N100 = csvread('N100.txt');
N1000 = csvread('N1000.txt');
N10000 = csvread('N10000.txt');

x10 = linspace(0,1,10);
x100 = linspace(0,1,100);
x1000 = linspace(0,1,1000);
x10000 = linspace(0,1,10000);
x = linspace(0,1,100000);

actual = 1-(1-exp(-10)).*x-exp(-10.*x);

subplot(3,2,1);
plot(x10,N10);
title('N=10 Approximation');
subplot(3,2,2);
plot(x100,N100);
title('N=100 Approximation');
subplot(3,2,3);
plot(x1000,N1000);
title('N=1000 Approximation');
subplot(3,2,4);
plot(x10000,N10000);
title('N=10000 Approximation');
subplot(3,2,5);
plot(x,actual);
title('u(x)=1-(1-exp(-10))x-exp(-10x)');

