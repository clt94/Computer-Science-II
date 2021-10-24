/*

Defines class recorder<Timer> for recording computing times as
measured by objects of class Timer.  See also recorder.h, which
defines another recorder class capable of also recording operation
counts.

*/

/*
 * Copyright (c) 1997 Rensselaer Polytechnic Institute
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Rensselaer Polytechnic Institute makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef COMPLEXITY_RECORDER_HPP
#define COMPLEXITY_RECORDER_HPP

#include <vector>
#include <iostream>
#include <iomanip>

using std::cout;

template <class Container>
typename Container::value_type median(Container &c)
{
  typename Container::iterator midpoint = c.begin() + (c.end() - c.begin())/2;
  nth_element(c.begin(), midpoint, c.end());
  return *midpoint;
}

template <class Timer>
class recorder {
  std::vector<double> times;

public:
    void record(const Timer& t) {
      times.push_back(t.time());
  }
  void report(std::ostream& o, int repeat_factor)
  {
    o << std::fixed << std::setprecision(3) << std::setw(12)
      << median(times)/repeat_factor;
      o << "     ";
  }
  void reset() {
    times.erase(times.begin(), times.end());
  }
};

#endif
