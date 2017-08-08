% Use optimization to find center of mass and velocity

% globals
global markers % marker data array NFx(NM*3)
global NF % number of frames

load markers

NF = 10; % number of frames (including initial frame)

% set options for fminunc()
% options = optimset();
options = optimset('MaxFunEvals',1000000);

% p0 is the intitial parameter vector
n_p = 6; % com 3, v 3
p0(n_p) = 0;
for i = 1:n_p
 p0(i) = 0;
end

% do optimization
[answer,fval,exitflag]=fminunc(@criterion,p0,options)

