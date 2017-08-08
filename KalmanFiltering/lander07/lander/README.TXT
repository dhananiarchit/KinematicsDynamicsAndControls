Files:
doit.m: run Kalman filter
hack_init_estimates.m: get initial state estimates
relinearize.m: handle nominal state (used for quaternion representation of rotation in part2)
predict_markers.m: measurement update
do_dynamics.m: process update
p1m00: example noisy marker data file
markers: clean marker data file
markersn: what doit.m uses
states: correct answer
Everything else (*.c *.h etc): Assignment 2 simulation to generate data.

% at shell level
cp p1n00 markersn
% in matlab
doit   % runs doit.m

% checking against correct answers

load states
maxi = 500;
ii = 1:maxi;
j = 1; % try 2, 3, 4, 5, 6 
plot(ii,states(ii,j),'r',ii,states_before_process_update(ii,j),'b')
plot(ii,states(ii,j)-states_before_process_update(ii,j),'b')

ii = 1:maxi;
j = 0;
plot(ii,marker_errors(ii,3*j+1),'r',ii,marker_errors(ii,3*j+2),'g',ii,marker_errors(ii,3*j+3),'b')

ii = 10:maxi;
plot(ii,kalman_gains(ii,1),'r',ii,kalman_gains(ii,2),'g',ii,kalman_gains(ii,3),'b')

ii = 10:maxi;
j = 1;
plot(ii,variance_estimates_before_measurement(ii,j),'r',ii,variance_estimates_before_process_update(ii,j),'b')
