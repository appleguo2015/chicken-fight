# Chicken Fight
## key
- `a d`/`h k`: move left/right
- `[space]`: squat
- `q`: quit
## entity
- `chicken`: move left/right, squat
```
_%-  <- chicken
##
^^
```
- `bullet`: move left
```
*   <- bullet
```
- `be hit chicken`: dieeeeeee
```
**  <- dead chicken
##
^^
```
## how to run
```bash
git clone https://github.com/appleguo2015/chicken_fight.git
cd chicken_fight/cmake-build-debug
cmake ..
./chicken_fight
```
## AI Player
An autonomous AI agent is available to play the game automatically. The AI detects incoming bullets and dodges them by ducking.

### How to run AI
```bash
git clone https://github.com/appleguo2015/chicken_fight.git
cd chicken_fight/cmake-build-debug
cmake ..
./chicken_fight_ai
```
The AI will control the chicken. Press `q` to quit the AI simulation.

### By aPpLegUo
