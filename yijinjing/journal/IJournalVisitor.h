#ifndef PROJECT_IJOURNALVISITOR_H
#define PROJECT_IJOURNALVISITOR_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

class Frame;
/**
 * visitor made for reader
 * any class with this interface can be added into JournalReader
*/
class IJournalVisitor 
{
public:
    virtual void visit(const string& name, Frame& frame) = 0;
}
YJJ_NAMESPACE_END

#endif // PROJECT_IJOURNALVISITOR_H
