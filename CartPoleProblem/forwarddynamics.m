function [dy] = forwarddynamics(t,y,constants)
    m = constants. m;
    M =constants.M;
    g= constants.g;
    l= constants.l;
    
    x = y(1,:);
    dx = y(2,:);
    th = wrapToPi(y(3,:));
    dth = y(4,:);
    
    f=0;
    
    ddx = (f+m*sin(th)*(l*dth^2 - g*cos(th)))/(M+m*(sin(th))^2);
    ddth = (-f*cos(th) - m*l*dth^2*sin(th)*cos(th)+(M+m)*g*sin(th))/(l*(M+m)-l*m*(cos(th))^2);
    
    dy = [dx;ddx;dth;ddth];
end