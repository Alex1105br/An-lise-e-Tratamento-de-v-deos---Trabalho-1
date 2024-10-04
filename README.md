# Analise-e-Tratamento-de-videos---Trabalho-1



# Image Processing with OpenCV

This project implements various image processing techniques using OpenCV. It includes functionalities for calculating global and local histograms, applying different transformations, and enhancing images. 

## Features

- **Global Histogram Calculation**: Compute and save the histogram of an entire image, separating it into Blue, Green, and Red channels.
- **Local Histogram Calculation**: Divide an image into four partitions, calculating and saving histograms for each.
- **Image Transformations**: 
  - Logarithmic scaling
  - Linear contrast stretching (two variants)
  - Compression and expansion transformations
  - Sawtooth transformation

## Requirements

- OpenCV
- C++ Compiler (g++)


## Compilation

To compile the project, use the following command:

```bash
g++ main.cpp -o main `pkg-config --cflags --libs opencv4`
```

## Usage

Run the compiled program:

```bash
./main
```

## File Descriptions

- `histograma_global.cpp`: Contains functionality to compute and save the global histogram of an image.
- `histograma_local.cpp`: Contains functionality to compute and save the local histograms by dividing the image into four partitions.
- `transformadas.cpp`: Implements various image transformations, including logarithmic scaling and contrast expansion.


