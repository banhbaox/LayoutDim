// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_ENUM_INC
#define CK_ENUM_INC

// Care and handling of ck_enum.h
//
//   To reduce dependancies, this header should not include any other headers.
//   This header shares values between the Core the SDK.
//
// In general, enums within this header should use the nomenclature CKSEnumTypeName
// We've been keeping the name of enum values in allcaps for legacy values to
// ease porting issues for our Solution Partners.  New enums should use the more
// "modern" mixed case look.

// @doc EXTERNAL SDK Internal

// @enum Event code constants.  CKNoError and CKError must be in the first
// and last positions, respectively.
enum Events {
    CKNoError = 0,      // @emem Operation Successful
    CKMenu1,            // @emem Menu Button 1 pressed
    CKMenu2,            // @emem Menu Button 2 pressed
    CKMenu3,            // @emem Menu Button 3 pressed
    CKMenu4,            // @emem Menu Button 4 pressed
    CKMenu5,            // @emem Menu Button 5 pressed
    CKMenu6,            // @emem Menu Button 6 pressed
    CKMenu7,            // @emem Menu Button 7 pressed
    CKMenu8,            // @emem Menu Button 8 pressed
    CKMenu9,            // @emem Menu Button 9 pressed
    CKMenu10,           // @emem Menu Button 10 pressed
    CKMenu11,           // @emem Menu Button 11 pressed
    CKAccept,           // @emem Accept Button pressed
    CKBackup,           // @emem Backup Button pressed
    CKEscape,           // @emem Escape Button pressed
    CKRoot,             // @emem The program is preparing to start a root function.
    CKExiting,          // @emem The program is attempting to shut down
    CKDocChange,        // @emem The active document has changed
    CKContextMenu,      // @emem Context menu event
    CKRButtonClick,     // @emem The right button was clicked with Quick Eye enabled.
    CKMouseMove,        // @emem The user moved the mouse over the active viewport
    CKMouseLeave,       // @emem The user moved the mouse out of the active viewport
    CKLButtonDown,      // @emem The user started a click in a viewport
    CKLButtonUp,        // @emem The user finished a click in a viewport
    CKClick,            // @emem The user clicked in a viewport.
    CKToggle,           // @emem The user pressed the selection or position toggle key.
    CKGenToggle,        // @emem The user pressed the generic toggle key.
    CKKeyDown,          // @emem The user pressed a key.
    CKKeyUp,            // @emem The user pressed a key.
    CKKeyPress,         // @emem The user pressed a key.
    CKMButtonDown,      // @emem The user started a click in a viewport
    CKMButtonUp,        // @emem The user finished a click in a viewport
    CKRButtonDown,      // @emem The user started a click in a viewport
    CKRButtonUp,        // @emem The user finished a click in a viewport
    CKLButtonDblClick,  // @emem The user double clicked in a viewport.
    CKMButtonDblClick,  // @emem The user double clicked in a viewport.
    CKRButtonDblClick,  // @emem The user double clicked in a viewport.
    CKFuture8,          // @emem For future expansion
    CKFuture9,          // @emem For future expansion
    CKFuture10,         // @emem For future expansion
    CKError,            // @emem A function-specific error occurred.
    };

// @enum Constants for SDK return values.  All success/failure returns in the
// SDK (other than pure true/false returns) shall use return values from
// this enum, or from the <t Events> enum.  The <e CKSErrors.CK_NOERROR> and
// <e Events.CKNoError> values shall be equivalent, and the
// <e CKSErrors.CK_ERROR> and <e Events.CKError> values shall be equivalent.
// All values in <t CKSErrors> shall be higher than <e CKSErrors.CK_ERROR> to
// prevent overlap with <t Events>.  These descriptions are generic
// descriptions of the type of error indicated by the constant.  The specific
// function documentation may give a more precise definition.
enum CKSErrors
    {
    CK_NOERROR = CKNoError, // @emem The function completed successfully.
    CK_ERROR = CKError, // @emem An unknown error occurred.
    CK_NO_PART,         // @emem The part's document no longer exists.
    CK_COP_ERR,         // @emem An error occurred in the copious system.
    CK_NO_DATA,         // @emem There is no valid data for the funciton.
    CK_NO_ENT,          // @emem The entity does not exist.
    CK_NO_TYPES,        // @emem No Copious of the given type code exists.
    CK_EXISTS,          // @emem The requested/provided object already exists.
    CK_NOT_EXISTS,      // @emem The requested/provided object does not exist.
    CK_BAD_ENT,         // @emem The entity pointer is not of the type needed.
    CK_BAD_COMP,        // @emem The composite does not exist.
    CK_BAD_MATRIX,      // @emem The matrix provided is not valid.
    CK_NOT_ALLOWED,     // @emem The operation requested is not allowed.
    CK_BADTYPE,         // @emem The type of the selected object is invalid.
    CK_BAD_INSTANCE,    // @emem The instance handle provided is not valid.
    CK_NOT_INSTANCE,    // @emem The instance handle provided is not valid.
    CK_NOT_LAYOUT,      // @emem The layout handle provided is not valid.
    CK_NOT_LEVEL,       // @emem The level handle provided is not valid.
    CK_MODEL_MODE,      // @emem The part is in Model mode.
    CK_LAYOUT_MODE,     // @emem The part is in Layout mode.
    CK_BAD_FLAG,        // @emem The flag sent to the function is not in range.
    CK_NO_LAYOUT,       // @emem There are no layouts in the current part.
    CK_LAYOUT_GEOM,     // @emem Specified entity is layout-specific.
    CK_NOT_DISP,        // @emem Entity referenced is not displayed.
    CK_BAD_MASK,        // @emem Mask supplied is invalid for this function.
    CK_NOT_TAGGED,      // @emem Entity is not tagged to an instance.
    CK_BAD_VPORT,       // @emem The viewport number is invalid.
    CK_BAD_OPT,         // @emem Invalid option passed to function.
    CK_ENT_NOFIT,
    CK_MODEL_ENT,       // @emem The entity is in model space.
    CK_LAYOUT_ENT,      // @emem The entity is in layout space.
    CK_BAD_FILENAME,    // @emem The filename is invalid.
    CK_BAD_PARTNAME,    // @emem The part name is invalid.
    CK_FILE_ERROR,      // @emem A error occurred processing a disk file.
    CK_PART_TRANSLATED, // @emem The part was opened from an older version.
    CK_PART_OPEN,       // @emem The part was already open.
    CK_WRONG_LAYOUT,    // @emem The layouts do not match.
    MT_NOINTRSC,        // @emem There is no intersection.
    MT_NO3DINTRSC,      // @emem There is no 3-D intersection.
    MT_3DFOUND,         // @emem A 3D entity was found.
    MT_BAD_SEGMENT,     // @emem The segment number was invalid.
    MT_BAD_PARAM,       // @emem The parameter value was invalid.
    CK_BAD_VALUE,       // @emem The argument value was out of range.
    MT_LEN_ERROR,       // @emem The length provided is out of range.
    MT_NO_SOLUTION,     // @emem An iterative algorithm didn't converge.
    CK_BAD_NAME,        // @emem Invalid name passed to function.
    CK_BAD_SCALE,       // @emem Invalid scale passed to function.
    CK_BAD_PAPER_SIZE,  // @emem Invalid paper size passed to function.
    MT_FORCED,          // @emem The segment/parameter was forced to within
                        //       the valid range for the entity.
    CK_BAD_WEIGHTS,     // @emem The number of weights does not equal control
                        //       points or a negative weight value was passed.
    CK_BAD_KNOTS,       // @emem The number of Knots is out of range or an
                        //       invalid value was provided.
    CK_BAD_CONIC,       // @emem Unknown type of Conic (out of range).
    CK_BAD_CTRLPTS,     // @emem Bad Weighted Control points.
    CK_BAD_CURVE,       // @emem The curve form is out of range.
    CK_BAD_FITPNTS,     // @emem Inalid fit points data.
    CK_BAD_DEGREE,      // @emem The degree of Curve is out of range.
    CK_BAD_NUMCOEFFS,   // @emem The number of Conic coeffs was invalid.
    CK_VAR_ERR,         // @emem The variable could not be made
    CK_BAD_DIMS,        // @emem The array dimension information is not valid
    CK_NO_ACTV_INST,    // @emem There is no active instance
    CK_READ_ONLY,       // @emem The part is marked as read-only.
    CK_UNREADABLE_ENTS, // @emem Unreadable entities found while loading the part.
    MT_NO_2ND_INTRSC,   // @emem No second intersecting entity found
    CK_NO_2ND_ENT,      // @emem No second entity was found
    CK_SOL_STATE_NOT_STARTED, // @emem CKPart::StartState was not called prior to calling this function
    CK_SOL_STATE_STARTED,     // @emem CKPart::StartState should not be called prior to calling this function
    CK_SOLID_MANIFOLD,              // @emem Solid is already Manifold.
    CK_START_POS_REQ_FOR_DIR_CRV_1, // @emem Start position needs to be specified since director curve is not closed.
    CK_START_POS_REQ_FOR_DIR_CRV_2, // @emem Start position needs to be specified since director curve is not closed.
    CK_START_POS_REQ_FOR_GEN_CRV_1, // @emem Start position needs to be specified since generator curve is not closed.
    CK_START_POS_REQ_FOR_GEN_CRV_2, // @emem Start position needs to be specified since generator curve is not closed.
    CK_BAD_ROOT,        // @emem Missing root folder for DDE/SelSets
    CK_ABORT,           // @emem The operation is aborted.
    };

