// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/graph.h>

void Graph_Init(struct Graph *g)
{
    DLL_Init(&g->head);
    g->nr_vertices = 0;
}

void Graph_AddVertex(struct Graph *g, struct Vertex *v)
{
    DLL_InsertTail(&g->head, &v->node);
    v->index = g->nr_vertices++;
}

void Vertex_Init(struct Vertex *v)
{
    DLL_Init(&v->node);
    v->visited = false;
    v->index = 0;
    DLL_Init(&v->adjacency);
}

void Vertex_AddEdge(struct Vertex *v, struct Edge *e)
{
    DLL_InsertTail(&v->adjacency, &e->node);
}

void Edge_Init(struct Edge *e)
{
    DLL_Init(&e->node);
    e->weight = 0;
    e->from = NULL;
    e->to = NULL;
}
