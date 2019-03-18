#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include "plugin.h"
#include "foo.h"

typedef void (*Pfoo_FUNC)(const INPUT_TYPE &, OUTPUT_TYPE &);

void plugin::init(std::string template_PATH, std::string function_cmd)
{
    std::ifstream template_fin;
    std::ofstream foocpp_fout;
    std::string template_foo;
    std::string template_file = template_PATH + "/_foo.template";
    std::string function_file = template_PATH + "/foo.cpp";
    //open the tampalte file and foo.cpp file
    template_fin.open(template_file.c_str(), std::ios::in);
    foocpp_fout.open(function_file.c_str(), std::ios::out|std::ios::trunc);
    
    if(template_fin.is_open() && foocpp_fout.is_open())
    {
        //initialize the foo.cpp code
        getline(template_fin, template_foo, '$');
        foocpp_fout << template_foo << std::endl;
        foocpp_fout << "{" << std::endl;
        foocpp_fout << function_cmd <<std::endl;
        foocpp_fout << "}" << std::endl;
        
        //close files
        foocpp_fout.close();
        template_fin.close();
        
        //build foo.cpp with compiler
        system("rm -rf lib*");
        system("g++ -Wall -fPIC -c foo.cpp");
        system("g++ -shared foo.o -o libfoo.so");
        system("rm -rf *.o");
        //system("sh ./build_foo.sh");
    }
    else
        std::cerr << "ERROR:Cannot open file foo.template or foo.cpp" << std::endl;
}

int plugin::exec(const INPUT_TYPE &x, OUTPUT_TYPE &y)
{
    //load the library
    pHandle = dlopen("libfoo.so", RTLD_LAZY);
    if(NULL == pHandle)
    {
        std::cerr << "ERROR:Cannot load the library" << std::endl;
        return EXIT_FAILURE;
    }

    //find the library symbol
    Pfoo_FUNC pfoo = (Pfoo_FUNC)dlsym(pHandle, "foo");
    if(NULL == pfoo)
    {
        std::cerr << "ERROR:Cannot find the function" << std::endl;
        dlclose(pHandle);
        pHandle = NULL;
        return EXIT_FAILURE;
    }

    //execute foo function
    try
    {
        pfoo(x,y);
    }
    catch(...)
    {
        //handle the exception
        std::cerr << "ERROR:Exception raised by function";
        return EXIT_FAILURE;
    }

    
    return EXIT_SUCCESS;
}

void plugin::del()
{
    template_PATH = "";
    
    //close the library
    dlclose(pHandle);
    pHandle = NULL;
}

