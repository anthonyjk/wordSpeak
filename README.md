# wordSpeak
 An alphanumeric only programming language

## Types

**Strings**

Strings in wordSpeak are declared with the keyword 'words' and closed with 'endwords'

Example:

```words This is a string endwords```

**Integers**

Since wordSpeak only allows alphanumeric characters to be processed, only integers can be processed in wordSpeak

Example:

Read as 1: ```1```

Read as 1: ```1.314```

## Syntax

**Comments**

Any line that begins with a non-alphanumeric character will be a comment as it is ignored.

Example:

```
- This is a comment becaue it begins with non-alphanumeric character '-'
```

**Variable Assignment**

To assign a variable in wordSpeak:

the keyword ```give``` is used to point to which variable is being assigned.

the keyword ```as``` is used to point to the value assigned to the variable.

Example:

```give myString as words Hello World endwords```

```give myInt as 1```

**Say Statement**

To output to the console in wordSpeak, the keyword ```say``` is used.

Example:

```
say words Hello World endwords
```

**Addition & Subtraction**

Math is done with the ```plus``` and ```minus``` keywords

Example:

```
give x as 1
give y as x plus 3
give z as y minus 2
```

**Conditionals**

Conditions are used in wordSpeak with the ```if``` or the ```while``` keywords.

Only integers can be compared in conditions, and there are four kinds of conditions that can be used:

x greater than y: ```x more y```

x less than y: ```x less y```

x equal to y: ```x same y```

x is not equal to y: ```x not y```

**If Statement**

In WordSpeak, if statements are started with the ```if``` keyword and the contents are contained by the ```open``` and ```close``` keywords.

Example:

```
if x more y open
 say words The x variable is greater than the y variable endwords
close
```

**While Statement**

While statements have the same syntax as if statements, but will keep running their contents until the condition is no longer met.

Example:

```
give x as 0
give cons as 3

--First ten y points of y = 3x + 3--

while x less 10 open
 give y as x plus x plus x plus cons
 say y

 give x as x plus 1
close
```

**Future Features**

wordSpeak may have more features added in the future.
