# Un process

Un process: un programme en cours d'execution auquel 
est associe un environnement processeur / memoire

un programme: c'est une suite d'instruction static
ca ne change pas mec.

linux est un system preemtif : 
il se reserve le droit de kill les process.

la force de linux est de permettre de creer de mult
iple precussuss dans une image binaire et de pouvoir 
le faire avec 2 moyen : fork and exec

pour s'y retrouver les process on chacun un PID unique
quand on fork on creer deux processus : 
le current pere et le new fils. 
quand on est dans le fils, le pere est PPID, (Parent pid)

les Pid vont de 0 a 32728 de maniere lineaire,
si le kernel arrive a 32728, il recommence par le bas
avec le pid des dead process. On peu modifier cette valeur

Mais les systeme unix sont tres base sur le cote multiuser, 
Ce qui fait que chaque user a un UID (numerique)
nous pouvons aussi diff les process en regardant leurs uid
- les uid sont dans /etc/login.defs.
- plus l'uid est bas, plus l'user a de privilege (normalement)

il y a 3 uid par procesus: 
- reel : le mec qui a lancer le processus
- effectif : les privilege de reel
- saved : copy de l'ancien uid s'il a ete modifier

Dans le /etc/passwd il y a tous les users de ma machine au format : 
NON:MOTDEPASSSE:UID:GID:COMMENTAIRE:REP:COMMANDE


 





