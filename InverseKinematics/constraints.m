%% constraints for optimizing 7 link inverse kinematics
function [ineq_violations,eq_violations]=constraints(joints,linkLengths,target,obstacles)
    joints = reshape(joints,[length(linkLengths) 3]);

    %forward kinematics
    [~, positions] = fk(joints,linkLengths,target);
    
    %avoid obstacle constraint
    numPoints = 10;
    zeroVector = [0;0;0];
    positions = [zeroVector positions];
    for i = 1:length(linkLengths) % each link
        for j = 1:3 % x,y,z
            checkPoints((numPoints*(i-1)+1):(numPoints*(i-1)+numPoints),j) = linspace(positions(j,i), positions(j,i+1), numPoints); %generate link interior
        end
    end
    for i=1:length(obstacles(:,1))
        for j=1:length(checkPoints)
           distances(i,j) = norm(checkPoints(j,:)-obstacles(i,1:3));
        end
        minDistance(i) = min(distances(i,:));
        distToSphere(i) = minDistance(i) - (obstacles(i,4) + 0.1);
        if distToSphere(i)>=0
            distCost(i) = 0;
        else
            distCost(i) = 1;
        end    
    end
    obstacle_violation = sum(distCost);
    
    %inequality violations
    ineq_violations=obstacle_violation;
    
    %equality violations
    eq_violations=[];
end