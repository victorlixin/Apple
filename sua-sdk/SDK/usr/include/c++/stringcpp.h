
#include <crtdefs.h>

#define sprintf_s snprintf
#define vsprintf_s vsnprintf

extern "C" {
_CRTIMP_ALTERNATIVE __checkReturn_wat errno_t __cdecl strcpy_s(__out_ecount_z(_DstSize) char * _P(_Dst), __in size_t _P(_DstSize), __in_z const char * _P(_Src));
}
