// lib.rs - The main library file that exposes the Resource Management module API

mod asset_loader;
mod asset_cache;
mod asset_handle;
mod hot_reloader;

pub use asset_loader::AssetLoader;
pub use asset_cache::AssetCache;
pub use asset_handle::AssetHandle;
pub use hot_reloader::HotReloader;

// Additional code to integrate the components will go here