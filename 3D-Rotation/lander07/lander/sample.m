w_final(1,:) = w(end,:);

a_final(1,:) = [ax(end)' ay(end)' az(end)'];

w_world_final(1,:) = [wx_world(end)' wy_world(end)' wz_world(end)'];

a_world_final(1,:) = [ax_world(end)' ay_world(end)' az_world(end)'];

com_final(1,:) = [com_assignment(end,1) com_assignment(end,2) com_assignment(end,3)];

rt_final(:,:,1) = rt(:,:,end);
rt_world_final(:,:,1) = rt_(:,:,end);

for i=2:NF
    com_final(i,:) = com_final(i-1,:) + init_vel*frequency*(i-1);
end

for i=1:1000
   % Simulate forward for next 10 seconds at frwquency 100 Hz
   % Angular velocity matrix
   w_matrix(:,:,i) = [0 -w_final(i,3) w_final(i,2);
                     w_final(i,3) 0 -w_final(i,1);
                     w_final(i,2) w_final(i,1) 0];
   W_matrix_world(:,:,i)= [0 -w_world_final(i,3) w_world_final(i,2);
                     w_world_final(i,3) 0 -w_world_final(i,1);
                     w_world_final(i,2) w_world_final(i,1) 0];
    
    drtdt(:,:,i) = rt_final(:,:,i)*w_matrix(:,:,i);
    drtdt_world(:,:,i) = rt_world_final(:,:,i)*W_matrix_world(:,:,i);
    
    rt_final(:,:,i+1) = rt_final(:,:,i) + drtdt(:,:,i)*frequency;
    w_final(i+1,1) = w_final(i,1) + a_final(i,1)*frequency;
    w_final(i+1,2) = w_final(i,2) + a_final(i,2)*frequency;
    w_final(i+1,3) = w_final(i,3) + a_final(i,3)*frequency;
%     
    rt_world_final(:,:,i+1) = rt_world_final(:,:,i) + drtdt_world(:,:,i);
    w_world_final(i+1,1)= w_world_final(i,1) + a_world_final(i,1)*frequency;
     w_world_final(i+1,2)= w_world_final(i,2) + a_world_final(i,2)*frequency;
     w_world_final(i+1,3)= w_world_final(i,3) + a_world_final(i,3)*frequency;
     
    a_final(i+1,:) = -(cross(w_final(i+1,:)',I_principle*w_final(i+1,:)'))'/I_principle;
     
     a_world_final(i+1,:) = -(cross(w_world_final(i+1,:)',I_principle*w_world_final(i+1,:)'))'/I_principle;
     
    
end