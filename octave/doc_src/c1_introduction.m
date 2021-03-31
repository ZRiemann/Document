echo off
echo on

%% Mathmatical constants
e
i
pi

%% Element caculations
exp(i*pi)

%% 1.2.2 Create Matrix
A=[1,2,3;4,5,6;7,8,9]
B = rand (3, 2)

%% 1.2.3 Matrix Arithmetric
2 * A
A * B
A' * A

## 1.2.4 Solving System of Linear Equations
## x1*H2 + x2*O2 --> H2O
## H: 2*x1 + 0*x2 --> 2
## O: 0*x1 + 2*x2 --> 1
A = [ 2, 0; 0, 2];
b = [2; 1];
x = A \ b

## 1.2.5 Intergrating Differential Equations(积分/微分方程)
## dx
## -- = f (x, t)
## dt
## x(t = t0) = x0
function xdot = f (x, t)
  r = 0.25;
  k = 1.4;
  a = 1.5;
  b = 0.16;
  c = 0.9;
  d = 0.8;

  xdot(1) = r*x(1)*(1 - x(1)/k) - a*x(1)*x(2)/(1 + b*x(1));
  xdot(2) = c*a*x(1)*x(2)/(1 + b*x(1)) - d*x(2);
endfunction

x0 = [1; 2];
t = linspace(0, 50, 200)';
x = lsode("f", x0, t);

## 1.2.6 Producting Graphical Output
## plot(t, x)
## print foo.pdf