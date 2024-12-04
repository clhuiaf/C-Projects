#include <sstream>
#include "num.h"
#include "raise.h"

using namespace std;

int to_num(const char s[]) {
    int res;
    istringstream ss (s);
    ss >> res;
    if ( !ss.eof() )
        raise(invalid_num);
    else
        return res;
}
