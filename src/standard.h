#ifndef STANDARD_H
#define STANDARD_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <istream>
#include <iterator>
#include <unistd.h> //sleep
#include <utility> //pair,make_pair
#include <functional> //bind2nd
#include <cmath>
#include <ctime>



int toInt(std::string str);
float ecartType(const std::vector<float> & donnees);

#include "standard.hpp" // <-- void afficheVecteur( const std::vector<T> & vecteur );

#endif //STANDARD_H

