# Use a base image with GCC including the necessary tools for C/C++ compilation
FROM gcc:9.2.0

# Set the working directory in the container
WORKDIR /usr/src/app

# Install required packages: 
# - cmake for building Google Test
# - git to clone Google Test
# - ARM GCC toolchain for STM32 development
RUN apt-get update -qq \
    && apt-get install --no-install-recommends -qq cmake git \
    && apt-get install -qq gcc-arm-none-eabi \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Clone and install Google Test
RUN git clone --depth=1 -b master https://github.com/google/googletest.git \
    && mkdir googletest/build \
    && cd googletest/build \
    && cmake .. \
    && make \
    && make install \
    && rm -rf /usr/src/app/googletest

# Return to the base working directory
WORKDIR /usr/src/app

# Copy your project files into the Docker container
COPY . .

# Create an object directory for the build artifacts
RUN mkdir obj

# Adjust your Makefile to use the ARM GCC toolchain and to compile the tests using Google Test.
# The Makefile should be configured to compile your STM32 code and the Google Test based tests.

# Run the make command to build your project
RUN make

# Specify the command to run tests. Replace `test_executable` with the actual test executable name.
CMD [ "./LineTracking" ]
