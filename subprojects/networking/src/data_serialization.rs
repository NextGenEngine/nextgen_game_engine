use crate::game_data::GameData;
use crate::network_error::NetworkError;
use serde::{Serialize, Deserialize};
use serde_json;
use bincode;

pub fn serialize<T: Serialize>(data: &T) -> Result<Vec<u8>, NetworkError> {
    // Serialize game data into a binary format
    bincode::serialize(data).map_err(|_| NetworkError::SerializationError)
}

pub fn deserialize<'a, T: Deserialize<'a>>(data: &'a [u8]) -> Result<T, NetworkError> {
    // Deserialize game data from a binary format
    bincode::deserialize(data).map_err(|_| NetworkError::DeserializationError)
}