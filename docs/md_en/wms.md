WMS
===

## About WMS

WMS is a scripting language of the OpenNovel engine.

OpenNovel's scenario files focus on how ordinary stories flow, and they are incapable of handling complex logic projects.
WMS should be used for such purposes.
Calling a WMS file from a scenario file makes it possible to write complex logic.

## Basics

A script to change a color of a message box is the following.

```
func main() {
    s2_set_config("msgbox.font.r", "128");
    s2_set_config("msgbox.font.g", "128");
    s2_set_config("msgbox.font.b", "128");
}
```

Use this script from `init.txt`.

```
We will change the color.

@wms change-color.txt

The color was changed.
```

## Syntax

### A program start from the main() function

```
func main() {
    // This is a comment.
    print("Hello, world!");
}
```

### A function can call other functions

```
func main() {
    foo(0, 1, 2);
}

func foo(a, b, c) {
    return a + b + c;
}
```

### Indirect call is possible via a string variable

```
func main() {
    myfunc = "foo";
    myfunc(0, 1, 2);
}

func foo(a, b, c) {
    return a + b + c;
}

func myfunc(a, b, c) {
    // This function will not be called. foo() will be called instead.
}
```

### Types and Variables

A program can use integer, floating point, string, or array variables.

```
func main() {
    // Integer
    a = 1;
    if(isint(a)) {
        print("a is int");
    }

    // Floating-point
    b = 1.0;
    if(isfloat(b)) {
        print("b is float");
    }

    // String
    c = "string";
    if(isstr(c)) {
        print("c is string");
    }

    // Array (with integer index)
    d[0] = 0;
    if(isarray(d)) {
        print("d is array");
    }

    // Array (with string index)
    e["abc"] = 0;
    if(isarray(e)) {
        print("e is array");
    }

    // Array of array
    f["key"] = e;
}
```

### Calculations

Integer and floating point values can be added, subtracted, multiplied, or divided.

For integers:

```
a = 1;
b = 2;
c = a + b;
// a += b; form is not supported.
```

For floating-points:
```
a = 1.0;
b = 2.0;
c = a + b;
```

For integer and floating-point:
```
a = 1;
b = 2.0;
c = a + b; // c is floating-point (promoted)
```

For integer reminder:
```
a = 3;
b = a % 2; // The result is the reminder of 3/2, i.e., 1
```

Strings can be concatenated by a plus operator:

```
a = "aaa";
b = "bbb";
c = a + b;
```

A string + an integer will be a string, but an integer + a string will be an integer.

### For loop with a simple counter

Repeats for the specified count:

```
func main() {
    for(i in 0..9) {
        print(i);
    }
}
```

### Repeat for each array element:

```
func main() {
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    for(v in a) {
        print(v);
    }
}
```

### Repeat for each array key-value pair:

```
func main() {
    a["key1"] = 0;
    a["key2"] = 1;
    a["key3"] = 2;

    for(k, v in a) {
        print(k + "=" + v);
    }
}
```

### The "while" loop:

```
func main() {
    a = 10;
    while (a > 0) {
        print(a);
        a = a - 1;
    }
}
```

### The break and continue statements:

```
func main() {
    for(i in 0..9) {
        if(i == 2) {
            continue;
        }
        if(i == 7) {
            break;
        }
    }
}
```

### Branches

if - else if - else

```
func main() {
    a = foo();
    if(a > 10) {
        print("a > 10");
    } else if(a > 5) {
        print("a > 5");
    } else {
        print("else");
    }
}

func foo() {
    return 6;
}
```

### Array

An array element has a key (index), and key can be one of these: integer, floating point, or string type.
Elements can have different key types in an array.

To make an array, assign a value to a variable by [key] syntax.

```
func main() {
    a[0] = 0;
    print(a);
}
```

To remove an array element, use remove().

```
func main() {
    a[0] = 0;
    remove(a, 0);
    print(a);
}
```

You can use `size()` to get the number of array elements.

```
func main() {
    a[0] = 0;
    print(size(a));
}
```

### Type Conversion

Integer to string:

```
s = "" + 123;
```

Floating point to string:

```
s = "" + 1.23;
```

Integer to floating point:

```
f = 0.0 + 123;
```

String to integer:

```
i = 0 + "123";
```

String to floating point:

```
f = 0.0 + "1.23";
```

That's all about the grammer.

## Calling OpenNovel Engine

Main game engine provides some functions to the plugin language.
Those functions have the s2_ prefix in their names.

### Getting a flag variable

`s2_get_variable()` is a function to get a flag value.

```
value = s2_get_variable(100);
```

### Setting a flag value

`s2_set_variable()` is a function to set a flag value.

```
s2_set_variable(100, 1);
```

### Getting a random number

`s2_random()` returns a random number between `0` and `9999`.

```
value = s2_random();
```

### Overwriting a config

`s2_set_config()` overwrites a config.

```
s2_set_config("msgbox.x", "0");
s2_set_config("msgbox.speed", "20.0");
```

<hr>

## Examples


### Get a flag variable value, calculate, then write back a flag

```
func main() {
    // Get variable values.
    a = s2_get_variable(0);
    b = s2_get_variable(1);
    c = s2_get_variable(2);

    // Calc the sum.
    sum = a + b + c;

    // Write to $100.
    s2_set_variable(100, sum);
}
```

### Getting real calendar date

get-datetime.txt

```
func main() {
    // Get date.
    now_y = s2_get_year();
    now_mo = s2_get_month();
    now_d = s2_get_day();
    now_h = s2_get_hour();
    now_mi = s2_get_minute();
    now_s = s2_get_second();
    now_w = s2_get_wday(); // 0=Sun

    // Write back.
    s2_set_variable(1, now_mo);
    s2_set_variable(2, now_d);
}
```

In a story file:

```
@wms get-datetime.txt

@if $1 == 4 on_april
@goto not_birthday

:on_april
@if $2 == 14 birthday
@goto not_birthday

:birthday
Happy birthday!
@goto common

:not_birthday
Regular date.

:common
# Common
```
