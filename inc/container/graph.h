// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Graph */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>
#include <stddef.h>

#include "common.h"
#include "dll.h"

struct Graph {
    struct DLL_Node head;
    size_t nr_vertices;
};

struct Vertex {
    struct DLL_Node node;
    bool visited;
    size_t index;
    struct DLL_Node adjacency;
};

struct Edge {
    struct DLL_Node node;
    int weight;
    struct Vertex *from;
    struct Vertex *to;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void Graph_Init(struct Graph *g);
extern void Graph_AddVertex(struct Graph *g, struct Vertex *v);

extern void Vertex_Init(struct Vertex *v);
extern void Vertex_AddEdge(struct Vertex *v, struct Edge *e);

extern void Edge_Init(struct Edge *e);

#ifdef __cplusplus
}
#endif
#endif /* __GRAPH_H__ */
