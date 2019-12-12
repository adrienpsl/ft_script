#!/usr/bin/env bash

frame .haut -relief flat -borderwidth 2
label .libelle -text []index $argv 1]
entry .saisie -relief sunken -borderwidth 2
.saisie insert 0 []index $argv 2]
pack .libelle .saisie -in .haut -expand true -fill x

## Le bas contient deux boutons, Ok et Annuler, chacun avec
## sa procédure associée.
frame .bts -relief sunken -borderwidth 2
button .ok -text "0k" -command bouton_ok
button .annuler -text "Annuler" -command bouton_annuler
pack .ok .annuler -side left -expand true -pady 3 -in .bts
pack .haut .bts
update

proc bouton_ok {} {
## La procédure associée à 0K transmet la chaîne lue
## sur la sortie standard.
puts [.saisie get]
exit 0;
}
