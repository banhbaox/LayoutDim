// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
#ifndef CKRFCTRL_H_LOADED
#define CKRFCTRL_H_LOADED

enum
    {
    RFAttr       = 0x00000001,
    RFBurst      = 0x00000002,
    RFTrimEnt    = 0x00000004,
    RFTrimBoth   = 0x00400000,
    RFTrimDbl    = 0x00000008,
    RFTrimPos    = 0x00000010,
    RFTrimSec    = 0x00000020,
    RFBreakEnt   = 0x00000040,
    RFBreakBoth  = 0x01000000,
    RFBreakDbl   = 0x00000080,
    RFBreakPos   = 0x00000100,
    RFBreakSec   = 0x00000200,
    RFMoveRigid  = 0x00000400,
    RFMoveWarped = 0x00000800,
    RFMoveNonRev = 0x00001000,
    RFCopyRigid  = 0x00002000,
    RFCopyWarped = 0x00004000,
    RFCopyNonRev = 0x00008000,
    RFJoinRigid  = 0x00010000,
    RFJoinWarped = 0x00020000,
    RFJoinNonRev = 0x00040000,
    RFBoxMove    = 0x00080000,
    RFDelete     = 0x00100000,
    RFDeleteSec  = 0x00200000,
    RFPartFile   = 0x00800000,
    RFPlotFile   = 0x02000000,
    RFPrint      = 0x04000000,
    RFCADL       = 0x08000000,
    RFTranslate  = 0x10000000,
    RFVerAtt     = 0x20000000,
    RFVerCoord   = 0x40000000,
    RFIntegrate  = 0x80000000
    };

// For backwards compatibility
#define RF1_TRIM_ENT        RFTrimEnt    // trimming to an entity
#define RF1_TRIM_DBL        RFTrimDbl    // double trimming
#define RF1_TRIM_POS        RFTrimPos    // trimming to a position
#define RF1_TRIM_SEC        RFTrimSec    // section trimming
#define RF1_BREAK_ENT       RFBreakEnt   // breaking to an entity
#define RF1_BREAK_DBL       RFBreakDbl   // double breaking
#define RF1_BREAK_POS       RFBreakPos   // breaking to a position
#define RF1_BREAK_SEC       RFBreakSec   // section breaking
#define RF1_MOVE_RIGID      RFMoveRigid  // xform move rigid
#define RF1_MOVE_WARPED     RFMoveWarped // xform move nonrigid reversible
#define RF1_MOVE_NONREV     RFMoveNonRev // xform move nonreversible
#define RF1_COPY_RIGID      RFCopyRigid  // xform copy rigid
#define RF1_COPY_WARPED     RFCopyWarped // xform copy nonrigid reversible
#define RF1_COPY_NONREV     RFCopyNonRev // xform copy nonreversible
#define RF1_JOIN_RIGID      RFJoinRigid  // xform join rigid
#define RF1_JOIN_WARPED     RFJoinWarped // xform join nonrigid reversible
#define RF1_JOIN_NONREV     RFJoinNonRev // xform join nonreversible
#define RF1_BOXMOVE         RFBoxMove    // box moving
#define RF2_ATTR            RFAttr       // attribute change
#define RF2_BURST           RFBurst      // composite bursting
#define RF2_DELETE          RFDelete     // deletion
#define RF2_DELETE_SEC      RFDeleteSec  // section deletion
#define RF2_PARTFILE        RFPartFile   // part filing
#define RF2_PLOTFILE        RFPlotFile   // writing to plot file
#define RF2_PRINT           RFPrint      // printing
#define RF2_CADL            RFCADL       // writing to cadl
#define RF2_TRANSLATE       RFTranslate  // translation (such as iges)
#define RF2_VERATT          RFVerAtt     // verification of attributes
#define RF2_VERCD           RFVerCoord   // verification of coordinates
#define RF2_INTEGRATE       RFIntegrate  // perimiter / area / moment

#define RF1_TRIM        (RF1_TRIM_ENT | RF1_TRIM_DBL | RF1_TRIM_POS | RF1_TRIM_SEC)
#define RF1_BREAK       (RF1_BREAK_ENT | RF1_BREAK_DBL | RF1_BREAK_POS | RF1_BREAK_SEC)
#define RF1_SECTION     (RF1_TRIM_SEC | RF1_BREAK_SEC)
#define RF1_TRIMBREAK   (RF1_TRIM | RF1_BREAK)
#define RF1_MOVE        (RF1_MOVE_RIGID | RF1_MOVE_WARPED | RF1_MOVE_NONREV)
#define RF1_COPY        (RF1_COPY_RIGID | RF1_COPY_WARPED | RF1_COPY_NONREV)
#define RF1_JOIN        (RF1_JOIN_RIGID | RF1_JOIN_WARPED | RF1_JOIN_NONREV)
#define RF1_RIGID       (RF1_MOVE_RIGID | RF1_COPY_RIGID | RF1_JOIN_RIGID)
#define RF1_WARPED      (RF1_MOVE_WARPED | RF1_COPY_WARPED | RF1_JOIN_WARPED)
#define RF1_NONREV      (RF1_MOVE_NONREV | RF1_COPY_NONREV | RF1_JOIN_NONREV)
#define RF1_REVERSIBLE  (RF1_RIGID | RF1_WARPED)
#define RF1_NONRIGID    (RF1_WARPED | RF1_NONREV)
#define RF1_XFORM       (RF1_MOVE | RF1_COPY | RF1_JOIN)

#define RF2_DELETE_ANY  (RF2_DELETE | RF2_DELETE_SEC)
#define RF2_FILE        RF2_PARTFILE | RF2_CADL | RF2_TRANSLATE
#define RF2_WRITE       (RF2_PLOTFILE | RF2_PRINT)
#define RF2_VERIFY      (RF2_VERATT | RF2_VERCD | RF2_INTEGRATE)

// Attribute codes

#define RFA_COLOR       1
#define RFA_LTYPE       2
#define RFA_LWIDTH      3
#define RFA_PEN         4
#define RFA_LEVEL       5

// Plot color flags

#define RFC_PEN         0
#define RFC_COLOR       1

// Join entity types

#define RFJ_LINES       0
#define RFJ_ARCS        1
#define RFJ_SPLINES     2

// Rigidity flags

#define RFX_RIGID       0
#define RFX_WARPED      1
#define RFX_NONREV      2

#endif  // CKRFCTRL_H_LOADED
