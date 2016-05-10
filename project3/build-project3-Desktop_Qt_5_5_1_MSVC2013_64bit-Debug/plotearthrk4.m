% A = csvread('earthrk4.csv');
% % y vs. x
% plot(A(:,2),A(:,4))

%x vs. t
%plot(A(:,1),A(:,2))

%y vs. t
%plot(A(:,1),A(:,4))

A = csvread('test8rk4N1000yr256.csv')
plot(A(:,2),(A(:,4)))