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
#### In this Final Version we use diferent kinds of design patterns: Creational design patterns and Structural design patterns.
#### - Creational design patterns:
These design patterns are all about class instantiation. This pattern can be further divided into class-creation patterns and object-creational patterns. While class-creation patterns use inheritance effectively in the instantiation process, object-creation patterns use delegation effectively to get the job done.

Singleton
A class of which only a single instance can exist, this pattern will be used for the cover of the game since it will only be used once.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/singleton.png)
#### - Structural design patterns:  
These design patterns are all about Class and Object composition. Structural class-creation patterns use inheritance to compose interfaces. Structural object-patterns define ways to compose objects to obtain new functionality.

Bridge:
Separates an object’s interface from its implementation,  to store all functions that use "Allegro" functions.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/Blank%20Diagram%20(1).jpeg)
or 
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/Blank%20Diagram.jpeg)
Facade:
A single class that represents an entire subsystem,to not have all the functions inside the main main.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/facade.png)
Flyweight:
A fine-grained instance used for efficient sharing,  we will use it in the creation part of the ships, either enemies or the hero, this will save data from each one.
![Version 1 UML](https://github.com/kenny181920/space_invaders/blob/master/Space_Invaders_V2/UML/Flyweight.png)
