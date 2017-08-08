function [ quaternion, state_estimate ] = hack_init_estimates( markersn )
%
%
global n_m markers_body

% use linear regression to estimate COM location
A = zeros( n_m*3, 3 );
b(n_m*3) = 0;

% load up matrices: A*p = b
for i = 1:n_m
 for j = 1:3
  row = (i-1)*3 + 1;
  A(row+j-1,j) = 1;
  b(row+j-1) = markersn( 1, row+j-1 );
 end
end

% actually do regression
b = b';
p = A\b
% check errors (residuals)
A*p - b

quaternion = [1 0 0 0]';
state_estimate = [ p(1) p(2) p(3) 0 0 0 ]';
