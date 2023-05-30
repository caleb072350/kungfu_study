#ifndef YIJINJING_PAGESERVICETASK_H
#define YIJINJING_PAGESERVICETASK_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

class PageEngine;

class PstBase
{
public:
    virtual void go() {};
    virtual string getName() const { return "Base"; };
    virtual boost::python::dict getInfo() const { return boost::python::dict(); }

};

DECLARE_PTR(PstBase)

class PstPidCheck : public PstBase
{
public:
    PstPidCheck(PageEngine *pe);
    void go();
    string getName() const { return "PidCheck"; };
private:
    PageEngine *engine;
};
DECLARE_PTR(PstPidCheck);

class PstTimeTick: public PstBase
{
public:
    PstTimeTick(PageEngine *pe);
    void go();
    string getName() const { return "TimeTick"; };
private:
    PageEngine *engine;
};
DECLARE_PTR(PstTimeTick)

class PstTempPage: public PstBase
{
public:
    static const string PageFullPath;
    PstTempPage(PageEngine *pe);
    void go();
    string getName() const { return "TempPage"; };
private:
    PageEngine *engine;
};
DECLARE_PTR(PstTempPage)

#define CONTROLLER_SWITCH_DAY       1
#define CONTROLLER_ENGINE_STARTS    2
#define CONTROLLER_ENGINE_ENS       3

class PstKfController: public PstBase
{
public:
    PstKfController(PageEngine *pe);
    void go();
    string getName() const {return "KfController";};
    boost::python::dict getInfo() const;
    void setDaySwitch(std::string formatTime);
    void addEngineStart(std::string formatTime);
    void addEngineEnd(std::string formatTime);
private:
    PageEngine *engine;
    vector<long>  next_nanos;
    vector<short> nano_types;
};
DECLARE_PTR(PstKfController)

YJJ_NAMESPACE_END

#endif