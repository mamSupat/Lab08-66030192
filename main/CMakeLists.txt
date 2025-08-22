# This is the main component of the project.
# Add your project-specific source files here.
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS ".")

# Include the components
# These names must match the folder names of your components
# which are typically named after the component itself (e.g., sensor, display)
add_subdirectory(sensor)
add_subdirectory(display)
add_subdirectory(led)
