echo off
#{
## A numberic constant may be
## a scalar, a vector, a metrix and
## it may contain complex values.
## :sizemax() 2,147,483,646 size of array
## :class(a) Data type
42
0x2A
# 0B10101010
# 0b10_1010
round(42.1)
round(42.6)

.105
1.05e-1
0.105
0.00105e+2

3+42i
3+42I
3 + 42j
3 + 42J

double(3)

complex(1)
complex(1,2)
# complex(1,2,3,4) error
complex([1,2], [3,4])

## 4.1 Matrices
A = [1,2; 3, 4]
## B = [1, 2; 3] error
[A, A]
[sin(pi)]
a = 1
[1 a']

sizemax()
intmax()
intmax

output_precision()

old = split_long_rows()
rand(2, 10)

split_long_rows(1, "local")
rand(2, 10)
split_long_rows(old)

## 4.2 Ranges
## write a row vector
1:5
[1:3:5]
0:0.1:1

## 4.3 Single Precision Data Types
sngl = single(rand(2,2))
class(sngl)
class(A)
B = ones(2,2, "single")
class(B)

## 4.4 Integer Data Types
## isfloat, ischar, islogical, isstring, isnumeric, isa.
## uint8, int16, uint16, int32, uint32, int64, uint64. 
f = rand(2,2)
i = int32(f)
intmax("int32")
intmax("int8")
intmax("uint8")
flintmax("double")

## 4.4.1 Integer Arithmetic
## :idivide (x, y, op)
idivide (int8 ([-3, 3]), int8 (4), "fix")
idivide (int8 ([-3, 3]), int8 (4), "round")
idivide (int8 ([-3, 3]), int8 (4), "floor")
idivide (int8 ([-3, 3]), int8 (4), "ceil")

## 4.5 Bit Manipulations(二进制操作)
## C = bitset(A, n) min x is 1, NOT 0
## C = bitset(A, n, val)
## :bit[and|or|xor](x,y)
## :bitcmp(A, k) bit complement
## :bitshift(a, k, n)
x = bitset(1, 3)
x = bitset([1, 2, 3], 3:5)
dec2bin(x)
x = bitset(0xf, 2, 0)
dec2bin(x)

bitget(100, 8:-1:1)
bitand(3,8)
bitand(3,2)
bitor(3,8)
bitor(3,2)
bitxor(3,8)
bitxor(3,2)

bitcmp(7,4)

x = eye(3)
bitshift(x, 1)

## 4.6 Logical Values
## true/false
## a & b, a | b, !a
data = [1, 2; 3, 4]
idx = (data <= 2)
data(idx)

logical(pi)
logical(0)
logical(true)
logical(false)
true(3)
false(2)
## 4.7 Promotion and Demotion Data Types
## Mixed Operation Result
## double OP single single
## double OP integer integer
## double OP char double
## double OP logical double
## single OP integer integer
## single OP char single
## single OP logical single

uint8(255) + 1
uint8(254) + 1
x = double(1)
y = int32(1)
class(x)
class(y)
z = x * y
class(z)
#}
echo on
## 4.8 Predicates for Numbric Objects
## isxxx(x)
## :isnumeric(x)
##  isinteger, isfloat, isreal, iscomplex, ischar, islogical, isstring, iscell, isstruct, isa. 

function a = z_abs (x)
  if (isreal (x))
    a = sign (x) .* x;
  elseif (iscomplex (x))
    a = sqrt (real(x).^2 + imag(x).^2);
  endif
endfunction

z_abs(-3.14)
z_abs(3.14)
z_abs(3 + 4i)

echo off