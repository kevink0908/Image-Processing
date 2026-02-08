CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

SRC_DIR := src
OBJ_DIR := obj
TARGET  := hw2

# OpenCV
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS   := $(shell pkg-config --libs opencv4)

CXXFLAGS += $(OPENCV_CFLAGS)

# all the source files will be listed here.
SRCS := \
  main.cpp \
  image_io.cpp \
  util.cpp \
  kernels.cpp \
  sobel.cpp \
  canny_opencv.cpp \
  halftone_threshold.cpp \
  halftone_dither.cpp \
  error_diffusion.cpp \
  color_halftone.cpp \
  mbvq.cpp

OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(OPENCV_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
