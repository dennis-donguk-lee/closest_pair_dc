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
float closestPair_aux(std::vector< Point > const& indices, int n);
float BruteForce(std::vector<Point> const& pts, int n);
float Dist(Point const& p1, Point const& p2);
float min(float x, float y);

////////////////////////////////////////////////////////////////////////////////
// The main function that finds the smallest distance  
// This method mainly uses closestPair_aux()
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
// Needed to sort array of points  
// according to X coordinate  
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
// A recursive function to find the  
// smallest distance. The array P contains  
// all points sorted according to x coordinate
////////////////////////////////////////////////////////////////////////////////
float closestPair_aux ( std::vector< Point > const& indices, int n)
{
	//int size = indices.size();
  int size = n;
	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();

  // If there are 2 or 3 points, then use brute force  
  if (size <= 3)
    return BruteForce(indices, size);

  // Find the middle point  
  int mid = size / 2;
  Point midPoint = indices[mid];

  // Consider the vertical line passing  
  // through the middle point calculate  
  // the smallest distance dl on left  
  // of middle point and dr on right side  
  float const dl = closestPair_aux(indices, mid);
  std::vector<Point> const drVec(
    indices.begin() + mid, indices.end()
  );
  float const dr = closestPair_aux(drVec, size - mid);

  // Find the smaller of two distances  
  float d = min(dl, dr);

	//return min_dist;
}

////////////////////////////////////////////////////////////////////////////////
// A Brute Force method to return the  
// smallest distance between two points  
// in P[] of size n  
////////////////////////////////////////////////////////////////////////////////
float BruteForce(std::vector<Point> const& pts, const int n)
{
	float min = FLT_MAX;
  for (int i = 0; i < n; ++i)
  {
    for (int j = i + 1; j < n; ++j)
    {
      float dist = Dist(pts[i], pts[j]);
      if (dist < min)
      {
        min = dist;
      }
    }
  }

  return min;
}

////////////////////////////////////////////////////////////////////////////////
// A utility function to find the  
// distance between two points  
////////////////////////////////////////////////////////////////////////////////
float Dist(Point const& p1, Point const& p2)
{
  return
    sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

////////////////////////////////////////////////////////////////////////////////
// A utility function to find  
// minimum of two float values  
////////////////////////////////////////////////////////////////////////////////
float min(float x, float y)
{
  return (x < y) ? x : y;
}

