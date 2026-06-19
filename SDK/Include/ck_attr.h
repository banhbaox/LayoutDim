// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
#ifndef CK_ATTR_H_LOADED
#define CK_ATTR_H_LOADED

// Care and handling of ck_attr.h
//
//   To reduce dependancies, this header should not include any other headers.
//   This header shares values between the Core the SDK.
//
// In general, enums within this header should use the nomenclature CKSEnumTypeName
// We've been keeping the name of enum values in allcaps for legacy values to
// ease porting issues for our Solution Partners.  New enums should use the more
// "modern" mixed case look.

// @doc EXTERNAL SDK

class CKAttrib;

// @class Those attributes common to all displayed objects.
class CKBasicAttrib
    {
public:
    CKBasicAttrib(UCHAR ucColor, UCHAR ucStyle, UCHAR ucWidth,
                  UCHAR ucPen) :
        m_ucColorNumber(ucColor), m_ucStyle(ucStyle),
        m_ucWidth(ucWidth), m_ucPenNumber(ucPen) {}

    CKBasicAttrib() : m_ucColorNumber(0xFF), m_ucStyle(0xFF),
        m_ucWidth(0xFF), m_ucPenNumber(0xFF) {}

    // @cmember The color number, 0-63
    UCHAR m_ucColorNumber;

    // @cmember The line style, see <t CKSLTypes> for values
    UCHAR m_ucStyle;

    // @cmember The line width.  Odd values from 1 to 15
    UCHAR m_ucWidth;

    // @cmember The pen number, 1-8.
    UCHAR m_ucPenNumber;
    };

// @class The data common to all entities.
// @base public | CKBasicAttrib
class CKEntityAttrib : public CKBasicAttrib
    {
    friend class CKEntity;
public:

    CKEntityAttrib(UCHAR ucColor, UCHAR ucType, UCHAR ucWidth,
                   UCHAR ucPen) :
        CKBasicAttrib(ucColor, ucType, ucWidth, ucPen),
        m_crFillColor(0xFFFFFFFF), m_ucGroupNum(UCHAR(-1)), m_ucSubGroupNum(0),
        m_ulRefControl(ULONG(-1)), m_ulID(0) {}

    CKEntityAttrib() :
        m_crFillColor(0xFFFFFFFF), m_ucGroupNum(UCHAR(-1)), m_ucSubGroupNum(0),
        m_ulRefControl(ULONG(-1)), m_ulID(0) {}

    // @cmember The fill color, primarily for polylines.
    // This is a standard RGB color value.
    COLORREF m_crFillColor;

    // @cmember The entity's group number, 1-127, or 0 if not in a group
    UCHAR m_ucGroupNum;

    // @cmember The entity's subgroup number, 0-255
    UCHAR m_ucSubGroupNum;

    // @cmember The entity's ref control flags
    ULONG m_ulRefControl;

    // @cmember The entity's ID
    ULONG m_ulID;
    };

// @enum Valid values for the dimensioning standard.
enum CKSStandard
    {
    CK_StdOther, // @emem User-defined
    CK_StdANSI,  // @emem ANSI
    CK_StdISO,   // @emem ISO
    CK_StdDIN,   // @emem DIN
    CK_StdJIS,   // @emem JIS
    CK_StdKS,    // @emem KS
    CK_NumCKSStandard   // @emem use for range test on this enum
    };

// @enum Valid values for a dimension's representation
enum CKSDimRep
    {
    CK_RepDecimal,    // @emem decimal
    CK_RepFractional, // @emem fractional
    CK_RepFeetInches, // @emem feet/inches
    CK_RepDegrees,    // @emem degrees
    CK_RepDegMinSec,  // @emem degrees, minutes, seconds
    CK_RepRadians,    // @emem radians
    CK_RepGradians,   // @emem gradians
    CK_RepDegMin,     // @emem degrees, minutes
    CK_NumCKSDimRep   // @emem use for range test on this enum
    };

// @enum Value type values.
enum CKSValType
    {
    CK_VAL_ACTUAL,
    CK_VAL_TEXT,
    };

// @enum Tolerance values
enum CKSTolerance
    {
    CK_TolNone,        // @emem none
    CK_TolBasic,       // @emem basic dimension
    CK_TolPM2Lines,    // @emem +/- 2 lines
    CK_TolPM1Line,     // @emem +/- 1 line
    CK_TolLimit2Lines, // @emem limit
    CK_TolLimit1Line,  // @emem limit on one line
    CK_TolReference,   // @emem Reference tolerance
    CK_TolISOFit2Line, // @emem ISO fit tolerance
    CK_TolISOFitSingle,// @emem Single ISO fit tolerance
    CK_TolManualText,  // @emem user entered text
    CK_NumCKSTolerance // @emem use for range test on this enum
    };

