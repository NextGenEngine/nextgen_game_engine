project('analytics_telemetry_module', 'rust')

analytics_telemetry_api = static_library('analytics_telemetry_api', 'analytics_telemetry_api.rs')

data_collection = static_library('data_collection', 'data_collection/mod.rs', dependencies : analytics_telemetry_api)
data_processing = static_library('data_processing', 'data_processing/mod.rs', dependencies : analytics_telemetry_api)
event_tracking = static_library('event_tracking', 'event_tracking/mod.rs', dependencies : analytics_telemetry_api)
performance_monitoring = static_library('performance_monitoring', 'performance_monitoring/mod.rs', dependencies : analytics_telemetry_api)
data_transmission = static_library('data_transmission', 'data_transmission/mod.rs', dependencies : analytics_telemetry_api)
privacy_management = static_library('privacy_management', 'privacy_management/mod.rs', dependencies : analytics_telemetry_api)

executable('game_engine', 'main.rs',
    dependencies : [
        analytics_telemetry_api,
        data_collection,
        data_processing,
        event_tracking,
        performance_monitoring,
        data_transmission,
        privacy_management,
    ]
)

# Define other Meson build configurations as needed.
