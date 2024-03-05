use crate::scene::{Scene, SceneLoader};
use crate::ecs::{Entity, Component, System};
use crate::spatial_partitioning::SpatialIndex;
use crate::level_streaming::StreamManager;
use crate::persistence::{SaveSystem, LoadSystem};

pub struct WorldManager {
    scene_loader: SceneLoader,
    stream_manager: StreamManager,
    save_system: SaveSystem,
    load_system: LoadSystem,
}

impl WorldManager {
    pub fn new(scene_loader: SceneLoader, stream_manager: StreamManager, save_system: SaveSystem, load_system: LoadSystem) -> Self {
        WorldManager {
            scene_loader,
            stream_manager,
            save_system,
            load_system,
        }
    }

    pub fn load_scene(&mut self, scene_name: &str) -> Result<(), String> {
        self.scene_loader.load_scene(scene_name)
    }

    pub fn save_game_state(&self, file_path: &str) -> Result<(), String> {
        self.save_system.save(file_path)
    }

    pub fn load_game_state(&self, file_path: &str) -> Result<(), String> {
        self.load_system.load(file_path)
    }
}

pub fn initialize_world_manager() -> Result<WorldManager, String> {
    let scene_loader = SceneLoader::new();
    let stream_manager = StreamManager::new();
    let save_system = SaveSystem::new();
    let load_system = LoadSystem::new();
    Ok(WorldManager::new(scene_loader, stream_manager, save_system, load_system))
}