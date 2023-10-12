function matlabMoveMotor(device,stepCnt,motorDirection)
%MOVE MOTOR a certain number of steps by uploading arduino IDE hex code to
%arduino. This depends on using the shell escape function and the output
%from the Arduino IDE verbose compile/upload command must be modified for
%each new computer!  See here for a tutorial on finding this code: https://www.aranacorp.com/en/generating-and-uploading-hex-files-to-an-arduino/#:~:text=Generate%20the%20HEX%20file%20with%20the%20Arduino%20IDE,to%20which%20you%20want%20to%20upload%20the%20program.

% Here is the arduino Hex code.  
%! "C:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude" "-CC:\Users\meyer\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega328p -carduino "-PCOM3" -b115200 -D "-Uflash:w:C:\Users\meyer\AppData\Local\Temp\arduino\sketches\FAD6F596B4C7D5EF8642720A52BB4AA8/1_matlab_move_motor_vector.ino.hex:i"
% Open the serial port to read and write to the arduino
%device = serialport(port,baud_rate);  %%% MUST come after the external call to avrdude!
%Configure the ascii terminator for windows machines
configureTerminator(device,"CR/LF");
writeline(device,num2str(1));  %Tell the arduino to do switch case 1

while(isempty(readline(device)));end %Wait until the arduino is ready
% Tell arduino which direction
writeline(device,num2str(motorDirection))
while(isempty(readline(device)));end %Wait until the arduino is ready
% Number of steps
writeline(device,num2str(stepCnt)) %Tell the arduino how many steps to take
while(isempty(readline(device)));end %Wait until the arduino is ready
writeline(device,'Got it') %Tell the arduino we got it and to proceed.
while(isempty(readline(device)));end %Wait until the arduino is finished

end