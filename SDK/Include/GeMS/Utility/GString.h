
//////////////////////////////////////////////////////////////////////
//
//      *GeMS++ V6.1
//
//      * U.S. Patent #6,421,690
//
//      © Honeywell Federal Manufacturing & Technologies, LLC, 2002
//
//  NOTICE: These data were produced by Honeywell Federal Manufacturing & Technologies, LLC 
//  under Contract No. DE-AC04-01AL66850 with the Department of Energy.  For 5 years 
//  from 4/1/2003, the Government is granted for itself and others acting on its behalf 
//  a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, 
//  prepare derivative works, and perform publicly and display publicly by or on behalf 
//  of the Government.  There is provision for the possible extension of the term of this 
//  license.  Subsequent to that period or any extension granted, the Government is granted 
//  for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide 
//  license in this data to reproduce, prepare derivative works, distribute copies to the
//  public, perform publicly and display publicly, and to permit others to do so.  The specific 
//  term of the license can be identified by inquiry made to the Contractor or DOE.  Neither 
//  the United States nor the United States Department of Energy, nor any of their employees, 
//  makes any warranty, express or implied, or assumes any legal liability or responsibility 
//  for the accuracy, completeness, or usefulness of any data, apparatus, product, or process 
//  disclosed, or represents that its use would not infringe privately owned rights.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//      This file may be sub-licensed and distributed in an unmodified
//      form to End Users, but only by a Licensee posessing a valid
//      Honeywell International Inc., Federal Manufacturing & Technology
//      Software License Agreement for Software Developers, Resellers
//      and Distributors of the FB-Tools software system.
//
//      Along with this header, the following .lib files may also
//      be sub-licensed and distributed under the same conditions:
//
//           Gems.lib,       Gemsd.lib,
//           GemsDll.lib,    GemsDlld.lib,
//           GemsDllm.lib,   GemsDlldm.lib,
//           GemsDllmu.lib,  GemsDlldmu.lib,
//           GemsDllu.lib,   GemsDlldu.lib
//
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Many of the ideas around which the current implementation of g_string are based come
//  from the MFC SourceBook, found at www.codeguru.com.  We would like to specifically thank
//  Joe O'Leary for the article he contributed in creating a CString-like class based upon
//  the STL basic_string<> template.  Much of the code in this implementation was taken
//  from his article, although some significant massaging was necessary to 'GeMSify' it.
//  In so doing, of course, it is no longer CString-like since the prior g_string implementation
//  had to be supported.  Nevertheless, it _does_ have much of CString's functionality (if
//  not its semantics), on top of STL's basic_string<> functionality and GeMS support.
//
//  g_string has:
//      - UNICODE support
//      - implicit casts to const TCHAR*
//
//  This header also declares our own version of the MFC/ATL UNICODE-MBCS
//  conversion macros.  Our version looks exactly like Microsoft's to
//  facilitate portability.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _g_string_h_
#define _g_string_h_

#include "GeMS/Utility/GBasicString.h"
#include "GeMS/Utility/compare.h"

#ifndef _MSC_VER
#define _wcsicmp wcscasecmp
#endif

///////////////////////////////////////////////////////////////////////////////
//
// g_string
//
class g_string : public std::wstring
    {
public:
    // constructors
    g_string() {}
    g_string(const std::wstring &str) : std::wstring(str) {}
    g_string(const wchar_t *pT) : std::wstring(pT ? pT : L"") {}
    g_string(const_iterator first, const_iterator last) :
        std::wstring(first, last) {}
    g_string(size_type nSize, value_type ch,
             const allocator_type &al = allocator_type()) :
        std::wstring(nSize, ch, al) {}
    explicit g_string(const allocator_type &al) : std::wstring(al) {}
    
    // assignment operators
    using std::wstring::operator=;
    g_string &operator=(const wchar_t *pT)
        {
        if(nullptr != pT)
            std::wstring::operator=(pT);
        else
            clear();

        return(*this);
        }
    
    // concatenation.
    using std::wstring::operator+=;
    const g_string& operator+=(const wchar_t *pT)
        { if(nullptr != pT) std::wstring::operator+=(pT); return(*this); }
    
    operator const wchar_t *() const { return c_str(); }

    GCompareResult compare(const wchar_t *right) const
        {
        if(nullptr == right) right = L"";
        return(GCompareResultFromInt(wcscmp(c_str(), right)));
        }

    GCompareResult compare_no_case(const wchar_t *right) const
        {
        if(nullptr == right) right = L"";
        return(GCompareResultFromInt(_wcsicmp(c_str(), right)));
        }
    };

// These are here so that they use the g_string::compare() function which
// allows the use of nullptr as the wchar_t *argument.
inline bool operator==(const g_string &_Left, const g_string &_Right)
    { return(_Right.compare(_Left) == 0); }

inline bool operator==(const wchar_t *_Left, const g_string &_Right)
    { return(_Right.compare(_Left) == 0); }

