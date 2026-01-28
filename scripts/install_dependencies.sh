#!/bin/bash

# Victoria Installer: Fails fast on missing dependencies
set -e

echo "🦾 Victoria-Blutenomicon Dependency Installer"
echo "Aggression Level: MAXIMUM"

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Ubuntu/Debian
    if command -v apt-get &> /dev/null; then
        sudo apt-get update
        sudo apt-get install -y \
            gcc-11 g++-11 \
            cmake ninja-build \
            libpcap-dev libssl-dev \
            doxygen graphviz \
            python3 python3-pip \
            clang-14 clang-tidy-14 \
            cppcheck valgrind
        
        # Set GCC-11 as default
        sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
        sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100
    fi
    
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    if command -v brew &> /dev/null; then
        brew update
        brew install \
            gcc@11 cmake ninja \
            libpcap openssl@3 \
            doxygen graphviz \
            python3 cppcheck \
            llvm@14
        
        echo 'export PATH="/usr/local/opt/llvm@14/bin:$PATH"' >> ~/.zshrc
    else
        echo "❌ Homebrew required on macOS"
        exit 1
    fi
else
    echo "❌ Unsupported OS: $OSTYPE"
    exit 1
fi

# Python tools (Victoria: precision tools only)
pip3 install --user \
    cpplint \
    gcovr \
    pre-commit \
    black

# Victoria Principle: Verify installation aggressively
echo "🔍 Verifying installations..."
gcc-11 --version || { echo "❌ GCC 11 missing"; exit 1; }
cmake --version || { echo "❌ CMake missing"; exit 1; }
cppcheck --version || { echo "❌ cppcheck missing"; exit 1; }

echo "✅ Victoria dependencies installed with extreme prejudice"
echo "⚠️  Remember: In cybersecurity, being nice is a vulnerability"
