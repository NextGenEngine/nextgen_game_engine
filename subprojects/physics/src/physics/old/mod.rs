pub mod collision;
pub mod dynamics;
pub mod particle;
pub mod physics_world;

pub trait PhysicsEngine {
    fn new() -> Self
    where
        Self: Sized;
    fn initialize(&mut self);
    fn update(&mut self, delta_time: f32);
    fn add_rigid_body(&mut self, body: dynamics::rigid_body::RigidBody);
    fn add_soft_body(&mut self, body: dynamics::soft_body::SoftBody);
    fn add_particle_system(&mut self, system: particle::ParticleSystem);
    fn remove_rigid_body(&mut self, body_id: u32);
    fn remove_soft_body(&mut self, body_id: u32);
    fn remove_particle_system(&mut self, system_id: u32);
    fn step_simulation(&mut self, delta_time: f32);
    fn query_world(&self, query: physics_world::PhysicsQuery) -> Vec<physics_world::QueryResult>;
}
