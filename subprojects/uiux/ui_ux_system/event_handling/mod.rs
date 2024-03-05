pub mod input_event_queue;
pub mod event_propagation;

// Define the InputEvent enum to represent different types of input events
pub enum InputEvent {
    Click { x: f32, y: f32 },
    Touch { x: f32, y: f32 },
    // Add more event types as needed
}

// Define the EventHandling trait for processing input events
pub trait EventHandling {
    fn process_event(&mut self, event: InputEvent);
}