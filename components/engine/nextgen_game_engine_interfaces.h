#ifndef NEXTGEN_GAME_ENGINE_INTERFACES_H
#define NEXTGEN_GAME_ENGINE_INTERFACES_H

#include "lib/std_ext.h"

namespace nextgen::engine::interfaces {

using lib::std_ext::InterfaceBase;

struct IComponent : InterfaceBase {
  virtual void Initialize() = 0;
  virtual void Shutdown() = 0;
};

// TODO(artem): make another branch and test out this interface with
// ConfigOrchestrator instead of using fully templated version of orchestrator
// template <typename ConfigType> struct IConfigurable : InterfaceBase {
//   virtual void ApplyConfiguration(const ConfigType& config) = 0;
//   virtual ConfigType GetDefaultConfig() = 0;
//   virtual std::optional<ConfigType> ValidateConfig(
//       const ConfigType& config) = 0;
// };

}  // namespace nextgen::engine::interfaces

#endif
