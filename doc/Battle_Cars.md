# Battle Drones

## Principle
Battle Drones is a top down perspective game, where the player controles a drone and has to shoot down other drones.
Each drone is equipped with a canon.
Randomly spawned power-ups can be collected to make the game more intersting and diverse.


## Design Choices
- 2 game modes:
    1. Singleplayer (Player 1 vs. Bot1 vs Bot2 vs Bot3)
    2. Multiplayer (Player 1 vs Player 2 vs Bot1 vs Bot2)
	3. Duell (Player 1 vs Player 2)
- Game stats on top
- Time indicator intecrated in game stats


## Current Features
Nothing.

## Future Ideas
The following are some ideas I came up with during concept phase and development.

### Power-ups
Power-ups do spawn randomly and can be collected by the player.
#### Buff
- Shrink
- Canon: Double, Triple, Laser
- Faster
- Increase Health/Armor

#### Nerf
- Increase size
- Slow Down
- No Canon for x seconds

## More Ideas:
- Add more Game Modes: Best of 3, Increasing Speed/Damage, ...
- collision: should bounce like go karts
- "HDR": bullets are more bright than everything else
- different drone vector lists can indicate condition of drone (much damage/ damaged slightly / as new)

TODO: same speed diagonally vs horizonzal/vertival



Vec_Btn_State vs Vec_Buttons

  1. Vec_Btn_State:
	- unmittelbaren Zustand
	- 0 -> gedrückt; 1 -> nicht gedrückt
    - Für Gas/Reverse
  2. Vec_Buttons:
	- "Umschalt"-Zustand der Tasten
	- Für Menü, Pause Taste oder Schießen