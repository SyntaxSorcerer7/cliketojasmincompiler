# Simple Jsamin Compiler 

In this project we have a very simple c-like programming language, that gets compiled into jasmin code ([more information about jasmin](http://jasmin.sourceforge.net/guide.html)). 

Jasmin is an assembler for the Java Virtual Machine. It takes ASCII descriptions of Java classes, written in a simple assembler-like syntax using the Java Virtual Machine instruction set. It converts them into binary Java class files, suitable for loading by a Java runtime system.

The parser is written in c++ by using bison ([more information about bison](https://aquamentus.com/flex_bison.html)). While parsing the source code, an abstract syntax tree will be created. The syntax tree will be optimized before, creating the output. In the end the jasmin code can be translated into jvm code by using jasmin.jar.  

To start just clone the repo and call `bash ./run.sh`.

Here is a simple program written in the language: 
```
n = 8;
sum=0;
product = 1+0*5+0;
i=1*1;
while (i < n) {
    if (i % 100 > 0) { } else { print(i); }
    sum = sum + i;
    product = product * i;
    i = i + 1;
}
print(sum);
print(product);
```