// @enum The type of intersection to find.
enum MTIntersection
    {
    MT_3DINTRSC,        // @emem For 3-D intersection computations
    MT_2DINTRSC,        // @emem For 2-D intersection computations
    };

// @enum Which depth to use for a 2D intersection.
enum MTDepth
    {
    MT_ENT1,            // @emem Find intersection at depth of 1st entity
    MT_ENT2,            // @emem Find intersection at depth of 2nd entity
    MT_VALUE,           // @emem Find intersection at given depth
    };

// @enum Whether the length should be computed in 2D or 3D
enum MTLength
    {
    MT_2DLENGTH,        // @emem Compute the length in 2D
    MT_3DLENGTH,        // @emem Compute the length in 3D
    };

// @enum Selection Options
enum CKSSelect
    {
    CK_SEL_SMART = 0,   // @emem Smart selection
    CK_SEL_SINGLE,      // @emem Single selection
    CK_SEL_CHAIN,       // @emem Chain selection
    CK_SEL_WINDOW,      // @emem Window selection
    CK_SEL_POLYGON,     // @emem Polygon selection
    CK_SEL_GROUP,       // @emem Group selection
    CK_SEL_PLANE,       // @emem Plane selection
    CK_SEL_ALLDSP,      // @emem All displayed selection
    CK_SEL_LEVEL        // @emem Level selection
    };

// @enum Window/Polygon Selection Options
enum CKSSelWinPoly
    {
    CK_ALL_IN = 1,      // @emem All in
    CK_PART_IN,         // @emem Part in
    CK_ALL_OUT,         // @emem All out
    CK_PART_OUT,        // @emem Part out
    CK_POLY_LINE,       // @emem Crossed by the line
    CK_BOX_MOVE         // @emem Box Move
    };

// @enum Entity Selection Options
enum CKSSelEntity
    {
    CK_NEXT_ENT = -1,   // @emem Next entity in the selection list
    CK_CUR_ENT,         // @emem Currently selected entity
    CK_SEL_LIST,        // @emem Entire selection list
    CK_ENT_LIST,        // @emem All entities in the list
    CK_ENT_DB,          // @emem All entities in database
    CK_DSP_ALL,         // @emem All displayed entities
    CK_DSP_BYTYPE,      // @emem Displayed entities specifying by type
    CK_DSP_EXTYPE       // @emem Displayed entities specifying by excluded type
    };

// @enum Position Options
enum CKSPosition
    {
    CK_POS_CURSOR = 1,  // @emem Cursor position
    CK_POS_POINT,       // @emem Point position
    CK_POS_END,         // @emem End position
    CK_POS_CENTER,      // @emem Center position
    CK_POS_INTERSECT,   // @emem Intersect position
    CK_POS_ALONG,       // @emem Along position
    CK_POS_TWO_POS,     // @emem Polar position
    CK_POS_OFFSET,      // @emem Delta position
    CK_POS_KEYIN        // @emem KeyIn position
    };

// @enum for the mode parameter SDK layout functions
enum CKSGetMode
    {
    CK_GET_CUR,             // @emem only retrieve the active element
    CK_GET_ALL,             // @emem retrieve list of all elements
    CK_GET_DISP_INST,       // @emem retrieve only the displayed instances
    CK_GET_NOT_DISP_INST,   // @emem retrieve only the non-displayed instances
    };

// @enum Chamfer Dimension type values.
enum CKSChamferType
    {
    CK_CHAMFER_C,           // @emem Chamfer dimension preceeded with 'C'
    CK_CHAMFER_X,           // @emem Chamfer dimension followed by " x 45°"
    };

// @enum Conic type values.
enum CKSConicType
    {
    CK_CON_QUAD,            // @emem quadratic coeffs for the conic.
    CK_CON_PARA,            // @emem parametric coeffs for the conic.
    };

// @enum Spline type values.
enum CKSSplineType
    {
    CK_SPL_NODE,            // @emem Node spline data
    CK_SPL_COEF,            // @emem Coefficent spline data
    };

// @enum Color numbers for using HC_Set_Color_By_Index
enum Color
    {
    BackgroundColor       = 64, // @emem Viewport background
    CursorColor,                // @emem Crosshair cursors (when enabled)
    HighlightColor,             // @emem Highlight of selected entities
    RubberbandColor,            // @emem Drag and rubberband boxes and lines
    MarkerColor,                // @emem Temporary markers
    SelectionColor,             // @emem An entity pending selection
    LayoutBorderColor,          // @emem Border of the paper
    InstanceColor,              // @emem Border of instances
    HReferenceColor,            // @emem Hidden part reference bounding boxes
    SReferenceColor,            // @emem Suppressed part reference bounding boxes
    BackgroundBottomColor,      // @emem Viewport background bottom
    BackgroundLayoutColor,      // @emem Layout background
    BackgroundBottomLayoutColor,// @emem Layout background bottom
    ShadowColor,                // @emem Shadow
    ErrorColor,                 // @emem Error
    CPlaneColor,                // @emem CPlane
    CuttingPlaneColor,          // @emem Cutting Planes
    CutEdgeColor,               // @emem Cut edges
    CutFaceColor,               // @emem Cut faces
    DispositionColor,           // @emem Disposition Color
    MaxColor                    // @emem Used to size the array given to HOOPS.
    };

// @enum Direction type values.
enum Direction
    {
    DirDown = 0,                // @emem Top to Bottom
    DirRight,                   // @emem Left to Right
    DirRightDown,               // @emem Top Left to Right Bottom
    DirRightUp                  // @emem Left Bottom to Right Top
    };

#pragma deprecated(AInstanceColor)
#pragma deprecated(IInstanceColor)
#define AInstanceColor LayoutBorderColor
#define IInstanceColor InstanceColor

// @enum Cursor Style Options
enum CurStyle
    {
    // @end The value of CK_CUR_CROSS is used as a default parameter in
    // PartDoc.h and MainFrm.h, so it musn't be changed without being
    // changed there.
    CK_CUR_CROSS = 0, // @emem Crosshairs Cursor
    CK_CUR_ARROW,     // @emem Arrow Cursor
    CK_CUR_RLINE,     // @emem Rubberband Line
    CK_CUR_RBOXD,     // @emem Rubberband Box in display plane
    CK_CUR_RARCD,     // @emem Rubberband Arc in display plane
    CK_CUR_RCIRCLED,  // @emem Rubberband Circle in display plane
    CK_CUR_DLINE,     // @emem Drag line in display plane
    CK_CUR_DBOXD,     // @emem Drag box in display plane
    CK_CUR_DARCD,     // @emem Drag arc in display plane
    CK_CUR_DCIRCLED,  // @emem Drag circle in display plane
    CK_CUR_RBOXC,     // @emem Rubberband Box in construction plane
    CK_CUR_RARCC,     // @emem Rubberband Arc in construction plane
    CK_CUR_RCIRCLEC,  // @emem Rubberband Circle in construction plane
    CK_CUR_DBOXC,     // @emem Drag box in construction plane
    CK_CUR_DARCC,     // @emem Drag arc in construction plane
    CK_CUR_DCIRCLEC,  // @emem Drag circle in construction plane
    CK_CUR_UNUSED1,   // @emem formerly Rubberband Nurbspline through point
    CK_CUR_UNUSED2,   // @emem formerly Nurbspline through contrl
    CK_CUR_DBOXP,     // @emem Drag box in display plane, size in pixels
    };

