#include "std_ext.h"

#include <algorithm>
#include <cctype>
#include <string>

namespace nextgen::lib::std_ext {

std::string toLowerCase(const std::string& input) {
  std::string output = input;
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char chr) { return std::tolower(chr); });
  return output;
}

}  // namespace nextgen::lib::std_ext
