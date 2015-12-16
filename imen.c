#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILE_LINE_DEFAULT_SIZE  100
#define ERROR        -1
#define NO_ERROR      0


/**************************************************/
/*                  Type Declaration              */
/**************************************************/



struct data
{
    char *s;
    int ligne;
};
typedef struct data DATA;



struct liste
{
    DATA d;
    struct liste *next;
    struct liste *prev;
};
typedef struct liste LISTE;


/**************************************************/
/*                 Function Prototype             */
/**************************************************/

int  get_option(void);
int  open_files(FILE **);
void charger_liste (FILE *,LISTE **);
void contenu_liste (LISTE *);
void contenu_lignes (LISTE * ,int, int);
void supprime_ligne (LISTE** ,int);
void supprime_lignes_vides (LISTE ** );
void supprime_bloc (LISTE **, int, int);
void affiche_lignes (LISTE *,char *);
void insere_ligne (LISTE **,int, char *);
void remplacer ( char *);
void save ();
void print_data(LISTE *);
void update_num_ligne(LISTE **, int);
void freee ( LISTE **);

int main()
{
      FILE * fichier;
      LISTE * debut_liste;
      int  option, num_ligne, num_ligne_sup,num_ligne_deb,num_ligne_fin;
      int  ligne_debut;// nbre_ligne;
      char sous_chaine [20], s_chaine [20] , chaine [FILE_LINE_DEFAULT_SIZE];


      debut_liste = NULL;
  if(open_files(&fichier) == ERROR)
  {
	  printf("\n Fichier Introvable, Merci d'ajouter les fichiers d'entre pour notre programme \n");
      system("PAUSE");
	  exit(0);
  }

  charger_liste(fichier,&debut_liste);

  while( (option=get_option()) != 0)
  {
    switch(option)
    {
      case 1:
    contenu_liste ( debut_liste);
	  break;
      case 2:
    printf (" >>>>>>>>>>> donner le numero de la ligne du debut :");
    scanf ("%d", &num_ligne_deb);
    printf (" >>>>>>>>>>> donner le numero de la ligne de fin :");
    scanf ("%d", &num_ligne_fin);
    contenu_lignes ( debut_liste,num_ligne_deb, num_ligne_fin);
	break;
      case 3:
    printf (" >>>>>>>>>>> donner le numero de la ligne a supprimer :");
    scanf ("%d", &num_ligne);
	supprime_ligne ( &debut_liste,num_ligne);
	update_num_ligne(&debut_liste,1);
	break;
      case 4:
	supprime_lignes_vides (&debut_liste);
	break;
      case 5:
    printf ("donner le numero de la ligne du debut :");
    scanf ("%d", &ligne_debut);
    printf ("donner le nombre de lignes a effacer :");
    scanf ("%d", &num_ligne_fin);
    supprime_bloc ( &debut_liste, ligne_debut, num_ligne_fin);

    break;
      case 6:
    printf (" >>>>>>>>>>> donner la chaine a chercher :");
    scanf ("%s", &sous_chaine[0]);
    affiche_lignes (debut_liste, sous_chaine);
    break;
      case 7:
    printf (" >>>>>>>>>>> donner le numero de la ligne avant :");
    scanf ("%d", &num_ligne_sup);
    printf (" >>>>>>>>>>> donner la chaine a inserer :");
    scanf ("%s", &chaine[0]);
    insere_ligne (&debut_liste, num_ligne_sup, chaine);
    break;
      case 8:
    printf (" >>>>>>>>>>> donner la chaine a remplacer :");
    scanf ("%s", &s_chaine[0]);
//    replace ( * chaine);
    break;
      case 9:
//    save ();
    break;
	  case 0 :
		  printf (" >>>>>>>>>>> Fin de l'application \n");
		  break;
      default:
    break;
    }
  }
  fclose(fichier);
  freee (&debut_liste);
}

int open_files(FILE **fp_fichier)
{
  *fp_fichier=fopen("fichier_projet3.txt","r+");



  if(*fp_fichier == NULL)
  {
    printf("Erreur D'ouverture du fichier\n");
    return(ERROR);

  }
  return NO_ERROR;
}


int get_option()
{
  int option = 0;
  printf("\n**********************************************************\n");
  printf("********************* Liste des Choix **********************\n");
  printf("************************************************************\n");
  printf("\n1: visualiser le contenu du fichier");
  printf("\n2: visualiser le contenu d'un bloc");
  printf("\n3: supprimer une ligne");
  printf("\n4: supprimer les lignes vides");
  printf("\n5: supprimer un bloc");
  printf("\n6: rechercher une ligne contenant une chaine");
  printf("\n7: inserer une ligne");
  printf("\n8: remplacer toutes les apparitions d'une chaine ");
  printf("\n9: sauvegarder le fichier modifie");
  printf("\n0: Quitter l'application");
  printf("\n\n Choix:");
  scanf("%d",&option);

  while ((option < 0) || (option>9))
  {
      printf ("erreur de saisie , Choix :");
      scanf("%d",&option);
  }

  return(option);
}

