#include "stdafx.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"
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

bool isEqual(float x, float y)
{
	return std::fabs(x - y) < 0.001;
}

SCENARIO("WRONG FILE - Empty file") {
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles = triangulation.Load("files/empty.dat");

	Steiner<float> steiner;
	std::vector<Vector2<float>> steinerpoints = steiner.additionalVertices(triangles);

	std::vector<Vector2<float>> points = triangulation.getVertices();
	Prim<float> prim;
	float result = prim.shortestPath(points, steinerpoints);
	REQUIRE(result == 0);
}

SCENARIO("WRONG FILE - Totally wrong file") {
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles = triangulation.Load("files/totallywrong.dat");

	Steiner<float> steiner;
	std::vector<Vector2<float>> steinerpoints = steiner.additionalVertices(triangles);

	std::vector<Vector2<float>> points = triangulation.getVertices();
	Prim<float> prim;
	float result = prim.shortestPath(points, steinerpoints);
	REQUIRE(result == 0);
}

SCENARIO("WRONG FILE - Wrong way to file") {
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles;
	REQUIRE_THROWS(triangles = triangulation.Load("wrongwaymeowmeow"));
}

SCENARIO("GOOD FILE - Cant divide into triangles") {
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles = triangulation.Load("files/notriangle.dat");
	REQUIRE(triangles.size() == 0);
	Steiner<float> steiner;
	std::vector<Vector2<float>> steinerpoints = steiner.additionalVertices(triangles);

	std::vector<Vector2<float>> points = triangulation.getVertices();
	Prim<float> prim;
	float result = prim.shortestPath(points, steinerpoints);
	REQUIRE(isEqual(result, 2.82843));
}

SCENARIO("GOOD FILE - Full run") {
	Delaunay<float> triangulation;
	std::vector<Triangle<float>> triangles;
	REQUIRE_NOTHROW(triangles = triangulation.Load("files/good.dat"));
	REQUIRE(triangles.size() == 3);
	Steiner<float> steiner;
	std::vector<Vector2<float>> steinerpoints = steiner.additionalVertices(triangles);
	REQUIRE(steinerpoints.size() == 3);
	std::vector<Vector2<float>> points = triangulation.getVertices();
	Prim<float> prim;
	float result = prim.shortestPath(points, steinerpoints);
	REQUIRE(isEqual(result, 5.4641) == 1);
}
