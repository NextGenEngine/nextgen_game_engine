#include "config_loader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {

auto GetDefaultConfig() -> std::string_view {
  // NOTE: there is no need to implement this function at the moment.
  // Each component have its own configuration. And I do not want to
  // know it on higher level. It gives me flexibility to easily
  // change component configuration without updating higher level
  // Engine component. Components become more encapsulated and decoupled
  // from higher level components.
  return "";
}

}  // namespace

namespace nextgen::engine::configuration {

/*========================================
            FILE LOADER
========================================*/

FileLoader::FileLoader(const std::string_view& file_path)
    : m_file_path(file_path) {}

YAML::Node FileLoader::Load() {
  try {
    return YAML::LoadFile(m_file_path);
  } catch (const YAML::Exception&) {
    // If the file does not exist or is invalid, create a default config
    std::cerr << "Creating default configuration file: " << m_file_path << '\n';
    auto default_config = GetDefaultConfig();

    // Create the default configuration file
    std::ofstream output_file(m_file_path);
    if (!output_file) {
      throw std::runtime_error("Unable to create default configuration file: " +
                               m_file_path);
    }
    output_file << default_config;
    output_file.close();

    // Load the default configuration
    try {
      return YAML::Load(std::string(default_config));
    } catch (const YAML::Exception& e) {
      throw std::runtime_error(
          "Failed to load default configuration.\nError: " +
          std::string(e.what()));
    }
  }
}

void FileLoader::Save(const YAML::Node* config) {
  std::ofstream output_stream(m_file_path);
  if (!output_stream) {
    throw std::runtime_error("Unable to open file for writing: " + m_file_path);
  }
  output_stream << *config;
}

/*========================================
            STRING LOADER
========================================*/

StringLoader::StringLoader(const std::string& yaml_content)
    : m_yaml_content(yaml_content) {}

YAML::Node StringLoader::Load() {
  try {
    return YAML::Load(m_yaml_content);
  } catch (const YAML::Exception& e) {
    throw std::runtime_error(
        "Failed to load configuration from string.\nError: " +
        std::string(e.what()));
  }
}

void StringLoader::Save(const YAML::Node* /*config*/) {
  // Do nothing or implement saving logic if needed
}

}  // namespace nextgen::engine::configuration
