// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CONTROLS_CALCEDIT_INC
#define CONTROLS_CALCEDIT_INC

#if defined(CADKEY_MAIN) || defined(SDK_MAIN)
# define CALC_TEXT_EXPORT extern __declspec(dllexport)
# define DDX_UTIL_EXPORT  extern __declspec(dllimport)
# include "Controls/ControlUtil.h"
#elif defined(KCUTIL_MAIN) || defined(HELPER_PROGRAM)
# define CALC_TEXT_EXPORT extern __declspec(dllimport)
# define DDX_UTIL_EXPORT  extern __declspec(dllexport)
# include "Controls/ControlUtil.h"
#else
# define CALC_TEXT_EXPORT extern __declspec(dllimport)
# define DDX_UTIL_EXPORT  extern __declspec(dllimport)
# ifndef KC_SDK_VER_MAJOR 
#  include "Controls/ControlUtil.h"
# endif
#endif

#include "ck_enum.h"

// String value with length validation
DDX_UTIL_EXPORT void DDX_Text(CDataExchange *pDX, int nIDC, CString &value,
                              int nMaxLength);

// List boxes using index other than int
DDX_UTIL_EXPORT void DDX_CBIndex(CDataExchange* pDX, int nIDC, UCHAR& index);

// Checkboxes with a bool variable
DDX_UTIL_EXPORT void DDX_Check(CDataExchange* pDX, int nIDC, bool &value);

// Decimal values
CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, long &value,
                                    long lMin, long lMax);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, long &value)
    {
    DDX_Calc_Text(pDX, nIDC, value, LONG_MIN, LONG_MAX);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, long &value,
                          bool bMin, long lMinMax)
    {
    if(bMin)
        DDX_Calc_Text(pDX, nIDC, value, lMinMax,  LONG_MAX);
    else
        DDX_Calc_Text(pDX, nIDC, value, LONG_MIN, lMinMax);
    }

CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ULONG &value,
                                    ULONG ulMin, ULONG ulMax);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ULONG &value)
    {
    DDX_Calc_Text(pDX, nIDC, value, 0UL, ULONG_MAX);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ULONG &value,
                          bool bMin,   ULONG ulMinMax)
    {
    if(bMin)
        DDX_Calc_Text(pDX, nIDC, value, ulMinMax, ULONG_MAX);
    else
        DDX_Calc_Text(pDX, nIDC, value, 0UL,      ulMinMax);
    }

CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, int &value,
                                    CString csFormat);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, BYTE  &value)
    {
    ULONG ulValue = value;
    DDX_Calc_Text(pDX, nIDC, ulValue, 0UL, 255UL);
    value = BYTE(ulValue);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, short &value)
    {
    long lValue = value;
    DDX_Calc_Text(pDX, nIDC, lValue, long(SHRT_MIN), long(SHRT_MAX));
    value = short(lValue);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, int &value)
    {
    long lValue = value;
    DDX_Calc_Text(pDX, nIDC, lValue);
    value = lValue;
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, int &value, bool bMin,
                          int nMinMax)
    {
    long lValue = value;
    DDX_Calc_Text(pDX, nIDC, lValue, bMin, long(nMinMax));
    value = lValue;
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, int &value,
                          int nMin, int nMax)
    {
    long lValue = value;
    DDX_Calc_Text(pDX, nIDC, lValue, long(nMin), long(nMax));
    value = lValue;
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, UINT &value)
    {
    ULONG ulValue = value;
    DDX_Calc_Text(pDX, nIDC, ulValue);
    value = ulValue;
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, UINT &value,
                          bool bMin, UINT unMinMax)
    {
    ULONG ulValue = value;
    DDX_Calc_Text(pDX, nIDC, ulValue, bMin, ULONG(unMinMax));
    value = ulValue;
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, UINT &value,
                          UINT unMin, UINT unMax)
    {
    ULONG ulValue = value;
    DDX_Calc_Text(pDX, nIDC, ulValue, ULONG(unMin), ULONG(unMax));
    value = ulValue;
    }

#ifdef _WIN64
CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ptrdiff_t &value,
                                    ptrdiff_t lMin, ptrdiff_t lMax);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ptrdiff_t &value)
    {
    DDX_Calc_Text(pDX, nIDC, value, _I64_MIN, _I64_MAX);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, ptrdiff_t &value,
                          bool bMin, ptrdiff_t lMinMax)
    {
    if(bMin)
        DDX_Calc_Text(pDX, nIDC, value, lMinMax,  _I64_MAX);
    else
        DDX_Calc_Text(pDX, nIDC, value, _I64_MIN, lMinMax);
    }

CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, size_t &value,
                                    size_t ulMin, size_t ulMax);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, size_t &value)
    {
    DDX_Calc_Text(pDX, nIDC, value, 0UI64, _UI64_MAX);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, size_t &value,
                          bool bMin,   size_t ulMinMax)
    {
    if(bMin)
        DDX_Calc_Text(pDX, nIDC, value, ulMinMax, _UI64_MAX);
    else
        DDX_Calc_Text(pDX, nIDC, value, 0UI64,    ulMinMax);
    }

