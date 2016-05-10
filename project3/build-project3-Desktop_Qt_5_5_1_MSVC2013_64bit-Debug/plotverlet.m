A = csvread('Earthrk4N100yr5.csv');
plot(A(:,2),A(:,4))
title('Earth orbiting fixed Sun - RK4 method, N=100, 5 years')