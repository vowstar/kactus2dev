#ifndef VHDLGENERATOR_GLOBAL_H
#define VHDLGENERATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef VHDLGENERATOR_LIB
# define VHDLGENERATOR_EXPORT Q_DECL_EXPORT
#else
# define VHDLGENERATOR_EXPORT Q_DECL_IMPORT
#endif

#endif // VHDLGENERATOR_GLOBAL_H
