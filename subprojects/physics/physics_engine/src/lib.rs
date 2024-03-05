pub mod collision_detection;
pub mod rigid_body_dynamics;
pub mod soft_body_dynamics;
pub mod particle_systems;
pub mod physics_world;

// This is the main API interface for the Physics Engine module.
// It exposes the necessary structures, traits, and methods for other modules in the Game Engine to interact with.

// Define the main PhysicsEngine structure that will be used to interact with the physics simulation.
pub struct PhysicsEngine {
    // Physics world that contains all the entities and manages their interactions.
    pub world: physics_world::PhysicsWorld,
}

impl PhysicsEngine {
    // Initializes a new PhysicsEngine with default settings.
    pub fn new() -> Self {
        Self {
            world: physics_world::PhysicsWorld::new(),
        }
    }

    // Starts the physics simulation.
    pub fn start_simulation(&mut self) {
        self.world.start_simulation();
    }

    // Steps the physics simulation by a given time step.
    pub fn step_simulation(&mut self, time_step: f32) {
        self.world.step_simulation(time_step);
    }

    // Stops the physics simulation.
    pub fn stop_simulation(&mut self) {
        self.world.stop_simulation();
    }

    // Adds a new rigid body to the physics world.
    pub fn add_rigid_body(&mut self, body: rigid_body_dynamics::RigidBody) {
        self.world.add_rigid_body(body);
    }

    // Adds a new soft body to the physics world.
    pub fn add_soft_body(&mut self, body: soft_body_dynamics::SoftBody) {
        self.world.add_soft_body(body);
    }

    // Adds a new particle system to the physics world.
    pub fn add_particle_system(&mut self, system: particle_systems::ParticleSystem) {
        self.world.add_particle_system(system);
    }

    // Removes a rigid body from the physics world.
    pub fn remove_rigid_body(&mut self, body_id: u32) {
        self.world.remove_rigid_body(body_id);
    }

    // Removes a soft body from the physics world.
    pub fn remove_soft_body(&mut self, body_id: u32) {
        self.world.remove_soft_body(body_id);
    }

    // Removes a particle system from the physics world.
    pub fn remove_particle_system(&mut self, system_id: u32) {
        self.world.remove_particle_system(system_id);
    }
}

// Other modules can use the PhysicsEngine API to interact with the physics simulation.