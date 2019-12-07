# Prelude
- is that a Posix book ? 
    no, because sometime, nonstandard extension are essential, either for 
    performance reason or to access functionality that is unavailable in the 
    standart UNIX interface.

- is linux a UNIX
    not at a official definition.
    
# It's very tough in english, so I will read an other book before came back to this one
Programation systeme en C sous linux.

## intro
Au debut du livre il parle des flagues de compilation, et des types de files 
new useful flag: 
    - pedantic : plus d'avertisselment qu'avec -Wall, oriente sur la portabilite
    - o / de 0 a 3: optimisation
    - DNDEBUG : kill all debug optimisation
classic dev process : gcc -Wall -pedancic -g fichier.c -o binary_name
classic distrib : gcc -Wall -DNDEBUG -O2 file.c -o binary_name

# le Debugger
si l'app est compiler avec le flag -g, il est possible de l'executer sous le
controle d'un debugger.
Sur linux on utilise gdb (gnu debuger). Ce debuger marche en line de commande est dur.
donc, DDD (data display debugger) a ete creer.
- debug dev :
    quand mon binaire fait des betises (memoire, op interdite), le noyau le kill,
    sous certain condition, l'arret produit un fichier core1 qui represente 
    une image de la memoire a ce moment precis.
- en prod : 
    je peux annalyser des programme en foncionnement avec gbd sur des 
    machine en ssh. Et la pas le temps ou le pouvoir de mettre une interface graphique
    il faut que ca debug et vite mon colonel.

# le profiler
le profiler enregistre les temps de connection et de presence de chacunne 
des routines du programme, et note toutes ses datas dans un file,
ce qui permettra de comprendre comment rendre l'app plus reactive.
le profiler gnu s'appelle gprof, il faut compiler avec le flag -pg pour que ca marche.

Il y a aussi trace, qui permet qui detecque tout les appels systeme d'un programme
il observe l'interface entre le noyau et le processus et memorise tout les syscall

nm, lire la doc, ca semble plus complique que prevu

dump.

# linter
il y a un linter : lclint qui linte, mais il est tres peut permissif
et il est mieux de l'utiliser a la fin, comme un relecture du programme.

# je passe ce chapitre car je connais globalement ce qui va se passer.

# Les processus:

# la notion
-   Sous Unix, toute tache qui est en cours d'execution est un procesuss.
    une entite elemetaire contenant a la fois du code et des donnees.
-   A un instant donee, un processus peut se trouver dans plusieur etat, 
    et pour que le multitache fonctionne correctement, le noyau schedule
    l'axe au microprocesseur.

# Le PID
Le premier process sera init.
ensuite, la seul maniere de faire un new process sera fork() qui va dup le 
process existant en deux nouveau dont la seule difference sera le PID (Process IDentifier).
l'original sera le pere, et le nouveau, la copie le fils. 
Mais le fils peut ensuite se remplacer par un autre programme comme le fait un shell.
pid_t fork() est dans <unistd.h>

pid_t getpid() permet de connaitre le PID c'est un des seul syscall qui n'echout jamais.

Mais le fork return deja cette valeur :
- 0 si nous somme dans le fils
- neg si error
- pid du fils si dans le pere.

Le principale atout de ceci est de pouvoir faire dialoger ces deux processus etre eux
par le biais de signaux, de tube, de shared memory.

le fils accede aux PPid (parent pid) avec:
pid_t getppid()

!! le pere ne peut avoir le numero de fils que lors du fork! 

si je tape la commande `ps xsj` j'ai le ppid de tous les process.

quand un prosses est cree par fork(), il herite: 
    - les donnees de son pere
    - l'enviroment de celui ci
    - sa table de discripteur etc....
fork est econome car il utiles une methode de copy sur ecriture, tant que 
ni le pere, ni le fils n'ont modifier les data, il n'y en a qu'un seul exemplaire
sur le system.

!! en cas d'error, return -1, et errno is set.
si errno == EAGAIN, le programme est inviter a recommencer.

regarder exo 01,
le wait() qui est un nouveau syscall, permet d'attendre que le 
fils est terminer avant de finir le pere.
le pere attend avec wait que le fils termine.

