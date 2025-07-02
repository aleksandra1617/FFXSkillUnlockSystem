# FFX Skill Unlock System

FFX Skill Unlock System is an attempt to recreate some of the most in-depth skill graph from the Final Fantasy Franchise.

## Brief description:
Final Fantasy X's skill graph, called Sphere Grid, is a unique character progression system where players customize their characters
by moving along a network of nodes to learn abilities and increase stats. The grid is a visual representation of the characters' development,
allowing players to observe their growth firsthand. There are different versions of the Sphere Grid, including Regular, Standard, and Expert,
each offering varying levels of customization.

## Requirements
Unreal Engine Version 5.6, ideally Visual Studio 22 or 19

## UI Elements: 
1. Node Graph: A large, scrollable/tile-based node graph showing:
   - Slots for stat or ability upgrades.
   - Connections: Lines showing paths between nodes (highlighted if accessible).

2. Graph Nodes: Circular icons/nodes representing stats/skills.
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
   - Options: Move, Use, Learn Ability, etc.
   - Confirm/Cancel Buttons

## Implementation Approach:
For the Data Model I'm planning to use:
1. Data Tables or Data Assets for:
   - The Graph Node Templates.
   - Settings for the Editor Graph Tool

2. Struct Array (copied from the Data Table) for:
   - Runtime state tracking (which nodes are unlocked, character positions, etc.).
   - Saving and modifying as the game progresses.

Code Driving the UI will be:
1. Graph Manager/Controller
   - Controls info panels, action menus
   - Communicates with Graph Model and the Graph View
     
2. Graph Model
   - Holds data structure for node layout
   - Calculates movement/reachability
 
3. Graph View
   - Handles drag and drop functionality
   - Handles displaying node connections
   - Manages Animations and any special effects on Graph Widgets

4. CharacterCursor
   - Handles selection
   - Moves between nodes
   - Stores the path travelled from starting node
