#include "Interpreter.h"
#include "SourceFile.h"
#include "Memory.h"
#include <map>
#include <stack>
#include <sstream>

size_t currentWordPosition;
bool jumpOccurred;

std::map<SourceFile::WordPositionType, std::pair<SourceFile::WordPositionType, size_t>> matchingClosingBracketPosition;
std::stack<std::pair<SourceFile::WordPositionType, size_t>> openingBrackets;

void executeWord(char word);

void jumpForwardIfZero(void);
void jumpBackwardsUnlessZero(void);

void Interpreter::execute()
{
    currentWordPosition = 0;
    jumpOccurred = false;
    while(!SourceFile::isEnded())
    {
        executeWord(SourceFile::currentWord());
        if(!jumpOccurred)
        {
            SourceFile::goToNextWord();
            currentWordPosition++;
        }
        jumpOccurred = false;
    }
}

void executeWord(char word)
{
    switch(word)
    {
        case '+': Memory::incrementCell();   break;
        case '-': Memory::decrementCell();   break;
        case '>': Memory::incrementIndex();  break;
        case '<': Memory::decrementIndex();  break;
        case '.': Memory::printCell();       break;
        case ',': Memory::readCell();        break;
        case '[': jumpForwardIfZero();       break;
        case ']': jumpBackwardsUnlessZero(); break;
    }
}

void jumpForwardIfZero(void)
{
    SourceFile::WordPositionType openingBrackedPosition = SourceFile::currentWordPosition();
    std::map<SourceFile::WordPositionType, std::pair<SourceFile::WordPositionType, size_t>>::iterator it;
    try
    {
        if(!Memory::isCellZero())
        {
            openingBrackets.push({openingBrackedPosition, currentWordPosition});
            return;
        }
        it = matchingClosingBracketPosition.find(openingBrackedPosition);
        if(it == matchingClosingBracketPosition.end())
        {
            do
            {
                SourceFile::goToNextWord();
            }
            while(SourceFile::currentWord() != ']' && !SourceFile::isEnded());
            if(SourceFile::isEnded())
            {
                throw Interpreter::MissingMatchingJumpBackwardsError(currentWordPosition);
            }
            it = matchingClosingBracketPosition.insert({openingBrackedPosition, {SourceFile::currentWordPosition(), currentWordPosition}}).first;
        }
        SourceFile::goToWord(it->second.first);
        currentWordPosition = it->second.second;
        jumpOccurred = true;
    }
    catch(const std::bad_alloc& e)
    {
        throw Interpreter::NoMemoryForLoopStack(currentWordPosition);
    }
}

void jumpBackwardsUnlessZero(void)
{
    if(openingBrackets.empty())
    {
        throw Interpreter::MissingMatchingJumpForwardError(currentWordPosition);
    }
    if(!Memory::isCellZero())
    {
        SourceFile::goToWord(openingBrackets.top().first);
        currentWordPosition = openingBrackets.top().second;
        openingBrackets.pop();
        jumpOccurred = true;
        return;
    }
    openingBrackets.pop();
}

void Interpreter::finish()
{
    if(!openingBrackets.empty())
    {
        throw Interpreter::MissingMatchingJumpBackwardsError(openingBrackets.top().second);
    }
    matchingClosingBracketPosition.clear();
}

Interpreter::MissingMatchingJumpBackwardsError::MissingMatchingJumpBackwardsError(size_t jumpForwardPosition) :
        std::runtime_error((std::ostringstream() << "Missing matching ']' for '[' at position "
                                                 << jumpForwardPosition << '.').str().c_str())
        {}

Interpreter::MissingMatchingJumpForwardError::MissingMatchingJumpForwardError(size_t jumpBackwardsPosition) :
        std::runtime_error((std::ostringstream() << "Missing matching '[' for ']' at position "
                                                 << jumpBackwardsPosition << '.').str().c_str())
        {}

Interpreter::NoMemoryForLoopStack::NoMemoryForLoopStack(size_t jumpForwardPosition) :
        std::runtime_error((std::ostringstream() << "Could not allocate memory for '[' at position "
                                                 << jumpForwardPosition << '.').str().c_str())
        {}
