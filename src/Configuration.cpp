#include "Configuration.h"
#include <cstring>
#include <sstream>

char* chosenSourceFilePath;

Configuration::MemoryType chosenMemoryType;

size_t chosenInitialMemorySize;

long double chosenMemoryGrowthFactor;

void Configuration::initialize(int argc, char** argv)
{
    bool wasSourceFilePathBeenSet = false;
    bool wasInitialMemorySizeSpecified = false;
    chosenMemoryType = DEFAULT_MEMORY_TYPE;
    chosenMemoryGrowthFactor = DEFAULT_MEMORY_GROWTH_FACTOR;
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] != '-')
        {
            if(wasSourceFilePathBeenSet)
            {
                throw MultipleSourceFilesError(chosenSourceFilePath, argv[i]);
            }
            chosenSourceFilePath = argv[i];
            wasSourceFilePathBeenSet = true;
            continue;
        }
        if(std::strcmp(argv[i], "--memory-type") == 0 || std::strcmp(argv[i], "--mt") == 0)
        {
            i++;
            if(i == argc) throw MissingArgumentValueError(argv[i-1]);
            if(std::strcmp(argv[i], "expanding") == 0 || std::strcmp(argv[i], "e") == 0)
            {
                chosenMemoryType = MemoryType::EXPANDING;
                continue;
            }
            if(std::strcmp(argv[i], "circular") == 0 || std::strcmp(argv[i], "c") == 0)
            {
                chosenMemoryType = MemoryType::CIRCULAR;
                continue;
            }
            throw InvalidArgumentValueError(argv[i-1], argv[i], "expanding; e; circular; c");
        }
        if(std::strcmp(argv[i], "--initial-memory-size") == 0 || std::strcmp(argv[i], "--memory-size") == 0
                || std::strcmp(argv[i], "--ims") == 0 || std::strcmp(argv[i], "--ms") == 0)
        {
            std::istringstream argumentValueStream;
            i++;
            if(i == argc) throw MissingArgumentValueError(argv[i-1]);
            argumentValueStream = std::istringstream(argv[i]);
            argumentValueStream >> chosenInitialMemorySize;
            if(!argumentValueStream.fail() && chosenInitialMemorySize != 0) 
            {
                wasInitialMemorySizeSpecified = true;
                continue;
            }
            throw InvalidArgumentValueError(argv[i-1], argv[i], "non-zero unsigned integer");
        }
        if(std::strcmp(argv[i], "--memory-growth-factor") == 0 || std::strcmp(argv[i], "--mgf") == 0)
        {
            std::istringstream argumentValueStream;
            i++;
            if(i == argc) throw MissingArgumentValueError(argv[i-1]);
            argumentValueStream = std::istringstream(argv[i]);
            argumentValueStream >> chosenMemoryGrowthFactor;
            if(!argumentValueStream.fail() && chosenMemoryGrowthFactor > 1.0F) continue;
            throw InvalidArgumentValueError(argv[i-1], argv[i], "real number greater than 1.0");
        }
        throw InvalidArgumentError(argv[i]);
    }
    if(!wasSourceFilePathBeenSet) throw NoSourceFileError();
    if(!wasInitialMemorySizeSpecified)
    {
        chosenInitialMemorySize = DEFAULT_INITIAL_MEMORY_SIZE.at(chosenMemoryType);
    }
}

const char* Configuration::sourceFilePath(void)
{
    return chosenSourceFilePath;
}

Configuration::MemoryType Configuration::memoryType(void)
{
    return chosenMemoryType;
}

size_t Configuration::initialMemorySize(void)
{
    return chosenInitialMemorySize;
}

long double Configuration::memoryGrowthFactor(void)
{
    return chosenMemoryGrowthFactor;
}

Configuration::MultipleSourceFilesError::MultipleSourceFilesError(const char* firstSourceFilePath, const char* secondSourceFilePath) :
        std::logic_error((std::ostringstream() << "Two source files were provided:\n"
                                               << firstSourceFilePath  << '\n'
                                               << secondSourceFilePath << '\n'
                                               << "Expected only one.").str().c_str())
        {}

Configuration::NoSourceFileError::NoSourceFileError(void) : std::logic_error("No source file was provided.") {}

Configuration::InvalidArgumentError::InvalidArgumentError(const char* argument) :
        std::logic_error((std::ostringstream() << "Invalid argument " << argument << '.').str().c_str())
        {}

Configuration::MissingArgumentValueError::MissingArgumentValueError(const char* argument) :
        std::logic_error((std::ostringstream() << "Missing value for argument " << argument << '.').str().c_str())
        {}

Configuration::InvalidArgumentValueError::InvalidArgumentValueError(const char* argument, const char* receivedValue, const char* expectedValue) :
        std::logic_error((std::ostringstream() << "Invalid value for argument " << argument << ".\n"
                                               << "Got: " << receivedValue  << '\n'
                                               << "Expected: " << expectedValue).str().c_str())
        {}
