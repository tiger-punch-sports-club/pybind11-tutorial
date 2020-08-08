#include <pybind11/pybind11.h>
#include <stdio.h>

void say_hello ()
{
    printf ("Hello World\n");
}

struct MyData
{
    float x, y;

    MyData () : x (0), y (0)
    {
    }

    MyData (float x, float y) : x (x), y (y)
    {
    }

    void print ()
    {
        printf ("%f, %f\n", x, y);
    }
};

PYBIND11_MODULE (pybind11module, module)
{
    module.doc () = "Pybind11Module";
    module.def ("say_hello", &say_hello);

    pybind11::class_<MyData> (module, "MyData")
        .def (pybind11::init<> ())
        .def (pybind11::init<float, float> (), "constructor 2", pybind11::arg ("x"), pybind11::arg ("y"))
        .def ("print", &MyData::print)
        .def_readwrite ("x", &MyData::x)
        .def_readwrite ("y", &MyData::y)
    ;
}
