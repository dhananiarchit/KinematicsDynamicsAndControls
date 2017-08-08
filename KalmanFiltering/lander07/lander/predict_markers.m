function [ marker_error, C ] = predict_markers( quaternion, state_estimate, index, markersn );
%
%
global n_m markers_body
for i = 1:n_m
 for j = 1:3
  ind = (i-1)*3 + j;
  marker_error(ind) = markers_body(i,j) + state_estimate(j) - markersn(index,ind);
 end
end
% make it vertical
marker_error = marker_error';

C = [ 1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0
      1 0 0 0 0 0
      0 1 0 0 0 0
      0 0 1 0 0 0 ];

