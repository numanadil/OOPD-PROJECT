# Modeling and Simulation of WiFi Communication

## Overview

The **Modeling and Simulation of WiFi Communication** project aims to simulate various WiFi communication protocols (WiFi 4, WiFi 5, and WiFi 6) to model and analyze key parameters such as throughput and latency. The simulation includes different access points (APs) using the CSMA/CA protocol for WiFi 4, MU-MIMO for WiFi 5, and OFDMA for WiFi 6.

By running simulations for different user counts (1, 10, and 100 users), this project provides valuable insights into how these protocols behave under different network conditions.

## Features

- **WiFi 4 (CSMA/CA):** Implements basic carrier sense multiple access with collision avoidance (CSMA/CA) for throughput and latency measurement.
- **WiFi 5 (MU-MIMO):** Simulates multi-user, multiple-input, multiple-output (MU-MIMO) technology to improve throughput for multiple users.
- **WiFi 6 (OFDMA):** Simulates orthogonal frequency division multiple access (OFDMA) to demonstrate more efficient spectrum usage and lower latency for multiple users.
  
Each of these protocols has unique transmission characteristics, which are modeled in this project to visualize their impact on network performance.

## Project Structure

- **WiFiSimulator.h**: Header file defining classes for packets, users, access points, and various WiFi standards (WiFi 4, WiFi 5, WiFi 6).
- **WiFiSimulator.cpp**: Implementation of classes and methods for WiFi simulation.
- **wifi4.cpp**: Main program for simulating WiFi 4 (CSMA/CA).
- **wifi5.cpp**: Main program for simulating WiFi 5 (MU-MIMO).
- **wifi6.cpp**: Main program for simulating WiFi 6 (OFDMA).
- **Makefile**: Build automation tool for compiling and linking the project.

## Requirements

To build and run the project, you will need:
- **g++ (GNU C++ Compiler)**: For compiling the C++ code.
- **Make**: For building the project with the provided Makefile.

## Installation and Setup

### 1. Clone the Repository

Clone this repository to your local machine using the following command:

```bash
git clone https://github.com/yourusername/WiFi-Communication-Simulation.git
cd WiFi-Communication-Simulation
