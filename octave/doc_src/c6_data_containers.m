echo off
#{

## 6 Data Container

## 6.1 Structures
## 6.1.1 Basic Usage and Examples
x.a = 1
x.b = [1, 2; 3, 4]
x.c = "string"
x
y = x
y
y.a = 2
x
y.d = x

function test_print_control()
  a.b.c.d.e = 1
  n = struct_levels_to_print(1, "local")
  a.b.c.d.e = 2

  n = print_struct_array_contents(true, "local")
endfunction
test_print_control()

c = 3 + 4i
function y = t_complex(c)
  y.re = real(c);
  y.im = imag(c);
endfunction
t_complex(c)
t_complex(rand(2) + rand(2) * I)
## 6.1.2 Structure Arrays
clear x
n = struct_levels_to_print(5)
x(1).a = "string1";
x(2).a = "string2";
x(1).b = 1;
x(2).b = 2;
x
x(1)
x(2)
x.a
x.b

[x.a] = deal ("new string1", "new string2");
x.a
x(3:4) = x(1:2);
x.a
x.b
[x([1,3]).a] = deal("other string1", "other string2");
x.a
size(x)
## 6.1.3 Creating Structures
clear all
a = "field2";
b = "long field with spaces (and funny char$)"
x.a = 1;
x.(a) = 2;
x.(b) = 3;
x

struct("field", 1, "field2", 2)
s = struct ("field1", {1, "one"}, "field2", {2, "two"},
            "field3", 3);
s.field1

struct ("field1", {{1, "one"}}, "field2", 2)

isstruct(s)
isstruct(1)
## 6.1.4 Manipulating Structures
clear -all
s = struct ("field1", {1, "one"}, "field2", {2, "two"},
            "field3", {{1, "one"}});
isstruct(s)
# numfields(s) ;octave 3.8.1 not support
fieldnames(s)
length(fieldnames(s))
#}
echo on

## 6.1.5 Processing Data in Structures
clear all
s = struct ("name", {"Peter", "Hannah", "Robert"},
            "age", {23, 16, 3});
c = struct2cell (s)
c(1,1,:)(:)

clear all
s.name = "Peter";
s.height = 185
s.age = 32;
#c = namedargs2cell(s)
c = {"name", "Peter", "height", 185, "Age", 42}
echo off
