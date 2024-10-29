#ifndef NEXTGEN_GAME_ENGINE_INTERFACES_H
#define NEXTGEN_GAME_ENGINE_INTERFACES_H

#include "lib/std_ext.h"

namespace nextgen::engine::interfaces {

using lib::std_ext::InterfaceBase;

struct IComponent : InterfaceBase {
  virtual void Initialize() = 0;
  virtual void Shutdown() = 0;
};

struct IConfigurationStrategy : InterfaceBase {
  virtual bool Configure() = 0;
};

template <typename ConfigType>
struct IConfigurable : InterfaceBase {
  virtual void ApplyConfiguration(const ConfigType& config) = 0;
};

struct IConfigValidator : InterfaceBase {
  virtual bool Validate(const void* config) = 0;
};

}  // namespace nextgen::engine::interfaces

#endif
