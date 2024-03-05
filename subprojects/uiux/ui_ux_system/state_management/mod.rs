pub mod stateful_widgets;
pub mod context_system;

// Define the StateManagement trait for managing the state of UI elements
pub trait StateManagement {
    fn update_state(&mut self);
}