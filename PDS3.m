%Reads/Loads sound
[x,fs] = audioread('noti_res.wav');
x = x(:,1);
x_sound = audioplayer(x, fs);
%Values for echo
delay = 2000;
echo = 5;
alpha = 0.5;
size = delay * eco;
%Equations
y1 = 1 : size;
y2 = 1 : size; 
y3 = 1 : (delay*(echo*2)); 
%Impulse response H1
h1 = zeros(1, size);
h1(1 , 1) = 1;
h1(1 , delay) = alpha;
%Impulse response H2
h2 = zeros(1, size);
h2(1 , 1) = 1;
for k = 1 : echo;
    h2(1 , (k * delay)) = (1 - alpha ^ 2) * a ^ (k - 2);
end
%Impulse response H3
h3 = zeros(1, size);
h3(1 , 1) = - alpha;
for k = 1 : (echo * 2);
    h3(1 , (k * delay)) = (1 - alpha ^ 2) * alpha ^ (k - 2);
end
%Graphs
plot(y1,h1);
title('H1 Impulse Response');
plot(y2,h2);
title('H2 Impulse Response');
plot(y3,h3);
title('H3 Impulse Response');

