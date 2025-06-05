# UART Telemetry Transport and Visualization

[![Status](https://img.shields.io/badge/status-WIP-orange)](https://github.com/SamCutmore/TelemetryViewer/)

## Overview

This project implements a UART transport layer for streaming telemetry data over serial communication. It serves as a testbed for developing and refining skills in:

- Serial port configuration and management (POSIX termios)
- UART data reading and framing
- Protocol layering
- Real-time telemetry visualization (planned with OpenGL)

The current implementation supports basic UART communication and frame parsing. Visualization is in progress.

## Features

- Configurable UART interface with standard serial settings  
- Background thread for continuous non-blocking reads  
- Simple framing state machine to assemble telemetry frames  

## Status

- Core UART transport is functional but may lose data at high baud rates  
- Visualization layer planned for the future  
