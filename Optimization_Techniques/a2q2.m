% Maximize Z = 5x1 + 8x2
% x1 + 2x2 ≤ 200,
% x1 + x2 ≤ 150,
% x2 ≤ 60,
% x1, x2 ≥ 0


clc
clear all
format short


%% Input parameters
c=[5, 8]; %cost objective function
A=[1,2; 1,1; 0,1; 0,1; 1,0]; 
B=[200; 150; 60; 0; 0];
n=size(A,1); 
x1=0:0.01:max(B);

for i=1:n-2 %we take n-2 since we are also taking x1=0 and x2=0 as they have no significance in our graph
    y(i,:)=(B(i)-A(i,1)*x1)/A(i,2);
end

%% Drawing the lines
for i=1:n-2
    y(i,:)=max(0,y(i,:));
    plot(x1,y(i,:),'linewidth',4)
    hold on
end
hold on


%% Finding the point of intersection
pt=[0;0];
for i=1:size(A,1)
    A1=A(i,:);
    B1=B(i,:);
    for j=i+1:size(A,1)
        A2=A(j,:);
        B2=B(j,:);
        A3=[A1;A2];
        B3=[B1;B2];
        X3=inv(A3)*B3
        % X3=A3\B3;
        if(X3>=0)%since the number of chairs can never be negative
            pt= [pt X3];
        end
    end
end
X=pt';
X=unique(X,'rows')%solution


%% Keep only Feasible Points
x1=X(:,1);
x2=X(:,2);

for i=1:n-2
    ind=find(A(i,:)*X'>B(i))
    X(ind,:)=[]
end

%% Evaluate The Objective Function Value
obj_val=c*X';
[value, ind]=max(obj_val);
value;
X(ind,:)
Optimal=[X(ind,:) value];

%% Shaded feasible region

x=X(:,1);
y=X(:,2);
scatter(X(:,1),X(:,2),'*')
hold on
k=convhull(x,y)%the shaded region where a and y is satisfied
fill(x(k),y(k),'m')

%% setting the axes
xlim([0 max(x)+1])
ylim([0 max(y)+1])

xlabel('x-axis')
ylabel('y-axis')
title('Feasible region of the linear programming problem')
legend('x_1+2x_2\leq10')