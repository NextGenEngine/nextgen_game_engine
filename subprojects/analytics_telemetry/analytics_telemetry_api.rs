// This file defines the API interface for the Analytics and Telemetry module.

pub mod data_collection;
pub mod data_processing;
pub mod event_tracking;
pub mod performance_monitoring;
pub mod data_transmission;
pub mod privacy_management;

// Structures, traits, and methods/functions/interfaces that the module provides to other modules in the Game Engine.

// EventListener trait to be implemented by any component that listens for game events.
pub trait EventListener {
    fn on_event(&self, event: &GameEvent);
}

// MetricSampler trait to be implemented by components that sample performance and usage metrics.
pub trait MetricSampler {
    fn sample(&self) -> Metric;
}

// DataAggregator trait for components that combine data from multiple sources.
pub trait DataAggregator {
    fn aggregate(&self, data: Vec<DataPoint>) -> AggregatedData;
}

// CustomEventLogger trait for logging custom events.
pub trait CustomEventLogger {
    fn log_event(&self, event: CustomEvent);
}

// PerformanceMonitor trait for monitoring resource usage and frame timing.
pub trait PerformanceMonitor {
    fn monitor_resource_usage(&self) -> ResourceUsage;
    fn monitor_frame_timing(&self) -> FrameTiming;
}

// DataTransmitter trait for handling the transmission of collected data.
pub trait DataTransmitter {
    fn transmit(&self, data: AggregatedData);
}

// PrivacyManager trait for managing user consent and data anonymization.
pub trait PrivacyManager {
    fn track_consent(&self, user_consent: UserConsent);
    fn anonymize_data(&self, data: &mut AggregatedData);
}

// Structures representing different data types used in the module.
pub struct GameEvent {
    // Details of the game event.
}

pub struct Metric {
    // Details of the metric.
}

pub struct DataPoint {
    // Details of a single data point.
}

pub struct AggregatedData {
    // Details of aggregated data.
}

pub struct CustomEvent {
    // Details of a custom event.
}

pub struct ResourceUsage {
    // Details of resource usage.
}

pub struct FrameTiming {
    // Details of frame timing.
}

pub struct UserConsent {
    // Details of user consent.
}