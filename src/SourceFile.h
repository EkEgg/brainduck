#include <fstream>
#include <stdexcept>

namespace SourceFile
{
    using WordPositionType = std::streampos;

    void open(void);
    void close(void);

    char currentWord(void);
    void goToNextWord(void);

    WordPositionType currentWordPosition(void);
    void goToWord(const WordPositionType& position);

    bool isEnded(void);

    class SourceFileCouldNotBeOpenedError : public std::runtime_error
    {
    public:
        SourceFileCouldNotBeOpenedError(const char* sourceFilePath);
    };
}
