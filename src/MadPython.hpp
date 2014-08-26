#include <python.h>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/function.hpp>

#include <iostream>
#include <string>
#include <memory>

#include "MadEditFrame.h"
#include "MadEdit/MadEdit.h"

extern MadEdit *g_ActiveMadEdit;

namespace mad_py = ::boost::python;

namespace mad_python
{
    class MadPython
    {
        public:
            void GoToLine(int line)
            {
                if(g_ActiveMadEdit && (line > 0))
                    g_ActiveMadEdit->GoToLine(line);
            }
    };

}

BOOST_PYTHON_MODULE(madpython)
{
    using namespace mad_python;
    using namespace mad_py;

    class_<MadPython>("MadPython", "This class is a collection of wrapper functions of MadEdit.")
        .def("gotoline", &MadPython::GoToLine, "Go To Line of current file")
        ;
}

