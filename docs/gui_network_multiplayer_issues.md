# Terminal MVP to Final GUI and Multiplayer Issues

This document lists the issues required to move EvoSphere from the completed
terminal MVP to a polished application with a GUI and network multiplayer.
These issues are intentionally not assigned to any team member.

## 1. Stabilize the Terminal MVP

- Confirm all terminal gameplay rules work correctly.
- Remove crashes caused by invalid input or null pointers.
- Complete unit and integration tests.
- Separate game logic from terminal input and output.
- Remove direct `std::cout` and `std::cin` usage from Core and Systems.
- Return game results through data structures or status values.
- Create a stable game API that the GUI can call.
- Document the final terminal rules before starting GUI work.

## 2. Finalize the Core Game API

- Make Core structs independent from Console code.
- Make Systems independent from Console code.
- Provide functions for starting a game, taking a turn, rolling, moving, and
  resolving tiles.
- Provide read-only functions for GUI rendering.
- Create clear result data for movement, battles, captures, events, and rewards.
- Add consistent error handling for invalid actions.
- Prevent GUI code from directly changing game data incorrectly.
- Add serialization support for the complete game state.

## 3. GUI Technology and Application Setup

- Choose the GUI framework and confirm platform support.
- Configure the GUI framework in CMake.
- Create the application entry point.
- Create the main application window.
- Add window resizing and fullscreen support.
- Add a fixed or scalable coordinate system.
- Add a frame/update loop.
- Add keyboard, mouse, and controller input support if required.
- Add application shutdown handling.
- Keep the GUI layer separate from Core and Systems.

## 4. GUI Screens and Navigation

- Create a main menu screen.
- Create a new-game setup screen.
- Create player-name input screens.
- Create starter-selection screens.
- Create the main board screen.
- Create the battle screen.
- Create the event-result screen.
- Create the Guardian encounter screen.
- Create the pause screen.
- Create the settings screen.
- Create the game-over screen.
- Add navigation between screens.
- Prevent invalid screen transitions.

## 5. Board and Game Rendering

- Render the complete 40-tile board.
- Display tile names and tile types.
- Display Evoran and Guardian information.
- Display player tokens and positions.
- Display tile ownership.
- Display territory information.
- Highlight the current player's position.
- Highlight available actions.
- Show movement animations.
- Show teleport animations.
- Keep rendering synchronized with the actual game state.

## 6. Player Interface and HUD

- Display Avatar Points.
- Display Evolution Gems.
- Display the current position.
- Display owned Evorans.
- Display Evoran HP and damage.
- Display evolved status.
- Display the current player's turn.
- Display orb results.
- Display action buttons such as Roll, Battle, Capture, and Evolve.
- Disable actions that are not currently valid.
- Show clear messages for rewards, damage, captures, and defeats.

## 7. GUI Battle and Capture

- Display the player's selected Evoran.
- Display the wild or Guardian opponent.
- Display HP bars and damage information.
- Add battle animations.
- Add battle-result messages.
- Add capture confirmation.
- Display the 30% capture threshold clearly.
- Allow the player to select an owned Evoran.
- Prevent invalid battle selections.
- Display Guardian rewards and penalties.

## 8. Assets, Audio, and Presentation

- Create or collect final board artwork.
- Create Evoran sprites and portraits.
- Create Guardian artwork.
- Create player token artwork.
- Create UI icons and buttons.
- Add fonts and text styles.
- Add background music.
- Add battle and event sound effects.
- Add asset loading and caching.
- Handle missing or invalid assets safely.
- Organize assets using the asset-pipeline documentation.

## 9. Save and Load

- Choose a save-file format.
- Save player progress and game state.
- Load saved games safely.
- Validate save-file data.
- Handle missing or corrupted save files.
- Add save and load controls to the GUI.
- Prevent incompatible older saves from crashing the application.

## 10. Application Accounts and Profiles

- Decide whether accounts are required.
- Create user registration and login if accounts are needed.
- Store player profiles securely.
- Add display names and profile information.
- Add logout handling.
- Protect account data from unauthorized access.
- Add password recovery if accounts are used.