// @enum Fit Tolerance Display modes
enum CKSFitTolDisplayStyle
    {
    CK_FTDisplayGrade,       // @emem Display as "Grade"
    CK_FTDisplayValue,       // @emem Display as "Value"
    CK_FTDisplayGradeValue,  // @emem Display as "Grade-Value"
    CK_FTDisplayValueGrade,  // @emem Display as "Value-Grade"
    CK_FTDisplayGrade_Value, // @emem Display as "Grade-(Value)"
    CK_NumCKSFitTolDisplay   // @emem used for range testing
    };

// @enum Text Style Values
enum CKSTxtStyle
    {
    CK_STY_LEFT,     // @emem left justified
    CK_STY_CENTER,   // @emem center justified
    CK_STY_RIGHT     // @emem right justified
    };

// @enum Text Path Values
enum CKSTxtPath
    {
    CK_PATH_RIGHT, // @emem left to right
    CK_PATH_DOWN,  // @emem up to down
    CK_PATH_LEFT,  // @emem right to left
    CK_PATH_UP     // @emem down to up
    };

// @enum Horizontal Text Placement Values.
enum CKSHorAlign
    {
    CK_HPL_RIGHT,   // @emem text placement right
    CK_HPL_CENTER,  // @emem text placement center
    CK_HPL_LEFT,    // @emem text placement left
    };

// @enum Vertical Text Placement Values.
enum CKSVertAlign
    {
    CK_VPL_BELOW,   // @emem text placement below
    CK_VPL_MIDDLE,  // @emem text placement center
    CK_VPL_ABOVE,    // @emem text placement above
    };

// @enum Dimension Orientation Type Values.
enum CKSOrientType
    {
    CK_OrientHorizontal,  // @emem horizontal dim
    CK_OrientVertical,    // @emem vertical dim
    CK_OrientParallel,    // @emem parallel dim
    CK_NumCKSOrientType   // @emem use for range test on this enum
    };

// @enum Display styles for dimensions
// Note that this does not imply that you can, for instance, change
// an Ordinate Linear dimension to a Radial Circular dimension
// simply by changing it's style.
enum CKSDimStyle
    {
    CK_OrdinateLinear,          // @emem Ordinate style dim
    CK_OrdinateLinearAligned,   // @emem Ordinate style dim, text aligned
    CK_BaselineLinear,          // @emem Baseline style dim
    CK_RunningLinear,           // @emem Running style dim
    CK_DiametralCircular,       // @emem Diametral circular dimension
    CK_RadialCircular,          // @emem Radial circular dimension
    CK_CStyleChamfer,           // @emem C-style chamfer dimension
    CK_XStyleChamfer,           // @emem x degree style chamfer dimension
    CK_ArcLengthLinear,         // @emem Linear arc length dimension
    CK_ArcLengthCircular,       // @emem Circular arc length dimension
    CK_ArcLengthCircularRad,    // @emem Circular Arc Length Dimension with Rad
    CK_ArcLengthCircularArrow,  // @emem Circular Arc Length dimension with arrow
    CK_ArcLengthCircularANSI,   // @emem Circular Arc Length dimension, new added style
    CK_RadialBentCircular,      // @emem Bent Radial circular dimension
    CK_ArcLengthRadial,         // @emem Radial style arc length dimension
    CK_NumCKSDimStyle           // @emem use for range test on this enum
    };

// @enum This describes the design intent of the dimension and describes a prefix
// that appears between the user-specified prefix and the text of the dimension.
// These values are a subset of <t CKSSymbolType>
// @devnote The values in CKSDimensionModifier and CKSSymbolType should be
// kept in sync for ease of handling and debugging.  If we use up all of
// the Unused values, it will force a file format change.
enum CKSDimensionModifier
    {
    CK_NoModifier,        // @emem No modifier is present
    CK_DiameterMod,       // @emem The diameter of a circle
    CK_SphericalDiaMod,   // @emem The diameter of a sphere
    CK_RadiusMod,         // @emem The radius of a circle
    CK_SphericalRadMod,   // @emem The radius of a sphere
    CK_ControlledRadMod,  // @emem Radius of an arc with no reversals
    CK_SquareMod,         // @emem The size of a square
    CK_ArcLengthMod,      // @emem The length of an arc
    CK_PlateThicknessMod, // @emem The thickness of a plate (JIS)
    CK_TrueDimMod,        // @emem Displays the true value, not projected
    CK_UnequallyDisposedMod,   // @emem value held for future use
    CK_UnusedModifier3,   // @emem value held for future use
    CK_UnusedModifier4,   // @emem value held for future use
    CK_UnusedModifier5,   // @emem value held for future use
    CK_UnusedModifier6,   // @emem value held for future use
    CK_UnusedModifier7,   // @emem value held for future use
    CK_UnusedModifier8,   // @emem value held for future use
    CK_NumCKSDimensionModifier   // @emem use for range test on this enum
    };

