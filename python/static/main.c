#include <python.h>

static PyObject *FastInt_Add(PyObject *self, PyObject *args)
{
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b))
    {
        return NULL;
    }

    return Py_BuildValue("i", a + b);
}

static PyMethodDef FastInt_StaticMethods[] = {
    { "add", FastInt_Add, METH_VARARGS, "Add two integers" },
    { NULL, NULL, 0, NULL }
};

#ifdef _MSC_VER
#define PYMODINIT_FUNC __declspec(dllexport) void
#else
#define PYMODINIT_FUNC void
#endif

PYMODINIT_FUNC initfastint()
{
    Py_InitModule("fastint", FastInt_StaticMethods);
}
