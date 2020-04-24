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
//bool operator<(Point const& a, Point const& b);
float closestPair_aux(std::vector< Point > const& indices, int n);
float BruteForce(std::vector<Point> const& pts, int n);
float Dist(Point const& p1, Point const& p2);
float Min(float x, float y);
float StripClosest(std::vector<Point>& strip, float d);

////////////////////////////////////////////////////////////////////////////////
// The main function that finds the smallest distance  
// This method mainly uses closestPair_aux()
////////////////////////////////////////////////////////////////////////////////
float closestPair ( std::vector< Point > const& points ) {
	int size = points.size();
	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();

	std::vector< Point > sortedPts = points;
  std::sort(
    sortedPts.begin(),
    sortedPts.end(),
    [](Point const& a, Point const& b)
    {
      return a.x < b.x;
    }
  );

	return closestPair_aux(sortedPts, size);
}

//////////////////////////////////////////////////////////////////////////////////
//// Needed to sort array of points  
//// according to X coordinate  
//////////////////////////////////////////////////////////////////////////////////
//bool operator<(Point const& a, Point const& b)
//{
//  //if (a.x == b.x)
//  //{
//		//return a.y < b.y;
//  //}
//
//	return a.x < b.x;
//}

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
  std::vector<Point> const dlVec(
    indices.begin(), indices.begin() + mid
  );
  float const dl = closestPair_aux(dlVec, mid);

  std::vector<Point> const drVec(
    indices.begin() + mid, indices.end()
  );
  float const dr = closestPair_aux(drVec, size - mid);

  // Find the smaller of two distances  
  float d = Min(dl, dr);

  // Build an array strip[] that contains  
  // points close (closer than d)  
  // to the line passing through the middle point  
  std::vector<Point> strip;
  for (int i = 0; i < n; i++)
    if (abs(indices[i].x - midPoint.x) < d)
      strip.push_back(indices[i]);

  // Find the closest points in strip.  
  // Return the minimum of d and closest  
  // distance is strip[]  
  return Min(d, StripClosest(strip, d));
}

////////////////////////////////////////////////////////////////////////////////
// A Brute Force method to return the  
// smallest distance between two points  
// in P[] of size n  
////////////////////////////////////////////////////////////////////////////////
float BruteForce(std::vector<Point> const& pts, const int n)
{
	float min = std::numeric_limits<float>::max();
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
  float const xDist = p1.x - p2.x;
  float const yDist = p1.y - p2.y;

  return
    sqrtf(xDist * xDist + yDist * yDist);
}

////////////////////////////////////////////////////////////////////////////////
// A utility function to find  
// minimum of two float values  
////////////////////////////////////////////////////////////////////////////////
float Min(float x, float y)
{
  return (x < y) ? x : y;
}

////////////////////////////////////////////////////////////////////////////////
// A utility function to find the  
// distance beween the closest points of  
// strip of given size. All points in  
// strip[] are sorted accordint to  
// y coordinate. They all have an upper 
// bound on minimum distance as d.  
// Note that this method seems to be  
// a O(n^2) method, but it's a O(n)  
// method as the inner loop runs at most 6 times  
////////////////////////////////////////////////////////////////////////////////
float StripClosest(std::vector<Point>& strip, float d)
{
  float min = d; // Initialize the minimum distance as d  

  std::sort(
    strip.begin(),
    strip.end(),
    [](Point const& a, Point const& b)
    {
      return a.y < b.y;
    }
  );

  // Pick all points one by one and try the next points till the difference  
  // between y coordinates is smaller than d.  
  // This is a proven fact that this loop runs at most 6 times  
  int const size = strip.size();
  for (int i = 0; i < size; ++i)
  {
    for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
    {
      float const dist = Dist(strip[i], strip[j]);
      if (dist < min)
        min = dist;
    }
  }

  return min;
}

