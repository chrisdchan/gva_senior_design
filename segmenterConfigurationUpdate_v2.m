function segmenterConfigurationUpdate_v2(app)
    activeDir = pwd; %Get active directory.  
    %If current segmentation_parameters.mat file does not exist, make one.
    if ~exist([activeDir filesep 'segmentation_parameters.mat'],'file')
        segT = struct();
        segT.model = [5;6;7;8;9];
        segT.maxRadii = ones(5,1)*app.MaxColonyRadiuspixelsSpinner.Value;
        segT.minRadii = ones(5,1)*app.EstimatedColonyDiameterpixelsSpinner.Value;
        segT.tipMask = ones(5,1)*app.TipMaskSpinner.Value;
        segT.colonySensitivity = ones(5,1)*app.SensitivitySlider.Value;
        segT.colonyEdge = ones(5,1)*app.ColonyEdgeThresholdSlider.Value;
        segT = struct2table(segT);
        save([activeDir filesep 'segmentation_parameters.mat'],'segT')
    end
    %Load the segmentation parameters table
    load([activeDir filesep 'segmentation_parameters.mat'])
    %Find the current model
    modelNum = app.SegmenterModelSpinner.Value;
    %Update the table and save
    segT(segT.model==modelNum,'tipMask') = array2table(app.TipMaskSpinner.Value);
    segT(segT.model==modelNum,'maxRadii') = array2table(app.MaxColonyRadiuspixelsSpinner.Value);
    segT(segT.model==modelNum,'minRadii') = array2table(app.EstimatedColonyDiameterpixelsSpinner.Value);
    segT(segT.model==modelNum,'colonyEdge') = array2table(app.ColonyEdgeThresholdSlider.Value);
    segT(segT.model==modelNum,'colonySensitivity') = array2table(app.SensitivitySlider.Value);
    save([activeDir filesep 'segmentation_parameters.mat'],'segT')
    %Auto reapply segmentation to current figure by using a robot
    %to press the button for ginput!!!
    h1 = findall(groot,'type','figure');
    figure(h1(1))
    robot = java.awt.Robot;
    robot.keyPress(java.awt.event.KeyEvent.(['VK_' num2str(modelNum)]))
    robot.keyRelease(java.awt.event.KeyEvent.(['VK_' num2str(modelNum)]))
end
    
