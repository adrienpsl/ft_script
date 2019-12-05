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




