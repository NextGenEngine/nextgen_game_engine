pub struct Entity(u32);

pub trait Component {
    // Component data
}

pub trait System {
    fn update(&mut self, entity: &Entity);
}

// Implementations for Entity, Component, and System will go here