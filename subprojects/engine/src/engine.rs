extern crate configuration as config_crate;


// Re-exporting configuration functions under a module
pub mod configuration {
    pub use config_crate::*;
}
