pub mod layout_rendering;
pub mod event_handling;
pub mod state_management;
pub mod animation_transitions;
pub mod theme_styling;

// Define the main UI/UX System interface
pub trait UiUxSystem {
    fn create_ui_element(&self) -> Box<dyn layout_rendering::Widget>;
    fn handle_event(&mut self, event: event_handling::InputEvent);
    fn update_state(&mut self);
    fn animate_ui_elements(&mut self);
    fn apply_theme(&mut self, theme: theme_styling::Theme);
}