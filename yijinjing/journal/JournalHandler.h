/**
 * Journal Handler
 * base class of Journal reader / writer
*/

#ifndef YIJINJING_JOURNALHANDLER_H
#define YIJINJING_JOURNALHANDLER_H

/*                    | - JournalReader (read)
* JournalHandler     -|
        |              | - JournalWriter (write)
        |
        | - add journal
        | - connect to PageEngine-service via page_provider
*/

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(Journal);
FORWARD_DECLARE_PTR(PageProvider);

/*
* JournalHandler
*/
class JournalHandler {
protected:
    /** all page-engine-interact stuff is handled by pageProvider */
    PageProviderPtr page_provider;
    /** journals */
    vector<JournalPtr> journals;
    /** current journal */
    JournalPtr curJournal;
public:
    /** default constructor with outside page provider */
    JournalHandler(PageProviderPtr ptr): page_provider(ptr) {};
    /** default destructor */
    ~JournalHandler();
    /** return  the journal's index in the vector */
    virtual size_t addJournal(const string& dir, const string& jname);
    /** default name */
    static string getDefaultName(const string& prefix);
};

YJJ_NAMESPACE_END

#endif // YIJINJING_JOURNALHANDLER_H