// @enum Cursor Placement Options for Drag Boxes
enum CurPlace
    {
    // @end The value of CK_BOX_LT is used as a default parameter in
    // PartDoc.h and MainFrm.h, so it musn't be changed without being
    // changed there.
    CK_BOX_LT = 0, // @emem Cursor is at top left.
    CK_BOX_CT, // @emem Cursor is at top center
    CK_BOX_RT, // @emem Cursor is at top right
    CK_BOX_LC, // @emem Cursor is at left center
    CK_BOX_CC, // @emem Cursor is at center
    CK_BOX_RC, // @emem Cursor is at right center
    CK_BOX_LB, // @emem Cursor is at bottom left
    CK_BOX_CB, // @emem Cursor is at bottom center
    CK_BOX_RB, // @emem Cursor is at bottom right
    };

// @enum Entity types for entity masking functions.
// @end Do not change this enum without also changing
// CKMasking::InitializeStrings() in Masking.cpp, the
// 400-499 group of #defines for the string table, and
// the file CADL/EntityInfo.txt to keep the CADL type codes correct.  Do
// not change the order of values in this enum, new codes MUST be added
// at the end.
enum CKMaskTypes
    {
    CKMaskNone = 0,         // @emem No type specified
    CKMaskPoint,            // @emem Points
    CKMaskLine,             // @emem Lines
    CKMaskArc,              // @emem Arcs and Circles
    CKMaskPolyline,         // @emem Polylines
    CKMaskOldConic,         // @emem Conics
    CKMaskSpline,           // @emem Splines
    CKMaskNURBSpline,       // @emem NURB Splines
    CKMaskComposite,        // @emem Composite entities
    CKMaskNote,             // @emem Notes
    CKMaskLabel,            // @emem Labels
    CKMaskLinearDim,        // @emem Linear Dimensions
    CKMaskAngularDim,       // @emem Angular Dimensions
    CKMaskCircularDim,      // @emem Circular Dimensions
    CKMaskBaseLinearDim,    // @emem Base Linear Dimensions
    CKMaskChamferDim,       // @emem Chamfer Dimensions
    CKMaskGenericDim,       // @emem Generic Dimensions
    CKMaskCoordinateDim,    // @emem Coordinate Dimensions
    CKMaskBalloon,          // @emem Balloons
    CKMaskCenterLine,       // @emem Center Lines
    CKMaskDatum,            // @emem Datums
    CKMaskDatumTarget,      // @emem Datum Targets
    CKMaskDrawInst,         // @emem Drawing Instances
    CKMaskGeoTol,           // @emem Geo Tol Symbols
    CKMaskHatch,            // @emem Cross Hatching
    CKMaskLeaderWitness,    // @emem Leaders and Witnesses
    CKMaskPartRef,          // @emem Part References
    CKMaskPlane,            // @emem Planes
    CKMaskSurfaceTexture,   // @emem Surface Texture Symbols
    CKMaskTarget,           // @emem Targets
    CKMaskVector,           // @emem Vectors
    CKMaskWeldingSymbol,    // @emem Welding Symbols
    CKMaskSolid,            // @emem Solids
    CKMaskParmSolid,        // @emem Parametric Solids
    CKMaskFeature,          // @emem Features
    CKMaskFastener,         // @emem Fasteners
    CKMaskChain,            // @emem Chains
    CKMaskOleEntity,        // @emem OLE Entity
    CKMaskText,             // @emem Textual entities
    CKMaskNoteTable,        // @emem Note Tables
    CKMaskDimension,        // @emem Dimension Entities
    CKMaskShell,            // @emem Shells
    CKMaskSolEdge,          // @emem Solid Edges
    CKMaskSolFace,          // @emem Solid Faces
    CKMaskSolVertex,        // @emem Solid Vertex
    CKMaskSolFlowline,      // @emem Solid Flowline
    CKMaskParmSolEdge,      // @emem Parametric Solid Edges
    CKMaskParmSolFace,      // @emem Parametric Solid Faces
    CKMaskParmSolVertex,    // @emem Parametric Solid Vertex
    CKMaskParmPlane,        // @emem Parametric Plane
    CKMaskParmSketchGeom,   // @emem Parametric Sketch Geometry
    CKMaskCuttingPlaneLine, // @emem Cutting Plane Line
    CKMaskSheet,            // @emem Sheet Body
    CKMaskSprocket,         // @emem Sprockets
    CKMaskBearBush,         // @emem Bearings/Bushings
    CKMaskGear,             // @emem Gears
    CKMaskShaft,            // @emem Shafts
    CKMaskSpring,           // @emem Springs
    CKMaskStructShape,      // @emem Structural Shapes
    CKMaskLight,            // @emem Lights
    CKMaskEntityMate,       // @emem Entity to entity mate
    CKMaskAutoLabel,        // @emem Automatic Label for Feature objects.
    CKMaskLeaderWitnessArc, // @emem Leader and Witness Arcs
    CKMaskDetailCallout,    // @emem Detail Callout Instance
    CKMaskSectionView,      // @emem Section View Instance
    CKMaskArcLabel,         // @emem Arc Label
    CKMaskBendLine,         // @emem Bend Lines
    CKMaskTable,            // @emem Table
    CKMaskImage,            // @emem Image
    CKMaskHoleNote,         // @emem Hole Note
    CKMaskHoleTable,        // @emem Hole Table
    CKMaskHoleFeature,      // @emem Hole Feature
    CKMaskArcLengthDim,     // @emem Arc length Dimensions
    CKMaskGeneralDetail,    // @emem General Details
    CKMaskCutting,          // @emem Cutting Entity
    CKMaskEllipse,          // @emem Ellipse
    CKMaskHelix,            // @emem Helix
    CKMaskParabola,         // @emem Parabola
    CKMaskHyperbola,        // @emem Hyperbola
    CKMaskSimConstraint,    // @emem Simulation Constraint
    CKMaskLastType,         // Types below this to not show up in the UI as unique types
    CKMaskHole = CKMaskLastType,
    CKMaskSheetmetalBend,
    CKMaskBlend,
    CKMaskPocket,
    CKMaskBoss,
    CKMaskChamfer,
    CKMaskCylinder,
    CKMaskSphere,
    CKMaskTorus,
    };

// @enum Spline type values
enum SplineType
    {
    CK_SPL_P2NN = 0,      // @emem 2D pts natural-natural
    CK_SPL_P2VN,          // @emem 2D pts vector-natural
    CK_SPL_P2NV,          // @emem 2D pts natural-vector
    CK_SPL_P2VV,          // @emem 2D pts vector-vector
    CK_SPL_P2C,           // @emem 2D pts closed
    CK_SPL_C2,            // @emem 2D coef open
    CK_SPL_C2C,           // @emem 2D coef closed
    CK_SPL_P3NN,          // @emem 3D pts natural-natural
    CK_SPL_P3VN,          // @emem 3D pts vector-natural
    CK_SPL_P3NV,          // @emem 3D pts natural-vector
    CK_SPL_P3VV,          // @emem 3D pts vector-vector
    CK_SPL_P3C,           // @emem 3D pts closed
    CK_SPL_C3,            // @emem 3D coef open
    CK_SPL_C3C,           // @emem 3D coef closed
    };

// @enum Marker Symbol Options
enum MarkerSymbol
    {
    CK_MARKER_CROSS,     // @emem Cross Marker (+)
    CK_MARKER_X,         // @emem X Marker (X)
    CK_MARKER_STAR,      // @emem Star Marker (*)
    CK_MARKER_TRIANGLE,  // @emem Triangle Marker (/_\)
    CK_MARKER_POUND,     // @emem Pound Marker (#)
    CK_MARKER_CIRCLE,    // @emem Circle Marker (O)
    CK_MARKER_FILLEDCIR, // @emem Filled-in Circle Marker ((*))
    CK_MARKER_FILLEDBOX  // @emem Filled-in Box ([*])
    };

// @enum Valid values for an entity's line type
enum CKSLTypes
    {
    CK_SOLID = 1, // @emem Solid lines.
    CK_DASHED,    // @emem Dashed lines.
    CK_CENTER,    // @emem Center lines.
    CK_PHANTOM    // @emem Phantom lines.
    };

enum CKSViewport
    {
    CK_ALL_VP   = -2,   // All viewports
    CK_PRIME_VP = -1,   // Primary viewport
    };

