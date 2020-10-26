#if defined(_DEBUG)
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include <pybind11/embed.h>

#include <stdio.h>

void say_something ()
{
    printf ("Say Something\n");
}

static int COUNTER = 0;

void set_counter (int count)
{
    COUNTER = count;
}

struct MyData
{
    float x;
};

PYBIND11_EMBEDDED_MODULE (embeddedmodule, module)
{
    module.doc () = "Embedded Module";
    module.def ("say_something", &say_something);
    module.def ("set_counter", &set_counter);

    pybind11::class_<MyData>(module, "MyData")
    .def_readwrite ("x", &MyData::x);
}

int main ()
{
    pybind11::scoped_interpreter guard{};

    auto sys = pybind11::module::import ("sys");
    pybind11::print (sys.attr ("path"));

    MyData data {};
    data.x = 33.0f;
           
    printf ("end\n");
    return 0;
}
