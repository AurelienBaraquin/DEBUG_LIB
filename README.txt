USAGE :

Dans un premier temps aller dans le fichier debug.h à la ligne L.93
ici vous pouvez mettre en commentaire l'une des 2 partie du code mis en évidence, pour choisir
entre une sortie constante et une sortie modifiable pendant l'exécution du programme.

Je conseil de laisser d'origine , soit la sortie modifiable pendant l'exécution du programme.


Maintenant il vous faudra définir les sortie d'erreur et de debug, lorsqu'il y a une erreur elle sera affiché
dans la sortie d'erreur et lorsqu'il y a un debug il sera affiché dans la sortie de debug.

Une erreur est toujours affiché en rouge et un debug en vert.

Pour définir ses sortie (ce qui est très important sinon le programme ne fonctionnera pas) il vous faudra
aller au début de votre programme et utiliser les MACRO suivante :

SET_DEBUG_OUTPUT(file);       -> je vous conseil de mettre stdout ou NULL_OUTPUT (NULL_OUTPUT est une sortie vide donc si il n'y a pas
                                d'erreur il n'y aura rien d'affiché, n'utilisez jamais NULL comme sortie !)

SET_ERROR_OUTPUT(file);       -> je vous conseil de mettre stderr

A noté que ce n'est pas nécéssaire si vous utiliser les sortie constantes (voir plus haut).



Maintenant vous pouvez utiliser les MACRO suivante pour afficher des debug et des erreurs :

DEBUG_VAR(type, var);        -> affiche la valeur d'une variable de type type (int, char, float, ...) et de nom var

DEBUG_INT(var);              -> affiche la valeur d'une variable de type int et de nom var
DEBUG_CHAR(var);             -> "" char
DEBUG_FLOAT(var);            -> "" float
DEBUG_DOUBLE(var);           -> "" double
DEBUG_STRING(var);           -> "" string
DEBUG_ARRAY(var);            -> "" array
DEBUG_2D_ARRAY(var);         -> "" 2d_array

DEBUG_LINE();                -> affiche une ligne de debug (utile pour séparer les debug et pour savoir où on est dans le programme)
                                la ligne affiche le nom du fichier, le numéro de la ligne où se trouve la macro

DEBUG_MSG(msg);              -> affiche un message de debug forcé de la couleur souhaité, voir debug.h L.22 pour les couleurs
                                (je vous ne vous conseil pas de l'utiliser car il n'y a pas de retour à la ligne)

PRINT_VAR(var);              -> affiche le nom de la variable brut en blue




Maintenant voici la fonction la plus importante :


void debug(char *type, int nb_arg, ...);


Cette fonction pest celle qui est appeller par les MACRO ci-dessus, mais elle peut être appeller directement.
Elle prend en paramètre un type de variable (int, char, float, ...) et un nombre d'argument variable.

Elle permet d'afficher autant de variable que vous le souhaité du type voulu, il faut juste mettre le nombre de variable mis en paramètre.

    ! Attention !
    La fonction marche grâce à un pointeur void, si vla variable que vous lui passé
    n'est pas déja un pointeur il faut lui passer l'adresse de la variable !

Exemple :

int a = 5;
debug("int", 1, &a);

----------------------------------------------

char *str = "Hello World !";
char *str2 = "Hello World 2 !";
debug("string", 2, str, str2);

----------------------------------------------

float f = 5.5;
float f2 = 6.6;
debug("float", 2, &f, &f2);

----------------------------------------------

char *array[] = {"Hello", "World", "!"};
char *array2[] = {"Hello", "World", "2", "!"};
debug("array", 2, array, array2);




Type de variable disponible :

int
char
float
double
string
array
2d_array
