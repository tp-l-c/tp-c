#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct liste {
    char *s;
    struct liste *next;
};
typedef struct liste LISTE;

// fonction affiche toute la liste
void affiche_tliste(LISTE *first)
{

   if (first)
   {

   affiche_tliste(first->next) ;
        printf("%s",first->s);
   }
}

//fonction insertion
void insert_tliste(LISTE **first, char *ligne) {
    LISTE *p;
    p = (LISTE *) malloc(sizeof(LISTE));
    p->s = (char *) malloc(sizeof(char) * (strlen(ligne)+1));
    strcpy(p->s,ligne);
    p->next = *first;
    *first = p;
}

//fonction recherche qui recherche ou se trouve une chaine

void recherche_chaine( LISTE * first, char* s_chaine)
{
    LISTE * current;
    current =  first;
    while (current != NULL)
    {
        if ( strstr ((current->s), s_chaine) == NULL)
        current = current ->next;
        else
        {
             printf("%s",current->s);
            current = current->next;
        }
    }
}


//fonction supprimer

void supprimer_ligne(LISTE ** first , char* s_chaine)
{
    LISTE * current;

if (*first)

    {
        if ( strstr (((*first)->s), s_chaine) == NULL)

        supprimer_ligne(&((*first)->next), s_chaine) ;

        else
        {
            current = *first ;
            *first = (*first)->next ;
           free(current) ;
 supprimer_ligne(&((*first)), s_chaine) ;
        }
    }

}
int get_option()
{
  int option = 0;
  printf("\n**********************************************************\n");
  printf("********************* Liste des Choix **********************\n");
  printf("************************************************************\n");
  printf("\n1: visualiser le contenu de la liste");
  printf("\n2: afficher les lignes qui contiennent le mot a saisir");
  printf("\n3: supprimer les lignes qui contiennent le mot a saisir");
  printf("\n4: affichage de la liste avec justification avec un numero max des chaines");
  printf("\n5: trier la liste");
  printf("\n6: sauvegarder le fichier modifie");
  printf("\n0: Quitter l'application");
  printf("\n\nChoix:");
  scanf("%d",&option);

  while ((option < 0) || (option>6))
  {
      printf ("erreur de saisie\nChoix :");
      scanf("%d",&option);
  }

  return(option);
}

void affiche_option (LISTE *first)
{
    char sous_chaine1 [20], sous_chaine2 [20] ;
    int  option;
     while( (option=get_option()) != 0)
  {
    switch(option)
    {
      case 1:
    affiche_tliste(first);
    break;
      case 2:
    printf ("\n>>>>>>>>>>> donner la chaine a chercher :");
    scanf ("%s", &sous_chaine1);
    recherche_chaine(first, sous_chaine1);
	break;
      case 3:
    printf("\ndonner la chaine pour effacer les elements qui la contiennet:");
    scanf("%s",&sous_chaine2) ;
    supprimer_ligne(&first,sous_chaine2) ;
    affiche_tliste(first);
	break;
      case 4:



	break;
      case 5:




    break;
      case 6:
//    save ();
    break;
	  case 0 :
		  printf (" >>>>>>>>>>> Fin de l'application \n");
		  break;
      default:
    break;
    }
  }
  exit(0);
}




int main(int argc, char *argv[]) {
    FILE *fp;

    LISTE *first;
    char ligne[256];
    if (!(fp = fopen("ahmed.txt", "r+")))
    {


        exit(0);
    }
    first = NULL;


    while (fgets(ligne, 200, fp)) {
      //  ligne[strlen(ligne)-1]='\0';
        insert_tliste(&first, ligne);

    }
affiche_option (first);

}
