#include "std_ext.h"

#include <algorithm>
#include <cctype>
#include <string>

namespace nextgen::lib::std_ext {

std::string toLowerCase(const std::string& input) {
  // std::string output = input;
  // std::transform(output.begin(), output.end(), output.begin(),
  //                [](unsigned char chr) { return std::tolower(chr); });
  // return output;
  // Use ranges to transform each character to lowercase
  std::string output = input;
  std::ranges::transform(output, output.begin(), [](unsigned char chr) {
    return static_cast<char>(std::tolower(chr));
  });
  return output;
}

}  // namespace nextgen::lib::std_ext