// @enum Curve Form Values
enum Curveforms
    {
    UNSPECIF_SHAPE  = 0, // @emem default; unspecified form
    POLYLINE_SHAPE,      // @emem polyline form
    CIRCULAR_SHAPE,      // @emem circular form
    ELLIPTIC_SHAPE,      // @emem elliptical form
    PARABOLIC_SHAPE,     // @emem parabolic form
    HYPERBOLIC_SHAPE,    // @emem hyperbolic form
    INTERSECT_SHAPE,     // @emem intersecting form
    };

// @enum Knot type flags
enum Knottypes
    {
    UNSPECIF_KNOTS  = 0,  // @emem default type, this includes non-uniform case
    UNIFORM_KNOTS,        // @emem unclamped and uniform
    QUASI_UNIFORM,        // @emem clampled and uniform
    PIECE_BEZIE,          // @emem distinct knot values are equally spaced
    };

// @enum Conic type flags
enum ConType
    {
    ConPoint,      // @emem A point
    ConLine,       // @emem A line
    ConArc,        // @emem An arc
    ConEllipse,    // @emem An ellipse
    ConParabola,   // @emem A parabola
    ConHyperbola   // @emem A hyperbola
    };

// @enum Cutting entity type flags
enum CuttingType
    {
    CutPlane,       // @emem Cutting Plane
    CutSection,     // @emem Cutting Section
    CutSlice,       // @emem Slicing Plane
    CutAny          // @emem Any Cutting Entity
    };

// @enum Cut face color flag
enum CutFaceColor
    {
    CutOpaque = 0,  // @emem Opaque
    CutMatch,       // @emem Match cut entity
    };

// @enum Units values.
enum CKSUnits
    {
    CK_UnitUnknown = -1, // @emem unknown (not set)
    CK_UnitInches,       // @emem inches
    CK_UnitMillimeters,  // @emem millimeters
    CK_UnitFeet,         // @emem feet
    CK_UnitCentimeters,  // @emem centimeters
    CK_UnitYards,        // @emem yards
    CK_UnitMeters,       // @emem meters
    CK_UnitDegrees,      // @emem degrees
    CK_UnitRadians,      // @emem radians
    CK_UnitGradians,     // @emem gradians
    CK_UnitUserDef,      // @emem user-defined units (assumed linear units?)
    CK_UnitMicrons,      // @emem internal use only
    CK_UnitKilometers,   // @emem internal use only
    CK_UnitMils,         // @emem internal use only
    CK_UnitMicroinches,  // @emem internal use only
    CK_UnitMiles,        // @emem internal use only
    CK_NumCKSUnits       // @emem use for range test on this enum
    };

// @enum Mass Units values.
enum CKSMassUnits
    {
    CK_UnitCentigrams,  // @emem centigrams
    CK_UnitGrams,       // @emem grams
    CK_UnitKilograms,   // @emem kilograms
    CK_UnitMilligrams,  // @emem milligrams
    CK_UnitOunces,      // @emem ounces
    CK_UnitPounds,      // @emem pounds
    CK_NumCKSMassUnits  // @emem use for range test on this enum
    };

// @enum Density Units values.
enum CKSDensityUnits
    {
    CK_UnitGramsCentimeter, // @emem Grams per centimeter cube
    CK_UnitKilogramsMeter,  // @emem Kilograms per meter cube
    CK_UnitPoundsFeet,      // @emem Pounds per feet cube
    CK_UnitPoundsInch,      // @emem Pounds per inch cube
    CK_UnitPoundsYard,      // @emem Pounds per yard cube
    CK_OunceInch,           // @emem Ounces per inch cube
    CK_NumCKSDensityUnits   // @emem use for range test on this enum
    };

// this is also in CADLVars.h as CADLVars::Type with the exception that None
// is not duplicated here
// @enum CADL variable types accessable through the SDK
enum CKSCADLVarType
    {
    CK_CADLDouble = 0,      // @emem Double variable
    CK_CADLString,          // @emem String variable
    CK_CADLStringList,      // @emem String list variable
    CK_CADLInteger,         // @emem Integer variable
    CK_CADLDoubleArray,     // @emem Double array variable
    CK_CADLStringArray,     // @emem String array variable
    CK_CADLIntegerArray,    // @emem Integer variable
    CK_CADLDrawInstVar,     // @emem Handle to a drawing instance
    CK_CADLEntityVar,       // @emem Handle to an entity
    CK_CADLLocationVar,     // @emem Handle to a location
    CK_CADLLevelVar,        // @emem Handle to a level
    CK_CADLLayoutVar,       // @emem Handle to a layout
    CK_CADLDrawInstArray,   // @emem Array of handles to drawing instances
    CK_CADLEntityArray,     // @emem Array of handles to entities
    CK_CADLLocationArray,   // @emem Array of handles to locations
    CK_CADLLevelArray,      // @emem Array of handles to levels
    CK_CADLLayoutArray,     // @emem Array of handles to layouts
    CK_CADLHatchPattern,    // @emem Array of handles to levels
    CK_CADLHatchPatArray,   // @emem Array of handles to layouts
    CK_NumCKSCADLVarType    // @emem use for range test on this enum
    };

// @enum Quick Move type
enum QuickMoveMode
    {
    MoveDefault = -1,       // @emem default quick moves
    NoQuickMove = 0,        // @emem no quick moves
    MoveXOR,                // @emem xor quick move
    MoveOverlay,            // @emem overlay quick move
    MoveSpriting,           // @emem spriting quick move
    WireMove,               // @emem quick move for wireframe
    SolidMove,              // @emem quick move for solid
    };

// @enum Anti-Alias flags
enum AntiAliasFlag
    {
    AntiAliasLine   = 0x0001, // @emem anti-alias for lines/edges
    AntiAliasText   = 0x0002, // @emem anti-alias for text
    AntiAliasFull   = 0x0004, // @emem full anti-alias
    AntiAliasEnable = 0x8000, // @emem anti-alias enabled (internal flag)
    };

// @enum Modifier type flags
enum ModifierType
    {
    ModNone         = 0,
    ModPos          = 0x00000001,   // @emem Position modifier
    ModVecX         = 0x00000002,   // @emem X axis direction modifier
    ModVecY         = 0x00000004,   // @emem Y axis direction modifier
    ModVecZ         = 0x00000008,   // @emem Z axis direction modifier
    ModVecXYZ       = 0x0000000E,   // @emem X/Y/Z axis direction modifier
    ModRotX         = 0x00000010,   // @emem X axis rotation modifier
    ModRotY         = 0x00000020,   // @emem Y axis rotation modifier
    ModRotZ         = 0x00000040,   // @emem Z axis rotation modifier
    ModRotXYZ       = 0x00000070,   // @emem X/Y/Z axis rotation modifier
    ModDefault      = 0x0000007F,   // @emem Default modifier
    ModLineX        = 0x00000100,   // @emem X axis indicator
    ModLineY        = 0x00000200,   // @emem Y axis indicator
    ModLineZ        = 0x00000400,   // @emem Z axis indicator
    ModLineXYZ      = 0x00000700,   // @emem X/Y/Z axis indicator
    ModAlign        = 0x00010000,   // @emem Alignment
    ModAlignMove    = 0x00020000,   // @emem Alignment Move
    ModMirror       = 0x00040000,   // @emem Mirror
    ModRePos        = 0x00080000,   // @emem Re-Position
    };

