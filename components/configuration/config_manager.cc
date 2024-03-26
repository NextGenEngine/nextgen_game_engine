#include "config_manager.h"

#include <string>

#include "components/configuration/config_loader.h"

template <typename LoaderType>
ConfigManager::ConfigManager(LoaderType loader,
                             const std::string &fileNameOrYamlContent)
    : config(loader.load(fileNameOrYamlContent)) {}

ConfigManager ConfigManager_File(const std::string &fileName) {
  return ConfigManager((FileLoader()), fileName);
}

ConfigManager ConfigManager_String(const std::string &yamlContent) {
  return ConfigManager((StringLoader()), yamlContent);
}
