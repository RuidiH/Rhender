# Run with: python3 build.py
import os
import platform

# (1)==================== COMMON CONFIGURATION OPTIONS ======================= #
COMPILER="g++ -std=c++17"   # The compiler we want to use 
                                #(You may try g++ if you have trouble)
SOURCE="./src/*.cpp"    # Where the source code lives
EXECUTABLE="proj"       # Name of the final executable
GLSLC = "glslc"         # Shader compiler
# ======================= COMMON CONFIGURATION OPTIONS ======================= #

# (2)=================== Platform specific configuration ===================== #
# For each platform we need to set the following items
ARGUMENTS=""            # Arguments needed for our program (Add others as you see fit)
INCLUDE_DIR=""          # Which directories do we want to include.
LIBRARIES=""            # What libraries do we want to include

if platform.system()=="Linux":
    ARGUMENTS="-D LINUX" # -D is a #define sent to preprocessor
    INCLUDE_DIR=(
        "-I ./include/ "
        "-I ./../common/thirdparty/glm/"
        "-I$VULKAN_SDK/include"     
    )
    LIBRARIES="-lSDL2 -lvulkan"
elif platform.system()=="Darwin":
    ARGUMENTS="-D MAC" # -D is a #define sent to the preprocessor.
    INCLUDE_DIR="-I ./include/ -I/Library/Frameworks/SDL2.framework/Headers -I./../common/thirdparty/old/glm "
    LIBRARIES="-F/Library/Frameworks -framework SDL2"
elif platform.system()=="Windows":
    GLSLC = "C:\VulkanSDK\1.3.275.0\Bin\glslc.exe"
    COMPILER="g++ -std=c++17" # Note we use g++ here as it is more likely what you have
    ARGUMENTS="-D MINGW -std=c++17 -static-libgcc -static-libstdc++" 
    INCLUDE_DIR="-I./include/ -I./../common/thirdparty/old/glm/ -IC:/VulkanSDK/1.3.275.0/Include -LC:/VulkanSDK/1.3.275.0/Lib"
    EXECUTABLE="proj.exe"
    LIBRARIES="-lmingw32 -lSDL2main -lSDL2 -lvulkan-1"
# (2)=================== Platform specific configuration ===================== #

# (3)====================== Building the Executable ========================== #
# Build a string of our compile commands that we run in the terminal
compileString=COMPILER+" "+ARGUMENTS+" -o "+EXECUTABLE+" "+" "+INCLUDE_DIR+" "+SOURCE+" "+LIBRARIES
# Print out the compile string
# This is the command you can type
print("============v (Command running on terminal) v===========================")
print("Compilng on: "+platform.system())
print(compileString)
print("========================================================================")
# Run our command
os.system(compileString)
# ========================= Building the Executable ========================== #


# Why am I not using Make?
# 1.)   I want total control over the system. 
#       Occassionally I want to have some logic
#       in my compilation process (like searching for missing files).
# 2.)   Realistically our projects are 'small' enough 
#       this will not matter.
# 3.)   Feel free to implement your own make files or autogenerate it from this
#       script
# 4.)   It is handy to know Python

# (4)====================== Compiling Shaders =================================#
# Define shader source and output directories
shader_dir = "shaders"
shader_files = ["main_shader.vert", "main_shader.frag"]

for shader in shader_files:
    shader_source = os.path.join(shader_dir, shader)
    shader_output = os.path.join(shader_dir, shader + ".spv")
    # Build the shader compile command
    shader_compile_cmd = f"{GLSLC} {shader_source} -o {shader_output}"
    print(f"Compiling shader: {shader_source}")
    print(shader_compile_cmd)
    # Run the shader compile command
    result = os.system(shader_compile_cmd)
    if result != 0:
        print(f"Failed to compile shader: {shader_source}")
        exit(1)
# ========================= Compiling Shaders =================================#

# (5)====================== Running the Executable =========================== #
# Optionally, you can run the executable automatically
print("Running the executable...")
if platform.system() == "Windows":
    os.system(EXECUTABLE)
else:
    os.system(f"./{EXECUTABLE}")
# ========================= Running the Executable =========================== #