## 11. Backend and Network Architecture

- Choose the backend language and framework.
- Create a server application.
- Define the client-server communication protocol.
- Choose HTTP, WebSocket, or another suitable transport.
- Define request and response formats.
- Add server-side game-state management.
- Keep the authoritative game state on the server.
- Validate all client actions on the server.
- Prevent clients from changing their own stats or positions directly.
- Add server logging and error handling.
- Add configuration for development and production servers.

## 12. Network Multiplayer Lobby

- Create a multiplayer menu.
- Create public and private rooms.
- Add room creation and joining.
- Add room codes or invitations.
- Display connected players.
- Allow players to select or confirm their starter Evorans.
- Add a ready-up system.
- Prevent the game from starting before the required players are ready.
- Handle players leaving before the game starts.

## 13. Online Multiplayer Game Flow

- Synchronize player turns through the server.
- Synchronize movement and orb results.
- Synchronize tile ownership.
- Synchronize battles and captures.
- Synchronize events and teleporting.
- Synchronize evolution and rewards.
- Synchronize defeats and the winner.
- Prevent out-of-order actions.
- Reject actions from players whose turn has ended.
- Handle duplicate or delayed messages.
- Keep all clients visually consistent.

## 14. Connection and Recovery

- Display connection status.
- Detect connection loss.
- Attempt reconnection.
- Restore the latest valid game state after reconnecting.
- Handle a player disconnecting during their turn.
- Add a timeout for inactive players.
- Decide whether disconnected players are removed, paused, or controlled by the
  server.
- Handle server shutdown safely.
- Display useful network error messages.

## 15. Security and Fairness

- Treat the server as authoritative.
- Validate all incoming actions.
- Prevent impossible movement values.
- Prevent invalid capture results.
- Prevent duplicate rewards.
- Prevent clients from changing Avatar Points or Gems.
- Add rate limits for network requests.
- Protect private rooms and invitations.
- Secure account and session data.
- Avoid exposing sensitive server information in client logs.

## 16. Matchmaking and Ranking

- Decide whether matchmaking is required.
- Add player search or room discovery.
- Add skill or rating information if needed.
- Record match results.
- Add leaderboards if required.
- Handle cancelled or incomplete matches.
- Prevent ranking abuse and repeated-result submissions.

## 17. Testing

- Test every GUI screen.
- Test screen transitions.
- Test keyboard and mouse input.
- Test rendering with different window sizes.
- Test asset loading failures.
- Test save and load behavior.
- Test server validation.
- Test two-player and three-player online matches.
- Test disconnections and reconnections.
- Test delayed and duplicated messages.
- Test invalid and malicious client actions.
- Test multiple simultaneous matches.
- Add automated client-server integration tests.

## 18. Performance and Compatibility

- Measure GUI frame performance.
- Optimize board and sprite rendering.
- Avoid blocking network operations on the GUI thread.
- Optimize server handling for multiple matches.
- Test on the supported operating systems.
- Test different screen resolutions.
- Test slow network connections.
- Test low-performance hardware.
- Reduce application startup time.
- Reduce unnecessary asset and network traffic.

## 19. Packaging and Distribution

- Create a production build configuration.
- Package the application with all required assets.
- Package or deploy the server separately.
- Add version information.
- Create an installer or portable build.
- Add automatic update planning if required.
- Add crash reporting if appropriate.
- Write installation and usage instructions.
- Create a clean release build without debug output.

## 20. Final Completion Criteria

The final GUI and multiplayer version is complete when:

- The GUI supports the complete EvoSphere game loop.
- The GUI uses the same Core and Systems logic as the terminal version.
- Players can start and finish local games through the application.
- Players can create or join online multiplayer rooms.
- The server controls and validates the game state.
- All players receive synchronized game updates.
- Disconnects and reconnections are handled safely.
- Save/load works if included in the final scope.
- The application is tested, packaged, and documented.
