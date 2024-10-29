#ifndef NEXTGEN_ENGINE_RENDERING_API_H
#define NEXTGEN_ENGINE_RENDERING_API_H

#include "components/engine/nextgen_game_engine_interfaces.h"
namespace nextgen::engine::rendering::api {

struct IRenderingApi : interfaces::IComponent {
  virtual void Render() = 0;
  virtual void MainLoop() = 0;
  virtual bool Exiting() = 0;
};

}  // namespace nextgen::engine::rendering::api

#endif
