/**
 * Page Provider
 * implements IPageProvider, diverge to different usage.
*/
#ifndef YIJINJING_PAGEPROVIDER_H
#define YIJINJING_PAGEPROVIDER_H

#include "IPageProvider.h"

YJJ_NAMESPACE_START

/**
 * PageProvider
 * abstract class with virtual interface,
 * utilized by JournalHandler
*/
class PageProvider : public IPageProvider 
{
protected:
    /** true if provider is used by a JournalWriter */
    bool is_writer;
    /** true if it is allowed to revise */
    bool revise_allowed;  // 是否允许修改
public:
    /** register journal when added into JournalHandler */
    virtual int register_journal(const string &dir, const string &jname) { return -1; }
    /** exit client after JournalHandler is released */
    virtual void exit_client() {}
    /** override IPageProvider */
    virtual bool isWriter() const { return is_writer; }
};

DECLARE_PTR(PageProvider)

/**
 * LocalPageProvider
 * provide local page, no need to connect with service.
*/
class LocalPageProvider : public PageProvider
{
public:
    /** constructor */
    LocalPageProvider(bool isWriting, bool reviseAllowed=false);
    /** override IPageProvider */
    virtual PagePtr getPage(const string& dir, const string& jname, int serviceIdx, short pageNum);
    /** override IPageProvider */
    void releasePage(void* buffer, int size, int serviceIdx);
};

/**
 * ClientPageProvider,
 * provide page via memory service, socket & comm
*/
class ClientPageProvider : public PageProvider
{
protected:
    string client_name;
    void*  comm_buffer;
    int    hash_code;
protected:
    /** register to service as a client */
    void register_client();
public:
    /** default constructor with client name and writing flag */
    ClientPageProvider(const string& clientName, bool isWriting, bool reviseAllowed=false);
    /** override PageProvider */
    virtual int register_journal(const string& dir, const string& jname);
    /** override PageProvider */
    virtual void exit_client();
    /** override IPageProvider */
    virtual PagePtr getPage(const string& dir, const string& jname, int serviceIdx, short pageNum);
    /** override IPageProvider */
    virtual void releasePage(void* buffer, int size, int serviceIdx);
};

YJJ_NAMESPACE_END

#endif