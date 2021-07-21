set -ex

# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
pushd emsdk

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh

popd

# Get pblib.
git clone https://github.com/master-keying/pblib.git
pushd pblib

# Make pblib.
emcmake cmake -H. -Bbuild
cmake --build build

pushd build
emmake make install

popd
popd

# Build api.cpp.
em++ pblib/build/libpb.a --bind api.cpp -o dist/api.js
