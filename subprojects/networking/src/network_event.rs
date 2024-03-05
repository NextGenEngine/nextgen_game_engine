use std::collections::VecDeque;
use crate::game_data::GameData;

pub struct MessageQueue {
    queue: VecDeque<GameData>,
}

impl MessageQueue {
    pub fn new() -> Self {
        MessageQueue {
            queue: VecDeque::new(),
        }
    }

    pub fn push(&mut self, message: GameData) {
        self.queue.push_back(message);
    }

    pub fn pop(&mut self) -> Option<GameData> {
        self.queue.pop_front()
    }
}

pub struct EventDispatcher {
    // Event dispatcher state
}

impl EventDispatcher {
    pub fn new() -> Self {
        EventDispatcher {
            // Initialize event dispatcher state
        }
    }

    pub fn dispatch(&self) {
        // Dispatch network events to the appropriate handlers
    }
}