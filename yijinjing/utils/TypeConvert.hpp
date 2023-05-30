/**
 * Define Type Convert utils here.
*/

#ifndef YIJINJING_TYPECONVERT_H
#define YIJINJING_TYPECONVERT_H

#include <vector>

#include "YJJ_DECLARE.h"
#include <boost/python/object.hpp>
#include <boost/locale.hpp>
#include <boost/python/stl_iterator.hpp>

YJJ_NAMESPACE_START

/**
 * transform python list into vector with template
*/
template<typename T>
inline vector <T> py_list_to_std_vector(const boost::python::object &iterable)
{
    return vector<T>(
        boost::python::stl_input_iterator<T>(iterable),
        boost::python::stl_input_iterator<T>()
    );
}

/**
 * transform vector with template into python list
*/
template<class T>
inline boost::python::list std_vector_to_py_list(const vector<T> &vector)
{
    typename vector<T>::const_iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter)
    {
        list.append(*iter);
    }
    return list;
}

/**
 * extract int from python dict with key, store in value.
*/
inline void getInt(const boost::python::dict &dict, const std::string &key, int *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<int> e(o);
        if (e.check())
        {
            *value = e();
        }
    }
}

/**
 * extract long from python dict with key, store in value.
*/
inline void getLong(const boost::python::dict &dict, const std::string &key, long *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<long> e(o);
        if (e.check())
        {
            *value = e();
        }
    }
}

/**
 * extract short from python dict with key, store in value.
*/
inline void getShort(const boost::python::dict &dict, const std::string &key, short *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<short> e(o);
        if (e.check())
        {
            *value = e();
        }
    }
}

/**
 * extract double from python dict with key, store in value.
*/
inline void getDouble(const boost::python::dict &dict, const std::string &key, double *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<double> e(o);
        if (e.check())
        {
            *value = e();
        }
    }
}

/**
 * extract char from python dict with key, store in value.
*/
inline void getChar(const boost::python::dict &dict, const std::string &key, char *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<char> e(o);
        if (e.check())
        {
            *value = e();
        }
    }
}

/**
 * extract string(char*) from python dict with key, store in value.
*/
inline void getString(const boost::python::dict &dict, const std::string &key, char *value)
{
    if (dict.has_key(key))
    {
        boost::python::object o = dict[key];
        boost::python::extract<std::string> e(o);
        if (e.check())
        {
            string s = e();
            const char* buffer = s.c_str();
            strcpy(value, buffer);
        }
    }
}

/**
 * convert gbk to utf8
*/
inline string gbk2utf8(const string &str)
{
    return boost::locale::conv::between(str, "UTF-8", "GBK");
}

YJJ_NAMESPACE_END

#endif