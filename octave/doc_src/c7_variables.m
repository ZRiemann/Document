echo off
#{
## 7.1 Global Variables
## A global variable is one that may be accessed anyware whith in
## Octave. A variable is declared global by using a global declaration
## statement.
global a
global a b
global c = 2
global d = 3 e f = 5
global x, y = 1
clear a
clear all

global x
function f()
  x = 1 # local variables x
endfunction
x
f()
x
function access_global()
  global x;
  x = 2 # global variable x
endfunction
access_global()
x

function pass_global(global_v)
  global_v = 0 # not modify global variable
endfunction

pass_global(x)
x

isglobal(x) ## error x, use "x"
isglobal("x")

## 7.2 Persistent Variables
## like C static variable in decleared function.
## A variable that has been declared /persistent/ within a function
## will retain its containts in memory between subsequent calls to
## the same function.
## The differenct between persistent variables and global variables
## is that persistent variables are local in scope to a particular
## function and are not visible elsewhere.
function count_calls()
  persistent calls = 0;
  persistent not_init;
  if(isempty(not_init))
    not_init = 1;
  endif
  printf("called %d times\n", ++calls);
endfunction
count_calls()
count_calls()

#}
echo on

## 7.3 Status Variables
## who[s|sline_format]
## who[s|sline_format] pattern ...
## who[s|sline_format] option pattern ...
## C = who[s|sline_format] ("pattern", ...)
## c = exist(name)
## c = exist(name, type)
##
## clear
## [options:-all|-exclusive|-functions|-global|-variables|-classes]
## pattern [...]
## clearvars pattren
## pack() # for compatbility of MATLAB, but does nothing in Octave
## type name ...
## which name ...
## what dir

echo off
