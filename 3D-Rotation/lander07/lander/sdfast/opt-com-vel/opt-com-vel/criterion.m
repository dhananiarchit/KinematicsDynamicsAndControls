%%% criterion for optimizing initial center of mass location and velocity
function score=criterion(p)

global markers_world
global NF

global NM % number of markers
dt = 0.01;

% pull out parameters
com = [ p(1) p(2) p(3) ];
vel = [ p(4) p(5) p(6) ];

score = 0;

% calculate distances from com to each marker.
d2(NM) = 0;
for j = 1:NM
 % last +1 to skip initial count variable
 v = markers_world(1,(3*(j-1)+1+1):(3*(j-1)+3+1)) - com;
 d2(j) = v*v'; % this is actually an inner product (since v is horizontal)
end


for i = 2:NF
     for j = 1:NM
          % last +1 to skip initial count variable
          v = markers_world(i,(3*(j-1)+1+1):(3*(j-1)+3+1)) - com - vel*dt*markers_world(i,1);
          dist = v*v';
          score = score + (d2(j) - dist)*(d2(j) - dist);
     end
end

end