## UID
Unix == multi user controle.
Tout process launch par user est soumis a strict control,
son process aussi, il a un User IDentifier.
UID peut changer
3 types :
    - UID reel      : celui de l'user launch programme, == privilege 
                      user launch programme
    - UID effectif  : current right 
    - UID sauve     : last effectif if changement 

Sous unix presque tout est noeud du file system, 
if try access file, kernel check if UID proccess >= file_right

Certain app, pontuellement need un privilege 
    - su
    - mount => allow to mount disk any user
    - ping => ask reseau basse couche.
to perform this specifique operation, P gets new grants
but keep in sauve the real right for kernel check

getuid() : reel
geteuid() : effectif
* voir cs 02

je peux faire avec chmod une chose similaire pour un file,
le program est le  ex_02_getuid.c, print getuid / geteuid
```bash
su
# pass ....
chmod root.root prog
chmod +s prog # ici set le uid a celui de root, le pr sera root tout le temps
ls -ln *
    # -rwsrwsr-x 1    0    0 8440 Dec  6 21:59 prg 
    # -rw-rw-r-- 1 1000 1000 1045 Dec  6 21:59 ex_02_getuid.c
./prg
# UID reel = 0, UID effectif = 0
 exit # the root mode
./prg
# UID reel = 1000, UID effectif = 0
```
l'attribut Set-UID indique par la lettre s dans les right.
quand je relance sans etre root, on voit que l'UID reel, le mien
a ete conserver.

il existe des syscall permetant a un process de changer son UID,
pour en perdre ou retrouver des anciens, mais jamais pour en gagner.
Comme avec mount, qui prend les droits root pour access au materiel
et peu etre use by all the users.

Pour sauver des configs user (alors que mode root), et permettre 
ensuit a use d'y avoir access on reduit ls droits le temps de la creation.

a tout moment un process peut demander au kernel de switch entre ses 3 UID


Donc un prossess avec Set-UID positionner start avec un uid effectif
different de l'user qui l'a start. et il peut switch entre les deux.

voici les api
`int setuid(uid_t uid_effectifs);
int seteuid(uid_t uid_effectifs);
int setreuid(uid_t uid_reel, uid_uid_effectifs);`
return -1 fail, 0 good

avec le function si dessus, je peux baisser en privilege, mais une fois
la modification effecture, je ne pourrai pas revenir en arriere
si je suis root, ca marche pour le reste des cas. 


## les GID
Group IDentifier, comme UID reel, effectif, saved.
Mais les GID ne dependent pas de la personne qui lance // set-UID
il correspond au group principal de l'user qui a lance le programme
un process peut appartenir a deux group qui n'ont rien en commun.

pour get les groups, il faut loop sur un file,
regarder dans le livre, page 35.

Modifier les groupes permet par exemple 
    - passer en root
    - ajouter un group pour access un peripherique
    - retourner en user

## les id de group de process
Ce ne sont pas des users group, c'est des group de process,
ils permettent l'envoie global a un groupe de process, 
c'est bien pour les shell et le job controle.

`pid_t getpgid()` 

page 39 il y un pg pour regarder comment get le group d'un process

a la creation d'un process, un id de group est creer, et tout ses 
descendant le partageront. Le process dont le pid est le meme que 
le gid est le leader du group (mais le fermer ne close pas les autres)

les group ne sont utils si je veux fermer tout ls process d'un program
d'un coup par exemple. comme avec un gestionnaire de fenetre.

!! si un fils lance une command exec, un process ne pourra plus 
changer le groupe de ses descendant.

classic ex : 
    - on fait un fork et on garde l'id du fils dans le parent.
    - le fils demande a devenir leader de son group avec setpgid(0,0);
    - le pere reclame aussi que le fils deviennent leader de son group
      pour eviter tout probleme concurentiel d'execution : setpgid(pid_fils, pid_fils);
    - le pere attend maintenant la fin de l'execution avec waitpid()
    - le fils appelle une fonction de la famille exec()
le Shell peux maintenant envoyer des signs a tout les process du fils,
STOP, CONT ...)

