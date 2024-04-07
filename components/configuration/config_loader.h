#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <utility>

namespace nextgen::engine::configuration {

class IConfigLoader {
 public:
  virtual YAML::Node Load() const = 0;
  virtual void Save(const YAML::Node* config) const = 0;

  IConfigLoader() = default;
  virtual ~IConfigLoader() = 0;

 protected:
  //  -- Assignment --
  IConfigLoader& operator=(const IConfigLoader&) = default;
  IConfigLoader& operator=(IConfigLoader&&) = default;
  IConfigLoader(const IConfigLoader&) = default;
  IConfigLoader(IConfigLoader&&) = default;
};

// Specialization for loading from a file
class FileLoader : public IConfigLoader {
 private:
  std::string filePath;

 public:
  explicit FileLoader(std::string filePath) : filePath(std::move(filePath)) {}

  YAML::Node Load() const override { return YAML::LoadFile(filePath); }

  // Implementation of the save functionality for files
  void Save(const YAML::Node* config) const override {
    std::ofstream outputStream(filePath);
    if (!outputStream) {
      throw std::runtime_error("Unable to open file for writing: " + filePath);
    }
    outputStream << *config;
  }

  ~FileLoader() override = default;

 protected:
  //  -- Assignment --
  FileLoader& operator=(const FileLoader&) = default;
  FileLoader& operator=(FileLoader&&) = default;
  FileLoader(const FileLoader&) = default;
  FileLoader(FileLoader&&) = default;
};

// Specialization for loading from a string
class StringLoader : public IConfigLoader {
 private:
  std::string yamlContent;

 public:
  explicit StringLoader(std::string yamlContent)
      : yamlContent(std::move(yamlContent)) {}

  YAML::Node Load() const override { return YAML::Load(yamlContent); }
  void Save(const YAML::Node* config) const override {}

  ~StringLoader() override = default;

 protected:
  //  -- Assignment --
  StringLoader& operator=(const StringLoader&) = default;
  StringLoader& operator=(StringLoader&&) = default;
  StringLoader(const StringLoader&) = default;
  StringLoader(StringLoader&&) = default;
};

}  // namespace nextgen::engine::configuration

#endif
