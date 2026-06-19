// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

/*
**  Module:                 SolidsStructures.h
*/

#ifndef SOLIDS_STRUCTURES_H
#define SOLIDS_STRUCTURES_H

#define     FS_CTYPE_UNKNOWN        0
#define     FS_CTYPE_LINE           2
#define     FS_CTYPE_ARC            3
#define     FS_CTYPE_CONIC          4
#define     FS_CTYPE_SPLINE         5
#define     FS_CTYPE_POLYLINE       7
#define     FS_CTYPE_NURB           8
#define     FS_CTYPE_CRVONSRF       9
#define     FS_CTYPE_COMPOSITE      11

typedef void FS_SURF;
typedef void FS_CURVE;
typedef void FS_SURF_FACETS;
typedef void CKSFS_SURF;
typedef void CKSFS_CURVE;
typedef void CKSFS_HUNTING_GRID;

#include "CKSMatrix.h"

struct FS_SRFCURVE
    {
    int         ncurves;            /* the number of curves             */
    FS_SURF    *base_srf;           /* the base surface (redundant)     */
    g_array<FS_CURVE *> mcurves;    /* the model space curves (on surf) */
    g_array<FS_CURVE *> pcurves;    /* the parameter space curves       */
    };

struct FS_FACE
    {
    FS_SURF     *base_srf;          /* the base surface                 */
    int          nislands;          /* the number of inner islands      */
    FS_SRFCURVE *boundary;          /* the boundary curve structure     */
    g_array<FS_SRFCURVE *> islands; /* the islands curve structures     */
    double       uvminmax[4];       /* the UV min.and max. of the trimmed region */
    };

// Structure definition for the X, Y, Z coordinates of a vertex
typedef struct
    {
    double x;
    double y;
    double z;
    } CKS_VERTEX_DATA;

// Structure definition for the components of the normal at each vertex.
typedef struct
    {
    double nX;
    double nY;
    double nZ;
    } CKS_NORMAL_DATA;

// Structure definition for the indices into the vertex array.
typedef struct
    {
    int *indices; // Indices into the vertex array
    } CKS_POLYGON_DATA;

// Structure definition for the mesh
typedef struct
    {
    int num_polygons;
    int num_vertices;
    float rgb[3];
    CKS_VERTEX_DATA *vertex_array;
    CKS_NORMAL_DATA *normal_array;
    CKS_POLYGON_DATA *polygon_list;
    } CKS_FACE_FACET_DATA;

typedef struct
    {
    // Surface Area
    double dArea;

    // Volume
    double dVolume;

    // Mass
    double dMass;

    // Surface Mass
    double dSurfaceMass;

    // Center of Mass
    CKSCoord ckscCenterOfMass;

    // Principal Moments
    CKSCoord ckscPrincipalMoments;

    // Principal axes
    CKSCoordArray ckscaPrincipalAxes;

    // Center of Mass based Moments and Product of Inertias (Ixx, Iyy, Izz, Ixy, Iyz, Ixz)
    double adCMInertias[6];

    // Center of Mass based Radius of gyration
    CKSCoord ckscCMRadiusOfGyration;

    // Center of Mass based Kinetic Energy
    double dCMKineticEnergy;

    // Center of Mass based Angular Momentum
    CKSCoord ckscCMAngularMomentum;

    // User based origin Moments and Product of Inertias (Ixx, Iyy, Izz, Ixy, Iyz, Ixz)
    double adUserInertias[6];

    // User based origin based Radius of gyration
    CKSCoord ckscUserRadiusOfGyration;

    // User based origin based Kinetic Energy
    double dUserKineticEnergy;

    // User based origin based Angular Momentum
    CKSCoord ckscUserAngularMomentum;

    } CKS_MASSPROP_DATA;


#endif // SOLIDS_STRUCTURES_H