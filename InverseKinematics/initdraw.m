function initdraw(numlinks)

    global h_axes link1 link2 link3 link4 link5 link6 link7 link8 link9 link10 targetVisual;

    scrsz = get(0,'ScreenSize');
    animation = figure(1);

    color0 = [0 0 0];
    color1 = [1 0 0];
    color2 = [0 0 1];
    color3 = [0 1 0];
    color4 = [1 0 1];

    set(animation,'name','My Robot','Position',[500 100 650 650]);
    h_axes = axes('Parent',animation,'Units','Pixels','Position',[100 100 500 500],'Ylim',[-5.0 5.0],'Xlim',[-5.0 5.0], 'Zlim',[-5.0 5.0]);
    axis equal;
    width = 6;
    targetVisual= line('Parent',h_axes,'Color',color4,'Visible','off','LineWidth',5);
    if numlinks == 1

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);

    elseif numlinks == 2

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);

    elseif numlinks == 3

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);

    elseif numlinks == 4

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);

    elseif numlinks == 5

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);


    elseif numlinks == 6

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link6 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);

    elseif numlinks == 7

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link6 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link7 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);

    elseif numlinks == 8

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link6 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link7 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link8 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);

    elseif numlinks == 9

        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link6 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link7 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link8 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link9 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);

    elseif numlinks == 10
        link1 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link2 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link3 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link4 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link5 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link6 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link7 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);
        link8 = line('Parent',h_axes,'Color',color2,'Visible','off','LineWidth',width);
        link9 = line('Parent',h_axes,'Color',color3,'Visible','off','LineWidth',width);
        link10 = line('Parent',h_axes,'Color',color1,'Visible','off','LineWidth',width);   
    end

    set(h_axes,'visible','on');

end