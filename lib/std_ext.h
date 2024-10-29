#ifndef NEXTGEN_ENGINE_LIB_STD_EXT_H
#define NEXTGEN_ENGINE_LIB_STD_EXT_H

#include <string>

namespace nextgen::lib::std_ext {

std::string toLowerCase(const std::string& input);

struct InterfaceBase {
  InterfaceBase() = default;
  virtual ~InterfaceBase() = default;

  InterfaceBase(const InterfaceBase&) = delete;
  InterfaceBase& operator=(const InterfaceBase&) = delete;
  InterfaceBase(InterfaceBase&&) = delete;
  InterfaceBase& operator=(InterfaceBase&&) = delete;
};

}  // namespace nextgen::lib::std_ext

#endif
