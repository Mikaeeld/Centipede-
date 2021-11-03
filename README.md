# Software Development II - Course Project - Centipede++

## Project Members
| Name | Student Number |
|-|-|
| Shivun Chinniah  |2090476|
| Mikaeel Dindar | 2128031 |

## Overview
Centipede++ is based on the arcade games 'Centipede', 'Millipede' or also known as 'Multipede'.
This re-implementation of the game was mainly inspired by 'Multipede' available online: https://archive.org/details/arcade_multiped

## Implementation
Centipede++ is implemented using C++ and the SFML library (https://sfml-dev.org)

### High Level Overview of Implementation

A `Game` class manages which `State` or Scene requires Input, Updates, or Rendering.

A `State` interface can be implemented to form specific states/scenes such as a:
- `PlayState` --> Game Play
- `SplashState` --> Beginning Instructions Screen
- `PauseState` --> Pause Screen
- and `GameOverState` --> Game Over Screen

From which the `Game` class will switch between, to form different scenes.

A specific state is responsible for handling input, providing renderable (SFML Drawable) objects, and updating the position of these objects over time to create motion.

To simplify the responsibility of a state for cases where there are many renderable objects such as the game sprites, another abstraction could be made.

An `EntityManager` stores a list of `GameEntity` objects. The `EntityManager` is responsible for calling an entity's update function; where an entity can update its own position or even update its texture to create animations. Since the `GameEntity`  objects do not know where the other entities are, it is also the responsibility of `EntityManager` to check for `GameEntity`-`GameEntity` collisions; It would then call the entity's collision-handling function providing information about the other entity. The entity manager will also handle requests that the `GameEntity` objects might make such as: requesting to be deleted, or requesting to spawn in another entity at a certain location.

Finally the `GameEntity` class therefore forms a base for all the entities:
- `Ship` --> the player's moveable ship that fires bullets.
- `Bullet` --> Spawned in by the ship, it has can collide and destroy other entities
- `CentipedeSegment` --> A single segment of the whole centipede. Many of them form the centipede.
- `Mushroom` --> the player can shoot these to prevent the centipede from bouncing off them and moving closer downward.
- `DDT` Bomb --> when shot will release an explosion cloud that obliterates all entities it touches.
- `Spider` --> An enemy that moves in a ziz-zag manner near the player area, an occasionally eats mushrooms.

