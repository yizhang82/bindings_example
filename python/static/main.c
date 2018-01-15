#include <python.h>
#include <structmember.h>       // PyMemberDef

//=============================================================================
// Static Methods
//=============================================================================

static PyObject *FastInt_Add(PyObject *self, PyObject *args)
{
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b))
    {
        return NULL;
    }

    return Py_BuildValue("i", a + b);
}

static PyMethodDef FastIntModule_StaticMethods[] = {
    { "add", FastInt_Add, METH_VARARGS, "Add two integers" },
    { NULL, NULL, 0, NULL }
};

//=============================================================================
// fastInt type
//=============================================================================

typedef struct {
    PyObject_HEAD
    int value;
} FastIntObject;

static PyObject *
FastInt_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    FastIntObject *self;

    self = (FastIntObject *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->value = 0;        
    }

    return (PyObject *)self;
}

static int
FastInt_init(FastIntObject *self, PyObject *args, PyObject *kwds)
{
    if (! PyArg_ParseTuple(args, "i", &self->value))
        return -1;

    return 0;
}

static PyObject *
FastInt_add(FastIntObject *self, PyObject *args)
{
    int operand;
    if (! PyArg_ParseTuple(args, "i", &operand))
        return NULL;

    self->value += operand;

    Py_INCREF(self);
    return (PyObject *)self;
}

static PyMethodDef FastInt_methods[] = {
    { "inc", (PyCFunction) FastInt_add, METH_VARARGS, "inc method" },
    {NULL}
};

static PyMemberDef FastInt_members[] = {
    { "value", T_INT, offsetof(FastIntObject, value), 0, "value of the integer" },
    { NULL }  /* Sentinel */
};

static PyTypeObject FastIntType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "fastint.fastInt",           /* tp_name */
    sizeof(FastIntObject),     /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Fast int object",         /* tp_doc */    
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    FastInt_methods,           /* tp_methods */
    FastInt_members,           /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)FastInt_init,    /* tp_init */
    0,                         /* tp_alloc */
    FastInt_new,               /* tp_new */    
};

//=============================================================================
// fastint module initialization
//=============================================================================

#ifdef _MSC_VER
#define PYMODINIT_FUNC __declspec(dllexport) void
#else
#define PYMODINIT_FUNC void
#endif

PYMODINIT_FUNC initfastint()
{
    PyObject *m;

    if (PyType_Ready(&FastIntType) < 0)
        return;

    m = Py_InitModule("fastint", FastIntModule_StaticMethods);
    if (m == NULL)
        return;

    Py_INCREF(&FastIntType);
    PyModule_AddObject(m, "fastInt", (PyObject *)&FastIntType);
}
