%Reads/Loads sound
[x,fs] = audioread('noti_res.wav');
x_sound = audioplayer(x, fs);
play(x_sound);
x = x(:,1);
%Values for echo
delay = 2000;
echo = 5;
alpha = 0.5;
size = delay * echo;
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
    h2(1 , (k * delay)) = (1 - alpha ^ 2) * alpha ^ (k - 2);
end
%Impulse response H3
h3 = zeros(1, size);
h3(1 , 1) = - alpha;
for k = 1 : (echo * 2);
    h3(1 , (k * delay)) = (1 - alpha ^ 2) * alpha ^ (k - 2);
end
%Graphs impulse response
plot(y1,h1);
title('H1 Impulse Response');
plot(y2,h2);
title('H2 Impulse Response');
plot(y3,h3);
title('H3 Impulse Response');
%Fourier Transform of impulse response
x_fft = abs(fft(x, length(x)));
h1_fft = abs(fft(h1, length(x)));
h2_fft = abs(fft(h2, length(x)));
h3_fft = abs(fft(h3, length(x)));
w = linspace(0, fs/2, length(x) / 2);
%Graphs of Fourier Transform of impulse response
plot(w, h1_fft(1 : length(x) / 2), 'Linewidth', 4);
title('H1 Fourier Transform');
plot(w, h2_fft(1 : length(x) / 2), 'Linewidth', 4);
title('H2 Fourier Transform');
plot(w, h3_fft(1 : length(x) / 2), 'Linewidth', 4);
title('H3 Fourier Transform');
%Filters for echoed signal
y1_echo = filter(h1, -1, x);
y2_echo = filter(h2, -1, x);
y3_echo = filter(h3, -1, x);
%Graphs of signals
plot(x);
title('Original signal');
plot(y1_echo);
title('Y1 Echoed');
plot(y2_echo);
title('Y2 Echoed');
plot(y3_echo);
title('Y3 Echoed');
%Play echos
y1_sound = audioplayer(y1_echo, fs);
y2_sound = audioplayer(y2_echo, fs);
y3_sound = audioplayer(y3_echo, fs);
play(y1_sound);
play(y2_sound);
play(y3_sound);