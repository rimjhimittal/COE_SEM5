% Matlab code for LCM Method
clc
clear all
format short
%% Input the parameter
Cost=[11 20 7 8; 21 16 10 12; 8 12 18 19]; % Cost of TP
S=[50 40 70]; % Supply
D=[30 25 35 40]; % Demand
% To Check balanced/unbalanced TP
if sum(S)==sum(D)
    fprintf('The given TP is Balanced\n')
else
    fprintf('The given TP is unbal.\n')
    if sum(S)<sum(D)
        Cost(end+1,:)=zeros(1,size(D,2))
        S(end+1)=sum(D)-sum(S)
    else
        Cost(:,end+1)=zeros(size(S,2),1)
        D(end+1)=sum(S)-sum(D)

    end
end
%% LCM Start
ICost=Cost;
X=zeros(size(Cost)); % initial alloc
[m,n]=size(Cost); % Finding the no of rows and col
BFS=m+n-1;
%% To find the cell (with min cost)
for i=1:size(Cost,1)
    for j=1:size(Cost,2)
        [row_ind, col_ind]=find(Cost==min(Cost(:))); % For finding min cost value
        x11=min(S(row_ind),D(col_ind));
        [val, index]=max(x11); % finding the min cost max alloc
        ii=row_ind(index); % Identify row posi
        jj=col_ind(index); % Ind col position
        y11=min(S(ii),D(jj));
        X(ii,jj)=y11;
        S(ii)=S(ii)-y11;
        D(jj)=D(jj)-y11;
        Cost(ii,jj)=Inf
    end
end
%% To print IBFS
fprintf('Initial BFS=\n')
IBFS=array2table(X);
disp(IBFS)
% To check Deg and non-dg
FinalBFS=length(nonzeros(X));
if FinalBFS==BFS
    fprintf('The IBFS is non-deg\n')
else
    fprintf('The IBFS is Deg\n')
end
%% Total TP Cost
TPCost=sum(sum(ICost.*X));
fprintf('The total TP cost is %d\n',TPCost)




SteepestDescent
format short 
clc
clear all

syms x1 x2

% Objective Function
f1 = x1-x2+2*x1^2+2*x1*x2+x2^2;
fx = inline(f1);
fobj = @(x) fx(x(:,1),x(:,2));

% Gradient
grad = gradient(f1)
gradx = inline(grad)
gradobj = @(x) gradx(x(:,1), x(:,2));

% Hessian
hess = hessian(f1)
hessx = inline(hess)

% Iterations

init_x = [1 1];
maxiter = 4
tol = 10^(-3)
curr_iter = 0
X = []

while norm(gradobj(init_x))>tol && curr_iter<maxiter
    X = [X; init_x]
    S = -gradobj(init_x)
    H = hessx(init_x)
    lambda = (S' * S) ./( S' * H * S);
    Xnew = init_x + lambda * S';
    init_x = Xnew
    curr_iter = curr_iter + 1
end

fobj(init_x)




