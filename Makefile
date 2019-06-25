openframeworks_directory = $(OF_DIRECTORY)

jobs = 8
args = -DOF_DIRECTORY=$(openframeworks_directory) -DCMAKE_EXPORT_COMPILE_COMMANDS=1

.PHONY = release debug

release:
	cmake -B build-release $(args) -DCMAKE_BUILD_TYPE=Release
	cmake --build build-release -j $(jobs) --target install

debug:
	cmake -B build-debug $(args) -DCMAKE_BUILD_TYPE=Debug
	cmake --build build-debug -j $(jobs)
