// Copyright Kubotek Corporation, 1991-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_DRAFT_H_LOADED
#define CK_DRAFT_H_LOADED

// @doc EXTERNAL SDK

#include "ck_attr.h"
#include "ck_types.h"
#include "CKSMatrix.h"

class CKSLocation;

class ck_string_entry;
class ck_string;
class CKCoord;
class CKWitness;
class CKWitnessArc;
class CKArrowhead;
class CKLeader;
class CKLeaderArc;
class CKRefLine;
class CKRefArc;
class CKDrawInstAttribMod;
class CKDrawInstTrimMod;
class DatumRef;

// @class A single string entry which holds a symbol and text.
//  If the symbol is present it always preceeds the text.
class CKStringEntry
    {
public:
    CKStringEntry() : m_ucSymbol(CK_NoSymbol) {}
    CKStringEntry(const std::wstring &csText) :
        m_ucSymbol(CK_NoSymbol), m_csText(csText) {}

    CKStringEntry(const ck_string_entry &);
    operator ck_string_entry() const;
    CKStringEntry &operator=(const ck_string_entry &);

    // @cmember The symbol
    CKSSymbolType m_ucSymbol;

    // @cmember The text string
    std::wstring m_csText;
    };

// @class A string consisting of <c CKStringEntry> elements.
class SDK_EXPORT CKString
    {
public:
    CKString() {}
    CKString(int nEntries) : m_Entries(nEntries) { }
    CKString(const ck_string &csText) { operator=(csText); }
    CKString(const std::wstring &lpszText) { operator=(lpszText); }

    operator std::wstring() const;

    operator ck_string() const;

    CKString &operator=(const ck_string &rRight);
    CKString &operator=(const std::wstring &csText);

    void GetString(ck_string &) const;

    // @cmember Array of string entries.
    std::vector<CKStringEntry> m_Entries;
    };

typedef std::vector<CKString> CKStringArray;

template<>
SDK_EXPORT ck_string *g_new_array(size_t n, const std::vector<CKString> &rSource);

//@class The text of a detail entity.
class CKSDimText
    {
public:
    CKSDimText() {}
    CKSDimText(const CKString &cksDimText, const std::wstring &lpszPrefix,
               const std::wstring &lpszSuffix, const std::wstring &lpszPosTol,
               const std::wstring &lpszNegTol);

    // @cmember The main text for the dimension
    CKString m_cksDimText;

    // @cmember The prefix
    std::wstring m_csPrefix;

    // @cmember The suffix
    std::wstring m_csSuffix;

    // @cmember The Positive tolerance
    std::wstring m_csPosTol;

    // @cmember The Negative tolerance
    std::wstring m_csNegTol;
    };

// @class The line measured by a dimension
class CKSRefLine
    {
public:
    CKSRefLine() {}

    CKSRefLine(const CKRefLine &);
    CKSRefLine &operator=(const CKRefLine &);

    operator CKRefLine() const;

    // @cmember The start point of the line
    CKSCoord m_ptStart;

    // @cmember The end point of the line
    CKSCoord m_ptEnd;
    };

typedef std::vector<CKSRefLine> CKSRefLineArray;

// @class The arc measured by a dimension
class CKSRefArc
    {
public:
    CKSRefArc() : m_dRadius(0), m_dStartAngle(0), m_dEndAngle(0) {}

    CKSRefArc(const CKRefArc &);
    CKSRefArc &operator=(const CKRefArc &);

    operator CKRefArc() const;

    // @cmember The center point of the arc.
    CKSCoord m_ptCenter;

    // @cmember The radius of the arc
    double m_dRadius;

    // @cmember The start angle of the arc, in radians.
    // Range: 0 to 2 * PI.
    double m_dStartAngle;

    // @cmember The end angle of the arc, in radians
    // Range: m_dStartAngle to m_dStartAngle + 2 * PI
    double m_dEndAngle;
    };

typedef std::vector<CKSRefArc> CKSRefArcArray;

// @class The data for a Witness line
class CKSWitness
    {
public:
    CKSWitness() {}

    CKSWitness(const CKWitness &);

    CKSWitness &operator=(const CKWitness &);

    operator CKWitness() const;

    // @cmember The points of the witness line
    std::vector<CKSCoord> m_aptPoints;

    // @cmember Array of blanked segment numbers, zero based
    std::vector<int> m_anSegmentNumbers;
    };

