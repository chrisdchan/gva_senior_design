function [stepCnt] = matlabManualMotorControl(device,msg_text)
%Home the stage by uploading arduino IDE hex code to
%arduino. This depends on using the shell escape function and the output
%from the Arduino IDE verbose compile/upload command must be modified for
%each new computer!  See here for a tutorial on finding this code: https://www.aranacorp.com/en/generating-and-uploading-hex-files-to-an-arduino/#:~:text=Generate%20the%20HEX%20file%20with%20the%20Arduino%20IDE,to%20which%20you%20want%20to%20upload%20the%20program.

%Manually control the motor and send back how many steps were taken
%! "C:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude" "-CC:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega328p -carduino "-PCOM3" -b115200 -D "-Uflash:w:C:\Users\meyer\AppData\Local\Temp\arduino\sketches\43CFE9033EAB1003E72C6B3C9EEE7A4D/3_matlab_manual_control_motor.ino.hex:i"
% Open the serial port to read and write to the arduino
%Configure the ascii terminator for windows machines
configureTerminator(device,"CR/LF");
writeline(device,num2str(3));  %Tell the arduino to do switch case 3

while(isempty(readline(device)));end %Wait until the arduino is ready
% Message box telling user what to do.
tmp = msgbox(msg_text);
%Wait until the user closes the message box.
while (isgraphics(tmp));pause(.1);end
writeline(device,'Finished'); % Tell arduino i'm done
stepCnt = [];
%Get the number of steps arduino went
while (isempty(stepCnt))
    stepCnt = readline(device);
    pause(0.1);
end
%Convert to number
stepCnt = str2double(stepCnt);
disp(['Manual Motor Stepper Count:' num2str(stepCnt)]);
%Tell arduino we got it
writeline(device,'Got it');
while(isempty(readline(device)));end %Wait until the arduino is finished
disp(['Finished stepping'])
end