#endif

// Single floating point values
CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, double &value,
                                    CKS::CalcTextRange nMin, double dMin,
                                    CKS::CalcTextRange nMax, double dMax,
                                    int nPrecision, bool bRoundZero,
                                    CString csFormat,
                                    std::vector<bool>::reference *pbMixed,
                                    bool bTruncate);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, double &value,
                          CKS::CalcTextRange nMin, double dMin,
                          CKS::CalcTextRange nMax, double dMax,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, nMin, dMin, nMax, dMax, nPrecision,
                  bRoundZero, L"", nullptr, false);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, double &value,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, CKS::RangeAny, 0.0, CKS::RangeAny, 0.0,
                  nPrecision, bRoundZero);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, double &value,
                          CString csFormat, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, CKS::RangeAny, 0.0, CKS::RangeAny, 0.0,
                  -1, bRoundZero, csFormat, nullptr, false);
    }

CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC,
                                    double &value, CKS::CalcTextRange nRange,
                                    double dMinMax, int nPrecision = -1,
                                    bool bRoundZero = false);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, double &value,
                          double dMin, double dMax, int nPrecision = -1,
                          bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, CKS::GreaterThanEqual, dMin,
                  CKS::LessThanEqual, dMax, nPrecision, bRoundZero);
    }

inline void DDX_Calc_Text_Truncate(CDataExchange *pDX, int nIDC, double &value,
                                   CKS::CalcTextRange nMin, double dMin,
                                   CKS::CalcTextRange nMax, double dMax)
    {
    DDX_Calc_Text(pDX, nIDC, value, nMin, dMin, nMax, dMax, -1, false, L"",
                  nullptr, true);
    }

// Single-precision floating-point values.
inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, float &value,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    double dValue = value;
    DDX_Calc_Text(pDX, nIDC, dValue, nPrecision, bRoundZero);
    value = float(dValue);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, float &value,
                          CKS::CalcTextRange nRange, float fMinMax,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    double dValue = value;
    DDX_Calc_Text(pDX, nIDC, dValue, nRange, fMinMax, nPrecision, bRoundZero);
    value = float(dValue);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, float &value,
                          float fMin, float fMax, int nPrecision = -1,
                          bool bRoundZero = false)
    {
    double dValue = value;
    DDX_Calc_Text(pDX, nIDC, dValue, CKS::GreaterThanEqual, fMin,
                  CKS::LessThanEqual, fMax, nPrecision, bRoundZero);
    value = float(dValue);
    }

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, float &value,
                          CKS::CalcTextRange nMin, float fMin,
                          CKS::CalcTextRange nMax, float fMax,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    double dValue = value;
    DDX_Calc_Text(pDX, nIDC, dValue, nMin, fMin, nMax, fMax, nPrecision,
                  bRoundZero);
    value = float(dValue);
    }

// Versions that return arrays of values
CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC, 
                                    g_array<double> &adValues,
                                    CKS::CalcTextRange nMin, double dMin,
                                    CKS::CalcTextRange nMax, double dMax,
                                    int nPrecision = -1,
                                    bool bRoundZero = false);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, 
                          g_array<double> &adValues,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, adValues, CKS::RangeAny, 0.0, CKS::RangeAny, 0.0,
                  nPrecision, bRoundZero);
    }

CALC_TEXT_EXPORT void DDX_Calc_Text(CDataExchange *pDX, int nIDC,
                                    g_array<double> &adValues,
                                    CKS::CalcTextRange nRange, double dMinMax,
                                    int nPrecision = -1,
                                    bool bRoundZero = false);

inline void DDX_Calc_Text(CDataExchange *pDX, int nIDC, 
                          g_array<double> &adValues, double dMin, double dMax,
                          int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, adValues, CKS::GreaterThanEqual, dMin,
                  CKS::LessThanEqual, dMax, nPrecision, bRoundZero);
    }

// Versions that support "undefined" or "multiple" values. 

inline void DDX_Calc_Text_Undefined(CDataExchange *pDX, int nIDC, double &value,
                                    CKS::CalcTextRange nMin, double dMin,
                                    CKS::CalcTextRange nMax, double dMax,
                                    std::vector<bool>::reference bMixed,
                                    int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, nMin, dMin, nMax, dMax, nPrecision,
                  bRoundZero, L"", &bMixed, false);
    }

inline void DDX_Calc_Text_Undefined(CDataExchange *pDX, int nIDC, double &value,
                                    std::vector<bool>::reference bMixed,
                                    int nPrecision = -1, bool bRoundZero = false)
    {
    DDX_Calc_Text(pDX, nIDC, value, CKS::RangeAny, 0.0, CKS::RangeAny, 0.0,
                  nPrecision, bRoundZero, L"", &bMixed, false);
    }

#endif
