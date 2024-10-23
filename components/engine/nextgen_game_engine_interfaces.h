#ifndef NEXTGEN_GAME_ENGINE_INTERFACES_H
#define NEXTGEN_GAME_ENGINE_INTERFACES_H

namespace nextgen::engine::interfaces {

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct IComponent {
  virtual void Initialize() = 0;
  virtual void Shutdown() = 0;
  virtual ~IComponent() = default;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct IConfigurationStrategy {
  virtual bool Configure() = 0;
  virtual ~IConfigurationStrategy() = default;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct IConfigurable {
  virtual void ApplyConfiguration(const void* config) = 0;
  virtual ~IConfigurable() = default;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct IConfigValidator {
  virtual bool Validate(const void* config) = 0;
  virtual ~IConfigValidator() = default;
};

}  // namespace nextgen::engine::interfaces

#endif
