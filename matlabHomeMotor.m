function matlabHomeMotor(device,stepCnt)
%Home the stage by uploading arduino IDE hex code to
%arduino. This depends on using the shell escape function and the output
%from the Arduino IDE verbose compile/upload command must be modified for
%each new computer!  See here for a tutorial on finding this code: https://www.aranacorp.com/en/generating-and-uploading-hex-files-to-an-arduino/#:~:text=Generate%20the%20HEX%20file%20with%20the%20Arduino%20IDE,to%20which%20you%20want%20to%20upload%20the%20program.

%! "C:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude" "-CC:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega328p -carduino "-PCOM3" -b115200 -D "-Uflash:w:C:\Users\meyer\AppData\Local\Temp\arduino\sketches\E9ED96BD40BE23387324740CBBEF4358/2_matlab_move_motor_to_home.ino.hex:i"
% Open the serial port to read and write to the arduino
%Configure the ascii terminator for windows machines
configureTerminator(device,"CR/LF");
writeline(device,num2str(2));  %Tell the arduino to do switch case 1

while(isempty(readline(device)));end %Wait until the arduino has hit the limit switch
%Tell arduino how many steps back to start imaging position
writeline(device,num2str(stepCnt)) 
readline(device); %Check the step count
writeline(device,'Got it') %Tell arduino to proceed
while(isempty(readline(device)));end %Wait until the arduino has finished
end