inline bool operator==(const g_string &_Left, const wchar_t *_Right)
    { return(_Left.compare(_Right) == 0); }

#ifdef _MFC_VER
inline bool operator==(const CString &_Left, const g_string &_Right)
    { return(_Left == _Right.c_str()); }

inline bool operator==(const g_string &_Left, const CString &_Right)
    { return(_Left.compare(_Right) == 0); }
#endif

inline bool operator!=(const g_string &_Left, const g_string &_Right)
    { return(!(_Left == _Right)); }

inline bool operator!=(const wchar_t *_Left, const g_string &_Right)
    { return(!(_Left == _Right)); }

inline bool operator!=(const g_string &_Left, const wchar_t *_Right)
    { return(!(_Left == _Right)); }

#ifdef _MFC_VER
inline bool operator!=(const CString &_Left, const g_string &_Right)
    { return(_Left != _Right.c_str()); }

inline bool operator!=(const g_string &_Left, const CString &_Right)
    { return(!(_Left == _Right)); }
#endif

inline bool operator<(const g_string &_Left, const g_string &_Right)
    { return(_Right.compare(_Left) > 0); }

inline bool operator<(const wchar_t *_Left, const g_string &_Right)
    { return(_Right.compare(_Left) > 0); }

inline bool operator<(const g_string &_Left, const wchar_t *_Right)
    { return(_Left.compare(_Right) < 0); }

#ifdef _MFC_VER
inline bool operator<(const CString &_Left, const g_string &_Right)
    { return(_Left < _Right.c_str()); }

inline bool operator<(const g_string &_Left, const CString &_Right)
    { return(_Left.compare(_Right) < 0); }
#endif

inline bool operator>(const g_string &_Left, const g_string & _Right)
    { return(_Right < _Left); }

inline bool operator>(const wchar_t *_Left, const g_string & _Right)
    { return(_Right < _Left); }

inline bool operator>(const g_string & _Left, const wchar_t *_Right)
    { return(_Right < _Left); }

#ifdef _MFC_VER
inline bool operator>(const CString &_Left, const g_string &_Right)
    { return(_Left > _Right.c_str()); }

inline bool operator>(const g_string & _Left, const CString &_Right)
    { return(_Right < _Left); }
#endif

inline bool operator<=(const g_string &_Left, const g_string & _Right)
    { return(!(_Right < _Left)); }

inline bool operator<=(const wchar_t *_Left, const g_string & _Right)
    { return(!(_Right < _Left)); }

inline bool operator<=(const g_string &_Left, const wchar_t *_Right)
    { return(!(_Right < _Left)); }

#ifdef _MFC_VER
inline bool operator<=(const CString &_Left, const g_string &_Right)
    { return(_Left <= _Right.c_str()); }

inline bool operator<=(const g_string &_Left, const CString &_Right)
    { return(!(_Right < _Left)); }
#endif

inline bool operator>=(const g_string &_Left, const g_string &_Right)
    { return(!(_Left < _Right)); }

inline bool operator>=(const wchar_t *_Left, const g_string &_Right)
    { return(!(_Left < _Right)); }

inline bool operator>=(const g_string &_Left, const wchar_t *_Right)
    { return(!(_Left < _Right)); }

#ifdef _MFC_VER
inline bool operator>=(const CString &_Left, const g_string &_Right)
    { return(!(_Left < _Right)); }

inline bool operator>=(const g_string &_Left, const CString &_Right)
    { return(!(_Left < _Right)); }
#endif

class g_compare_strings : public comparator<g_string>
    {
public:
    virtual GCompareResult operator()(const g_string *left,
                                        const g_string *right) const
        {
        return left->compare(*right);
        }
    };

class g_compare_strings_ignoring_case : public comparator<g_string>
    {
public:
    virtual GCompareResult operator()(const g_string *left,
                                        const g_string *right) const
        {
        return left->compare_no_case(*right);
        }
    };

inline std::wstring operator+(wchar_t ch, const std::wstring &str)
    {
    return(std::wstring(1, ch) + str);
    }

inline std::wstring operator+(char ch, const std::wstring &str)
    {
    return(std::wstring(1, ch) + str);
    }

inline std::wstring operator+(const wchar_t *psz, const std::wstring &str)
    {
    return(std::wstring(psz) + str);
    }

inline std::wstring operator+(const char *psz, const std::wstring &str)
    {
    return(GStdA2WHelper(psz) + str);
    }

inline std::wstring operator+(wchar_t ch, const std::string &str)
    {
    return(std::wstring(1, ch) + GStdA2WHelper(str));
    }

inline std::string operator+(char ch, const std::string &str)
    {
    return(std::string(1, ch) + str);
    }

inline std::wstring operator+(const wchar_t *psz, const std::string &str)
    {
    return(std::wstring(psz) + GStdA2WHelper(str));
    }

inline std::string operator+(const char *psz, const std::string &str)
    {
    return(std::string(psz) + str);
    }

#endif
