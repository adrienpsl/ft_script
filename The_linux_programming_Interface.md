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

## Execution des programme
how que c'est comment que on lance un process mec ?

### Lancer un nouveau programme

#### exec
if exec reussit, il ne revient pas, sinon, il retourn -1 et errno 
log l'error. 

Il n'existe qu'un seul execve() est le seul syscall, les autres
sont des variation de celui ci, sur comment on passe les datas.

!! pour le path il est smart de mettre en premier les 
directory les plus utiliser.

!! $SHLVL contient le nombre de shell imbriquer.
a chaque execve il y en a un nouveau.

nous allons reproduire ca :
```bash
sh -c "echo $SHLVL"
```
l'option -c ask shell, do that and quit.
**ex_04**

les autres fonctions fonctionne de la meme maniere,
avec des differences d'argument.

#### la copie.
Quand un call a execve est fait, et qu'il reussi: 
le nouveau programme replace totalement l'ancien: 
    - les segments, les variables, le pile, tout est liberer
    - les chaines d'environemnet et d'argument sont copier,
        on peut utiliser n'importe quel genre de variable 
        pour transmettre les arguments de exec().
l'ancien programme transmet au new :
- les PID, PPID, PGID, SID, **il n'y a pas de new process**
- les UID et GID, sauf si set-UID/GID est active,
    dans ce cas la, seuls les reel sont conserver, les effectifs
    sont mis a jour.
- le masque des signaux est bloque, et les signaux en attente
- autre chose avec les signaux, chapitre 7.
- les discripteurs de fichiers ouverts ainsi que leurs 
    eventuel verrous. sauf si le file a l'attribut: close-on-exec.
**par contre :**
- les temps d'execution associer au process continue
- les privileges restent les memes.

#### les erreurs
l'appel de exve ne reviens pas, donc s'il revient, il y a une erreur:
- le fichier n'existe pas, n'est pas executable,
   le process appelant n'as pas le bon right. 
- le fichier est trop gros, plus de memoir, pb d'ouverture fichier
    c'est des err critic, on quit program
- ptr in valide
- fichier deja ouvert
- l'error : ETXTBSY, voir la suite, le fichier est deja ouvert en ecriture.

##### petite formation sur les pages
linux donne des pages (hehe malloc mon gars)
en realiter, il y un mappage fait par le processeur entre la memoire physique
et les pages donne. elle peuvent bouger de place, etre mis sur le disque dur
si plus de place...Mais la page peut deja etre sur le disque.
auquel cas, il y a une faute de page, et le kernel la reload.
le noyau garde trace de toute les pages modifier, car si elle sont sur le disque
et la ram, et plus de place, il delete les pages sur les deux. 
c'est malin ce truc !
La force de ce prosses c'est que tout n'a pas besoin d'etre en memoire, le noyau
charge et decharge au fur et a mesure.
Mais, il faut securiser les fichiers ou sont les data, ceux du disque, 
car s'il change et que les data ne sont plus en memoire bha ca ne marche plus.
c'est pour ca que on ne peux pas modifier un fichier en cours d'execution.
le kernel l'a lock.

c'est pour ca que je ne peux pas recomplier un programme ouvert. c'est bloquer bitch

#### fonction simplifier pour executer un sous-programme
on veut parfois lancer une commande extren sans remplacer le process en cours.
on utilse la command system() pour faire ca. Cette fonction invoque le shell
et lui transmet la command fourni, et reviens a la fin de l'execution.
voir ex_06_system, pour avoir une interpretation simplifier

! la command system represente une tres grosse fail de securite, 
si le program qui la lance est en set-UID root, il poura faire ce qu'il veut:
la command search dans PATH les binaire, si je cherche ls et que le pirate 
a remplacer ls, il lancera sont programme en root, et c'est la merde.
le danger avec system, c'est qu'il appelle un shell au lieu de lancer la command.
system est une commande super, mais il ne faut pas l'utiliser avec tout !

ouvrir un nouveau process en lui donnant des inputs:
- popen (const char *command, const char *mode);
    - elle ouvrira un fork ou un excev
    - en fonction du mode, le flux d'entree ou de sortie du programme est utilise
    - il faut toujours la refermer avec pclose(), qui attend la fin du process
        et retour son retour. 
    - voir ex_06
    - cette routine, fait comme system, un execl, elle cherche dans PATH
- la second utilite de popen est recuper des donne difficile a optenir 
    et de les parcer (who, ps, netstat...)
    - voir ex_08

## Fin du program

### assert
Pour check en direct ce que fais un processus, on utilise le define assert
qui va si l'assertion est fausse quitter le program et ecrire des data de 
debug.

