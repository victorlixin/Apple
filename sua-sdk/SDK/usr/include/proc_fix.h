#ifndef _SKIP_H_
#define _SKIP_H_


#ifdef _MSC_VER		/* Microsoft compiler */
#pragma message("Removing former inclusion,as stdarg.h and varargs.h should not be included together.")
#elif defined (__GNUC__)

#warning "Removing former inclusion,as stdarg.h and varargs.h should not be included together."

#endif 

#endif
