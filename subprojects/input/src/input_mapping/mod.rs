pub struct InputMapper {
    // Fields related to input mapping
}

impl InputMapper {
    pub fn new() -> Self {
        Self {
            // Initialize fields
        }
    }

    pub fn register_action_mapping(&mut self, action: &str, device: InputDevice, key: KeyCode) {
        // Register action mapping
    }

    pub fn register_axis_mapping(&mut self, action: &str, device: InputDevice, axis: AxisCode, scale: f32) {
        // Register axis mapping
    }

    pub fn map_events(&mut self, events: &[InputEvent]) {
        // Map input events to actions and axes
    }
}

// Other necessary structs and enums
pub enum InputDevice {
    // Reuse the enum from input_capture
}

pub enum KeyCode {
    // Reuse the enum from input_capture
}

pub enum AxisCode {
    // Define axis codes
}

pub struct ActionMapping {
    // Define action mapping structure
}

pub struct AxisMapping {
    // Define axis mapping structure
}