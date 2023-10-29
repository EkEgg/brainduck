#include <cstddef>
#include <stdexcept>

namespace Memory
{
    void initialize(void);
    void destroy(void);

    void incrementCell(void);
    void decrementCell(void);

    void incrementIndex(void);
    void decrementIndex(void);

    void printCell(void);
    void readCell(void);

    bool isCellZero(void);

    class NoMemoryForProgramMemory : public std::runtime_error
    {
    public:
        NoMemoryForProgramMemory(size_t newMemorySize);
    };
}
