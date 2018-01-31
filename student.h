/**
 * Author: David Mascharka
 * Last Updated: 6 April 2017
 *
 * Holds all the information we care about referring to a student
 */

#ifndef __STUDENT__
#define __STUDENT__

#include <string>
#include <vector>

using namespace std;

/*
  What this class represents: a row of a CSV file containing a single student
  and their FYS preferences (top N)
*/

class student
{
public:
    student(string ln, string fn, int id)
        : last_name(ln), first_name(fn), id_number(id) {}
    ~student();
    void add_fys_preference(string pref) { fys_preferences.push_back(pref); }
    string get_last_name() { return last_name; }
    string get_first_name() { return first_name; }
    int get_id_number() { return id_number; }
    vector<string> get_fys_preferences() {return fys_preferences; }

private:
    student();
    student operator=(const student&);
    string last_name;
    string first_name;
    int id_number;
    vector<string> fys_preferences;
};


#endif
