%%%%%% 
% 16-711 Kinematics, Dynamics and Controls
% Assignment 3
% Author - Archit Dhanani
%%%%% 
% 3D Rotation of the object

clc
clear all
close all

global markers
global markers_world
global NM
global NF


fname = 'd00122';

fid=fopen(fname, 'r','ieee-be');
specs=fscanf(fid,'%d %d %d %f',4);  % [dummy,cols,rows,freq]
MRDS.cols = specs(2);
MRDS.rows = specs(3);
MRDS.freq = specs(4);
MRDS.t    = (1:MRDS.rows)'/MRDS.freq;  % the time column
MRDS.vars = [];
MRDS.fname= fname;

for i=1:MRDS.cols,
	MRDS.vars(i).name=fscanf(fid,'%s',1);
	MRDS.vars(i).unit=fscanf(fid,'%s',1);
end;
fscanf(fid,'%c',3);

MRDS.data = fread(fid, [MRDS.cols,MRDS.rows],'float32');
MRDS.data=MRDS.data';
fclose(fid);


%% Basic DATA from the file


% Coordinates of the marker in the assignment co-ordinate system
markers = MRDS.data(:,81:104);
% Co-ordinates of the marker in the world co-ordinate system
markers_world = MRDS.data(:,57:80);

% position of the lander
pos_lander = MRDS.data(:,16:18);

%% Finding COMs from the optimization
NM = 8;
time = 10;
frequency = 0.01;

markers = [MRDS.data(:,1) markers];

markers_world = [MRDS.data(:,1) markers_world];

NF = time/frequency;

options = optimset('MaxFunEvals',1000000);

% p0 is the intitial parameter vector
n_p = 6; % com 3, v 3
p0(n_p) = 0;
for i = 1:n_p
 p0(i) = 0;
end

% do optimization
[answer,fval,exitflag]=fminunc(@criterion,p0,options);

init_com_world = answer(1:3);
init_vel = answer(4:6);

init_com_assignment = init_com_world - pos_lander(1,1:3);
com_world(1,:) = init_com_world;
com_assignment(1,:) = init_com_assignment;

%%
for i = 2:(NF+1)
    com_world(i,:) = init_com_world + init_vel*0.01*(i-1);
    com_assignment(i,:) = init_com_assignment + init_vel*0.01*(i-1);
end
%% Finding COMs from SDFAST

% SDFAST data

t = 0:0.01:10;

for i=1:(NF+1)
    comx(i) = (markers(i,2) + markers(i,23))/2;
    comy(i) = (markers(i,3) + markers(i,24))/2;
    comz(i) = (markers(i,4) + markers(i,25))/2; 
end

figure
hold on
plot(t,comx);
plot(t,comy);
plot(t,comz);
legend('com_x','com_y','com_z');
hold off

%% Calculating the quaternion

