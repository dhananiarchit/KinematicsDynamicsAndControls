%% optimization criterion: joints is vector of joint angles
function score = criterionCMAES(joints)
    global target1 link_length1 min_roll1 min_pitch1 min_yaw1 max_roll1 max_pitch1 max_yaw1 obstacles1

    joints = reshape(joints,[length(link_length1) 3]);

    %forward kinematics
    [pose, positions] = fk_cmaes(joints,link_length1,target1);
    
    %joints near limit their limits cost
    for i=1:length(joints)
        roll_average(i) = mean([min_roll1(i) max_roll1(i)]);
        pitch_average(i) = mean([min_pitch1(i),max_pitch1(i)]);
        yaw_average(i) = mean([min_yaw1(i),max_yaw1(i)]);
        difference_matrix(i,:) = [abs(joints(i,1)-roll_average(i)), abs(joints(i,2)-pitch_average(i)), abs(joints(i,3)-yaw_average(i))];
    end
    joint_limit_cost = 0.25 * norm(difference_matrix);
    
    %final pose cost
    final_pose_cost = 5 * norm(pose(1:7)-target1(1:7));  
    
    %avoid obstacle cost
    numPoints = 10;
    zeroVector = [0;0;0];
    positions = [zeroVector positions];
    for i = 1:length(link_length1) % each link
        for j = 1:3 % x,y,z
            checkPoints((numPoints*(i-1)+1):(numPoints*(i-1)+numPoints),j) = linspace(positions(j,i), positions(j,i+1), numPoints); %generate link interior
        end
    end
    for i=1:length(obstacles1(:,1))
        for j=1:length(checkPoints)
           distances(i,j) = norm(checkPoints(j,:)-obstacles1(i,1:3));
        end
        minDistance(i) = min(distances(i,:));
        distToSphere(i) = minDistance(i) - (obstacles1(i,4) + 0.1);
        if distToSphere(i)>=0
            distCost(i) = 0;
        else
            distCost(i) = 1;
        end    
    end
    obstacle_cost = sum(distCost);
    
    %total cost
    score = final_pose_cost + joint_limit_cost + obstacle_cost;
end