// @enum Modifier context menu
enum ModifierContextOp
    {
    ModOpNone = 0,
    ModOpPos,           // @emem Position XYZ
    ModOpPosX,          // @emem Position X
    ModOpPosY,          // @emem Position Y
    ModOpPosZ,          // @emem Position Z
    ModOpOffset,        // @emem Offset XYZ
    ModOpOffsetX,       // @emem Offset X
    ModOpOffsetY,       // @emem Offset Y
    ModOpOffsetZ,       // @emem Offset Z
    ModOpAngX,          // @emem Angle X
    ModOpAngY,          // @emem Angle Y
    ModOpAngZ,          // @emem Angle Z
    ModOpDelta,         // @emem Delta XYZ
    ModOpDeltaX,        // @emem Delta X
    ModOpDeltaY,        // @emem Delta Y
    ModOpDeltaZ,        // @emem Delta Z
    ModOpDeltaAngX,     // @emem Delta Angle X
    ModOpDeltaAngY,     // @emem Delta Angle Y
    ModOpDeltaAngZ,     // @emem Delta Angle Z
    ModOpDeltaLocal,    // @emem Delta Local XYZ
    ModOpAlignWld,      // @emem Align to World
    ModOpAlignCP,       // @emem Aligh to CPlane
    ModOpAlignMoveWld,  // @emem Move to World
    ModOpAlignMoveCP,   // @emem Move to CPlane
    ModOpAlignVec,      // @emem Align to Vector
    ModOpAlignPln,      // @emem Align to Plane
    ModOpAlignMoveVec,  // @emem Align Move to Vector
    ModOpAlignMovePln,  // @emem Align Move to Plane
    ModOpMirrorXY,      // @emem Mirror XY
    ModOpMirrorYZ,      // @emem Mirror YZ
    ModOpMirrorXZ,      // @emem Mirror XZ
    ModOpTranslateInc,  // @emem Translate Increment
    ModOpRotateInc,     // @emem Rotate Increment
    ModOpArrowScaleUp,  // @emem Arrow Scale Up (Obsolete)
    ModOpArrowScaleDown,// @emem Arrow Scale Down (Obsolete)
    ModOpArrowSizeUp,   // @emem Arrow Size Up (Obsolete)
    ModOpArrowSizeDown, // @emem Arrow Size Down (Obsolete)
    ModOpArrowTransUp,  // @emem Arrow Transparency Up (Obsolete)
    ModOpArrowTransDown,// @emem Arrow Transparency Down (Obsolete)
    ModOpTooltip,       // @emem Tooltip Toggle
    ModOpRePos,         // @emem Re-Position
    ModOpTransparent,   // @emem Toggle Transparent (Obsolete)
    ModOpTransparency,  // @emem Transparency (Obsolete)
    ModOpAlignView,     // @emem Align to View
    ModOpAlignViewNum = ModOpAlignView + 9,
    ModOpAlignMoveView, // @emem Align Move to View
    ModOpAlignMoveViewNum = ModOpAlignMoveView + 9,
    ModOpOptions,       // @emem Options
    ModOpCustom,
    };

// @enum Modifier mirror flags
enum ModifierMirror
    {
    ModMirrorXY     = 0x0001,   // @emem Mirrored on XY
    ModMirrorYZ     = 0x0002,   // @emem Mirrored on YZ
    ModMirrorXZ     = 0x0004,   // @emem Mirrored on XZ
    };

