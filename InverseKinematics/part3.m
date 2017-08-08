function [r, p, y] = part3( target, link_length, min_roll, max_roll, min_pitch, max_pitch, min_yaw, max_yaw, obstacles )
%% Function that uses optimization to do inverse kinematics for a snake robot
global target1 link_length1 min_roll1 min_pitch1 min_yaw1 max_roll1 max_pitch1 max_yaw1 obstacles1
target1 = target;
link_length1 = link_length;
min_roll1 = min_roll;
min_pitch1 = min_pitch;
min_yaw1 = min_yaw;
max_roll1 = max_roll;
max_pitch1 = max_pitch;
max_yaw1 = max_yaw;
obstacles1 = obstacles;

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
initdraw(length(link_length1));
hold on;

%generate obstacle spheres
for i=1:length(obstacles(:,1))
    [x(:,:,i),y(:,:,i),z(:,:,i)] = sphere(10);
    surf(x(:,:,i)*obstacles(i,4)+obstacles(i,1),y(:,:,i)*obstacles(i,4)+obstacles(i,2),z(:,:,i)*obstacles(i,4)+obstacles(i,3));
end
    
%define initial configuration and bounds
numLinks = length(link_length1);
for i=1:numLinks*3
    q0(i) = 0;
end
%do optimization
opts.LBounds = -pi; opts.UBounds = pi; opts.Restarts = 3; opts.maxfunevals=5000;
[answer,fmin, counteval,stopflag,out,bestever] = cmaes('criterionCMAES',q0(:),0.3,opts);
% disp(answer);
% disp(fmin);

if(fmin>2.5)
    disp('  Target not within reach');
end

r = answer(:,1);
p = answer(:,2);
y = answer(:,3);

end