#include "components/engine/nextgen_game_engine.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>

#include "components/configuration/config_loader.h"

using nextgen::engine::NextGenEngine;

auto inline init_engine() -> std::optional<std::unique_ptr<NextGenEngine>> {
  try {
    return std::make_unique<NextGenEngine>(
        std::make_unique<nextgen::engine::configuration::FileLoader>(
            "config.yaml"));
  } catch (std::exception& e) {
    std::cout << "Engine initialization failed" << e.what() << "\n";
    return std::nullopt;
  }
}

void inline game_loog() {}

int inline successful_exit(int code) {
  std::cout << "Successful exit"
            << "\n";
  return code;
}

int main() {
  auto engine = init_engine();
  if (!engine) {
    return successful_exit(EXIT_FAILURE);
  }

  game_loog();

  engine.reset();

  return successful_exit(EXIT_SUCCESS);
}
