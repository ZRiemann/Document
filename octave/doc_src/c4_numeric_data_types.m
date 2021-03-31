echo on

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
idivide()