pub mod widget_tree;
pub mod layout_engine;
pub mod rendering_backend;

// Define the Widget trait, which will be the base for all UI elements
pub trait Widget {
    fn draw(&self, renderer: &rendering_backend::Renderer);
    fn set_position(&mut self, x: f32, y: f32);
    fn set_size(&mut self, width: f32, height: f32);
}