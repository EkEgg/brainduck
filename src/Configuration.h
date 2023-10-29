#include <unordered_map>
#include <cstddef>
#include <stdexcept>
#include <forward_list>

namespace Configuration
{
    enum class MemoryType
    {
        EXPANDING,
        CIRCULAR
    };

    const MemoryType DEFAULT_MEMORY_TYPE = MemoryType::EXPANDING;

    const std::unordered_map<MemoryType, size_t> DEFAULT_INITIAL_MEMORY_SIZE =
    {
        {Configuration::MemoryType::EXPANDING,  1024},
        {Configuration::MemoryType::CIRCULAR,  30000}
    };
    
    const long double DEFAULT_MEMORY_GROWTH_FACTOR = 1.5F;

    void initialize(int argc, char** argv);

    const char* sourceFilePath(void);

    MemoryType memoryType(void);

    size_t initialMemorySize(void);

    long double memoryGrowthFactor(void);

    class MultipleSourceFilesError : public std::logic_error
    {
    public:
        MultipleSourceFilesError(const char* firstSourceFilePath, const char* secondSourceFilePath);
    };

    class NoSourceFileError : public std::logic_error
    {
    public:
        NoSourceFileError(void);
    };

    class InvalidArgumentError : public std::logic_error
    {
    public:
        InvalidArgumentError(const char* argument);
    };

    class MissingArgumentValueError : public std::logic_error
    {
    public:
        MissingArgumentValueError(const char* argument);
    };

    class InvalidArgumentValueError : public std::logic_error
    {
    public:
        InvalidArgumentValueError(const char* argument, const char* receivedValue, const char* expectedValue);
    };
}
