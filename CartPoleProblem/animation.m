function [] = animation(x_cart, theta_pole, length_pole)
    
    length_cart = 0.6;
    breadth_cart = 0.3;
    
    % Draw Cart Pole
    hold on;
    rectangle('Position', [x_cart-0.5*length_cart 0 length_cart breadth_cart], 'FaceColor', [0.5 0 0], 'LineWidth', 2);
    line([x_cart x_cart+length_pole*sin(theta_pole)], [breadth_cart breadth_cart+length_pole*cos(theta_pole)], 'Color', 'b', 'LineWidth', 1.5);


    % Draw Wheels
    th = 0:pi/50:2*pi; r = 0.1;
    yunit = r * sin(th) - r;
    xunit = r * cos(th) + (x_cart-0.25*length_cart);
    plot(xunit, yunit, 'LineWidth', 2, 'Color', [0 0 0]);
    xunit = r * cos(th) + (x_cart+0.25*length_cart);
    plot(xunit, yunit, 'LineWidth', 2, 'Color', [0 0 0]);

    % Draw Ground
    xmin = -6; xmax = 6; ymin = -4; ymax = 4;
    line([xmin  xmax], [-2*r -2*r], 'Color', [0 0 0], 'LineWidth', 2);
    xlim([xmin xmax]); ylim([ymin ymax]);
    
    xlabel('x (m)'); ylabel('y (m)');

end