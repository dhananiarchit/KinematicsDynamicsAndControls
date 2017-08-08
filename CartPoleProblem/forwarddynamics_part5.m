function [dy] = forwarddynamics_part5(t,y,constants,A,B)
    m = constants. m;
    M =constants.M;
    g= constants.g;
    l= constants.l;
    
    x = y(1,:);
    dx = y(2,:);
    th = wrapToPi(y(3,:));
    dth = y(4,:);
    
    if(th>40*pi/180)
%         Ee = 0.5*m*l*l*dth^2 + m*g*l*(1+cos(pi-th));
         Ee = 0.5*l*(dth^2)/g - (1+cos(pi-th));
%         kv = 50;
%         ke = 1;
%         kx = 100;
%         k = 300;
         th
%         u = -(kv*(m*l*dth*sin(pi-th)^2+m*g*cos(pi-th)*sin(pi-th)) + (m*sin(pi-th)^2)*(kx*x+k*dx))/((m*sin(pi-th)^2+M)*ke*Ee+kv);
         k_ =  230;
%          A = k_*(Ee*cos(pi-th)*dth/l-dx);
%          delta = m*sin(pi-th)*dth;
%          u = A*delta - m*l*dth^2*sin(pi-th) - m*g*sin(pi-th)*cos(pi-dth);
        u = -k_*dth*cos(th)*Ee;
        f= u
        ddx = (f+m*sin(pi-th)*(l*dth^2 + g*cos(pi-th)))/(M+m*(sin(pi-th))^2);
        ddth = (-f*cos(pi-th) - m*l*dth^2*sin(pi-th)*cos(pi-th)-(M+m)*g*sin(pi-th))/(l*(M+m)-l*m*(cos(pi-th))^2);
        dy = [dx;ddx;dth;ddth];    
    else
        f=-constants.k*y
        dy = A*y+B*f;
    end
end