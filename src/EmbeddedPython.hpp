#include <python.h>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/function.hpp>

#include <iostream>
#include <string>
#include <memory>
#include "MadPython.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void Py_Initialize();
//extern "C" int PyRun_SimpleString(const char *s);
void Py_Finalize();
//PyObject * Py_InitModule4(const char *name, PyMethodDef *methods,
//                                      const char *doc, PyObject *self,
//                                      int apiver);
#ifdef __cplusplus
}
#endif

namespace py = ::boost::python;

namespace embedded_python {

    enum direction_type {
        STDIN,
        STDOUT,
        STDERR
    };

    template<direction_type>
    class py_redirector
    {
    public:
        py_redirector()
        { }

        py_redirector(boost::function<void (const std::string&)> f)
            : m_write_fn(f)
        { }

        void write(const std::string& text) {

            if (m_write_fn)
                m_write_fn(text);
            else
                std::cout << text;
        }

    public:
        boost::function<void (const std::string&)> m_write_fn;
    };

    typedef py_redirector<STDOUT>	stdout_redirector;
    typedef py_redirector<STDERR>	stderr_redirector;


    static std::auto_ptr<stdout_redirector> make_stdout_redirector() {

        std::auto_ptr<stdout_redirector> ptr(new stdout_redirector);

        return ptr;
    }

    static std::auto_ptr<stderr_redirector> make_stderr_redirector() {

        std::auto_ptr<stderr_redirector> ptr(new stderr_redirector);

        return ptr;
    }
}

BOOST_PYTHON_MODULE(redirector)
{
    using namespace embedded_python;
    using namespace py;

    class_<stdout_redirector>("stdout",
                              "This class redirects python's standard output "
                              "to the console.",
                              init<>("initialize the redirector."))
        .def("__init__", make_constructor(make_stdout_redirector), "initialize the redirector.")
        .def("write", &stdout_redirector::write, "write sys.stdout redirection.")
        ;

    class_<stderr_redirector>("stderr",
                              "This class redirects python's error output "
                              "to the console.",
                              init<>("initialize the redirector."))

        .def("__init__", make_constructor(make_stderr_redirector), "initialize the redirector.")
        .def("write", &stderr_redirector::write, "write sys.stderr redirection.");
}


class EmbeddedPython
{
public:
    EmbeddedPython()
    {
        // Register the module with the interpreter; must be called before Py_Initialize.
        /* ToDo: C style cast to avoid compiler warning about
           deprecated conversion from string constant to 'char*' */
        if (PyImport_AppendInittab((char*)"redirector", initredirector) == -1) {
            throw std::runtime_error("Failed to add embedded_python to python's "
                                     "interpreter builtin modules");
        }

        if (PyImport_AppendInittab((char*)"madpython", initmadpython) == -1) {
            throw std::runtime_error("Failed to add madpython to python's "
                                     "interpreter builtin modules");
        }

        Py_Initialize();

        // Retrieve the main module
        m_main_module = py::import("__main__");

        // Retrieve the main module's namespace
        m_main_global = py::dict(m_main_module.attr("__dict__"));

        try {

            static const char* const redirect_py =
                "import sys\n"
                "import redirector\n"
                "sys.stdout = redirector.stdout()\n"
                "sys.stderr = redirector.stderr()\n"
                "from madpython import MadPython";

#if 0
            /* FixMe: exception thrown, mmh - seems a bug in boost.python, see
             * http://www.nabble.com/Problems-with-Boost::Python-Embedding-Tutorials-td18799129.html */
            py::exec(redirect_py, m_main_global);
#else
            PyRun_String(redirect_py,
                         Py_file_input,
                         m_main_global.ptr(), m_main_global.ptr());
#endif

        }
        catch(const py::error_already_set&) {

            if (PyErr_Occurred()) {
                std::cerr << "*** Redirection failed ***\n";
                PyErr_Print();
                PyErr_Clear();
            }
            else {
                std::cerr << "A C++ exception was thrown for which "
                          << "there was no exception handler registered.";
            }
        }
    }

    ~EmbeddedPython() {
        // Boost.Python doesn't support Py_Finalize yet, so don't call it!
        //Py_Finalize();
    }

    void exec(const std::string& command)
    {
        try {
            py::object result = py::exec(command.c_str(),
                                         m_main_global, m_main_global);
        }
        catch(const py::error_already_set&) {

            if (PyErr_Occurred()) {
                PyErr_Print();
                PyErr_Clear();
            }
            else {
                std::cerr << "A C++ exception was thrown for which "
                          << "there was no exception handler registered.\n";
            }
        }
    }

    void write_stdout(const std::string& text) {

        std::cout << ">>> " << text;

    }

    void write_stderr(const std::string& text) {

        std::cout << "xxx " << text;

    }

private:
    py::object m_main_module;
    py::dict   m_main_global;
};

