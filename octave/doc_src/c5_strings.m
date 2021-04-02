echo off
#{
## 5 Strings
## Since the single-quote mark is also used for the transpose operator
## it is best to use double-quote marks to denote strings.

## concatenated strings
["foo", "bar", "baz"]

## 5.1 Escape Sequences in Stirng Constants
double("\n")
double('\n')
double("\\n")
x = '\n'
y = "\n"
is_dq_string(x)
is_sq_string(x)

is_dq_string(y)
is_sq_string(y)

## 5.2 Character Arrays
collection = ["String #1", "String #2"]
collection = ["String #1"; "String #2"]

## 5.3 Creating Strings
a = blanks(3)
class(a)
length(a)
double(a)

## 5.3.1 Concatenating Strings
## :newline == "\n"
## 3.8 notsupport, 6.x support
## joined_string = [newline "line1" newline "line2"]

## 5.4 Comparing Strings
GNU = "GNU's Not UNIX"
spaces = (GNU == " ")

## 5.5 Manipulating Strings
## :deblank(s) Remove trailing whitespace and nulls from s.
deblank(["   abc   "; "   def   "])
## :strtrim(s) Remove leading and trailing whitespace from s.
strtrim("  \tabc   \n")
## :strtrunc(s, n)
strtrunc("abcdefghijlmn", 5)
## :strfind(str, pattern)
## :strjoin(cstr, delimiter)
strjoin({"octave", "Scilab", "Lush", "Yoric"}, " * ")
strsplit("a b c")

## 5.6 String Conversiongs
hex2dec("FF")
hex2dec("0xFF")
#hex2dec(1100) must (cell)string
bin2dec("1100")
dec2bin(12)
num2hex ([-1, 1, e, Inf])

#}
echo on

## 5.7 Character Class Functions
isalpha("!Q@WERT^Y&")

echo off