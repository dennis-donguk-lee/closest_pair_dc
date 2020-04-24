#include "closestpair.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <utility>

std::ostream& operator<< (std::ostream& os, Point const& p) {
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

std::istream& operator>> (std::istream& os, Point & p) {
	os >> p.x >> p.y;
	return os;
}

////////////////////////////////////////////////////////////////////////////////
bool operator<(Point const& a, Point const& b);
float closestPair_aux (std::vector<Point> const& pts, int size);

////////////////////////////////////////////////////////////////////////////////
float closestPair ( std::vector< Point > const& points ) {
	int size = points.size();

	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();

	std::vector< Point > sortedPts = points;
	std::sort(sortedPts.begin(), sortedPts.end());

	return closestPair_aux(sortedPts, size);
}

////////////////////////////////////////////////////////////////////////////////
bool operator<(Point const& a, Point const& b)
{
  //if (a.x == b.x)
  //{
		//return a.y < b.y;
  //}

	return a.x < b.x;
}

////////////////////////////////////////////////////////////////////////////////
float closestPair_aux ( std::vector< Point > const& pts , int size)
{
	//int size = indices.size();

	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();


	//return min_dist;
}