## Session ID
Le dernier regroupement de process, reuni divers group de process.
les sessions sont liees aux terminal de control : shell et window manager
ou les demon.
Generalement une session est attacher a un terminal de control 
auquel l'user se connect. la session est composer par 2 sous groups,
ce qui recoive directement les user inputs, et the remaining.

voir page 40 pour plus de detail.

- un process appartient toujours a un group
- un group appartient a une session
- la session peut avoir un terminal de control
- le terminal connait le numero des groupe en avant-plan.
c'est en general, le leader de la session (le shell) qui bascule
les group en avant ou arriere plan.

### les capaciter d'un process
Depuis linux 2.2, il est possible de limiter les droits d'une app
executer sous l'uid root. Ces capatiter correspondent a des privilege 
plus fin. On peut laisser un programme modifier son jeu d'ordonancement
et rien d'autre. Ca protege au cas ou l'app est corromput, de ne rien
risque de plus que les autorisations de l'app.

un process a three ensemble de capacite:
    - effecives: celui qui est utiliser a un instant T, comme UID effective
    - transmissible: c'est ce qui sera transmit lors d'un exec, fork() ne 
        change rien.
    - possible: sa reserve de privilege, un process peut transfere de cette
        reserve au deux precedent. C'est la veritable capaciter du process

pour le moment, ceci n'est pas encore applicable au file system

segmentation root est tres importante pour l'avenir de linux,
elle permet a un admin de deleger certain tache a un user de confiance
mais protege aussi contre les fails exploitables dans des app. 
Si l'app est corumpu, le pirate ne peut pas casser plus que les 
capaciter de l'app.

### Conclusion
Dans ce chapitre, nous avons vu les deffernt id qui peuvent etre 
attacher a un processus.
UID GID SID CID.
UID les autorisation pour le processus (set-id, effectifs...)
GID (set gid) acces a du materiel
SID graphic et shell, jobcontrole
CID tres cool, en implantation

## Access a l'env
une app peut s'executer dans une multitude de contex.
il faut donc annalyse l'env pour pour savoir ou elle start.

### Variable d'envieronement
un process peut agir sur ces variable d'env (et donc de ses fils)
mais pas sur le remaining. Lors du fork, l'env du pere est copied 
pour le fils.
quand un program C start, son env est automatiquement copier dans un 
char** accessible par `extern char ** environ`
on peut aussi y acceder comme 3eme element du main, mais, la norme
posix recommande de ne pas le faire.

apres il y a setenv, unsetenv ... je connais tout ca.

### Variable d'env courament used
Pour comprendre quoi sert a quoi, nous allons regarder comment sont 
set ces variables, depuit le demarage du system.

#### init
A tout seigneur, tout honneur: le kernel commence par fill env pour 
le process initial : init (/usr/init | /etc/init | ...)
(usr/src/linux/init/main.c)
HOME=/
TERM=linux

il configure ensuite:
- PATH= ...
- RUNLEVEL=niveau d'execution
- PREVLEVEL=niveau precedent (en cas de redemarage a chaud)
- CONSOLE=perepherique console 

after, il analyse le fichier /etc/inittab pour connecter a un terminal
1:13241:respaown:/sbin/mingetty tty1
ici, mingtty est use pour surveiller la connection tty1 et et declancher la /bin/login

#### /bin/login (util-linux)
- check the user id, (avec etc/passwd). Et en deduit le shell de connection
- detruit le current env, et met celui de l'user a la place.
- lance le shell desire par l'user.

les vars les plus courrante:
    - HOME, PATH, PWD
    - LANG: qui est la localisation choisi par l'user
    - LOGNAME / USER : contiennent le nom de l'user
    - TERM: contient le type de term utiliser
    - SHELL: le shell de connection user
Ces routines influent sur d'autre routines
    - POSIXLY_CORRECT : modifie le comportement de certain routine
                        pour qu'elle colle a la norme posix
    - MALLOC_XXX les fonctions de malloc

### les arguments en line de command
ils sont separer par IFS en bash

#### les options simples
- si une option necessite un argument, elle peut etre ou non seporer
  -a file
  -afile
-- indique la fin des options, tout le reste apres sera pas une option
'-' est transmit comme un argument, et stop la prise d'option





