// @enum The symbol types available in a <c ck_string_entry>
// these values are a superset of <t CKSDimensionModifier>.
// @devnote The values in CKSDimensionModifier and CKSSymbolType should be
// kept in sync for ease of handling and debugging.
// @devnote When symbols are added or removed form here there are three other
// places that will need updating also.  The are
// <mf ck_string_entry::StringToSymbol>, <mf ck_string_entry::SymbolToString>,
// and <mf CKTextEditor::OnSymbolMenu>.
enum CKSSymbolType
    {
    CK_NoSymbol           = CK_NoModifier,        // @emem No Symbol. This should always be first in the enum
    CK_DiameterSymb       = CK_DiameterMod,       // @emem The diameter of a circle
    CK_SphericalDiaSymb   = CK_SphericalDiaMod,   // @emem The diameter of a sphere
    CK_RadiusSymb         = CK_RadiusMod,         // @emem The radius of a circle
    CK_SphericalRadSymb   = CK_SphericalRadMod,   // @emem The radius of a sphere
    CK_ControlledRadSymb  = CK_ControlledRadMod,  // @emem Radius of an arc with no reversals
    CK_SquareSymb         = CK_SquareMod,         // @emem The size of a square
    CK_ArcLengthSymb      = CK_ArcLengthMod,      // @emem The length of an arc
    CK_PlateThicknessSymb = CK_PlateThicknessMod, // @emem The thickness of a plate (JIS)
    CK_TrueDimSymb        = CK_TrueDimMod,        // @emem Displays the true value, not projected
    CK_UnequallyDisposedSymb  = CK_UnequallyDisposedMod,   // @emem value held for future use
    CK_UnusedSymb3        = CK_UnusedModifier3,   // @emem value held for future use
    CK_UnusedSymb4        = CK_UnusedModifier4,   // @emem value held for future use
    CK_UnusedSymb5        = CK_UnusedModifier5,   // @emem value held for future use
    CK_UnusedSymb6        = CK_UnusedModifier6,   // @emem value held for future use
    CK_UnusedSymb7        = CK_UnusedModifier7,   // @emem value held for future use
    CK_UnusedSymb8        = CK_UnusedModifier8,   // @emem value held for future use
    CK_ChamferSymb,        // @emem (find good phrasing).
    CK_ByOrCountSymb,      // @emem number of instances
    CK_CounterboreSymb,    // @emem diameter of a counterbore
    CK_CountersinkSymb,    // @emem diameter of a countersink
    CK_DepthSymb,          // @emem depth of holes, counterbores
    CK_FlatTaperSymb,      // @emem amount of change per unit of length.
                           // Also called Slope.
    CK_ConicalTaperSymb,   // @emem amount of change in diameter over a unit
                           // length of the axis.
    CK_MMC_Symb,           // @emem GD&T Maximum Material Condition.
    CK_RFS_Symb,           // @emem GD&T Regardless of Feature Size.
    CK_LMC_Symb,           // @emem GD&T Least Material Condition.
    CK_ProjectedSymb,      // @emem tol zone projects beyond the part surface
    CK_StatisticalSymb,    // @emem tol value derived from statistical analysis.
    CK_FreeStateSymb,      // @emem dimension or tolerance is applicable in
                           // the free state.
    CK_TangentPlaneSymb,   // @emem tol zone is applicable to a tangent plane
                           // rather than the feature surface.
    CK_EnvelopeSymb,       // @emem Denotes that the limits of size of a
                           // feature prescribe the extent within variations of
                           // geometric form, as well as size, are allowed.
                           // This implied in ANSI/ASME drawings, but may be
                           // explicitly marked in some ISO drawings.
                           // (Also called Taylor Principle)
    CK_ReciprocitySymb,    // @emem GD&T Symbol for Principle of Reciprocity,
                           // a proposed extension to MMC, not yet in ISO.
    CK_TruePositionSymb,   // @emem position of a feature.  (Also called Position)
    CK_ConcentricitySymb,  // @emem control of the axis of a feature relative
                           // to a datum axis.
    CK_SymmetrySymb,       // @emem control of of the symmetry of a
                           // noncylindrical size feature by its median line.
    CK_CylindricitySymb,   // @emem circularity and paralleism control on the
                           // elements of a surface.
    CK_StraightnessSymb,   // @emem straightness of surface elements, or of
                           // an axis or center plane.
    CK_FlatnessSymb,       // @emem form variations of a flat surface.
    CK_ParallelismSymb,    // @emem orientation of two parallel features.
    CK_CircularitySymb,    // @emem control on the surface of a circular
                           // feature at individual cross sections.
    CK_PerpendicularSymb,  // @emem GD&T constraint of perpendicularity,
                           //   also called Squareness or Normality.
    CK_AngularitySymb,     // @emem GD&T constraint of angularity in
                           // combination with an angular dimension.
    CK_SurfaceProfileSymb, // @emem a three-dimensional surface control
                           // along the length and width of a feature.
    CK_LineProfileSymb,    // @emem two-dimensional surface control along
                           // the length of a feature.
    CK_CircularRunoutSymb, // @emem circular runout surface control.
    CK_TotalRunoutSymb,    // @emem a total runout surface control.
    CK_BetweenSymb,        // @emem GD&T control extents between two labeled
                           // points on the feature.
    CK_DegreeSymb,         // @emem Degree Symbol
    CK_PlusMinusSymb,      // @emem Plus-Minus Symbol
    CK_DashSymb,           // @emem A dash symbol
    CK_EndOfLineSymb,      // @emem  This forces a newline prior to the
                           // string subcomponent.
    CK_SuperscriptSymb,    // @emem This causes the corresponding text to be
                           // drawn as a superscipt.
    CK_SubscriptSymb,      // @emem This causes the corresponding text to be
                           // drawn as a subscipt.
    CK_OpenBracketSymb,    // @emem Draws an open bracket symbol '[' which is
                           // to be used in conjunction with a following
                           // close bracket symbol ']'
    CK_CloseBracketSymb,   // @emem Draws a close bracket symbol ']' which is
                           // to be used in conjunction with a preceeding
                           // open bracket symbol '['.
    CK_CursorSymb,         // for internal use only
    CK_START_FIELDNOTES,   // Just to indicate the start of Field note types
    CK_Field_System_Start,          // @emem Start System Field
    CK_Field_FileName,              // @emem Field : Filename
    CK_Field_PartName,              // @emem Field : Partname
    CK_Field_FilePath,              // @emem Field : File path
    CK_Field_SysTime,               // @emem Field : System Time
    CK_Field_LevName,               // @emem Field : Unit
    CK_Field_LevNum,                // @emem Field : Unit
    CK_Field_Unit,                  // @emem Field : Unit
    CK_Field_SplineTol,             // @emem Field : Spline Tol
    CK_Field_CoincTol,              // @emem Field : Coincidence Tolerance
    CK_Field_CADL_Expression,       // @emem Field : CADL Numeric Expression
    CK_Field_CADL_Var,              // @emem Field : CADL Variable
    CK_Field_System_End,            // @emem End System Field
    CK_Field_FileProp_Start,        // @emem Start File Properties Field
    CK_Field_File_PartNum,          // @emem Field : File Part Number
    CK_Field_File_Description,      // @emem Field : File Description
    CK_Field_File_CreatedBy,        // @emem Field : File Created By
    CK_Field_File_Keywords,         // @emem Field : File Keywords
    CK_Field_File_LastSavedBy,      // @emem Field : File Last Saved By
    CK_Field_File_Revision,         // @emem Field : File Revision
    CK_Field_File_Material,         // @emem Field : File Material
    CK_Field_File_Vendor,           // @emem Field : File Vendor
    CK_Field_File_CreatedAt,        // @emem Field : File Created At
    CK_Field_File_LastSavedAt,      // @emem Field : File Last Saved At
    CK_Field_File_Comment,          // @emem Field : File Comments
    CK_Field_File_User,             // @emem Field : File User Property
    CK_Field_FileProp_End,          // @emem End File Properties Field
    CK_Field_PartProp_Start,        // @emem Start Part Properties Field
    CK_Field_Part_PartNum,          // @emem Field : Part Part Number
    CK_Field_Part_Description,      // @emem Field : Part Description
    CK_Field_Part_CreatedBy,        // @emem Field : Part Created By
    CK_Field_Part_Keywords,         // @emem Field : Part Keywords
    CK_Field_Part_LastSavedBy,      // @emem Field : Part Last Saved By
    CK_Field_Part_Revision,         // @emem Field : Part Revision
    CK_Field_Part_Material,         // @emem Field : Part Material
    CK_Field_Part_Vendor,           // @emem Field : Part Vendor
    CK_Field_Part_CreatedAt,        // @emem Field : Part Created At
    CK_Field_Part_LastSavedAt,      // @emem Field : Part Last Saved At
    CK_Field_Part_Comment,          // @emem Field : Part Comments
    CK_Field_Part_User,             // @emem Field : Part User Property
    CK_Field_PartProp_End,          // @emem End Part Properties Field
    CK_Field_Layout_Start,          // @emem Start Layout Field
    CK_Field_Layout_Name,           // @emem Field : Layout Name
    CK_Field_Layout_Description,    // @emem Field : Layout Description
    CK_Field_Layout_Scale,          // @emem Field : Layout Scale
    CK_Field_Layout_End,            // @emem End Layout Field
    CK_END_FIELDNOTES,      // Just to indicate the end of the fieldnotes symbols
    CK_PartingLineSymb,     // @emem Parting Line symbol
    CK_CenterLineSymb,      // @emem Center Line Symbol
    CK_Field_FileNameOnly,          // @emem Field : File Name without extension
    CK_Field_EntityData_Start,      //indicate the start of the entity data field
    CK_Field_EntityLength,            // @emem Field : Entity Length
    CK_Field_DimText,                // @emem Field : Dimension Text
    CK_Field_Entity_PartNum,          // @emem Field : Entity Part Number
    CK_Field_Entity_Description,      // @emem Field : Entity Description
    CK_Field_Entity_CreatedBy,        // @emem Field : Entity Created By
    CK_Field_Entity_Keywords,         // @emem Field : Entity Keywords
    CK_Field_Entity_LastSavedBy,      // @emem Field : Entity Last Saved By
    CK_Field_Entity_Revision,         // @emem Field : Entity Revision
    CK_Field_Entity_Material,         // @emem Field : Entity Material
    CK_Field_Entity_Vendor,           // @emem Field : Entity Vendor
    CK_Field_Entity_CreatedAt,        // @emem Field : Entity Created At
    CK_Field_Entity_LastSavedAt,      // @emem Field : Entity Last Saved At
    CK_Field_Entity_Comment,          // @emem Field : Entity Comments
    CK_Field_Entity_User,             // @emem Field : Entity User Property
    CK_Field_Entity_FilePartNum,          // @emem Field : Entity File Part Number
    CK_Field_Entity_FileDescription,      // @emem Field : Entity File Description
    CK_Field_Entity_FileCreatedBy,        // @emem Field : Entity File Created By
    CK_Field_Entity_FileKeywords,         // @emem Field : Entity File Keywords
    CK_Field_Entity_FileLastSavedBy,      // @emem Field : Entity File Last Saved By
    CK_Field_Entity_FileRevision,         // @emem Field : Entity File Revision
    CK_Field_Entity_FileMaterial,         // @emem Field : Entity File Material
    CK_Field_Entity_FileVendor,           // @emem Field : Entity File Vendor
    CK_Field_Entity_FileCreatedAt,        // @emem Field : Entity File Created At
    CK_Field_Entity_FileLastSavedAt,      // @emem Field : Entity File Last Saved At
    CK_Field_Entity_FileComment,          // @emem Field : Entity File Comments
    CK_Field_Entity_FileUser,             // @emem Field : Entity File User Property
    CK_Field_Entity_Name,                 // @emem Field : Entity Name
    CK_Field_Layout_Paper_Format,         // @emem Field : Layout Paper Format
    CK_Field_FutureUse3,                  // @emem Field : reserved for future use
    CK_Field_FutureUse4,                  // @emem Field : reserved for future use
    CK_Field_FutureUse5,                  // @emem Field : reserved for future use
    CK_Field_FutureUse6,                  // @emem Field : reserved for future use
    CK_Field_FutureUse7,                  // @emem Field : reserved for future use
    CK_Field_FutureUse8,                  // @emem Field : reserved for future use
    CK_Field_FutureUse9,                  // @emem Field : reserved for future use
    CK_Field_FutureUse10,                  // @emem Field : reserved for future use
    CK_Field_FutureUse11,                  // @emem Field : reserved for future use
    CK_Field_FutureUse12,                  // @emem Field : reserved for future use
    CK_Field_FutureUse13,                  // @emem Field : reserved for future use
    CK_Field_FutureUse14,                  // @emem Field : reserved for future use
    CK_Field_FutureUse15,                  // @emem Field : reserved for future use
    CK_Field_FutureUse16,                  // @emem Field : reserved for future use
    CK_Field_FutureUse17,                  // @emem Field : reserved for future use
    CK_Field_FutureUse18,                  // @emem Field : reserved for future use
    CK_Field_FutureUse19,                  // @emem Field : reserved for future use
    CK_Field_FutureUse20,                  // @emem Field : reserved for future use
    CK_Field_FutureUse21,                  // @emem Field : reserved for future use
    CK_Field_FutureUse22,                  // @emem Field : reserved for future use
    CK_Field_FutureUse23,                  // @emem Field : reserved for future use
    CK_Field_FutureUse24,                  // @emem Field : reserved for future use
    CK_Field_FutureUse25,                  // @emem Field : reserved for future use
    CK_Field_FutureUse26,                  // @emem Field : reserved for future use
    CK_Field_FutureUse27,                  // @emem Field : reserved for future use
    CK_Field_FutureUse28,                  // @emem Field : reserved for future use
    CK_Field_FutureUse29,                  // @emem Field : reserved for future use
    CK_Field_FutureUse30,                  // @emem Field : reserved for future use
    CK_Field_FutureUse31,                  // @emem Field : reserved for future use
    CK_Field_FutureUse32,                  // @emem Field : reserved for future use
    CK_Field_EntityData_End,          //Just to indicate the end of the entity data fields
    CK_DynamicProfileSymb,          // @emem Dynamic profile symbol
    CK_ContinuousFeatureSymb,       // @emem Continuous feature symbol
    CK_NumCKSSymbolType,    // @emem use for range test on this enum
    CK_UninitalizedSymb,    // for internal use only
    CK_IndeterminantSymb,   // ALWAYS LAST in enum
    };

