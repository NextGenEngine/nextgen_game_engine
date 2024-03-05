mod vulkan_api;
mod graphics_abstractor;
mod game_mechanics;
mod scene_management;
mod timeline_management;
mod input_management;
mod rendering;

// pub use vulkan_api::*;
// pub use graphics_abstractor::*;
// pub use game_mechanics::*;
// pub use scene_management::*;
// pub use timeline_management::*;
// pub use input_management::*;
// pub use rendering::*;

use crate::vulkan_api::initialize_vulkan;
use crate::vulkan_api::cleanup_vulkan;
use crate::vulkan_api::render;


fn main() {
    println!("NextGen Game Engine Example Scene");

    // Setup Vulkan Environment
    // if initialize_vulkan().is_err() {
    //     eprintln!("Failed to initialize Vulkan");
    //     return;
    // }

    initialize_vulkan();

    // Load Shaders, Create Graphics Pipeline, and Render Shapes
    // This is a placeholder for the actual rendering logic
    // if render().is_err() {
    //     eprintln!("Failed to render frame");
    // }

    render();

    // Cleanup
    cleanup_vulkan();
}