assert permet de documente les element d'une routine qui ne doivent pas etre 
d'une certaine valeur, il faut le voir comme un super commentaire.

assert(ptr != NULL)
c'est comme // ptr nedd != NULL

ces commentaire ne seront surment pas vu en cas de changement du code,
alors que le assert etant compiler, le sera et raisera une error

il est possible d'activer NDEBUG avec define et de le desactiver avec #undef
pour activer ou desactiver le debug dans certain portion.

il faut ensuite inclure un flag -DNDEBUG  ou define #NDEBUG pour basculer 
entre dev et production.

notons que assert utilise la routine abort()


### Routine de terminaison
Il est possbible avec les fonction atexit() et on_exit(), 
de faire enregistrer des fonctions qui seront ex quand le P terminera normalement

elles peuvents servire a:
- effacer des fichiers temporaire / save le setup de l'user
- save sur disque un sturct du programme
- libere des verro sur les fichiers ou hoses de donnees
- restauren l'etat initial du terminal
- terminer un dialog resaut proprement en suivant un protocol complets

On peut le faire dans P mais:
- on peut quitter de ou on veut
- c'est sur qu'il n'y aurra pas d'oublie

int atexit (void *routine(void));
- elle recoit un ptr sur une void *routine(void) et le save, pour le call plus tard
- les fonctions sont pop comme un array, un f mise *2 le sera 2
- il n'y a pas de facon de deprogrammer un f add, add global inside to control
- exit() ne fais rien dedans
- _exit() exit without call other function 

### attendre la fin d'un processus fils
linux est base sur un grand nombre de function mise ensemble, 
il est donc primordial, de pouvoir get leur retour pour pouvoir les 
get les erreur. a tel point, que tant que le retour d'un process 
n'est pas fait, il passe en mode zombie et attend indefiniment d'etre lu

il est tres important de mettre un wait dans le code du pere, ou de 
handle correctement les signaux, sinon le fils a la fin devient un zombie.
car quand un programme termine, son return est stocker dans le registre des programme
et ca prend une place ! Et c'est pas bien du tout !

si le pere termine avant le fils, init: le process 1, devient le pere du fils

### lire le retour d'un process:
Il existe 4 function pour avoir le retour d'un process: wait, waitpid, wait3, wait4
seul wait4 est un syscall.

#### wait
pid_t wait(int *status);
elle bloque le process appelant jusqu'a ce que l'un de ses fils se termine.
Elle return ensuite l'id du fils terminer. si le satus est non null, 
il contiendra le return du fils.
Le retour est opaque et il faut utiliser des masques pour connaitre les valeurs
de retour.
WFEXITED(status): le process s'est terminer avec exit() ou main, 
WEXITSTATUS(status): le return du program

WFSIGNALED(status): terminer a cause d'un signal (y compris le GABRT de abort())
WTERMSI(s): le signal qui a tuer le process
WCOREDUMP(s): signal si un core dump a ete creer  

WFSTOPPED(S): indique que le fils est stope
WSTOPSIG(S): le sig qui a stop le fils

la F wait() peut echouer si pas de fils, et return -1 en placant l'err ECHILD
dans errno.

Mais il y a deux pb: 
    - l'appel et bloquant, je ne peux rien faire dans le pere tant que l'un des fils
        n'a pas fini (une loop qui lance des routines tant que wait n'est pas fini)
    - je ne peux pas choisir quel fils j'attend avec wait, je peux faire des trics
        avec SIGCHLD mais ce n'est pas optimun

pour pallier a ces deux pb 
#### waitpid
pid_t waitpid(pid_t pid, int *status, int options);
Le premier argument permet de determiner le fils que l'on attend:
    - si strictement positif -> attendre la fin du process == a ce pid
    - 0 : attendre le premier fils appartenant au meme group qui fini // WAIT_MYPGRG
    - -1:  atterdre la fin de n'importequel processus
    - < -1: attendre la fin de n'importequel processus qui appartient au grop du process 
        dont le num est -pid
status == wait(status)
options : binary, | 
    - WNOHANG : ne pas rester bloquer aucun process == pid n'est terminer, return 0
    - WENTRACED: acceder au informations concernant les processus fils stop 

#### wait3
Permet d'obtenir des informations suplementaire sur le process qui s'est terminer.
ces informations sont transisent par une struct : rusage (page 106, tout est detaille)
linux ne remplie pas tout, c'est plus utiliser pour dev des truc de ouf : 
    - time
    - faute de pages
    - les swaps
 















































