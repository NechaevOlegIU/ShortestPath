#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <iterator>
//-----------
#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"
#include "steiner.h"
#include "prim.h"

int main()
{
	char path[255]; std::cin >> path;
	
	// Divide our graph into triangles (Delaunay triangulation)
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles = triangulation.Load(path);
	
	// Create additional vertices
	Steiner<float> steiner;
	std::vector<Vector2<float>> steinerpoints = steiner.additionalVertices(triangles);
	
	// Find shortest path
	std::vector<Vector2<float>> points = triangulation.getVertices();
	Prim<float> prim;
	float result = prim.shortestPath(points, steinerpoints);
	
	return 0;
}

