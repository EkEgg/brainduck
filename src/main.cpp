#include "Configuration.h"
#include "SourceFile.h"
#include "Interpreter.h"
#include "Memory.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
    try
    {
        Configuration::initialize(argc, argv);
        SourceFile::open();
        Memory::initialize();
        Interpreter::execute();
        Interpreter::finish();
        Memory::destroy();
        SourceFile::close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr << "An unknown error occurred. Rethrowing exception." << std::endl;
        std::rethrow_exception(std::current_exception());
        return 2;
    }
    return 0;
}