typedef std::vector<CKSWitness> CKSWitnessArray;

// @class The data for a Witness arc
class CKSWitnessArc
    {
public:
    CKSWitnessArc() : m_dRadius(0),  m_dStartAngle(0), m_dEndAngle(0) {}

    CKSWitnessArc(const CKWitnessArc &);
    CKSWitnessArc &operator=(const CKWitnessArc &);

    operator CKWitnessArc() const;

    // @cmember The center point of the witness arc.
    CKSCoord m_ptCenter;

    // @cmember The radius of the witness arc.
    double m_dRadius;

    // @cmember The start angle of the arc, in radians.
    // Range: 0 to 2 * PI.
    double m_dStartAngle;

    // @cmember The end angle of the arc, in radians
    // Range: m_dStartAngle to m_dStartAngle + 2 * PI
    double m_dEndAngle;
    };

typedef std::vector<CKSWitnessArc> CKSWitnessArcArray;

// @class Arrowhead
class CKSArrowhead
    {
public:
    CKSArrowhead() : m_dAngle(0) {}

    CKSArrowhead(const CKArrowhead &);
    CKSArrowhead &operator=(const CKArrowhead &);

    operator CKArrowhead() const;

    // @cmember The coordinate of the arrowhead tip
    CKSCoord m_ptTip;

    // @cmember The rotation angle of the arrowhead, measured
    // counter-clockwise from the positive x axis.
    double m_dAngle;
    };

typedef std::vector<CKSArrowhead> CKSArrowheadArray;

// @class A Leader line.  This class derives from <c CKSWitness> and
// adds a <c CKSArrowhead> object.  Leaders start at the arrowhead
// running towards the tail.
// @base public | CKSWitness
class CKSLeader : public CKSWitness
    {
public:
    CKSLeader() {}

    CKSLeader(const CKLeader &);
    CKSLeader &operator=(const CKLeader &);

    operator CKLeader() const;

    // @cmember The leader's arrowhead.
    CKSArrowhead m_arrowhead;
    };

typedef std::vector<CKSLeader> CKSLeaderArray;

// @class A Leader arc.  This class derives from <c CKSWitnessArc> and
// adds a <c CKSArrowhead> object.  Leader arcs start at the arrowhead
// running towards the tail.
// @base public | CKSWitnessArc
class CKSLeaderArc : public CKSWitnessArc
    {
public:
    CKSLeaderArc() {}

    CKSLeaderArc(const CKLeaderArc &);
    CKSLeaderArc &operator=(const CKLeaderArc &);

    operator CKLeaderArc() const;

    // @cmember The leader's arrowhead.
    CKSArrowhead m_arrowhead;
    };

typedef std::vector<CKSLeaderArc> CKSLeaderArcArray;

// @group Instance Modification classes

// @class A Modification.  This is the base class for the instance
//  modifications.  This class is never instantiated directly, but is used
//  as the common base class for all modification types.
class CKSDrawInstMod : public GAtom
    {
protected:
    // @cmember Constructor
    CKSDrawInstMod(CKSEntity &rEnt) : m_pEntity(rEnt) {}

public:
    // @cmember The entity this modification affects.
    CKSEntity m_pEntity;
    };

typedef ptr_array<CKSDrawInstMod> CKSDrawInstModArray;

// @class An Attribute modification.  This specifies that the entity is shown
//  with attributes that may be different from that of the original model
//  geometry being represented.
// @base public | CKSDrawInstMod
class CKSDrawInstAttribMod : public CKSDrawInstMod
    {
public:
    CKSDrawInstAttribMod(CKSEntity &rEnt, const CKDrawInstAttribMod *pSource);

    // @cmember The new attributes of the entity being modified.
    CKBasicAttrib m_Attrib;
    };

// @class A Blank modification.  The entity this modification refers to is not
//  shown in the drawing instance if this modification exists.
// @base public | CKSDrawInstMod
class CKSDrawInstBlankMod : public CKSDrawInstMod
    {
public:
    CKSDrawInstBlankMod(CKSEntity &rEnt);
    };

