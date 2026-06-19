// Copyright Kubotek Corporation, 1999-2024
// All Rights Reserved
#ifndef CK_SDK_INCLUDED
#define CK_SDK_INCLUDED
#include <map>
#include <string>
#include <vector>

#if !defined(_UNICODE) || !defined(UNICODE)
#error Both _UNICODE and UNICODE must be defined to use the KeyCreator SDK
#endif

#if (_MSC_VER < 1940 || _MSC_VER >= 1950)
#error Only Visual Studio 2022 is supported for use with the KeyCreator SDK
#endif

#ifndef _NATIVE_WCHAR_T_DEFINED
#error The wchar_t as native type option must be enabled to use the KeyCreator SDK
#endif

#include "ck_partbase.h"
#include "ck_types.h"
#include "ck_enum.h"
#include "ck_set.h"
#include "ck_ldef.h"
#include "ck_draft.h"
#include "CKSDetailOptions.h"
#include "CKSMatrix.h"
#include "CKSSimConstraintOptions.h"
#include "FSFacetStructs.h"
#include "SolidsStructures.h"

// These constants are to allow for conditional compilation of a CDE based on
// the features available in a given release of KeyCreator.  These will not be
// changed during a release cycle.  They will only be changed once when a
// function is added/removed/changed after a given release.  If no changes
// are made between two releases, they will have the same version numbers.
#define KC_SDK_VER_MAJOR 9
#define KC_SDK_VER_MINOR 0
#define KC_SDK_VER_POINT 0

#define DEPRECATED_IN_13(szNew) \
    __declspec(deprecated("deprecated in v12.5, use " szNew " instead.")) 

#define DEPRECATED_IN_12_5(szNew) \
    __declspec(deprecated("deprecated in v12.5, use " szNew " instead.")) 

#define DEPRECATED_IN_12(szNew) \
    __declspec(deprecated("deprecated in v12.0, use " szNew " instead.")) 

// See the SDK help file for documentation of these functions.
// Gets the version numbers for the application
SDK_FUNC int ck_get_vernum(int &nMajorVersion, int &nMinorVersion, int &nPointVersion,
                           int &nBuildNumber);
//  Gets the current language
SDK_FUNC std::wstring ck_get_language();
//  Gets the current language directory
SDK_FUNC std::wstring ck_get_languagedir();

SDK_FUNC int ck_set(int nParameter, int nData);
SDK_FUNC int ck_set(int nParameter, double dData);
SDK_FUNC int ck_set(int nParameter, double dData1, double dData2, double dData3);
SDK_FUNC int ck_set(int nParameter, long lData1, long lData2);
SDK_FUNC int ck_set(int nParameter, const std::wstring &csData);
SDK_FUNC int ck_set(int nParameter, const std::vector<std::wstring> &lcsData);
SDK_FUNC int ck_set(int nParameter, PVOID pData);
SDK_FUNC int ck_inquire(int nParameter, int &nData);
SDK_FUNC int ck_inquire(int nParameter, double &dData);
SDK_FUNC int ck_inquire(int nParameter, double &dData1, double &dData2, double &dData3);
SDK_FUNC int ck_inquire(int nParameter, long &lData1, long &lData2);
SDK_FUNC int ck_inquire(int nParameter, std::wstring &csData);
SDK_FUNC int ck_inquire(int nParameter, std::vector<std::wstring> &lcsData);
SDK_FUNC int ck_inquire(int nParameter, PVOID pData);

SDK_FUNC std::wstring ck_get_support_path();
SDK_FUNC int ck_set_userdata_path(const std::wstring &csPath);
SDK_FUNC std::wstring ck_get_userdata_path();
SDK_FUNC int ck_register_path(const std::wstring &csName,
                              CKS::BasePathType nBasePath,
                              const std::wstring &csDisplayText,
                              const std::wstring &csDefault);
SDK_FUNC int ck_unregister_path(const std::wstring &csName);
SDK_FUNC int ck_set_path(const std::wstring &csName,
                         const std::wstring &csPath);
SDK_FUNC int ck_get_path(const std::wstring &csName, std::wstring &csPath);

SDK_FUNC int ck_set_autosave_path(const std::wstring &csPath);
SDK_FUNC std::wstring ck_get_autosave_path();
SDK_FUNC int ck_set_backup_path(const std::wstring &csPath);
SDK_FUNC std::wstring ck_get_backup_path();

// Get three doubles
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             double &dX, double &dY, double &dZ,
                             int nType, bool bAccept = false, int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             double &dX, double &dY, double &dZ,
                             int nType, bool bAccept = false, int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);

// Get one double
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             double &dValue, bool bAccept = false,
                             int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             double &dValue, bool bAccept = false,
                             int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);

// Get an array of doubles
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             g_array<double> &adValues, bool bAccept = false,
                             int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             g_array<double> &adValues, bool bAccept = false,
                             int nDefault = 1,
                             CKS::CalcTextRange nMin = CKS::CalcTextRange(0),
                             double dMin = 0.0,
                             CKS::CalcTextRange nMax = CKS::CalcTextRange(0),
                             double dMax = 0.0);

// Get one integer
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             int &nValue, bool bAccept = false,
                             int nDefault = 1, int *pMin = NULL,
                             int *pMax = NULL);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             int &nValue, bool bAccept = false,
                             int nDefault = 1, int *pMin = NULL,
                             int *pMax = NULL);

// Get a string
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             std::wstring &csValue, bool bAccept = false,
                             int nDefault = 1);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             std::wstring &csValue, bool bAccept = false,
                             int nDefault = 1);

// Get a menu choice
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             bool bAccept = true, int nDefault = 1);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             bool bAccept = true, int nDefault = 1);
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             bool bAccept, int nDefault, ULONG ulFuncs);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             bool bAccept, int nDefault, ULONG ulFuncs);

// Get a cursor position
SDK_FUNC Events ck_get_input(const std::wstring &csPrompt,
                             const std::wstring &csMenu,
                             CKSCoord &rCoord, bool bAccept = true,
                             int nDefault = 1,
                             CurStyle nCurStyle = CK_CUR_CROSS,
                             CurPlace nCurPlace = CK_BOX_LT,
                             double dRotation = 0, bool bUseModifier = false);
SDK_FUNC Events ck_get_input(ULONG ulPrompt, ULONG ulMenu,
                             CKSCoord &rCoord, bool bAccept = true,
                             int nDefault = 1,
                             CurStyle nCurStyle = CK_CUR_CROSS,
                             CurPlace nCurPlace = CK_BOX_LT,
                             double dRotation = 0, bool bUseModifier = false);

SDK_FUNC Events ck_pause();
SDK_FUNC Events ck_pause(const std::wstring &csPrompt);
SDK_FUNC Events ck_pause(ULONG ulPrompt);
SDK_FUNC Events ck_prompt(const std::wstring &csPrompt);
SDK_FUNC Events ck_prompt(ULONG ulPrompt);

typedef Events (*ck_getevent_func_type)(Events, UINT, CKSCoord);

SDK_FUNC Events ck_getevent(ck_getevent_func_type pCallback,
                            const std::wstring &csPrompt,
                            const std::wstring &csMenu,
                            CKSCoord *pCoord = NULL,
                            CurStyle nCurStyle = CK_CUR_CROSS,
                            CurPlace nCurPlace = CK_BOX_LT,
                            CKSCoordArray *paCoord = NULL,
                            double dRotation = 0, int nDefault = 1);
SDK_FUNC Events ck_getevent(ck_getevent_func_type pCallback,
                            ULONG ulPrompt, ULONG ulMenu,
                            CKSCoord *pCoord = NULL,
                            CurStyle nCurStyle = CK_CUR_CROSS,
                            CurPlace nCurPlace = CK_BOX_LT,
                            CKSCoordArray *paCoord = NULL,
                            double dRotation = 0, int nDefault = 1);

SDK_FUNC int ck_get_style(int &nResult);
SDK_FUNC int ck_get_width(int &nResult);
SDK_FUNC int ck_get_color(int &nResult);

SDK_FUNC int ck_redraw();

SDK_FUNC bool is_kc_in_leaf_function();

SDK_FUNC int cadl_execute_file(const std::wstring &csFilename);
SDK_FUNC int cadl_execute(const std::wstring &csText);
SDK_FUNC int calc_evaluate(const std::wstring &csText, double &dValue);

class SDK_EXPORT CKPart;

SDK_FUNC int sys_part_load(const std::wstring &csFileName,
                           const std::wstring &csPartName,
                           CKPart &rPart, bool bVisible,
                           CKS::FileType nType, bool bQuiet);

SDK_FUNC int sys_part_new(CKPart &rPart, std::wstring &csFileName,
                          bool bNewDesignDoc, std::wstring &csPartName,
                          bool bCreateFrame);

SDK_FUNC int sys_part_get(const std::wstring &csFileName,
                          const std::wstring &csPartName, CKPart &rPart);

SDK_FUNC int sys_partfiles_list(const std::wstring &csFileName,
                                std::vector<std::wstring> &rPartsList);

class CWnd;

SDK_FUNC int ck_select_directory(std::wstring &csPath,
                                 const std::wstring *pcsCaption = NULL,
                                 const std::wstring *pcsInitialDir = NULL,
                                 CWnd *pWnd = NULL);

SDK_FUNC bool ck_enable_level_dragging(bool bEnable);

SDK_FUNC int sys_open_workspace(const std::wstring &csWorkSpace,
                                bool bSuppressError);
SDK_FUNC int sys_close_workspace();
SDK_FUNC int sys_save_workspace();

SDK_FUNC int sys_call_func(UINT unID);

SDK_FUNC bool ck_batch_translate(CKS::FileType nImportType,
                                 CKS::FileType nExportType,
                                 const std::vector<std::wstring> &lcsDirs,
                                 const std::vector<std::wstring> &lcsFiles,
                                 const std::vector<std::wstring> &acsFilters,
                                 bool bRecurse,
                                 const std::wstring &csDestPath,
                                 const std::wstring &csLogFile, bool bQuiet);

SDK_FUNC CKSErrors kc_get_file_units(CKS::FileType eFileType,
                                     const std::wstring& csFileName,
                                     const std::wstring& csPartName,
                                     CKSUnits& eLengthUnits);

class CKEntity;
class SDK_EXPORT CKSAnim;
class SDK_EXPORT CKSModifierAnim;
class CKDispView;

class SDK_EXPORT CKSBody;
typedef std::vector<CKSBody *> CKSBodyArray;
class SDK_EXPORT CKSFace;
typedef std::vector<CKSFace *> CKSFaceArray;
class SDK_EXPORT CKSEdge;
typedef std::vector<CKSEdge *> CKSEdgeArray;
class SDK_EXPORT CKSVertex;
typedef std::vector<CKSVertex *> CKSVertexArray;

enum GraftType;
enum DirectionType;

// @doc EXTERNAL SDK

