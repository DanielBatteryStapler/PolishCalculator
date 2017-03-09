#PolishCalculator
A command-line polish-style calculator for ncurses compatible operating systems

Works on an "operator first" basis, so 1 + 2 is written as +1 2

Supports most operators

Can store numbers as either long doubles, or as fraction; it will convert from fraction to floating point as needed

#Usage:
>PolishCalculator <expression>
will just execute the following expression, already has the variables p (pi) and e (e) set to approximate values 
>PolishCalculator
will open up a calculator command line where you can just directly type in the expressions to calculate
also supports setting custom varibles, unlike the single expression version

#Valid operators:
##Single Operand:
Convert to decimal: d - Converts the operand to a floating point type form a fraciton if it is not already one. 1/3 -> 0.33..

Negative: _ - negates the operand(this means that negative numbers are written as _x not -x). 23 -> -23

Square Root: r - will attempt to keep it in exact fraction form, many convert to decimal in unsuccesssful

Sine: s

Consine: c

Tangent: t

Inverse Sine: S

Inverse Consine: C

Inverse Tangent: T

##Double Operand:

Union: u - combines two numbers into a set of those numbers. u2 3 -> {2, 3}

Add: +

Subtract: -

Multiply: *

Divide: /

Modulo: % - programming style modulo

Power: ^

Log: l

#Sets
A single "number"(or variable) can actually exist as a set of numbers, and they can be used in normal mathematical expression as you'd expect. For example: +u1 2u3 4 = {4, 5, 6} (written in normals maths as {1, 2} + {3, 4} = {4, 5, 6}). As you can see, it will find the sum of every number in the first set with every number in the second set, removng any repeats. It does discriminate based on the fractionness of the number. (i.e. 4.0 and 4 will not combine into a single number because one is a floating point and the other is considered a fraction)

#Decimal(Floating Point) Vs Fractions
whenever you type in a number, even in the form x.x (e.g. 12.2) it will convert it to the fractional equivalent (61/5). The only way it converts to a decimal is explicitly(with the decimal operator) or automatically(trying to find the square root of 2).

#Why?
Because of the fact that polish notation is completely unambiguous, there is no need for parenthesis. Also because having a simple, yet powerful, calculator on the command line ready at any time is very useful
