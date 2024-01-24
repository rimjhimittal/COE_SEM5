clc;
all clear;
%Phase 1: input parameters
C=[40, 24]; %cost objective function
A=[20,50; 80, 50; 0,1; 1,0]; 
B=[480; 720; 0; 0];
%Phase 2 : Plotting Graph
x1 = 0:0.5:10;
x21= (B(1) - A(1,1)*x1)/A(1,2);
x22= (B(2) - A(2,1)*x1)/A(2,2);
x21= max(0,x21);
x22 = max(0,x22);
plot(x1,x21,'r',x1,x22,'g');
title('x1 vs x2');
xlabel('Values of x');
ylabel('Values of y');
%Phase 3 : Find Corner points with the axes
c1 = find(x1==0);
c2 = find(x21 == 0);
c3 = find(x22 == 0);
const1 = [x1(:,[c1,c2]);x21(:,[c1,c2])];
const2 = [x1(:,[c1,c3]);x22(:,[c1,c3])];
conpt = unique([const1,const2]','rows');


%Phase 4 : Find all intersection points

intpt = [];
for i= 1:size(A,1)
    for j=i+1: size(A,1)
        a = [A(i,:); A(j,:)];
        b= [B(i);B(j)];
        X = a\b;
        if X>= 0
            pt = X';
        else 
            pt = [];
        end
        intpt = [intpt;pt];
    end
end

%Phase 5 : Write all points
allpt= [intpt;conpt];
upt = unique(allpt,'rows');

%phase 6: Find the feasible points 
for i = 1:size(A,1)
    constraint = A(i,1)*upt(:,1) + A(i,2)*upt(:,2) -B(i);
    NF = find(constraint >0);
    upt(NF,:) = [];
end
disp(upt)
FP=unique(upt,'rows');
%Phase 7 : Finding optimal points for min and max
for i = 1:size(FP,1)
    z(i,:)=  FP(i,:)*C';
end
[opt_valmin,ind1] = min(z)
[opt_valmax,ind2]= max(z)
opt_minpt = FP(ind1,:)
opt_maxpt = FP(ind2,:)