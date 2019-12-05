# ft_script


[article de linux mag](http://rachid.koucha.free.fr/tech_corner/pty_pdip_fr.html)

Quand un process est charge en memoire pour etre executier,
il devient un procussus et est attache au terminal courant.
Il recoit et donne par les entre standard sans avoir besoin
de savoir ce qu'il y a derriere.

## Le premier progam, Mylogin
### je peux rediriger la stdout with
`
$ ./mylogin > output.txt
log
pas
$ cat output.txt
log
pass
$`
Avec cet redirection de la sortie, sans problem aucun, on
peut switch de std witout pb. Et ca c'est pas rien!

### rediriger l'entree
`$ ./mylogin < input.txt
login: Mot de passe : la saisie est:
log
pass`
l'ordinateur a remplacer l'humain qui tape les reponses.


https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus

### tout le temps
Mais on ne peux pas faire ca tout le temps:
- car certain programme interactif on des shema plus complex
Pour un programme de saisi de mot de passe classic :

- passe en raw mode et on clean le cash avec un fseek()
mais en faisant ca, je ne peux plus mettre mon fichier dedans.
En effets, ca bloque car : avec le fseek, le cash est clear
et le next fread, rencontre une EFO.
Ces modifications des inputs, ne marche plus si stdin n'est 
pas un terminal.
Pour repondre a ce probleme, on a creer des pseudos terminal

## les pseudos terminal
Ou pty, c'est une paire de peripherique virtuel en mode charactere
l'un est esclave, l'autre maitre. Un canal bidirectionel les reli
l'input de l'un est l'input de l'autre

la partie esclave se comporte exactement comme un terminal,
un proc peut l'ouvrir pour en faire son entree standart/sortie
je peux faire sur cet esclave des echo, carriage return et
des line feed.
Il y en a plusieur, mais nous on va juste prendre la sysV

la mise en oeuvre des terminaux se fait avec une simple api

### the function
- posix_openpt :
    it call /dev/ptmx to get the master fd of the pty, with open /dev/ptmx
    It seam on osx, this do not exist, and I need to loop on tty like in this post
    (https://stackoverflow.com/questions/43956208/does-mac-os-x-have-the-dev-ptmx-file/43956337)
    in the man of that func, there is a version with only syscall :
    (http://man7.org/linux/man-pages/man3/posix_openpt.3.html)
- grantpt
    apres l'open, on utilise pour changer les droits d'acces
    sur la partie esclave du pt.
    userid = userid parent, group = random
    right = crw--w----
- unlockpt 
    on lui pas le descripteur pour unlock le p esclave
- ftsname
    me donne le nom de mon esclave
    je peux l'ouvrir avec open
    




# I'm fucked, I didn't understand all that shit, so I restart by the start
## what is tty 
(first link)[https://www.howtoforge.com/linux-tty-command/]
In linux everything is a file, even the hardware device, that are special file
`tty [option]` print the current tty of the current terminal



what is pty
















objectif : les convaincre
pas de risques comment faire pour les convaincres
qu'est ce qui fait que on dej ensemble 
alexs minchella.com
adreou sole hec prof : experienc suivre, shodowing.


pourquoi en dej ensemble? 

souplesse + flexible 
reactiviter, source.
temps pour leurs activeter qui sont visible.
dev, mettre a jour.

qu'est ce que t'en dis.




