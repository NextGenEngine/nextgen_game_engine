# Example Data

To prevent the Git repository from becoming unwieldy due to large files, the example data required for this project is not included. This document explains how to obtain and set up the necessary resources. Alternatively, you can use your own models, textures, and shaders, provided they adhere to the expected formats and are placed in the correct directories.

## Expected Directory Structure

The project expects the following files to be present in the specified locations:

```bash
models/viking_room.obj - 3D model file
textures/viking_room.png - Texture image
shaders/vert.spv - Compiled vertex shader
shaders/frag.spv - Compiled fragment shader
```

## Downloading Example Data

You can download the required example data from the original sources:

### 3D Model and Texture

- **3D Model (`viking_room.obj`)**
- **Texture (`viking_room.png`)**

Download these files from the [Vulkan Tutorial resources repository](https://github.com/Overv/VulkanTutorial/tree/main/resources).

### Shaders

- **Vertex Shader (`vert.spv`)**: Download the source code [here](https://github.com/Overv/VulkanTutorial/blob/main/code/27_shader_depth.vert).
- **Fragment Shader (`frag.spv`)**: Download the source code [here](https://github.com/Overv/VulkanTutorial/blob/main/code/27_shader_depth.frag).

After downloading the shader source files, you need to compile them to SPIR-V binary format using a shader compiler like `glslangValidator`. Place the compiled `.spv` files in the `shaders` directory as specified.

## Additional Information

For detailed explanations and guidance on using these resources, refer to the [Vulkan Tutorial on Loading Models](https://vulkan-tutorial.com/Loading_models) or its [corresponding GitHub page](https://github.com/Overv/VulkanTutorial/blob/main/en/08_Loading_models.md).

## Using Your Own Assets

You are welcome to use your own models, textures, and shaders. Ensure that they are in the correct formats and placed in the appropriate directories as outlined above. This will allow the project to locate and utilize them without additional configuration.