for i = 1: (NF+1)
    
    %finding the rotation matrix of the alien at every instance
    vectorx = markers_world(i,14:16) - markers_world(i,2:4);
    vectorx = vectorx./norm(vectorx);
    vectory = markers_world(i,8:10) - markers_world(i,2:4);
    vectory = vectory./norm(vectory);
    vectorz = markers_world(i,5:7) - markers_world(i,2:4);
    vectorz = vectorz./norm(vectorz);
    
    %in world co-ordinates
    rt(:,:,i) = [vectorx' vectory' vectorz'];
    
    %in assignment co-ordinates
    rt_(:,:,i) = rt(:,:,i)*[0 -1 0; 1 0 0; 0 0 1 ];
    
    % Quaternion in Assignment Co-ordinates
    q(:,i) = rotm2quat(rt_(:,:,i));
    if i>1
        if norm(q(:,i)-q(:,i-1))>1
            q(:,i) = -q(:,i);
        end
    end
    
    % Quaternion in World Co-ordinates
    qworld(:,i) = rotm2quat(rt(:,:,i));
    if i>1
        if norm(qworld(:,i)-qworld(:,i-1))>1
            qworld(:,i) = -qworld(:,i);
        end
    end
end

%% Writing the answer

fid1 = fopen('problem_2_0.dat','w');

q_scalar = q(1,:);
qx = q(2,:);
qy = q(3,:);
qz = q(4,:);

for i = 1:length(comx)
    fprintf(fid1,'%d %d %d %d %d %d %d\n',com_assignment(i,1),com_assignment(i,2),com_assignment(i,3),q_scalar(i),qx(i),qy(i),qz(i));
end
fclose(fid1);

%% Part B

% Angular velocity in Assignment Co-ordinates
for i = 1 : (NF)
   drt_(:,:,i) = (rt_(:,:,i+1)-rt_(:,:,i))/0.01;
   drt(:,:,i) = (rt(:,:,i+1)-rt(:,:,i))/0.01;
   
   % Calculation for Angular velocity in Assignment co-ordinates
   
   wt_(:,:,i) = transpose(rt_(:,:,i))*drt_(:,:,i);
   
   
   % Calculation for Angular velocity in World co-ordinates
   wt(:,:,i) = transpose(rt(:,:,i))*drt(:,:,i);
   
   wx(i) = wt_(3,2,i);
   wy(i) = wt_(1,3,i);
   wz(i) = wt_(2,1,i);
   
   wx_world(i) = wt(3,2,i);
   wy_world(i) = wt(1,3,i);
   wz_world(i) = wt(2,1,i);
end

%% Writing the file 
fid2 = fopen('problem_2_1.dat','w');

for i = 1:length(wx)
    fprintf(fid2,'%d %d %d\n',wx(i),wy(i),wz(i));
end
fclose(fid2);

%% Angular Acceleration Part 2C

for i = 1:NF-1
   ax(i) = (wx(i+1) - wx(i))/0.01;
   ay(i) = (wy(i+1) - wy(i))/0.01;
   az(i) = (wz(i+1) - wz(i))/0.01;
   
   ax_world(i) = (wx_world(i+1) - wx_world(i))/0.01;
   ay_world(i) = (wy_world(i+1) - wy_world(i))/0.01;
   az_world(i) = (wz_world(i+1) - wz_world(i))/0.01;
    
end
ax(i+1) = ax(i);
ay(i+1) = ay(i);
az(i+1) = az(i);

ax_world(i+1) = ax_world(i);
ay_world(i+1) = ay_world(i);
az_world(i+1) = az_world(i);
%% Writing the file 
fid3 = fopen('problem_2_2.dat','w');


for i = 1:length(ax)
    fprintf(fid3,'%d %d %d\n',ax(i),ay(i),az(i));
end
fclose(fid2);

%% Part 2D

wd = [ax' ay' az'];

w = [wx' wy' wz'];

a_total =[];

for i = 1:50:size(wd,1)
   a1 = [wd(i,1) 0 0 0 wd(i,3) wd(i,2);
        0 wd(i,2) 0 wd(i,3) 0 wd(i,1);
        0 0 wd(i,3) wd(i,2) wd(i,1) 0];
    
    a2 = [0 -w(i,3) w(i,2);
        w(i,3) 0 -w(i,1);
        -w(i,2) w(i,1) 0];
    a3 = [w(i,1) 0 0 0 w(i,3) w(i,2);
        0 w(i,2) 0 w(i,3) 0 w(i,1);
        0 0 w(i,3) w(i,2) w(i,1) 0]; 
    a = a1+a2*a3;
    
    a_total = [a_total;a];
    
end

[U,S,V] = svd(a_total);

I = [V(1,6) V(6,6) V(5,6);
    V(6,6) V(2,6) V(4,6);
    V(5,6) V(4,6) V(3,6)]

I_principle = diag([V(2,6) V(1,6) V(3,6)])

rotation_asstoprin = inv(I)*I_principle;

%% Part E

% Estimation of the Future trajectory of the object
% for next 10 seconds at frequency 100 Hz. 

w_final(1,:) = w(end,:);

a_final(1,:) = [ax(end)' ay(end)' az(end)'];

w_world_final(1,:) = [wx_world(end)' wy_world(end)' wz_world(end)'];

a_world_final(1,:) = [ax_world(end)' ay_world(end)' az_world(end)'];

com_final(1,:) = [com_assignment(end,1) com_assignment(end,2) com_assignment(end,3)];

rt_final(:,:,1) = rt(:,:,end);
rt_world_final(:,:,1) = rt_(:,:,end);

for i=2:NF
    com_final(i,:) = com_final(i-1,:) + init_vel*frequency;
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

rt_ = cat(3,rt_,rt_final);

rt = cat(3,rt,rt_world_final);

for i = 1:size(rt_,3)
q(:,i) = rotm2quat(rt_(:,:,i));
    if i>1
        if norm(q(:,i)-q(:,i-1))>1
            q(:,i) = -q(:,i);
        end
    end
    
    % Quaternion in World Co-ordinates
    qworld(:,i) = rotm2quat(rt(:,:,i));
    if i>1
        if norm(qworld(:,i)-qworld(:,i-1))>1
            qworld(:,i) = -qworld(:,i);
        end
    end
end
com_final = [com_assignment;com_final];

q_final = q';

%% Writing the file 
fid3 = fopen('problem_2_3.dat','w');


for i = 1:length(com_final(:,1))
    fprintf(fid3,'%d %d %d %d %d %d %d\n',com_final(i,1),com_final(i,2),com_final(i,3),q_final(i,1),q_final(i,2),q_final(i,3),q_final(i,4));
end
fclose(fid3);

%% Controller

rt(:,:,end)=[];
rt_(:,:,end)=[];
for i=1:NF
%     R_full(:,:,i) = quat2rotm(q_full_world(i,:));
    if i<=1000
        R_full(:,:,i) = rt_(:,:,i);
    else
        R_full(:,:,i) = rt_(:,:,i-1000);
    end
end

%Lander Trajectory
com_trajectory = com_world;
for i = 1:NF
    if i < 500
        offset = [-0.5 0 0];
    else
        offset = [-0.5 0 0];
    end
    com_trajectory(i,:) = com_trajectory(i,:) + offset*transpose(R_full(:,:,i));
 end
    
%Save data for simulation control
fid = fopen('q_scalar.txt','wt');
fprintf(fid,'q_scalar\n');
for i =1:NF
    fprintf(fid, '%f\n',q_final(i,1));
end
fclose(fid);

fid = fopen('q_x.txt','wt');
fprintf(fid,'q_x\n');
for i =1:NF
    fprintf(fid, '%f\n',q_final(i,2));
end
fclose(fid);

fid = fopen('q_y.txt','wt');
fprintf(fid,'q_y\n');
for i =1:NF
    fprintf(fid, '%f\n',q_final(i,3));
end
fclose(fid);

fid = fopen('q_z.txt','wt');
fprintf(fid,'q_z\n');
for i =1:NF
    fprintf(fid, '%f\n',q_final(i,4));
end
fclose(fid);


fid = fopen('COM_X.txt','wt');
fprintf(fid,'COM_X\n');
for i =1:NF
    fprintf(fid, '%f\n',com_trajectory(i,1));
end
fclose(fid);

fid = fopen('COM_Y.txt','wt');
fprintf(fid,'COM_Y\n');
for i =1:NF
    fprintf(fid, '%f\n',com_trajectory(i,2));
end
fclose(fid);

fid = fopen('COM_Z.txt','wt');
fprintf(fid,'COM_Z\n');
for i =1:NF
    fprintf(fid, '%f\n',com_trajectory(i,3));
end
fclose(fid);

fid = fopen('W_X.txt','wt');
fprintf(fid,'W_X\n');
for i =1:NF
    fprintf(fid, '%f\n',wx(i));
end
fclose(fid);

fid = fopen('W_Y.txt','wt');
fprintf(fid,'W_Y\n');
for i =1: NF
    fprintf(fid, '%f\n',wy(i));
end
fclose(fid);

fid = fopen('W_Z.txt','wt');
fprintf(fid,'W_Z\n');
for i =1: NF
    fprintf(fid, '%f\n',wz(i));
end
fclose(fid);
