echo on

## 3.1 Built-in Data Types
## 3.1.1 Number Objects
## Real, complex and integer scalars and matrices.
## Floating point numberic data is currently stored as double
## precision numbers.
realmin
realmax
eps

## 3.1.2 Missing Data
## Represent missing data explicitly using NA(short for "Not
## Available"). Only support floating point numbers. NaN
NA
NA(2)
NA(2,3)
NA(2,3,4)
NA(2,3,4,5);

a = [13, Inf, NA, NaN]
isna(a)
isnan(a)
isinf(a)
isfinite(a)

## 3.1.3 String Objects
'String with single-quote'
"String with double-quote"

## 3.1.4 User-defined Data Types
## see 6.1 Structures
## 3.1.5 Cell Array Objects
## see Cell Arrays

## 3.2 User-defined Data types
## 3.3 Object Sizes
## :ndims(a) return the numberof dimensions of a.
##           all objects have a minimum of two dimensions
##           and row vectors are left unchanged.
##           for compatibility with MATLAB
## :columns(a)
## :rows(a)
## :numel(a)
## :length(a) N-dims equivalent to max (size (a)
## :size(a)
## :isempty(a)
## :isnull(x)
## :sizeof(val)
## :size_equal(a,b,...)
## :squeeze(x)
a = ones(4,1,2,1)
b = ones(3,2,2,2)
ndims(a)
ndims(b)
columns(a)
columns(b)
rows(a)
rows(b)
numel(a)
numel(b)
length(a)
length(b)
size(a)
size(b)
sizeof(a)
sizeof(b)
isempty(a)
isempty([])
isempty("")
isnull([])
isnull("")