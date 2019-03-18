#include <iostream>
#include <string>
#include "plugin.h"

int main()
{
    std::string template_PATH = ".";
    std::string cmd_hint = "Please input the code of the function y = foo(const int &x, int &y)";
    std::string function_cmd;
    plugin plugin_foo;
    std::cout << cmd_hint << std::endl;
    getline(std::cin, function_cmd);
    int x, y;
    std::cout << "Input the value of x:";
    std::cin >> x;
    try
    {
        plugin_foo.init(template_PATH, function_cmd);
        if(EXIT_SUCCESS == plugin_foo.exec(x, y))
            std::cout << "y = " << y << std::endl;
        else
            std::cerr << "ERROR" << std::endl;
        plugin_foo.del();
    }
    catch(...) {}
    return 0;
}

