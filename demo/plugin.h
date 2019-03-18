#pragma once
#include <string>

typedef int INPUT_TYPE;
typedef int OUTPUT_TYPE;

class plugin
{
private:
    std::string template_PATH;
    void *pHandle;
public:
    void init(std::string template_PATH, std::string function_cmd);
    int exec(const INPUT_TYPE &x, OUTPUT_TYPE &y);
    void del();
};
