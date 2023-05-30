char const* greet()
{
    return "Hello World!";
}

#include <boost/python.hpp>
BOOST_PYTHON_MODULE(hello)
{
    using namespace boost::python;
    def("greet", greet);
}