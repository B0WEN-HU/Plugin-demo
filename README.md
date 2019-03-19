# Plugin-demo
A demo of plugin structure

Execute the following command in the shell to run the program.
``` Shell
sh build_and_run.sh
```

The program will give the hint.
``` C++
Please input the code of the function y = foo(const int &x, int &y)
```
Input line will be the body of the function `foo.cpp`. For example, enter `y = 7 * x + 11;`.
Then, the program will ask for the value of `x`.
``` C++
Input the value of x:
```
Enter `3` for example.
The program will give the answer.
``` C++
y = 32
```

The demo accept standard input as the body part of foo.cpp, compile and link the foo.cpp into dynamic library named libfoo.so at runtime, then load the dynamic library to excute the foo.cpp by plugin.cpp. Declaration part of the function is placed in `_foo.template`.


The structure is like:
```
main.cpp
├─── plugin.h
└─── plugin.cpp
     ├─── foo.h
     ├─── _foo.template
     └─── foo.cpp
```
