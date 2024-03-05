mod world_manager;
mod scene;
mod ecs;
mod spatial_partitioning;
mod level_streaming;
mod persistence;

fn main() {
    let mut world_manager = world_manager::initialize_world_manager().expect("Failed to initialize world manager");
    world_manager.load_scene("main_scene").expect("Failed to load scene");
}