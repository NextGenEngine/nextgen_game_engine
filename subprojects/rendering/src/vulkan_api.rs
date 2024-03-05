// Declare the extern "C" block to import C functions
extern "C" {
    fn vulkan_init();
    fn vulkan_cleanup();
    fn vulkan_create_device();
    fn vulkan_create_swapchain();
    fn vulkan_render();
}

pub fn initialize_vulkan() {
    unsafe {
        vulkan_init();
        vulkan_create_device();
        vulkan_create_swapchain();
    }
}

pub fn cleanup_vulkan() {
    unsafe {
        vulkan_cleanup();
    }
}

pub fn render() {
    unsafe {
        vulkan_render();
    }
}