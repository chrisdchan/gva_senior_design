function [well2examine] = platemap_check(CFUs,collList,activeDir)

screensize = get( groot, 'Screensize' );
fig = figure('color','w','Units','pixels','position',[1 screensize(4)/2 screensize(3)/3 screensize(4)/1600*400]);
tmp = 'A':'Z';
yvalues = num2cell(tmp(1:size(collList,1)));
xvalues = 1:size(collList,2);
lCFUs = log10(CFUs);
colormap(turbo)
imAlpha = ones(size(CFUs));
imAlpha(isnan(lCFUs)) = 0;
imagesc(lCFUs,'AlphaData',imAlpha)
h = colorbar();
h.Label.String = 'log10(CFUs)';
xticks(1:length(xvalues))
yticks(1:length(yvalues))
xticklabels(xvalues)
yticklabels(yvalues)
title({'Check CFU counts. Wells with 0 colonies automatically set to 1/2 LOD.', 'Nan = pipette error', 'Right click to go back to a specific well.','f to accept and finish'})
set(gca,'Color','k')
if verLessThan('matlab','9.12')
    % -- Code to run in MATLAB R2021b and earlier here --
    if max(lCFUs(:)) ~= -Inf
        caxis([0,max(lCFUs(:))])
    end
else
    % -- Code to run in MATLAB R2022a and later here --
    if max(lCFUs(:)) ~= -Inf
        clim([0,max(lCFUs(:))])
    end
end

[x,y] = meshgrid(1:size(collList,2),1:size(collList,1));
labels = num2str(lCFUs(:),'%.2f');
text(x(:),y(:),labels,'horizontalalignment','center','verticalalignment','middle','color','w');
try
    [x, y, button] = ginput(1);
end
    
%If they closed the figure
if isgraphics(fig)
    while (button ~= 1) && (button ~= 102)
        [x, y, button] = ginput(1);
        title({'Incorrect Button', 'Left click to go back to a specific well.','f to accept and finish'})
    end
    if button == 1
        x = round(x);
        y = round(y);
        well2examine = collList{y,x};
        disp('Selected')
        disp(collList{y,x})
    else
        well2examine = [];
    end
    saveas(gca,[activeDir filesep 'PlateMap.png'])
    %saveas(gca,[activeDir filesep 'PlateMap.fig'])
    try
        close(fig)
    end
else
    well2examine = [];    
end
