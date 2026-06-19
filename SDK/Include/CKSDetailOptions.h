// Copyright Kubotek Corporation, 2006-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CKSDETAILOPTIONS_H_LOADED
#define CKSDETAILOPTIONS_H_LOADED

#include "ck_draft.h"
#include <memory>

class CKDetailDimText;
class CKDetailFormat;
class CKDetailLines;
class CKDetailUnits;
class CKDetailOptions;

class SDK_EXPORT CKPart;

// @doc EXTERNAL SDK

/////////////////////////////////////////////////////////////////////////////
// FormatOptions

// @class
// The class for the Format options of detail entities in KeyCreator.
class SDK_EXPORT CKSDetailFormat
    {
public:

    CKSDetailFormat();
    ~CKSDetailFormat();

    CKSDetailFormat(const CKSDetailFormat &rRight);

    CKSDetailFormat &operator=(const CKDetailFormat &rRight);
    CKSDetailFormat &operator=(const CKSDetailFormat &);

    void GetDetailFormat(CKDetailFormat &) const;

    // @cmember Sets all the unused flags to true, essentially clearing the options
    void Clear();

// @group Options use flags
    // @comm The Is* functions check the current use state of the option.  If the option
    //  is to be used they will return true, otherwise they will return false.<nl>
    //  The Set* functions set the state of the use flags.  Setting an option to a given
    //  value will automatically set the use flag to true, these Set* functions can be
    //  used to turn off certain options.  They will return the new state of the flag.

    /* @cmember Check Flag */  bool IsUnusedAligned         () const;
    /* @cmember Check Flag */  bool IsUnusedAspectRatio     () const;
    /* @cmember Check Flag */  bool IsUnusedAutoCenter      () const;
    /* @cmember Check Flag */  bool IsUnusedCharHeight      () const;
    /* @cmember Check Flag */  bool IsUnusedColorNumber     () const;
    /* @cmember Check Flag */  bool IsUnusedColorNumberFlag () const;
    /* @cmember Check Flag */  bool IsUnusedFilledFont      () const;
    /* @cmember Check Flag */  bool IsUnusedFont            () const;
    /* @cmember Check Flag */  bool IsUnusedHorAlignment    () const;
    /* @cmember Check Flag */  bool IsUnusedJustify         () const;
    /* @cmember Check Flag */  bool IsUnusedLineSpacing     () const;
    /* @cmember Check Flag */  bool IsUnusedMinSpacing      () const;
    /* @cmember Check Flag */  bool IsUnusedMirrorText      () const;
    /* @cmember Check Flag */  bool IsUnusedPath            () const;
    /* @cmember Check Flag */  bool IsUnusedPenNumber       () const;
    /* @cmember Check Flag */  bool IsUnusedPenNumberFlag   () const;
    /* @cmember Check Flag */  bool IsUnusedSlantAngle      () const;
    /* @cmember Check Flag */  bool IsUnusedStandard        () const;
    /* @cmember Check Flag */  bool IsUnusedStaticSizeText  () const;
    /* @cmember Check Flag */  bool IsUnusedStrikethrough   () const;
    /* @cmember Check Flag */  bool IsUnusedSupSubScale     () const;
    /* @cmember Check Flag */  bool IsUnusedTextAngle       () const;
    /* @cmember Check Flag */  bool IsUnusedTextStyle       () const;
    /* @cmember Check Flag */  bool IsUnusedTextWidth       () const;
    /* @cmember Check Flag */  bool IsUnusedUnderline       () const;
    /* @cmember Check Flag */  bool IsUnusedVerAlignment    () const;
    /* @cmember Check Flag */  bool IsUnusedCPlaneText      () const;

    /* @cmember Set Flag */  bool SetUnusedAligned          (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedAspectRatio      (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedAutoCenter       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedCharHeight       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedColorNumber      (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedColorNumberFlag  (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedFilledFont       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedFont             (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedHorAlignment     (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedJustify          (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedLineSpacing      (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedMinSpacing       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedMirrorText       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedPath             (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedPenNumber        (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedPenNumberFlag    (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedSlantAngle       (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedStandard         (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedStaticSizeText   (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedStrikethrough    (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedSupSubScale      (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedTextAngle        (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedTextStyle        (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedTextWidth        (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedUnderline        (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedVerAlignment     (bool bUnused = true);
    /* @cmember Set Flag */  bool SetUnusedCPlaneText       (bool bUnused = true);

// @group Data Set functions
    // @comm Sets the value for the given member.  These functions check the
    //  provided value to make sure it is in a valid range for the setting.
    //  Returns true if the value is set, false it it was not.

    /* @cmember Set Option */  bool SetAligned          (const bool bAligned);
    /* @cmember Set Option */  bool SetAspectRatio      (const double dAspectRatio);
    /* @cmember Set Option */  bool SetAutoCenter       (const bool bAutoCenter);
    /* @cmember Set Option */  bool SetCharHeight       (const double dCharHeight);
    /* @cmember Set Option */  bool SetColorNumber      (const UCHAR ucColorNumber);
    /* @cmember Set Option */  bool SetColorNumberFlag  (const UCHAR ucColorNumber);
    /* @cmember Set Option */  bool SetFilledFont       (const bool bFilledFont);
    /* @cmember Set Option */  bool SetFont             (const std::wstring &csFont);
    /* @cmember Set Option */  bool SetHorAlignment     (const UCHAR ucHorAlignment);
    /* @cmember Set Option */  bool SetJustify          (const UCHAR ucJustify);
    /* @cmember Set Option */  bool SetLineSpacing      (const double dLineSpacing);
    /* @cmember Set Option */  bool SetMinSpacing       (const double dMinSpacing);
    /* @cmember Set Option */  bool SetMirrorText       (const bool bMirrorText);
    /* @cmember Set Option */  bool SetPath             (const UCHAR ucPath);
    /* @cmember Set Option */  bool SetPenNumber        (const UCHAR ucPenNumber);
    /* @cmember Set Option */  bool SetPenNumberFlag    (const UCHAR ucPenNumber);
    /* @cmember Set Option */  bool SetSlantAngle       (const double dSlantAngle);
    /* @cmember Set Option */  bool SetStandard         (const UCHAR ucStandard);
    /* @cmember Set Option */  bool SetStaticSizeText   (const int nStaticSizeText);
    /* @cmember Set Option */  bool SetStrikethrough    (const bool bStrikethrough);
    /* @cmember Set Option */  bool SetSupSubScale      (const double dSupSubScale);
    /* @cmember Set Option */  bool SetTextAngle        (const double dTextAngle);
    /* @cmember Set Option */  bool SetTextStyle        (const UCHAR dTextStyle);
    /* @cmember Set Option */  bool SetTextWidth        (const UCHAR dTextWidth);
    /* @cmember Set Option */  bool SetUnderline        (const bool bUnderline);
    /* @cmember Set Option */  bool SetVerAlignment     (const UCHAR ucVerAlignment);
    /* @cmember Set Option */  bool SetCPlaneText       (const bool bCPlaneText);

    /* @cmember Set Option */  bool SetTextAttrib       (CKBasicAttrib &rAttrib);

// @group Get Member Data
    // @comm These functions get the value for the member.  If the value is
    //  mixed then the passed in variable is not changed.<nl>
    //  Return false if the value is unused.
    //  Return true if the value was retrieved.

    /* @cmember Get Option */  bool GetAligned          (bool &) const;
    /* @cmember Get Option */  bool GetAspectRatio      (double &) const;
    /* @cmember Get Option */  bool GetAutoCenter       (bool &) const;
    /* @cmember Get Option */  bool GetCharHeight       (double &) const;
    /* @cmember Get Option */  bool GetColorNumber      (UCHAR &) const;
    /* @cmember Get Option */  bool GetFilledFont       (bool &) const;
    /* @cmember Get Option */  bool GetFont             (std::wstring &) const;
    /* @cmember Get Option */  bool GetHorAlignment     (UCHAR &) const;
    /* @cmember Get Option */  bool GetJustify          (UCHAR &) const;
    /* @cmember Get Option */  bool GetLineSpacing      (double &) const;
    /* @cmember Get Option */  bool GetMinSpacing       (double &) const;
    /* @cmember Get Option */  bool GetMirrorText       (bool &) const;
    /* @cmember Get Option */  bool GetPath             (UCHAR &) const;
    /* @cmember Get Option */  bool GetPenNumber        (UCHAR &) const;
    /* @cmember Get Option */  bool GetSlantAngle       (double &) const;
    /* @cmember Get Option */  bool GetStandard         (UCHAR &) const;
    /* @cmember Get Option */  bool GetStaticSizeText   (bool &) const;
    /* @cmember Get Option */  bool GetStrikethrough    (bool &) const;
    /* @cmember Get Option */  bool GetSupSubScale      (double &) const;
    /* @cmember Get Option */  bool GetTextAngle        (double &) const;
    /* @cmember Get Option */  bool GetTextStyle        (UCHAR &) const;
    /* @cmember Get Option */  bool GetTextWidth        (UCHAR &) const;
    /* @cmember Get Option */  bool GetUnderline        (bool &) const;
    /* @cmember Get Option */  bool GetVerAlignment     (UCHAR &) const;
    /* @cmember Get Option */  bool GetCPlaneText       (bool &) const;

    /* @cmember Set Option */ bool GetTextAttrib       (CKBasicAttrib &rAttrib);

    // to be removed
    bool IsUnusedViewReadableText() const;
    bool SetViewReadableText(const bool bViewReadableText);
    bool GetViewReadableText(bool &) const;

private:

    friend class CKSDetailOptions;
    friend class CKSDimensionOptions;

    std::unique_ptr<CKDetailFormat> m_pFormat;
    };

/////////////////////////////////////////////////////////////////////////////
// Units Options

// @class
// The class for the Primary Units options of detail entities in KeyCreator.
class SDK_EXPORT CKSDetailUnits
    {
public:

    CKSDetailUnits();
    ~CKSDetailUnits();

    CKSDetailUnits(const CKSDetailUnits &rRight);

    CKSDetailUnits &operator=(const CKDetailUnits &rRight);
    CKSDetailUnits &operator=(const CKSDetailUnits &);

    void GetDetailUnits(CKDetailUnits &) const;

    // @cmember Sets all the unused flags to true, essentially clearing the options
    void Clear();

// @group Options use flags
    // @comm The Is* functions check the current use state of the option.  If the option
    //  is to be used they will return true, otherwise they will return false.<nl>
    //  The Set* functions set the state of the use flags.  Setting an option to a given
    //  value will automatically set the use flag to true, these Set* functions can be
    //  used to turn off certain options.  They will return the new state of the flag.

    /* @cmember Check flag */ bool IsUnusedBasicBoxGap          () const;
    /* @cmember Check flag */ bool IsUnusedBasicBoxGapIsValue   () const;
    /* @cmember Check flag */ bool IsUnusedConversionFactor     () const;
    /* @cmember Check flag */ bool IsUnusedDecimalPoint         () const;
    /* @cmember Check flag */ bool IsUnusedDisplayDualUnits     () const;
    /* @cmember Check flag */ bool IsUnusedDisplayLabel         () const;
    /* @cmember Check flag */ bool IsUnusedDualPlacement        () const;
    /* @cmember Check flag */ bool IsUnusedFractionChar         () const;
    /* @cmember Check flag */ bool IsUnusedLeadingZeros         () const;
    /* @cmember Check flag */ bool IsUnusedLowerTolerance       () const;
    /* @cmember Check flag */ bool IsUnusedLowerToleranceText   () const;
    /* @cmember Check flag */ bool IsUnusedPrecision            () const;
    /* @cmember Check flag */ bool IsUnusedRepresentation       () const;
    /* @cmember Check flag */ bool IsUnusedRound5ToEven         () const;
    /* @cmember Check flag */ bool IsUnusedRoundoff             () const;
    /* @cmember Check flag */ bool IsUnusedShowZeroTolerance    () const;
    /* @cmember Check flag */ bool IsUnusedToleranceMode        () const;
    /* @cmember Check flag */ bool IsUnusedTrailingZeros        () const;
    /* @cmember Check flag */ bool IsUnusedTwoLineFraction      () const;
    /* @cmember Check flag */ bool IsUnusedUnitLabel            () const;
    /* @cmember Check flag */ bool IsUnusedUnits                () const;
    /* @cmember Check flag */ bool IsUnusedUpperTolerance       () const;
    /* @cmember Check flag */ bool IsUnusedUpperToleranceText   () const;
    /* @cmember Check flag */ bool IsUnusedFitTolDisplay        () const;
    /* @cmember Check flag */ bool IsUnusedTolLeadingZeros      () const;
    /* @cmember Check flag */ bool IsUnusedTolTrailingZeros     () const;

    /* @cmember Set flag */ bool SetUnusedBasicBoxGap           (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedBasicBoxGapIsValue    (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedConversionFactor      (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedDecimalPoint          (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedDisplayDualUnits      (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedDisplayLabel          (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedDualPlacement         (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedFractionChar          (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedLeadingZeros          (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedLowerTolerance        (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedLowerToleranceText    (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedPrecision             (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedRepresentation        (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedRound5ToEven          (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedRoundoff              (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedShowZeroTolerance     (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedToleranceMode         (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedTrailingZeros         (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedTwoLineFraction       (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedUnitLabel             (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedUnits                 (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedUpperTolerance        (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedUpperToleranceText    (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedFitTolDisplay         (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedTolLeadingZeros       (bool bUnused = true);
    /* @cmember Set flag */ bool SetUnusedTolTrailingZeros      (bool bUnused = true);

// @group Set Member Data
    // @comm Sets the value for the given member.  These functions check the
    //  provided value to make sure it is in a valid range for the setting.
    //  If it is the value is set and the bit in <m m_MixedFlags> is cleared.
    //  If it is not a valid value, the bit in <m m_MixedFlags> is Set.
    //  Returns true if the value is set, false it it was not.

    /* @cmember Set Option */  bool SetBasicBoxGap          (const double dvalue);
    /* @cmember Set Option */  bool SetBasicBoxGapIsValue   (const bool bvalue);
    /* @cmember Set Option */  bool SetConversionFactor     (const double dValue);
    /* @cmember Set Option */  bool SetDecimalPoint         (const wchar_t cValue);
    /* @cmember Set Option valid only when used as dual units */
                               bool SetDisplayDualUnits     (const bool bValue);
    /* @cmember Set Option */  bool SetDisplayLabel         (const bool bValue);
    /* @cmember Set Option */  bool SetDualPlacement        (const UCHAR ucValue);
    /* @cmember Set Option */  bool SetFractionChar         (const std::wstring &csValue);
    /* @cmember Set Option */  bool SetLeadingZeros         (const bool bValue);
    /* @cmember Set Option */  bool SetLowerTolerance       (const double dValue);
    /* @cmember Set Option */  bool SetLowerToleranceText   (const CKString &csTxt);
    /* @cmember Set Option */  bool SetPrecision            (const UINT unValue);
    /* @cmember Set Option */  bool SetRepresentation       (const UCHAR ucValue);
    /* @cmember Set Option */  bool SetRound5ToEven         (const bool bValue);
    /* @cmember Set Option */  bool SetRoundoff             (const UINT unValue);
    /* @cmember Set Option */  bool SetShowZeroTolerance    (const bool bValue);
    /* @cmember Set Option */  bool SetToleranceMode        (const UCHAR ucValue);
    /* @cmember Set Option */  bool SetTrailingZeros        (const bool bValue);
    /* @cmember Set Option */  bool SetTwoLineFraction      (const bool bValue);
    /* @cmember Set Option */  bool SetUnitLabel            (const std::wstring &csValue);
    /* @cmember Set Option */  bool SetUnits                (const UCHAR ucValue);
    /* @cmember Set Option */  bool SetUpperTolerance       (const double dValue);
    /* @cmember Set Option */  bool SetUpperToleranceText   (const CKString &csTxt);
    /* @cmember Set Option */  bool SetFitTolDisplay        (const UCHAR Val);
    /* @cmember Set Option */  bool SetTolLeadingZeros      (const bool Val);
    /* @cmember Set Option */  bool SetTolTrailingZeros     (const bool Val);

// @group Get Member Data
    // @comm These functions get the value for the member.  If the value is
    //  mixed then the passed in variable is not changed.<nl>
    //  Return false if the value is unused.
    //  Return true if the value was retrieved.

    /* @cmember Get Option */  bool GetBasicBoxGap          (double &Val) const;
    /* @cmember Get Option */  bool GetBasicBoxGapIsValue   (bool &Val) const;
    /* @cmember Get Option */  bool GetConversionFactor     (double &Val) const;
    /* @cmember Get Option */  bool GetDecimalPoint         (wchar_t &Val) const;
    /* @cmember Get Option valid only when used as dual units */
                               bool GetDisplayDualUnits     (bool &Val) const;
    /* @cmember Get Option */  bool GetDisplayLabel         (bool &Val) const;
    /* @cmember Get Option */  bool GetDualPlacement        (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetFractionChar         (std::wstring &Val) const;
    /* @cmember Get Option */  bool GetLeadingZeros         (bool &Val) const;
    /* @cmember Get Option */  bool GetLowerTolerance       (double &Val) const;
    /* @cmember Get Option */  bool GetLowerToleranceText   (CKString &Val) const;
    /* @cmember Get Option */  bool GetPrecision            (UINT &Val) const;
    /* @cmember Get Option */  bool GetRepresentation       (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetRound5ToEven         (bool &Val) const;
    /* @cmember Get Option */  bool GetRoundoff             (UINT &Val) const;
    /* @cmember Get Option */  bool GetShowZeroTolerance    (bool &Val) const;
    /* @cmember Get Option */  bool GetToleranceMode        (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetTrailingZeros        (bool &Val) const;
    /* @cmember Get Option */  bool GetTwoLineFraction      (bool &Val) const;
    /* @cmember Get Option */  bool GetUnitLabel            (std::wstring &Val) const;
    /* @cmember Get Option */  bool GetUnits                (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetUpperTolerance       (double &Val) const;
    /* @cmember Get Option */  bool GetUpperToleranceText   (CKString &Val) const;
    /* @cmember Get Option */  bool GetFitTolDisplay        (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetTolLeadingZeros      (bool &Val) const;
    /* @cmember Get Option */  bool GetTolTrailingZeros     (bool &Val) const;

private:

    friend class CKSDimensionOptions;

    std::unique_ptr<CKDetailUnits> m_pUnits;
    };


/////////////////////////////////////////////////////////////////////////////
// DetailLines Options

// @class
// The class for the detail line options of detail entities for KeyCreator.
class SDK_EXPORT CKSDetailLines
    {
public:
    CKSDetailLines();
    ~CKSDetailLines();

    CKSDetailLines(const CKSDetailLines &rRight);

    CKSDetailLines &operator=(const CKDetailLines &rRight);
    CKSDetailLines &operator=(const CKSDetailLines &);

    void GetDetailLines(CKDetailLines &) const;

    // @cmember Sets all the unused flags to true, essentially clearing the options
    void Clear();

// @group Options use flags
    // @comm The Is* functions check the current use state of the option.  If the option
    //  is to be used they will return true, otherwise they will return false.<nl>
    //  The Set* functions set the state of the use flags.  Setting an option to a given
    //  value will automatically set the use flag to true, these Set* functions can be
    //  used to turn off certain options.  They will return the new state of the flag.

    /* @cmember Check flag */  bool IsUnusedArrowColorNumber            () const;
    /* @cmember Check flag */  bool IsUnusedArrowGap                    () const;
    /* @cmember Check flag */  bool IsUnusedArrowGapIsValue             () const;
    /* @cmember Check flag */  bool IsUnusedArrowLineStyle              () const;
    /* @cmember Check flag */  bool IsUnusedArrowLineWidth              () const;
    /* @cmember Check flag */  bool IsUnusedArrowPenNumber              () const;
    /* @cmember Check flag */  bool IsUnusedCreationArrowDirection      () const;
    /* @cmember Check flag */  bool IsUnusedDisplayStyle                () const;
    /* @cmember Check flag */  bool IsUnusedExtensionColorNumber        () const;
    /* @cmember Check flag */  bool IsUnusedExtensionDimTextAllowed     () const;
    /* @cmember Check flag */  bool IsUnusedExtensionGap                () const;
    /* @cmember Check flag */  bool IsUnusedExtensionGapIsValue         () const;
    /* @cmember Check flag */  bool IsUnusedExtensionLineStyle          () const;
    /* @cmember Check flag */  bool IsUnusedExtensionLineWidth          () const;
    /* @cmember Check flag */  bool IsUnusedExtensionPenNumber          () const;
    /* @cmember Check flag */  bool IsUnusedExtensionStyle              () const;
    /* @cmember Check flag */  bool IsUnusedFirstArrowHeight            () const;
    /* @cmember Check flag */  bool IsUnusedFirstArrowHeightIsValue     () const;
    /* @cmember Check flag */  bool IsUnusedFirstArrowhead              () const;
    /* @cmember Check flag */  bool IsUnusedJogLength                   () const;
    /* @cmember Check flag */  bool IsUnusedJogLengthIsValue            () const;
    /* @cmember Check flag */  bool IsUnusedLeaderColorNumber           () const;
    /* @cmember Check flag */  bool IsUnusedLeaderLineStyle             () const;
    /* @cmember Check flag */  bool IsUnusedLeaderLineWidth             () const;
    /* @cmember Check flag */  bool IsUnusedLeaderMinExtension          () const;
    /* @cmember Check flag */  bool IsUnusedLeaderMinExtensionIsValue   () const;
    /* @cmember Check flag */  bool IsUnusedLeaderPenNumber             () const;
    /* @cmember Check flag */  bool IsUnusedLeaderSide                  () const;
    /* @cmember Check flag */  bool IsUnusedLeaderStyle                 () const;
    /* @cmember Check flag */  bool IsUnusedLeaderToTextGap             () const;
    /* @cmember Check flag */  bool IsUnusedLeaderToTextGapIsValue      () const;
    /* @cmember Check flag */  bool IsUnusedLeaderUnderText             () const;
    /* @cmember Check flag */  bool IsUnusedSecondArrowHeight           () const;
    /* @cmember Check flag */  bool IsUnusedSecondArrowHeightIsValue    () const;
    /* @cmember Check flag */  bool IsUnusedSecondArrowhead             () const;
    /* @cmember Check flag */  bool IsUnusedShortenedDetails            () const;
    /* @cmember Check flag */  bool IsUnusedStoreActualArrowDirection   () const;
    /* @cmember Check flag */  bool IsUnusedStoredArrowDirection        () const;

    /* @cmember Set flag */  bool SetUnusedArrowColorNumber          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedArrowGap                  (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedArrowGapIsValue           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedArrowLineStyle            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedArrowLineWidth            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedArrowPenNumber            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedCreationArrowDirection    (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedDisplayStyle              (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionColorNumber      (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionDimTextAllowed   (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionGap              (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionGapIsValue       (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionLineStyle        (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionLineWidth        (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionPenNumber        (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedExtensionStyle            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedFirstArrowHeight          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedFirstArrowHeightIsValue   (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedFirstArrowhead            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedJogLength                 (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedJogLengthIsValue          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderColorNumber         (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderLineStyle           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderLineWidth           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderMinExtension        (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderMinExtensionIsValue (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderPenNumber           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderSide                (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderStyle               (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderToTextGap           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderToTextGapIsValue    (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedLeaderUnderText           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSecondArrowHeight         (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSecondArrowHeightIsValue  (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSecondArrowhead           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedShortenedDetails          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedStoreActualArrowDirection (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedStoredArrowDirection      (bool bUnused = true);

// @group Set Member Data
    // @comm Sets the value for the given member.  These functions check the
    //  provided value to make sure it is in a valid range for the setting.
    //  If it is the value is set and the bit in <m m_MixedFlags> is cleared.
    //  If it is not a valid value, the bit in <m m_MixedFlags> is Set.
    //  Returns true if the value is set, false it it was not.

    /* @cmember Set Option */  bool SetArrowColorNumber         (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetArrowGap                 (const double dVal);
    /* @cmember Set Option */  bool SetArrowGapIsValue          (const bool bVal);
    /* @cmember Set Option */  bool SetArrowLineStyle           (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetArrowLineWidth           (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetArrowPenNumber           (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetCreationArrowDirection   (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetDisplayStyle             (UCHAR ucVal);
    /* @cmember Set Option */  bool SetExtensionColorNumber     (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetExtensionDimTextAllowed  (const UCHAR bVal);
    /* @cmember Set Option */  bool SetExtensionGap             (const double dVal);
    /* @cmember Set Option */  bool SetExtensionGapIsValue      (const bool bVal);
    /* @cmember Set Option */  bool SetExtensionLineStyle       (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetExtensionLineWidth       (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetExtensionPenNumber       (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetExtensionStyle           (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetFirstArrowHeight         (const double dVal);
    /* @cmember Set Option */  bool SetFirstArrowHeightIsValue  (const bool bVal);
    /* @cmember Set Option */  bool SetFirstArrowhead           (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetJogLength                (const double dVal);
    /* @cmember Set Option */  bool SetJogLengthIsValue         (const bool bVal);
    /* @cmember Set Option */  bool SetLeaderColorNumber        (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetLeaderLineStyle          (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetLeaderLineWidth          (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetLeaderMinExtension       (const double dVal);
    /* @cmember Set Option */  bool SetLeaderMinExtensionIsValue(const bool bVal);
    /* @cmember Set Option */  bool SetLeaderPenNumber          (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetLeaderSide               (const UCHAR ucValue);
    /* @cmember Set Option */  bool SetLeaderStyle              (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetLeaderToTextGap          (const double dVal);
    /* @cmember Set Option */  bool SetLeaderToTextGapIsValue   (const bool bVal);
    /* @cmember Set Option */  bool SetLeaderUnderText          (const bool bVal);
    /* @cmember Set Option */  bool SetSecondArrowHeight        (const double dVal);
    /* @cmember Set Option */  bool SetSecondArrowHeightIsValue (const bool bVal);
    /* @cmember Set Option */  bool SetSecondArrowhead          (const UCHAR ucVal);
    /* @cmember Set Option */  bool SetShortenedDetails         (const bool bVal);
    /* @cmember Set Option */  bool SetStoreActualArrowDirection(const bool bVal);
    /* @cmember Set Option */  bool SetStoredArrowDirection     (const UCHAR ucVal);

    /* @cmember Set Option */ bool SetArrowAttrib       (CKBasicAttrib &rAttrib);
    /* @cmember Set Option */ bool SetExtensionAttrib   (CKBasicAttrib &rAttrib);
    /* @cmember Set Option */ bool SetLeaderAttrib      (CKBasicAttrib &rAttrib);

// @group Get Member Data
    // @comm These functions get the value for the member.  If the value is
    //  mixed then the passed in variable is not changed.<nl>
    //  Return false if the value is unused.
    //  Return true if the value was retrieved.

    /* @cmember Get Option */  bool GetArrowColorNumber         (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetArrowGap                 (double &Val) const;
    /* @cmember Get Option */  bool GetArrowGapIsValue          (bool &Val) const;
    /* @cmember Get Option */  bool GetArrowLineStyle           (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetArrowLineWidth           (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetArrowPenNumber           (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetCreationArrowDirection   (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetDisplayStyle             (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionColorNumber     (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionDimTextAllowed  (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionGap             (double &Val) const;
    /* @cmember Get Option */  bool GetExtensionGapIsValue      (bool &Val) const;
    /* @cmember Get Option */  bool GetExtensionLineStyle       (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionLineWidth       (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionPenNumber       (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetExtensionStyle           (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetFirstArrowHeight         (double &Val) const;
    /* @cmember Get Option */  bool GetFirstArrowHeightIsValue  (bool &Val) const;
    /* @cmember Get Option */  bool GetFirstArrowhead           (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetJogLength                (double &Val) const;
    /* @cmember Get Option */  bool GetJogLengthIsValue         (bool &Val) const;
    /* @cmember Get Option */  bool GetLeaderColorNumber        (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderLineStyle          (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderLineWidth          (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderMinExtension       (double &Val) const;
    /* @cmember Get Option */  bool GetLeaderMinExtensionIsValue(bool &Val) const;
    /* @cmember Get Option */  bool GetLeaderPenNumber          (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderSide               (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderStyle              (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetLeaderToTextGap          (double &Val) const;
    /* @cmember Get Option */  bool GetLeaderToTextGapIsValue   (bool &Val) const;
    /* @cmember Get Option */  bool GetLeaderUnderText          (bool &Val) const;
    /* @cmember Get Option */  bool GetSecondArrowHeight        (double &Val) const;
    /* @cmember Get Option */  bool GetSecondArrowHeightIsValue (bool &Val) const;
    /* @cmember Get Option */  bool GetSecondArrowhead          (UCHAR &Val) const;
    /* @cmember Get Option */  bool GetShortenedDetails         (bool &Val)  const;
    /* @cmember Get Option */  bool GetStoreActualArrowDirection(bool &Val) const;
    /* @cmember Get Option */  bool GetStoredArrowDirection     (UCHAR &Val) const;

    /* @cmember Set Option */ bool GetArrowAttrib       (CKBasicAttrib &rAttrib);
    /* @cmember Set Option */ bool GetExtensionAttrib   (CKBasicAttrib &rAttrib);
    /* @cmember Set Option */ bool GetLeaderAttrib      (CKBasicAttrib &rAttrib);

// Depricated members
    bool IsUnusedExtensionDimText() const
        {return(IsUnusedExtensionDimTextAllowed());}
    bool SetUnusedExtensionDimText(bool bUnused = true)
        {return(SetUnusedExtensionDimTextAllowed(bUnused));}
    bool SetExtensionDimText(const bool bVal)
        {return(SetExtensionDimTextAllowed(bVal?UCHAR(1):UCHAR(0)));}
    bool GetExtensionDimText(UCHAR &Val) const
        {return(GetExtensionDimTextAllowed(Val));}

private:

    void SetAttrib(CKBasicAttrib &rAttrib, CKAttrib &attr);

    friend class CKSDetailOptions;
    friend class CKSDimensionOptions;

    std::unique_ptr<CKDetailLines> m_pLines;
    };

//////////////////////////////////////////////////////////////////////////
// DetailDimText Options

// @class
// The class for the dimension text options for KeyCreator.
class SDK_EXPORT CKSDetailDimText
    {
public:
    CKSDetailDimText();
    ~CKSDetailDimText();

    CKSDetailDimText(const CKSDetailDimText &rRight);

    CKSDetailDimText &operator=(const CKDetailDimText &rRight);
    CKSDetailDimText &operator=(const CKSDetailDimText &);

    void GetDetailDimText(CKDetailDimText &) const;

    // @cmember Sets all the unused flags to true, essentially clearing the options
    void Clear();

// @group Options use flags
    // @comm The Is* functions check the current use state of the option.  If the option
    //  is to be used they will return true, otherwise they will return false.<nl>
    //  The Set* functions set the state of the use flags.  Setting an option to a given
    //  value will automatically set the use flag to true, these Set* functions can be
    //  used to turn off certain options.  They will return the new state of the flag.

    /* @cmember Check flag */  bool IsUnusedIsManualText         () const;
    /* @cmember Check flag */  bool IsUnusedManualText           () const;
    /* @cmember Check flag */  bool IsUnusedManualValue          () const;
    /* @cmember Check flag */  bool IsUnusedModifier             () const;
    /* @cmember Check flag */  bool IsUnusedModifierAsFont       () const;
    /* @cmember Check flag */  bool IsUnusedPrefix               () const;
    /* @cmember Check flag */  bool IsUnusedReference            () const;
    /* @cmember Check flag */  bool IsUnusedSpaceAfterModifier   () const;
    /* @cmember Check flag */  bool IsUnusedSuffix               () const;
    /* @cmember Check flag */  bool IsUnusedUseManualValue       () const;
    /* @cmember Check flag */  bool IsUnusedPrefixAbove          () const;
    /* @cmember Check flag */  bool IsUnusedSuffixBelow          () const;

    /* @cmember Set flag */  bool SetUnusedIsManualText         (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedManualText           (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedManualValue          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedModifier             (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedModifierAsFont       (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedPrefix               (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedReference            (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSpaceAfterModifier   (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSuffix               (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedUseManualValue       (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedPrefixAbove          (bool bUnused = true);
    /* @cmember Set flag */  bool SetUnusedSuffixBelow          (bool bUnused = true);

// @group Set Member Data
    // @comm Sets the value for the given member.  These functions check the
    //  provided value to make sure it is in a valid range for the setting.
    //  If it is the value is set and the bit in <m m_MixedFlags> is cleared.
    //  If it is not a valid value, the bit in <m m_MixedFlags> is Set.
    //  Returns true if the value is set, false it it was not.

    /* @cmember Set Option */  bool SetIsManualText         (const bool bVal);
    /* @cmember Set Option */  bool SetManualText           (const CKString &csTxt);
    /* @cmember Set Option */  bool SetManualValue          (const double dVal);
    /* @cmember Set Option */  bool SetModifier             (const CKSDimensionModifier ucVal);
    /* @cmember Set Option */  bool SetModifierAsFont       (const bool bVal);
    /* @cmember Set Option */  bool SetPrefix               (const CKString &csTxt);
    /* @cmember Set Option */  bool SetReference            (const bool bVal);
    /* @cmember Set Option */  bool SetSpaceAfterModifier   (const bool bVal);
    /* @cmember Set Option */  bool SetSuffix               (const CKString &csTxt);
    /* @cmember Set Option */  bool SetUseManualValue       (const bool bVal);
    /* @cmember Set Option */  bool SetPrefixAbove          (const bool bVal);
    /* @cmember Set Option */  bool SetSuffixBelow          (const bool bVal);

// @group Get Member Data
    // @comm These functions get the value for the member.  If the value is
    //  mixed then the passed in variable is not changed.<nl>
    //  Return false if the value is unused.
    //  Return true if the value was retrieved.

    /* @cmember Get Option */  bool GetIsManualText         (bool &Val) const;
    /* @cmember Get Option */  bool GetManualText           (CKString &Val) const;
    /* @cmember Get Option */  bool GetManualValue          (double &Val) const;
    /* @cmember Get Option */  bool GetModifier             (CKSDimensionModifier &Val) const;
    /* @cmember Get Option */  bool GetModifierAsFont       (bool &Val) const;
    /* @cmember Get Option */  bool GetPrefix               (CKString &Val) const;
    /* @cmember Get Option */  bool GetReference            (bool &Val) const;
    /* @cmember Get Option */  bool GetSpaceAfterModifier   (bool &Val) const;
    /* @cmember Get Option */  bool GetSuffix               (CKString &Val) const;
    /* @cmember Get Option */  bool GetUseManualValue       (bool &Val) const;
    /* @cmember Get Option */  bool GetPrefixAbove          (bool &Val) const;
    /* @cmember Get Option */  bool GetSuffixBelow          (bool &Val) const;

    // @cmember Value type
    UCHAR GetValueType() const;

private:

    friend class CKSDimensionOptions;

    std::unique_ptr<CKDetailDimText> m_pDimText;
    };


// @class
//  Detail options for detail entities.
//
// @base public | CObject
class SDK_EXPORT CKSDetailOptions
    {
    public:
        CKSDetailOptions();
        CKSDetailOptions(const CKSDetailOptions &rRight);
        explicit CKSDetailOptions(CKPart &rDoc, bool bGetDefaults = false);

        CKSDetailOptions &operator=(const CKSDetailOptions &);

        // @cmember Initialize the elements as all Unused or all Used.
        void Initialize(bool bUnUsed = true);

        const CKDetailFormat &GetCKFormat() const;
        const CKDetailLines  &GetCKLines() const;
        void GetCKDetailOptions(CKDetailOptions &rDetailOptions) const;

        void Match(CKSDetailOptions &rRight);
        void Merge(CKSDetailOptions &rRight);

    public:
        // @cmember Text format options
        CKSDetailFormat  m_Format;

        // @cmember Detail lines options
        CKSDetailLines   m_Lines;

        // @cmember Entity attributes
        CKEntityAttrib m_EntAttrib;
    };

// @class
//  Detail options for dimension entities.
//
// @base public | CKSDetailOptions
class SDK_EXPORT CKSDimensionOptions : public CKSDetailOptions
    {
public:
    CKSDimensionOptions();
    CKSDimensionOptions(const CKSDimensionOptions &rRight);
    CKSDimensionOptions &operator=(const CKSDimensionOptions &);

    // @cmember Initialize the elements as all Unused or all Used.
    void Initialize(bool bUnUsed = true);

    const CKDetailDimText &GetCKDimText() const;
    const CKDetailUnits   &GetCKPrimaryUnits() const;
    const CKDetailUnits   &GetCKDualUnits() const;

    void Merge(CKSDimensionOptions &rRight);

public:
    // @cmember Primary units options
    CKSDetailUnits   m_Units;

    // @cmember Dual units options
    CKSDetailUnits   m_DualUnits;

    // @cmember Dimension text options
    CKSDetailDimText m_DimText;
    };
#endif