function CFUs = CFUcalculator(CFUs,apX,apY,rr,nn,assayVol,dilutionFactor,fudgeFactor,pixSz,channelL,collStart)
if length(apY)<5
    CFUs(rr,nn) = length(apY)*1000/assayVol * dilutionFactor;
else
    ys = pixSz*sort(apY - (collStart{rr,nn}-fudgeFactor/pixSz));
    ymin = max(0,ys(1));
    ymax = ys(length(ys));
    cnt = sum(ys>=ymin & ys<ymax); %Must be ys<ymax to avoid double counting
    ysub = ys(ys>=ymin & ys<=ymax);
    try
        CFUs(rr,nn) = cnt./trapz(ysub,3*ysub.^2/channelL^3) / (assayVol/1000) * dilutionFactor;
    catch
        disp('Check your points - could not calculate');
    end
end