// @class This class is used for all part-specific SDK functions.
// The object corresponding to the currently active
// Part can be obtained through the function <f CKGetActivePart>.
class SDK_EXPORT CKPart : public CKPartBase
    {
public:
    CKPart();
    CKPart(CKPartDoc *pDoc);
    CKPart(const CKPart &rRight);
    CKPart &operator=(const CKPart &rRight);
    ~CKPart();

    // @cmember bool | IsValid() const ||
    // Does this object refer to a valid Part.
    bool IsValid() const { return(m_pDocHandle != NULL); }

    // @cmember Is the part to which this handle refers open as read-only?
    bool IsReadOnly() const;

    // @cmember Is the database locked against editing?
    bool IsDBLocked() const;

    // @cmember Given an entity handle, get its permanent ID.
    ULONG GetID(const CKSEntity &pEntity) const;

    // @cmember Given a drawing instance handle, get its permanent ID.
    ULONG GetID(const CKSDrawInst &rEntity) const;

    // @cmember Given a copious handle, get its permanent ID.
    ULONG GetID(const CKSCopious &rCopious) const;

    // @cmember Given an entity ID, get its handle.
    CKSEntity GetEntity(ULONG ulID) const;

    // @cmember Given a layout name, get its handle.
    CKSLayout GetLayout(const std::wstring &csName);

    // @cmember Get active layout handle.
    CKSLayout GetActiveLayout();

    // @cmember Given a drawing instance ID, get its handle.
    CKSDrawInst GetInstance(ULONG ulID) const;

    // @cmember Given a copious ID, get its handle.
    CKSCopious GetCopious(ULONG ulID) const;

    //@cmember Return a copious pointer matching one in a list of copious types.
    CKSCopious GetNextCopiousType(CKSCopious &rCopious,
                                  const std::vector<USHORT> &ausTypes);

    // @cmember Get the part's name
    int GetPartName(std::wstring &csPartName);

    // @cmember Set the name of any part that belongs to the design file
    // of this part.  Any leading or trailing whitespace will be stripped,
    // and the provided string will be modified appropriately.
    int SetPartName(std::wstring &csNewPartName,
                    const std::wstring &csOldPartName);

    // @cmember Get the full pathname to the part
    int GetPathName(std::wstring &csPathName);

    // @cmember Get the area and centroid of the given entities
    CKSErrors GetAreaAndCentroid(CKSEntityArray &aEnts, bool bUsePanels,
                                 double dPanelInterval,
                                 double &dArea, CKSCoord &ckscCentroid);

    // @cmember Get the moments of the given entities about an axis point
    CKSErrors GetMoments(CKSEntityArray &aEnts, CKSCoord &ckscAxisPoint,
                         double dPanelInterval, double &dMomentX, double &dMomentY);

    // @cmember Get the actual and projected perimeter of the given entities
    CKSErrors GetPerimeter(CKSEntityArray &aEnts, double &dActual,
                           double &dProjected);

    // @cmember Close this part
    int Close(bool bForceClose = false, bool bCloseFile = false);

    // @cmember Make this the active part
    int MakeActive(bool bCreateFrame = false);

    // @cmember Save this part, optionally with a different filename.
    int Save(const std::wstring *pcsPathName = NULL, bool bQuickSave = false,
             bool bMsgs = false);

    // @cmember Save the thumbnail preview of a viewport
    int SavePreview(int nVPNum);

    // @cmember Start print interaction using the given viewport.
    int Print(int nVPNum);

    // @cmember Start print preview interaction using the given viewport.
    int PrintPreview(int nVPNum);

    // @cmember Print the given viewport with no user interaction.
    int PrintDirect(int nVPNum);

    // @cmember Prompt the user to select one of two vectors
    int SelectSide(const std::wstring &csPrompt, const CKSMatrix &rMatrix,
                   bool &bPositiveVec);

    // @cmember Prompt the user to select one of two vectors
    int SelectSide(const std::wstring &csPrompt,const CKSCoord &ckcBase,
                   const CKSCoord &ckcTip, bool &bPositiveVec);

    // @cmember Prompt the user to reverse or accept a set of vectors
    // (used to select side of a compound curve)
    int SelectSide(const std::wstring &csPrompt,
                   const CKSCoordArray &ackcBases,
                   const CKSCoordArray &ackcTips, bool &bPositiveVec);

    //// Trim either or both ends of an entity
    int Trim(CKSEntity &pEntity, bool bStartTrim, int nStartSeg,
             double dStartParam, bool bEndTrim, int nEndSeg, double dEndParam);

    // @cmember Compute extents of the geometry in model mode
    int GetModelExtents(CKSCoord &rckcMin, CKSCoord &rckcMax,
                        CKSMatrix *pViewMat);

    // @cmember Delete a Single entity
    int DeleteEntity(CKSEntity &pEntity);

    // @cmember Delete multiple entities
    int DeleteEntities(CKSEntityArray &aEntities);

    // @cmember Gets the Matrix of an entity
    int GetMatrix(CKSEntity &rEntity, CKSDrawInst *pDrawInst,
                  CKSMatrix &rMatrix);

    // @cmember Transforms the given coordinate from the entity's local
    // coordinate system into the world coordinate system
    int ToWorld(CKSEntity &rEntity, CKSCoord &rCoord) const;

    // @cmember Transforms the given coordinate from the world coordinate
    // system into the entity's local coordinate system
    int FromWorld(CKSEntity &rEntity, CKSCoord &rCoord) const;

    // @cmember Transforms the given vector from the entity's local
    // coordinate system into the world coordinate system
    int VectorToWorld(CKSEntity &rEntity, CKSCoord &rCoord) const;

    // @cmember Transforms the given vector from the world coordinate
    // system into the entity's local coordinate system
    int VectorFromWorld(CKSEntity &rEntity, CKSCoord &rCoord) const;

// @Group Construction Plane Functions
    // @cmember Gets the matrix of the active construction plane
    int GetActiveCPlaneMatrix(CKSMatrix &rMat);

    // @cmember Sets the matrix of the active construction plane
    int SetActiveCPlaneMatrix(CKSMatrix &rMat);

    // @cmember Sets the matrix of the active construction plane
    int SetActiveCPlaneMatrix(CKSEntity &pPlane);

    // @cmember Gets the number of the active construction plane
    int GetActiveCPlaneNumber(int &nCPlane);

    // @cmember Converts a coordinate from World space to the CPlane space
    int WorldToCPlane(CKSCoord &rckcPos);

    // @cmember Converts a coordinate from CPlane space to the World space
    int CPlaneToWorld(CKSCoord &rckcPos);

    // @cmember Converts a vector from World space to the CPlane space
    int VectorWorldToCPlane(CKSCoord &rckcPos);

    // @cmember Converts a vector from CPlane space to the World space
    int VectorCPlaneToWorld(CKSCoord &rckcPos);

    // @cmember Extend a line until it reaches the window border.
    int ExtendToBorder(CKSCoord &ckscStart, CKSCoord &ckscEnd, int nMode,
                       int nViewport = -1);

// @Group Creation Functions

    // @cmember Add a new Angular dimension to this part.
    CKSEntity AddAngularDim(bool bInnerAngle,
                            const CKSRefLine &rlFirst,
                            const CKSRefLine &rlSecond,
                            CKS::LocationArray &aLocations,
                            CKS::Location *pTextLoc,
                            CKSDrawInst *pInst = NULL,
                            const CKSDimensionOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL,
                            const CKSWitness *pwitFirst = NULL,
                            const CKSWitness *pwitSecond = NULL,
                            const CKSLeaderArc *pldrFirst = NULL,
                            const CKSLeaderArc *pldrSecond = NULL);

    // @cmember Add a new angular three point dimension to the part
    CKSEntity AddAngularDim(bool bInnerAngle,
                            CKS::Location *pTextLoc,
                            CKS::Location *locVertex,
                            CKS::Location *locPoint1,
                            CKS::Location *locPoint2,
                            CKSCoord    &ckscAnglePick,
                            const CKSDimensionOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

    // @cmember Add a new angular two line dimension to the part
    CKSEntity AddAngularDim(bool bInnerAngle,
                            CKS::Location *pTextLoc,
                            const CKSEntity &rlFirst,
                            const CKSEntity &rlSecond,
                            CKSCoord    &ckscAnglePick,
                            const CKSDimensionOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

    // @cmember Add a new Arc to this part.
    CKSEntity AddArc(double dX, double dY, double dZ, double dRadius,
                     double dStartAngle, double dDeltaAngle,
                     const CKEntityAttrib *pAttrib = NULL,
                     const CKSMatrix *pMatrix = NULL,
                     CKSLevel *pLevel = NULL,
                     CKSAnim *pAnim = NULL);

    // @cmember Add a new Arc to this part.
    CKSEntity AddArc(const CKSCoord &rCenter, double dRadius,
                     double dStartAngle, double dDeltaAngle,
                     const CKEntityAttrib *pAttrib = NULL,
                     const CKSMatrix *pMatrix = NULL,
                     CKSLevel *pLevel = NULL,
                     CKSAnim *pAnim = NULL);

     // @cmember Add a new Arc Length Dimension to this part.
    CKSEntity AddArcLengthDim(const CKSEntity *pEnt,
                              CKS::Location *ckscTextPos,
                              const CKEntityAttrib *pAttrib,
                              int nDispView,
                              const CKSDetailFormat &detFormat,
                              const CKSDetailUnits &detUnits,
                              const CKSDetailUnits &detDualUnits,
                              const CKSDetailLines &detLines,
                              const CKSDetailDimText &detText,
                              const CKSMatrix *pMatrix,
                              CKSLevel *pLevel, CKSAnim *pAnim);

     // @cmember Add a new Arc Length Dimension to this part.
    CKSEntity AddArcLengthDim(const CKSEntity *pEnt,
                              CKS::Location *ckscTextPos,
                              const CKEntityAttrib *pAttrib,
                              int nDispView,
                              CKSDimStyle ucDimStyle,
                              bool   bPartial,
                              int    nSeg1,
                              double dParam1,
                              int    nSeg2,
                              double dParam2,
                              const CKSDetailFormat &detFormat,
                              const CKSDetailUnits &detUnits,
                              const CKSDetailUnits &detDualUnits,
                              const CKSDetailLines &detLines,
                              const CKSDetailDimText &detText,
                              const CKSMatrix *pMatrix,
                              CKSLevel *pLevel, CKSAnim *pAnim);

    // @cmember Add a new Balloon to this part
    CKSEntity AddBalloon(const CKString &cksPrimaryText,
                      CKSBalloonType nBallonType = CK_CircleBalloon,
                      CKSLeaderType nLeaderType = CK_NoLeader,
                      double dDiameterRatio = 1.5,
                      const CKString &cksSecondaryText = NULL,
                      CKS::Location *pSymbolLoc= NULL,
                      CKS::LocationArray *paLocations = NULL,
                      CKSStackingAlign nAlign = CK_NoStacking,
                      int nDispView = 0,
                      const CKSDetailOptions *pOptions = NULL,
                      const CKSMatrix *pMatrix = NULL,
                      CKSLevel *pLevel = NULL,
                      CKSAnim *pAnim = NULL);

    // @cmember Add a new Baseline dimension to this part.
    CKSEntity AddBaseLinearDim(CKSEntity *pBaseDim, double dOffsetValue,
                               UCHAR ucDispStyle,
                               double dAxisAngle,
                               const CKSWitness &rWitness,
                               const CKSLeader &rFirstLeader,
                               const CKSLeader &rSecondLeader,
                               CKS::Location *pLocation,
                               CKS::Location *pTextLocation = NULL,
                               int nDispView = 0,
                               const CKSDimensionOptions *pOptions = NULL,
                               const CKSMatrix *pMatrix = NULL,
                               CKSLevel *pLevel = NULL,
                               CKSAnim *pAnim = NULL);

    // @cmember Add a new base Baseline dimension to this part using minimal
    //  dimension information
    CKSEntity AddBaseLinearDim(UCHAR ucDispStyle,
                               double dAxisAngle,
                               CKS::Location *pLocation,
                               CKS::Location *pTextLoc = NULL,
                               int nDispView = 0,
                               const CKSDimensionOptions *pOptions = NULL,
                               const CKSMatrix *pMatrix = NULL,
                               CKSLevel *pLevel = NULL,
                               CKSAnim *pAnim = NULL);

    // @cmember Add a new BOM Table to this part
    CKSEntity AddBOMTable(CKSLevel *pLevel,CKSDetailFormat *rAttrib,
                            CKAttrib *rGridAttrib,const CKSMatrix *rMatrix,
                            CKS::Location *pBaseLoc, int nDispView,
                            CKSAnim *pAnim);

    // @cmember Add a new attached Centerline to this part
    CKSEntity AddCenterLine(const CKS::CenterlineType ucType,
                            const double dExtension,
                            const bool bAbsolute,
                            CKS::Location *pFirstLoc,
                            CKS::Location *pSecondLoc = NULL,
                            const CKEntityAttrib *pAttrib = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new unattached Centerline to this part
    CKSEntity AddCenterLine(const CKS::CenterlineType ucType,
                            const double dExtension,
                            const bool bAbsolute,
                            CKSCoord &rFirst,
                            CKSCoord *pSecond,
                            double *pRad,
                            const CKEntityAttrib *pAttrib = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new chamfer dimension to this part.
    CKSEntity AddChamferDim(CKSChamferType ucDimType,
                            const CKSEntity &rChamferLine,
                            CKS::Location *pTextLoc = NULL,
                            int nDispView = 0,
                            const CKSDimensionOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new chamfer dimension to this part.
    CKSEntity AddChamferDim(CKSChamferType ucDimType,
                            const  CKSRefLine &RefLine,
                            CKS::Location *pTextLoc = NULL,
                            int nDispView = 0,
                            const CKSDimensionOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new circle to this part.
    CKSEntity AddCircle(double dX, double dY, double dZ, double dRadius,
                        const CKEntityAttrib *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

     // @cmember Add a new circle to this part
    CKSEntity AddCircle(const CKSCoord &rCenter, double dRadius,
                        const CKEntityAttrib *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL) ;

    // @cmember Add a new circular dimension to this part.
    CKSEntity AddCircularDim(const CKSRefArc &rRefArc,
                             CKSEntity *pArc,
                             CKS::Location *pTextLoc,
                             int nDispView = 0,
                             const CKSDimensionOptions *pOptions = NULL,
                             const CKSMatrix *pMatrix = NULL,
                             CKSLevel *pLevel = NULL,
                             CKSDrawInst *pInst = NULL,
                             CKS::Location *pRefCntrLoc = NULL,
                             CKSCoord *pckcElbow1 = NULL,
                             CKSCoord *pckcElbow2 = NULL,
                             const CKSWitness *pWitLine = NULL,
                             const CKSWitnessArc *pWitArc = NULL,
                             const CKSLeader *pLdrFirst = NULL,
                             const CKSLeader *pLdrSecond = NULL,
                             CKSAnim *pAnim = NULL);

    // @cmember Add a new circular dimension to this part.
    CKSEntity AddCircularDim(const CKSRefArc &rRefArc,
                             CKSEntity *pArc,
                             CKSCoord *pHitPos,
                             CKS::Location *pTextLoc,
                             int nDispView = 0,
                             const CKSDimensionOptions *pOptions = NULL,
                             const CKSMatrix *pMatrix = NULL,
                             CKSLevel *pLevel = NULL,
                             CKSDrawInst *pInst = NULL,
                             CKS::Location *pRefCntrLoc = NULL,
                             CKSCoord *pckcElbow1 = NULL,
                             CKSCoord *pckcElbow2 = NULL,
                             CKSAnim *pAnim = NULL);

    // @cmember Add a new composite entity to this part.
    CKSEntity AddComposite(const std::wstring *pcsName = NULL,
                           const CKEntityAttrib *pAttrib = NULL,
                           const CKSMatrix *pMatrix = NULL,
                           CKSLevel *pLevel = NULL,
                           CKSAnim *pAnim = NULL);

   // @cmember Add a new Conic entity to this part using Quadratic data coefficients
   CKSEntity AddConic(const CKSCoord &rStart,const CKSCoord &rEnd,
                      const std::vector<double> &adDataQuadratic,
                      const CKEntityAttrib *pAttrib = NULL,
                      const CKSMatrix *pMatrix = NULL,
                      CKSLevel *pLevel = NULL,
                      CKSAnim *pAnim = NULL);

    // @cmember Add a new Conic entity to this part using Parametric data coefficients
    CKSEntity AddConic(ConType nType, double dStartParam, double dEndParam,
                       const std::vector<double> &adDataParametric,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    CKSEntity AddCoordinateDim(CKS::Location* pOriginLoc,
                               CKS::Location* pCoordinateLoc,
                               CKS::Location *pTextLoc,
                               int nDisplayType,
                               bool b3D = false,
                               double dShrink = 1.0,
                               bool bMultiline = false,
                               bool bBrackets = true,
                               bool bAxisLabel = false,
                               bool bDisplayUnits = false,
                               bool bAddPoint = false,
                               const CKSDimensionOptions* pOptions = NULL,
                               const CKSMatrix* pMatrix = NULL,
                               CKSLevel* pLevel = NULL,
                               CKSAnim* pAnim = NULL);

    // @cmember Add a new CPlane to this part
    ULONG AddCPlane(const CKSMatrix &rMatrix, const std::wstring &csName);

    // @cmember Add a new CPlane to this part
    ULONG AddCPlane(CKSEntity &rPlane, const std::wstring &csName);

    // @cmember Add a new Cutting Entity to this part
    CKSEntity AddCuttingEntity(CuttingType nType, const CKSMatrixArray &aMatrix,
                               int nViewport = 0, float fSliceTol = 0);

    // @cmember Add a new Cutting Plane Line to this part
    CKSEntity AddCuttingPlaneLine(const CKSCoordArray &aCoords,
                                  const CKS::LocationArray &aLocations,
                                  const std::vector<UINT> &aucUses,
                                  const std::wstring &csLabel,
                                  UCHAR ucStandard,
                                  UCHAR ucProjType,
                                  UCHAR ucTextPlacement,
                                  double dArrowHeadLength,
                                  double dArrowLeaderLength,
                                  bool bFilledArrowHead,
                                  const CKSDetailFormat &rFormat,
                                  const CKEntityAttrib &LineAtt,
                                  const CKEntityAttrib &ElbowAtt,
                                  const CKEntityAttrib &ArrowAtt,
                                  const CKEntityAttrib &TextAtt,
                                  const CKSMatrix &rMatrix,
                                  CKSLevel *pLevel = NULL,
                                  CKSEntity *pSectionView = NULL);

    // @cmember Add a new Datum to this part
    CKSEntity AddDatum(const std::wstring &csText,
                       CKS::GDT::Attachment nAttach,
                       CKS::Location *pSymbolLoc, CKS::Location *pLeaderLoc,
                       CKS::GDT::Standard nStandard, int nDispView = 0,
                       const CKSDetailOptions *pOptions = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    DEPRECATED_IN_12_5("version that takes in a CKSDetailOptions")
    CKSEntity AddDatum(const std::wstring &csText,
                       CKS::GDT::Attachment nAttach,
                       CKS::Location *pSymbolLoc, CKS::Location *pLeaderLoc,
                       CKS::GDT::Standard nStandard, int nDispView = 0,
                       const CKSDetailFormat *pFormat = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new Datum Target to this part
    CKSEntity AddDatumTarget(const std::wstring &csSize,
                             const std::wstring &csDatum,
                             CKS::GDT::DTLeader nLeaderType,
                             CKS::GDT::TargetPoint nTargetPoint,
                             bool bOutside,
                             bool bMovable,
                             CKS::Location *pSymbolLoc,
                             CKS::Location *pLeaderLoc,
                             int nDispView = 0,
                             const CKSDetailOptions *pOptions = NULL,
                             const CKSMatrix *pMatrix = NULL,
                             CKSLevel *pLevel = NULL,
                             CKSAnim *pAnim = NULL);

    // @cmember Add a new Detail Call-out to this part
    CKSDrawInst AddDetailCallout(CKSDrawInst &DefInstance,
                                 CKS::CalloutRegionType ucRegionType,
                                 CKS::Location *locDefArcCenter,
                                 CKS::Location *locEdgePosition,
                                 CKS::Location *locArcLabel,
                                 const CKSCoord &ckscBase,
                                 CKString cksArcLabel,
                                 CKString cksCalloutNote,
                                 double dScale,
                                 bool bScaleFromModel,
                                 bool bShowScale,
                                 bool bDrawBorder = true,
                                 bool bCalloutTaggedGeometry = false,
                                 const CKSDetailOptions *pAttrib = NULL,
                                 CKSLevel *pLevel = NULL,
                                 CKSAnim *pAnim = NULL);

    DEPRECATED_IN_13("version with CKS::CalloutRegionType")
    CKSDrawInst AddDetailCallout(const CKSCoord &ckscBase,
                                 CKSDrawInst &DefInstance,
                                 CKS::Location *locDefArcCenter,
                                 const double dDefArcRadius,
                                 CKS::Location *locArcLabel,
                                 CKString cksArcLabel,
                                 CKString cksCalloutNote,
                                 double dScale,
                                 bool bScaleFromModel,
                                 bool bShowScale,
                                 bool bDrawBorder = true,
                                 const CKSDetailFormat *pAttrib = NULL,
                                 CKSLevel *pLevel = NULL,
                                 CKSAnim *pAnim = NULL,
                                 bool bCalloutTaggedGeometry = false,
                                 const CKSDetailOptions *pAttribLabel = NULL);

    // @cmember Add a new DispView to this part
    ULONG AddDispView(const CKSMatrix &rMatrix, const std::wstring &csName);

    // @cmember Add a new DispView to this part
    ULONG AddDispView(CKSEntity &rDispView, const std::wstring &csName);

    // @cmember Add a new Ellipse entity to the part
    CKSEntity AddEllipse(double &dMajorAxis, double &dMinorAxis, double &dAxisAngle,
                         CKSCoord &ckcCenter, const CKEntityAttrib *pAttrib = NULL,
                         const CKSMatrix *pMatrix = NULL,
                         CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new generic dimension to this part.
    CKSEntity AddGenericDim(const CKString &cksText,
                            CKSRefLineArray *aLines = NULL,
                            CKSRefArcArray *pArcs = NULL,
                            CKSArrowheadArray *pArrows = NULL,
                            CKS::Location *pLoc = NULL,
                            int nDispView = 0,
                            const CKSDetailOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

    // @cmember Add a new GeoTol (Geometric Dimension and Tolerance)
    // symbol to this part.
    CKSEntity AddGeoTol(CKSFeatureControlFrame *pFrame1,
                        CKSFeatureControlFrame *pFrame2 = NULL,
                        CKSFeatureControlFrame *pFrame3 = NULL,
                        CKS::GDT::Standard nStandard = CKS::GDT::Other,
                        CKS::Location *pSymbolLoc = NULL,
                        CKS::LocationArray *paLocations = NULL,
                        bool bBoundary = false, bool bAllAround = false,
                        const std::wstring *pcsOtherText = NULL,
                        const std::wstring *pcsBetweenFirst = NULL,
                        const std::wstring *pcsBetweenSecond = NULL,
                        CKSEntity *pDatum = NULL,
                        CKSLeaderType nLeaderType = CK_NoLeader,
                        CKSOrientType nOrientation = CK_OrientHorizontal,
                        CKSStackingAlign nAlign = CK_NoStacking,
                        CKS::ArrowDirection nArrowDir = CKS::ArrowsAuto,
                        int nDispView = 0,
                        const CKSDetailOptions *pOptions = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new CrossHatch to this part.
    CKSEntity AddHatch(const CKSRefLineArray &raSolidLines,
                       const CKSRefLineArray &raDashLines,
                       const CKSRefLineArray &raCenterLines,
                       const CKSRefLineArray &raPhantomLines,
                       CKSHatchPattern &pPattern,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new CrossHatch to this part
    CKSEntity AddHatch(const CKSEntityArray &aBorderEnts,
                       const CKSCoordArray &aPoints,
                       CKSHatchPattern &pPattern, double dAngle,
                       double dXScale, double dYScale, double dXOffset,
                       double dYOffset, double dBoundaryOffset,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Find a pattern with the given pattern data, creating it if it
    // doesn't exist.
    CKSHatchPattern FindPattern(const std::vector<int> &anData,
                                const std::vector<double> &adData,
                                const std::vector<std::wstring> &acsData);

    // @cmember Find a pattern with the given old style pattern data,
    // creating it if it doesn't exist.
    CKSHatchPattern FindPattern(const std::vector<UCHAR> &aucPatternDef,
                                bool bDouble, double dAngle,
                                const std::wstring &csName);

    // @cmember Find a pattern with the given old style pattern number,
    // creating it if it doesn't exist.
    CKSHatchPattern FindPattern(UCHAR ucPattern, const std::wstring &csName);

    // @cmember Find a pattern with the given name, if any.
    CKSHatchPattern FindPattern(const std::wstring &csName);

    // @cmember Load patterns from the given file.
    int LoadPatterns(const std::wstring &csFileName,
                     CKSHatchPatternArray &aPatterns);

    // @cmember Get a list of all the hatch patterns.
    int GetHatchPatternList(CKSHatchPatternArray &apPatterns);

    // @cmember Get the data for a given hatch pattern.
    int GetHatchPatternData(const CKSHatchPattern     &pPattern,
                            std::vector<int>          &anData,
                            std::vector<double>       &adData,
                            std::vector<std::wstring> &acsData);

    // @cmember Get a list of all the hatches using a given pattern.
    int GetHatchPatternHatchList(const CKSHatchPattern &pPattern,
                                 CKSEntityArray &aHatches);

    // @cmember Delete a hatch pattern, only works if it isn't in use.
    int DeleteHatchPattern(CKSHatchPattern &pPattern);

    // @cmember Add a new Table to this part.
    CKSEntity AddHoleTable(bool bDiameterDisplay = true,
                           bool bGroupAscending = true,
                           double dRowSpacing = 1.0, double dColSpacing = 1.0,
                           UCHAR nFirstSort = 0, bool bFirstAscending = true,
                           UCHAR nSecondSort = 1, bool bSecondAscending = true,
                           bool bTopDown = true, double dLabelAngle = 135.0,
                           CKS::Location *pTableLoc = NULL,
                           int nDispView = 0,
                           const CKSDetailUnits *pUnitsOptions = NULL,
                           const CKSDetailFormat *pBodyFormat = NULL,
                           const CKSDetailFormat *pHeaderFormat = NULL,
                           CKEntityAttrib *pGridAttrib = NULL,
                           const CKSMatrix *pMatrix = NULL,
                           CKSLevel *pLevel = NULL,
                           CKSAnim *pAnim = NULL);

    // @cmember Add a new instance to a layout in this part.
    CKSDrawInst AddInstance(const CKSCoord &ckscBase,
                            double dScale, double dRotation,
                            double dWidth, double dHeight,
                            bool bFrozen, bool bDrawBorder,
                            const CKS::Rendering ucRender,
                            const CKSLevelArray &aLevels,
                            const CKEntityAttrib &rAttrib,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL,
                            CKS::ThreadRendering ucThreadRender = CKS::ThreadRenderSimple,
                            bool bPHLV5Display = true,
                            bool bDisplayModelDetailEnts = false,
                            CKS::WireRendering ucWireRender = CKS::WireStandard);

    CKSDrawInst AddInstance(const CKSCoord &ckscBase,
                            double dScale, double dRotation,
                            double dWidth, double dHeight,
                            bool bFrozen, bool bDrawBorder,
                            const CKS::Rendering ucRender,
                            const CKSLevelArray &aLevels,
                            const CKEntityAttrib &rAttrib,
                            const CKSMatrix *pMatrix,
                            CKSLevel *pLevel,
                            CKSAnim *pAnim,
                            CKS::ThreadRendering ucThreadRender,
                            int nPHLV5Display,
                            bool bDisplayModelDetailEnts,
                            CKS::WireRendering ucWireRender);

    // @cmember Add a new Label to this part.
    CKSEntity AddLabel(const CKString &cksText,
                       const CKSLeaderArray &aLeaders,
                       CKS::LocationArray *paLocations = NULL,
                       CKS::Location *pTextLoc = NULL,
                       int nDispView = 0,
                       const CKSDetailOptions *pOptions = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new layout to this part
    CKSLayout AddLayout(const std::wstring &csName,
                        const std::wstring &csDescription, double dXsize,
                        double dYsize, double dScale, bool bBorder,
                        bool bInches = true,
                        CKS::PaperSize ucBasePaperSize = CKS::PaperKeyIn);

    // @cmember Add a new LeaderWitness line to this part.
    CKSEntity AddLdrWit(const CKSLeader &rLeader,
                        bool bDisplayArrowhead,
                        int nDispView = 0,
                        const CKSDetailOptions *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new LeaderWitness line to this part.
    CKSEntity AddLdrWitArc(const CKSLeaderArc &rLeader,
                           int nDisplayArrowhead,
                           int nDispView = 0,
                           const CKSDetailOptions *pAttrib = NULL,
                           const CKSMatrix *pMatrix = NULL,
                           CKSLevel *pLevel = NULL,
                           CKSAnim *pAnim = NULL);

    // @cmember Add a new light to this part.
    CKSEntity AddLight(const CKSMatrix &rMatrix, CKSCoord &cksTarget,
     					int Type, int Outer_units, int Inner_units,
						double Outer_size, double Inner_size, double Concentration,
						double FRed, double FGreen, double FBlue,
                        CKSLevel *pLevel);

    // @cmember Add a new line to this part.
    CKSEntity AddLine(double dXStart, double dYStart, double dZStart,
                      double dXEnd, double dYEnd, double dZEnd,
                      const CKEntityAttrib *pAttrib = NULL,
                      const CKSMatrix *pMatrix = NULL,
                      CKSLevel *pLevel = NULL,
                      CKSAnim *pAnim = NULL);

    // @cmember Add a new line to this part.
    CKSEntity AddLine(const CKSCoord &ckscFirst, const CKSCoord &ckscSecond,
                      const CKEntityAttrib *pAttrib = NULL,
                      const CKSMatrix *pMatrix = NULL,
                      CKSLevel *pLevel = NULL,
                      CKSAnim *pAnim = NULL);

    // @cmember Add a new linear dimension to the part
    CKSEntity AddLinearDim(double dAxisAngle,
                           CKSRefLine *pRefLine,
                           CKS::Location *pFirstLoc = NULL,
                           CKS::Location *pSecondLoc = NULL,
                           CKS::Location *pTextLoc = NULL,
                           const CKSDimensionOptions *pLinDimOptions = NULL,
                           int nDispView = 0,
                           CKSLevel *pLevel = NULL,
                           const CKSMatrix *pMatrix = NULL,
                           CKSAnim *pAnim = NULL);

    // @cmember Add a new Note to this part.
    CKSEntity AddNote(const CKString &cksText,
                      CKS::Location *pTextLoc = NULL,
                      int nDispView = 0, bool bFileName = false,
                      bool bLinkToFile = false,
                      const CKSDetailOptions *pOptions = NULL,
                      const CKSMatrix *pMatrix = NULL,
                      CKSLevel *pLevel = NULL,
                      CKSAnim *pAnim = NULL);

    // @cmember Add a new NURBSpline entity to this part using Control Points
    CKSEntity AddNURBSpline(int nDegree, bool bRational, bool bClosed,
                            const std::vector<double> &adKnots,
                            const CKSCoordArray &ackscControlPoints,
                            const std::vector<double> &adWeights,
                            const CKEntityAttrib *pAttrib = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

     // @cmember Add a new NURBSpline entity to this part using Fit Points
     CKSEntity AddNURBSpline(int nDegree, bool bRational, bool bClosed,
                            const CKSCoordArray &ackcFits,
                            const CKEntityAttrib *pAttrib = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

    // @cmember Create an OLE Entity also link/embedd an OLE client Item into a part
    CKSEntity AddOleEntity(bool bPaste, double dWidth, double dHeight,
                           CKS::Location *pLocStart, CKS::Location *pLocEnd,
                           UCHAR ucHorAlign, UCHAR ucVerAlign,
                           int nDispView = 0,
                           const CKEntityAttrib *pAttrib = NULL,
                           const CKSMatrix *pMatrix = NULL,
                           CKSLevel *pLevel = NULL,
                           CKSAnim *pAnim = NULL);

    // @cmember Add a new Part Reference to this part.
    CKSEntity AddPartReference(const std::wstring &csFile,
                               const std::wstring &csPart,
                               const std::wstring *pcsName = NULL,
                               const std::wstring *pcsLevelSet = NULL,
                               CKS::FileType nType = CKS::FileDesignFile,
                               bool bAllowsRelativePaths = true,
                               bool bHidden = false, bool bSuppressed = false,
                               bool bLightweight = false,
                               CKSEntity *pInsertionPlane = NULL,
                               bool bKeepPlane = true,
                               CKS::Location *pPositionLoc = NULL,
                               bool bKeepPositionLoc = true,
                               CKS::Location *pRotationLoc = NULL,
                               bool bKeepRotationLoc = true,
                               double dFixedRotation = 0.0,
                               std::vector<std::wstring> *pacsStandardProperties = NULL,
                               std::vector<std::wstring> *pacsUserProperties = NULL,
                               bool bDetailEntities = false,
                               const CKSMatrix *pMatrix = NULL,
                               CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSMatrix &rMatrix,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSCoordArray &aPoints,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(CKS::LocationArray &apLocations,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSEntity &pEntity1, const CKSEntity &pEntity2,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSEntity &pEntity, int nSeg = 0,
                       double dParam = 0.0, double dOffset = 0.0,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSEntity &pEntity, bool bStart,
                       CKS::Location *pLocation,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSEntity &pEntity1, const CKSEntity &pEntity2,
                       bool bLineStart1, bool bLineStart2,
                       CKS::Location *pLoc,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new plane to this part
    CKSEntity AddPlane(const CKSEntity &pEntity,
                       const CKEntityAttrib *pAttrib = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new pocket or cut feature to this part.
    int AddPocketFeature(CKSBody *Ent2BCut, CKSBody *pSheetBody,
                         CKSFace *pForwardFace, CKSFace *pBackFace,
                         const CKSCoord &ForwardPoint,
                         const CKSCoord &BackwardPoint,
                         int cut_direction, int draft_opt, int convex_opt,
                         int forward_condition, int backward_condition,
                         int cut_outside, int vecopt, double forward_distance,
                         double backward_distance, double draft_angle,
						 CKCoord *rPoint, CKCoord *rVec);

    // @cmember Add a new point to this part.
    CKSEntity AddPoint(double dX, double dY, double dZ,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new point to this part.
    CKSEntity AddPoint(const CKSCoord &rCoord,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new point projected on curve to this part.
    CKSEntity AddPointProjectCurve(const CKSEntityArray &aEntities,
                                   const CKSCoord &ckcPoint,
                                   const CKEntityAttrib *pAttrib = NULL,
                                   CKSLevel *pLevel = NULL,
                                   CKSAnim *pAnim = NULL);

    // @cmember Adds new points to this part at the nodes of the given splines
    CKSEntity AddPointsAtSplineNodes(CKSEntityArray &aPoints,
                                     const CKSEntityArray &aSplines,
                                     const CKEntityAttrib *pAttrib = NULL,
                                     const CKSMatrix *pMatrix = NULL,
                                     CKSLevel *pLevel = NULL, 
                                     CKSAnim *pAnim = NULL);

    // @cmember Add a new polyline to this part.
    CKSEntity AddPolyline(const CKSCoordArray &aptPoints,
                          bool bClosed, bool bFilled,
                          const CKEntityAttrib *pAttrib = NULL,
                          const CKSMatrix *pMatrix = NULL,
                          CKSLevel *pLevel = NULL,
                          CKSAnim *pAnim = NULL);

    // @cmember Add a new protrude(boss) feature to this part
    int AddProtrudeFeature(CKSBody *pProtBody, CKSBody *pSheetBody,
                           CKSFace *pForwardFace, CKSFace *pBackwardFace,
                           const CKSCoord &ForwardPoint,
                           const CKSCoord &BackwardPoint,
                           int protrude_direction, int draft_opt,
                           int convex_opt, int forward_condition,
                           int backward_condition, int vecopt,
                           double forward_distance,
                           double backward_distance, double draft_angle);

    // @cmember Add a new section view to this part.
    CKSEntity AddSectionView(const CKSDrawInst& rPrimaryInst,
                             const CKSEntity& rCuttingPlaneLine,
                             const CKSEntityArray& aSectionedSolids,
                             const CKSEntityArray& aOtherSolids,
                             const CKSMatrix &rViewMatrix,
                             const CKSCoord &rCenter,
                             const std::wstring &csViewText,
                             bool bProjected,
                             double dScale,
                             bool bDrawScaleNote,
                             bool bDrawHLR,
                             bool bIsPartialView,
                             bool bDrawHatches,
                             CKSHatchPattern &pHatchPattern, double dAngle,
                             double dXScale, double dYScale, double dXOffset,
                             double dYOffset, double dBoundaryOffset,
                             bool bFlatten,
                             const CKEntityAttrib &VisAttr,
                             const CKEntityAttrib &ExtAttr,
                             const CKEntityAttrib &HatchAttr,
                             const CKSMatrix &rMatrix,
                             const CKSLevel &rLevel,
                             bool bLabelView=true,
                             bool m_bTangentLines=true,
                             CKSDetailFormat *pNote1Format = NULL,
                             CKSDetailFormat *pNote2Format = NULL,
                             CKSDetailFormat *pNote3Format = NULL);

	// @cmember Add a new spiral spline to this part
	CKSEntity AddSpiral(const CKSCoord &rCenterCoord,
						const CKSCoord &rStartCoord,
						double dWidth,
						double dTurns,
						bool bClockwise = true,
						const CKEntityAttrib *pAttrib = NULL,
						const CKSMatrix *pMatrix = NULL,
						CKSLevel *pLevel = NULL,
						CKSAnim *pAnim = NULL);

    // @cmember Add a new spline to this part, using coefficients
    CKSEntity AddSpline(bool b3D, bool bClosed,
                        const std::vector<double> &adData,
                        const CKEntityAttrib *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new spline to this part, using node points
    CKSEntity AddSpline(bool b3D, bool bClosed, bool bStartVector,
                        bool bEndVector, const CKSCoord &ckscStartVec,
                        const CKSCoord &ckscEndVec,
                        const CKSCoordArray &ackscPoints,
                        const CKEntityAttrib *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new surface texture symbol to this part.
    CKSEntity AddSurfaceTexture(CKS::Surface::Type ucType,
                        CKS::Surface::LayDirection ucDirection,
                        CKS::Surface::Leader ucLdrType,
                        CKS::Location *pTextLoc = NULL,
                        double dAngle = 0.0,
                        const std::wstring *pcsMaxRough = NULL,
                        const std::wstring *pcspMinRough = NULL,
                        const std::wstring *pcsCutoff = NULL,
                        const std::wstring *pcsMaxRoughWidth = NULL,
                        const std::wstring *pcsWaveHt = NULL,
                        const std::wstring *pcsWaveHtSpacing = NULL,
                        const std::wstring *pcsMatlRemoved = NULL,
                        int nDispView = 0,
                        const CKSDetailOptions *pOptions = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new surface texture symbol to this part.
    CKSEntity AddSurfaceTextureSymbol(CKS::Surface::Type ucType,
                        CKS::Surface::LayDirection ucDirection,
                        CKS::Surface::Leader ucLdrType,
                        CKS::Location *pTextLoc = NULL,
                        double dAngle = 0.0,
                        const bool bAllAround = false,
                        const std::wstring *pcsMaxRough = NULL,
                        const std::wstring *pcspMinRough = NULL,
                        const std::wstring *pcsCutoff = NULL,
                        const std::wstring *pcsMaxRoughWidth = NULL,
                        const std::wstring *pcsWaveHt = NULL,
                        const std::wstring *pcsWaveHtSpacing = NULL,
                        const std::wstring *pcsMatlRemoved = NULL,
                        const bool bShowHorizontal = false,
                        int nDispView = 0,
                        const CKSDetailOptions *pOptions = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new surface texture symbol to this part.
    CKSEntity AddSurfaceTextureSymbolEx(CKS::Surface::Type ucType,	// <K3D-11073KXL>
                        CKS::Surface::LayDirection ucDirection,
                        CKS::Surface::Leader ucLdrType,
                        CKS::Location *pTextLoc = NULL,
                        double dAngle = 0.0,
                        const bool bAllAround = false,
                        const std::wstring *pcsMaxRough = NULL,
                        const std::wstring *pcspMinRough = NULL,
                        const std::wstring *pcsCutoff = NULL,
                        const std::wstring *pcsMaxRoughWidth = NULL,
                        const std::wstring *pcsWaveHt = NULL,
                        const std::wstring *pcsWaveHtSpacing = NULL,
                        const std::wstring *pcsMatlRemoved = NULL,
                        const bool bJIS2 = false,
                        const std::wstring *pcsPreMark = NULL,
                        const std::wstring *pcsPostMark = NULL,
                        const bool bShowHorizontal = false,
                        int nDispView = 0,
                        const CKSDetailOptions *pOptions = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new optimized shell to this part.
    CKSEntity AddOptimizedShell(const CKSCoordArray &ackcPoints,
                                const std::vector<int> &anFaceList,
                                const CKSCoordArray *packcNormals,
                                const CKEntityAttrib *pAttrib = NULL,
                                const CKSMatrix *pMatrix = NULL,
                                CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Add a new weld symbol to this part.
    CKSEntity AddWeldSymbol(double dReferenceLineLength,
                            double dReferenceLineSpacing,
                            int nDashPlacement,
                            bool bLeftArrow,
                            int nArrowStyle,
                            bool bBreakLeader,
                            CKS::Location *pTextLoc = NULL,
                            CKS::Location *pArrowLoc = NULL,
                            int nDispView = 0,
                            const CKSDetailOptions *pOptions = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL,
                            CKSAnim *pAnim = NULL);

    // @cmember Add a new weld symbol to this part.
    int AddWeldSymbolRefLine(CKSEntity &cksWeld,
                             size_t nRefLineNum,
                             std::vector<ptrdiff_t> &anWSymbol,
                             CStringArray &acsFields,
                             bool bTail,
                             bool bFieldUp,
                             bool bFieldDown,
                             bool bAllAround,
                             bool bConsumableInsert,
                             bool bBackingSpacer,
                             LPCTSTR lpszTailTextTop,
                             LPCTSTR lpszTailTextMiddle,
                             LPCTSTR lpszTailTextBottom,
                             CKS::Location *pBreakLoc = NULL);

    // @cmember Add a new shell to this part.
    CKSEntity AddShell(const CKSCoordArray &ackcPoints,
                       const std::vector<int> &anFaceList,
                       const CKSCoordArray *packcNormals,
                       const CKEntityAttrib *pAttrib = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Creates a new sheet body with a boundary curve surface.
    CKSErrors CreateBoundaryCurveSurfSheet(CKSBody *&pSheetBody, 
                                           const CKSEntityArray &aGenerator,
                                           const CKSMatrix *pMatrix=NULL);


    // @cmember Creates a new sheet body with a ruled surface using RuledSurfaceExactMake
    // or RuledSurfaceApproxMake
    CKSErrors CreateRuledSurfSheet(CKSBody *&pRuledSheetBody, int nFitMethod, int nRuleMethod,
                                   CKSEntity &pWire1, CKSEntity &pWire2,
                                   CKSCoord &Pnt, double dTol, int nPatches,
                                   const CKSMatrix *pMatrix=NULL);

    // @cmember Creates a new sheet body of revolution.
    CKSErrors CreateSurfOfRevSheet(CKSBody *&pSheetBody, const CKSEntityArray &aGenerator,
                                   const CKSCoord &pnt, const CKSCoord &vec,
                                   double dStartAngle, double dEndAngle, bool bConvertToSpline,
                                   const CKSMatrix *pMatrix=NULL);

    // @cmember Creates a new sheet body with a tabulated cylinder surface
    CKSErrors CreateTabcylSurfSheet(CKSBody *&pSheetBody,
                                    const CKSEntityArray &aGenerator,
                                    const CKSCoord &vec, double dStart, 
                                    double dDistance, bool bConvertToSpline, 
                                    const CKSMatrix *pMatrix=NULL);

    // @cmember Creates a new sheet body with a constant offset surface
    CKSErrors CreateConstantOffsetSurfSheet(CKSBodyArray &acksbConstantOffsetSurfSheetBody,
                                            const CKSFaceArray &aCKSFaces, double dOffsetValue,
                                            const CKSMatrix *pMatrix=NULL);

    // @cmember Creates a new sheet body with a constant offset surface
    CKSErrors CreateConstantOffsetSurfSheet(CKSEntityArray &aFaces, double dOffsetValue, 
                                            CKSEntityArray &aOffsetSheets,
                                            const CKEntityAttrib *pAttrib = nullptr,
                                            CKSLevel *pLevel = nullptr);

    // @cmember Creates a new General Curve Surface sheet
    CKSErrors CreateGenCurveSurfSheet(CKSBody *&pGenCrvSurfSheetBody,
                                      const CKSEntityArray &aEnt1,
                                      double dCurveTol, int nPatches, int nFitMethod, 
                                      int nNumCrvs, const CKSMatrix *pMatrix=NULL);

    // @cmember Creates a new edge curve surface sheet
    CKSErrors CreateEdgeCurveSurfSheet(CKSBody *&pEdgeCrvSurfSheetBody, 
                                       const CKSEntityArray &aGenerators,
                                       double dCurveTol, const CKSMatrix *pMatrix=NULL);

    // @cmember Creates new parting surface sheets
    CKSErrors CreatePartingSurfSheet(CKSBodyArray &acksbSheetBodies, 
                                     double dAngle, double dLength,
                                     int nDraftType, double dCurveFitTol,
                                     const CKSEntityArray &aEnt, 
                                     std::vector<unsigned int> &aunFlags, 
                                     CKSCoord ckcVec,
                                     const CKSMatrix *pMatrix=NULL);

    // @cmember Add a new Table to this part.
    CKSEntity AddTable(const CKStringArray &lcsHeaders,
                       const std::vector<double> &adWidths,
                       double dRowSpacing = 1.0, double dColSpacing = 1.0,
                       const std::vector<int> *pWidthBehaviours = NULL,
                       CKS::Location *pTableLoc = NULL,
                       int nDispView = 0,
                       const CKSDetailFormat *pOptions = NULL,
                       const CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSAnim *pAnim = NULL);

    // @cmember Add a new target to this part.
    CKSEntity AddTarget(double dOuterDia, CKS::TargetPointType nPointType,
                        CKS::Location *pLocation = NULL,
                        int nDispView = 0,
                        const CKEntityAttrib *pAttrib = NULL,
                        const CKSMatrix *pMatrix = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

    // @cmember Add a new Vector to this part using the display scale and a matrix
    CKSEntity AddVector(const double dDisplayScale,
                        const CKSMatrix *pMatrix = NULL,
                        const CKEntityAttrib *pAttrib = NULL,
                        CKSLevel *pLevel = NULL,
                        CKSAnim *pAnim = NULL);

     
    // @cmember Reverses the normals of faces belonging to a sheet body
    CKSErrors ChangeSheetBodiesNormals(CKSBodyArray &aBodies);

    // @cmember Fixes incorrect solid face normals
    CKSErrors FixSolidNormals(CKSBodyArray &aBodies);

    // @cmember Repairs normals in a non-manifold 
    CKSErrors RepairNonMainfold(CKSBody *pNonManifBody, CKSBodyArray &aNewBodies);

    // @cmember Tolerizes the bodies' topology
    CKSErrors TolerizeBodies(CKSBodyArray &aBodies);

    // @cmember Cleans the bodies' topology by removing redundant faces.
    CKSErrors MergeRedundantFaces(CKSBodyArray &aBodies, int &nNumFacesRemoved);

    // @cmember Cleans the bodies' topology by removing selective redundant faces.
    CKSErrors MergeRedundantFaces(CKSBodyArray &aBodies, CKSFaceArray &aFacesToExclude, int &nNumFacesRemoved);

    // @cmember Simplifies the bodies' topology by replacing spline surfaces and 
    // edges with analytical surfaces edges.
    CKSErrors SimplifySplineFacesAndEdges(CKSBodyArray &aBodies, bool bSplineEdges, 
                                         bool bSplineFaces, bool bProceduralFaces);

    // @cmember Recreates any bad curves found in the body.
    CKSErrors RegenerateParamCurves(CKSBodyArray &aBodies, bool bRegeneratedCurves);

    // @cmember Splits the periodic spline faces in the selected body/bodies.
    CKSErrors SplitPeriodicSplineFaces(CKSBodyArray &aBodies, bool bSplitFaces);

    // @cmember Calculate a specific DDE/Folder
    int CalculateDDE(const std::wstring &csPath);

    // @cmember Get selset entity list
    int GetSelSetEnts(const std::wstring &csPath, CKSEntityArray& aEnts);

    // @cmember Add entities to a specific selset
    int AddEntsToSelSet(const std::wstring &csPath, const CKSEntityArray &aEnts, bool bCreate);
    
    // @cmember Add entities to a specific selset
    int RemoveEntsFromSelSet(const std::wstring &csPath, const CKSEntityArray &aEnts);

    // @cmember Delete selset
    int DeleteSelSet(const std::wstring &csPath);

    // @cmember Delete selset folder
    int DeleteSelSetFolder(const std::wstring &csPath, bool bClearChilds = false);

    // @cmember Create a folder in specified path
    int CreateSelSetFolder(const std::wstring &csPath);

    // @cmember Create selset in specified path
    int CreateSelSet(const std::wstring &csPath, bool bCreateFolder);

    // @cmember Set No Section flag inside pEntity solid
    int SetSolidNotSectionable(CKSEntity pEntity, bool bNotSectionable);

    // @cmember Get No Section status for pEntity solid
    int GetSolidNotSectionable(CKSEntity pEntity, bool& bIsNotSectionable);

    // @cmember Create a vector given a line
    CKSEntity CreateVectorFromLine(CKSEntity &pEntity, double dParamVal,
                                   double dDisplayScale,
                                   const CKEntityAttrib *pAttrib,
                                   CKSLevel *pLevel, CKSAnim *pAnim);

    // @cmember Create a vector from the cross product of two other vectors
    CKSEntity CrossProductVectors(CKSEntity &cksVec1, CKSEntity &cksVec2,
                                  double dDisplayScale,
                                  const CKEntityAttrib *pAttrib,
                                  CKSLevel *pLevel, CKSAnim *pAnim);

    // @cmember Create a vector based on the normal to a curve
    int CurveNormalVectors(CKSEntity &pcksCurve, int iMenu, int nPts,
                           const CKSCoord &ckcSelectedPoint, double dParamVal,
                           double dDisplayScale, const CKEntityAttrib *pAttrib,
                           CKSLevel *pLevel, CKSAnim *pAnim,
                           CKSEntityArray &cksVectors);

    // @cmember Extract Visible and Hidden lines from a set of entities
    CKSErrors ExtractHiddenLines(const CKSEntityArray &aSolids, 
                                 const CKSMatrix *pViewMatrix,
                                 bool bGetHiddenCurves, 
                                 bool bGetObscuredCurves, 
                                 bool bGetTangentCurves, bool bFlatten, 
                                 const CKEntityAttrib &rVisibleAttr,
                                 CKSLevel *pVisibleSLevel,
                                 const CKEntityAttrib &rExteriorAttr,
                                 CKSLevel *pExteriorSLevel,
                                 const CKEntityAttrib &rVisibleTanAttr,
                                 CKSLevel *pVisibleTanSLevel,
                                 const CKEntityAttrib &rHiddenAttr,
                                 CKSLevel *pHiddenSLevel,
                                 const CKEntityAttrib &rHiddenTanAttr,
                                 CKSLevel *pHiddenTanSLevel,
                                 CKSEntityArray &aSolidCurves,
                                 CKSEntityArray &aDashedCurves,
                                 CKSEntityArray &aExteriorCurves,
                                 CKSEntityArray &aVisibleTangentCurves,
                                 CKSEntityArray &aHiddenTangentCurves);

    // @cmember Extract Visible and Hidden lines from a set of entities
    CKSErrors ExtractHiddenLines(const CKSEntityArray &aSolids, 
                                 const CKSMatrix *pViewMatrix,
                                 bool bGetHiddenCurves, 
                                 bool bGetObscuredCurves, 
                                 bool bGetTangentCurves, bool bFlatten, 
                                 const CKEntityAttrib &rVisibleAttr,
                                 CKSLevel *pVisibleSLevel,
                                 const CKEntityAttrib &rExteriorAttr,
                                 CKSLevel *pExteriorSLevel,
                                 const CKEntityAttrib &rVisibleTanAttr,
                                 CKSLevel *pVisibleTanSLevel,
                                 const CKEntityAttrib &rHiddenAttr,
                                 CKSLevel *pHiddenSLevel,
                                 const CKEntityAttrib &rHiddenTanAttr,
                                 CKSLevel *pHiddenTanSLevel,
                                 CKSEntityArray &aSolidCurves,
                                 CKSEntityArray &aDashedCurves,
                                 CKSEntityArray &aExteriorCurves,
                                 CKSEntityArray &aVisibleTangentCurves,
                                 CKSEntityArray &aHiddenTangentCurves,
                                 CKSEntityArray *paOrigSolidCurves,
                                 CKSEntityArray *paOrigDashedCurves = nullptr,
                                 CKSEntityArray *paOrigExteriorCurves = nullptr,
                                 CKSEntityArray *paOrigVisibleTangentCurves = nullptr,
                                 CKSEntityArray *paOrigHiddenTangentCurves = nullptr);

    // @cmember Create a vector based on the normal to a plane
    CKSEntity PlaneNormalVectors(const CKSMatrix &mat, double dDisplayScale,
                                 const CKEntityAttrib *pAttrib,
                                 CKSLevel *pLevel, CKSAnim *pAnim);

    // @cmember Create a vector based on the intersection of two planes
    CKSEntity PlanePlaneIntersectionVectors(const CKSMatrix &ckPlane1,
                                            const CKSMatrix &ckPlane2,
                                            double dDisplayScale,
                                            const CKEntityAttrib *pAttrib,
                                            CKSLevel *pLevel, CKSAnim *pAnim);

    // @cmember Create a vector based on the tangent to a curve
    int CurveTangentVectors(CKSEntity &pcksCurve, int iMenu, int nPts,
                            const CKSCoord &ckcSelectedPoint, double dParamVal,
                            double dDisplayScale,
                            const CKEntityAttrib *pAttrib, CKSLevel *pLevel,
                            CKSAnim *pAnim, CKSEntityArray &cksVectors);

    // @cmember Create a vector based on two points
    CKSEntity Vector2Points(const CKSCoord &cksCoord1,
                            const CKSCoord &cksCoord2, double dDisplayScale,
                            const CKEntityAttrib *pAttrib, CKSLevel *pLevel,
                            CKSAnim *pAnim);

    // @cmember Create an instance projected from an existing instance
    CKSDrawInst CreateInstanceFromInstance(const CKSDrawInst &pInst,
                                           int nProjectionType,
                                           CKSCoord &ckcPickPoint,
                                           CKSEntity &pEntity,
                                           CKSCoord *ckcInstPos = nullptr,
                                           CKSLevel *pLevel = nullptr,
                                           bool bParallel = true);

    // @cmember Align one instance to another
    int MakeInstancesAligned(const CKSDrawInst  &pFixedInst,
                             CKSDrawInst        &pAlignInst,
                             double             &dAlignAngle,
                             CKSCoord           &ckcBase,
                             CKSCoord           *ckcPlacementPos);

    // @cmember Remove an instance from being aligned with another
    int RemoveFromAlignment(CKSDrawInst &pInst,
                            CKSDrawInst &pRemoveInst);

// @Group Entity Retrieval
    // @cmember Retrieves the next entity in a composite
    int CompositeNextEntity(const CKSEntity &rComposite,
                            const CKSEntity &rCurrent,
                            CKSEntity &rNext);

    // @cmember Retrieves the next copious attached to an entity
    int EntityNextCopious(const CKSEntity &rCurrent,
                          const CKSCopious &rCopious,
                          CKSCopious &pNext) ;

    // @cmember Retrieves the Entity type
    int GetEntityType(const CKSEntity &pEntity, CKMaskTypes &nType);

    // @cmember Retrieves the Value of a dimension and the user value
    // if defined.
    int GetDimensionValues(const CKSEntity &pEntity, CKS::ValueType &rValueType,
                           double &dMeasuredValue, double &dManualValue,
                           CKSDimensionOptions *pOptions = NULL,
                           CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from an angular dimension
    int GetAngularDim(const CKSEntity &pEntity,
                      CKSDimensionOptions *pOptions = NULL,
                      CKSCoord *pTextCoord = NULL,
                      bool *pbInnerAngle = NULL,
                      CKSRefLine *pRlFirst = NULL,
                      CKSRefLine *pRlSecond = NULL,
                      CKSWitness *pWitFirst = NULL,
                      CKSWitness *pWitSecond = NULL,
                      CKSLeaderArc *pLdrFirst = NULL,
                      CKSLeaderArc *pLdrSecond = NULL,
                      CKS::LocationArray *paLoc = NULL,
                      CKS::LocationPtr *pTextLoc = NULL,
                      int *pnDispView = NULL,
                      CKSMatrix *pMatrix = NULL);

    // @cmember Get information about an arc entity.
    int GetArc(const CKSEntity &rArc, const CKSDrawInst *hDrawInst = NULL,
               double *pRad = NULL, double *pStartAng = NULL,
               double *pDeltaAng = NULL, CKEntityAttrib *pAttrib = NULL,
               CKSMatrix *pMatrix = NULL);

     // @cmember Add a new Arc Length Dimension to this part.
    int GetArcLengthDim(const CKSEntity &rEntity,
                        CKSDimensionOptions *pOptions = NULL,
                        CKSCoord         *pTextCoord = NULL,
                        CKSRefArc        *pRefArc = NULL,
                        CKSRefLine       *pRefSpline = NULL,
                        CKSWitness       *pWitFirst = NULL,
                        CKSWitness       *pWitSecond = NULL,
                        CKSLeaderArc     *pLdrFirst = NULL,
                        CKSLeaderArc     *pLdrSecond = NULL,
                        CKSWitnessArc    *pWitArc = NULL,
                        CKS::LocationPtr *pTextLoc = NULL,
                        int              *pnDispView = NULL,
                        CKSMatrix        *pMatrix = NULL);

    // @cmember Gets the generic attributes of any entity.
    int GetAttrib(const CKSEntity &pEntity, CKEntityAttrib &rAttrib,
                  const CKSDrawInst *pDrawInst = NULL);

    // @cmember Gets the attributes of a Text entity
    int GetAttrib(const CKSEntity &rEntity, CKSDetailOptions &rOptions);

    // @cmember Gets the attributes of a Dimension entity
    int GetAttrib(const CKSEntity &rEntity, CKSDimensionOptions &rOptions);

    // @cmember Gets the Ref Control flags of an entity.
    int GetRefControl(const CKSEntity &pEntity, ULONG &ulFlags);

    // @cmember Sets the Ref Control flags of an entity.
    int SetRefControl(CKSEntity &pEntity, ULONG ulFlags);

    // @cmember Gets the data to a Balloon entity.
    int GetBalloon(const CKSEntity &pEntity,
                   CKString *cksPrimaryText = NULL,
                   CKSBalloonType *nBalloonType = NULL,
                   CKSLeaderType *nLeaderType = NULL,
                   double *dDiameterRatio = NULL,
                   CKString *cksSplitText = NULL,
                   CKSStackingAlign *nAlign = NULL,
                   int *nDispView = NULL,
                   CKS::LocationPtr *pBalloonLoc = NULL,
                   CKSLeaderArray *paLeaders = NULL,
                   CKS::LocationArray *paLocations = NULL,
                   CKSDetailOptions *pOptions = NULL,
                   CKSMatrix *pMatrix = NULL);

    // @cmember Gets a Baseline dimension entity.
    int GetBaseLinearDim(const CKSEntity &pEntity,
                         CKSDimensionOptions *pOptions = NULL,
                         CKSCoord *pTextCoord = NULL,
                         CKSCoord *pRefPoint = NULL,
                         double *pdOffsetValue = NULL,
                         UCHAR *pucDispStyle = NULL,
                         CKSWitness *pWitness = NULL,
                         CKSLeader *pFirstLeader = NULL,
                         CKSLeader *pSecondLeader = NULL,
                         CKS::LocationPtr *pLocation = NULL,
                         CKS::LocationPtr *pParentLocation = NULL,
                         CKS::LocationPtr *pTextLocation = NULL,
                         int *pnDispView = NULL,
                         double *pdDimAngle = NULL,
                         bool *pbParent = NULL,
                         CKSEntity *pParent = NULL,
                         CKSMatrix *pMatrix = NULL);

    // @cmember Gets a list of the child baseline dimensions form the given
    // parent
    int GetBaseLinearChildren(const CKSEntity &pEntity,
                              CKSEntityArray &rChildren);

    // @cmember Get information for a bend line entity
    int GetBendLine(const CKSEntity &rBendLine, double &dBendAngle,
                    double &dBendRadius, double &dKFactor);

    // @cmember Retrieves the data from a chamfer dimension
    int GetChamferDim(const CKSEntity &pEntity,
                      CKSDimensionOptions *pOptions = NULL,
                      CKSCoord *pTextCoord = NULL,
                      UCHAR *ucDimType = NULL,
                      CKSEntity *pChamferLine = NULL,
                      CKSRefLine *pRefLine = NULL,
                      CKSLeader *pLeader = NULL,
                      CKS::LocationPtr *pTextLoc = NULL,
                      int *pnDispView = NULL,
                      CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a circular dimension
    int GetCircularDim(const CKSEntity &pEntity,
                       CKSDimensionOptions *pOptions = NULL,
                       CKSCoord *pTextCoord = NULL,
                       CKSEntity *pArc = NULL,
                       CKSRefArc *pRefArc = NULL,
                       CKS::LocationPtr *pTextLoc = NULL,
                       CKSDimStyle *pucDimStyle = NULL,
                       int *pnDispView = NULL,
                       CKSMatrix *pMatrix = NULL,
                       CKSLevel *pLevel = NULL,
                       CKSDrawInst *pInst = NULL,
                       bool *pbBent = NULL,
                       CKS::LocationPtr *pRefCntrLoc = NULL,
                       CKSCoord *pckcElbow1 = NULL,
                       CKSCoord *pckcElbow2 = NULL,
                       CKSWitness *pWitLine = NULL,
                       CKSWitnessArc *pWitArc = NULL,
                       CKSLeader *pLdrFirst = NULL,
                       CKSLeader *pLdrSecond = NULL);

    // @cmember Retrieves the data from a composite entity.
    int GetComposite(const CKSEntity &pEntity, const CKSDrawInst *pDrawInst,
                     std::wstring *pcsName = NULL, CKEntityAttrib *pAttrib = NULL,
                     CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the Quadratic data for a Conic
    int GetConic(const CKSEntity &rConic, const CKSDrawInst *pDrawInst,
                 CKSCoord &ckcStart, CKSCoord &ckcEnd,
                 int &nType, double &dStartParm, double &dEndParm,
                 std::vector<double> &adData,
                 CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the Parametric data for a conic
    int GetConic(const CKSEntity &rConic, const CKSDrawInst *pDrawInst,
                 int &nType, double &dStartParm, double &EndParm,
                 std::vector<double> &adData,
                 CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a cutting entity
    int GetCuttingEntity(const CKSEntity &rCutting, int &nType,
                         CKSMatrixArray &aMatrix, float *pSliceTol = NULL);

    // @cmember Retrieves the data from a datum
    int GetDatum(const CKSEntity &rDatum, std::wstring *pcsText,
                 CKS::GDT::Attachment *pnAttach = NULL,
                 CKS::LocationPtr *pSymbolLoc = NULL,
                 CKS::LocationPtr *pLeaderLoc = NULL,
                 CKS::GDT::Standard *pnStandard = NULL, int *pnDispView = 0,
                 CKSDetailOptions *pOptions = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a Detail Callout
    int GetDetailCallout(CKSDrawInst &DetailCallout,
                         CKSCoord *ckscBase = NULL,
                         CKSDrawInst *DefInstance = NULL,
                         CKS::LocationPtr *locDefArcCenter = NULL,
                         double *dDefArcRadius = NULL,
                         CKS::LocationPtr *locArcLabel = NULL,
                         CKString *cksArcLabel = NULL,
                         CKString *cksCalloutNote = NULL,
                         double *dScale = NULL,
                         bool *bDrawBorder = NULL,
                         CKEntityAttrib *pAttrib = NULL,
                         CKSLevel *pLevel = NULL,
                         bool *bFromModel = NULL,
                         bool *bShowScale = NULL);

    // @cmember Gets the data for an indirect entity reference
    int GetEntRefData(const CKSEntity &pEntity, CKSEntity &pRef,
                      std::vector<unsigned long> &auIDs);

    // @cmember Sets the data for an indirect entity reference
    int SetEntRefData(CKSEntity &pEntity, const CKSEntity &pRef,
                      const std::vector<unsigned long> &aunIDs);

    // @cmember Retrieves the data from a generic dimension
    int GetGenericDim(const CKSEntity &pEntity, CKString *cksText,
                      CKSRefLineArray *aLines,
                      CKSRefArcArray *aArcs,
                      CKSArrowheadArray *aArrows,
                      CKS::LocationPtr *pLoc = NULL,
                      int *pnDispView = NULL,
                      CKSDetailOptions *pOptions = NULL,
                      CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a GeoTol
    // (Geometric Dimensioning and Tolerancing) symbol
    int GetGeoTol(const CKSEntity &pEntity,
                  CKSFeatureControlFrame *pFrame1 = NULL,
                  CKSFeatureControlFrame *pFrame2 = NULL,
                  CKSFeatureControlFrame *pFrame3 = NULL,
                  CKS::GDT::Standard *nStandard = NULL,
                  CKS::LocationPtr *pSymbolLoc = NULL,
                  CKS::LocationArray *aLocations = NULL,
                  bool *bBoundary = NULL, bool *bAllAround = NULL,
                  std::wstring *csOtherText = NULL,
                  std::wstring *csBetweenFirst = NULL,
                  std::wstring *csBetweenSecond = NULL,
                  CKSEntity *pDatum = NULL,
                  CKSLeaderType *nLeaderType = NULL,
                  CKSStackingAlign *nAlign = NULL,
                  CKSOrientType *nOrientation = NULL,
                  CKS::ArrowDirection *nArrowDir = NULL,
                  int *nDispView = 0, CKSDimensionOptions *pOptions = NULL,
                  CKSMatrix *pMatrix = NULL,
                  CKSLeaderArray *pLeaders = NULL,
                  CKSWitnessArray *pWitnesses = NULL);

    // @cmember Retrieves the data from a hatch entity
    int GetHatch(const CKSEntity &rEntity,
                 CKSEntityArray *paBorderEnts = NULL,
                 CKSRefLineArray *paSolidLines = NULL,
                 CKSRefLineArray *paDashLines = NULL,
                 CKSRefLineArray *paCenterLines = NULL,
                 CKSRefLineArray *paPhantomLines = NULL,
                 CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a hatch entity
    int GetHatch(const CKSEntity &rEntity, CKSHatchPattern &pPattern,
                 double &dAngle, double &dXScale, double &dYScale,
                 double &dXOffset, double &dYOffset, double &dBoundaryOffset,
                 CKSEntityArray &aEntities, CKSCoordArray &ackcPoints,
                 CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a label entity
    int GetLabel(const CKSEntity &pEntity, CKString *cksText,
                 CKSWitness *pWitness = NULL,
                 CKSLeaderArray *apLeaders = NULL,
                 CKS::LocationArray *apLoc = NULL,
                 CKS::LocationPtr *pTextLoc = NULL,
                 int *pnDispView = NULL,
                 CKSDetailOptions *pOptions = NULL,
                 CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a Leader entity
    int GetLdrWit(const CKSEntity &pEntity, CKSLeader &rLeader,
                  CKSDetailOptions *pAttrib = NULL,
                  CKSMatrix *pMatrix = NULL);

    // @cmember Get information for a line entity
    int GetLine(const CKSEntity &rLine, const CKSDrawInst *pHInst,
                CKSCoord &ckscStart, CKSCoord &ckscEnd,
                CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a Light entity
    int GetLight(const CKSEntity &rLight, CKSCoord &cksPos, CKSCoord &cksTarget,
        int &Type, int &Outer_units, int &Inner_units,
        double &Outer_size, double &Inner_size, double &Concentration,
        double &FRed, double &FGreen, double &FBlue);

    // @cmember Retrieves the data from a linear dimension
    int GetLinearDim(const CKSEntity &pEntity,
                     CKSDimensionOptions *pOptions = NULL,
                     CKSCoord   *pTextCoord = NULL,
                     CKSRefLine *pRefLine = NULL,
                     CKSWitness *pFirstWit = NULL,
                     CKSWitness *pSecondWit = NULL,
                     CKSLeader *pFirstLeader = NULL,
                     CKSLeader *pSecondLeader = NULL,
                     CKS::LocationPtr *pFirstLoc = NULL,
                     CKS::LocationPtr *pSecondLoc = NULL,
                     CKS::LocationPtr *pTextLoc = NULL,
                     int *pnDispView = NULL,
                     double *pdDimAngle = NULL,
                     CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a Note entity
    int GetNote(const CKSEntity &pEntity, CKString *cksText,
                CKS::LocationPtr *pTextLoc = NULL,
                int *pnDispView = NULL,
                CKSDetailOptions *pOptions = NULL,
                CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the data from a NURBSpline entity
    int GetNURBSpline(const CKSEntity &pEntity, const CKSDrawInst *pHInst,
                      int &nDegree, bool &bRational, bool &bClosed,
                      std::vector<double> &adKnots,
                      CKSCoordArray &ackscControlPoints,
                      std::vector<double> &adWeights,
                      CKEntityAttrib *pAttrib = NULL,
                      CKSMatrix *pMatrix = NULL);

     // @cmember Retrieves the data for a CKOleEntity
    int GetOleEntity(const CKSEntity &pEntity, const CKSDrawInst *pDrawInst,
                     double &dWidth, double &dHeight, CKS::LocationPtr *pFirstLoc,
                     CKS::LocationPtr *pSecondLoc, UCHAR &ucHorAlign,
                     UCHAR &ucVerAlign, int *pnDispView = NULL,
                     CKSMatrix *pMatrix = NULL);

    // @cmember Gets the CKPart in which the entity resides
    static int GetPartFromEnt(const CKSEntity &rEntity, CKPart &rpPart);

    // @cmember Retrieves the data from a part reference
    int GetPartReference(const CKSEntity &rPartRef, std::wstring *pcsFile,
                         std::wstring *pcsPart = NULL,
                         std::wstring *pcsName = NULL,
                         std::wstring *pcsLevelSet = NULL,
                         CKS::FileType *nType = NULL, bool *pbRelative = NULL,
                         bool *pbHidden = NULL, bool *pbSuppressed = NULL,
                         bool *pbLightweight = NULL, bool *pbExploded = NULL,
                         bool *pbHasExplodedOffset = NULL,
                         CKSCoord *pExplodedOffset = NULL,
                         CKS::LocationPtr *ppPositionLoc = NULL,
                         CKS::LocationPtr *ppRotationLoc = NULL,
                         double *pdRotation = NULL,
                         std::vector<std::wstring> *pcsStandardProperties = NULL,
                         std::vector<std::wstring> *pacsUserProperties = NULL,
                         bool *pbDetailEnts = NULL,
                         CKEntityAttrib *pAttrib = NULL,
                         CKSMatrix *pMatrix = NULL);

    // @cmember Retrieves the absolute path to a reference's file.
    int GetPartRefAbsolutePath(const CKSEntity &rPartRef, std::wstring &csFile);

    // @cmember Gets the data for a point entity
    int GetPoint(const CKSEntity &rPoint, const CKSDrawInst *pHInst = NULL,
                 CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Gets the data about the specified polyline entity.
    int GetPolyline(const CKSEntity &rPolyline, const CKSDrawInst *pHInst,
                    CKSCoordArray &ackscPoints, bool &bClosed, bool &bFilled,
                    COLORREF &ulFillColor, CKEntityAttrib *pAttrib = NULL,
                    CKSMatrix *pMatrix = NULL);

    // @cmember Get the data from a shell in this part.
    int GetShell(const CKSEntity &pShell, const CKSDrawInst *pHInst,
                 CKSCoordArray &packcNodes,
                 std::vector<int> &anConnList,
                 CKSCoordArray *packcNormals = NULL,
                 CKEntityAttrib *pAttrib = NULL,
                 CKSMatrix *pMatrix = NULL);

    // @cmember Gets the coefficients data about the specified Spline entity.
    int GetSpline(const CKSEntity &rSpline, const CKSDrawInst *pHInst,
                  std::vector<double> &adCoeffs, bool &b3D,
                  bool &bClosed,CKEntityAttrib *pAttrib = NULL,
                  CKSMatrix *pMatrix = NULL);

    // @cmember Gets the nodes data about the specified Spline entity
    int GetSpline(const CKSEntity &pEntity, const CKSDrawInst *pDrawInst,
                  CKSCoordArray &ackcNodes,
                  CKSCoord *ckscStartVec, CKSCoord *ckscEndVec,
                  bool &b3D, bool &bClosed,
                  CKEntityAttrib *pAttrib = NULL,
                  CKSMatrix *pMatrix = NULL);

    // @cmember Get the data from a target entity.
    int GetTarget(const CKSEntity &pEntity, double *pdOuterDia,
                  CKS::TargetPointType *pnPointType = NULL,
                  CKS::LocationPtr *pLocation = NULL, int *pnDispView = NULL,
                  CKEntityAttrib *pAttrib = NULL, CKSMatrix *pMatrix = NULL);

    // @cmember Gets the corners of the text box of a text entity.
    int GetTextCorners(const CKSEntity &pEntity, CKSCoord &ckscUpperLeft,
                       CKSCoord &ckscUpperRight, CKSCoord &ckscLowerLeft,
                       CKSCoord &ckscLowerRight);

    bool GetTextExtent(LPCTSTR lpszText, CKSDetailFormat &rFormat,
                       double &dWidth, double &dHeight);

    // @cmember Get information on the Vector entity.
    int GetVector(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                  double &dDisplayScale, CKEntityAttrib *pAttrib,
                  CKSMatrix *pMatrix);

     /////  VIEW & CPLANE related stuff..

    // @cmember Delete a User defined CPlane
    int DeleteCPlane(int nCPlane);

    // @cmember Delete a User define Display View
    int DeleteDispView(int nDispView);

    // @cmember Get a CPlane's matrix from this part
    int GetCPlane(const std::wstring &csName, CKSMatrix &rMatrix);

    // @cmember Get a CPlane's number given its name.  Since names are
    // not necessarily unique, this will return the first cplane with
    // the given name.
    int GetCPlane(const std::wstring &csName);

    // @cmember Get a CPlane's matrix from this part
    int GetCPlane(int nNumber, CKSMatrix &rMatrix);

    // @cmember Get a CPlane's name from its number
    int GetCPlane(int nNumber, std::wstring &csName);

    // @cmember Get a list of CPlane names and their associated numbers
    int GetCPlanes(std::vector<unsigned int> &aunNumbers,
                   std::vector<std::wstring> &acsNames);

    // @cmember Get a list of DispView names and their associated numbers
    int GetDispViews(std::vector<unsigned int> &aunNumbers,
                     std::vector<std::wstring> &acsNames);

    // @cmember Get the name for a display view.
    int GetDispViewName(int nView, std::wstring &csViewName);

    //@cmember Get the name for a CPlane.
    int GetCPlaneName(int nCPlane, std::wstring &csCPlaneName);

    // @cmember Set the name of a display view.
    int SetDispViewName(int nView, const std::wstring &csViewName);

    // Set the name of a CPlane.
    int SetCPlaneName(int nCPlane, const std::wstring &csCPlaneName);

// @Group Entity Modification

    // @cmember Add a leader to the specified label.
    int LabelAddLdr(CKSEntity &pEntity,
                    const CKSLeaderArray &aLeaders,
                    CKS::LocationArray *paLocations);
    // @cmember Add a leader to the specified label.
    int BalloonAddLdr(CKSEntity &pEntity,
                      CKSLeaderType nLeaderType,
                      CKS::LocationArray *paLocations);

    // @cmember Add to an existing Baseline dimension entity
    int BaselineAddDimension(CKSEntity &rBaseDim, CKS::Location *pTextLoc,
                             CKS::Location *pLoc,
                             const CKSDimensionOptions *pOptions = NULL);

    // @cmember Change arrowhead by polygon selection
    int ChangeArrowheadByPolygon(int nMethod,
                                 const CKSCoordArray &ackcCoord,
                                 UCHAR ucArrowheadStyle,
                                 int nViewPort = -1);

    // @cmember Add an existing entity to a composite entity
    int CompositeAddEntity(CKSEntity &rComposite, CKSEntity &pEntity);

    // @cmember Add an array of entities to a composie entity
    int CompositeAddEntity(CKSEntity &pEntity, CKSEntityArray &aEntities);

    // @cmember Removes an entity from a composite entity
    int CompositeRemoveEntity(CKSEntity &rComposite, CKSEntity &pEntity);

    // @cmember Removes entities from a composite
    int CompositeRemoveEntity(CKSEntity &rComposite, CKSEntityArray &rEntities);

    // @cmember Transforms an array of entities
    int DoXForm(CKS::XFormCmd nCmd, CKS::XFormType nType,
               CKSMatrix &rMatrix, CKSEntityArray &psEntities,
               CKSEntityArray *psCopied = NULL);

    int XForm(CKS::XFormCmd nCmd, CKS::XFormType nType,
        CKSMatrix &ckmTransform, CKSEntityArray &aEntities);

    // Transform entities in a boxed window by moving them
    int XFormBoxMove(int nMethod, const CKSCoordArray &ackcCoord,
                     const CKSCoord *ckcDeltaPos, const CKSCoord *ckcOldBase,
                     const CKSCoord *ckcNewBase, int nViewPort = -1);

    // @cmember Offset given entities by a given distance in the CPlane and
    // a given depth above that plane.
    int XFormChainOffset(const CKSEntityArray &aEntities, double dOffset,
                         double dDepth, double dChordTol, bool bJoinLines,
                         bool bDeleteEnts, int nCornering,
                         int nRepresentation, CKSEntityArray *pNewEnts);

    // @cmember Rotates geometry about a defined axis by a given angle while
    // maintaining its original orientation.
    int XFormCircularArray(const CKSEntityArray &aEntities,
                           const CKSCoord &ckcStartAxis,
                           const CKSCoord *ckcEndAxis,
                           const CKSCoord &ckcBase, double dAngle,
                           int nCopies, CKS::XFormCmd nCmd,
                           CKSEntityArray *psCopied = NULL);

    // @cmember Provides the functionality of the Transform-Compress Curves
    // function.
    int XFormCompressCurves(const CKSEntityArray &aEntities, double dTol,
                            bool bCompress, bool bRemove, bool bLevel,
                            bool bColor, bool bType, bool bWidth, bool bPen,
                            bool bGroup, bool bSubGroup);

    // @cmember Transform an array of entities by Delta
    int XFormDelta(const CKSEntityArray &aEntities, const CKSCoord &vecDelta,
                   int nCopies, CKS::XFormCmd nCmd,
                   CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities via a Helical rotation
    int XFormHelix(const CKSEntityArray &aEntities, const CKSCoord &ckcStart,
                   const CKSCoord *ckcEnd,  int nCopies, double dPitch,
                   double dAngle, CKS::XFormCmd nCmd, int nJoin = 1,
                   double dTolerance = 0.001, CKSEntityArray *psCopied = NULL);

    // @ cmember Transform an array of entities by Mirroring
    int XFormMirror(const CKSEntityArray &aEntities, int nPlaneType,
                    const CKSCoord  *ckcPos1, const CKSCoord *ckcPos2,
                    const CKSMatrix *ckmPlane, CKS::XFormCmd nCmd,
                    CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities by using Old to New positions
    int XFormOldNew(const CKSEntityArray &aEntities,
                    const CKSCoordArray &ackcOldCoord,
                    const CKSCoordArray &ackcNewCoord, int nCopies,
                    CKS::XFormCmd nCmd, CKSEntityArray  *psCopied = NULL);

    // @cmember Transform an array of entities by Projection
    int XFormProject(CKSEntityArray &aEntities, const CKSMatrix &ckmPlane,
                     CKS::XFormCmd nCmd, int nProjectType,
                     const CKSCoord *ckcDirection = NULL,
                     CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities by Rotation
    int XFormRotate(const CKSEntityArray &aEntities, const CKSCoord &ckcBase,
                    const CKSCoord *ckcVec, int nCopies, double dAngle,
                    CKS::XFormCmd nCmd, int nJoin = 1,
                    CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities by scaling them along coordinate axes.
    int XFormScaleAxes(CKSEntityArray &aEntities, const CKSCoord &ckcBase,
                       const CKSCoord &ckcScale, int nCopies,
                       CKS::XFormCmd nCmd, CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities by fully scaling each entity.
    int XFormScaleFull(const CKSEntityArray &aEntities,
                       const CKSCoord &ckcBase, double dScale, int nCopies,
                       CKS::XFormCmd nCmd, CKSEntityArray *psCopied = NULL);

    // @cmember Transform an array of entities by scaling in one direction.
    int XFormScaleUnidir(CKSEntityArray &aEntities, const CKSCoord &ckcBase,
                         const CKSCoord &ckcScale, double dScale, int nCopies,
                         CKS::XFormCmd nCmd, CKSEntityArray *psCopied = NULL);

    // @cmember Get matrix perpendicular to CPlane horizontal to DispView
    // containing selected position
    int GetMatrixOnePosHoriz(const CKSCoord &ckcPos, CKSMatrix &ckmPlane);

    // @cmember Get matrix perpendicular to CPlane and vertical to DispView
    // containing selected position
    int GetMatrixOnePosVertical(const CKSCoord &ckcPos, CKSMatrix &ckmPlane);

    // @cmember Get the matrix perpendicular to the CPlane and containing the
    // two selected positions
    int GetMatrixTwoPosVertical(const CKSCoord &ckcPos1,
                                const CKSCoord &ckcPos2, CKSMatrix &ckmPlane);

    // @cmember Break two entities at their intersection
    int BreakBoth(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                  double dParam1, CKSCoord &ckscCoord1,
                  CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                  double dParam2, CKSCoord &ckscCoord2,
                  CKSEntityArray *apNewEnts = NULL,
                  const std::wstring &csGroup = std::wstring());

    // @cmember Break entity into three ents at intersections defined by two other entities
    int BreakDivide(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                    double dParam1, CKSCoord &ckscCoord1,
                    CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                    double dParam2, CKSCoord &ckscCoord2,
                    CKSEntity &pEnt3, const CKSDrawInst &pDrawInst3, int nSeg3,
                    double dParam3, CKSCoord &ckscCoord3,
                    CKSEntityArray *apNewEnts = NULL,
                    const std::wstring &csGroup = std::wstring());

    // @cmember Break entity at intersections defined by two other entities
    int BreakDouble(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                    double dParam1, CKSCoord &ckscCoord1,
                    CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                    double dParam2, CKSCoord &ckscCoord2,
                    CKSEntity &pEnt3, const CKSDrawInst &pDrawInst3, int nSeg3,
                    double dParam3, CKSCoord &ckscCoord3,
                    CKSEntityArray *apNewEnts = NULL,
                    const std::wstring &csGroup = std::wstring());

    // @cmember Break entity based on common intersection with single entity
    int BreakFirst(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                   double dParam1, CKSCoord &ckscCoord1,
                   CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                   double dParam2, CKSCoord &ckscCoord2,
                   CKSEntityArray *apNewEnts = NULL,
                   const std::wstring &csGroup = std::wstring());

    // @cmember Break entity at intersections defined by 2 other entities
    int BreakModal(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                   double dParam1, CKSCoord &ckscCoord1,
                   CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                   double dParam2, CKSCoord &ckscCoord2,
                   CKSEntityArray *apNewEnts = NULL,
                   const std::wstring &csGroup = std::wstring());

    // @cmember Break entity at a position indicated.
    int BreakPos(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                 double dParam1, CKSCoord &ckscCoord1, CKSCoord ckscTrimPos,
                 CKSEntityArray *apNewEnts = NULL,
                 const std::wstring &csGroup = std::wstring());

    // @cmember Break an entity and closest entity at intersection of both.
    int BreakSmartBoth(CKSEntity &pEnt, const CKSDrawInst &pDrawInst, int &nSeg,
                       double &dParam,  CKSCoord &ckscSelPos,
                       CKSEntityArray *apNewEnts = NULL,
                       const std::wstring &csGroup = std::wstring());

    // @cmember Break entity at intersection with its closest entity
    int BreakSmartSingle(CKSEntity &pEnt, const CKSDrawInst &pDrawInst,
                         int &nSeg, double &dParam,  CKSCoord &ckscSelPos,
                         CKSEntityArray *pNewEnts = NULL,
                         const std::wstring &csGroup = std::wstring());

    // @cmember Create a chamfer to two lines.
    int ChamferNoTrim(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1,
                      double dParam1, CKSEntity &pEnt2,
                      const CKSDrawInst &pDrawInst2, double dParam2,
                      double dDist1, double dDist2);

    // @cmember Create a chamfer to two lines and trim.
    int ChamferTrim(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1,
                    double dParam1, CKSEntity &pEnt2,
                    const CKSDrawInst &pDrawInst2, double dParam2,
                    double dDist1, double dDist2);

    // @cmember Create an Arc (or Spline) fillet to two entities
    int FilletNoTrim(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1,
                     int nSeg1, double dParam1,
                     CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2,
                     int nSeg2, double dParam2,
                     double dRadius, CKEntityAttrib *pAtrrib = NULL);

    // @cmember Create an Arc(or Spline) fillet to two entities and trim
    int FilletTrim(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1,
                   int nSeg1, double dParam1,
                   CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2,
                   int nSeg2, double dParam2,
                   double dRadius, CKEntityAttrib *pAtrrib = NULL);

    // @cmember Trim either or both ends of an entity or its instance
    int Trim(CKSEntity &pEnt, CKSDrawInst &pDrawInst,
             bool bTrimStart, int nSegStart, double dParamStart,
             bool bTrimEnd, int nSegEnd, double dParamEnd);

    // @cmember Trim two entities at their intersection
    int TrimBoth(CKSEntity &pEnt1, const CKSDrawInst &pInst1, int nSeg1,
                 double dParam1, CKSCoord &ckscCoord1,
                 CKSEntity &pEnt2, const CKSDrawInst &pInst2, int nSeg2,
                 double dParam2, CKSCoord &ckscCoord2);

    // @cmember Trim entity into three ents at intersections defined by two other entities
    int TrimDivide(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                   double dParam1, CKSCoord &ckscCoord1,
                   CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                   double dParam2, CKSCoord &ckscCoord2,
                   CKSEntity &pEnt3, const CKSDrawInst &pDrawInst3, int nSeg3,
                   double dParam3, CKSCoord &ckscCoord3);

     // @cmember Trim entity at intersections defined by 2 other entities
    int TrimDouble(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                   double dParam1, CKSCoord &ckscCoord1,
                   CKSEntity &pEnt2, const CKSDrawInst &pDrawInst2, int nSeg2,
                   double dParam2, CKSCoord &ckscCoord2,
                   CKSEntity &pEnt3, const CKSDrawInst &pDrawInst3, int nSeg3,
                   double dParam3, CKSCoord &ckscCoord3);

    // @cmember Trim entity based on common intersection with a single entity
    int TrimFirst(CKSEntity &pEnt1, const CKSDrawInst &pInst1, int nSeg1,
                  double dParam1, CKSCoord &ckscCoord1,
                  CKSEntity &pEnt2, const CKSDrawInst &pInst2, int nSeg2,
                  double dParam2, CKSCoord &ckscCoord2);

    // @cmember Trim entity at intersections defined by 2 other entities
    int TrimModal(CKSEntity &pEnt1, const CKSDrawInst &pInst1, int nSeg1,
                  double dParam1, CKSCoord &ckscCoord1,
                  CKSEntity &pEnt2, const CKSDrawInst &pInst2, int nSeg2,
                  double dParam2, CKSCoord &ckscCoord2);

    // @cmember Trim entity at a position indicated.
    int TrimPos(CKSEntity &pEnt1, const CKSDrawInst &pDrawInst1, int nSeg1,
                double dParam1, CKSCoord &ckscCoord1, CKSCoord ckscTrimPos);

    // @cmember Trim entity and closest entity at intersection of both.
    int TrimSmartBoth(CKSEntity &pEnt, const CKSDrawInst &pDrawInst, int &nSeg,
                      double &dParam,  CKSCoord &ckscSelPos);

    // @cmember Trim entity to intersection of closest entity
    int TrimSmartSingle(CKSEntity &pEnt, const CKSDrawInst &pDrawInst,
                        int &nSeg, double &dParam, CKSCoord &ckscSelPos);

    // @cmember Trim model with cutting entity
    int TrimCuttingEntity(CKSEntityArray &aCutEnts, int nOperation,
                          bool bCurve, bool bHatch,
                          bool bActiveLevel = true, double dTolerance = 1e-5,
                          CKSHatchPattern *ppPattern = NULL,
                          double dAngle = 0,
                          double dXScale = 0, double dYScale = 0,
                          double dXOffset = 0, double dYOffset = 0,
                          double dBoundaryOffset = 0);

    // @cmember Add existing Copious to an Entity
    int EntityAddCopious(CKSEntity &pEntity, CKSCopious &rCopious);

    // @cmember Removes a Copious from an Entity
    int EntityRemoveCopious(CKSEntity &pEntity, CKSCopious &rCopious);

    // @cmember Modifies the attributes of an existing Text entity.
    int ModEntityAttrib(CKSEntity &pEntity, CKSDetailOptions &rAttrib);

    // @cmember Modifies the attributes of an existing Dimension entity.
    int ModEntityAttrib(CKSEntity &pEntity, CKSDimensionOptions &rAttrib);

    // @cmember Modifies the attributes of an existing entity .
    int ModEntityAttrib(CKSEntity &pEntity, CKEntityAttrib &rAttrib);

    // @cmember Modifies the attributes of an existing entity .
    int ModEntityAttrib(CKSEntityArray &aEntities, CKSDetailOptions &rAttrib);

    // @cmember Modifies the data in a Balloon entity.
    int ModBalloon(CKSEntity &pEntity,
                   const CKString *cksPrimaryText = NULL,
                   const CKSBalloonType *nBalloonType = NULL,
                   const CKSLeaderType *nLeaderType = NULL,
                   const double *dDiameterRatio = NULL,
                   const CKString *cksSplitText = NULL,
                   const CKSStackingAlign *nAlign = NULL,
                   const int *nDispView = NULL,
                   const CKS::LocationPtr *pSymbolLoc = NULL,
                   const CKS::LocationArray *apLocations = NULL,
                   const CKSDetailOptions *pOptions = NULL,
                   const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies the text and attributes of an existing dimension entity.
    int ModDimension(CKSEntity &pEntity,
                     const CKS::LocationPtr *pTextLoc = NULL,
                     const int *pnDispView = NULL,
                     const CKSDimensionOptions *pOptions = NULL,
                     const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Angular dimension entity
    int ModAngularDim(CKSEntity &pEntity,
                      const bool *pbInnerAngle = NULL,
                      const CKSRefLine *pRlFirst = NULL,
                      const CKSRefLine *pRlSecond = NULL,
                      const CKSWitness *pWitFirst = NULL,
                      const CKSWitness *pWitSecond = NULL,
                      const CKSLeaderArc *pLdrFirst = NULL,
                      const CKSLeaderArc *pLdrSecond = NULL,
                      CKS::LocationArray *caLocations = NULL,
                      const CKS::LocationPtr *pTextLoc = NULL,
                      const int *pnDispView = NULL,
                      const CKSDimensionOptions *pOptions = NULL,
                      const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Arc entity
    int ModArc(CKSEntity &rArc, const double *pdRad,
               const double *pdStartAng, const double *pdDeltaAng,
               const CKEntityAttrib *pAttrib = NULL,
               const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies a Baseline dimension entity.
    int ModBaseLinearDim(CKSEntity &pEntity,
                         const double *pdOffsetValue = NULL,
                         const UCHAR *pucDispStyle = NULL,
                         const CKS::LocationPtr *pLocation = NULL,
                         const CKS::LocationPtr *pTextLocation = NULL,
                         const int *pnDispView = NULL,
                         const CKSDimensionOptions *pOptions = NULL,
                         const CKSWitness *pWitness = NULL,
                         const CKSLeader *pFirstLeader = NULL,
                         const CKSLeader *pSecondLeader = NULL,
                         const CKSMatrix *pMatrix = NULL);

    int ModChamferDim(CKSEntity &pEntity,
                      const UCHAR *pucDimType = NULL,
                      CKSEntity *pChamferLine = NULL,
                      const CKSLeader *pLeader = NULL,
                      const CKS::LocationPtr *pTextLoc = NULL,
                      const int *pnDispView = NULL,
                      const CKSDimensionOptions *pOptions= NULL,
                      const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Circular dimension entity
    int ModCircularDim(CKSEntity &pEntity,
                       const bool *bBentRadial = NULL,
                       const CKSRefArc *pRefArc = NULL,
                       const CKSWitness *pWitLine = NULL,
                       const CKSWitnessArc *pWitArc = NULL,
                       const CKSLeader *pLdrFirst = NULL,
                       const CKSLeader *pLdrSecond = NULL,
                       CKSEntity *pArc = NULL,
                       const CKS::LocationPtr *pRefCenterLoc = NULL,
                       const CKS::LocationPtr *pTextLoc = NULL,
                       const int *pnDispView = NULL,
                       const CKSDimensionOptions *pOptions = NULL,
                       const CKSMatrix *pMatrix = NULL);

#ifndef CADKEY_VIEWER
    // @cmember Modifies an existing composite entity.
    int ModComposite(CKSEntity &pEntity, const std::wstring *pcsName = NULL,
                     const CKEntityAttrib *pAttrib = NULL,
                     const CKSMatrix *pMatrix = NULL);
#endif

    // @cmember Modifies an existing Conic entity using Quadratic data
    // coefficients
    int ModConic(CKSEntity &pEntity, const CKSCoord *pckcStart, const CKSCoord *pckcEnd,
                 const std::vector<double> *padData,
                 const CKEntityAttrib *pAttrib = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Conic entity using Parametric data
    // coefficients
    int ModConic(CKSEntity &drEntity, int nType,
                 double *pdStartParam, double *pdEndParam,
                 const std::vector<double> *padData,
                 const CKEntityAttrib *pAttrib = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing cutting entity.
    int ModCuttingEntity(CKSEntity &pEntity, const CKSMatrixArray &aMatrix, float fSliceTol = 0);

    // @cmember  Modifies an existing datum.
    int ModDatum(CKSEntity &rDatum, const std::wstring *pcsText = NULL,
                 CKS::GDT::Attachment *pnAttach = NULL,
                 const CKS::LocationPtr *pSymbolLoc = NULL,
                 const CKS::LocationPtr *pLeaderLoc = NULL,
                 CKS::GDT::Standard *pnStandard = NULL,
                 int *pnDispView = 0,
                 const CKSDetailOptions *pOptions = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Generic dimension entitiy
    int ModGenericDim(CKSEntity &pEntity, const CKString *cksText = NULL,
                      const CKSRefLineArray *aLines = NULL,
                      const CKSRefArcArray *aArcs = NULL,
                      const CKSArrowheadArray *aArrows = NULL,
                      const CKS::LocationPtr *pLoc = NULL,
                      const int *pnDispView = NULL,
                      const CKSDetailOptions *pOptions = NULL,
                      const CKSMatrix *pMatrix = NULL);

    // @cmember Modify a GeoTol (Geometric Dimension and Tolerance)
    // symbol in this part.
    int ModGeoTol(CKSEntity &pEntity,
                  const CKSFeatureControlFrame *pFrame1,
                  const CKSFeatureControlFrame *pFrame2 = NULL,
                  const CKSFeatureControlFrame *pFrame3 = NULL,
                  const CKS::GDT::Standard *nStandard = NULL,
                  const CKS::LocationPtr *pSymbolLoc = NULL,
                  const CKS::LocationArray *aLocations = NULL,
                  const bool *bBoundary = NULL, const bool *bAllAround = NULL,
                  const std::wstring *pcsOtherText = NULL,
                  const std::wstring *pBetweenFirst = NULL,
                  const std::wstring *pBetweenSecond = NULL,
                  const CKSEntity *pDatum = NULL,
                  const CKSLeaderType *nLeaderType = NULL,
                  const CKSOrientType *nOrientation = NULL,
                  const CKSStackingAlign *nAlign = NULL,
                  const CKS::ArrowDirection *nArrowDir = NULL,
                  const int *nDispView = 0, const CKSDetailOptions *pOptions = NULL,
                  const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies a hatch entity.
    int ModHatch(const CKSEntity &rEntity, CKSHatchPattern *ppPattern,
                 double *pdAngle, double *pdXScale, double *pdYScale,
                 double *pdXOffset, double *pdYOffset,
                 double *pdBoundaryOffset, CKSEntityArray *papEntities,
                 CKSCoordArray *packcPoints, CKEntityAttrib *pAttrib = NULL,
                 CKSMatrix *pMatrix = NULL);

    // @cmember Add entities or points to a hatch.
    int HatchAddEntities(CKSEntity &pEntity, const CKSEntityArray &aEntities,
                         const CKSCoordArray &aPoints);

    // @cmember Remove entities or points from a hatch.
    int HatchRemoveEntities(CKSEntity &pEntity, const CKSEntityArray &aEntities,
                            const CKSCoordArray &aPoints);

    // @cmember Modifies an existing Label entity
    int ModLabel(CKSEntity &pEntity, const CKString *cksText = NULL,
                 const CKSWitness *pWitness = NULL,
                 const CKSLeaderArray *apLeaders = NULL,
                 CKS::LocationArray *apLocs = NULL,
                 const CKS::LocationPtr *pTextLoc = NULL,
                 const int *pnDispView = NULL,
                 const CKSDetailOptions *pAttrib = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Line entity
    int ModLine(CKSEntity &rLine, const CKSCoord *pckscStart,
                const CKSCoord *pkscEnd,
                const CKEntityAttrib *pAttrib = NULL,
                const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Linear dimension
    int ModLinearDim(CKSEntity &pEntity,
                     const CKSRefLine *pRefLine = NULL,
                     const CKSWitness *pWitFirst = NULL,
                     const CKSWitness *pWitSecond = NULL,
                     const CKSLeader *pFirstLeader = NULL,
                     const CKSLeader *pSecondLeader = NULL,
                     const CKS::LocationPtr *pLocFirst = NULL,
                     const CKS::LocationPtr *pLocSecond = NULL,
                     const CKS::LocationPtr *pTextLoc = NULL,
                     const int *pnDispView = NULL,
                     const double *pdDimAngle = NULL,
                     const CKSDimensionOptions *pOptions = NULL,
                     const CKSMatrix *pMatrix = NULL);

    // @cmember Merge the specified linear dimensions.
    int LinearDimMerge(CKSEntity &pDim1, CKSEntity &pDim2);

    // @cmember Align the text positions of an array of dimensions to a base
    // dimension.
    int LinearDimAlign(CKSEntity &pDim, CKSEntityArray &psDims, double dStep);

    // @cmember Modifies an existing LeaderWitness
    int ModLdrWit(CKSEntity &rEntity, const CKSLeader *pLeader = NULL,
                  const CKSDetailOptions *pAttrib = NULL,
                  const CKSMatrix *pMatrix = NULL);

    // @cmember Modify the points of an existing LeaderWitness.
    int SetLdrWitPoints(CKSEntity &rEntity, CKSCoordArray &ackscPoints,
                        const std::vector<int> &aHVSegment,
                        int nStartIndex = 0);

    // @cmember Modifies an existing Note entity
    int ModNote(CKSEntity &pEntity, const CKString *cksText = NULL,
                const CKS::LocationPtr *pTextLoc = NULL,
                const int *pnDispView = NULL,
                const CKSDetailOptions *pOptions = NULL,
                const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing NURBSpline entity using Control Points
    int ModNURBSpline(CKSEntity &pEntity, const int *pnDegree,
                      const bool *pbRational = NULL,
                      const bool *pbClosed = NULL,
                      const std::vector<double> *pdKnots = NULL,
                      const CKSCoordArray *packscControlPoints = NULL,
                      const std::vector<double> *padWeights = NULL,
                      const CKEntityAttrib *pAttrib = NULL,
                      const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing NURBSpline entity using Fit Points
    int ModNURBSpline(CKSEntity &pEntity, const int *pnDegree,
                      const bool *pbRational = NULL,
                      const bool *pbClosed = NULL,
                      const CKSCoordArray *packscFits = NULL,
                      const CKEntityAttrib *pAttrib = NULL,
                      const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing OLE Entity
    int ModOleEntity(CKSEntity &pEntity, const double *pdWidth = NULL,
                     const double *pdHeight = NULL,
                     CKS::Location *pFirstLoc = NULL,
                     CKS::Location *pSecondLoc = NULL,
                     const UCHAR *pucHorAlign = NULL,
                     const UCHAR *pucVerAlign = NULL,
                     const int *pnDispView = NULL,
                     const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies the data of a part reference
    int ModPartReference(CKSEntity &rPartRef, const std::wstring *pcsFile,
                         const std::wstring *pcsPart = NULL,
                         const std::wstring *pcsName = NULL,
                         const std::wstring *pcsLevelSet = NULL,
                         const CKS::FileType *nType = NULL,
                         const bool *pbRelative = NULL,
                         const bool *pbHidden = NULL,
                         const bool *pbSuppressed = NULL,
                         const bool *pbLightweight = NULL,
                         const bool *pbExploded = NULL,
                         const CKSCoord *pExplodedOffset = NULL,
                         const CKSEntity *pInsertionPlane = NULL,
                         bool bKeepPlane = true,
                         const CKS::LocationPtr *ppPositionLoc = NULL,
                         bool bKeepPositionLoc = true,
                         const CKS::LocationPtr *ppRotationLoc = NULL,
                         bool bKeepRotationLoc = true,
                         const double *pdRotation = NULL,
                         const std::vector<std::wstring> *pcsStandardProperties = NULL,
                         const std::vector<std::wstring> *pacsUserProperties = NULL,
                         const bool *pbDetailEnts = NULL,
                         const CKEntityAttrib *pAttrib = NULL,
                         const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Point entity
    int ModPoint(CKSEntity &rPoint, const CKEntityAttrib *pAttrib = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Polyline entity
    int ModPolyline(CKSEntity &rPolyline,
                    const CKSCoordArray *packscPoints = NULL,
                    const bool *pbClosed = NULL, const bool *pbFilled = NULL,
                    const COLORREF *pulFillColor = NULL,
                    const CKEntityAttrib *pAttrib = NULL,
                    const CKSMatrix *pMatrix = NULL);

    // @cmember Get the data from a shell in this part.
    int ModShell(const CKSEntity &pShell, const CKSCoordArray &ackcNodes,
                 const std::vector<int> &anConnList,
                 const CKSCoordArray *packcNormals = NULL,
                 const CKEntityAttrib *pAttrib = NULL,
                 const CKSMatrix *pMatrix = NULL);

    // @cmember modifies an existing Spline entity using coefficients data
    int ModSpline(CKSEntity &rSpline,
                  const std::vector<double> *padData = NULL,
                  const bool *pb3D = NULL, const bool *pbClosed = NULL,
                  const CKEntityAttrib *pAttrib = NULL,
                  const CKSMatrix *pMatrix = NULL);

    //  @cmember Modifies an existing Spline using Nodes data
    int ModSpline(CKSEntity &rSpline, const bool *pb3D = NULL,
                  const bool *pbClosed = NULL, const bool *pbStartVector = NULL,
                  const bool *pbEndVector = NULL,
                  const CKSCoord *pckscStartVec = NULL,
                  const CKSCoord *pckscEndVec = NULL,
                  const CKSCoordArray *packscPoints = NULL,
                  const CKEntityAttrib *pAttrib =NULL,
                  const CKSMatrix *pMatrix = NULL);

    // @cmember Modify the data of a target entity.
    int ModTarget(CKSEntity &pEntity,
                  const double *pdOuterDia,
                  const CKS::TargetPointType *pnPointType = NULL,
                  const CKS::LocationPtr *pLocation = NULL,
                  const int *pnDispView = NULL,
                  const CKEntityAttrib *pAttrib = NULL,
                  const CKSMatrix *pMatrix = NULL);

    // @cmember Modifies an existing Vector entity.
    int ModVector(CKSEntity &rEntity, const double *dDisplayScale = NULL,
                  const CKEntityAttrib *pAttrib = NULL,
                  const CKSMatrix *pMatrix = NULL);

    int ModVector2P(CKSEntity & rEntity, const CKS::LocationPtr *pLocStart = NULL,
                    const CKS::LocationPtr *pocLocEnd = NULL,
                    const double *dDispayScale = NULL,
                    const CKEntityAttrib *pAttrib = NULL,
                    const CKSMatrix *pMatrix = NULL);

    // @cmember Forces a modified entity to update itself in the graphics
    // system.
    int DrawEntity(CKSEntity &pEntity);

    // @cmember Forces modified entities to update themselves in the graphics
    // system.
    int DrawEntity(CKSEntityArray &aEntities);

    // @cmember Expands field specifiers in a CKString
    int ExpandFieldSpecifiers(CKSEntity &rEntity, CKString &csText);

    // @cmember Returns the displayed text of a note in a CKString
    int GetNoteDisplayedText(CKSEntity &rEntity, CKString &csText);

    // @cmember Bursts an entity into its component parts.  For objects
    // such as composites, the original child entities are used.
    int Burst(CKSEntity &pEntity, CKSEntityArray *paEntities = NULL);

    // @cmember Bursts an array of entities into their component parts.
    // For objects such as composites, the original child entities are used.
    int Burst(CKSEntityArray &aEntities, CKSEntityArray *paEntities = NULL);

    // @cmember Bursts a copy of an entity into its component parts.  For
    // objects such as composites, new copies of the child entities are
    // created.
    int BurstCopy(CKSEntity &pEntity, CKSEntityArray *paEntities = NULL);

    // @cmember Convert an array of entities to KeyCreator native details.
    int ConvertToKCDetail(CKSEntityArray &aEntities);

    // @cmember Applies a transformation on an array of entities
    int TransformEntities(CKSEntityArray &aEntities,
                          const CKSMatrix &ckmTransform,
                          CKS::XFormType nType);

    // @cmember Copies an entity
    int CopyEntity(CKSEntity &pEntity, CKSEntity &pNewEntity);

    // @cmember Copies an entity to a new parent.
    int CopyEntity(CKSEntity &pEntity, CKSEntity &pNewEntity,
                   const CKSEntity &pParent, const CKSLevel &pLevel);

    // @cmember Copies an array of entities
    int CopyEntities(CKSEntityArray &aEntities, CKSEntityArray &aNewEntities);

    // @cmember Copies an array of entities to a new parent.
    int CopyEntities(CKSEntityArray &aEntities, CKSEntityArray &aNewEntities,
                     const CKSEntity &pParent, const CKSLevel &pLevel);

    // @cmember Blank entities
    int BlankEntities(CKSEntityArray &aEntities);

    // @cmember UnBlank entities
    int UnBlankEntities(CKSEntityArray &aEntities);

    // @cmember UnBlank all entities
    int UnBlankAllEntities();

    // @cmember Check if entity is blanked
    bool IsEntityBlanked(CKSEntity &pEntity);

    // @cmember Set entity rendering
    int SetEntityRendering(CKSEntityArray &aEntities,
                           CKS::Rendering ucRendering,
                           CKS::WireRendering ucWireRendering = CKS::WireDefault,
                           CKS::ThreadRendering ucThreadRendering = CKS::ThreadRenderDefault);

    // @cmember UnSet entity rendering
    int UnSetEntityRendering(CKSEntityArray &aEntities);

    // @cmember Set cutting entity visibility.
    int CuttingEntityVisible(CKSEntityArray &aEntities, bool bVisible);

    // @cmember Edit a part reference in context.
    int EditInContextPartRef(const CKSEntity &rPartRef);

// @Group Selection Functions
    // @cmember Invoke Universal Selection Menu and wait until one or more
    //  entities are selected.
    int GenSel(const std::wstring &csPmpt, CKSEntityArray &aEntities,
               ULONG ulOptions = 0, ULONG ulFuncs = 0,
               bool bPreSelected = false);

    // @cmember Invoke specified selection mechanism and wait until one or more
    //  entities are selected.
    int GenSelMethod(const std::wstring &csPmpt, CKSSelect nOption,
                     CKSEntityArray &aEntities, ULONG ulOptions = 0);

    // @cmember Select entities via polygon selection.
    int SelEntPoly(int nOption, int nVpNum, CKSEntityArray &aEntities,
                   const CKSCoordArray *paPoints, ULONG ulOptions = 0);

    // @cmember Select all of the entities residing within the current viewport
    //  boundaries.
    int SelEntView(int nVpNum, CKSEntityArray &aEntities,
                   ULONG ulOptions = 0);

    int SelMethod(CKSSelect nOption, int nOption2, int nViewport,
                  CKSEntityArray &psEntities, CKSCoordArray *paCoord = NULL,
                  ULONG ulOptions = 0);

    // @cmember Compute a chain selection from the given entity and 
    // selection location information.
    int SelectChain(CKSEntity &pEntity, const CKSDrawInst &pInst, int nSeg,
                    double dParam, ULONG ulOptions, CKSEntityArray &aEntities);

    // @cmember Function for selecting an entity.
    int GetEnt(const std::wstring &csPrompt, CKSEntity &pEntity,
               CKSDrawInst &pInst, ULONG ulOptions = 0, int *pSeg = NULL,
               double *pParam = NULL, CKSCoord *pCoord = NULL,
               const std::wstring *pcsMacroText = NULL,
               CKSAnim* pAnim = NULL,
               ULONG ulFuncs = CKS::GMDefault, ULONG ulMenu = 0);

    // @cmember Select an entity at the given x/y view position.
    int GetEntXY(double dX, double dY, int nVpNum, CKSEntity &pEntity,
                 ULONG ulOptions = 0);

    // @cmember Select an entity at the given x/y view position.
    int GetEntXY(double dX, double dY, int nVpNum, CKSEntity &pEntity,
                 ULONG ulOptions = 0, int *pSeg = NULL, double *pParam = NULL,
                 double dSearchRadius = -1.0);

    // @cmember Return an array of entities at the given x/y view position.
    int GetEntXY(double dX, double dY, int nVpNum, CKSEntityArray &apEntities,
                 ULONG ulOptions = 0);

    // @cmember Return an array of entities at the given x/y view position.
    int GetEntXY(double dX, double dY, int nVpNum, CKSEntityArray &apEntities,
                 ULONG ulOptions = 0, double dSearchRadius = -1.0);

    // @cmember Get the Parent of an entity
    int GetEntityParent(const CKSEntity &pEntity, CKSEntity &pParent);

    // @cmember Get entities by the Parent of an entity
    int GetEntsBySolidChainSel(const CKSEntity& rSeedEnt, int nMethod,
                               int nGenToggleLevel, int nSelectionMask,
                               CKSEntityArray &aSelEntities);

    // @cmember Find the entity closest to a position.
    int FindEnt(int nVpNum, const CKSCoord &ckscCoord, ULONG ulOptions,
                CKSEntity &pEntity, CKSDrawInst &rInst, int &nSeg,
                double &dParam);

    // @cmember Return the selection list of entities that the user has
    //  currently built up.
    int GetSelectList(CKSEntityArray &aEntity);

    // @cmember Check if specified entity is contained in root selection.
    bool RootSelectionContains(const CKSEntity &pEntity);

    // @cmember Add entity to root selection.
    void AddRootSelection(const CKSEntity &pEntity);

    // @cmember Add entities to root selection.
    void AddRootSelection(const CKSEntityArray &psEntities);

    // @cmember Get number of entities in root selection.
    int GetRootSelectionCount();

    // @cmember Get entities in root selection.
    void GetRootSelection(CKSEntityArray &aEntities);

    // @cmember Clear root selection.
    void ClearRootSelection();

    // @cmember Prompts the user to define a plane.
    int DefinePlane(CKSMatrix &rPlane, const std::wstring &csPrompt);

    // @cmember Prompt the user to define a direction.
    int DefineDirection(CKSCoord &ckcDirection, bool bNormalize = true,
                        const std::wstring &csPrompt = std::wstring());

    // @cmember Prompts user for selection of a drawing instance.
    int DrawInstSelect(CKSDrawInst &pDrawInst, int nInstTypes,
                       const std::wstring &csPrompt, bool bAccept = false);

    // @cmember Prompts user for selection of drawing instances.
    int DrawInstSelect(CKSDrawInstArray &psDrawInst, int nInstTypes,
                       const std::wstring &csPrompt);

// @Group Positioning Functions
    // @cmember Invoke Universal Position Menu and wait until a 3-D position
    //  in space is indicated.
    int GetPos(const std::wstring &csPmpt, int &nDefault,
               CKS::LocationPtr &pLocation, int nCurType = 0,
               const CKSCoordArray *paPoints = NULL, int nCurAnchor = 0,
               bool bPosSnap = true, ULONG ulFuncs = CKS::GPDefault,
               ULONG ulMenu = 0, CKSAnim* pAnim = NULL);

    // @cmember Invoke Universal Position Menu and wait until a 3-D position
    //  in space is indicated.
    int GetPos(const std::wstring &csPmpt, int &nDefault, CKSCoord &rCoord,
               int nCurType = 0, const CKSCoordArray *paPoints = NULL,
               int nCurAnchor = 0, bool bPosSnap = true,
               ULONG ulFuncs = CKS::GPDefault, ULONG ulMenu = 0,
               CKSAnim *pAnim = NULL);

    // @cmember Invoke specified position mechanism and wait until a 3-D position
    //  in space is indicated.
    int GetPosMethod(const std::wstring &csPmpt, int nOption,
                     CKS::LocationPtr &pLocation, bool bPosSnap = true);

    // @cmember Get the Corner extents for a window
    int GetWindowCorners(CKSCoord &ckcLowerLeftCorner, CKSCoord &ckcUpperRightCorner,
                         int nViewport);

    // @cmember Define window with rubber-banding and return the corner extents.
    int GetWindow(const std::wstring &csFirst, const std::wstring &csSecond,
                  const std::wstring &csMenu, CKSCoordArray &ackcCoord,
                  int *nViewPort, ULONG ulFlags = CKS::GMDefault,
                  int nDefault = 0);

    // @cmember Define polygon with rubber-banding and return the positions.
    int GetPolygon(const std::wstring &csPrompt, CKSCoordArray &ackcCoord,
                   int *nViewPort);

    // @cmember Get the position and matrix
    int GetPosMatrix(const std::wstring &csPmpt, CKSMatrix &rMatrix,
                     UINT nModType = ModDefault,
                     const std::wstring *pMenu = NULL, ULONG ulFuncs = 0,
                     int nDefault = 0);

    // @cmember Get the position and matrix
    int GetPosMatrix(const std::wstring &csPmpt, CKSMatrixArray &aMatrix,
                     const std::vector<UINT> &aModTypes,
                     const std::wstring *pMenu = NULL, ULONG ulFuncs = 0,
                     int nDefault = 0);

    // @cmember Get the position and matrix
    int GetPosMatrix(const std::wstring &csPmpt, CKSModifierAnim *pAnim,
                     const std::wstring *pMenu = NULL, ULONG ulFuncs = 0,
                     int nDefault = 0);

// @Group Layout Functions

    // @cmember Makes a copy of a layout with the given attributes
    int CopyLayout(const CKSLayout &rOriginal, const std::wstring &csName,
                   const std::wstring &csDescription, double dXsize,
                   double dYsize, double dScale, bool bBorder,
                   CKSLayout &rCopy);

    // @cmember Deletes the given layout from the part
    int DeleteLayout(CKSLayout &rLayout);

    // @cmember Retrieves an array of handles for all instance-specific entities
    //  within the given instnace.
    int GetInstanceGeometry(const CKSDrawInst &pInstance,
                            CKSEntityArray &aGeometry);

    // @cmember Retrieves an array of handles for all entities tagged to
    //  the given instnace.
    int GetTaggedGeometry(const CKSDrawInst &pInstance,
                          CKSEntityArray &aGeometry);

    // @cmember Gets a list of modified entities in the instance.
    int GetInstanceModifications(const CKSDrawInst &rInst,
                                 CKSDrawInstModArray &rModList,
                                 UCHAR ucMask);

    // @cmember Gets a list of the instances in a given layout.
    int GetInstances(UCHAR ucMode, CKSLayout &rLayout,
                     CKSDrawInstArray &aInstances);

    // @cmember Get a list of instance aligned to a given instance.
    int GetInstAlignments(CKSDrawInst &pInst,
                          CKSDrawInstArray &aInstances,
                          std::vector<double> &aAlignAngles);

    int GetInstAttributes(CKSDrawInst &rInst, CKSCoord &ckscBase,
                          double &dScale, double &dRotation,
                          double &dWidth, double &dHeight,
                          bool &bFrozen, bool &bDrawBorder,
                          CKS::Rendering &ucRendering, CKSMatrix *pViewMat,
                          CKSLevelArray *paLevels, CKEntityAttrib *pAttrib,
                          CKSMatrix *pMatrix, CKSLevel *pLevel,
                          CKS::ThreadRendering *pucThreadRender,
                          std::wstring *pcsName, bool *pbPHLV5Display,
                          bool *pbCircularBorder, CKSCoord *pckscVCenter,
                          bool *pbDisplayModelDetails);

    int GetInstAttributes(CKSDrawInst &rInst, CKSCoord &ckscBase,
                          double &dScale, double &dRotation,
                          double &dWidth, double &dHeight,
                          bool &bFrozen, bool &bDrawBorder,
                          CKS::Rendering &ucRendering, CKSMatrix *pViewMat,
                          CKSLevelArray *paLevels, CKEntityAttrib *pAttrib,
                          CKSMatrix *pMatrix, CKSLevel *pLevel,
                          CKS::ThreadRendering *pucThreadRender,
                          std::wstring *pcsName, int *pnPHLV5Display,
                          bool *pbCircularBorder, CKSCoord *pckscVCenter,
                          bool *pbDisplayModelDetails,
                          CKS::WireRendering *pucWireRender);

    // @cmember Get attributes of an instance in layout mode
    int GetInstAttributes(CKSDrawInst &rInst, CKSCoord &ckscBase,
                          double &dScale, double &dRotation,
                          double &dWidth, double &dHeight,
                          bool &bFrozen, bool &bDrawBorder,
                          CKS::Rendering &ucRendering,
                          CKSMatrix *pViewMat = NULL,
                          CKSLevelArray *paLevels = NULL,
                          CKEntityAttrib *pAttrib = NULL,
                          CKSMatrix *pMatrix = NULL,
                          CKSLevel *pLevel = NULL,
                          CKS::ThreadRendering *pucThreadRender = NULL,
                          std::wstring *pcsName = NULL,
                          bool *pbPHLV5Display = NULL,
                          bool *pbCircularBorder = NULL,
                          CKSCoord *pckscVCenter = NULL,
                          bool *pbDisplayModelDetails = NULL,
                          CKS::WireRendering *pucWireRender = NULL);

    //@cmember Get the HLR attributes for a Drawing Instance
    int GetInstanceHLRAttributes(CKSDrawInst &pInst,
                                 bool *pbShowTangentLines = NULL,
                                 CKBasicAttrib *pattrExt = NULL,
                                 CKBasicAttrib *pattrVis = NULL,
                                 CKBasicAttrib *pattrHid = NULL,
                                 CKBasicAttrib *pattrVisTan = NULL,
                                 CKBasicAttrib *pattrHidTan = NULL,
                                 CKS::Rendering *pucRendering = NULL,
                                 bool *pbPHLV5Display = NULL,
                                 CKS::WireRendering *pucWireRender = NULL);

    // @cmember Get the attributes of a specific layout.
    int GetLayoutAttrib(const CKSLayout &rLayout,
                        std::wstring    &csName,
                        std::wstring    &csDescription,
                        double          *pdXSize = NULL,
                        double          *pdYSize = NULL,
                        double          *pdScale = NULL,
                        CKSLevelArray   *paLevels = NULL,
                        bool            *pbDrawBorder = NULL);

    // @cmember Gets a list of the layouts in the current part.
    int GetLayouts(UCHAR ucMode, CKSLayoutArray &aLayouts);

    // @cmember Tells if the current part is in layout mode or not.
    int InLayoutMode();

    // @cmember Determins if a given entity is layout specific or not.
    int LayoutSpecific(const CKSEntity &pEntity, CKSLayout &rLayout);

    // @cmember Convert an instance point to the coordinates of model-mode.
    int LayoutToModel(const CKSDrawInst &rInst, CKSCoord &ckscPoint);

    // @cmember Loads the given layout
    int LoadLayout(CKSLayout &rLayout, bool bQuickOpen = false);

    // @cmember Makes the given entity a layout specific entity.
    int MakeLayoutSpecific(CKSEntity &pEntity, CKSLevel &rLayoutLevel);

    // @cmember Modelize an entire layout
    int ModelizeLayout(CKSLayout &rLayout);

    // @cmember Modelize an entire instance
    int ModelizeInstance(CKSDrawInst &rInst);

    // @cmember Modelize a list of entities in an instance
    int ModelizeEntities(CKSEntityArray &apEnts, CKSDrawInst &rInst);

    // @cmember Convert a model-mode point to the coordinates of an instance.
    int ModelToLayout(const CKSDrawInst &rInst, CKSCoord &ckscPoint);

    // @cmember Add modifications to the provided entities in an instance
    int ModifyInstEnts(CKSDrawInst &rDrawInst, CKSEntityArray &aEnts,
                       ULONG *pBlank, const CKBasicAttrib *pAttrib = NULL);

#ifndef CADKEY_VIEWER
    // @cmember Add a new section view to this part.
    int ModifySectionView(CKSDrawInst  &pSectionView,
                          bool         *bShowLabel,
                          std::wstring *csViewText,
                          bool         *bProjected,
                          double       *dScale,
                          bool         *bScaleDetailsToo,
                          bool         *bDrawScaleNote,
                          bool         *bDrawHatches,
                          bool         *bIsPartialView,
                          bool         *bDrawHiddenLines,
                          bool         *bTangentLines,
                          bool         *bDashHiddenLines,
                          bool         *bScaleNoteHalfHeight = nullptr);
#endif

    // @cmember Re-process a layout to make sure it's up to date with the model
    int CKPart::ReProcessLayout(CKSLayout &rLayout);

    // @cmember Sets attributes of an instance in layout mode
    int SetInstAttributes(CKSDrawInst &rInst, CKSCoord *ckscBase = NULL,
                          double *dScale = NULL, double *dRotation = NULL,
                          double *dWidth = NULL, double *dHeight = NULL,
                          bool *bFrozen = NULL, bool *bDrawBorder = NULL,
                          CKS::Rendering *pucRendering = NULL,
                          CKSMatrix *pViewMat = NULL,
                          CKSLevelArray *paLevels = NULL,
                          CKEntityAttrib *pAttrib = NULL,
                          CKSLevel *pLevel = NULL,
                          CKS::ThreadRendering *pucThreadRender = NULL,
                          const std::wstring *pcsName = NULL,
                          bool *pbPHLV5Display = NULL,
                          bool *pbCircularBorder = NULL,
                          bool *pbDisplayModelDetails = NULL,
                          CKS::WireRendering *pucWireRender = NULL);

    // @cmember Set the HLR attributes for a Drawing Instance
    int SetInstanceHLRAttributes(CKSDrawInst &pInst,
                                 bool *pbShowTangentLines = NULL,
                                 CKBasicAttrib *pattrExt = NULL,
                                 CKBasicAttrib *pattrVis = NULL,
                                 CKBasicAttrib *pattrHid = NULL,
                                 CKBasicAttrib *pattrVisTan = NULL,
                                 CKBasicAttrib *pattrHidTan = NULL,
                                 CKS::Rendering *pucRendering = NULL,
                                 bool *pbPHLV5Display = NULL,
                                 CKS::WireRendering *pucWireRendering = NULL);

    int SetInstanceHLRAttributes(CKSDrawInst &pInst,
                                 bool *pbShowTangentLines,
                                 CKBasicAttrib *pattrExt,
                                 CKBasicAttrib *pattrVis,
                                 CKBasicAttrib *pattrHid,
                                 CKBasicAttrib *pattrVisTan,
                                 CKBasicAttrib *pattrHidTan,
                                 CKS::Rendering *pucRendering,
                                 int *pnPHLV5Display,
                                 CKS::WireRendering *pucWireRendering);

    // @cmember Allows for selection of instance depiction geometry
    int SelInstEnt(const std::wstring &csPmpt, CKSDrawInst &rInst,
                   CKSEntity &rEnt, ULONG ulOptions = 0);

    // @cmember Set the margin around the drawing instance
    int SetInstBorderFlags(CKSDrawInst &rInst,
                           int *pnMargin = NULL,
                           bool *pbAutoFit = NULL,
                           bool *pbCenterGeometry = NULL,
                           bool *pbDrawBorder = NULL);

    // @cmember Set the center of the drawing instance view.
    int SetInstViewCenter(CKSDrawInst &rpInst,
                          CKS::Location *cksLocCenter = NULL,
                          CKSCoord *ckscCenter = NULL);

    // @cmember Sets attributes of a layout
    int SetLayoutAttrib(CKSLayout &rLayout, const std::wstring *pcsName,
                        const std::wstring *pcsDescription = NULL,
                        double *pdXSize = NULL, double *pdYSize = NULL,
                        double *pdScale = NULL, bool *pbInches = NULL);

    // @cmember Tags an entity to an instance.
    int TagEntity(CKSEntity &pEntity, CKSDrawInst &pInstance);

    // @cmember Tags a set of entities to an instance.
    int TagGeometry(CKSEntityArray &aEntities, CKSDrawInst &pInstance);

    // @cmember Toggles the layout paper border on and off.
    int ToggleLayoutBorder();

    // @cmember Untags an entity from an instance.
    int UnTagEntity(CKSEntity &pEntity, CKSDrawInst &pInstance);

    // @cmember Untags a set of entities from an instance.
    int UnTagGeometry(CKSEntityArray &aEntities, CKSDrawInst &pInstance);

// @Group Table Manipulation Functions
    // @cmember Append a row of entity pointers to a Table entity.
    int TableAppendRow(CKSEntity &rEntity, CKSEntityArray &aEntities);

    // @cmember Get information about an existing table entity
    int GetTable(CKSEntity &rEntity,
                 size_t *punColumns = NULL,
                 CKStringArray *plcsHeaders = NULL,
                 CKStringArray *plcsDisplayedHeaders = NULL,
                 std::vector<double> *padWidths = NULL,
                 double *pdRowSpacing = NULL,
                 double *pdColSpacing = NULL,
                 bool *pbTopDown = NULL,
                 std::vector<int> *pWidthBehaviours = NULL,
                 std::vector<bool> *pbDisplayFlags = NULL,
                 CKS::LocationPtr *pTableLoc = NULL,
                 CKSDetailOptions *pOptions = NULL,
                 int *pnDispView = NULL,
                 CKSMatrix *pMatrix = NULL);

    // @cmember Modify an existing table entity
    int ModifyTable(CKSEntity &rEntity,
                    const UINT *punColumns = NULL,
                    const CKStringArray *plcsHeaders = NULL,
                    const std::vector<double> *padWidths = NULL,
                    const double *pdRowSpacing = NULL,
                    const double *pdColSpacing = NULL,
                    const bool *pbTopDown = NULL,
                    const std::vector<int> *pWidthBehaviours = NULL,
                    const std::vector<bool> *pbDisplayFlags = NULL,
                    const CKS::LocationPtr *pTableLoc = NULL,
                    const CKSDetailFormat *pFormat = NULL,
                    const int *pnDispView = NULL,
                    const CKSMatrix *pMatrix = NULL);

    // @cmember Add holes to an existing hole table
    int AddHolesToTable(CKSEntity &rEntity,
                        CKSEntityArray &aEntities);

    // @cmember Set the reference point in a hole table
    int SetHoleTableLabelDistance(CKSEntity &rEntity,
                           double dDistance,
                           bool bValue);

    // @cmember Set the reference point in a hole table
    int SetHoleTableRefPnt(CKSEntity &rEntity,
                           CKS::Location *pReference,
                           const bool bPlaceTarget = false);

    // @cmember Modify the legend of the hole table
    int ModifyHoleTableLegend(CKSEntity &rTable, const bool *pbDisplay = NULL,
                              const CKS::Location *pTableLoc = NULL,
                              const double *pdRowSpacing = NULL,
                              const double *pdColSpacing = NULL,
                              const bool *pbTolCol = NULL,
                              const bool *pbQtyCol = NULL);

    // @cmember Add holes to an existing hole table
    int RemoveHolesFromTable(CKSEntity &rEntity,
                             CKSEntityArray &aEntities);

// @Group Configuration Data
    // @cmember Set part parameters.
    int Set(int nParameter, int nData);

    // @cmember Set part parameters.
    int Set(int nParameter, ULONG ulData);

    // @cmember Set part parameters.
    int Set(int nParameter, double dData);

    // @cmember Set part parameters.
    int Set(int nParameter, double dData1, double dData2, double dData3);

    // @cmember Set part parameters.
    int Set(int nParameter, double dData1, double dData2,
            double dData3, double dData4);

    // @cmember Set one or more colors in the color palette
    int SetPalette(std::vector<COLORREF> &arcColors, int nStart = 0,
                   int nCount = 64);

    // @cmember Set the RGB value of a part special color.
    int SetColorValue(Color nValue, COLORREF crValue);

    // @cmember Set the units and tolerances for the part.
    int SetPartUnitsTolerances(int nUnits, double dSplineTol,
                               double dCoincidentDist, double dNormalDev,
                               double dMaximumEdgeLen,
                               double dMaximumCurveLen,
                               double dCurveNormalDev, bool bUseShellEdges);

    // @cmember Get part parameters.
    int Get(int nParameter, int &nData);

    // @cmember Get part parameters.
    int Get(int nParameter, ULONG &lData);

    // @cmember Get part parameters.
    int Get(int nParameter, double &dData);

    // @cmember Get part parameters.
    int Get(int nParameter, double &dData1, double &dData2, double &dData3);

    // @cmember Get part parameters.
    int Get(int nParameter, double &dData1, double &dData2,
            double &dData3, double &dData4);

    // @cmember Get one or more colors in the color palette
    int GetPalette(std::vector<COLORREF> &arcColors, int nStart = 0,
                   int nCount = 64);

    // @cmember Get the RGB value of a part color.
    COLORREF GetColorValue(Color nValue);

    // @cmember Get the units and tolerances for the part.
    int GetPartUnitsTolerances(int &nUnits, double &dSplineTol,
                               double &dCoincidentDist, double &dNormalDev,
                               double &dMaximumEdgeLen,
                               double &dMaximumCurveLen,
                               double &dCurveNormalDev, bool &bUseShellEdges);

    // @cmember Loads a detail settings file (*.dim) into the part as the
    //  active detail settings.
    int LoadDetailSettings(const std::wstring &csFileName = std::wstring());

    // @cmember Sets the active detail text formatting for the part.
    int SetDetailFormat(CKMaskTypes nType, CKSDetailFormat &detFormat,
                         CKSEntity *pDetailEnt = NULL);

    // @cmember Gets the active detail text formatting for the part.
    int GetDetailFormat(CKMaskTypes nType, CKSDetailFormat &detFormat,
                        CKSEntity *pDetailEnt = NULL);

    // @cmember Sets the active detail units for the part.
    int SetDetailUnits(CKMaskTypes nType, CKSDetailUnits &detFormat, bool bDual = false,
                         CKSEntity *pDetailEnt = NULL);

    // @cmember Gets the active detail units for the part.
    int GetDetailUnits(CKMaskTypes nType, CKSDetailUnits &detFormat, bool bDual = false,
                       CKSEntity *pDetailEnt = NULL);

    // @cmember Sets the active detail units for the part.
    int SetDetailLines(CKMaskTypes nType, CKSDetailLines &detFormat,
                         CKSEntity *pDetailEnt = NULL);

    // @cmember Gets the active detail units for the part.
    int GetDetailLines(CKMaskTypes nType, CKSDetailLines &detFormat,
                       CKSEntity *pDetailEnt = NULL);

    // @cmember Sets the active detail units for the part.
    int SetDetailDimText(CKMaskTypes nType, CKSDetailDimText &detFormat,
                         CKSEntity *pDetailEnt = NULL);

    // @cmember Gets the active detail units for the part.
    int GetDetailDimText(CKMaskTypes nType, CKSDetailDimText &detFormat,
                         CKSEntity *pDetailEnt = NULL);

    // @cmember Refresh the display of a dimension.
    int RefreshDimension(const CKSEntity &pDimension);

    // @cmember Update dimensions to use the current detail settings
    int UpdateDetailEnts(const CKSEntityArray &aEntities);

    // @cmember Get the part's standard properties
    int GetStandardProperties(std::vector<std::wstring> &acsProperties,
                              __time64_t &tCreation, __time64_t &tModification,
                              std::wstring &csLastSavedApp);

    // @cmember Set the part's standard properties
    int SetStandardProperties(std::vector<std::wstring> &acsProperties);

    // @cmember Get the part's user properties
    int GetUserProperties(std::map<std::wstring, std::wstring> &mapProperties);

    // @cmember Set the part's user properties
    int SetUserProperties(std::map<std::wstring, std::wstring> &mapProperties);

    // @cmember Get the file's standard properties
    int GetFileStandardProperties(std::vector<std::wstring> &acsProperties,
                                  __time64_t &tCreation,
                                  __time64_t &tModification,
                                  std::wstring &csLastSavedApp);

    // @cmember Set the file's standard properties
    int SetFileStandardProperties(std::vector<std::wstring> &acsProperties);

    // @cmember Get the file's user properties
    int GetFileUserProperties(std::map<std::wstring, std::wstring> &mapProperties);

    // @cmember Set the file's user properties
    int SetFileUserProperties(std::map<std::wstring, std::wstring> &mapProperties);

    // @cmember Get an entity's standard properties
    int GetEntityProperties(const CKSEntity &pEntity,
                            std::wstring &csName,
                            std::vector<std::wstring> &acsStdProperties,
                            std::vector<std::wstring> &acsUserProperties);

    // @cmember Set an entity's standard properties
    int SetEntityProperties(CKSEntityArray &apEntities,
                            const std::wstring &csName,
                            const std::vector<std::wstring> &acsStdProperties,
                            const std::vector<std::wstring> &acsUserProperties);

    // @cmember Get the Active drawing attributes
    int GetActiveAttrib(CKEntityAttrib &rAttrib);

    // @cmember Get the active options for dimension entities
    int GetActiveAttrib(CKSDimensionOptions &rDimOptions, UCHAR ucMask);

    // @cmember Get the active options for note and other detail entities
    int GetActiveAttrib(CKSDetailOptions &rOptions, UCHAR ucMask);

    int PaintFormat(CKSEntity &rSourceEnt,
                    CKSEntity &rChangeEnt);

// @Group Group Functions
    // @cmember Create a Group
    int AddGroup(const std::wstring &csGroupName, int &nGroupNum);

    // @cmember Get the name of a group
    int GetGroup(int nGroupNum, std::wstring &csGroupName);

    // @cmember Delete the information pertaining to a group
    int DeleteGroup(int nGroupNum, int nSubGroupNum = 0);

    // @cmember Renames an existing group
    int RenameGroup(int nGroupNum, const std::wstring &csGroupName);

    // @cmember Adds an entity to a group
    int AddToGroup(int nGroupNum, int nSubGroupNum, CKSEntity &pEntity);

    // @cmember Adds entities to a group
    int AddToGroup(int nGroupNum, int nSubGroupNum, CKSEntityArray &aEntities);

    // @cmember Removes an entity from its group
    int RemoveFromGroup(CKSEntity &pEntity);

    // @cmember Removes entities from their groups
    int RemoveFromGroup(CKSEntityArray &aEntities);

// @Group Copious Functions
    // @cmember Create a copious entity.
    int AddCopious(int nTypeCode, CKSCopious &rCopious);

    // @cmember Delete a copious entity.
    int DeleteCopious(CKSCopious &rCopious);

    // @cmember Get the copious type code corresponding to a particular
    // copious type name.
    int CopiousGetType(const std::wstring &csName, bool bCreate);

    // @cmember Get the copious type name corresponding to a particular
    // copious type code.
    int CopiousGetType(int nTypeCode, std::wstring &csName);

    // @cmember Get the copious type id corresponding to a particular
    // copious entity.
    int CopiousGetType(const CKSCopious &rCopious, int &nTypeCode);

    // @cmember Get the copious type name corresponding to a particular
    // copious entity.
    int CopiousGetType(const CKSCopious &rCopious, std::wstring &csName);

    // @cmember Delete a copious type code
    int CopiousDeleteType(int nTypeCode);

    // @cmember Moves the read/write pointer in a copious entity.
    int CopiousMove(const CKSCopious &rCopious, int nOffset, int nStartPos);

    // @cmember Gets the size of a copious entity's data.
    int CopiousGetSize(const CKSCopious &rCopious, ULONG &ulSize);

    // @cmember Changes the size of a copious entity's data.
    int CopiousSize(CKSCopious &rCopious, ULONG ulSize);

// @Group Reading Copious Data
    // @cmember Read a character from a copious entity
    int CopiousRead(const CKSCopious &rCopious, char &cData);

    // @cmember Read an unsigned character from a copious entity
    int CopiousRead(const CKSCopious &rCopious, UCHAR &ucData);

    // @cmember Read a short from a copious entity
    int CopiousRead(const CKSCopious &rCopious, short &sData);

    // @cmember Read an unsigned short from a copious entity
    int CopiousRead(const CKSCopious &rCopious, USHORT &usData);

    // @cmember Read a long from a copious entity
    int CopiousRead(const CKSCopious &rCopious, long &lData);

    // @cmember Read an unsigned long from a copious entity
    int CopiousRead(const CKSCopious &rCopious, ULONG &ulData);

    // @cmember Read a float from a copious entity
    int CopiousRead(const CKSCopious &rCopious, float &fData);

    // @cmember Read a double from a copious entity
    int CopiousRead(const CKSCopious &rCopious, double &dData);

    // @cmember Read arbitrary data from a copious entity
    int CopiousRead(const CKSCopious &rCopious, UINT unBytes, PBYTE pData);

    // @cmember Read an entity handle from a copious entity
    int CopiousRead(const CKSCopious &rCopious, CKSEntity &pEntity);

    // @cmember Read a copious handle from a copious entity
    int CopiousRead(const CKSCopious &rCopious, CKSCopious &rHandle);

    // @cmember Read a std::wstring from a copious entity
    int CopiousRead(const CKSCopious &rCopious, std::wstring &csData);

// @Group Writing Copious Data
    // @cmember Write a character to a copious entity
    int CopiousWrite(CKSCopious &rCopious, char cData);

    // @cmember Write an unsigned character to a copious entity
    int CopiousWrite(CKSCopious &rCopious, UCHAR ucData);

    // @cmember Write a short to a copious entity
    int CopiousWrite(CKSCopious &rCopious, short sData);

    // @cmember Write an unsigned short to a copious entity
    int CopiousWrite(CKSCopious &rCopious, USHORT usData);

    // @cmember Write a long to a copious entity
    int CopiousWrite(CKSCopious &rCopious, long lData);

    // @cmember Write an unsigned long to a copious entity
    int CopiousWrite(CKSCopious &rCopious, ULONG ulData);

    // @cmember Write a float to a copious entity
    int CopiousWrite(CKSCopious &rCopious, float fData);

    // @cmember Write a double to a copious entity
    int CopiousWrite(CKSCopious &rCopious, double dData);

    // @cmember Write arbitrary data to a copious entity
    int CopiousWrite(CKSCopious &rCopious, UINT unBytes, PBYTE pData);

    // @cmember Write an entity handle to a copious entity
    int CopiousWrite(CKSCopious &rCopious, const CKSEntity &pEntity);

    // @cmember Write a copious entity handle to a copious entity
    int CopiousWrite(CKSCopious &rCopious, const CKSCopious &rHandle);

    // @cmember Write a std::wstring to a copious entity
    int CopiousWrite(CKSCopious &rCopious, const std::wstring &csData);

// @Group Rollback System Functions
    // @cmember Roll back n states (defaults to 1)
    size_t Undo(size_t nStates = 1);

    // @cmember Roll forward n states (defaults to 1)
    size_t Redo(size_t nStates = 1);

    // @cmember Roll to a particular state in the undo system.
    int RollTo(PVOID hState);

    // @cmember Note a new state in the system.
    int NoteState();

    // @cmember Note a new state in the system.
    int NoteState(PVOID &ulState);

    // This function should only be used when absolutely necessary.
    // In general it should be left to the user to determine when it is
    // appropriate to purge the undo history for a given part.
    int PurgeUndo();

    // This function should only be used when absolutely necessary.
    // In general it should be left to the user to determine when it is
    // appropriate to purge the undo history for a given part.
    int PurgeTo(PVOID ulState);

// @Group Import/Export Functions
      // @cmember Import model geometry from another part.
    int ImportPart(const std::wstring &csFileName,
                   const std::wstring &csPartName,
                   const CKSMatrix &rTransform, int nParentOpt = 0,
                   CKSLevel *pParentLevel = NULL, int nLevelOpt = 0,
                   int nLevelOffset = 0, bool bGroup = false,
                   const std::wstring &csGroup = std::wstring());

    // @cmember Import model geometry from another part and put it into a composite.
    int ImportPart(const std::wstring &csFileName,
                   const std::wstring &csPartName, CKSEntity &rComposite,
                   const CKSMatrix &rTransform, int nParentOpt = 0,
                   CKSLevel *pParentLevel = NULL, int nLevelOpt = 0,
                   int nLevelOffset = 0, bool bGroup = false,
                   const std::wstring &csGroup = std::wstring());

    // @cmember Set options for importing a KeyCreator file
    CKSErrors SetKCImportOptions(int nParentLevelOpt,
                                 const std::wstring &csParentLevel,
                                 int nLevelOpt, bool bMakeComposite,
                                 int nLevelOffset, bool bAnimate,
                                 int nRotateOpt, double dRotateValue,
                                 int nScaleOpt, double dScaleValue,
                                 int dGroupOpt,
                                 const std::wstring &csGroupName);

    // @cmember Set options for importing a STEP file
    CKSErrors SetSTEPImportOptions(bool bScanOnly, bool bSplitSTEPFile,  
                                   bool bReadSolids, bool bReadSheets, 
                                   bool /*bFutureUse*/, bool bReadCurves,
                                   bool bReadHidden, bool bBlankHidden, 
                                   bool bTransfToCPlane, 
                                   int nAttribOpt, bool bTranslateFaceColor, 
                                   int nLevelOpt, 
                                   const std::wstring *pOneEntPerLevStartLev, 
                                   int nAssemblyOpt, int nExtRefDirOpt,
                                   const std::wstring *pDirName, 
                                   bool bLightWeight, bool bAnnotations,
                                   bool bMerge);  

    // @cmember Set options for importing a (CatiaV4, V5, V6, Creo, NX, Inventor, SolidWorks, Solid Edge, Parasolid, JT, Rhino, IFC) files
    CKSErrors SetFileImportOptions(CKS::FileType eFileType, int nAsmOpt, const std::wstring* pDirName, int nExtRefDirOpt, 
                                   bool bReadHidden, int nScaleOpt, double dScale, int nPartRefSearchOpt, bool bMerge,
                                   bool bImpActiveLevel);

    // @cmember Set options for importing a SAT type file
    CKSErrors SetSATImportOptions(bool bLocate, bool bDynamic, int nRefPoint,
                                  int nUseSystemAttributes,
                                  bool bTransformToCPlane,
                                  bool bTranslateFaceColor, int nLevelOpt,
                                  const std::wstring &csEntPerLevelStart,
                                  int nPolygonOpt, int nPolylineOpt);

    // @cmember Set options for importing a STL file
    CKSErrors SetSTLImportOptions(int nCreatePolyOpt);

    // @cmember Set options for importing an IGES file
    CKSErrors SetIGESImportOptions(bool bScanOnly=false, bool bSplitIGESFile=false,  
                                   bool bReadSolids=true, bool bReadSheets=false, 
                                   bool bFutureUse=true, bool bReadCurves=true,
                                   bool bReadAnnotations=true, bool bReadLayouts=true,
                                   bool bReadHidden=true, bool bBlankHidden=false, 
                                   int nDimConvOpt=0, bool bTransfToCPlane=false, 
                                   int nAttribOpt=0, bool bTranslateFaceColor=true, 
                                   const std::wstring *pFontName=NULL, int nLevelOpt=0, 
                                   const std::wstring *pOneEntPerLevStartLev=NULL, 
                                   int nAssemblyOpt=0, int nExtRefDirOpt=0,
                                   const std::wstring *pDirName=NULL, 
                                   bool bLightWeight=true, bool bMerge=true);

    // @cmember Set options for importing a DWG/DXF file
    CKSErrors SetDWGDXFImportOptions(const std::wstring &csDefFont,
                                     int ucDefLineType,
                                     int nUseGenericDimension,
                                     bool bTranslateSpecialChars,
                                     bool bActiveLevel, bool bConvBarPrompt,
                                     bool bEmptyLayout,
                                     bool bImportDetailOptions,
                                     bool bActiveSubLevels = false,
                                     const std::wstring &csImportPrefix = L"ACAD_LAYER_");

    // @cmember Export model geometry into another part
    int ExportPart(const CKSEntityArray &psEntities,
                   const CKSLevelArray &psLevels,
                   const std::wstring &csFilename,
                   const std::wstring &csPartName,
                   const CKSMatrix &rMatrix, int nOption);

    // @cmember Set options for exporting a KeyCreator(KC) file
    CKSErrors SetKCExportOptions(int nEntityOption, bool bRelative);

    // @cmember Set options for exporting a SAT file
    CKSErrors SetSATExportOptions(int nVersion, bool bChooseBase,
                                  bool bExportPlaneVec);

    // @cmember Set options for exporting a DWGDXF file
    CKSErrors SetDWGDXFExportOptions(double dChordTolerance,
                                     const std::wstring &csDefFont,
                                     UCHAR ucVersion,
                                     bool bTranslateSpecialChars,
                                     int nLayoutFromModel, bool bBurstLayout,
                                     bool bSplineAsPolylines,
                                     bool bExportToSingleLayer = false);

    // @cmember Set options for exporting an IGES file
    CKSErrors SetIGESExportOptions(const std::wstring *pAuthorName=NULL, 
                                   const std::wstring *pOrgName=NULL, 
                                   const std::wstring *pProdId=NULL, 
                                   int nSolidOpt=0, int nSurfOpt=0, bool bExpAsWires=false,
                                   bool bExpSurfAsSpln=false, bool bExpEdgeAsSpln=false, 
                                   bool bExpWiresAsSpln=false, bool bRelToCPln=false, 
                                   bool bSplitClosedFacesInTwo=false);

    // @cmember Set options for exporting a Parasolid file
    CKSErrors SetPSExportOptions(int nSaveVersion, int nMachineDependent,
                                 bool bHealModel, bool bVerifyModel,
                                 bool bExportPlaneVec,
                                 bool bChooseBase = false,
                                 bool bExpRelCPln = false);

    // @cmember Set options for exporting a STEP file
    CKSErrors SetSTEPExportOptions(int nWriteFormat, int nConformanceClass,
                                   const std::wstring &csFileName,
                                   const std::wstring &csFileDescription,
                                   const std::wstring &csAuthor,
                                   const std::wstring &csOrganization,
                                   const std::wstring &csAuthorization,
                                   bool bExportPlaneVec,
                                   bool bChooseBase = false,
                                   bool bExpRelCPln = false,
                                   bool bUseBodyColorForFace = false);

    // @cmember Set options for exporting a CGM file
    CKSErrors SetCGMExportOptions(bool bBlackAndWhite, int nQuality = 0);

    // @cmember Set options for exporting a Image file
    CKSErrors SetImageExportOptions(int nResolution, bool bBlackAndWhite);

    // @cmember Set options for exporting a CatiaV5 file
    CKSErrors SetCatiaV5ExportOptions(int nCatia5Version, bool bC5ExpPlnVec,
                                      bool bC5BasePosOpts = false,
                                      bool bC5RelCPln = false);

// @Group Viewport Manipution
    // @cmember Double the scale of a viewport
    int ScaleDouble(int nViewport = -1);

    // @cmember Halve the scale of a viewport
    int ScaleHalf(int nViewport = -1);

    // @cmember Halve the scale of a viewport
    int ScalePercent(double dPercent, int nViewport = -1);

    // @cmember Automatically set the scale of a viewport
    int ScaleAuto(int nViewport = -1);

    // @cmember Set the scale of a viewport
    int ScaleSet(double dScale, int nViewport = -1);

    // @cmember Set the scale of a viewport
    int ScaleSet(double dScale, const CKSCoord &ckscCenter,
                 int nViewport = -1);

    // @cmember Set the window to a particular region
    int Window(const CKSCoord &ckscCorner1, const CKSCoord &ckscCorner2,
               int nViewport = -1);

    // @cmember Pan a viewport to the left
    int PanLeft(double dPercent, int nViewport = -1);

    // @cmember Pan a viewport to the right
    int PanRight(double dPercent, int nViewport = -1);

    // @cmember Pan a viewport up
    int PanUp(double dPercent, int nViewport = -1);

    // @cmember Pan a viewport down
    int PanDown(double dPercent, int nViewport = -1);

    // @cmember Rotate a viewport to the left
    int RotateLeft(double dAngle, int nViewport = -1);

    // @cmember Rotate a viewport to the right
    int RotateRight(double dAngle, int nViewport = -1);

    // @cmember Rotate a viewport up
    int RotateUp(double dAngle, int nViewport = -1);

    // @cmember Rotate a viewport down
    int RotateDown(double dAngle, int nViewport = -1);

    // @cmember Rotate a viewport up
    int RotateCW(double dAngle, int nViewport = -1);

    // @cmember Rotate a viewport down
    int RotateCCW(double dAngle, int nViewport = -1);

    // @cmember Select a viewport layout
    int ViewportLayout(UINT unLayout, UINT unView1 = 0, UINT unView2 = 0,
                       UINT unView3 = 0, UINT unView4 = 0);

    // @cmember Set the display view for a viewport
    int SetView(int nDispView, bool bAutoscale = false, int nViewport = -1);

    // @cmember Set rendering mode for a viewport
    int SetRenderMode(int nMode, int nViewport = -1);

    // @cmember Set wireframe render mode for a viewport
    int SetWireRender(int nMode, int nViewport = -1);

    // @cmember Set silhouette mode for a viewport
    int SetSilhouette(bool bSilhouette, int nViewport = -1);

    // @cmember Set quick hidden line mode for a viewport
    int SetQuickHiddenLine(bool bMode, int nViewport = -1);

    // @cmember Set shadow mode for a viewport
    int SetShadow(bool bShadow, int nViewport = -1);

    // @cmember Set shadow map mode for a viewport
    int SetShadowMap(bool bShadowMap, int nViewport = -1);

    // @cmember Set reflection mode for a viewport
    int SetReflection(bool bReflection, int nViewport = -1);

    // @cmember Set thread render mode for a viewport
    int SetThreadRenderMode(int nMode, int nViewport = -1);

    // @cmember Get a display view's matrix.  Since names are not required
    // to be unique, this will return the first view with the given name.
    int GetDispView(const std::wstring &csName, CKSMatrix &rMatrix);

    // @cmember Get a display view's number.  Since names are not required
    // to be unique, this will return the first view with the given name.
    int GetDispView(const std::wstring &csName, int &nDispNum);

    // @cmember Get a display view's matrix from this part
    int GetDispView(int nDispNum, CKSMatrix &rMatrix);

    // @cmember Get a display view's name from its number.
    int GetDispView(int nDispNum, std::wstring &csDispName);

    // Get the number and name of the active Display View
    int GetActiveDispView(int &nDispNum, std::wstring &csDispName);

    // @cmember Sets the view matrix of a given viewport
    int SetDispViewMatrix(CKSMatrix &rMat, int nVPort = -1);

    // @cmember Sets the view matrix of a given viewport
    int SetDispViewMatrix(CKSEntity &pPlane, int nVPort = -1);

    // @cmember Gets the view matrix of a given viewport
    int GetDispViewMatrix(CKSMatrix &rMat, int nVPort = -1);

    // @cmember Gets the number of the display view for a given viewport
    int GetDispViewNumber(int &nDispView, int nVPort = -1);

    // @cmember Select a viewport
    int SelViewport(const std::wstring &csPmpt, int &nViewport,
                    bool bCurrent = false);

    // @cmember Get rendering mode for a viewport
    int GetRenderMode(int &nMode, int nViewport = -1);

    // @cmember Get wireframe render mode for a viewport
    int GetWireRender(int &nMode, int nViewport = -1);

    // @cmember Get silhouette mode for a viewport
    int GetSilhouette(bool &bSilhouette, int nViewport = -1);

    // @cmember Get quick hidden line mode for a viewport
    int GetQuickHiddenLine(bool &bMode, int nViewport = -1);

    // @cmember Get shadow mode for a viewport
    int GetShadow(bool &bShadow, int nViewport = -1);

    // @cmember Get shadow map mode for a viewport
    int GetShadowMap(bool &bShadowMap, int nViewport = -1);

    // @cmember Get reflection mode for a viewport
    int GetReflection(bool &bReflection, int nViewport = -1);

    // @cmember Get thread render mode for a viewport
    int GetThreadRenderMode(int &nMode, int nViewport = -1);

    // @cmember Get display performance for a viewport
    int GetDisplayPerformance(double &dFramesPerSec, int nViewport = -1);

// @Group variable functions
    // @cmember Creates a variable
    int MakeVariable(const std::wstring &csName, CKSCADLVarType nType,
                     const std::vector<size_t> *pDims = NULL);

    // @cmember Clears a variable from memory
    int ClearVariable(const std::wstring &csName);

    // @cmember Clears variables from memory
    int ClearVariables(std::vector<std::wstring> &acsNames,
                       std::wstring *pBadName = NULL);

    // @cmember Clears variables from memory
    int ClearAllVariables(bool bPartSpecific);

    // @cmember Get the names of all the KXL variables.
    void GetAllVariableNames(std::vector<std::wstring> &acsNames,
                             bool bWantPart = true, bool bWantGlobal = true);

    // @cmember Get the value of a double variable
    int GetVariable(const std::wstring &csName, double &dValue);

    // @cmember Get the value of a double array variable
    int GetVariable(const std::wstring &csName, std::vector<double> &adValues);

    // @cmember Get the value of an integer variable
    int GetVariable(const std::wstring &csName, ptrdiff_t &nValue);

    // @cmember Get the value of an integer array variable
    int GetVariable(const std::wstring &csName, std::vector<ptrdiff_t> &anValues);

    // @cmember Get the value of an CKSEntity variable
    int GetVariable(const std::wstring &csName, CKSEntity &pEntity);

    // @cmember Get the value of an CKSEntity array variable
    int GetVariable(const std::wstring &csName, CKSEntityArray &aEntities);

    // @cmember Get the value of a string variable
    int GetVariable(const std::wstring &csName, std::wstring &csValue);

    // @cmember Get the values of a string list or string array variable
    int GetVariable(const std::wstring &csName,
                    std::vector<std::wstring> &acsValues);

    // @cmember Put the value of a double variable
    int PutVariable(const std::wstring &csName, double dValue);

    // @cmember Put the value of a double array variable
    int PutVariable(const std::wstring &csName,
                    const std::vector<size_t> &anDims,
                    const std::vector<double> &adValues);

    // @cmember Put the value of an integer variable
    int PutVariable(const std::wstring &csName, ptrdiff_t nValue);

    // @cmember Put the value of an integer array variable
    int PutVariable(const std::wstring &csName,
                    const std::vector<size_t> &anDims,
                    const std::vector<ptrdiff_t> &anValues);

    // @cmember Put the value of a string variable
    int PutVariable(const std::wstring &csName, const std::wstring &csValue);

    // @cmember Put the values of a string list or string array variable
    int PutVariable(const std::wstring &csName,
                    const std::vector<size_t> &anDims,
                    const std::vector<std::wstring> &acsValues);

    // @cmember Provides information about a variable
    int InquireVariable(const std::wstring &csName, CKSCADLVarType &nType,
                        std::vector<size_t> *pnDimSizes);

// @Group Level manipulation functions
    // @cmember Add a new level to the Part
    CKSLevel AddLevel(CKSLevel *pParent = NULL,
                      const std::wstring *pcsDescriptor = NULL,
                      int nLevelNumber = 0, bool bDisplayed = true,
                      bool bSelectable = true);

    // @cmember Add a new level to a layout
    CKSLevel AddLevel(CKSLayout &pLayout,
                      const std::wstring *pcsDescriptor = NULL,
                      int nLevelNumber = 0, bool bDisplayed = true,
                      bool bSelectable = true);

    // @cmember Add a level to a Parent Level
    int AddLevel(CKSLevel &rLevel, CKSLevel &rcksLevel);

    // @cmember Add a level to a layout
    int AddLevel(CKSLevel &rLevel, CKSLayout &rLayout);

    // @cmember Delete a level from a Part
    int DeleteLevel(CKSLevel &rLevel);

    // @cmember Level information
    int GetLevelInfo(CKSLevel &rLevel, std::wstring *pcksDescriptor = NULL,
                     std::wstring *pcksLevelNumber = NULL,
                     int *pnLevelNumber = NULL,
                     CKSLevel *pParentLevel = NULL,
                     std::wstring *pcsComments = NULL);

    // @cmember Set the level info.
    int SetLevelInfo(CKSLevel &rLevel,
                     const std::wstring *pcsDescriptor = NULL,
                     int *pnLevelNumber = NULL,
                     const std::wstring *pcsComments = NULL);

    // @cmember Get the level's attributes
    int GetLevelAttributes(CKSLevel &rLevel, bool &bDisplayed,
                           bool &bSelectable);

    // @cmember Set the level's attributes
    int SetLevelAttributes(CKSLevel &rLevel, const bool *pbDisplayed,
                           const bool *pbSelectable = NULL);

    // @cmember Set the level attributes on multiple levels
    int SetLevelAttributes(CKSLevelArray &aLevels, const bool *pbDisplayed,
                           const bool *pbSelectable = NULL);

    // @cmember Get the level's basic attributes
    int GetLevelAttributes(CKSLevel &rLevel, CKBasicAttrib &rAttrib);

    // @cmember Set the level's basic attribues
    int SetLevelAttributes(CKSLevel &rLevel, CKBasicAttrib &rAttrib);

    // @cmember Move entity to level
    int MoveToLevel(CKSLevel &rLevel, CKSEntity &pEntity);

    // @cmember Move entities to a level
    int MoveToLevel(CKSLevel &rLevel, CKSEntityArray &aEntities);

    // @cmember Move level to another level
    int MoveToLevel(CKSLevel &rParent, CKSLevel &rLevel);

    // @cmember Move an array of levels to another level
    int MoveToLevel(CKSLevel &rLevel, CKSLevelArray  &aLevels);

    // @cmember Get the level that owns an entity
    int GetEntityLevel(CKSEntity &pEntity, CKSLevel &rLevel);

    // @cmember Get back a level after providing it's name
    CKSLevel GetLevelByName(const std::wstring &csLevel, CKSLayout &pLayout);

    // @cmember Get a level pointer given a string containing a level number.
    CKSLevel GetLevelByNumber(const std::wstring &csLevel,
                              const CKSLayout *pLayout = NULL,
                              bool bCreate = true);

    // @cmember Retrieves the child level having the given number.
    CKSLevel GetChildLevel(CKSLayout &pLayout, int nLevelNumber);

    // @cmember Retrieves the child level having the given number.
    CKSLevel GetChildLevel(CKSLevel &pLevel, int nLevelNumber);

    // @cmember Get all the child levels of a level
    int GetLevels(CKSLevel &rLevel, CKSLevelArray &aLevels);

    // @cmember Get all the child levels of a layout
    int GetLevels(CKSLayout &rLayout, CKSLevelArray &aLevels);

    // @cmember Get all child levels of the Part
    int GetLevels(CKSLevelArray &rPartLevels);

    // @cmember Get all the displayed levels of the Model
    int GetDisplayedModelLevels(CKSLevelArray &rDisplayLevels);

    // @cmember Get all the entity children of a level
    int GetLevelsEntities(CKSLevel &rLevel, CKSEntityArray &aEntities);

    // @cmember Set the active level in a layout
    int SetActiveLevel(CKSLevel &rLevel, CKSLayout &rLayout );

    // @cmember Set the active level for Model Mode
    int SetActiveLevel(CKSLevel &rLevel);

    // @cmember Get the currently active level
    CKSLevel GetActiveLevel();

    // @cmember Prompt the user to select levels.
    int SelLevels(const std::wstring &csPrompt, CKSLevelArray &aLevels,
                  bool bCreate, bool bFirstOnly, const std::wstring &csMenu,
                  bool bFirstButtonIsActiveLevel);

// @Group Part Reference Level Set Manipulation
    // @cmember Create a new level set.
    int LevelSetCreate(const std::wstring &csLevelSetName);

    // @cmember Destroy a level set.
    int LevelSetDestroy(const std::wstring &csLevelSetName);

    // @cmember Get a list of all level set names.
    int LevelSetList(std::vector<std::wstring> &lcsNames);

    // @cmember Rename a level set.
    int LevelSetRename(const std::wstring &csLevelSetName,
                       const std::wstring &csNewName);

    // @cmember Add a level to a level set.
    int LevelSetAdd(const std::wstring &csLevelSetName,
                    const CKSLevel &rLevel);

    // @cmember Add levels to a level set.
    int LevelSetAdd(const std::wstring &csLevelSetName,
                    const CKSLevelArray &aLevels);

    // @cmember Remove a level from a level set.
    int LevelSetRemove(const std::wstring &csLevelSetName,
                       const CKSLevel &rLevel);

    // @cmember Remove levels from a level set.
    int LevelSetRemove(const std::wstring &csLevelSetName,
                       const CKSLevelArray &aLevels);

    // @cmember Get all the levels listed in a level set.
    int LevelSetGetLevels(const std::wstring &csLevelSetName,
                          CKSLevelArray &aLevels);

    // @cmember Get all the levels displayed by references using a level set.
    int LevelSetGetDisplayedLevels(const std::wstring &csLevelSetName,
                                   CKSLevelArray &aLevels);

    // @cmember Does a level set contain a given level.
    int LevelSetContains(const std::wstring &csLevelSetName,
                         const CKSLevel &rLevel);

    // @cmember Does a level set display a given level.
    int LevelSetDisplays(const std::wstring &csLevelSetName,
                         const CKSLevel &rLevel);

    // @cmember Is the saving of the lightweight stream enabled for a level set.
    int LevelSetLightweightEnabled(const std::wstring &csLevelSetName);

    // @cmember Set the flag for enabling the saving of the lightweight stream
    // for a level set.
    int LevelSetEnableLightweightStream(const std::wstring &csLevelSetName,
                                        bool bEnable);

//  @Group Create Solid Bodies Functions

    // @cmember Creates a solid block
    CKSErrors CreateSolidBlock(CKSBody *&pNewBody, double dLength,
                               double dWidth, double dHeight,
                               const CKSCoord &rLowerLeftCorner,
                               const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid cone
    CKSErrors CreateSolidCone(CKSBody *&pNewBody, double dHeight,
                              const CKSCoord &rBaseCenterPoint,
                              double dBaseMajorRadius,
                              double dUpperRadius = 0.0,
                              bool bElliptical = false,
                              double dBaseMinorRadius = 1.0,
                              const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid cylinder
    CKSErrors CreateSolidCylinder(CKSBody *&pNewBody, double dHeight,
                                  const CKSCoord &rBaseCenterPoint,
                                  double dMajorRadius,
                                  bool bElliptical = false,
                                  double dMinorRadius = 1.0,
                                  const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid prism
    CKSErrors CreateSolidPrism(CKSBody *&pNewBody, double dMajRad, double dHeight, int nSides,
                               const CKSCoord &rCenter, bool bElliptical = false,
                               double dMinRad = 1.0, const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid pyramid
    CKSErrors CreateSolidPyramid(CKSBody *&pNewBody, double dMajRad, double dTopRad, double dHeight,
                                 int nSides, const CKSCoord &rCenter, bool bElliptical = false,
                                 double dMinRad = 1.0, const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid sphere
    CKSErrors CreateSolidSphere(CKSBody *&pNewBody, double dRadius,
                                const CKSCoord &rCenter,
                                const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a solid torus
    CKSErrors CreateSolidTorus(CKSBody *&pNewBody, double dMajorRadius,
                               double dMinorRadius, const CKSCoord &rCenter,
                               const CKSMatrix *pMatrix = NULL);

    // @cmember Creates wire bodies from an array of entities
    CKSErrors CreatePlanarWireBodies(CKSBodyArray &aWireBodies,
                                     CKSEntityArray &aEntities,
                                     bool bMustBeClosed = true,
                                     const CKSMatrix *pMatrix = NULL);

    // @cmember Covers one or more closed planar wire bodies with faces
    CKSErrors CreateFaces(CKSFaceArray &aFaces, CKSBodyArray &aWireBodies);

    // @cmember Creates solids by extruding wireframe profile entities
    CKSErrors CreateExtrude(CKSBodyArray &pNewBodyArray,
                            CKSBodyArray &aProfileBodies,
                            const CKSCoord &rVectorBasePoint,
                            const CKSCoord &rDirectionVector,
                            CKS::ExtrudeEndMethod eEndMethod = CKS::ExtrudeByLength,
                            double dDistance = 1.0,
                            CKSBody *pEndBody = NULL,
                            CKSFace *pEndFace = NULL,
                            bool bMidplane = false,
                            double dDraftAngle = 0.0,
                            CKS::ConvexEdges eConvexEdges = CKS::Natural,
                            bool bDraftRepair = false,
                            double dTwistAngle = 0.0,
                            const CKSMatrix *pMatrix = NULL,
                            CKSCoord *pFirstPos = NULL,
                            CKSCoord *pSecondPos = NULL,
                            CKSCoord *pToPos = NULL);

    // @cmember Creates solids by piping wireframe profile entities
    CKSErrors MakePipe(CKSBody *&pNewBody, CKSEntityArray &aGenerator,
                       double dOutDiam, double dInDiam);

    // @cmember Creates solids by revolving wireframe profile entities
    CKSErrors CreateRevolve(CKSBodyArray &pNewBodyArray,
                            CKSBodyArray &aProfileBodies,
                            const CKSCoord &rVectorBasePoint,
                            const CKSCoord &rDirectionVector,
                            const CKSCoord &rRevolveDirectionVector,
                            double dRevolveAngle = 90.0,
                            int nNumSteps = 0,
                            CKSBody *pEndBody = NULL,
                            bool bMidplane = false,
                            double dDraftAngle = 0.0,
                            CKS::ConvexEdges eConvexEdges = CKS::Natural,
                            bool bDraftRepair = false,
                            const CKSMatrix *pMatrix = NULL,
                            CKS::RevolveEndMethod eEndMethod = CKS::RevolveByAngle,
                            CKSCoord *pFirstPos = NULL,
                            CKSCoord *pSecondPos = NULL);

    // @cmember Creates solids by sweeping wireframe profile entities.
    CKSErrors CreateSweep(CKSBodyArray &pNewBodyArray,
                          CKSBodyArray &aProfileBodies,
                          CKSBody *pPathBody,
                          CKSBody *pEndBody = NULL, CKSFace *pEndFace = NULL,
                          double dDraftAngle = 0.0,
                          CKS::ConvexEdges eConvexEdges = CKS::Natural,
                          bool bDraftRepair = false,
                          CKS::MiterMethod eMiterMethod = CKS::MiterNew,
                          double dTwistAngle = 0.0,
                          const CKSMatrix *pMatrix = NULL,
                          CKS::SweepEndMethod eEndMethod = CKS::SweepToEndOfPath,
                          CKSCoord *pFirstPos = NULL,
                          CKSCoord *pSecondPos = NULL);

    // @cmember Creates surface by skinning/lofting
    CKSErrors SkinTopology(CKSBody       *&pNewBody,
                           CKSEntityArray &aProfiles,
                           CKSEntityArray *apGuideCrvs = NULL,
                           CKSEntityArray *apTangentFaces = NULL,
                           std::vector<double> *adTanFactors=NULL,
                           CKSEntityArray *apTanEdges = NULL,
                           bool bMakeSolid=true, bool bAutoOrder=true, 
                           bool bPeriodic=false, bool bClosed=false);

    // @cmember Creates surface by sweeping profile(s) along a path
    CKSErrors CreateMultipleProfileSweep(CKSBody       *&pNewBody,
                                         CKSEntityArray &aProfiles,
                                         CKSEntityArray &apPaths,
                                         bool bRotate=true, 
                                         bool bCoverEnds=false);

    // @cmember Creates surface by sweeping 1 or 2 profiles profiles along 1 o2 2 paths
    CKSErrors DualPathSweptSurf(CKSBody          *&pNewBody,
                                CKSEntityArray   &aCKSProfiles1,
                                CKSEntityArray   &aCKPath1,
                                int               nOrientationOpt,
								bool              bCoverEnds,
                                CKSEntityArray   *aCKSProfiles2,
                                CKSEntityArray   *aCKPath2,
                                CKSEntity        *pCtrlFace);

    // @cmember Creates a new body by revolving an array of wirebody profile
    // entities along a helical path
    CKSErrors CreateHelix(CKSBody *&pNewBody, CKSBody *pProfileBody,
                          CKSCoord &rckcAxisStart, CKSCoord &rckcAxisEnd,
                          double dPitch = 1.0, bool bRightHandedSweep = true,
                          double dTaperAng = 0, const CKSMatrix *pMatrix = NULL);

    // @cmember Creates a linear pattern of bodies in up to 3 directions
    CKSErrors CreateLinearPattern(CKSBodyArray &aBodies,
                                  CKSCoord &ckcDelta1, int nFirstDir,
                                  CKSCoord &ckcDelta2, int nSecondDir,
                                  CKSCoord &ckcDelta3, int nThirdDir);

    // @cmember Creates a linear pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements in up to 3 directions
    CKSErrors CreateLinearPattern(CKSEntityArray &aEntities,
                                  CKSCoord &ckcDelta1, int nFirstDir,
                                  CKSCoord &ckcDelta2, int nSecondDir,
                                  CKSCoord &ckcDelta3, int nThirdDir);

    // @cmember Creates a circular pattern of bodies
    CKSErrors CircularPattern(CKSBodyArray &aBodies, double dAngle,
                              CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                              int nElements, bool bRotate,
                              CKSCoord &ckcRoot, double dRatio,
                              CKSCoord &ckcMajor);

    // @cmember Creates a circular pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements
    CKSErrors CircularPattern(CKSEntityArray &aEntities, double dAngle,
                              CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                              int nElements, bool bRotate,
                              CKSCoord &ckcRoot, double dRatio,
                              CKSCoord &ckcMajor);

    // @cmember Creates a radial pattern of bodies
    CKSErrors RadialPattern(CKSBodyArray &aBodies, double dAngle,
                            CKSCoord &ckcRoot, CKSCoord &ckcNormal,
                            int nRadial, int nAngular, double dSpacing,
                            bool bRotate, double dRatio, CKSCoord &ckcStart);

    // @cmember Creates a radial pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements
    CKSErrors RadialPattern(CKSEntityArray &aEntities, double dAngle,
                            CKSCoord &ckcRoot, CKSCoord &ckcNormal,
                            int nRadial, int nAngular, double dSpacing,
                            bool bRotate, double dRatio, CKSCoord &ckcStart);

    // @cmember Creates a cylindrical pattern of bodies
    CKSErrors CylindricalPattern(CKSBodyArray &aBodies, CKSFace *pCylFace,
                                 CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                                 int nAngular, int nAxial,
                                 double dRingSpacing, bool nStaggered);

    // @cmember Creates a cylindrical pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements
    CKSErrors CylindricalPattern(CKSEntityArray &aEntities, CKSFace *pCylFace,
                                 CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                                 int nAngular, int nAxial,
                                 double dRingSpacing, bool nStaggered);

    // @cmember Creates a spherical pattern of bodies
    CKSErrors SphericalPattern(CKSBodyArray &aBodies,
                               CKSCoord &ckcCenter, CKSCoord &ckcRoot,
                               int nRings, double dSpacing);

    // @cmember Creates a spherical pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements
    CKSErrors SphericalPattern(CKSEntityArray &aEntities,
                               CKSCoord &ckcCenter, CKSCoord &ckcRoot,
                               int nRings, double dSpacing);

    // @cmember Creates a pattern of bodies along an edge
    CKSErrors CurvePattern(CKSBodyArray &aBodies, CKSEdge *pEdge,
                           CKSFace *pFace, int nNumElements, CKSCoord &ckcRoot, 
                           bool bOnEnds, bool bAlignToFace, bool bAlignToCurve,
                           CKSCoord &ckcNormalDir, CKSCoord &ckcTanDir);

    // @cmember Creates a pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements along an edge
    CKSErrors CurvePattern(CKSEntityArray &aEntities, CKSEdge *pEdge,
                           CKSFace *pFace, int nNumElemOpt, int nNumElements, 
                           double dSpacing, CKSCoord &ckcRoot, 
                           bool bOnEnds, bool bAlignToFace, bool bAlignToCurve,
                           CKSCoord &ckcNormalDir, CKSCoord &ckcTanDir);

    // @cmember Creates a pattern of bodies along a face
    CKSErrors FacePattern(CKSBodyArray &aBodies, CKSFace *pFace, int nNumU,
                          int nNumV, CKSCoord &ckcRoot, bool bOnBoundary,
                          bool bFollowSrfNorm, CKSCoord &ckcUDir,
                          CKSCoord &ckcVDir);

    // @cmember Creates a pattern of solids, sheets and solid fasteners, 
    // features, structural shapes and mechanical elements along a face
    CKSErrors FacePattern(CKSEntityArray &aEntities, CKSFace *pFace, int nNumU,
                          int nNumV, CKSCoord &ckcRoot, bool bOnBoundary,
                          bool bFollowSrfNorm, CKSCoord &ckcUDir,
                          CKSCoord &ckcVDir);

    // @cmember Creates a linear pattern of bump faces in up to 3 directions
    CKSErrors CreateLinearPattern(CKSFaceArray &aBodies,
                                  CKSCoord &ckcDelta1, int nFirstDir,
                                  CKSCoord &ckcDelta2, int nSecondDir,
                                  CKSCoord &ckcDelta3, int nThirdDir);

    // @cmember Creates a circular pattern of bump faces
    CKSErrors CircularPattern(CKSFaceArray &aBodies, double dAngle,
                              CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                              int nElements,  bool bRotate,
                              CKSCoord &ckcRoot,
                              double dRatio, CKSCoord &ckcMajor);

    // @cmember Creates a radial pattern of bump faces
    CKSErrors RadialPattern(CKSFaceArray &aBodies, double dAngle,
                            CKSCoord &ckcRoot, CKSCoord &ckcNormal,
                            int nRadial, int nAngular, double dSpacing,
                            bool bRotate, double dRatio, CKSCoord &ckcStart);

    // @cmember Creates a cylindrical pattern of bump faces
    CKSErrors CylindricalPattern(CKSFaceArray &aBodies, CKSFace *pCylFace,
                                 CKSCoord &ckcCenter, CKSCoord &ckcNormal,
                                 int nAngular, int nAxial,
                                 double dRingSpacing, bool nStaggered);

    // @cmember Creates a spherical pattern of bump faces
    CKSErrors SphericalPattern(CKSFaceArray &aBodies, CKSCoord &ckcCenter,
                               CKSCoord &ckcRoot, int nRings, double dSpacing);

    // @cmember Creates a pattern of bump faces along an edge
    CKSErrors CurvePattern(CKSFaceArray &aBodies, CKSEdge *pEdge,
                           CKSFace *pFace, int nNumElements,
                           CKSCoord &ckcRoot, bool bOnEnds,
                           bool bAlignToFace, bool bAlignToCurve,
                           CKSCoord &ckcNormalDir, CKSCoord &ckcTanDir);

    // @cmember Creates a pattern of bump faces along a face
    CKSErrors FacePattern(CKSFaceArray &aBodies, CKSFace *pFace, int nNumU,
                          int nNumV, CKSCoord &ckcRoot, bool bOnBoundary,
                          bool bFollowSrfNorm, CKSCoord &ckcUDir,
                          CKSCoord &ckcVDir);

//  @Group Modify Solids Functions

#ifndef CADKEY_VIEWER
    // @cmember Performs a boolean operation on the solid bodies.
    CKSErrors BooleanSolids(CKSBody *pBlankBody, CKSBodyArray &rToolBodies,
                            CKS::BooleanType &eType);

    // @cmember Performs a boolean operation on solid bodies optionally keeping the original solids
    CKSErrors BooleanKeepSolids(CKSBodyArray &aBlankBodies,
                                CKSBodyArray &aToolBodies, CKS::BooleanType &eType,
                                CKS::BooleanKeepOption eKeepOpt = CKS::KeepNeither);

    // @cmember Separates multiple objects (lumps) that are not physically
    // connected in a single body into distinct bodies.
    CKSErrors SeparateDisjointBody(CKSBody *pDisjointBody,
                                   CKSBodyArray &aNewBodies);

    // @cmember Combines the given bodies into one body that contains all the
    // lumps and wires from the original bodies.
    CKSErrors CombineSolids(CKSBodyArray &aBodies, CKSBody *&pCombinedBody);
#endif

    // @cmember Drills a hole in a face
    CKSErrors Hole(int EndCondition,
                   int PlacementOption,
                   CKSEntity &CKSDrillFace,
                   CKSEntity &CKSFaceToDrillTo,
                   CKSEntity &CKSCircleOrLine,
                   CKSCoord &DrillPosition,
                   double Diameter,
                   double Depth,
                   double Offset);

    CKSErrors GetHoleParams(CKSEntity& rFace,
                            CKSCoord& rCenter,
                            CKSCoord& rAxis,
                            double& rHoleDiameter,
	                        double& rSmallHoleDepth,
	                        double& rLargeHoleDepth,
	                        double& rCounterSinkDiameter,
	                        double& rCounterSinkDepth,
	                        double& rCounterSinkAngle,
	                        double& rBoreDepth,
	                        double& rBoreDiameter,
	                        double& rBottomAngle,
	                        bool& rThroughHole);

    CKSErrors SetHoleParams(CKSEntity& rFace,
                            const CKSCoord& rCenter,
                            const CKSCoord& rAxis,
                            const CKSCoord& rHit,
                            double dHoleDiameter,
	                        double dSmallHoleDepth,
	                        double dLargeHoleDepth,
	                        double dCounterSinkDiameter,
	                        double dCounterSinkDepth,
	                        double dCounterSinkAngle,
	                        double dBoreDepth,
	                        double dBoreDiameter,
	                        double dBottomAngle,
	                        bool bThroughHole,
                            bool bCreateHole);

    // @cmember Trims or breaks a solid
    CKSErrors TrimBreakSolid(int nTrimOrBreak,
                             CKSEntity* pBlank,
                             CKSEntityArray& rTools,
                             const CKSCoord& ckscVec,
                             const CKSCoord& ckscSideToKeep);

    // @cmember Trims or breaks a solid to a set of curves
    CKSErrors TrimBreakSolidToCurves(int nTrimOrBreak,
                                     int nOrientationMethod,
                                     CKSBody *pBody,
                                     const CKSCoord &ckscSidePos,
                                     CKSEntityArray &aCurves,
                                     const CKSCoord &ckscCuttingDirVec,
                                     CKSBodyArray &aBrokenSolids,
                                     bool bTrmBrkOpt = false);

    // @cmember Trims or breaks a solid to a sheet body
    CKSErrors TrimBreakSolidToSheet(int nTrimOrBreak, CKSBody *pBody,
                                    CKSBody *pSheetBody, bool bKeepSheetNormalSide,
                                    CKSBodyArray &aBrokenSolids,
                                    bool bTrmBrkOpt = false);

    // @cmember Trims or breaks a solid to a set of connected faces
    CKSErrors TrimBreakSolidToConnectedFaces(int nTrimOrBreak,
                                             CKSBody *pBody,
                                             CKSFaceArray &paConnectedFaces,
                                             bool bKeepConnectedFacesNormalSide,
                                             CKSBodyArray &aBrokenSolids,
                                             bool bTrmBrkOpt = false);

    // @cmember Trims or breaks a solid to a plane
    CKSErrors TrimBreakSolidToPlane(int nTrimOrBreak,
                                    CKSBody *pBody,
                                    CKSMatrix &cksmPlaneMatrix,
                                    bool bKeepPlaneNormalSide,
                                    CKSBodyArray &aBrokenSolids,
                                    bool bTrmBrkOpt = false);

    // @cmember Trims or breaks a solid to another solid
    CKSErrors TrimBreakSolidToSolid(int nTrimOpt, int nKeepOpt,
                                    bool bUniteBodies, CKSBody *pFirstBody,
                                    CKSCoord &ckscFirstBodyPos,
                                    CKSBody *pSecondBody,
                                    CKSCoord &ckscSecondBodyPos,
                                    bool bTrmBrkOpt = false);

    // @cmember Unstitches all the faces of bodies
    CKSErrors UnstitchBodies(CKSBodyArray &aBodies,
                             int nBodyEditType,
                             int nBodyUnstitchResult);

    // @cmember Unstitches Faces of a body
    CKSErrors UnstitchFaces(CKSFaceArray &aFaces,
                            int nFaceEditType,
                            int nFaceUnstitchResult);

    // @cmember Stitches sheet bodies
    CKSErrors StitchSheetBodies(CKSBodyArray &aSheetBodies,
                                double dStitchTol, bool bMergeFaces=true, 
                                int nCoincidentFacesAction=2);

    // @cmember Modifies a solid by editing a dimension attached to it
    CKSErrors DimensionDrivenEdit(const CKSEntity &rEntity, 
                                  const CKSCoord &ckscPosition, 
                                  double dNewVal,
                                  CKSEntityArray *pFacesToAdd=NULL,
                                  CKSEntityArray *pFacesToRemove=NULL);

// @Group Solids Part Management functions

    // @cmember invokes the part management system.
    // It should be called before making any changes to the model.
    //
    // @comm NOTE: Changes to the model between the calls to StartState and
    // EndState are registered with the part management system, which will
    // take care of updating the wireframe and rendering of the bodies.
    CKSErrors StartState();

    // @cmember Registers the body into the database.
    // @comm All new bodies created have to be registered with the database
    //       for them to be displayed.
    CKSErrors RegisterBody (CKSEntity &pEntity, CKSBody *pNewBody,
                            const CKEntityAttrib *pAttrib = NULL,
                            const CKSMatrix *pMatrix = NULL,
                            CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    //@cmember Registers multiple Bodies into the database
    CKSErrors RegisterBodies (CKSEntityArray &aEntities, CKSBodyArray &aBodies,
                              const CKEntityAttrib *pAttrib = NULL,
                              const CKSMatrix *pMatrix = NULL,
                              CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Should be called for any function call between StartState()
    // and EndState() that returns an error.
    // It thus ensures the proper termination of the StartState().
    CKSErrors AbortState();

    // @cmember Should only be called after a call to StartState and
    // after all the function calls affecting the model.  This must be
    // called before, and in addition to, calling <mf CKPart:NoteState>.
    // There can be multiple solids states per undo state.
    //
    // @comm NOTE: Changes to the model between the calls to StartState and
    // EndState are registered with the part management system, which will
    // take care of updating the wireframe and rendering of the bodies.
    CKSErrors EndState(bool bNoteKEYCREATORState = true);

    // @cmember Get the Body from an Entity
    CKSErrors GetBodyFromCKEntity(CKSEntity &pEntity, CKSBody *&pBody);

    // @cmember Get an array of bodies from an entity array
    CKSErrors GetBodiesFromCKEntities(CKSEntityArray &aEntities,
                                      CKSBodyArray &aBodies);

    // @cmember Get a face from an entity
    CKSErrors GetFaceFromCKEntity(CKSEntity &pEntity, CKSFace *&pFace);

    // @cmember Get an array of faces from an array of entities
    CKSErrors GetFacesFromCKEntities(CKSEntityArray &aEntities,
                                     CKSFaceArray &aFaces);

    // @cmember Get an edge from an entity
    CKSErrors GetEdgeFromCKEntity(CKSEntity &pEntity, CKSEdge *&pEdge);

    // @cmember Get an array of edges from an array of entities
    CKSErrors GetEdgesFromCKEntities(CKSEntityArray &aEntities,
                                     CKSEdgeArray &aEdges);

    // @cmember Gets the entity in the KeyCreator database that is associated with the given CKSBody
    CKSErrors GetCKEntityFromBody(CKSEntity &rEntity, CKSBody *pBody);

    // @cmember Gets the entity in the KeyCreator database that is associated with the given CKSFace
    CKSErrors GetCKSEntityFromCKSFace(CKSEntity &pEntity, CKSFace *pFace);

    // @cmember Gets the entity in the KeyCreator database that is associated with the given CKSEdge
    CKSErrors GetCKSEntityFromCKSEdge(CKSEntity &pEntity, CKSEdge *pFace);

// @Group Solids File Import/Export functions

    // @cmember Outputs an array of entities to a SAT file.
    CKSErrors WriteEntitiesToSATFile(const std::wstring &csFileName,
                                     CKSEntityArray &rEntities,
                                     bool bSaveText = true,
                                     CKS::AcisVersion nVersion =
                                     CKS::AcisCurrent);

    // @cmember Reads entities out of a SAT file
    CKSErrors ReadEntitiesFromSATFile(const std::wstring &csFileName,
                                      CKSBodyArray &aBodies,
                                      std::vector<CKEntityAttrib> &aAttribs);

    // @cmember Reads entities out of the given file type
    CKSErrors ReadEntitiesFromFile(CKS::FileType eFileType,
                                   const std::wstring &csFileName);

    // @cmember Writes all entities in the current part out to a given file type
    CKSErrors WriteAllEntitiesToFile(CKS::FileType eFileType,
                                     const std::wstring &csFileName);

    // @cmember Writes user selected entities in the current part out to a given file type
    CKSErrors WriteEntitiesToFile(CKSEntityArray aEntities,
                                  CKS::FileType eFileType,
                                  const std::wstring &csFileName,
                                  CKSCoord &ckscBasePos);

    CKSErrors WriteEntitiesToImageFile(CKS::FileType eFileType,
                                       const std::wstring &csFileName,
                                       CKSCoord &ckscFirst, CKSCoord &ckscSecond,
                                       int nViewport = -1);

#ifndef CADKEY_VIEWER
    CKSErrors ReadKCMFile(const std::wstring &csFileName);

    CKSErrors WriteKCMFile(const std::wstring &csFileName, CKSEntityArray *paEntities=NULL);
#endif

// @Group Solids Miscellaneous Tools

    // @cmember Extracts the specified data at a given point on the face
    CKSErrors ExtractFaceData(CKSEntityArray &aEntities,
                              CKSFace *pFace, CKSCoord &ckcTargetPoint, 
                              bool bTangentVector=false, bool bCrossVector=false, 
                              bool bTangentPlane=false, bool bUCurve=false, bool bVCurve=false,  
                              const CKSMatrix *pMatrix=NULL, const CKEntityAttrib *pAttrib=NULL, 
                              CKSLevel *pLevel=NULL, CKSAnim *pAnim = NULL);

    // @cmember Extracts the specified data at a given point on the face.
    CKSErrors ExtractFaceData(CKSEntityArray &aEntities, CKSEntity &pFace, 
                              CKSCoord &ckcTargetPoint, bool bPntOnFace=true, 
                              bool bNormalVec=true, bool bTangentVector=true, 
                              bool bCrossVector=true, bool bTangentPlane=true, 
                              bool bUCurve=true, bool bVCurve=true, 
                              const CKSMatrix *pMatrix=nullptr, 
                              const CKEntityAttrib *pAttrib=nullptr, 
                              CKSLevel *pLevel=nullptr, CKSAnim *pAnim=nullptr);

    // @cmember Attaches a string attribute to a solid, solid face or a solid edge
    CKSErrors AttachAttributeToEntity(CKSEntity &rEntity,
                                      const std::wstring &csAttributeName,
                                      const std::wstring &csAttributeValue);

    // @cmember Retrieves a string attribute from a solid, solid face or a solid edge if one exists
    CKSErrors RetrieveAttributeFromEntity(CKSEntity &rEntity,
                                          std::wstring &csAttributeName,
                                          std::wstring &csAttributeValue);

    // @cmember Deletes a string attribute from a solid, solid face or a solid edge if one exists
    CKSErrors DeleteAttributeFromEntity(CKSEntity &rEntity,
                                        const std::wstring &csAttributeName);

    // @cmember Gets the sidedness of a sheet body
    CKSErrors GetSheetBodySidedness(CKSBody *pSheetBody, int &nSidedness);

    // @cmember Sets the sidedness of the given sheet bodies
    CKSErrors SetSheetBodiesSidedness(CKSBodyArray &aBodies, int nSidedness);

    // @cmember Computes the hidden and visible lines for the given list of CKSBody entities
    CKSErrors ExtractHiddenLines(const CKSBodyArray &aBodies,
                                 const CKSMatrix *pViewMatrix,
                                 bool bGetHiddenCurves,
                                 bool bGetObscuredCurves,
                                 bool bGetTangentCurves,
                                 bool bFlatten,
                                 CKSEdgeArray &aSolidEdges,
                                 CKSEdgeArray &aDashedEdges,
                                 CKSEdgeArray &aExteriorEdges,
                                 CKSEdgeArray &aVisibleTangentEdges,
                                 CKSEdgeArray &aHiddenTangentEdges);

    // @cmember Computes the area of the faces in the array
    CKSErrors GetFacesArea(const CKSFaceArray &aFaces,
                           std::vector<double> &adFaceAreas);

    // @cmember Checks for interference between two bodies
    CKSErrors CheckInterference(CKSBody *pFirstBody, CKSBody *pSecondBody,
                                CKSBody *&pNewBody, bool &bInterference);

    // @cmember Creates new solid bodies from wireframe geometry by using
    // the Picture-It algorithm to recognize solids out of wireframe entities.
    // @comm The wireframe entities must obey the rules of Picture-It topology
    // in order to be recognized.
    CKSErrors SolidifyWireframe(CKSBodyArray &aBodies, CKSEntityArray &aEntities,
                                CKS::SolidifyMaskingMethod eMaskingMethod =
                                CKS::ByLevel,
                                bool bDeleteWireframe = true);

    // @cmember Creates wireframe entities from a body
    CKSErrors ExtractWiresFromBody(CKSEntityArray &aEntities, CKSBody *pBody,
                                   const CKEntityAttrib *pAttrib=nullptr,
                                   const CKSMatrix *pMatrix=nullptr,
                                   CKSLevel *pLevel=nullptr, CKSAnim *pAnim=nullptr);

    // @cmember Creates wireframe entities from an array of solid faces
    CKSErrors ExtractWiresFromFaces(CKSEntityArray &aEntities,
                                    CKSFaceArray &aFaces, bool bEdges,
                                    bool bSilhouetteCurves,
                                    CKSCoordArray &cksaVectorBasePoints, 
                                    CKSCoordArray &cksaUnitVectors,
                                    bool bExistingFlowlines, int nULines, int nVLines,
                                    bool bUseAttribOfOwningSolid,
                                    int nLevelOpt, int nLevel,
                                    const CKSMatrix *pMatrix=NULL);

    // @cmember Creates wireframe entities from solids and sheet bodies
    CKSErrors ExtractWiresFromBodies(CKSEntityArray &aWiresOut, 
                                     CKSEntityArray &aSolidsIn, 
                                     bool bEdges, 
                                     bool bSilhouetteCurves, 
                                     CKSCoordArray &aVecBasePnts, 
                                     CKSCoordArray &aUnitVecs, 
                                     bool bExistingFlowlines, int nULines, int nVLines, 
                                     bool bUseAttribOfOwningSolid,
                                     int nLevelOpt, int nLevel, 
                                     const CKSMatrix *pMatrix=nullptr);

    // @cmember Creates wireframe entities from faces of a solid or sheet body 
    CKSErrors ExtractWiresFromFaces(CKSEntityArray &aWiresOut, 
                                    CKSEntityArray &aFacesIn, 
                                    bool bEdges, 
                                    bool bSilhouetteCurves, 
                                    CKSCoordArray &aVecBasePnts, CKSCoordArray &aUnitVecs, 
                                    bool bExistingFlowlines, int nULines, int nVLines, 
                                    bool bUseAttribOfOwningSolid,
                                    int nLevelOpt, int nLevel, 
                                    const CKSMatrix *pMatrix=nullptr);

    // @cmember Creates wireframe entities from edges and flowlines of a solid or sheet body.
    CKSErrors ExtractWiresFromEdgesAndFlowlines(CKSEntityArray &aWiresOut, 
                                                CKSEntityArray &aEntitiesIn, 
                                                bool bUseAttribOfOwningSolid,
                                                int nLevelOpt, int nLevel, 
                                                const CKSMatrix *pMatrix=nullptr);

    CKSErrors ExtractPolygonsFromSolids(CKSBodyArray &aBodies, double dSurfaceTol, 
                                        double dNormalTol, CKS::PolygonSides &PolygonSides, 
                                        bool bFillPoly, COLORREF crPolyFillColor,
                                        CKSLevel *pLevel = NULL, CKSAnim *pAnim = NULL);

    // @cmember Changes flowlines on solid faces
    CKSErrors ModifyFlowlines(CKSEntityArray &aEntities,
                              bool bDrawMinimalFlowlines=true,
                              int nPlaneU=0, int nPlaneV=0,
                              int nConeCylU=1, int nConeCylV=0,
                              int nSphereU=4, int nSphereV=1,
                              int nTorusU=1, int nTorusV=1,
                              bool bDrawSplineUVAtKnots=false,
                              int nSplineU=0, int nsplineV=0);

    // @cmember Generates face by face facet information for a body
    CKSErrors GetBodyFacetData(CKS_FACE_FACET_DATA **&sffd, CKSBody *pBody,
                               int &rNumFaces, double dSurfaceFacetTol = 0.010,
                               double dNormalAngleTol = 15.00);

    // @cmember Generates face by face facet information for a body
    CKSErrors GetBodyFacetData(CKS_FACE_FACET_DATA **&sffd,
                               const CKSEntity &pSolid,
                               CKSEntityArray &raFaces);

    // @cmember Generates face by face facet information for a body
    CKSErrors GetBodyFacetData(const CKSEntity &pSolid,
                               CKSEntityArray &raFaces,
                               std::vector<std::vector<int>> &raFacetFaces,
                               std::vector<std::vector<float>> &raPoints,
                               std::vector<std::vector<float>> &raNormals);

    // @cmember Free's the memory allocated for the facet data structures
    // by the function GetBodyFacetData()
    CKSErrors FreeBodyFacetData(int numFaces, CKS_FACE_FACET_DATA **sffd);

    // @cmember Converts an array of solid bodies into an array of
    // surfaces (trimmed and/or untrimmed)
    CKSErrors ConvertBodiesToSurfaces(CKSBodyArray &aBodies,
                                      int &nNumSurfaces,
                                      CKSFS_SURF **&aSurfaces);

    // @cmember Free's the memory allocated for the surface data structures
    // by the function ConvertBodiesToTrimmedSurfaces()
    CKSErrors FreeSurfaceData(CKSFS_SURF *pSurface);

    // @cmember Determines if a "CKSFS_SURF" surface is trimmed
    bool IsTrimmedSurface(CKSFS_SURF *pSurface);

    // @cmember This routine returns the face of a trimmed surface.
    // @comm The face object contains the trimming curve information of a trimmed surface.
    CKSErrors GetTrimmingCurveData(CKSFS_SURF *pSurface, FS_FACE *&pFace);

    // @cmember Frees the memory allocated for the trimming curve data structures
    // by the function GetTrimmingCurveData()
    CKSErrors FreeTrimmingCurveData(FS_FACE *pFace);

    // @cmember Retrieves the data of a general NURB surface
    CKSErrors GetNURBSurfaceData(CKSFS_SURF *pSurface, double *pdControlPoints,
                                 double *pdWeights, double *pdUKnots, double *pdVKnots,
                                 double dUVLimits[4], int &nNumUDirControls,
                                 int &nNumVDirControls, int &nNumUKnots, int &nNumVKnots,
                                 int &nDegreeInUDir, int &nDegreeInVDir,
                                 bool &bRational, bool &bClosedInUDir,
                                 bool &bClosedInVDir);

    // @cmember Retrieves the data of a general NURB spline curve
    CKSErrors GetNURBCurveData(CKSFS_CURVE *pCurve, double *pdControlPoints,
                               double *pdWeights, double *pdKnots,
                               double *pdULimits, int &nNumControls,
                               int &nNumKnots, int &nDegree,
                               bool &bRational, bool &bClosed);

    DEPRECATED_IN_12("Version that takes in a CKSEntityArrayInstead")
    CKSErrors GetMassProperties(CKSBody *pBody, CKS_MASSPROP_DATA &pMassProp,
                                bool bPrecise);

    // @cmember Calculates the mass properties of solids, sheets, shells and part references
    CKSErrors GetMassProperties(CKSEntityArray &aEntities, 
                                const std::vector<double> &adDensities, 
                                const std::vector<double> &adAreaDensities, 
                                CKSCoordArray &aUserDefOrigins, 
                                CKSCoordArray &aAngularVelocities,
                                bool bPrecise, 
                                std::vector<CKS_MASSPROP_DATA *> &aMassProperties);

    // @cmember Retrieves the last error message resulting from failure of a solids related SDK function
    void GetLastSolidsErrorMessage(std::wstring &rMessage);

    // @cmember Removes unnecessary faces, edges and vertices from a body
    CKSErrors RemoveRedundantTopology(CKSBody *pBody);

    // @cmember Offsets an array of faces by a given distance
    CKSErrors OffsetFaces(CKSFaceArray &aFaces, double dOffsetDistance, 
                          int nOffsetMethod=0, CKSCoord *pToPos=NULL, 
                          CKSFace *pToFace=NULL);

    // @cmember Offsets an array of bodies by a given distance
    CKSErrors OffsetSolids(CKSBodyArray &aBodies, double dDistance, int nOffsetOpt);

    // @cmember Shadow Tapers an array faces of a solid body with respect to a vector
    CKSErrors ShadowTaperFaces(CKSFaceArray &aFaces, CKSCoord ckcVector, double dShadowTaperAngle);

    // @cmember Tapers an array of faces about an array of edges with respect to a vector
    CKSErrors TaperFacesAboutEdges(CKSFaceArray &aFaces, CKSEdgeArray &aEdges,
                                   double dTaperAngle, CKSCoord &ckscTaperRefVec);

    // @cmember Tapers the given faces with respect to the given plane
    CKSErrors TaperFacesAboutPlane(CKSFaceArray &aFaces, double dTaperAngle,
                                   CKSCoord &ckscPlanePos, CKSCoord &ckscPlaneNorm);

    // @cmember Transforms an array of faces by the given matrix
    CKSErrors TransformSolidFaces(CKSFaceArray &aFaces, const CKSMatrix *pMatrix);

    // @cmember Shells a solid
    CKSErrors ShellSolid(CKSBody *pBody, int nShellDirection, double dInwardOffset,
                         double dOutwardOffset, CKSFaceArray &aOpenFaces,
                         bool bCreateLip, double dLipWidth, double dLipThickness,
                         CKSFaceArray &aSpecificOffsetFaces,
                         const std::vector<double> &aSpecificOffsets);

    // @cmember Thickens a sheet body into a solid
    CKSErrors ThickenSheet(CKSBody *pBody, double dThickness1, bool bBothDirections, double dThickness2=0.0);

    // @cmember Detects and fixes accuracy problems in the body's geometry
    CKSErrors HealBody(CKSBody *pBody);

    // @cmember Simplifies the body's geometry and topology
    CKSErrors SimplifyBody(CKSBody *pBody);

    // @cmember Rebuilds the given array of solids by recreating all the edges and seam lines 
    CKSErrors RebuildWires(bool bAll, CKSEntityArray *paEntities=NULL);

    // @cmember Applies a constant or variable radius blend to the given edge
    CKSErrors BlendEdges(CKSEdge *pEdge, double dStartRadius,
                         bool bVariableRadius = false,
                         double dEndRadius = 0.0,
                         CKS::BlendCrossSection eSection = CKS::Circular,
                         double dThumbWeight = 2.0,
                         bool bBlendAlongSmoothEdges = true,
                         bool bCheckInterference = false);

    // @cmember Blends edges with a constant radius
    CKSErrors BlendConstantRadiusEdges(CKSEdgeArray& rBlendEdges,
                                       double dRadius, bool bSmooth,
                                       bool bOverflow, bool bInterferenceCheck);

    // @cmember Blends edge with a variable radius specified by a start and end radius
    CKSErrors VarRadEdgeBlendByStartAndEnd(CKSEdge *pEdge, double dStartRadius,
                                           double dEndRadius,
                                           CKS::BlendCrossSection eSection,
                                           double dThumbWeight,
                                           bool bBlendAlongSmoothEdges,
                                           bool bCheckInterference,
                                           bool bSlidingDisc = false,
                                           CKSCoord *cksDiscDir = NULL);

    // @cmember Blends edge with a constant radius
    CKSErrors VarRadEdgeBlendByConstRad(CKSEdge *pEdge, double dRadius,
                                        CKS::BlendCrossSection eSection,
                                        double dThumbWeight,
                                        bool bBlendAlongSmoothEdges,
                                        bool bCheckInterference,
                                        bool bSlidingDisc = false,
                                        CKSCoord *cksDiscDir = NULL);

    // @cmember Blends edge with a constant width
    CKSErrors VarRadEdgeBlendByConstWidth(CKSEdge *pEdge, double dWidth,
                                          CKS::BlendCrossSection eSection,
                                          double dThumbWeight,
                                          bool bBlendAlongSmoothEdges,
                                          bool bCheckInterference,
                                          bool bSlidingDisc = false,
                                          CKSCoord *cksDiscDir = NULL);

    // @cmember Blends edge with a variable radius specified by an elliptical cross section
    CKSErrors VarRadEdgeBlendByRotatedEllipse(CKSEdge *pEdge, double dMajorAxis,
                                              double dMinorAxis, double dAngle,
                                              CKS::BlendCrossSection eSection,
                                              double dThumbWeight,
                                              bool bBlendAlongSmoothEdges,
                                              bool bCheckInterference,
                                              bool bSlidingDisc = false,
                                              CKSCoord *cksDiscDir = NULL);

    // @cmember Blends edge with a variable radius by specifying different radii along points on the edge
    CKSErrors VarRadEdgeBlendByPointRadPairs(CKSEdge *pEdge,
                                             CKSCoordArray &aPoints,
                                             double *adRadii,
                                             CKS::BlendCrossSection eSection,
                                             double dThumbWeight,
                                             bool bBlendAlongSmoothEdges,
                                             bool bCheckInterference,
                                             bool bSlidingDisc = false,
                                             CKSCoord *cksDiscDir = NULL);

    // @cmember Blends edge with a variable radius computed as a function of a 2D curve
    CKSErrors VarRadEdgeBlendBy2DSpline(CKSEdge *pEdge, CKSEntity &rSpline,
                                        CKS::BlendCrossSection eSection,
                                        double dThumbWeight,
                                        bool bBlendAlongSmoothEdges,
                                        bool bCheckInterference,
                                        bool bSlidingDisc = false,
                                        CKSCoord *cksDiscDir = NULL);

    // @cmember Creates a blend between 2 faces
    CKSErrors FaceFaceBlend(CKSFace *pFirstFace, CKSFace *pSecondFace,
                            CKSEdgeArray &aRollAroundEdges,
                            CKSVertexArray &aRollAroundVertices,
                            bool bCheckInterference);

    // @cmember Creates a blend between an edge and a face
    CKSErrors FaceFaceBlend(CKSEdge *pEdge, CKSFace *pFace,
                            CKSEdgeArray &aRollAroundEdges,
                            CKSVertexArray &aRollAroundVertices,
                            bool bCheckInterference);

    // @cmember Creates a vertex blend
    CKSErrors VertexBlend(CKSVertexArray &aVertices, double dEdgeSetback,
                          CKSEdgeArray &aConvergingEdges,
                          double *dEdgeRadii, bool bCheckInterference);

    // @cmember Chamfers the given edges
    CKSErrors ChamferEdges(CKSEdgeArray &aEdges, double dLength1,
                           double dLength2, bool bBlendAlongSmoothEdges,
                           bool bCheckInterference, bool bByAngle = false);

    // @cmember Chamfers the given vertices
    CKSErrors ChamferVertices(CKSBody *pBody, CKSCoordArray &aVertices,
                              double dRadius, bool bBlendAlongSmoothEdges,
                              bool bCheckInterference,
                              bool bChamferConvergingEdges=true);

    // @cmember Changes a blend radius
    CKSErrors EditBlend(CKSEntityArray& rBlendFaces, double dNewRadius);

    // @cmember Changes a chamfer length or angle
    CKSErrors EditChamfer(CKSEntityArray& rBlendFaces, double dNewLength, double dNewAngle);

    // @cmember Create a feature
    CKSErrors Feature(CKSEntity &rEntity, CKSCoord &ckcPos,
                      int nFeatureType, int nHoleType, int nUnit,
                      const std::wstring &csSize,
                      double dValue1 = 0, double dValue2 = 0,
                      double dDiam1 = 0, double dDiam2 = 0,
                      double dDepth1 = 0, double dDepth2 = 0,
                      double dAngle = 0,
                      const std::wstring *pcsDrill = NULL,
                      const std::wstring *pcsSeries = NULL,
                      const std::wstring *pcsDBType = NULL);

    // @cmember Forget a feature
    CKSErrors ForgetFeature(CKSEntity& rFeature);

    // @cmember Delete a feature
    CKSErrors DeleteFeature(CKSEntity& rFeature);

    // @cmember Gets the faces of an owning body
    CKSErrors GetFacesFromBody(CKSBody *pBody, int &nNumFaces, CKSFaceArray &aFaces);

    // @cmember Determines if a face belongs to a closed solid body
    CKSErrors IsFaceFromSolid(CKSFace *pFace, bool &bFromSolid);

    // @cmember Determines if the underlying surface of a face is periodic in either U or V directions
    CKSErrors IsUnderlyingSurfacePeriodic(CKSFace *pFace, bool &bPeriodic);

    // @cmember Determines if the underlying surface of a face is analytic
    CKSErrors IsFaceAnalytic(CKSFace *pFace, bool &bAnalytic);

    // @cmember Retrieves the Owning Body of a Face
    CKSErrors GetOwnerBody(CKSFace *pFace, CKSBody *&pOwner);

    // @cmember Facets a face and returns a FACE_FACET_DATA structure
    CKSErrors FacetFace(CKSFace *pFace, double dStol, double dAtol, int nNsides,
                        bool bUvflag, double dMaxEdgeLength,
                        FACE_FACET_DATA *&pFaceFacetData);

    // @cmember Free the face facet data structure generated by ::FacetFace()
    CKSErrors FreeFaceFacetData(FACE_FACET_DATA *pFaceFacetData);

    // @cmember Facets the edges of a face and returns an EDGE_FACET_DATA structure
    CKSErrors FacetFaceEdges(CKSFace *pFace, double dStol, double dAtol,
                             double dMaxEdgeLength,
                             EDGE_FACET_DATA *&pEdgeFacetData);

    // @cmember Free the edge facet data structure generated by ::FacetFaceEdges()
    CKSErrors FreeEdgeFacetData(EDGE_FACET_DATA *pEdgeFacetData);

    // @cmember Returns the min/max box of a face in xyz space
    CKSErrors GetFaceBox(CKSFace *pFace, double p1[3], double p2[3]);

    // @cmember Evaluates the underlying surface of a face using the ACIS surface evaluator
    CKSErrors FaceEvaluate(CKSFace *pFace, double dUi, double dVi, int nNd,
                           double adPd[11][3]);

    // @cmember Evaluates a surface using the FastSURF surface evaluator
    CKSErrors SurfExEvaluate(CKSFS_SURF *pSrf, double dUi, double dVi, int nNd,
                           double adPd[11][3]);

    // @cmember Evaluates a curve using the FastSURF curve evaluator
    CKSErrors CurveEvaluate(CKSFS_CURVE *pCrv, double dUi, int nNd, double adPd[7][3]);

    // @cmember Free a CKSFS_SURF surface pointer
    CKSErrors FreeFSurf (CKSFS_SURF *pSrf);

    // @cmember Free an array of CKSFS_SURF surface pointers
    CKSErrors FreeFSurfArray (CKSFS_SURF **pSrfs, int nNumSrfs);

    // @cmember Free a CKSFS_CURVE curve pointer
    CKSErrors FreeFCurve (CKSFS_CURVE *pCrv);

    // @cmember Free an array of CKSFS_CURVE curve pointers
    CKSErrors FreeFCurveArray (CKSFS_CURVE **pCrvs, int nNumCrvs);

    // @cmember Convert an array of ACIS FACE's to their corresponding CKSFS_SURF surface representations
    CKSErrors ConvertACISFacesToFSurfs(CKSFace **pFaces, int nNumFaces,
                                       CKSFS_SURF **&pSrfs);

    // @cmember Get the parameter range of the surface underlying the face
    CKSErrors FaceSurfaceParameterRange(CKSFace *pFace, double *dUlow,
                                        double *dUhigh,
                                        double *dVlow, double *dVhigh);

    // @cmember Extract pcurves (ONLY) from an ACIS FACE
    CKSErrors ExtractPCurvesFromSplineFace(CKSFace *pFace, FS_FACE *&pNewFace);

    // @cmember Deletes faceter attributes attached to the bodies
    CKSErrors DeleteFacetAttributes(CKSBodyArray &aBodies, int nNumBodies,
                                    int &nNumAttribsDeleted);

    // @cmember Get the Document's system spline tolerance
    CKSErrors GetSplineTolerance(double &dSplineTolerance);

    // @cmember Define Vector menu
    int DefineVectorDirection(const std::wstring &csPrompt, CKSCoord &ckcPnt,
                              CKSCoord &ckcVec);

    // @cmember Generate surface hunting grid to aid projections
    CKSErrors SurfHuntingGrid(CKSFS_SURF *pSrf, CKSFS_HUNTING_GRID *&pHuntGrid);

    // @cmember Free the surface hunting grid memory
    CKSErrors FreeHuntingGrid(CKSFS_HUNTING_GRID *pHuntGrid);

    // @cmember Find the minimum distance from a point to a surface
    CKSErrors PointToSurfMinDist(int nHuntFlag, CKSFS_SURF *pSrf,
                                 CKSFS_HUNTING_GRID *pHuntGrid,
                                 double adPt[3], double adPds[11][3],
                                 double *dDist, double *dUu,
                                 double *dVv, int *irc);

    // @cmember Find the intersection of a vector and surface
    CKSErrors VectorSurfIntersection(int nHuntFlag, CKSFS_SURF *pSrf,
                                     CKSFS_HUNTING_GRID *pHuntGrid,
                                     double adVec[6], double *dUu, double *dVv,
                                     double *dTt,
                                     double adPds[11][3], int *irc);

    // @cmember Get the spline data from an CKSFS_CURVE
    CKSErrors GetSplineData(CKSFS_CURVE *pCrv, double *pCoefs, double *pUlist,
                            int *nNumSegs, int *irc);

    // @cmember Get the curve type from an CKSFS_CURVE
    CKSErrors GetCurveType(CKSFS_CURVE *pCrv, int &nType);

    // @cmember Convert a curve entity to a CKSFS_CURVE
    CKSErrors ConvertEntityToFCurve (CKSEntity &rEnt, CKSFS_CURVE *&pCrv);

    // @cmember Project a curve onto a surface
    CKSErrors ProjectCurveOntoSurf(CKSFS_SURF *pSrf,
                                   CKSFS_HUNTING_GRID *pHuntGrid,
                                   int nProjMethod, bool bTrimToBoundaries,
                                   double adVec[3], CKSFS_CURVE *pCrv,
                                   double dCurveFitTol, int &nNumNewCrvs,
                                   CKSFS_CURVE **&pNewCrvs, int *irc);

    // @cmember Make a surface from a rectangular array of points and optional tangents/normal constraint vectors
    CKSErrors MakePointVectorSurf(int nNumU, int nNumV,
                                  const CKSCoordArray &ackcNodePts,
                                  int *pUTangentFlags,
                                  const CKSCoordArray &ackcUTangents,
                                  int *pVTangentFlags,
                                  const CKSCoordArray &ackcVTangents,
                                  int *pNormalFlags,
                                  const CKSCoordArray &ackcNormals,
                                  CKSBody *&pSheetBody);

    // @cmember Create a curve mesh surface from a mesh of U and V direction curves
    CKSErrors MakeCurveMeshSurf(CKSEntityArray &rPrimaryCurves,
                                CKSEntityArray &rSecondaryCurves,
                                double dFitTol, CKSBody *&pSheetBody);

    // @cmember Create a swept surface by sweeping curves along a path
    CKSErrors MakeSweptSurf(CKSBody *&pSheetBody, 
                            CKSEntityArray &aDirectorCurve1, CKSEntityArray &aGeneratorCurve1,
                            CKSCoord *pStartDirCrv1=NULL, CKSCoord *pStartGenCrv1=NULL,
                            CKSEntityArray *paDirectorCurve2=NULL, CKSCoord *pStartDirCrv2=NULL,
                            CKSEntityArray *paGeneratorCurve2=NULL, CKSCoord *pStartGenCrv2=NULL,
                            double dFitTol=0.001, int nOrientationOpt=0, CKSFace *pControlFace=NULL);

    CKSErrors MakeSurfaceExtension(CKSBody *&pSheetBody, CKSFace *pFace,
                                   int nEdge, int nMethod, int nOption,
                                   double dValue);

    // @cmember Suppress a feature
    CKSErrors RenameFeature(CKSEntity& rFeature, const std::wstring &csName);

    // @cmember Suppress a feature
    CKSErrors SuppressFeature(CKSEntity& rFeature);

    // @cmember UnSuppress a feature
    CKSErrors UnSuppressFeature(CKSEntity& rFeature);

    // @cmember Determine if a face is a sliver face
    CKSErrors IsSliverFace (CKSFace *pFace, bool &bSliverFace);

    // @cmember Convert a curve to a spline
    CKSErrors ConvertFCurveToSpline(CKSFS_CURVE *pCrv, double dFitTolerance,
                                    CKSFS_CURVE *&pSplCrv);

    // @cmember Convert a chain of curves to a spline
    CKSErrors ConvertChainToSpline(CKSEntityArray &rChainOfCurves,
                                   double dFitTolerance, CKSFS_CURVE *&pSplCrv);

    // @cmember Prune faces of a solid
    CKSErrors Prune(CKSEntityArray& rBlendFaces, bool bCut,
                    CKSEntityArray *paPrunedSolids = NULL);

    // @cmember Prune faces of a body
    CKSErrors Prune(CKSFaceArray& rPruneFaces, bool bCut,
                    CKSEntityArray *paPrunedSolids=NULL);

    // @cmember Graft faces of a solid
    CKSErrors Graft(GraftType GType, DirectionType DType, bool bExtend, CKCoord &Direction,
                        CKSEntity SolidTool, CKSEntity SolidTarget,
                        CKSEntity ToolFace, CKSEntity TargetFace,
                        CKCoord &ToolCoord, CKCoord &RootPoint, CKMatrix &CKMat,
                        CKSEntityArray& AdditionalSolids, bool bKeep = false);


    // @cmember Tweak faces of a solid
    CKSErrors Tweak(CKSEntityArray& rTweakedFaces, CKSEntity TweakFace, bool bReverse);

    // @cmember Deterine if UV is with active region of face (trimmed surface)
    CKSErrors IsUVInActiveRegionOfFace(CKSFS_SURF *pSrf, double dU, double dV,
                                       bool &bActive);

    // @cmember Generates curves as a result of intersecting the given bodies with a plane
    CKSErrors CreatePlaneBodySlice(CKSBodyArray &aBodies, CKSEntity rPlane, CKSEntityArray &aEnts);

    // @cmember Remove Faces from Solids
    CKSErrors RemoveFaces(CKSFaceArray &aFaces);

    // @cmember Verifies bodies and identifies and heals problem bodies
    CKSErrors DiagnoseBodies(CKSBodyArray &aBodies, bool bCheckFaceFaceIntr,
                             bool bCheckDiscont, bool bDrawWireEnts,
                             bool bHealProbEnts, bool bTolerize,
                             bool bReCheck, bool bChangeAttrib,
                             bool bChangeEntLevel, int nLevelOpt, 
                             bool &bFoundCheckErrors);

    // @cmember Verifies the distance between two Bodies.
    CKSErrors VerifyMinDistBodyToBody(CKSBody *pBody1, CKSBody *pBody2,
                                      double &dDistance, CKSCoord &ckscPoint1,
                                      CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Body and a Face.
    CKSErrors VerifyMinDistBodyToFace(CKSBody *pBody, CKSFace *pFace,
                                      double &dDistance, CKSCoord &ckscPoint1,
                                      CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Body and a Curve.
    CKSErrors VerifyMinDistBodyToCurve(CKSBody *pBody, const CKSEntity &pCurve,
                                       double &dDistance, CKSCoord &ckscPoint1,
                                       CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Body and a Plane.
    CKSErrors VerifyMinDistBodyToPlane(CKSBody *pBody,
                                       const CKSMatrix &ckmPlane,
                                       double &dDistance, CKSCoord &ckscPoint1,
                                       CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Body and a Point.
    CKSErrors VerifyMinDistBodyToPoint(CKSBody *pBody,
                                       const CKSCoord &ckscPoint,
                                       double &dDistance,
                                       CKSCoord &ckscPoint1);

    // @cmember Verifies the distance between two Faces.
    CKSErrors VerifyMinDistFaceToFace(CKSFace *pFace1, CKSFace *pFace2,
                                      double &dDistance, CKSCoord &ckscPoint1,
                                      CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Face and a Curve.
    CKSErrors VerifyMinDistFaceToCurve(CKSFace *pFace, const CKSEntity &pCurve,
                                       double &dDistance, CKSCoord &ckscPoint1,
                                       CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Face and a Plane.
    CKSErrors VerifyMinDistFaceToPlane(CKSFace *pFace,
                                       const CKSMatrix &ckmPlane,
                                       double &dDistance, CKSCoord &ckscPoint1,
                                       CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Face and a Point.
    CKSErrors VerifyMinDistFaceToPoint(CKSFace *pFace,
                                       const CKSCoord &ckscPoint,
                                       double &dDistance,
                                       CKSCoord &ckscPoint1);

    // @cmember Verifies the distance between a two Curves.
    CKSErrors VerifyMinDistCurveToCurve(const CKSEntity &pCurve1,
                                        const CKSEntity &pCurve2,
                                        double &dDistance,
                                        CKSCoord &ckscPoint1,
                                        CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Curve and a Plane.
    CKSErrors VerifyMinDistCurveToPlane(const CKSEntity &pCurve1,
                                        const CKSMatrix &ckmPlane,
                                        double &dDistance,
                                        CKSCoord &ckscPoint1,
                                        CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Curve and a Point.
    CKSErrors VerifyMinDistCurveToPoint(const CKSEntity &pCurve,
                                        const CKSCoord &ckscPoint,
                                        double &dDistance,
                                        CKSCoord &ckscPoint1);

    // @cmember Verifies the distance between two Planes.
    CKSErrors VerifyMinDistPlaneToPlane(const CKSMatrix &ckmPlane1,
                                        const CKSMatrix &ckmPlane2,
                                        double &dDistance,
                                        CKSCoord &ckscPoint1,
                                        CKSCoord &ckscPoint2);

    // @cmember Verifies the distance between a Plane and a Point.
    CKSErrors VerifyMinDistPlaneToPoint(const CKSMatrix &ckmPlane,
                                        const CKSCoord &ckscPoint,
                                        double &dDistance,
                                        CKSCoord &ckscPoint1);

    // @cmember Verifies the distance between two Points.
    CKSErrors VerifyMinDistPointToPoint(const CKSCoord &ckscPoint1,
                                        const CKSCoord &ckscPoint2,
                                        double &dDistance);

	// @cmember Verifies the distance between two Faces.
	CKSErrors VerifyMaxDistFaceToFace(const CKSEntity &pFace1,
                                      const CKSEntity &pFace2,
		                              double &dDistance,
                                      CKSCoord &ckscPoint1,
		                              CKSCoord &ckscPoint2);

	// @cmember Verifies the distance between a two Curves.
	CKSErrors VerifyMaxDistCurveToCurve(const CKSEntity &pCurve1,
                                        const CKSEntity &pCurve2,
		                                double &dDistance,
                                        CKSCoord &ckscPoint1,
		                                CKSCoord &ckscPoint2);

    // @cmember Verifies the interference between bodies
    CKSErrors StaticInterferenceCheck(const CKSEntityArray& aBodies,
                                      int nFullContainment);

    // @cmember Imprints solid faces by projecting curves along the specified vector
    CKSErrors ImprintFacesWithCurves(CKSFaceArray &aFaces, 
                                     const CKSCoord &ckcProjVector, 
                                     CKSEntityArray &aCKSCurves);

    // @cmember Imprints a solid body by projecting curves along the specified vector
    CKSErrors ImprintBodyWithCurves(CKSBody *pBody,
                                    const CKSCoord &ckcProjVector,
                                    CKSEntityArray &aCurves);

    // @cmember Imprints/Intersects a solid body with a plane.
    CKSErrors ImprintBodyWithPlane(CKSBody *pBody, CKSMatrix &cksmPlaneMatrix);

    // @cmember Imprints/Intersects two solid bodies.
    CKSErrors ImprintBodyWithBody(CKSBody *pBody1, CKSBody *pBody2);

    // @cmember To set different facet tolerances for each solid/sheet in a part
    CKSErrors SetSolidFacetRefinement(CKSBodyArray &aBodies, double dSurfDeviation,
                                      double dNormalDeviation, bool bSpecifyMaxEdgeLength,
                                      double dMaxEdgeLength);

    // @cmember Creates a bounding box around the given entities in the orientation of the given plane
    CKSErrors AddBoundingBox(CKSEntityArray &aEntities, CKSMatrix *pPlaneMatrix,
                             int nBoxOption, int nBoxType,
                             bool bCreateCenterPoint, int nTransparency,
                             const CKEntityAttrib *pAttrib = NULL,
                             CKSLevel *pLevel = NULL,
                             bool bDimensions = false,
                             double dLengthIncr = 0.0,
                             double dWidthIncr = 0.0,
                             double dHeightIncr = 0.0);

    // @cmember Checks if an array of faces can be extracted from a mold in a
    // given direction. Alternatively this function compares the draft angle of
    // the faces in the array to a specified draft angle along the pull direction
    CKSErrors VerifyDraftAngle(CKSFaceArray &aFaces, CKSCoord &ckcDirectionVector,
                               int nVerifyOpt, double dDraftAngle,
                               int nPositiveDraftColorR,
                               int nPositiveDraftColorG,
                               int nPositiveDraftColorB,
                               int nNegativeDraftColorR,
                               int nNegativeDraftColorG,
                               int nNegativeDraftColorB,
                               int nZeroDraftColorR,
                               int nZeroDraftColorG,
                               int nZeroDraftColorB,
                               int nAmbigousDraftColorR,
                               int nAmbigousDraftColorG,
                               int nAmbigousDraftColorB);

    // @cmember Measures the maximum deviation from the edge of one surface to
    //          another surface when tangency is desired in preparing to join a surface.
    CKSErrors VerifyDeviationEdgeToSurf(CKSEdge *pEdge, CKSFace *pFace,
                                        int nTestPoints, double dPositionTol,
                                        double dNormalAngleTol,
                                        CKSCoordArray &gaPositions,
                                        CKSCoordArray &gaNormalBases,
                                        CKSCoordArray &gaNormalDirections,
                                        CKSCoord &ckcWorstEdgePoint,
                                        CKSCoord &ckcWorstEdgeNormalBasePoint,
                                        CKSCoord &ckcWorstEdgeNormal,
                                        CKSCoord &ckcWorstSurfacePoint,
                                        CKSCoord &ckcWorstSurfaceNormalBasePoint,
                                        CKSCoord &ckcWorstSurfaceNormal,
                                        double &dMaxPositionDeviation,
                                        double &dMaxAngularDeviation);

    // @cmember Measures the maximum deviation from the edge boundary of one surface
    //          to the edge boundary of another surface.
    CKSErrors VerifyDeviationEdgeToEdge(CKSEdge *pFirstEdge, CKSEdge *pSecondEdge,
                                        double dPositionTol,double dNormalAngleTol,
                                        int nTestPoints, int &nActualTestPoints,
                                        CKSCoordArray &gaPositions,
                                        CKSCoordArray &gaNormalBases,
                                        CKSCoordArray &gaNormalDirections,
                                        CKSCoord &adWorstFirstPoint,
                                        CKSCoord &adWorstSecondPoint,
                                        CKSCoord &adWorstFirstNormalBasePoint,
                                        CKSCoord &adWorstFirstNormal,
                                        CKSCoord &adWorstSecondNormalBasePoint,
                                        CKSCoord &adWorstSecondNormal,
                                        double &dMaxPositionDeviation,
                                        double &dMaxAngularDeviation);

    // @cmember  Measures the maximum deviation from a curve to a surface to verify congruency or constant offset value.
    CKSErrors VerifyDeviationCurveToSurf(CKSEntity *pCurve, CKSFace *pFace,
                                         int nTestPoints,
                                         double dPositionTol, double dNormalAngleTol,
                                         CKSCoordArray &gaPositions,
                                         CKSCoordArray &gaNormalBases,
                                         CKSCoordArray &gaNormalDirections,
                                         CKSCoord &ckcWorstCurvePoint,
                                         CKSCoord &ckcWorstCurveTangentBasePoint,
                                         CKSCoord &ckcWorstCurveTangent,
                                         CKSCoord &ckcWorstSurfacePoint,
                                         CKSCoord &ckcWorstSurfaceNormalBasePoint,
                                         CKSCoord &ckcWorstSurfaceNormal,
                                         double &dMaxPositionDeviation,
                                         double &dMaxAngularDeviation);

    // @cmember  Measures the distances from a series of points to a surface.
    CKSErrors VerifyDeviationPointToFace(CKSFace *pFaceSurf, CKSCoord &ckcPoints,
                                         CKSCoord &ReturnPos, double &dDistance);

    // @cmember  Measures the positional and normal angle deviations from one surface to another.
    CKSErrors VerifyDeviationFaceToFace(CKSFace *pRefSurf,CKSFace *pEvalSurf,
                                        int nUTestPos, int nVTestPos, double dPosTol,
                                        double dAngleTol, double dOffset,
                                        CKSCoordArray &gaPositions1,
                                        CKSCoordArray &gaPositions2,
                                        CKSCoordArray &gaNormalVectorBases1,
                                        CKSCoordArray &gaNormalVectorDirs1,
                                        CKSCoordArray &gaNormalVectorBases2,
                                        CKSCoordArray &gaNormalVectorDirs2,
                                        double &pmax, double &vnmax);

    // @cmember Extract flat pattern for acis faces (unwrap fast surface in cadkey 19)
    CKSErrors ExtractFlatPattern(CKSFaceArray &aFaces, double dCurveFitTol/*, double &dTotalArea*/);

    // @cmember Find duplicate bodies in the part and replace them with an
    // external part and part references.
    int DiscoverAssembly(CKSEntityArray &aSolids);

    CKSErrors ConvertLevelsBasedPartToReferencesBasedPart(CKSEntityArray &aEntities,
                                                          const std::wstring &csNewRootFileName);

    // @cmember Get the face data
    CKSErrors GetFaceData(CKSEntity &pFace,
                          CKSCoordArray &ackcPoints,
                          std::vector<int> &anFaceList,
                          CKSCoordArray &ackcNormals);

    // @cmember Changes the color of existing faces
    CKSErrors SetFacesColor(CKSEntityArray &aFaces,
                            int nRed, int nGreen, int nBlue);

    // @cmember Sets the transparency of an array of faces
    CKSErrors SetFacesTransparency(CKSFaceArray &aBodies, int nTransparency);

    // @cmember Sets the transparency of a an array of bodies
    CKSErrors SetSolidsTransparency(CKSBodyArray &aBodies, int nTransparency);

    // @cmember Sets the transparency of a an array of part references
    CKSErrors SetReferenceTransparency(CKSEntityArray &aRefs, int nTransparency);

    // @cmember Gets the transparency of a an array of part references
    CKSErrors GetReferenceTransparency(CKSEntityArray &aRefs,
                                       std::vector<int> &anTransparency);

    // @cmember Get the RGB values of the face's color
    CKSErrors GetFaceColor(CKSFace *pFace,
                           int &nRed, int &nGreen, int &nBlue);

    // @cmember Get the name of the Material applied to the face
    CKSErrors GetFaceMaterial(CKSFace *pFace, std::wstring &csMaterial);

    // @cmember Set the RGB values of the face's facet color
    CKSErrors SetFaceFacetColor(CKSEntity &pFace,
                                const std::vector<int> &anFacetIndices,
                                const std::vector<COLORREF> &acrColors);

    // @cmember Get the RGB values of the face's facet color
    CKSErrors GetFaceFacetColor(CKSEntity &pFace,
                                const std::vector<int> &anFacetIndices,
                                std::vector<COLORREF> &acrColors);

    // @cmember Set the material of an array of entities
    CKSErrors SetEntityMaterial(CKSEntityArray &aEnts,
                                const std::wstring &csName, int nColorFlags,
                                int nColor, int nAmbient, int nSpecular,
                                int nTransparency, int nGloss, int nMirror,
                                const std::wstring *pTextureFile = NULL,
                                int nTextureMap = 0,
                                double dTextureUnum = 1, double dTextureVnum = 1,
                                double dTextureRotate = 0);

    // @cmember Get the material of an entity
    CKSErrors GetEntityMaterial(CKSEntity &pEntity,
                                std::wstring &csName, int &nColorFlags,
                                int &nColor, int &nAmbient, int &nSpecular,
                                int &nTransparency, int &nGloss, int &nMirror,
                                std::wstring &csTextureFile,
                                int &nTextureMap,
                                double &dTextureUnum, double &dTextureVnum,
                                double &dTextureRotate);

    // @cmember Set face vertex color of the entity
    CKSErrors SetEntityVertexColors(CKSEntity &pEntity,
                                    std::vector<double> &adVertexColors);

    // @cmember Set options used for simulation
    CKSErrors SetSimulationOptions(double         dFPS, 
                                   double         dDuration, 
                                   double         dSimTimestep, 
                                   double         dGravity, 
                                   double         dConcavity, 
                                   double         dLDamping,
                                   double         dADamping, 
                                   bool           bAnimateCalc, 
                                   bool           bHighightCol, 
                                   bool           bUseGravity, 
                                   bool           bIgnoreCol,
                                   bool           bHaltOnCol, 
                                   bool           bDrawColGeo);

    // @cmember Run simulation
    CKSErrors SimulateCalc(double dDuration, bool bResetBodies);

	// @cmember Replay simulation
	CKSErrors SimulateReplay(double dDuration, bool bResetBodies);

    // @cmember Add bodies to simulation
    CKSErrors SimulateAddBodies(CKSEntityArray &aEntities);

    // @cmember Merge simulation bodies
    CKSErrors SimulateMergeBodies(CKSEntityArray &aEntities);

    // @cmember Split simulation bodies
    CKSErrors SimulateSplitBodies(CKSEntityArray &aEntities);

	// @cmember Set options on a constraint
	CKSErrors SetConstraintOptions(CKSEntity pConstraint, const CKSSimConstraintOptions &opts);

	// @cmember Get options from a constraint
	CKSErrors GetConstraintOptions(CKSEntity pConstraint, CKSSimConstraintOptions &opts);

	// @cmember Create ball and socket constraint
	CKSEntity AddBallConstraint(CKSEntity pEntity1,
								CKSEntity pEntity2,
								CKS::Location *pBasePt,
								CKS::Location *pLabelPos,
								CKSSimConstraintOptions &opts);

	// @cmember Create hinge constraint
	CKSEntity AddHingeConstraint(CKSEntity pEntity1,
								 CKSEntity pEntity2,
								 CKS::Location *pBasePt,
								 CKS::Location *pAxisPt,
								 CKS::Location *pLabelPos,
								 CKSSimConstraintOptions &opts);

	// @cmember Create slider constraint
	CKSEntity AddSliderConstraint(CKSEntity pEntity1,
								  CKSEntity pEntity2,
								  CKS::Location *pBasePt,
								  CKS::Location *pAxisPt,
								  CKS::Location *pLabelPos,
								  CKSSimConstraintOptions &opts);

	// @cmember Create fixed constraint
	CKSEntity AddFixedConstraint(CKSEntity pEntity1,
								 CKSEntity pEntity2,
								 CKS::Location *pBasePt,
								 CKS::Location *pLabelPos,
								 CKSSimConstraintOptions &opts);

	// @cmember Create follow curve constraint
	CKSEntity AddFollowCurveConstraint(CKSEntity pEntity1,
		                               CKSEntity pEntity2,
		                               CKS::Location *pBasePt,
		                               CKSEntity pCurve,
		                               CKS::Location *pLabelPos,
		                               CKSSimConstraintOptions &opts);

	// @cmember Create gear constraint
	CKSEntity AddGearConstraint(CKSEntity pEntity1,
								CKSEntity pEntity2,
								CKS::Location *pBasePt,
								CKS::Location *pAxisPt,
								CKS::Location *pBody2Base,
								CKS::Location *pBody2Axis,
								CKS::Location *pLabelPos,
								CKSSimConstraintOptions &opts);

	// @cmember Create rack and pinion constraint
	CKSEntity AddPinionConstraint(CKSEntity pPinion,
								  CKSEntity pRack,
								  CKS::Location *pPinionBasePt,
								  CKS::Location *pPinionAxisPt,
								  CKS::Location *pRackBase,
								  CKS::Location *pRackAxis,
								  CKS::Location *pLabelPos,
								  CKSSimConstraintOptions &opts);

	// @cmember Create universal joint constraint
	CKSEntity AddUniversalConstraint(CKSEntity pEntity1,
								     CKSEntity pEntity2,
								     CKS::Location *pBasePt,
								     CKS::Location *pAxis1Pt,
								     CKS::Location *pAxis2Pt,
								     CKS::Location *pLabelPos,
								     CKSSimConstraintOptions &opts);


// Private Functions
private:
    // Determine if we are in the same mode as the specified entity.
    int GetModeCheck(const CKEntity *pEntity, const CKSDrawInst *pInst);

    // Get a display view by number
    CKDispView *GetDispView(int nDispView);
    };

SDK_FUNC CKPart CKGetActivePart();

//Attempt to acquire a partner license
SDK_FUNC bool CKCheckOutLicense(std::wstring sFeature);

//Return a partner license
SDK_FUNC bool CKReturnLicense(std::wstring sFeature);

// @class Instantiate an object of this class to block all accelerator key
// mappings.  When the object goes out of scope, the mappings
// will be restored.  The F-keys, Escape, and Return are not blocked by
// this.
class SDK_EXPORT CKSBlockAccelKeys
    {
public:
    CKSBlockAccelKeys(CKS::AccelBlockState nState = CKS::BlockAllButSpecial);
    ~CKSBlockAccelKeys();
private:
    CKS::AccelBlockState m_nState;
    };

// @class Instantiate an object of this class when calling UI functions from
// a modeless dialog or something similar that is outside of a function 
// executed through the main function interface.  This will tell the system
// that it is in the middle of a function and shouldn't clear the
// conversation bar.
class SDK_EXPORT CKSFunctionStack
    {
public:
    CKSFunctionStack();
    ~CKSFunctionStack();
    };

#endif
