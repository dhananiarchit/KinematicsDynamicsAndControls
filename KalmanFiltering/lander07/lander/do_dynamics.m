function [ state_estimate, A ] = do_dynamics( quaternion, state_estimate );
%
%
global T
for i = 1:3
 state_estimate(i) = state_estimate(i) + T*state_estimate(i+3);
end
A = [ 1 0 0 T 0 0
      0 1 0 0 T 0
      0 0 1 0 0 T
      0 0 0 1 0 0
      0 0 0 0 1 0
      0 0 0 0 0 1 ];
