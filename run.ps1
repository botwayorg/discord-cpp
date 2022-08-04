if (Test-Path -path build) {
    cd build
    make -j
} else {
    New-Item -ItemType "directory" -Path build
    cd build
    cmake ..
    make -j
}