// @enum The type of balloon being displayed.
enum CKSBalloonType
    {
    CK_CircleBalloon,      // @emem A circular balloon.
    CK_BoxBalloon,         // @emem A square balloon.
    CK_BoxCircleBalloon,   // @emem A square with a circle inscribing it.
    CK_SplitCircleBalloon, // @emem Circle with two lines of text.
    CK_HexagonBalloon,     // @emem A regular hexagon.
    CK_TriangleBalloon,    // @emem An isosceles triangle.
    CK_RectangleBalloon,   // @emem A rectangle.
    CK_OvalBalloon,        // @emem An oval.
    CK_BoxPointBalloon,    // @emem A box with a point on the right
    CK_TextOnlyBalloon,    // @emem Just the text, no balloon.
    // @emem use for range test on this enum
    CK_NumCKSBalloonType
    };

// @enum Leader Type.
// These leader types may not be appropriate for all kinds of details.
enum CKSLeaderType
    {
    CK_NoLeader,                // @emem no leader is displayed
    CK_ElbowLeader,             // @emem standard label leader with witness
    CK_StraightLeader,          // @emem standard label leader without the witness
    CK_StackLeader,             // @emem attached to another entity (no actual leader)
                                // see <t CKSStackingAlign> for the method of the stacking
    CK_StringLeader,            // @emem multiple leaders off of common stem
    CK_HorzVertLeader,          // @emem horizontal/vertical leader
    CK_LinearLeader,            // @emem "gap" leader that looks like a linear dimension
    CK_CircularLeader,          // @emem leader that looks like a circular dimension
    CK_HorzVertSegmentLeader,   // @emem leader with horizontal and vertical segments
    // @emem use for range test on this enum
    CK_NumCKSLeaderType
    };

