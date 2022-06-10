#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

typedef long long ll;

#define FOR(i,a) for(int i = 0; i < (a); ++i)
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define EMPTY 0
#define NONE 0 
#define WHITE 1
#define BLACK 2

#define FALSE 0
#define TRUE 1
#define UNKNOWN 2

#define OR_NODE 0
#define AND_NODE 1

#define MAX_NODES 2147483640
#define INFINITY 9223372036854700000

struct Field;
struct Board;
struct Node;
struct Solver;

#include "Field.hpp"
#include "Board.hpp"
#include "Interface.hpp"
#include "Solver.hpp"
#include "Utils.hpp"
#include "Node.hpp"
#include "PnSearch.hpp"