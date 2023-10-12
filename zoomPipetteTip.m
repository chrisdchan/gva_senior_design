function [x1, x2, y1, y2] = zoomPipetteTip(im,tipAngle,startPix,currZoom,ax,fig)
%Function to zoom in and out on the pipette tip
[ysize,xsize] = size(im);
zBuffer_y = 3;
zBuffer_x = .01;

%How long is the tip in pixels
if currZoom > 1
    tipLen =  xsize-startPix;
    x1 = max(1,startPix-tipLen/currZoom*zBuffer_x);
    x2 = min(xsize,startPix+tipLen/currZoom*(zBuffer_x+1));
    y1 = max(1,ysize/2 - tand(tipAngle)*tipLen/currZoom*(zBuffer_y+1));
    y2 = min(ysize,ysize/2 + tand(tipAngle)*tipLen/currZoom*(zBuffer_y+1));
else
    tipLen =  xsize-startPix;
    x1 = 1;
    x2 = xsize;
    y1 = max(1,ysize/2 - tand(tipAngle)*tipLen/currZoom*(zBuffer_y+1));
    y2 = min(ysize,ysize/2 + tand(tipAngle)*tipLen/currZoom*(zBuffer_y+1));
end

if ~isempty(ax)
    set(ax,'XLim',[x1 x2])
    set(ax,'YLim',[y1,y2])                                    
    truesize(fig)
    img_ratio = x2/y2;
    pixPos_fig = getpixelposition(fig);
    pixPos_fig(4) = pixPos_fig(3)/img_ratio;
    screensize = get( groot, 'Screensize' );
    pixPos_fig(2) = screensize(4)/10;
    set(fig,'Position',pixPos_fig);
end