#[derive(Debug)]
pub enum NetworkError {
    ConnectionError,
    SerializationError,
    DeserializationError,
    // Other network-related errors
}