// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

/*
**  Module: FSFacetStructs.h
*/

#ifndef FSFACET_STRUCTS_H
#define FSFACET_STRUCTS_H


struct FACE_FACET_DATA
    {
    int         num_polygons;
    int         num_vertices;
    double      **vertex_list;
    int         **polygon_list;
    int         **loop_list;
    };

struct EDGE_FACET_DATA
    {
    int         num_vertices;
    double      **vertex_list;
    int         **loop_list;
    };

#endif // FSFACET_STRUCTS_H