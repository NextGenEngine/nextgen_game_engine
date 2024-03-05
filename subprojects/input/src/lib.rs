mod input_capture;
mod event_processing;
mod input_mapping;
mod input_state_management;

pub use input_capture::{InputDevice, KeyCode, InputCapture};
pub use event_processing::{EventProcessor, InputEvent};
pub use input_mapping::{ActionMapping, AxisMapping, InputMapper};
pub use input_state_management::{InputState, InputStateManager};

pub struct InputSystem {
    input_capture: input_capture::InputCapture,
    event_processor: event_processing::EventProcessor,
    input_mapper: input_mapping::InputMapper,
    input_state_manager: input_state_management::InputStateManager,
}

impl InputSystem {
    pub fn new() -> Self {
        Self {
            input_capture: input_capture::InputCapture::new(),
            event_processor: event_processing::EventProcessor::new(),
            input_mapper: input_mapping::InputMapper::new(),
            input_state_manager: input_state_management::InputStateManager::new(),
        }
    }

    pub fn initialize(&mut self) {
        // Initialize the input system components here
    }

    pub fn register_action_mapping(&mut self, action: &str, device: InputDevice, key: KeyCode) {
        self.input_mapper.register_action_mapping(action, device, key);
    }

    pub fn register_axis_mapping(&mut self, action: &str, device: InputDevice, axis: AxisCode, scale: f32) {
        self.input_mapper.register_axis_mapping(action, device, axis, scale);
    }

    pub fn is_action_pressed(&self, action: &str) -> bool {
        self.input_state_manager.is_action_pressed(action)
    }

    pub fn get_axis_value(&self, action: &str) -> f32 {
        self.input_state_manager.get_axis_value(action)
    }

    pub fn update(&mut self) {
        let events = self.input_capture.capture_events();
        let processed_events = self.event_processor.process_events(events);
        self.input_mapper.map_events(&processed_events);
        self.input_state_manager.update(&processed_events);
    }
}

pub enum InputError {
    DeviceNotSupported,
    InvalidMapping,
    // Other error cases
}

// Other necessary types and enums
pub enum InputDevice {
    Keyboard,
    Mouse,
    Gamepad,
    Touchscreen,
}

pub enum KeyCode {
    // Define key codes
}

pub enum AxisCode {
    // Define axis codes
}

// Other necessary structs and traits