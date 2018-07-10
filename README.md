# Space Invaders
## Introduction
### In the next work called "Space Invaders" we will present two versions, version one is a rustic or simple form of the game where no design pattern is applied and the second version is where the design patterns are already applied.
## Versions of the game
### * Version 1 UML
#### As you can see in the following UML we can see that the way in which the game is made, only uses functions and structures, its simplicity makes it easy to handle, but this does not ensure an optimal way to do it compared to the version with design patterns.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V1/Diagrama%20de%20Clases%20V1.png)
### * Version 2
#### In this version we will use the following design patterns:
#### - Singleton: this pattern will be used for the cover of the game since it will only be used once.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/singleton.png)
#### - Bridge: to store all functions that use "Allegro" functions.
#### - Facade: to not have all the functions inside the main main.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/facade.png)
#### - Flyweight: we will use it in the creation part of the ships, either enemies or the hero, this will save data from each one.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/Flyweight.png)
### Final Version
#### 
