# FFX Skill Trees

FFX Skill Trees is an attempt to recreate some of the most in-depth skill trees from the Final Fantasy Franchise.

## Brief description:
Final Fantasy X's skill tree, called Sphere Grid, is a unique character progression system where players customize their characters
by moving along a network of nodes to learn abilities and increase stats. The grid is a visual representation of the characters' development,
allowing players to observe their growth firsthand. There are different versions of the Sphere Grid, including Regular, Standard, and Expert,
each offering varying levels of customization.

## UI Elements: 
1. Node Grid: A large, scrollable/tile-based node graph showing:
   - Slots for stat or ability upgrades.
   - Connections: Lines showing paths between nodes (highlighted if accessible).
2. Sphere Nodes: Circular icons/nodes representing stats/skills.
   - Node Icon: Different icons for strength, defense, ability, etc.
   - Highlight Ring: Changes color depending on status - Available, Activated, Locked
3. Camera Controls: Pan, zoom, and possibly rotate functionality.
4. Cursor Path: Current character’s position and the avalable paths highlighted.
   - Current Location Marker: A glowing orb or icon.
   - Reachable Nodes: Highlighted with a specific color.
   - Path Lines: Animated or glowing lines to show where a character can move next.
5. Character Info Panel:
   - Character Details: Name, Portrait, Level/Sphere Level Count, HP, MP, Stats Overview
   - Selected Node Info: Shows what stat boost or skill the selected node gives.
6. Action Menu: Pops up when you're about to interact with a node or move.
   - Options: Move, Use Sphere, Learn Ability, etc.
   - Confirm/Cancel Buttons

## Implementation Approach:
For the Data Model I'm planning to use:
1. Data Tables for:
   - The static version of the Sphere Grid (node ID, position, type, connections).
   - This will load once at game start.
2. Struct Array (copied from the Data Table) for:
   - Runtime state tracking (which nodes are unlocked, character positions, etc.).
   - Saving and modifying as the game progresses.

Code Driving the UI will be:
1. UI Manager
   - Controls info panels, action menus
   - Communicates with GridManager
2. Grid Manager
   - Holds data structure for node layout
   - Calculates movement/reachability
   - Handles input
2. CharacterCursor
   - Moves between nodes
   - Stores the path travelled from starting node
