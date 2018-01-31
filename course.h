/**
 * Author: David Mascharka
 * Last Updated: 6 April 2017
 *
 * Holds all the information we care about relating to a course
 */

#ifndef __COURSE__
#define __COURSE__

#include <string>

using namespace std;

class course
{
public:
    course(string cn, int c, int slots)
        : course_number(cn), crn(c), num_slots_available(slots) {}
    ~course();
    string get_course_number() { return course_number; }
    int get_crn() { return crn; }
    int get_num_slots_available() { return num_slots_available; }
    
private:
    course();
    course operator=(const course&);
    string course_number;
    int crn;
    int num_slots_available;
};

#endif
