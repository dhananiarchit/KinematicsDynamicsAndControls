% load marker data file
load markersn

global T
% time step (length of time between measurements)
T = 0.1;

% number of filter states
global n_x
n_x = 6;
% number of markers
global n_m
n_m = 8;
% number of samples
n_t = length(markersn);

% marker locations in body coordinates
global markers_body
markers_body = [
  -1.5   -3.0   -4.5
  -1.5   -3.0    1.5
  -1.5    1.0   -4.5
  -1.5    1.0    1.5
   0.5   -3.0   -4.5
   0.5   -3.0    1.5
   0.5    1.0   -4.5
   0.5    1.0    1.5
];

% set up data arrays
quaternions_before_measurement( n_t, 4 ) = 0;
states_before_measurement( n_t, n_x ) = 0;
quaternions_before_process_update( n_t, 4 ) = 0;
states_before_process_update( n_t, n_x ) = 0;
marker_errors( n_t, n_m*3 ) = 0;
kalman_gains( n_t, 3 ) = 0;
variance_estimates_before_measurement( n_t, n_x ) = 0;
variance_estimates_before_process_update( n_t, n_x ) = 0;

% Initial estimates. Since EKF, need to get nonlinear part to be close
[ quaternion, state_estimate ] = hack_init_estimates( markersn );

% Initial condition noise model
variance_estimate = eye( n_x );

% postions
variance_estimate(1,1) = 1;
variance_estimate(2,2) = 1;
variance_estimate(3,3) = 1;

% velocities
variance_estimate(4,4) = 1;
variance_estimate(5,5) = 1;
variance_estimate(6,6) = 1;

Q = diag( ones( n_x, 1 ) );
Q(1,1) = 1e-10;
Q(2,2) = 1e-10;
Q(3,3) = 1e-10;
Q(4,4) = 1e-6;
Q(5,5) = 1e-6;
Q(6,6) = 1e-6;

% Measurement noise model: marker variance
R = diag( ones( n_m*3, 1 ) );

index = 1;

for index = 1:length(markersn)

 % Relinearize
 [ quaternion, state_estimate ] = relinearize( quaternion, state_estimate );

 % Compute measurement error
 [ marker_error, C ] = predict_markers( quaternion, state_estimate, ...
				 index, markersn );

 % Store values
 quaternions_before_measurement( index, : ) = quaternion;
 states_before_measurement( index, : ) = state_estimate;
 marker_errors( index, : ) = marker_error;
 for i = 1:n_x
  variance_estimates_before_measurement( index, i ) = ...
	   variance_estimate( i, i );
 end

 % Measurement update
 % should not use inv(), solve set of equations instead.
 kalman_gain = variance_estimate*C'*inv(C*variance_estimate*C' + R);
 for i = 1:3
  kalman_gains( index, i ) = kalman_gain( i, i );
 end
 state_estimate = state_estimate - kalman_gain*marker_error;
 variance_estimate = (eye(n_x) - kalman_gain*C)*variance_estimate;

 % Relinearize
 [ quaternion, state_estimate ] = relinearize( quaternion, state_estimate );

 % Store values
 quaternions_before_process_update( index, : ) = quaternion;
 states_before_process_update( index, : ) = state_estimate;
 for i = 1:n_x
  variance_estimates_before_process_update( index, i ) = ...
	   variance_estimate( i, i );
 end

 % Process update.
 [ state_estimate, A ] = do_dynamics( quaternion, state_estimate );
 variance_estimate = A*variance_estimate*A' + Q;

end
