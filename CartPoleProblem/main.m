clc 
clear all
close all

%% PART A Symbolic dynamics program
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

eq1 = vpa(simplify(ddt(diff(Lagr,dx),[x dx ddx th dth ddth])-diff(Lagr,x)),3)==F
eq2 = vpa(simplify(ddt(diff(Lagr,dth),[x dx ddx th dth ddth])-diff(Lagr,th)),3)==0

ddxeq = simplify(subs(eq1,ddth,solve(eq2,ddth)));
ddx_solve = simplify(solve(ddxeq,ddx));
ddtheq = simplify(subs(eq2,ddx,solve(eq1,ddx)));
ddth_solve = simplify(solve(ddtheq,ddth));

f = [dx;ddx_solve;dth;ddth_solve]

%Now write out the full Jacobian
Jac = jacobian(f,[x dx th dth]);

Asym = subs(Jac,[x dx th dth F],[0 0 0 0 0]);
%Now let's find the B matrix
Bsym = subs(diff(f,F),[x dx th dth F],[0 0 0 0 0]);
%Now, substitute the values of the parameters

A = double(vpa(subs(Asym,[g l m M],[9.81 1 0.1 1]),3));
B = double(vpa(subs(Bsym,[g l m M],[9.81 1 0.1 1]),3));
 
C = [1 0 0 0;0 1 0 0];

D = [0; 0];

sys = ss(A,B,C,D);
G = tf(sys);

%% PART B

warning off;
y0 = [0 0 pi/3 0];
tspan = [0 10];
constants.m = 0.1;
constants.M = 1;
constants.g = 9.81;
constants.l = 1;

options = odeset('RelTol',1e-3);
[t,y] = ode45(@(t,y)forwarddynamics(t,y,constants),tspan,y0',options);


vid = VideoWriter('part2.avi');
open(vid)
fig = figure(1); hold on;
for i = 1: length(y)-1
    clf(1);
    animation(y(i,1), y(i,3), 1);
    pause(t(i+1)-t(i));
    frame = getframe(gcf);
    writeVideo(vid,frame)
end
close(vid)

%% PART C
% Manual Controller Gain

warning off;

constants.m = 0.1;
constants.M = 1;
constants.g = 9.81;
constants.l = 1;
constants.k = [-1 -3 -44.9 -13];

y0 = [0 0 pi/3 0];

tspan = [0 10];

options = odeset('RelTol',1e-3);
[t,y] = ode45(@(t,y)forwarddynamics_part3(t,y,constants),tspan,y0',options);


vid = VideoWriter('part3.avi');
open(vid);
fig = figure(1); hold on;
for i = 1: length(y)-1
    clf(1);
    animation(y(i,1), y(i,3), constants.l);
    pause(t(i+1)-t(i));
    frame = getframe(gcf);
    writeVideo(vid,frame)
end
close(vid)

%% Part 4 

% implementation of LQR controller
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

eq1 = vpa(simplify(ddt(diff(Lagr,dx),[x dx ddx th dth ddth])-diff(Lagr,x)),3)==F
eq2 = vpa(simplify(ddt(diff(Lagr,dth),[x dx ddx th dth ddth])-diff(Lagr,th)),3)==0

ddxeq = simplify(subs(eq1,ddth,solve(eq2,ddth)));
ddx_solve = simplify(solve(ddxeq,ddx));
ddtheq = simplify(subs(eq2,ddx,solve(eq1,ddx)));
ddth_solve = simplify(solve(ddtheq,ddth));

f = [dx;ddx_solve;dth;ddth_solve]

%Now write out the full Jacobian
Jac = jacobian(f,[x dx th dth]);

Asym = subs(Jac,[x dx th dth F],[0 0 0 0 0]);
%Now let's find the B matrix
Bsym = subs(diff(f,F),[x dx th dth F],[0 0 0 0 0]);
%Now, substitute the values of the parameters

A = double(vpa(subs(Asym,[g l m M],[9.81 1 0.1 1]),3));
B = double(vpa(subs(Bsym,[g l m M],[9.81 1 0.1 1]),3));
 
C = [1 0 0 0;0 1 0 0];

D = [0; 0];

%%
Q = [0.5 0 0 0; 0 0.1 0 0; 0 0 1 0; 0 0 0 0.1];
R = 1;
[K_lqr,S_lqr] = lqr(A,B,Q,R)
constants.k = K_lqr;


y0 = [0 0 -pi/3 0];
tspan = [0 10];

options = odeset('RelTol',1e-3);
[t,y] = ode45(@(t,y)forwarddynamics_part4(t,y,constants,A,B),tspan,y0',options);


vid = VideoWriter('part4.avi');
open(vid);
fig = figure(1); hold on;
for i = 1: length(y)-1
    clf(1);
    animation(y(i,1), y(i,3), constants.l);
    pause(t(i+1)-t(i));
    frame = getframe(gcf);
    writeVideo(vid,frame)
end
close(vid)



%% Non linear controller