void insert_at_last (LISTE ** Current_List, LISTE ** last_created,int i, char* l)
{
    LISTE * Current;
    if (*Current_List != NULL)
    {
        Current = *Current_List;
        (Current)->prev = (LISTE *)NULL;
        Current = (Current)->next;
        insert_at_last (&Current, Current_List,i,l);
    }
    else
    {
        Current= (LISTE *) malloc (sizeof (LISTE));
        (Current)->d.s = (char*) malloc(FILE_LINE_DEFAULT_SIZE * sizeof(char));
		memset((Current)->d.s,0x00,FILE_LINE_DEFAULT_SIZE);
        memcpy((Current)->d.s,l, strlen(l));
        (Current)->d.ligne=i;
        (Current)->next = NULL ;
        if (last_created != NULL)
		{
			(Current)->prev = *last_created;
            (*last_created)->next = Current;
		}
		else
		{
			(Current)->prev = NULL;
			*Current_List = Current;
		}
        last_created = &Current;
    }

}

void charger_liste (FILE * fichier,LISTE ** first)
{
    FILE* fp;
    char l[FILE_LINE_DEFAULT_SIZE];

    int i;
    void* ret ;
    fp = fichier;
    i=1;
    memset(l,'\0',FILE_LINE_DEFAULT_SIZE);
    while ( !feof(fp))
    {
        ret = fgets (l, FILE_LINE_DEFAULT_SIZE, fp);
        if (ret != NULL)
        {
            insert_at_last (first,NULL,i,l);
            i++;
        }

    }
    printf(" >>>>>>>>>>> fin chargement fichier \n");
	fclose(fp);
}



void contenu_liste (LISTE *first)
{
    if (first)
    {
        print_data (first);
        contenu_liste (first->next);
    }
}

void contenu_lignes( LISTE * first,int n1, int n2)
{
    LISTE *current;
    current = first ;
    if ((n1>n2)||(n1<=0)||(n2<=0))
    {
        printf (" >>>>>>>>>>> erreur de saisie \n");
        return;
    }
    else
    {
        while ( current != NULL)
        {
            if (current->d.ligne < n1)
                current=current->next;
            else if (current->d.ligne<=n2)
            {
                print_data (current);
                current=current->next;
            }
            else
            return ;


        }
    }
}

void update_num_ligne(LISTE **first,int nombre_ligne)
{
    int i = nombre_ligne;
    LISTE* current= *first;

    if(current != NULL)
    {
        current->d.ligne = i;
        i++;
        current = current->next;
        update_num_ligne(&current,i);

    }
}


void supprime_ligne( LISTE ** first, int n)
{
    LISTE *current;
    current = *first;
    LISTE *previous = NULL;
    LISTE *nextb = NULL;
    if (n<=0)
    {
        printf (" >>>>>>>>>>> erreur de saisie \n");
        return;
    }

    while ( current != NULL )
    {
        nextb =current->next;
        if ((current->d).ligne ==n)
        {
            free (current->d.s);
            free (current);
            current = NULL;

            ///
            if (previous == NULL)
            {
                if(nextb != NULL)
                {
                    nextb->prev = previous;
                    *first = nextb;
                }
            }
            else
            {
                previous->next = nextb;
                if ( nextb != NULL)
                    nextb->prev = previous;
            }
            break;
        }
        else
        {
            previous = current;
            current= current->next;
        }
    }
}


void supprime_lignes_vides (LISTE ** first)
{
    int i=0;
    LISTE * current;
    current = *first ;
    while ( current != NULL )
    {
        if ((current->d).s[0] == '\n')
        {
            i= current->d.ligne;
            supprime_ligne ( first, i);
        }
        else
        current= current->next;
    }
    update_num_ligne(first,1);
}


void print_data(LISTE * Current)
{

    if (Current == NULL)
    {
        printf("\n \n ******************************** \n FIN FICHIER \n");
    }
    else
    {
        printf(" >>>>>>>>>>> Num ligne = %d \n %s\n", Current->d.ligne ,Current->d.s);

    }
}


void supprime_bloc (LISTE ** first,  int ld, int nl)
{
    int nf;
    nf=nl+ld;
    int i = 0;

    for (i= ld; i<nf; i++ )
    {
        supprime_ligne(first,i);
    }
    update_num_ligne(first,1);
}


void affiche_lignes( LISTE * first, char* s_chaine)
{
    LISTE * current;
    current =  first;
    while (current != NULL)
    {
        if ( strstr ((current->d).s, s_chaine) == NULL)
        current = current ->next;
        else
        {
            print_data( current);
            current = current->next;
        }
    }
}

void insere_ligne(LISTE **first, int n, char* s)
{
    LISTE * part1;
    LISTE * part2;
    part1 = *first;
    part2 = *first;
     if (n<0)
    {
        printf (" >>>>>>>>>>> erreur de saisie \n");
        return;
    }
    else if ( n=0)
    {
        malloc;
    }
    else
    {
        while (( part1 != NULL)&& ((part1->d).ligne != n))
           {
                part1 = part1->next;
           }
        part2= part1->next;
        part1->next = NULL;
        part1 = *first;
        insert_at_last(& part1, NULL, n+1, s );
        while (part1->next != NULL)
            {
                part1 = part1->next;
            }
        part1->next = part2;
        part2->prev = part1;
        update_num_ligne(first, 1);

    }
}

void freee (LISTE ** first)
{
    LISTE * current;
    LISTE * current_next;
    current = *first;
    current_next = * first;
    while ( current =! NULL)
    {
        current_next = current->next;
        free (current->d.s);
        free (current);
        current = current_next;
    }
    first = NULL;
}



