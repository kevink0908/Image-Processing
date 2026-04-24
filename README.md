# Edge Detection and Half-Toning

## Overview
This project explores core image processing techniques including **edge detection**, **digital half-toning**, and **color quantization**. It compares classical methods with learning-based approaches and evaluates performance using both qualitative visualization and quantitative metrics.

---

## Objectives
- Implement and compare edge detection algorithms  
- Evaluate performance using precision, recall, and F-measure  
- Explore grayscale and color half-toning techniques  
- Analyze trade-offs between visual quality and computational methods  

---

## Methods

## 1. Edge Detection

### Sobel Edge Detector
- Implemented from scratch using gradient filters  
- Computed horizontal and vertical gradients and combined into magnitude maps  
- Tuned thresholds to balance edge preservation and noise  

<p align="center">
  <img src="./figures/Bird_sobel_gx.png" width="250"/>
  <img src="./figures/Bird_sobel_gy.png" width="250"/>
  <img src="./figures/Bird_sobel_mag.png" width="250"/>
</p>
<p align="center"><em>Bird: Sobel gradient components and magnitude</em></p>

<p align="center">
  <img src="./figures/Deer_sobel_gx.png" width="250"/>
  <img src="./figures/Deer_sobel_gy.png" width="250"/>
  <img src="./figures/Deer_sobel_mag.png" width="250"/>
</p>
<p align="center"><em>Deer: Sobel gradient components and magnitude</em></p>

<p align="center">
  <img src="./figures/Bird_sobel_edge.png" width="300"/>
  <img src="./figures/Deer_sobel_edge.png" width="300"/>
</p>
<p align="center"><em>Final Sobel edge maps</em></p>

---

### Canny Edge Detector
- Applied multi-stage edge detection:
  - Noise reduction  
  - Gradient computation  
  - Non-maximum suppression  
  - Double thresholding  

<p align="center">
  <img src="./figures/Bird_canny_L30_H90.png" width="200"/>
  <img src="./figures/Bird_canny_L50_H150.png" width="200"/>
  <img src="./figures/Bird_canny_L70_H210.png" width="200"/>
  <img src="./figures/Bird - Canny.png" width="200"/>
</p>
<p align="center"><em>Bird: Canny results with different thresholds</em></p>

<p align="center">
  <img src="./figures/Deer_canny_L30_H90.png" width="200"/>
  <img src="./figures/Deer_canny_L50_H150.png" width="200"/>
  <img src="./figures/Deer_canny_L70_H210.png" width="200"/>
  <img src="./figures/Deer - Canny.png" width="200"/>
</p>
<p align="center"><em>Deer: Canny results with different thresholds</em></p>

---

### Structured Edge Detection
- Applied Random Forest-based structured edge detection  
- Generated probability maps and thresholded outputs  

<p align="center">
  <img src="./figures/Bird_SE_prob.png" width="250"/>
  <img src="./figures/Bird_SE_edge.png" width="250"/>
  <img src="./figures/Bird_SE_edgepercent=5.png" width="250"/>
</p>
<p align="center"><em>Bird: Structured Edge probability and binary outputs</em></p>

<p align="center">
  <img src="./figures/Deer_SE_prob.png" width="250"/>
  <img src="./figures/Deer_SE_edge.png" width="250"/>
  <img src="./figures/Deer_SE_edgepercent=25.png" width="250"/>
</p>
<p align="center"><em>Deer: Structured Edge probability and binary outputs</em></p>

<p align="center">
  <img src="./figures/Bird - Structured Edge.png" width="300"/>
  <img src="./figures/Deer - Structured Edge.png" width="300"/>
</p>
<p align="center"><em>Comparison: Structured Edge results</em></p>

---

### Edge Detection Comparison
<p align="center">
  <img src="./figures/Bird - Sobel.png" width="250"/>
  <img src="./figures/Bird - Canny.png" width="250"/>
  <img src="./figures/Bird - Structured Edge.png" width="250"/>
</p>
<p align="center"><em>Bird: Sobel vs. Canny vs. Structured Edge</em></p>

<p align="center">
  <img src="./figures/Deer - Sobel.png" width="250"/>
  <img src="./figures/Deer - Canny.png" width="250"/>
  <img src="./figures/Deer - Structured Edge.png" width="250"/>
</p>
<p align="center"><em>Deer: Sobel vs. Canny vs. Structured Edge</em></p>

---

## 2. Digital Half-Toning (Grayscale)

### Dithering Methods
<p align="center">
  <img src="./figures/fixedReflection.png" width="250"/>
  <img src="./figures/randomReflection.png" width="250"/>
</p>
<p align="center"><em>Fixed vs Random thresholding</em></p>

<p align="center">
  <img src="./figures/Bayer2Reflection.png" width="250"/>
  <img src="./figures/Bayer8Reflection.png" width="250"/>
  <img src="./figures/Bayer32Reflection.png" width="250"/>
</p>
<p align="center"><em>Bayer dithering (increasing matrix size)</em></p>

---

### Error Diffusion
<p align="center">
  <img src="./figures/FloydSteinberg.png" width="250"/>
  <img src="./figures/JJN.png" width="250"/>
  <img src="./figures/Stucki.png" width="250"/>
</p>
<p align="center"><em>Error diffusion results</em></p>

---

## 3. Color Half-Toning

### Separable Error Diffusion
<p align="center">
  <img src="./figures/Flowers_sep.png" width="400"/>
</p>
<p align="center"><em>Separable RGB error diffusion</em></p>

---

### MBVQ-Based Error Diffusion
<p align="center">
  <img src="./figures/Flowers_mbvq.png" width="400"/>
</p>
<p align="center"><em>MBVQ-based color quantization</em></p>

---

## Key Results
- Structured Edge detection achieved the best balance between precision and recall  
- Canny produced thin, well-localized edges but required careful tuning  
- Error diffusion significantly improved gradient smoothness over dithering  
- MBVQ-based diffusion improved color consistency in complex regions  

---

## Author
Kevin Kim  
M.S. Candidate, Computer Science – Artificial Intelligence  
USC Viterbi School of Engineering
