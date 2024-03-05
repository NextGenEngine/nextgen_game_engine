pub mod animation_controller;
pub mod transition_system;

// Define the Animation trait for animating UI elements
pub trait Animation {
    fn start_animation(&mut self);
    fn stop_animation(&mut self);
}