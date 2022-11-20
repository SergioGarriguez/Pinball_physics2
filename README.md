# Pinball_physics2

## Controls:

 - left and right arrows to control the flipers
 - hold the down arrow to control the kicker
 - 1 to create or reset the ball
 - 2 to reduce the gravity
 - 3 to augment the gravity
 - 4 to reduce the restitution and reset the ball
 - 5 to augment the restitution and reset the ball
 - f1 to activate/deactivate debug

## Combos and mechanics:

 - When you hit a heart it starts to beat faster, this means that if you hit the other without using the flippers you will recieve a bonus of 200 points
 - When you go over 1000 points in that round a saucer spawns. It has different behaviours (it gets applied a force with random direction, it moves in different directions acording
to the position of the ball, and it moves randomly).
 - When you kill the saucer, you get a bonus of 3000 points one extra life. But beware of the explosion. This also makes you win the game although it does not stop you from continuing.
 - I also tried to make a one way wall, but it doesn't work well, it only works when the ball is going fast, otherwise, all it does is go halfway through and then back.
The commented code in ModuleMouth.cpp is what has to be uncomented to spawn the wall, just in case you are interested.

## Development process:

I first made a sketch of the map on paint and then using that as a reference I created a chain body and then the ball with restitution. After that, I started to make the flippers (modulePlayer using revolute 
joints with a motor enabled in order to make them go back to their place once the key is released but this caused the issue of them not going back to the initial position, which I later solved by 
setting the rotational speed to a fixed value while the key is held and the flippers have certain angle. Then I made the kicker (ModulePiston) with a prismatic joint, the physics didn't give me
much trouble, but creating the animations did, when I tried to make the animation reset when pressing down it instantly changed to the 3rd animation, I solved this by changing
a few functions of Animations.h. Then I added the bumpers which are basically balls with 1.2 of restitution, for this I had to change the function to create balls in physics.cpp to let me input restitution
values and I made them add score when they collide with the ball, to make sure that it is the ball I used an atributte which only the ball has set to true (isbullet, which also helps to avoid tunneling).
The next thing I made was to add the score system and the round system although not yet the graphical representation. Then I started to make the graphics of the game and started the animations.
After that, I made the saucer (ModuleBoss) which gave me 2 main problems, one was the same as the animation of the kicker and the other was that when trying to reset it the ball that represents the boss
would stay there even after destroing the boss, so I had to make it destroy itself in the update function while being careful not to make anything crash. Finally I added the last touches like making some
extra animations, displaying the score and adding sounds. I also tried to make the one way wall and the only thing left is the animation activated with sensors.

## Miscelania:

 - The game had no particular references other than pinball in general.
 - Assets and animations by Sergio Garriguez Redondo.

## Created by:

 - Sergio Garriguez Redondo https://github.com/SergioGarriguez

## Repository of the game:

https://github.com/SergioGarriguez/Pinball_physics2