// Do not use at-class to document this, that is already done in ck_attr.h
namespace CKS
    {
    // @menum CKS | SelParams | Parameters for various selection functions.
    enum SelParams
        {
        IgnoreSelectFlag    = 0x0001,   // @emem Entities currently marked as
                                        // selected can still be chosen.
        IgnoreActiveInst    = 0x0002,   // @emem Obsolete.
        SuppressRefEnts     = 0x0004,   // @emem When the user selects an entity
                                        // displayed through a part reference, the
                                        // part reference is selected instead.
        SelParentNonInst    = 0x0008,   // @emem When the user selects an entity
                                        // that has a parent entity, the parent is
                                        // selected instead, unless the entity is
                                        // an instance-specific entity.
        SelectParent        = 0x0010,   // @emem When the user selects a entity that
                                        // has a parent entity, the parent is
                                        // selected instead.
        SelectInst          = 0x0020,   // @emem When the user selects an instance
                                        // specific entity, the instance is selected
                                        // instead in layout mode.
        SelectInstTagged    = 0x0040,   // @emem When the user selects a tagged
                                        // entity, the instance is selected instead.
        SelectFeature       = 0x0080,   // @emem When the user selects a feature
                                        // entity that has a parent solid entity,
                                        // it is selected as well.
        AllowAccept         = 0x0100,   // @emem Displays the accept button in the
                                        // functions that support it.
        SelectCutting       = 0x0200,   // @emem Cutting Entities can be selectable.
        SortByIDValue       = 0x0400,   // @emem Portions of the selection that
                                        // select multiple entities in a single
                                        // operation, such as Window or All Dsp,
                                        // will sort that group of entities by
                                        // their ID value before adding them to
                                        // the selection list.  This does not include
                                        // chain select, which places the entities
                                        // in chain order, or any single select
                                        // method, which places them in the order
                                        // selected, unless the selected entity is
                                        // part of a group, and the user elects to
                                        // select the entire subgroup or group.
                                        // This is ignored when selecting entities
                                        // displayed through part references is
                                        // allowed.
                                        //
                                        // This will cause the entities to be
                                        // selected in the order that they were
                                        // created, as long as the entities were
                                        // created  in a single operation, or in
                                        // a series of operations without closing
                                        // the part or purging the undo history
                                        // during that sequence of operations.
                                        // Either of those two actions can cause
                                        // entity IDs that are no longer in use
                                        // to be reused for creation of new
                                        // entities, and thus cause the entity
                                        // ID sequence to not match the creation
                                        // order.
        SelectFace          = 0x0800,   // @emem When the user selects a solid face,
                                        // it is selected as well regardless
                                        // SelectParent flag.
        SingleChain         = 0x1000,   // @emem Select only one chain in chain selection.
        SelectAllFacesSolid = 0x2000,   // @emem When the user selects solid and its all faces,
                                        // only solid is counted for selection count.
        IgnoreChild         = 0x4000,   // @emem Ignore members of composite and
                                        // child base linear dimensions.
                                        // This has to be used with SelectParent.
        IgnoreParent        = 0x8000,   // @emem Ignore parent entity. This cannot
                                        // be used with SelectParent and SelectInst.
                                        // (Used by positioning internally)
        };

#pragma deprecated(IgnoreActiveInst)

    // @enum The types of functions available to the user in UPM.
    enum GPFuncMask
        {
        GPCursor     = 0x0001, // @emem Cursor is available.
        GPPoint      = 0x0002, // @emem Point is available.
        GPEndEnt     = 0x0004, // @emem EndEnt is available.
        GPCenter     = 0x0008, // @emem Center is available.
        GPIntersect  = 0x0010, // @emem Intersection is available.
        GPAlongCurve = 0x0020, // @emem Along curve is available.
        GPTwoPos     = 0x0040, // @emem Two Positions is available.
        GPOffset     = 0x0080, // @emem Offset is available.
        GPKeyIn      = 0x0100, // @emem KeyIn is available.
        GPF10        = 0x0200, // @emem User-defined 10th button.
        GPF11        = 0x0400, // @emem User-defined 11th button.
        GPAccept     = 0x0800, // @emem The accept button is available.
        GPBackEsc    = 0x1000, // @emem The backup/escape buttons are available.(Used by UPM)
        GPDefault    = 0x11FF, // @emem Default UPM Menu.
        GPDone       = 0x2000, // @emem There is a done button in the 11th menu
                               // position.  This takes precedence over GPSkip,
                               // but is only available if a custom menu isn't
                               // provided.
        GPSkip       = 0x4000, // @emem There is a skip button in the 11th menu
                               // position.  This is overridden by GPDone, or a
                               // custom menu.
        GPSysMask    = 0x8000, // @emem Include the active system mask
                               // in addition to the mask that GetPos
                               // sets internally.
        };

    // @enum The types of functions available to the user in USM.
    enum GSFuncMask
        {
        GSSingle  = 0x0001, // @emem Single is available.
        GSChain   = 0x0002, // @emem Chain is available.
        GSWindow  = 0x0004, // @emem Window is available.
        GSPolygon = 0x0008, // @emem Polygon is available.
        GSGroup   = 0x0010, // @emem Group is available.
        GSPlane   = 0x0020, // @emem Plane is available.
        GSAllDsp  = 0x0040, // @emem All Dsp is available.
        GSDefault = 0x047F, // @emem Default USM Menu.
        GSAddSub  = 0x0080, // @emem The add/subtract buttons are available.
                            // (Used by USM internally)
        GSClear   = 0x0100, // @emem The clear button is available.
                            // (Used by USM internally)
        GSLevel   = 0x0200, // @emem Level is available.
        GPSelSet  = 0x0400, // @emem Selection set.
        GSAccept  = 0x0800, // @emem The accept button is available.
        GSBackEsc = 0x1000  // @emem The backup/escape buttons are available.
                            // (Used by UPM internally)
        };

    // @enum The mask available for GetInput when used like a simple "GetMenu"
    enum GMFuncMask
        {
        GMMenu1      = 0x0001, // @emem Menu1 is available.
        GMMenu2      = 0x0002, // @emem Menu2 is available.
        GMMenu3      = 0x0004, // @emem Menu3 is available.
        GMMenu4      = 0x0008, // @emem Menu4 is available.
        GMMenu5      = 0x0010, // @emem Menu5 is available.
        GMMenu6      = 0x0020, // @emem Menu6 is available.
        GMMenu7      = 0x0040, // @emem Menu7 is available.
        GMMenu8      = 0x0080, // @emem Menu8 is available.
        GMMenu9      = 0x0100, // @emem Menu9 is available.
        GMMenu10     = 0x0200, // @emem Menu10 is available.
        GMMenu11     = 0x0400, // @emem Menu11 is available.
        GMAllMenus   = 0x07FF, // @emem All menu buttons are available.
        GMAccept     = 0x0800, // @emem Accept button is available.
        GMBackEsc    = 0x1000, // @emem The backup/escape buttons are available.
        GMDefault    = 0x17FF, // @emem Default Menu.
        GMGetVals   = 0x10000, // @emem Pressing menu button gets edit field
                               // values.  This must not share any values with
                               // enums from GPFuncMask or GSFuncMask.
        };

    // @enum The types of snap options available.
    enum PosSnap
        {
        PosNone      = 0x0000, // @emem No Snap is available.
        PosPoint     = 0x0001, // @emem Point Snap is available.
        PosEnd       = 0x0002, // @emem End Snap is available.
        PosCenter    = 0x0004, // @emem Center Snap is available.
        PosMid       = 0x0008, // @emem Midpoint Snap is available.
        PosQuad      = 0x0010, // @emem Quadrant Snap is available.
        PosTan       = 0x0020, // @emem Tangent Snap is available.
        PosX3D       = 0x0040, // @emem 3D Intersection Snap is available.
        PosX2D       = 0x0080, // @emem 2D Intersection Snap is available.
        PosCustom    = 0x0100, // @emem Custom Snap is available.
        PosCut       = 0x0200, // @emem Cutpoint Snap is available.
        PosEntity    = 0x4000, // @emem Entity Snap is available.
                               // (Used by Smart Cursor internally)
        PosNear      = 0x8000, // @emem Near Snap is available.
                               // (Used by Smart Cursor internally)
        };

    // @enum The types of snap modes available.
    enum PosMode
        {
        PosNoSnap = 0,      // @emem No Snap (cursor position only).
        PosBoth,            // @emem Snap both significant and cursor position.
        PosSnapOnly,        // @emem Snap significant position only.
        PosConfirm,         // @emem Confirm significant position by click.
        };

    enum AxisDirection
        {
        AxisPosX,           // @emem Positive X vector
        AxisNegX,           // @emem Negative X vector
        AxisPosY,           // @emem Positive Y vector
        AxisNegY,           // @emem Negative Y vector
        AxisPosZ,           // @emem Positive Z vector
        AxisNegZ            // @emem Negative Z vector
        };

    // @enum Rendering styles
    enum Rendering
        {
        RenderNone = 0x0,   // @emem No self defined rendering
        RenderWire,         // @emem Wire-frame display
        RenderHLR,          // @emem Hidden Line Removed display
        RenderHLD,          // @emem Hidden Line Dashed display
        RenderFlat,         // @emem Flat shaded display
        RenderSmooth,       // @emem Gouraud shaded display
        RenderSmoothWire,   // @emem Gouraud shaded with all wire-frame display (Obsolete)
        RenderSmoothNoWire, // @emem Gouraud shaded without wire-frame display (Obsolete)
        RenderPhong,        // @emem Phong shaded display
        RenderFlatStd,      // @emem Flat shaded with standard wire-frame display (Obsolete)
        RenderSmoothStd,    // @emem Gouraud shaded with standard wire-frame display (Obsolete)
        RenderRaytrace,     // @emem Raytraced render mode (Obsolete)
        NumRendering,       // @emem Used for range test on this item
        };

    // @enum Wireframe Rendering styles
    enum WireRendering
        {
        WireDefault = -1,   // @emem No self defined rendering
        WireStandard = 0,   // @emem Standard wireframe rendering
        WireAll,            // @emem All wireframe rendering
        WireNone,           // @emem No wireframe rendering
        WireDash,           // @emem Dashed hidden line wireframe rendering
        NumWireRendering,   // @emem Used for range test on this item
        };

    // @enum Thread Rendering styles
    enum ThreadRendering
        {
        ThreadRenderDefault = -1, // @emem No self defined rendering
        ThreadRenderNone = 0x0,   // @emem No thread display
        ThreadRenderSimple,       // @emem Simple thread display
        ThreadRenderSchematic,    // @emem Schematic thread display
        ThreadRenderDetail,       // @emem Detail thread display
        ThreadRenderDetailNL,     // @emem Detail thread without lines display
        NumThreadRendering,       // @emem Used for range test on this item
        };

    // @enum Centerline types.
    enum CenterlineType
        {
        CLHorizontal = 0x0, // @emem Horizontal
        CLVertical,         // @emem Vertical
        CLParallel,         // @emem Parallel
        CLRadial2CLines,    // @emem Radial 2 CenterLines
        CLRadial4LinesPt,   // @emem Radial 4 Lines with a point at center
        CLRadialLinePoint,  // @emem Radial 4 Lines with 2 lines crossed at center
        CLRadialNoPoint,    // @emem Radial 4 Lines with no center point
        CLRadialPointOnly,  // @emem Radial 4 Lines with only a center point
        CLAxial3D,          // @emem Unprojected axial centerline
        CLNumTypes
        };

    // @enum Options that determine the type of boolean operation
    enum BooleanType
        {
        Union=0,                // @emem Boolean unite operation
        Intersection,           // @emem Boolean intersect operation
        Subtraction             // @emem Boolean subtract operation
        };

    enum BooleanKeepOption
        {
        KeepNeither = 0,        // @emem Keep neither the tool nor the blank
        KeepToolsOnly,          // @emem Keep the tools
        KeepBlanksOnly,         // @emem Keep the blanks
        KeepToolsAndBlanks      // @emem Kepp both tools and blanks
        };

    // @enum Options that determine how the end of the extrusion is to be defined
    enum ExtrudeEndMethod
        {
        ExtrudeByLength=0,          // @emem Extrusion created to the given length
        ExtrudeByLengthAndPosition, // @emem Extrusion by base length and position
        ExtrudeToPosition,          // @emem Extrusion created to target position
        ExtrudeBetweenPositions,    // @emem Extrusion created between 2 positions
        ExtrudeToBody,              // @emem Extrusion is trimmed to given target body
        ExtrudeToFace,              // @emem Extrusion is trimmed to given target face
        ExtrudeDynamic              // @emem Extrusion created between 2 positions, animated
        };

    // @enum Options that determine how the end of the extrusion is to be defined
    enum RevolveEndMethod
        {
        RevolveByAngle=0,       // @emem Revolution created based on given angle
        RevolveToPosition,      // @emem Revolution created to target position
        RevolveBetweenPositions,// @emem Revolution created between positions
        RevolveDynamic          // @emem Revolution created between 2 positions, animated
        };

    // @enum Options that determine the direction of extrusion
    enum ExtrudeDirectionMethod
        {
        ExtrudeNormally=0,      // @emem Extrude normal to the plane of the curves
        ExtrudeAlongVector      // @emem Extrude along the given vector
        };

    // @enum Options that determine now the end of the sweep is to be defined
    enum SweepEndMethod
        {
        SweepToEndOfPath=0,     // @emem Sweeps profile to the end of the given path
        SweepBetweenPositions,  // @emem Sweep between two positions along the given path
        SweepToBody             // @emem Sweep is trimmed to given target body
        };

    // @enum Miter options for the sweep function
    enum MiterMethod
        {
        MiterNew=0,             // @emem Default miter option
        MiterCrimp              // @emem Crimp miter option
        };

    // @enum Options that determine draft direction for extrude, revolve
    // and sweep operations
    enum DraftDirection
        {
        DraftInward=0,          // @emem Draft Inward
        DraftOutward            // @emem Draft Outward
        };

    // @enum Options that specify how to fill in gaps created by offsetting
    // when the draft option is used in extrude, revolve and sweep operations
    enum ConvexEdges
        {
        Natural=0,              // @emem Natural gap type
        Round,                  // @emem Rounded gap type
        Extend                  // @emem Extended gap type
        };

    // @enum Specifies the number of sides of the polygons generated by the faceter
    enum PolygonSides 
        {
        ThreeSided = 0, 
        FourSidedPreferred, 
        FourSidedOnly 
        };

    // @enum Option for specifying Acis Version numbers
    enum AcisVersion
        {
        AcisCurrent = 0,
        AcisVersion105,
        AcisVersion106,
        AcisVersion200,
        AcisVersion201,
        AcisVersion300,
        AcisVersion400,
        AcisVersion500,
        AcisVersion600,
        AcisVersion700,
        AcisVersion800,
        AcisVersion1000,
        AcisVersion1100,
        AcisVersion1200,
        AcisVersion1300,
	    AcisVersion1400,
        AcisVersion1500,
        AcisVersion1600,
        AcisVersion1700,
        AcisVersion1800,
		AcisVersion1900,
        AcisVersion2000,
        AcisVersion2100,
        AcisVersion2200,
        AcisVersion2300,
        AcisVersion2400,
        AcisVersion2500,
        AcisVersion2600,
        AcisVersion2700,
        AcisVersion2800,
        AcisVersion2900,
        AcisVersion3000,
        AcisVersion3100,
        AcisVersion3200,
        AcisVersion3300,
        AcisVersion3400
        };

    // @enum Option for specifying the masking method for solidify
    enum SolidifyMaskingMethod
        {
        ByLevel = 0,
        ByColor,
        ByPen,
        ByGroup,
        BySubGroup
        };

    enum BlendCrossSection
        {
        Circular = 0,
        ThumbWeighted
        };

    enum VPLayout
        {
        VPLSingle = 0,
        VPLLeftRight,
        VPLTopBottom,
        VPL2Left1Right,
        VPL2Right1Left,
        VPL2Bottom1Top,
        VPL2Top1Bottom,
        VPLQuad,
        };

    enum Viewport
        {
        VPortAll             = -2,
        VPortActive          = -1,
        VPortSingle          =  0,
        VPortLRLeft          =  0,
        VPortLRRight         =  1,
        VPortTBTop           =  0,
        VPortTBBottom        =  1,
        VPort2L1RRight       =  0,
        VPort2L1RTopLeft     =  1,
        VPort2L1RBottomLeft  =  2,
        VPort1L2RLeft        =  0,
        VPort1L2RTopRight    =  1,
        VPort1L2RBottomRight =  2,
        VPort2T1BBottom      =  0,
        VPort2T1BTopLeft     =  1,
        VPort2T1BTopRight    =  2,
        VPort1T2BTop         =  0,
        VPort1T2BBottonLeft  =  1,
        VPort1T2BBottomRight =  2,
        VPortQuadTopLeft     =  0,
        VPortQuadTopRight    =  1,
        VPortQuadBottomLeft  =  2,
        VPortQuadBottomRight =  3,
        };

    enum StandardProperties
        {
        PartNumber,
        Description,
        Creator,
        Keywords,
        LastAuthor,
        Revision,
        Material,
        Vendor,
        Comments,
        Creation,
        Modification,
        LastSavedBy,
        NumStandardProps
        };

    // @enum Ref Control Flags
    enum RefControl
        {
        RFChangeAttr  = 1 <<  0, // @emem Change Attributes
        RFBurst       = 1 <<  1, // @emem Burst Composite (includes Add and Remove)
        RFTrimEnt     = 1 <<  2, // @emem Trim Entity
        RFTrimBoth    = 1 <<  3, // @emem Trim Both
        RFTrimDbl     = 1 <<  4, // @emem Trim Double
        RFTrimPos     = 1 <<  5, // @emem Trim Position
        RFTrimSec     = 1 <<  6, // @emem Trim Section
        RFBreakEnt    = 1 <<  7, // @emem Break Entity
        RFBreakBoth   = 1 <<  8, // @emem Break Both
        RFBreakDbl    = 1 <<  9, // @emem Break Double
        RFBreakPos    = 1 << 10, // @emem Break Position
        RFBreakSec    = 1 << 11, // @emem Break Section
        RFMoveRigid   = 1 << 12, // @emem XForm Move Rigidly
        RFMoveUniform = 1 << 13, // @emem Uniform XForm Scale Move
        RFMoveWarped  = 1 << 14, // @emem Non-uniform XForm Scale Move
        RFMoveNonRev  = 1 << 15, // @emem XForm Project Move
        RFCopyRigid   = 1 << 16, // @emem XForm Copy Rigidly
        RFCopyUniform = 1 << 17, // @emem Uniform XForm Scale Move
        RFCopyWarped  = 1 << 18, // @emem Non-uniform XForm Scale Copy
        RFCopyNonRev  = 1 << 19, // @emem XForm Project Copy
        RFJoinRigid   = 1 << 20, // @emem XForm Join Rigidly
        RFJoinUniform = 1 << 21, // @emem Uniform XForm Scale Move
        RFJoinWarped  = 1 << 22, // @emem Non-uniform XForm Scale Join
        RFJoinNonRev  = 1 << 23, // @emem XForm Project Join
        RFBoxMove     = 1 << 24, // @emem Box move
        RFDelete      = 1 << 25, // @emem Deletion
        RFDeleteSec   = 1 << 26, // @emem Delete by Section
        RFPrint       = 1 << 27, // @emem Printing
        RFVerifyEnt   = 1 << 28, // @emem Verify Entity
        RFGenericEdit = 1 << 29, // @emem Generic Edit
        // @end
        // Unused     = 1 << 30, // @emem Unused
        RFUnset       = 1 << 31, // @emem The value ULONG(-1) is used in
                                 //       CKEntityAttrib to indicate that
                                 //       the value should be ignored.  This
                                 //       effectively eliminates this value.
        };

    // @enum XForm commands
    enum XFormCmd
        {
        XFMove,     // @emem Move
        XFCopy,     // @emem Copy
        XFJoin      // @emem Join
        };

    // @enum XForm types
    enum XFormType
        {
        XFRigid,            // @emem Rigid
        XFScaleUniform,     // @emem Scale Uniform
        XFWarped,           // @emem Warped
        XFProject,          // @emem Project
        XFMirror            // @emem Mirror
        };

    // @enum Controls which keys are blocked.
    enum AccelBlockState
        {
        // @emem Unknown state, used by trees and such to indicate that
        // they're not responsible for the current state
        BlockUnknown = -1,
        // @emem No keys are blocked.
        BlockNone,
        // @emem Non-modified and certain modified keys are blocked.
        // (modified keys selected in Tools-Options-Misc).
        BlockSelected,
        // @emem All keys except F-keys, Escape and Return are blocked.
        BlockAllButSpecial,
        // @emem Tree navigation and modification keys are blocked
        // (Return, Space, Arrow keys, Delete, F2)
        BlockTreeNavigation,
        // @emem Blocks everything blocked by BlockSelected and
        // BlockTreeNavigation, plus Escape.
        BlockSelectedNavAndEscape
        };

    // @cmember,menum These values are used to determine what value is
    // used to create the dimension text string
    enum ValueType
        {
        // @@emem The variable <md CKDimension::m_dMeasuredValue> shall
        // be used.
        MeasuredValue = 0,
        // @@emem The string <md CKNote::m_csTextString> contains user
        // specified text and shall be used as-is.
        ManuallyEditedText,
        // @@emem The variable <md CKDimension::m_dSuppliedValue>
        // contains a value specified by the user.
        ManuallyEditedValue,
        // @@emem The variable <md CKDimension::m_dSuppliedValue>
        // contains a correct out-of-scale value specified by the
        // user.  The out-of-scale indication shall be used, but the
        // dimension shall not be marked as incorrect, or be prevented
        // by the "Prevent Incorrect Dimensions" flag.
        // Also known as a Reference Dimension.
        ReferenceValue,
        // @@emem The variable <md CKDimension::m_dSuppliedValue>
        // contains the value that <md CKDimension::m_dMeasuredValue>
        // had when the instance the dimension is part of was Burst.
        ModelizedValue,
        };

    // CKS::ArrowheadType cannot be UCHAR_MAX or UCHAR_MAX-1, which are used
    // for initilization, and for the indeterminant state of the flag, both of
    // which are required when editing many detail entities of different types
    // at the same time.
    // DanPoch Feb 2005

    // @cmember,menum The type of arrowhead.
    enum ArrowheadType
        {
        NoArrowHead = 0,  // @@emem No arrowhead, in detail symbols.
        UnfilledArrow,    // @@emem Unfilled arrow, leader penetrates
        FilledArrow,      // @@emem Filled arrow
        Slash,            // @@emem Slash or hash mark
        FilledCircle,     // @@emem Filled circle
        UnfilledCircle,   // @@emem Unfilled circle, leader penetrates
        TriangleStand,    // @@emem Filled triangle, (datum triangle stand)
        OpenArrow,        // @@emem Unfilled arrow, leader doesn't penetrate
        OpenCircle,       // @@emem Unfilled circle, leader doesn't penetrate
        OpenTriangle,     // @@emem Unfilled triangle, leader doesn't penetrate
        WedgeArrow,       // @@emem Unfilled arrow, no connecting line over leader
        FilledRectangle,  // @@emem Filled rectangle (for future use)
        UnfilledRectangle,// @@emem Unfilled rectangle, leader doesn't penetrate (for future use)
        IntegralSign,     // @@emem Integral sign (for future use)
        NumArrowHead      // MUST BE LAST, used for range checking only
        };

    // @cmember,menum File type values used by functions for importing or
    //                exporting.  Not all values are supported by all functions.
    enum FileType
        {
        FileUnspecified,        // @@emem The file type will be determined by its extension.
        FileDesignFile,         // @@emem Design Files
        FileDFTemplate,         // @@emem Template Files
        FilePart,               // @@emem CADKEY Part Files
        FilePattern,            // @@emem CADKEY Pattern Files
        FileKVTSessionFile,     // @@emem KVT Session Files
        FileKCM,                // @@emem KCM Files
        FilePDF3D,              // @@emem PDF3D Files
        FileACIS,               // @@emem ACIS Files
        FileSAT,                // @@emem ACIS SAT Files
        FileSAB,                // @@emem ACIS SAB Files
        FileACAD,               // @@emem AutoCAD Files
        FileDWG,                // @@emem AutoCAD DWG Files
        FileDXF,                // @@emem AutoCAD DXF Files
        FileCatiav4,            // @@emem Catia v4 Files
        FileCatiav4Model,       // @@emem Catia v4 Model Files
        FileCatiav4Export,      // @@emem Catia v4 Export Files
        FileCatiav4Session,     // @@emem Catia v4 Session Files
        FileCatiav4Drawing,     // @@emem Obsolete Drawing Files
        FileCatiav5,            // @@emem Catia v5 Files
        FileCatiav5Part,        // @@emem Catia v5 Part Files
        FileCatiav5Product,     // @@emem Catia v5 Product Files
        FileCatiav5Drawing,     // @@emem Catia v5 Drawing Files
        FileCatiav5CGR,         // @@emem Catia v5 CGR Files
        File3DXML,              // @@emem CATIA v5-3DX (3D Experience) Files
        FileCGM,                // @@emem CGM Files
        FileFusion,             // @@emem Fusion Files
        FileHMF,                // @@emem HMF HOOPS Files
        FileHSF,                // @@emem HSF HOOPS Files
        FileHTML,               // @@emem HTML Files
        FileHPGL,               // @@emem HPGL Files
        FileHPGL2,              // @@emem HPGL2 Files
        FileIFC,                // @@emem IFC Files
        FileIGES,               // @@emem IGES Files
        FileIGESGeometry,       // @@emem IGES geometry
        FileBMP,                // @@emem Bitmap Image Files
        FileDIB,                // @@emem DIB Image Files
        FileGIF,                // @@emem GIF Image Files
        FileJPG,                // @@emem JPEG Image Files
        FileTIF,                // @@emem TIF Image Files
        FileInventor,           // @@emem Inventor Files
		FileInventorPart,       // @@emem Inventor Part Files
		FileInventorAssembly,   // @@emem Inventor Assembly Files
        FileJT,                 // @@emem JT files
        FileParasolid,          // @@emem Parasolid Files
        FileParasolidText,      // @@emem Parasolid Text Files
        FileParasolidBinary,    // @@emem Parasolid Binary Files
        FileProE,               // @@emem PTCCreo Pro/E Files
		FileProEPart,           // @@emem Pro/E Part Files
        FileProEAssembly,       // @@emem Pro/E Assembly Files
        FileProEDrawing,        // @@emem PTCCreo Pro/E Drawing Files
        FileCSV,                // @@emem CSV Files
        FileRhino,              // @@emem Rhino Files
        FileSolidedgeFile,      // @@emem Solidedge Files
		FileSolidedgePart,      // @@emem Solidedge Part Files
        FileSolidedgeAssembly,  // @@emem Solidedge Assembly Files
        FileSolidedgeShtMetal,  // @@emem Solidedge Sheet Metal Workbench Files
        FileSolidedgeDrawing,   // @@emem Solidedge Drawing Files
        FileSolidworks,         // @@emem Solidworks Files
		FileSolidworksPart,     // @@emem Solidworks Part Files
        FileSolidworksAssembly, // @@emem Solidworks Assembly Files
        FileSolidworksDrawing,  // @@emem Solidworks Drawing Files
        FileSTEPAll,            // @@emem STEP Files
        FileSTEP,               // @@emem STEP (Uncompressed) Files
        FileSTEPCompressed,     // @@emem Compressed STEP Files
        FileStereoLithography,  // @@emem Stereolithography (.stl) Files
        FileUnigraphics,        // @@emem Unigraphics files
        FileUnigraphicsDrawing, // @@emem Unigraphics Drawing files
        FilePDF,                // @@emem PDF Files
        FileU3D,                // @@emem U3D Files,
        FileOBJ,                // @@emem OBJ Files
        FileCGM3,               // @@emem CGM3 Files
        FileVRML,               // @@emem VRML files
        File3MF,                // @@emem 3MF files
        FileglTF,               // @@emem glTF  files
        FileglTFText,           // @@emem glTF Text files
        FileglTFBinary,         // @@emem glTF Binary files
        FileJTAssembly,         // @@emem JT Assembly files
        FileCount
        };

    //MMBActions Controls which actions correspond to which modifier keys
    //              in a middle mouse button drag.
    enum MMBActions
        {
        PanZoomRotate,  // Ctrl=Pan,    Shift=Zoom,   Alt/None=Rotate
        PanRotateZoom,  // Ctrl=Pan,    Shift=Rotate, Alt/None=Zoom
        ZoomPanRotate,  // Ctrl=Zoom,   Shift=Pan,    Alt/None=Rotate
        ZoomRotatePan,  // Ctrl=Zoom,   Shift=Rotate, Alt/None=Pan
        RotatePanZoom,  // Ctrl=Rotate, Shift=Pan,    Alt/None=Zoom
        RotateZoomPan   // Ctrl=Rotate, Shift=Zoom,   Alt/None=Pan
        };

    enum BendLineTypes
        {
        BendLineNone = 0, // @emem No type specified
        BendStartLine,    // @emem start line
        BendCenterLine,   // @emem center line
        BendEndLine,      // @emem end line
        BendLineLast
        };

    // @cmember,menum <c CKTable> column width behavior flags.
    enum TableWidthBehaviour {
        WB_AUTO,	// @@emem Column width will grow and shrink as data changes.
                    // Row height does not change.
        WB_WRAP,	// @@emem Column width is fixed with the test wrapping.
                    // Row height changes to fit data as it wraps.
        WB_FIXED,	// @@emem Column width is fixed with the text truncated.
                    // Row height does not change.
        };

    // @cmember,menum <c CKHoleTable> numbering method for holes of the same
    //  size.
    enum HTNumberingMethod {
        XInc_YInc = 0,
        XInc_YDec,
        XDec_YInc,
        XDec_YDec,
        YInc_XInc,
        YInc_XDec,
        YDec_XInc,
        YDec_XDec,
        };

    // @cmember,menum Point Type
    enum TargetPointType
        {
        TargetSolid,    // @@emem solid circle with crosshairs
        TargetQuadRing, // @@emem quadranted ring with crosshairs
        TargetQuad      // @@emem quadranted circle with crosshairs
        };

    // @enum Which path is the base for the given value.
    enum BasePathType
        {
        SupportPath = 0,
        UserDataPath = 1,
        LanguagePath = 2
        };

    // @enum Range checking values for calculator and input functions.
    enum CalcTextRange
        {
        RangeAny,
        GreaterThan,
        GreaterThanEqual,
        LessThan,
        LessThanEqual,
        MagGreaterThan,
        MagGreaterThanEqual,
        MagLessThan,
        MagLessThanEqual
        };

    // @enum Flags for the types of instances that can be selected by the
    // DrawInstSelect function.
    enum InstSelect
        {
        GetDrawInst        = 0x001,    // @emem Just Drawing Instances
        GetDetailCallout   = 0x002,    // @emem Just Detail Callouts
        GetSectionView     = 0x004,    // @emem Section Views
        GetAllInst         = 0x007,    // @emem All of them
        };

    // @enum Types of regions supported by the Detail Callout object
    enum CalloutRegionType {
        CAR_Rectangular    = 0,
        CAR_Circular,
        CAR_RoundedRectangular,
        };
    };

#endif
