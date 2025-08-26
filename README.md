# Procedural Island Generator

A C++ SFML project demonstrating **procedural island generation** with adjustable noise parameters, editable tiles presets, and real-time preview.

---

## Features

### Procedural Generation
- Generates islands using **fractal noise** + **falloff maps** .
- Supports **multiple islands** via `minIslands` / `maxIslands`.
- Configurable **island shapes** using `minIslandSizeFactor` / `maxIslandSizeFactor`.
- Height-based **tiles**: DeepWater ? ShallowWater ? Sand ? Grass ? DarkGrass ? Mountain.

### User Interface (ImGui)
- **Noise Controls**: Map size, seed, scale, octaves, persistence, lacunarity.
- **Island Settings**: Min/max islands, min/max island size.
- **Tile Editor**: Adjust tile colors and height thresholds.
- **General Controls**: Regenerate island, save island as PNG.

### Real-time Updates
- Auto-update island when parameters or tiles change.
- Zoom and pan with mouse drag and scroll.
- Reset view to fit the entire island.

### Persistence
- Save and load **NoiseParams** on exit/startup.
- Save **island images (PNG)** with custom filenames.
- Tile thresholds and colors persist during session.

---

## Project Structure

/src
- Noise.hpp/.cpp // Noise creating 
- IslandFallOff.hpp/.cpp // Falloff mask to combine with main noise 
- NoiseManager.hpp/.cpp // Procedural generation logic handler
- TileManager.hpp/.cpp // Tile definitions and editing
- UIManager.hpp/.cpp // ImGui interface
- SaveManager.hpp/.cpp // Saving/loading parameters, tiles
- NoiseParams.hpp // Noise parameter struct
- IslandGenerator.cpp // Main application loop


- **SFML**: Graphics rendering and window management.
- **ImGui-SFML**: GUI for real-time controls.
- **TileManager**: Encapsulates tiles, colors, and thresholds.
- **SaveManager**: Handles saving parameters, tiles, and images.

---

## Controls

| Action | Input |
|--------|-------|
| Pan view | Left-click + drag |
| Zoom view | Mouse scroll |
| Reset view | `R` key |
| Regenerate island | Regenerate button |
| Save island | Save PNG button (filename input) |
| Adjust tile colors | Tile Editor color pickers |
| Adjust tile thresholds | Tile Editor sliders |

---

## Usage

1. Clone the repository.
2. Ensure **SFML** and **ImGui-SFML** are installed and linked.
3. Build the project in your preferred IDE.
4. Run `IslandGenerator.exe` (or your compiled binary).
5. Adjust parameters and tiles, pan/zoom the view, and save islands.

---

## Future Enhancements 
- Animated effects (clouds or water).
- Procedural biomes (desert, forest, snow).
- Dynamic tile creation.
- MetaData to load and save islands.

---

## License
MIT License - free to use and modify.