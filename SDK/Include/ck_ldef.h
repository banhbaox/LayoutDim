// Copyright Kubotek Corporation, 1991-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_LDEF_H_LOADED  /* MUST BE FIRST LINE OF FILE */
#define CK_LDEF_H_LOADED

// @doc EXTERNAL SDK

#include "ck_attr.h"
#include "ck_draft.h"

class CADKEY_EXPORT CKLocation;
class CADKEY_EXPORT CKEndEntLoc;
class CADKEY_EXPORT CKCenterLoc;
class CADKEY_EXPORT CKMidpointLoc;
class CADKEY_EXPORT CKAlongEntLoc;
class CADKEY_EXPORT CKIntersectLoc;
class CADKEY_EXPORT CKDiametralLoc;
class CADKEY_EXPORT CKRadialLoc;
class CADKEY_EXPORT CKEntityLoc;
class CADKEY_EXPORT CKTwoPositionLoc;
class CADKEY_EXPORT CKFaceLoc;

namespace CKS
    {
class Location;
typedef ptr<Location> LocationPtr;

// @class CKS::Location | A Location in space defined by more than its position.  This
//  is the base class for all other CKS*Loc entities.  This base class by
//  itself is not associative.  It is the derived classes that can add entity
//  associativity to the location.
class Location : public GAtom
    {
protected:
    ~Location() {}

public:
    // @cmember || Location | Constructs a <c Location>.
    //
    // @syntax Location();
    // @syntax Location(const CKSCoord &ckscPoint, CKSEntity &rEnt);
    // @syntax Location(const CKSCoord &ckscPoint, CKSEntity &rEnt,
    //  CKSDrawInst &rInst);
    //
    // @parm const <c CKSCoord> & | ckscPoint | The coordinate of the location.
    // @parm <c CKSEntity> & | rEnt | The entity the location may refer to.
    // @parm <c CKSDrawInst> & | rInst | The instance the location may refer to.
    Location() {}

    Location(const CKSCoord &ckscPoint, CKSEntity &rEnt) :
        m_ptCoord(ckscPoint), m_pEntity(rEnt) {}

    Location(const CKSCoord &ckscPoint, CKSEntity &rEnt, CKSDrawInst &rInst) :
        m_ptCoord(ckscPoint), m_pEntity(rEnt), m_pInstance(rInst) {}

    Location(const CKLocation *pSource);

    Location(const CKSCoord &ckscPoint) : m_ptCoord(ckscPoint) {}

    static LocationPtr New(const CKLocation *);

    void GetSafeLocation(ptr<CKLocation> &pLoc) const;

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember The coordinate in 3-D space.
    CKSCoord m_ptCoord;

    // @cmember An offset from the coordinate in 3-D space, used for creating
    //  an offset from any of the location types.  When a CKS::Location object
    //  is retrieved through an SDK function, the <md Location::m_ptCoord>
    //  member already contains the offset, and the offset is filled in for
    //  reference purposes.  When a CKS::Location-derived object is passed in
    //  to an SDK function, the m_ptCoord member is ignored, and the offset
    //  member is applied to the location.  The new location object created
    //  in the core computes the proper coordinate based on the other data
    //  in the location object.  When a fixed location (CKS::Location itself
    //  and not a derived class) is provided, the m_ptCoord member is used
    //  and the m_ptOffset member is ignored.
    CKSCoord m_ptOffset;

    // @cmember Handle to the entity the location may refer to.
    CKSEntity m_pEntity;

    // @cmember Handle to the instance, if any, this location
    // is related to.
    CKSDrawInst m_pInstance;
    };

typedef ptr_array<Location> LocationArray;

// @class CKS::AlongEntLoc | An Along Entity Location.  Specifies a position along a particular
//  entity.  This is an associative location.
// @base public | <c Location>
class AlongEntLoc : public Location
    {
protected:
    ~AlongEntLoc() {}

public:
    // @cmember || AlongEntLoc | Constructors.
    //
    // @syntax AlongEntLoc();
    // @syntax AlongEntLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                     double dDist, bool bFirst, bool bAbsolute);
    // @syntax AlongEntLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                     CKSDrawInst &pInst, double dDist, bool bFirst,
    //                     bool bAbsolute);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of the location.
    // @parm <c CKSEntity> & | pEnt | The entity the location may refer to.
    // @parm <c CKSDrawInst> & | rInst | The instance the location may refer to.
    // @parm double | dDist | The distance along the entity.
    // @parm bool | bFirst | Is <p dDist> from the first end of entity?
    // @parm bool | bAbsolute | Is <p dDist> an absolute or percentage value?
    AlongEntLoc() : m_dDistance(0.0), m_bFirst(true), m_bAbsolute(false) {}

    AlongEntLoc(const CKSCoord &Point, CKSEntity &pEnt, double dDist,
                bool bFirst, bool bAbsolute) : Location(Point, pEnt),
        m_dDistance(dDist), m_bFirst(bFirst), m_bAbsolute(bAbsolute) {}

    AlongEntLoc(const CKSCoord &Point, CKSEntity &pEnt, CKSDrawInst &pInst,
                double dDist, bool bFirst, bool bAbsolute) :
        Location(Point, pEnt, pInst), m_dDistance(dDist), m_bFirst(bFirst),
        m_bAbsolute(bAbsolute) {}

    AlongEntLoc(const CKAlongEntLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember The distance along the entity of the position.
    //  This is either an absolute value, or a percentage of the
    //  entity's length.
    double m_dDistance;

    // @cmember Measure from the start of the entity
    bool m_bFirst;

    // @cmember The distance is an absolute distance from the specified end
    bool m_bAbsolute;
    };

typedef ptr<AlongEntLoc> AlongEntLocPtr;

// @class CKS::CenterLoc | A Center Location.  This location points to the center of an arc
//  entity.  This is an associative location.
// @base public | <c Location>
class CenterLoc : public Location
    {
protected:
    ~CenterLoc() {}

public:
    // @cmember || CenterLoc | Constructs a <c CenterLoc>.
    //
    // @syntax CenterLoc();
    // @syntax CenterLoc(const CKSCoord &Point, CKSEntity &pArc);
    // @syntax CenterLoc(const CKSCoord &Point, CKSEntity &pArc,
    //                   CKSDrawInst &pInst);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of arc center.
    // @parm <c CKSEntity> & | pArc | The arc that this location is the center of.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    CenterLoc() {}

    CenterLoc(const CKSCoord &Point, CKSEntity &pArc) : 
        Location(Point, pArc) {}

    CenterLoc(const CKSCoord &Point, CKSEntity &pArc, CKSDrawInst &pInst) :
        Location(Point, pArc, pInst) {}

    CenterLoc(const CKCenterLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;
    };

typedef ptr<CenterLoc> CenterLocPtr;

// @class CKS::DiametralLoc | A Diametral Location.
//  This is primarily used for edge-diametral dimensions.
//  This is an associative location
// @base public | <c Location>
class DiametralLoc : public Location
    {
protected:
    ~DiametralLoc() {}

public:
    // @cmember || DiametralLoc | Constructs a <c DiametralLoc>.
    //
    // @syntax DiametralLoc();
    // @syntax DiametralLoc(const CKSCoord &Point, CKSEntity &pArc,
    //                      bool bFirst, double dAngle);
    // @syntax DiametralLoc(const CKSCoord &Point, CKSEntity &pArc,
    //                      CKSDrawInst &pInst, bool bFirst, double dAngle);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of arc center.
    // @parm <c CKSEntity> & | pArc | The arc that this location is the center of.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    // @parm bool | bFirst | Is this the first point on the diameter?
    // @parm double | dAngle | The angle the diameter makes with the x axis.
    DiametralLoc() : m_bFirst(false), m_dAngle(0.0) {}

    DiametralLoc(const CKSCoord &Point, CKSEntity &pArc, bool bFirst,
                 double dAngle) : Location(Point, pArc), m_bFirst(bFirst),
        m_dAngle(dAngle) {}

    DiametralLoc(const CKSCoord &Point, CKSEntity &pArc, CKSDrawInst &pInst,
                 bool bFirst, double dAngle) : Location(Point, pArc, pInst),
        m_bFirst(bFirst), m_dAngle(dAngle) {}

    DiametralLoc(const CKDiametralLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember Location refers to the first point on the diameter.
    bool m_bFirst;

    // @cmember The angle the diameter makes with the x axis.
    double m_dAngle;
    };

typedef ptr<DiametralLoc> DiametralLocPtr;

// @class CKS::EndEntLoc | An EndEnt Location.  This is an associative location.
// @base public | <c Location>
class EndEntLoc : public Location
    {
protected:
    ~EndEntLoc() {}

public:
    // @cmember || EndEntLoc | Constructors.
    //
    // @syntax EndEntLoc();
    // @syntax EndEntLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                   bool bFirst, int nSeg);
    // @syntax EndEntLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                   CKSDrawInst &pInst, bool bFirst, int nSeg);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of the location.
    // @parm <c CKSEntity> & | pEnt | The entity the location may refer to.
    // @parm <c CKSDrawInst> & | rInst | The instance the location may refer to.
    // @parm bool | bFirst | Does this location reference the start of the entity?
    // @parm int | nSeg | Segment number for entities that need it.
    EndEntLoc() : m_bFirst(false), m_nSegment(0) {}

    EndEntLoc(const CKSCoord &Point, CKSEntity &pEnt, bool bFirst,
             int nSeg) : Location(Point, pEnt), m_bFirst(bFirst),
        m_nSegment(nSeg) {}

    EndEntLoc(const CKSCoord &Point, CKSEntity &pEnt, CKSDrawInst &pInst,
              bool bFirst, int nSeg) :
        Location(Point, pEnt, pInst), m_bFirst(bFirst), m_nSegment(nSeg) {}

    EndEntLoc(const CKEndEntLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember The Start of the entity is being referenced.
    bool m_bFirst;

    // @cmember Segment number for polylines, and anything else that.
    // needs it.
    int m_nSegment;
    };

typedef ptr<EndEntLoc> EndEntLocPtr;

// @class CKS::EntityLoc | An Entity Location.  This is primarily used for angular and
//  circular dimensions.  This is an associative location.
// @base public | <c Location>
class EntityLoc : public Location
    {
protected:
    ~EntityLoc() {}

public:
    // @cmember || EntityLoc | Constructs a <c EntityLoc>.
    //
    // @syntax EntityLoc();
    // @syntax EntityLoc(const CKSCoord &Point, CKSEntity &pEntity);
    // @syntax EntityLoc(const CKSCoord &Point, CKSEntity &pEntity,
    //                   CKSDrawInst &pInst);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of Entity.  This
    //       may not always be relevant, as in the case of a line for an
    //       angular dimension.  It is good practice to use the center point
    //       for arcs and the midpoint for other geometric entities.
    // @parm <c CKSEntity> & | pEnt | The Entity for the location.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    EntityLoc() {}

    EntityLoc(const CKSCoord &ckc, CKSEntity &pEnt) : Location(ckc, pEnt) {}

    EntityLoc(const CKSCoord &Point, CKSEntity &pEnt, CKSDrawInst &pInst) :
        Location(Point, pEnt, pInst) {}

    EntityLoc(const CKEntityLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;
    };

typedef ptr<EntityLoc> EntityLocPtr;

// @class CKS::IntersectLoc | An Intersection Location.  For an intersection both entities must
//  be in the same instance.  This is an associative location.
// @base public | <c Location>
class IntersectLoc : public Location
    {
protected:
    ~IntersectLoc() {}

public:
    // @cmember || IntersectLoc | Constructs a <c IntersectLoc>.
    //
    // @syntax IntersectLoc();
    // @syntax IntersectLoc(const CKSCoord &Point, CKSEntity &pEnt1,
    //                      int nSeg1, double dParm1, CKSEntity &pEnt2,
    //                      int nSeg2, double dParm2);
    // @syntax IntersectLoc(const CKSCoord &Point, CKSEntity &pEnt1,
    //                      int nSeg1, double dParm1, CKSEntity &pEnt2,
    //                      int nSeg2, double dParm2, CKSDrawInst &pInst);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of intersection
    //  of the two entities.  This is a best guess, as the actual coordinate
    //  will be calculated automatically.
    // @parm <c CKSEntity> & | pEnt1 | The first entity that defines the
    //  intersection.
    // @parm int | nSeg1 | Segment of intersection on the first entity.
    // @parm double | dParm1 | Segment of intersection on the first entity.
    // @parm <c CKSEntity> & | pEnt2 | The second entity that defines the
    //  intersection.
    // @parm int | nSeg2 | Segment of intersection on the second entity.
    // @parm double | dParm2 | Segment of intersection on the second entity.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    IntersectLoc() : Location (), m_nSegment1(0), m_dParameter1(0.0),
        m_nSegment2(0), m_dParameter2(0.0), m_b3D(true) {}

    IntersectLoc(const CKSCoord &Point, CKSEntity &pEnt1, int nSeg1,
                 double dParm1, CKSEntity &pEnt2, int nSeg2, double dParm2,
                 const CKSMatrix *pMatrix = NULL) :
        Location(Point, pEnt1), m_nSegment1(nSeg1), m_dParameter1(dParm1),
        m_pEnt2(pEnt2), m_nSegment2(nSeg2), m_dParameter2(dParm2),
        m_b3D(NULL == pMatrix)
        {
        if(!m_b3D)
            m_ckm2DMatrix = *pMatrix;
        }

    IntersectLoc(const CKSCoord &Point, CKSEntity &pEnt1, int nSeg1,
                 double dParm1, CKSEntity &pEnt2, int nSeg2, double dParm2,
                 CKSDrawInst &pInst, const CKSMatrix *pMatrix = NULL) :
        Location(Point, pEnt1, pInst), m_nSegment1(nSeg1),
        m_dParameter1(dParm1), m_pEnt2(pEnt2), m_nSegment2(nSeg2),
        m_dParameter2(dParm2), m_b3D(NULL == pMatrix)
        {
        if(!m_b3D)
            m_ckm2DMatrix = *pMatrix;
        }

    IntersectLoc(const CKIntersectLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember The segment where the intersection occurs on each entity,
    // to resolve entities that intersect multiple times.
    int m_nSegment1, m_nSegment2;

    // @cmember The parameter value where the intersection occurs on
    // each entity, to resolve entities that intersect multiple times.
    double m_dParameter1, m_dParameter2;

    // @cmember The second entity of the intersection.
    CKSEntity m_pEnt2;

    // @cmember Whether this is a 2d intersection or a 3d intersection.
    bool m_b3D;

    // @cmember Matrix for a 2d intersection.
    CKSMatrix m_ckm2DMatrix;
    };

typedef ptr<IntersectLoc> IntersectLocPtr;

// @class CKS::MidpointLoc | A Midpoint Location.  This is an associative location.
// @base public | <c Location>
class MidpointLoc : public Location
    {
protected:
    ~MidpointLoc() {}

public:
    // @cmember || MidpointLoc | Constructs a <c MidpointLoc>.
    //
    // @syntax MidpointLoc();
    // @syntax MidpointLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                     int nSegment);
    // @syntax MidpointLoc(const CKSCoord &Point, CKSEntity &pEnt,
    //                     CKSDrawInst &pInst, int nSegment);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of midpoint.
    // @parm <c CKSEntity> & | pEnt | The Entity of for the location.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    // @parm int | nSegment | The segment for entities that need it.
    MidpointLoc() : m_nSegment(0) {}

    MidpointLoc(const CKSCoord &Point, CKSEntity &pEnt, int nSegment) :
        Location(Point, pEnt), m_nSegment(nSegment) {}

    MidpointLoc(const CKSCoord &Point, CKSEntity &pEnt, CKSDrawInst &pInst,
                int nSegment) :
        Location(Point, pEnt, pInst), m_nSegment(nSegment) {}

    MidpointLoc(const CKMidpointLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember Segment number for polylines, and anything else that
    // needs it.
    int m_nSegment;
    };

typedef ptr<MidpointLoc> MidpointLocPtr;

// @class CKS::RadialLoc | A Radial Location.  This is primarily used for edge-radial
//  dimensions.
// @base public | <c Location>
class RadialLoc : public Location
    {
protected:
    ~RadialLoc() {}

public:
    // @cmember || RadialLoc | Constructs a <c RadialLoc>.
    //
    // @syntax RadialLoc();
    // @syntax RadialLoc(const CKSCoord &Point, CKSEntity &pArc,
    //                   bool bCenter, double dAngle);
    // @syntax RadialLoc(const CKSCoord &Point, CKSEntity &pArc,
    //                   CKSDrawInst &pInst, bool bCenter, double dAngle);
    //
    // @parm const <c CKSCoord> & | Point | The coordinate of arc center.
    // @parm <c CKSEntity> & | pArc | The arc that this location is the center of.
    // @parm <c CKSDrawInst> & | pInst | The instance the location may refer to.
    // @parm bool | bCenter | Is this the center point on the radius?
    // @parm double | dAngle | The angle the diameter makes with the x axis.
    RadialLoc() : m_bCenter(true), m_dAngle(0.0) {}

    RadialLoc(const CKSCoord &Point, CKSEntity &pArc, bool bCenter,
              double dAngle) :
        Location(Point, pArc), m_bCenter(bCenter), m_dAngle(dAngle) {}

    RadialLoc(const CKSCoord &Point, CKSEntity &pArc, CKSDrawInst &pInst,
                 bool bCenter, double dAngle) :
        Location(Point, pArc, pInst), m_bCenter(bCenter), m_dAngle(dAngle) {}

    RadialLoc(const CKRadialLoc *pSource);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    // @cmember Location refer to the center of the arc (vs the radial position).
    bool m_bCenter;

    // @cmember The angle the radius line makes with the x axis.
    double m_dAngle;
    };

typedef ptr<RadialLoc> PtrRadialLoc;

// @class CKS::TwoPositionLoc | A location that is the midpoint between
// two other locations.  This is an associative location.
// @base public | <c Location>
class TwoPositionLoc : public Location
    {
protected:
    ~TwoPositionLoc() {}

public:
    TwoPositionLoc(const CKTwoPositionLoc *pSource);

    TwoPositionLoc(Location *pFirstLoc, Location *pSecondLoc);

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

public:
    LocationPtr m_pFirstLoc;
    LocationPtr m_pSecondLoc;
    };

typedef ptr<TwoPositionLoc> TwoPositionLocPtr;

// @class CKS::FaceLoc | A location that is at a position on a face defined
// by U and V parameter values.  This is an associative location.
// @base public | <c Location>
class FaceLoc : public Location
    {
protected:
    ~FaceLoc() {}

public:
    FaceLoc(const CKFaceLoc *pSource);

    FaceLoc(CKSEntity &pFace, CKSDrawInst &pInst, double dU, double dV) :
        Location(CKSCoord(), pFace, pInst), m_dU(dU), m_dV(dV) {}

protected:
    SDK_EXPORT virtual void GetCKLocation(ptr<CKLocation> &pLoc) const;

    double GetU() const { return(m_dU); }
    double GetV() const { return(m_dV); }

public:
    double m_dU, m_dV;
    };

typedef ptr<FaceLoc> FaceLocPtr;
    };

#endif  /* CK_LDEF_H_LOADED */ /* MUST BE LAST LINE OF FILE */
