#ifndef _WCHARCPP_H_
#define _WCHARCPP_H_

#define sprintf_s snprintf
#define vsprintf_s vsnprintf

extern "C" {
#if     defined(_M_IA64)
_CRT_INSECURE_DEPRECATE_MEMORY void *  __cdecl memmove(__out_bcount_full_opt(_MaxCount) void * _P(_Dst), __in_bcount_opt(_MaxCount) const void * _P(_Src), size_t _P(_MaxCount));
#else
_CRTIMP _CRT_INSECURE_DEPRECATE_MEMORY void *  __cdecl memmove(__out_bcount_full_opt(_MaxCount) void * _P(_Dst), __in_bcount_opt(_MaxCount) const void * _P(_Src), __in size_t _P(_MaxCount));
#endif
_CRT_INSECURE_DEPRECATE_MEMORY void *  __cdecl memcpy(__out_bcount_full_opt(_MaxCount) void * _P(_Dst), __in_bcount_opt(_MaxCount) const void * _P(_Src), __in size_t _P(_MaxCount));
_CRTIMP errno_t __cdecl memcpy_s(__out_bcount_part_opt(_DstSize, _MaxCount) void * _P(_Dst), __in size_t _P(_DstSize), __in_bcount_opt(_MaxCount) const void * _P(_Src), __in size_t _P(_MaxCount));
_CRTIMP errno_t __cdecl memmove_s(__out_bcount_part_opt(_DstSize, _MaxCount) void * _P(_Dst), __in size_t _P(_DstSize), __in_bcount_opt(_MaxCount) const void * _P(_Src), __in size_t _P(_MaxCount));
_CRTIMP_ALTERNATIVE __checkReturn_wat errno_t __cdecl strcpy_s(__out_ecount_z(_DstSize) char * _P(_Dst), __in size_t _P(_DstSize), __in_z const char * _P(_Src));


__inline errno_t __CRTDECL wmemcpy_s(__out_ecount_part_opt(_N1, _N) wchar_t *_S1, __in size_t _N1, __in_ecount_opt(_N) const wchar_t *_S2, size_t _N)
        {
            return memcpy_s(_S1, _N1*sizeof(wchar_t), _S2, _N*sizeof(wchar_t));
        }

__inline errno_t __CRTDECL wmemmove_s(__out_ecount_part_opt(_N1, _N) wchar_t *_S1, __in size_t _N1, __in_ecount_opt(_N) const wchar_t *_S2, __in size_t _N)
        {
            return memmove_s(_S1, _N1*sizeof(wchar_t), _S2, _N*sizeof(wchar_t));
        }
}

#ifndef _SVR_I18N

extern "C++" {
wint_t __cdecl btowc (int c);
inline const wchar_t *wmemchr(const wchar_t *_S, wchar_t _C, size_t _N)
        {for (; 0 < _N; ++_S, --_N)
                if (*_S == _C)
                        return (_S);
        return (0); }
inline int wmemcmp(const wchar_t *_S1, const wchar_t *_S2, size_t _N)
        {for (; 0 < _N; ++_S1, ++_S2, --_N)
                if (*_S1 != *_S2)
                        return (*_S1 < *_S2 ? -1 : +1);
        return (0); }
inline wchar_t *wmemcpy(wchar_t *_S1, const wchar_t *_S2, size_t _N)
        {
            return (wchar_t *)memcpy(_S1, _S2, _N*sizeof(wchar_t));
        }
inline wchar_t *wmemmove(wchar_t *_S1, const wchar_t *_S2, size_t _N)
        {
            return (wchar_t *)memmove(_S1, _S2, _N*sizeof(wchar_t));
        }
inline wchar_t *wmemset(wchar_t *_S, wchar_t _C, size_t _N)
        {wchar_t *_Su = _S;
        for (; 0 < _N; ++_Su, --_N)
                *_Su = _C;
        return (_S); }

inline wchar_t *wmemchr(wchar_t *_S, wchar_t _C, size_t _N)
        {return ((wchar_t *)wmemchr((const wchar_t *)_S, _C, _N)); }
}

#endif /* _SVR_I18N */


#endif


