echo off
#{
## 8 Expressions
## An expression evaluates a value.

## 8.1 Index Expressions
## An index expression allows you to reference or extract selected
## element of a vactor, a matrix(2-d), or a higher-dimensional array.
##
## Indices may be scalars, vectors, ranges, or the special operator
## ":". An index expression consists of a set of parentheses
## encloseing M expressions separated by commas.
##
## 1) all components are scalars
## 2) the dimensionality of the index expressoin M
##    is equal to the dimensionality of the object it is applied to.
A = reshape(1:8, 2, 2, 2)
## second row
## first column
## second slice
A(2, 1, 2)
A([1, 2], 1, 2)
A([1; 2], 1, 2)
A([1; 2], 1, [1, 2])
A([1,2], [1,2], [1,2])
A(1, [2, 1, 1], 1)
A(ones(2,2), 1, 1)
A(1, [1,2])
A(1, 1:2)
A(1,:)
A(:)

A(1:end/2)
a=size(A)
a(end) = []; #delete element
a
length(A)
size(A)
#}
echo on

## 8.1.1 Advanced Indexing
## sub2ind
A = reshape(1:8, 2, 2, 2)
echo off