// @enum Which side of the stacking of entity is used. (used by ballons, frames)
enum CKSStackingAlign
    {
    CK_NoStacking,       // @emem Not stacked
    CK_TopStacking,      // @emem Stacked above the other entity.
    CK_RightStacking,    // @emem Stacked to the right of the other entity.
    CK_BottomStacking,   // @emem Stacked below the other entity.
    CK_LeftStacking,     // @emem Stacked to the left of the other entity.
    // @emem use for range test on this enum
    CK_NumCKSStackingAlign
    };

// @class CKS | Namespace for SDK enums
namespace CKS
    {
    // @cmember,menum Paper sizes for layout mode
    enum PaperSize
        {
        PaperKeyIn,     // @@emem User Defined size paper
        PaperA,         // @@emem A size  (  8.5 x   11 in)
        PaperB,         // @@emem B size  ( 11   x   17 in)
        PaperC,         // @@emem C size  ( 17   x   22 in)
        PaperD,         // @@emem D size  ( 22   x   34 in)
        PaperE,         // @@emem E size  ( 34   x   44 in)
        PaperA4,        // @@emem A4 size (210   x  297 mm)
        PaperA3,        // @@emem A3 size (297   x  420 mm)
        PaperA2,        // @@emem A2 size (420   x  594 mm)
        PaperA1,        // @@emem A1 size (594   x  841 mm)
        PaperA0,        // @@emem A0 size (841   x 1189 mm)
        NumPaperSize    // @@emem Range checking
        };

    // @cmember,menum The direction of arrowheads on dimensions
    enum ArrowDirection
        {
        ArrowsIn,   // @@emem Arrows inside the witnesses/circle
        ArrowsOut,  // @@emem Arrows outside the witnesses/circle
        ArrowsAuto, // @@emem Inside vs. Outside determined automatically
        ArrowsNone, // @@emem No arrows displayed.
        NumArrowDirection,   // @@emem Range Checking
        };

    // @enum Leader Style.
    // The display style for the leaders of most dimension entities.
    enum LeaderStyle
        {
        LSBroken,        // @emem Leader line broken around the text
        LSBrokenFirst,   // @emem Leader line broken around the text, first only
        LSBrokenSecond,  // @emem Leader line broken around the text, second only
        LSNone,          // @emem No leader lines are displayed
        LSSolid,         // @emem Solid leader line below the text
        LSSolidFirst,    // @emem Solid leader line with first arrowhead only
        LSSolidSecond,   // @emem Solid leader line with second arrowhead only
        LSSolidNone,     // @emem Solid leader line with no arrowheads shown
        LSNumLeaderStyle, // @emem Range checking
        };

    // @enum Witness Style.
    // The display style for the witnesses of most dimension entities.
    enum WitnessStyle
        {
        WSBoth,     // @emem Both witnesses are displayed
        WSFirst,    // @emem Only the first witness is displayed
        WSSecond,   // @emem Only the second witness is displayed
        WSNone,     // @emem Neither of the witnesses are displayed
        WSNumWitnessStyle,  // @emem Range checking
        };

    // @member WeldSymbol | Namespace for Weld Symbol enums.
    // @class CKS::WeldSymbol | Namespace of Weld Symbol enums.
    namespace WeldSymbol
        {
    // @cmember,menum The possible types of weld symbols.
        enum Types
            {
            SquareGroove,                   // @emem Square groove
            ScarfGroove,                    // @emem Scarf groove
            VGroove,                        // @emem V groove
            BevelGroove,                    // @emem Bevel groove
            UGroove,                        // @emem U groove
            JGroove,                        // @emem J groove
            FlareVGroove,                   // @emem Flare groove
            FlareBevelGroove,               // @emem Flare bevel groove
            Fillet,                         // @emem Fillet
            Plug,                           // @emem Plug
            Stud,                           // @emem Stud
            Spot,                           // @emem Spot
            Seam,                           // @emem Seam
            Back,                           // @emem Back
            Surfacing,                      // @emem Surfacing
            EdgeFlange,                     // @emem Edge flange
            CornerFlange,                   // @emem Corner flange
            FoldedJoint,                    // @emem Folded joint
            BevelButt,                      // @emem Bevel butt
            VButt,                          // @emem V butt
            SteepFlankedSingleVButt,        // @emem Steep flanked single V butt
            SteepFlankedSingleBevelButt,    // @emem Steep flanked single bevel butt
            InclinedJoint,                  // @emem Inclined joint
            Edge,                           // @emem Edge
            SurfaceJoint                    // @emem Surface joint
            };

        // @cmember,menum Weld Symbol contour types
        enum Contour
            {
            None = 0,
            FlatFlush,
            Convex,
            Concave
            };

        // @cmember,menum The Weld Symbol notch style
        enum Notch
            {
            NoNotch = 0,
            StyleOne,
            StyleTwo
            };
        }

    // @member GDT | Namespace for GD&T enums.
    // @class CKS::GDT | Namespace of GD&T enums.
    namespace GDT
        {
        // @cmember,menum The frame type of a GD&T symbol.  This controls
        // how the frames of the GD&T are drawn with respect to each other.
        enum FrameType
            {
            StandardFrame,        // @@emem Standard frame.
            CompositeTopTwo,      // @@emem The top frame in a composite pair.
            CompositeBottomTwo,   // @@emem The bottom frame in a composite pair.
            CompositeTopThree,    // @@emem The top frame in a three-frame composite.
            CompositeMiddleThree, // @@emem The bottom frame in a three-frame composite.
            CompositeBottomThree, // @@emem The bottom frame in a three-frame composite.
            FrameTypeCount        // @@emem use for range test on this enum
            };

        // @enum Where is the datum attached, for datums attached to
        // GeoTol and dimension entities.
        enum Attachment
            {
            Attached,           // @emem Normal Attachment to a Location on a
                                // target entity
            Extension,          // @emem Attachment via an extension line from
                                // a target entity
            AboveText,          // @emem Above the center of the target entity
                                // (usually a CKGeoTol) uses the top center of
                                // the target entity to work from
            BelowText,          // @emem Below the center of the target entity
                                // (usually a CKGeoTol) uses the top center of
                                // the target entity to work from
            AboveFirstWitness,  // @emem Above the arrows of the first Witness,
                                // denoting an edge plane
            OnFirstWitness,     // @emem On the arrows of the first Witness,
                                // denoting a center plane
            AboveSecondWitness, // @emem Above the arrows of the second
                                // Witness, denoting an edge plane
            OnSecondWitness,    // @emem On the arrows of the second Witness,
                                // denoting a center plane
            AboveSymbolFrame,   // @emem Above the symbol frame portion
                                // of the CKGeoTol entity.
            BelowSymbolFrame,   // @emem Below the symbol frame portion
                                // of the CKGeoTol entity.
            UnAttached          // @emem General placed datum not always attached
                                // to an entity.
            };

        // @cmember,menum Which standard was this symbol created in?
        // This is separate from the other standard enum because it
        // differentiates between ANSI Y14.5M-1982 and ASME Y14.5M-1994.
        // This only affects the appearance of GD&T symbols (including
        // datums), and so is part of the CKS::GDT namespace.
        enum Standard
            {
            Other,  // @@emem No defined standard
            ANSI82, // @@emem ANSI Y14.5M-1982
            ASME94, // @@emem ASME Y14.5M-1994
            ISO,    // @@emem ISO
            DIN,    // @@emem DIN
            JIS,    // @@emem JIS
            KS      // @@emem KS
            };

        // @cmember What type of leader is used for a datum target
        enum DTLeader
            {
            NoLeader,
            Filled,
            Unfilled,
            SolidLine,
            DashedLine
            };

        // @cmember What type of target point is used
        enum TargetPoint
            {
            NoPoint,
            CrossPoint,
            XPoint
            };
        }

    // @member Surface | Namespace for SurfaceTexture enums.
    // @class CKS::Surface | Namespace of SurfaceTexture enums.
    namespace Surface
        {
        // @cmember,menum Which leader style is used
        enum Leader
            {
            Normal,    // @emem Regular leaders, multiple arrows
            Aligned,   // @emem Attached to and aligned with an entity
            Unaligned  // @emem No leaders, and not on an entity
            };

        // @cmember,menum Which style is used for the basic symbol
        enum Type
            {
            Basic,               // @emem Basic Surface Symbol
            BasicPartExtended,   // @emem Basic Part Extended Surface Symbol
            BasicExtended,       // @emem Basic Extended Surface Symbol
            Machine,             // @emem Machine Surface Symbol
            MachinePartExtended, // @emem Machine Part Extended Surface Symbol
            MachineExtended,     // @emem Machine Extended Surface Symbol
            MachineProhibit,     // @emem Machine Prohibited Surface Symbol
            };

        // @cmember,menum Which lay symbol appears to the right of the base
        enum LayDirection
            {
            None,             // @emem None
            Parallel,         // @emem Parallel
            Perpendicular,    // @emem Perpendicular
            Angular,          // @emem Angular
            Multidirectional, // @emem Multidirectional
            Circular,         // @emem Circular
            Radial,           // @emem Radial
            Particulate       // @emem Particulate
            };
        }
    }

#define CK_EMPTY_MASK   0x000  // No mask set
#define CK_COLOR_MASK   0x001  // Entities whose color has changed
#define CK_PEN_MASK     0x002  // Entities whose pen # has changed
#define CK_STYLE_MASK   0x004  // Entities whose line style has changed
#define CK_WIDTH_MASK   0x008  // Entities whose line width has changed
#define CK_ATTR_MASK    (CK_COLOR_MASK | CK_PEN_MASK | CK_STYLE_MASK | CK_WIDTH_MASK)
#define CK_BLANK_MASK   0x010  // Entities who have been blanked
#define CK_TRIM_MASK    0x020  // Entities who have been trimmed
#define CK_ALL_MOD_MASK (CK_ATTR_MASK | CK_BLANK_MASK | CK_TRIM_MASK)

// @enum Leader side for labels and other entities that can have a leader
//  from either side
enum CKSLeaderSide
    {
    CK_LeaderRight,     // @emem Right hand leader
    CK_LeaderLeft,      // @emem Left hand leader
    CK_LeaderAuto,      // @emem Auto leader side selection
    CK_NumCKSLeaderSide // @emem use for range test on this enum
    };

#endif  // CK_ATTR_H_LOADED  MUST BE LAST LINE OF FILE
