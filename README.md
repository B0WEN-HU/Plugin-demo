# Plugin-demo
A demo of plugin structure

```Shell
sh build_and_run.sh to run the main_exe
```

The demo accept standard input, and compile and link the foo.cpp into dynamic library named libfoo.so at runtime, then load the dynamic library to excute the foo.cpp by plugin.cpp.

The structure is like:
```
main.cpp
└─── plugin.cpp
     └─── foo.cpp
```
