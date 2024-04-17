#ifndef NEXTGEN_ENGINE_CONFIG_SERVICE_H
#define NEXTGEN_ENGINE_CONFIG_SERVICE_H

#include <vector>

namespace nextgen::engine::configuration {

class IConfigObserver {
 public:
  virtual void onConfigUpdated(const RenderingEngineConfig& newConfig) = 0;
};

class ConfigurationService {
  std::vector<IConfigObserver*> observers;

 public:
  void subscribe(IConfigObserver* observer) { observers.push_back(observer); }

  void updateRenderingEngineConfig(const RenderingEngineConfig& newConfig) {
    // Update and validate newConfig
    renderingEngineConfig = newConfig;
    notifyObservers();
  }

 private:
  void notifyObservers() {
    for (auto* observer : observers) {
      observer->onConfigUpdated(renderingEngineConfig);
    }
  }
};

}  // namespace nextgen::engine::configuration

#endif