// @class A Trim modification.  The entity is trimmed at the locations
//  specified by this modification
// @base public | CKSDrawInstMod
class CKSDrawInstTrimMod : public CKSDrawInstMod
    {
public:
    CKSDrawInstTrimMod(CKSEntity &rEnt, const CKDrawInstTrimMod *pSource);

    // @cmember Is this entity trimmed at the start, and/or end?
    bool m_bStartTrim, m_bEndTrim;

    // @cmember Segment of the start/end trim location.
    int m_nStartSeg, m_nEndSeg;

    // @cmember Parameter of the start/end trim location.
    double m_dStartParam, m_dEndParam;
    };

class DatumRef;

// @class A single datum reference in a feature control frame, which should
// then match with a CKDatum elsewhere in the drawing. (the matching behavior,
// however, is not enforced, since a CKNote or other method can be used to
// mark a datum).
class SDK_EXPORT CKSDatumRef
    {
public:
    // @cmember Default constructor
    CKSDatumRef();

    // @cmember Constructor from core type
    CKSDatumRef(const DatumRef &ref);

    // @cmember Construction of a DatumRef through its literal values
    CKSDatumRef(CKSEntity &pDatum1, const std::wstring &lpszDatum1,
                CKSSymbolType eMaterial1, CKSEntity *pDatum2 = NULL,
                const std::wstring *pcsDatum2 = NULL,
                CKSSymbolType eMaterial2 = CK_NoSymbol);

    void PutValues(DatumRef &rDatumRef) const;
    void GetValues(const DatumRef &rDatumRef);

    // @cmember The <c CKDatum> object that represents this datum
    CKSEntity m_pDatum1, m_pDatum2;

    // @cmember The MaterialCondition modifier for this datum reference.
    CKSSymbolType m_nMaterial1, m_nMaterial2;

    // @cmember The datum identifier string.
    CKString m_csDatum;
    };

typedef std::vector<CKSDatumRef> CKSDatumRefArray;

class FeatureControlFrame;

// @class The data for a single frame of a geotol symbol
class SDK_EXPORT CKSFeatureControlFrame
    {
public:
    // @cmember Constructors
    CKSFeatureControlFrame();

    // @cmember Constructor
    CKSFeatureControlFrame(CKS::GDT::FrameType nFrameType,
                           CKSSymbolType nSymbolType,
                           CKSDimensionModifier nTolModifier,
                           const std::wstring &lpszTolerance,
                           CKSSymbolType nMaterial,
                           const std::wstring *pcsMaximum = NULL,
                           bool bProjected = false,
                           const std::wstring *pcsProjected = NULL,
                           bool bStatistical = false, bool bFreeState = false,
                           bool bTangentPlane = false, bool bEnvelope = false,
                           bool bReciprocity = false,
                           CKSDatumRefArray *pDatumRefs = NULL);

    // Put class values into the internal format
    void PutValues(FeatureControlFrame &rFrame) const;

    // Get class values from the internal format
    void GetValues(const FeatureControlFrame &rFrame);

    // @cmember The FrameType of the symbol
    CKS::GDT::FrameType m_nFrameType;

    // @cmember The type of control, a subset of <t CKSSymbolType>
    CKSSymbolType m_nSymbolType;

    // @cmember The tolerance modifier
    CKSDimensionModifier m_nTolModifier;

    // @cmember The tolerance displayed by this entry
    std::wstring m_csTolerance;

    // @cmember The MaterialCondition modifier
    CKSSymbolType m_nMaterial;

    // @cmember The maximum value for perpendicular and parallel
    std::wstring m_csMaximum;

    // @cmember Does this tolerance zone project past the part surface?
    bool m_bProjected;

    // @cmember The distance the tolerance zone projects past the part surface.
    std::wstring m_csProjected;

    // @cmember Is this tolerance arrived at through calculations?
    bool m_bStatistical;

    // @cmember Is this tolerance applicable in a free state?
    bool m_bFreeState;

    // @cmember Is this tolerance applied in a tangent plane?
    bool m_bTangentPlane;

    // @cmember Does this follow the Envelope principle? (only applies to ISO)
    // implied in ANSI/ASME standards.
    bool m_bEnvelope;

    // @cmember Not used yet, may be in next ISO standard
    bool m_bReciprocity;

    // @cmember Dynamic Profile
    bool m_bDynamicProfile;

    // @cmember The primary, secondary, and tertiary <c CKSDatumRef>s,
    // in that order.
    CKSDatumRefArray m_aDatumRefs;
    };

#endif  /* CK_DRAFT_H_LOADED */ /* MUST BE LAST LINE OF FILE */
