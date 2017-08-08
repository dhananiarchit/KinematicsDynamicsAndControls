function [r, p, y] = part1( target, link_length, min_roll, max_roll, min_pitch, max_pitch, min_yaw, max_yaw, obstacles )
%% Function that uses optimization to do inverse kinematics for a snake robot

%%Outputs 
  % [r, p, y] = roll, pitch, yaw vectors of the N joint angles
  %            (N link coordinate frames)
%%Inputs:
    % target: [x, y, z, q0, q1, q2, q3]' position and orientation of the end
    %    effector
    % link_length : Nx1 vectors of the lengths of the links
    % min_xxx, max_xxx are the vectors of the 
    %    limits on the roll, pitch, yaw of each link.
    % limits for a joint could be something like [-pi, pi]
    % obstacles: A Mx4 matrix where each row is [ x y z radius ] of a sphere
    %    obstacle. M obstacles.

% Your code goes here.

%initialize stuff
initdraw(length(link_length));
hold on;

%generate obstacle spheres
for i=1:length(obstacles(:,1))
    [x(:,:,i),y(:,:,i),z(:,:,i)] = sphere(10);
    surf(x(:,:,i)*obstacles(i,4)+obstacles(i,1),y(:,:,i)*obstacles(i,4)+obstacles(i,2),z(:,:,i)*obstacles(i,4)+obstacles(i,3));
end
    
%define initial configuration and bounds
numLinks = length(link_length);
for i=1:numLinks
    q0(i,:) = [0 0 0];
    answers(i,:,1) = [0 0 0];
    lb(i,1) = min_roll(i);
    lb(i,2) = min_pitch(i);
    lb(i,3) = min_yaw(i);
    ub(i,1) = max_roll(i);
    ub(i,2) = max_pitch(i);
    ub(i,3) = max_yaw(i);
end

%do optimization
options = optimoptions(@fmincon,'Display','iter','MaxFunEvals',2500,'Algorithm','interior-point');
[answer,fval,exitflag]=fmincon(@(q0)criterionPart1(q0,target,link_length,min_roll,min_pitch,min_yaw,max_roll,max_pitch,max_yaw),q0,[],[],[],[],lb,ub,@(q0)constraints(q0,link_length,target,obstacles),options);

% disp(answer);
% disp(fval);
% disp(exitflag);

if(fval>2.5)
    disp('  Target not within reach');
end

r = answer(:,1);
p = answer(:,2);
y = answer(:,3);

end