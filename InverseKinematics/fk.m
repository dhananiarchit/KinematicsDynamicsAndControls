%% do forward kinematics of 7 link arm
function [pose, positions] = fk(joints,linkLengths,target)
    Tfinal = eye(4);
    
    %get complete Rotation Matrix
    for i=1:length(linkLengths)
        %rotation matrix for roll (Rx)
        Rx(:,:,i) = [1        0                      0       ; ...
                    0   cos(joints(i,1))    -sin(joints(i,1)); ...
                    0   sin(joints(i,1))     cos(joints(i,1))];
        
        %for pitch (Ry)
        Ry(:,:,i) = [cos(joints(i,2))   0    sin(joints(i,2)); ...
                    0                   1           0        ; ...
                    -sin(joints(i,2))   0    cos(joints(i,2))];
        
        %for yaw (Rz)  
        Rz(:,:,i) = [cos(joints(i,3))   -sin(joints(i,3))   0; ...
                    sin(joints(i,3))     cos(joints(i,3))   0; ...
                    0                        0              1];
       
        %overall rotation matrix
        R(:,:,i) = Rx(:,:,i)*Ry(:,:,i)*Rz(:,:,i);
        
        %homogeneous transformation matrix for one link
        Trot(:,:,i) = eye(4);
        Trot(1:3,1:3,i) = R(:,:,i);
        Ttrans(:,:,i) = eye(4);
        Ttrans(1,4,i) = linkLengths(i);
        T(:,:,i) = Trot(:,:,i)*Ttrans(:,:,i);
        
        %get complete transformation matrix
        Tfinal = Tfinal * T(:,:,i);
        positions(:,i) = Tfinal(1:3,4);
    end
    
    %get final pose
    Rfinal(:,:) = Tfinal(1:3,1:3);
    Qfinal = rotm2quat(Rfinal);
    Pfinal = positions(:,end)';
    finalPose = [Pfinal Qfinal];
	pose = finalPose;
end