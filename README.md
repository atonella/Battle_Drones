# Vectrocopters

A top-down perspective arena shooter for the Vectrex console. Take control of a vectrocopter and dominate all the other vectrocopters!

## Game Modes
1. **Singleplayer**  
   One human vs. three computer-controlled vectrocopters.  
2. **Multiplayer**  
   Two human players vs. two computer-controlled vectrocopters.  
3. **Duel**  
   Two human players in direct 1-on-1 combat.

All vectrocopters are enemies—there are no teams. Only the first vectrocopter to reach 10 kills wins.

## Controls
Vectrocopters uses the built-in Vectrex control panel:
- **Button 1**: Pause / Resume  
- **Button 4**: Fire  
- **Joystick**: Move in 8 directions  

## How to Play

### Mode Selection
- After boot in the home screen, scroll through game modes with **Button 2** / **Button 3**.  
- Confirm your choice with **Button 4**.

### Objective
Shoot down other vectrocopters while avoiding their shots.  
The first vectrocopter to score 10 kills wins.

### Respawning
When destroyed, you respawn after a 4-second cooldown at a random location. Unlimited lives.

### Scoring Rules
- Only the final hit gives credit for a kill.  
- No assists possible.

## Pause & Scoreboard
Press **Button 1** to pause. While paused:
- Game logic is frozen but the scene continues to render.  
- The current scoreboard is displayed.  
- Only the player who paused can resume with **Button 1**.

## After the Battle
When someone reaches 10 kills:
- A summary screen shows the winner and stats (kills & deaths).  
- An asterisk indicates the champion.  
- Press **Button 1** to return to mode selection or **Button 4** to play again.

## Health & Damage
- Vectrocopters start with **50 HP**.  
- Each bullet hit subtracts **10 HP**.  
- At 0 HP, the vectrocopter is destroyed and removed from the arena.
