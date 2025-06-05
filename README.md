# UART Telemetry Visualization

[![Status](https://img.shields.io/badge/status-WIP-orange)](https://github.com/SamCutmore/TelemetryViewer/)

## Overview

This project implements a UART datalink layer for streaming telemetry data over serial communication. It serves as a testbed for developing and refining skills in:

- Serial port configuration and management
- Event driven sub/pub architecture for modular services
- UART data reading and framing
- Protocol layering
- Real-time telemetry visualization (planned with OpenGL)

The current implementation supports basic UART communication and frame parsing.

## Features

- Configurable UART interface with standard serial settings  
- Background thread for continuous non-blocking reads  
- Simple framing state machine to assemble telemetry frames  

## Status

- Core UART datalink is functional
- Protocol parsing planned
- Telemetry Visualization layer planned
- Optimisation and experimentation with concurrency and prioritisation queues of events
- GUI interface planned
