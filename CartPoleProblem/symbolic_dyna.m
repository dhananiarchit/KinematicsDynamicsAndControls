clc 
clear all
close all

syms x dx ddx th dth ddth real

syms M m l g F positive

%Forward Kinematics
x1 = [x; 0];
x2 = x1 + [l*sin(th); -l*cos(th)];

%Velocity of each body
v1 = ddt(x1,[x dx ddx]);  %Velocity of mass 1
v2 = ddt(x2,[x dx ddx th dth ddth]);

%Kinetic Energy
T1 = simplify(1/2*M*norm(v1)^2);
T2 = simplify(1/2*m*norm(v2)^2);
%Total kinetic energy
T = T1+T2;  

%The total potential energy
V = M*x1(2)*g+m*x2(2)*g;  
Lagr = T-V;  %Form the Lagrangian

eq1 = vpa(simplify(ddt(diff(Lagr,dx),[x dx ddx th dth ddth])-diff(Lagr,x)),3)==F;
eq2 = vpa(simplify(ddt(diff(Lagr,dth),[x dx ddx th dth ddth])-diff(Lagr,th)),3)==0;

ddxeq = simplify(subs(eq1,ddth,solve(eq2,ddth)));
ddx_solve = simplify(solve(ddxeq,ddx));
ddtheq = simplify(subs(eq2,ddx,solve(eq1,ddx)));
ddth_solve = simplify(solve(ddtheq,ddth));

f = [dx;ddx_solve;dth;ddth_solve];

%Now write out the full Jacobian
Jac = jacobian(f,[x th dx dth]);

Asym = subs(Jac,[x th dx dth F],[0 0 0 0 0]);
%Now let's find the B matrix
Bsym = subs(diff(f,F),[x th dx dth F],[0 0 0 0 0]);
%Now, substitute the values of the parameters

A = double(vpa(subs(Asym,[g l m M],[9.81 1 0.1 1]),3));
B = double(vpa(subs(Bsym,[g l m M],[9.81 1 0.1 1]),3));
 
C = [1 0 0 0;0 1 0 0];

D = [0; 0];

sys = ss(A,B,C,D);
G = tf(sys);


%% Implementing the LQR control.
Asym = subs(Jac,[x th dx dth F],[0 0 0 0 0]);
%Now let's find the B matrix
Bsym = subs(diff(f,F),[x th dx dth F],[0 0 0 0 0]);
%Now, substitute the values of the parameters

A = double(vpa(subs(Asym,[g l m M],[9.81 3 1 5]),3));
B = double(vpa(subs(Bsym,[g l m M],[9.81 3 1 5]),3));
    
     

Q = eye(4);
R = 3;
[K_lqr,S_lqr] = lqrd(A,B,Q,R,0.01)
F = K_lqr*x;
x_1 = A*x+B*F;

x = [0;0;0;0];
figure
hold on
for i=1:20
    F = K_lqr*x;
    x_1 = A*x+B*F;
    plot(x_1(3),i,'x');
    x = x_1;
end