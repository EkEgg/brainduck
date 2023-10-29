#include <stdexcept>

namespace Interpreter
{
    void execute(void);
    void finish(void);

    class MissingMatchingJumpBackwardsError : public std::runtime_error
    {
    public:
        MissingMatchingJumpBackwardsError(size_t jumpForwardPosition);
    };

    class MissingMatchingJumpForwardError : public std::runtime_error
    {
    public:
        MissingMatchingJumpForwardError(size_t jumpBackwardsPosition);
    };

    class NoMemoryForLoopStack : public std::runtime_error
    {
    public:
        NoMemoryForLoopStack(size_t jumpForwardPosition);
    };
}
