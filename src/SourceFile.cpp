#include "SourceFile.h"
#include "Configuration.h"
#include <sstream>

std::ifstream programStream;

void SourceFile::open(void)
{
    programStream.open(Configuration::sourceFilePath());
    if(programStream.fail())
    {
        throw SourceFileCouldNotBeOpenedError(Configuration::sourceFilePath());
    }
}

void SourceFile::close(void)
{
    programStream.close();
}

char SourceFile::currentWord(void)
{
    return programStream.peek();
}

void SourceFile::goToNextWord(void)
{
    programStream.ignore();
}

SourceFile::WordPositionType SourceFile::currentWordPosition(void)
{
    return programStream.tellg();
}

void SourceFile::goToWord(const SourceFile::WordPositionType& position)
{
    programStream.seekg(position);
}

bool SourceFile::isEnded(void)
{
    programStream.peek();
    return programStream.eof();
}

SourceFile::SourceFileCouldNotBeOpenedError::SourceFileCouldNotBeOpenedError(const char* sourceFilePath) :
        std::runtime_error((std::ostringstream() << "Could not open source file " << sourceFilePath << '.').str().c_str())
        {}
