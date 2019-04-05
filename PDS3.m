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
plot(w, h1_fft(1 : lenght(x) / 2), 'Linewidth', 4);
title('H1 Fourier Transform');
plot(w, h2_fft(1 : lenght(x) / 2), 'Linewidth', 4);
title('H2 Fourier Transform');
plot(w, h3_fft(1 : lenght(x) / 2), 'Linewidth', 4);
title('H3 Fourier Transform');