%% Solve LPP using simplex using Simplex Algo
%Max Z= x1-3x2-x1+3x2-2x3
% s.t.  3x1-x2+2x3<=7
%       -2x1+4x2<=12
%       -4x1+3x2+8x3<=10
%       xi>=0  i=1-3
%% Phase-T: Input the Parameter
Noofvariables=3;
variables={'x1','x2','x3','s1','s2','s3','sol'};
c=[-1 3 -2]; % cost of objective func33
Abar=[3 -1 2; -2 4 0; -4 3 8];% const coeff
B=[7;12;10]; %RHS of constraints
s=eye(size(Abar,1));
A=[Abar s B];
Cost=zeros(1,size(A,2));
Cost(1:Noofvariables)=c;
%% Contraints BV
BV=Noofvariables+1:1:size(A,2)-1;
% To calculate Zj-Cj
ZjCj=Cost(BV)*A-Cost;
% For printing 1st simplex table
ZCj=[ZjCj;A];
simplextable=array2table(ZCj);
simplextable.Properties.VariableNames(1:size(ZCj,2))=variables
%% Start simplex Algorithm
Run = true;
while Run
if any(ZjCj<0) % to check if any negative value there 
    fprintf('The current BFS is not optimal\n')
    fprintf('Next iteration required \n')
    disp('Old basic variable (BV)=')
    disp(BV)
    % For finding entering variable
    Zc=ZjCj(1:end-1);
    [Ent_col pvt_col]=min(Zc);
    fprintf('The most negative value in Zj-Cj row is %d and coresponding to column %d \n',Ent_col,pvt_col)
    fprintf('Entering variable is %d \n',pvt_col)
    %For finding the leaving variable
    sol=A(:,end);
    column=A(:,pvt_col);
    if all(column<=0)
        error('The LPP has unbounded solution \n since all enteries are <=0 in %d \n',pvt_col)
    else 
        for i=1:size(column,1)
            if column(i)>0
                ratio(i)=sol(i)./column(i)
            else 
                ratio(i)=inf
            end
        end
        %% To finding minimmum ratio
        [minratio pvt_row]=min(ratio);
        fprintf('The minimum ratio corresponding to pivot row %d \n ',pvt_row)
        fprintf('leaving variable is %d \n ',BV(pvt_row))
        BV(pvt_row)=pvt_col;
        disp('New basic variable(BV)==')
        disp(BV)
        pvt_key=A(pvt_row,pvt_col)
        %% To update table for next iteration
        A(pvt_row,:)=A(pvt_row,:)./pvt_key
        for i = 1:size(A,1)
            if i~= pvt_row
                A(i,:)=A(i,:)- A(i,pvt_col).*A(pvt_row,:);
            end
            ZjCj=ZjCj-ZjCj(pvt_col).*A(pvt_row,:);
        end

    end
    %% For printing
    ZCj=[ZjCj;A];
    FinalTable= array2table(ZCj);
    FinalTable.Properties.VariableNames(1:size(ZCj,2))=variables;
    FinalTable.Properties.RowNames(1:size(ZCj,1))={'Zj-Cj','X1','X2','S3'};
    BFS=zeros(1,size(A,2));
    BFS(BV)=A(:,end)
    BFS(end)=sum(BFS.*Cost)
    currentBFS=array2table(BFS);
    currentBFS.Properties.VariableNames(1:size(currentBFS,2))={'X1','X2','X3','S1','S2','S3','OptVal'}

else
    disp('Optimal sol is reached')
    Run = false;
end

end







bigm



clc
clear all
format short
%% Solve the LPP using Big M method
% Max Z=-2x1-x2
% s.t. 3x1+x2=3
%      4x1+3x2>=6
%      x1+2x2<=3
%% Phase-I Input the parameter
Variables={'x1','x2','s2','s3','A1','A2','sol'};
M=1000;
Cost=[-2 -1 0 0 -M -M 0];
A=[3 1 0 0 1 0 3; 4 3 -1  0 0 1 6; 1 2 0 1 0 0 3];
s=eye(size(A,1));
% To find starting BFS
BV=[];
for j=1:size(s,2)
    for i=1:size(A,2)
        if A(:,i)==s(:,j)
            BV=[BV i]
        end
    end
end
ZjCj=Cost(BV)*A-Cost;
 Run=true
 while Run
if any(ZjCj(1:end-1)<0) % to check if any zj-cj is negative
    fprintf('The current BFS is not optimal\n')
    fprintf('The next iteration req \n')
    disp('Old basic variable (BV)=')
    disp(BV)
    ZCj=ZjCj(1:end-1);
    [Ent_col pvt_col]=min(ZCj);
    fprintf('Entering col=%d \n',pvt_col)
    sol=A(:,end);
    column=A(:,pvt_col);
    if all (column<=0)
        error('The LPP has unbdd sol')
    else
        for i=1:size(A,1)
            if column(i)>0
                ratio(i)=sol(i)./column(i);
            else
                ratio(i)=inf;
            end
        end
        [min_ratio pvt_row]=min(ratio)
        fprintf('Leaving row=%d\n',pvt_row)
        BV(pvt_row)=pvt_col;
        disp(BV)
        pvt_key=A(pvt_row,pvt_col)
        A(pvt_row,:)=A(pvt_row,:)./pvt_key;
        for i=1:size(A,1)
            if i~=pvt_row
                A(i,:)=A(i,:)-A(i,pvt_col).*A(pvt_row,:);
            end
        end
        ZjCj=ZjCj-ZjCj(pvt_col).*A(pvt_row,:);
        ZC=[ZjCj;A];
        Finaltable=array2table(ZC)
        Finaltable.Properties.VariableNames(1:size(ZC,2))=Variables
        BFS(BV)=A(:,end)
    end
 else
     Run=false;
     fprintf('The current BFS is optimal\n')

end
end

