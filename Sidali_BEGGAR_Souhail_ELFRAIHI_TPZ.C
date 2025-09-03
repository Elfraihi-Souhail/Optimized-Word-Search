  /**--------------------------------------------------------**/
  /**       T r a n s l a t i o n   Z to C (Standard)        **/
  /**             By Pr. D.E ZEGOUR                          **/
  /**             E S I - Algier                             **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #include <stdbool.h>

  /* ANSI Color codes for Windows and Unix-like systems */
  #define RESET   "\033[0m"
  #define BLACK   "\033[30m"
  #define RED     "\033[31m"
  #define GREEN   "\033[32m"
  #define YELLOW  "\033[33m"
  #define BLUE    "\033[34m"
  #define MAGENTA "\033[35m"
  #define CYAN    "\033[36m"
  #define WHITE   "\033[37m"
  #define BOLD    "\033[1m"
  #define BG_BLACK "\033[40m"
  #define BG_RED   "\033[41m"
  #define BG_WHITE "\033[47m"
  #define PURPLE  "\033[38;5;129m"
  #define PINK    "\033[38;5;206m"

  typedef char * string255 ;
  typedef char * string2 ;

  #define True 1
  #define False 0

  /* Function to clear the screen - cross-platform */
  void clearScreen() {
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
  }

  /* Function to pause the screen */
  void pauseScreen() {
    printf("\n%s%s%sPress Enter to continue...%s", BG_BLACK, PINK, BOLD, RESET);
    while(getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter key
  }

  /* Function to display a menu header */
  void displayMenu(const char* title) {
    printf("\n\n\n");
    printf("%s", WHITE);
    printf("\t\t\t  ________________________________________________  \n");
    printf("\t\t\t /                                                \\ \n");
    printf("\t\t\t|%s%s%s", BG_BLACK, RED, BOLD);
    int len = strlen(title);
    int padding = (50 - len) / 2;
    printf("%*s%s%*s", padding, "", title, padding, "");
    printf("%s|\n", RESET);
    printf("\t\t\t \\________________________________________________/ \n\n");
  }

  /** -Implementation- **\: BINARY SEARCH TREE OF STRINGS**/

  /** Binary search trees **/

  typedef string255 Typeelem_As   ;
  typedef struct Noeud_As * Pointer_As ;

  struct Noeud_As
    {
      Typeelem_As  Val ;
      Pointer_As Fg ;
      Pointer_As Fd ;
      Pointer_As Pere ;
     } ;

  Typeelem_As Node_value_As( Pointer_As P )
    { return P->Val;   }

  Pointer_As Lc_As( Pointer_As P)
    { return P->Fg ; }

  Pointer_As Rc_As( Pointer_As P)
    { return P->Fd ; }

  Pointer_As Parent_As( Pointer_As P)
    { return P->Pere ; }

  void Ass_node_val_As ( Pointer_As P, Typeelem_As Val)
    {
       strcpy( P->Val , Val );
    }

  void Ass_lc_As( Pointer_As P, Pointer_As Q)
    { P->Fg =  Q;  }

  void Ass_rc_As( Pointer_As P, Pointer_As Q)
    { P->Fd =  Q ; }

  void Ass_parent_As( Pointer_As P, Pointer_As Q)
    { P->Pere =  Q ; }

void Allocate_node_As(Pointer_As *P)
{
    *P = (struct Noeud_As *) malloc(sizeof(struct Noeud_As));
    if (*P == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    (*P)->Val = (char*) malloc(255 * sizeof(char));
    if ((*P)->Val == NULL) {
        free(*P);
        printf("Memory allocation failed!\n");
        return;
    }
    
    (*P)->Fg = NULL;
    (*P)->Fd = NULL;
    (*P)->Pere = NULL;
}

  void Free_node_As( Pointer_As P)
  { 
    free(P->Val);  
    free (P ) ; 
  }


  /** -Implementation- **\: FILE **/

  /* Managing open files */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Stack_open_files  = NULL;

  /* Test if a file is open */
  _Ptr_Noeud _Open_file ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Stack_open_files; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Add an open file */
  void Push_Open_file ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Stack_open_files;
      _Stack_open_files = P;
    }

  /* Delete an open file and return its name */
  char * Pop_Open_file ( FILE *Fl)
    {
      char * Fp = (char*) malloc(100);
      _Ptr_Noeud P,  Prec  ;
      P= _Stack_open_files;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Stack_open_files = P->Suiv;
      free (P);
      return Fp ;
    }


   /** Files **/

  typedef char _Tx[255];
  typedef string255 Typestruct1_s;
  typedef _Tx Typestruct1_s_Buf;


  /** Abstract machine on files **/

  void Open_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Open_file(Fp);
      if ( P != NULL )
      /* The file is already open */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* The file is not open */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      Push_Open_file( Fp, *s);
    }

  void Close_s ( FILE * s )
    {
      char * Fp = (char*) malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, Pop_Open_file(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le m�me nom ?  */
      /* If yes, open it again at the saved position */
      P =  _Open_file (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Writeseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Writedir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Readseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
      }
    }

  void Readdir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
    }

  void Add_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, 0, 2); /* End of file */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Endfile_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* End of file */
      long K2 = ftell(s);   /* Position from beginning */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_block_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* End of file */
      K = ftell(s);   /* Position from beginning */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }


  /** -Implementation- **\: QUEUE OF BINARY SEARCH TREES OF STRINGS**/
  /** Queues **/

  typedef Pointer_As Typeelem_FAs ;
  typedef  struct Filedattente_FAs * Pointer_FAs ;
  typedef  struct Maillon_FAs * Ptliste_FAs ;

  struct Maillon_FAs
    {
      Typeelem_FAs Val ;
      Ptliste_FAs Suiv  ;
    };

  struct Filedattente_FAs
    {
      Ptliste_FAs Tete, Queue ;
    };

  void Createqueue_FAs ( Pointer_FAs *Fil   )
    {
      *Fil = (struct Filedattente_FAs *) malloc( sizeof( struct Filedattente_FAs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Empty_queue_FAs (Pointer_FAs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enqueue_FAs ( Pointer_FAs Fil , Typeelem_FAs Val   )
    {
      Ptliste_FAs Q;

      Q = (struct Maillon_FAs *) malloc( sizeof( struct Maillon_FAs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Empty_queue_FAs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Dequeue_FAs (Pointer_FAs Fil, Typeelem_FAs *Val )
    {
      if (! Empty_queue_FAs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "Queue is empty");
    }


  /** -Implementation- **\: QUEUE OF INTEGERS**/
  /** Queues **/

  typedef int Typeelem_Fi ;
  typedef  struct Filedattente_Fi * Pointer_Fi ;
  typedef  struct Maillon_Fi * Ptliste_Fi ;

  struct Maillon_Fi
    {
      Typeelem_Fi Val ;
      Ptliste_Fi Suiv  ;
    };

  struct Filedattente_Fi
    {
      Ptliste_Fi Tete, Queue ;
    };

  void Createqueue_Fi ( Pointer_Fi *Fil   )
    {
      *Fil = (struct Filedattente_Fi *) malloc( sizeof( struct Filedattente_Fi)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Empty_queue_Fi (Pointer_Fi Fil  )
    { return  Fil->Tete == NULL ;}

  void Enqueue_Fi ( Pointer_Fi Fil , Typeelem_Fi Val   )
    {
      Ptliste_Fi Q;

      Q = (struct Maillon_Fi *) malloc( sizeof( struct Maillon_Fi))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Empty_queue_Fi(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Dequeue_Fi (Pointer_Fi Fil, Typeelem_Fi *Val )
    {
      if (! Empty_queue_Fi(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "Queue is empty");
    }

   
  /** Variables of main program **/
  int Cmpt;
  string255 Search_word;
  string255 Word1;
  string255 Word2;
  Pointer_As Bst1=NULL;
  Pointer_As Bst2=NULL;
  Pointer_As Bst3=NULL;
  Pointer_As Search_result=NULL;
  FILE *F;
  Typestruct1_s S ;
  int Lines;
  int Depth1;
  int Depth2;
  int Depth3;
  int Choice;
  int Choice_level;
  int Counter;
  bool Accepted;

  /** Standard functions **/

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = (char*) malloc(N+1);

      char Chr1[27] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }

  char *Caract ( string255 Ch , int I )
    {
      char *s = (char*) malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }


  /** Function prototypes **/

  void Create_file (FILE *F , int *Lines);
  void Create_node (Pointer_As *P , string255 *Word);
  bool  Is_xyz (Pointer_As *R) ;
  void Insert_bst (Pointer_As *P , Pointer_As *N , string255 *Word);
  void Left_rotate (Pointer_As *P , Pointer_As *Q);
  void Right_rotate (Pointer_As *P , Pointer_As *Q);
  int  Depth (Pointer_As *P) ;
  void Inorder_bst (Pointer_As *P);
  void Inorder_count (Pointer_As *P , int *Counter);
  void Create_bst1 (Pointer_As *Bst1 , FILE *F , int *Lines);
  void Create_bst2 (Pointer_As *Bst2 , FILE *F , int *Lines);
  void Create_bst3 (Pointer_As *Bst3 , FILE *F , int *Lines);
  void Xyz_in_level (Pointer_As *R);
  void Count_xyz (Pointer_As *N , int *Cmpt);
  void Search_bst1 (Pointer_As *P , string255 *Word , Pointer_As *Result);
  void Search_bst2 (Pointer_As *P , string255 *Word , Pointer_As *Result);
  void Search_bst3 (Pointer_As *P , string255 *Word , Pointer_As *Result);
  void Single_word_search (Pointer_As *P1 , Pointer_As *P2 , Pointer_As *P3 , string255 *Word , Pointer_As *Result);
  Pointer_As Next_inorder (Pointer_As *P) ;
  void Range_search (Pointer_As *Bst1 , Pointer_As *Bst2 , Pointer_As *Bst3 , string255 *Word_1 , string255 *Word_2);
  void Write_file (FILE *F , int *Lines);
  void freeBST(Pointer_As *root);
  
  /* Statistical modules prototypes */
  void Create_bst0 (Pointer_As *Bst0, FILE *F, int *Lines);
  int Search_bst0 (Pointer_As *P, string255 *Word, Pointer_As *Result, int *PathLength);
  int Search_bst_triplet (Pointer_As *P1, Pointer_As *P2, Pointer_As *P3, string255 *Word, Pointer_As *Result);
  int Range_search_bst0 (Pointer_As *Bst0, string255 *Word_1, string255 *Word_2, int *NodesTraversed);
  int Range_search_triplet (Pointer_As *Bst1, Pointer_As *Bst2, Pointer_As *Bst3, string255 *Word_1, string255 *Word_2);
  void SimulateWordSearch(int M, int N);
  void SimulateRangeSearch(int M, int N);
  void Create_random_file(FILE *F, int Lines, char *Filename);
  void Create_random_pairs_file(FILE *F, int Lines, char *Filename);

  /*------------------------------------------------------------------------------------------*/
  void Create_file (FILE *F , int *Lines)
    {
      Typestruct1_s S ;
      int I;

     S = (char*) malloc(255 * sizeof(char));
     Open_s (&F , (char*)"F.txt" , (char*)"N" ) ;
     for( I  =  0 ;I <=  *Lines ; ++I){
       strcpy (S,   Aleachaine(Aleanombre(5 ) + 1 )) ;
       Writeseq_s ( F , S ) ;
      
     } ;
     Close_s ( F ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Create_node (Pointer_As *P , string255 *Word)
    {

     Allocate_node_As (& *P ) ;
     Ass_node_val_As ( *P , *Word ) ;
     Ass_parent_As ( *P , NULL ) ;
     Ass_rc_As ( *P , NULL ) ;
     Ass_lc_As ( *P , NULL ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  bool  Is_xyz (Pointer_As *R)
    {
      /** Local variables **/
      bool  Is_xyz2 ;
      string255 Word;
      string2 X;
      string2 Y;
      string2 Z;
      string2 W;

      /** Body of function **/
     Word = (char*) malloc(255 * sizeof(char));
     X = (char*) malloc(2 * sizeof(char));
     Y = (char*) malloc(2 * sizeof(char));
     Z = (char*) malloc(2 * sizeof(char));
     W = (char*) malloc(2 * sizeof(char));
     if( ( *R != NULL )) {
       strcpy (X,   "X") ;
       strcpy (Y,   "Y") ;
       strcpy (Z,   "a") ;
       strcpy (Word,   Node_value_As ( *R )) ;
       strcpy (W,   Caract ( Word , 1 )) ;
       if( ( (strcmp( W, X) == 0  ) || (strcmp( W, Y) == 0  ) || (strcmp( W, Z) == 0  ) )) {
         Is_xyz2  =  True ;
         }
       else
         {
         Is_xyz2  =  False ;
        
       } ;
      
     } ;
    
     return Is_xyz2 ;
    }
  /*------------------------------------------------------------------------------------------*/
  void Insert_bst (Pointer_As *P , Pointer_As *N , string255 *Word)
    {
      /** Local variables **/
      Pointer_As Q=NULL;
      bool Inserted;

      /** Body of function **/
     if( ( *P == NULL )) {
       Create_node ( & *P , & *Word ) ;
       *N  =  *P ;
       Inserted  =  True ;
       }
     else
       {
       if( (strcmp( *Word, Node_value_As ( *P )) == 0  )) {
         *N  =  *P ;
         Inserted  =  False ;
         }
       else
         {
         if( (strcmp( *Word, Node_value_As ( *P )) < 0  )) {
           Q  =  Lc_As ( *P ) ;
           Insert_bst ( & Q , & *N , & *Word ) ;
           Ass_lc_As ( *P , Q ) ;
           Ass_parent_As ( Q , *P ) ;
           Inserted  =  True ;
           }
         else
           {
           Q  =  Rc_As ( *P ) ;
           Insert_bst ( & Q , & *N , & *Word ) ;
           Ass_rc_As ( *P , Q ) ;
           Ass_parent_As ( Q , *P ) ;
           Inserted  =  True ;
          
         } ;
        
       } ;
      
     } ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Left_rotate (Pointer_As *P , Pointer_As *Q)
    {

      /** Body of function **/
     Ass_rc_As ( *P , Lc_As ( *Q ) ) ;
     if( ( Lc_As ( *Q ) != NULL )) {
       Ass_parent_As ( Lc_As ( *Q ) , *P ) ;
      
     } ;
     Ass_lc_As ( *Q , *P ) ;
     Ass_parent_As ( *Q , Parent_As ( *P ) ) ;
     if( ( Parent_As ( *Q ) != NULL )) {
       if( ( *P == Lc_As ( Parent_As ( *Q ) ) )) {
         Ass_lc_As ( Parent_As ( *Q ) , *Q ) ;
         }
       else
         {
         Ass_rc_As ( Parent_As ( *Q ) , *Q ) ;
        
       } ;
      
     } ;
     Ass_parent_As ( *P , *Q ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Right_rotate (Pointer_As *P , Pointer_As *Q)
    {

      /** Body of function **/
     Ass_lc_As ( *P , Rc_As ( *Q ) ) ;
     if( ( Rc_As ( *Q ) != NULL )) {
       Ass_parent_As ( Rc_As ( *Q ) , *P ) ;
      
     } ;
     Ass_rc_As ( *Q , *P ) ;
     Ass_parent_As ( *Q , Parent_As ( *P ) ) ;
     if( ( Parent_As ( *Q ) != NULL )) {
       if( ( *P == Lc_As ( Parent_As ( *Q ) ) )) {
         Ass_lc_As ( Parent_As ( *Q ) , *Q ) ;
         }
       else
         {
         Ass_rc_As ( Parent_As ( *Q ) , *Q ) ;
        
       } ;
      
     } ;
     Ass_parent_As ( *P , *Q ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  int  Depth (Pointer_As *P)
    {
      /** Local variables **/
      int  Depth2 ;
      int Right_depth;
      int Left_depth;
     Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( ( *P == NULL )) {
       Depth2  =  - 1 ;
       }
     else
       {
       _Px1 =  Lc_As ( *P ) ;
       Left_depth  =  Depth ( &_Px1) ;
       _Px2 =  Rc_As ( *P ) ;
       Right_depth  =  Depth ( &_Px2) ;
       Depth2  =  Max ( Left_depth , Right_depth ) + 1 ;
      
     } ;
    
     return Depth2 ;
    }
  /*------------------------------------------------------------------------------------------*/
  void Inorder_bst (Pointer_As *P)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;
      string2 firstChar;

      /** Body of function **/
     if( ( *P != NULL )) {
       _Px1 =  Lc_As ( *P ) ;
       Inorder_bst ( &_Px1) ;
       
       // Color words differently based on first character
       firstChar = (char*) malloc(2 * sizeof(char));
       firstChar[0] = Node_value_As(*P)[0];
       firstChar[1] = '\0';
       
       if(strcmp(firstChar, "X") == 0 || strcmp(firstChar, "Y") == 0 || strcmp(firstChar, "a") == 0) {
           printf(" %s%s%s", RED, Node_value_As(*P), RESET);
       } else if(strcmp(firstChar, "a") > 0 || strcmp(firstChar, "Z") == 0) {
           printf(" %s%s%s", GREEN, Node_value_As(*P), RESET);
       } else {
           printf(" %s%s%s", YELLOW, Node_value_As(*P), RESET);
       }
       
       free(firstChar);
       
       _Px2 =  Rc_As ( *P ) ;
       Inorder_bst ( &_Px2) ;
     } ;
    }
  /*------------------------------------------------------------------------------------------*/
  void Inorder_count (Pointer_As *P , int *Counter)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( ( *P != NULL )) {
       _Px1 =  Lc_As ( *P ) ;
       Inorder_count ( &_Px1, & *Counter ) ;
       *Counter  =  *Counter + 1 ;
       _Px2 =  Rc_As ( *P ) ;
       Inorder_count ( &_Px2, & *Counter ) ;
      
     } ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Create_bst1 (Pointer_As *Bst1 , FILE *F , int *Lines)
    {
      /** Local variables **/
      Pointer_As N=NULL;
      Typestruct1_s Word ;
      int I;
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     Word = (char*) malloc(255 * sizeof(char));
     Open_s (&F , (char*)"F.txt" , (char*)"A" ) ;
     for( I  =  1 ;I <=  *Lines ; ++I){
       Readseq_s ( F , Word ) ;
       Insert_bst ( & *Bst1 , & N , & Word ) ;
       if( ( Is_xyz ( & N ) )) {
         while( ( Parent_As ( N ) != NULL )) {
           if( ( N == Rc_As ( Parent_As ( N ) ) )) {
             _Px1 =  Parent_As ( N ) ;
             Left_rotate ( &_Px1, & N ) ;
             }
           else
             {
             _Px2 =  Parent_As ( N ) ;
             Right_rotate ( &_Px2, & N ) ;
            
           } ; 
 } ;
         *Bst1  =  N ;
        
       } ;
      
     } ;
     Close_s ( F ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Create_bst2 (Pointer_As *Bst2 , FILE *F , int *Lines)
    {
      /** Local variables **/
      Pointer_As N=NULL;
      Pointer_As Temp=NULL;
      Typestruct1_s Word ;
      int I;
      int Curr_depth;
      int Target_depth;
      string2 First_char;
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;
      Pointer_As _Px3=NULL;
      Pointer_As _Px4=NULL;

      /** Body of function **/
     Word = (char*)malloc(255 * sizeof(char));
     First_char = (char*)malloc(2 * sizeof(char));
     Open_s (&F , (char *)"F.txt" , (char *)"A" ) ;
     for( I  =  1 ;I <=  *Lines ; ++I){
       Readseq_s ( F , Word ) ;
       Insert_bst ( & *Bst2 , & N , & Word ) ;
       if( ( N != NULL )) {
         strcpy (First_char,   Caract ( Word , 1 )) ;
         if( ( (strcmp( First_char, "X") == 0  ) || (strcmp( First_char, "Y") == 0  ) || (strcmp( First_char, "a") == 0  ) )) {
           Curr_depth  =  0 ;
           Temp  =  N ;
           while( ( Parent_As ( Temp ) != NULL )) {
             Curr_depth  =  Curr_depth + 1 ;
             Temp  =  Parent_As ( Temp ) ;
            
 } ;
           Target_depth  =  Curr_depth / 2 ;
           while( ( ( Parent_As ( N ) != NULL ) && ( Curr_depth > Target_depth ) )) {
             if( ( N == Rc_As ( Parent_As ( N ) ) )) {
               _Px1 =  Parent_As ( N ) ;
               Left_rotate ( &_Px1, & N ) ;
               }
             else
               {
               _Px2 =  Parent_As ( N ) ;
               Right_rotate ( &_Px2, & N ) ;
              
             } ;
             Curr_depth  =  Curr_depth - 1 ;
            
 } ;
           }
         else
           {
           if( (strcmp( First_char, "a") > 0  ) || (strcmp( First_char, "Z") == 0 ) ) {
             while( ( Parent_As ( N ) != NULL )) {
               if( ( N == Rc_As ( Parent_As ( N ) ) )) {
                 _Px3 =  Parent_As ( N ) ;
                 Left_rotate ( &_Px3, & N ) ;
                 }
               else
                 {
                 _Px4 =  Parent_As ( N ) ;
                 Right_rotate ( &_Px4, & N ) ;
                
               } ;
              
 } ;
             *Bst2  =  N ;
            
           } ;
          
         } ;
        
       } ;
      
     } ;
     Close_s ( F ) ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Create_bst3 (Pointer_As *Bst3 , FILE *F , int *Lines)
    {
      /** Local variables **/
      Pointer_As N=NULL;
      Typestruct1_s Word ;
      int I;
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     Word = (char*) malloc(255 * sizeof(char));
     Open_s (&F , (char*)"F.txt" , (char*)"A" ) ;
     for( I  =  1 ;I <=  *Lines ; ++I){
       Readseq_s ( F , Word ) ;
       Insert_bst ( & *Bst3 , & N , & Word ) ;
       if( ( ! ( Is_xyz ( & N ) ) )) {
         while( ( Parent_As ( N ) != NULL )) {
           if( ( N == Rc_As ( Parent_As ( N ) ) )) {
             _Px1 =  Parent_As ( N ) ;
             Left_rotate ( &_Px1, & N ) ;
             }
           else
             {
             _Px2 =  Parent_As ( N ) ;
             Right_rotate ( &_Px2, & N ) ;
            
           } ;
          
 } ;
         *Bst3  =  N ;
        
       } ;
      
     } ;
     Close_s ( F ) ;
    }
  /*------------------------------------------------------------------------------------------*/
  void Xyz_in_level (Pointer_As *R)
    {
      /** Local variables **/
      Pointer_As N=NULL;
      Pointer_FAs Q=NULL;
      Pointer_Fi L=NULL;
      int Cmpt;
      int Level;
      int Current_lvl;
      string2 firstChar;

      /** Body of function **/
     Createqueue_FAs (& Q ) ;
     Createqueue_Fi (& L ) ;
     Level  =  1 ;
     if( ( *R != NULL )) {
       Enqueue_FAs ( Q , *R ) ;
       Enqueue_Fi ( L , Level ) ;
     } ;
     
     Cmpt  =  0 ;
     Current_lvl  =  1 ;
     
     // Print header for first level
     printf("\n%s%s%sLEVEL %d:%s\n", BG_BLACK, BOLD, CYAN, Current_lvl, RESET);
     
     while( ( ! Empty_queue_FAs ( Q ) )) {
       Dequeue_FAs ( Q , &N ) ;
       Dequeue_Fi ( L , &Level ) ;
       
       // If we've moved to a new level, print summary of previous level and header for new level
       if( Current_lvl != Level ) {
         printf("\n%s%s%s%d words in level %d%s\n", 
                BG_BLACK, BOLD, RED, Cmpt, Current_lvl, RESET);
         Current_lvl = Level;
         printf("\n%s%s%sLEVEL %d:%s\n", BG_BLACK, BOLD, CYAN, Current_lvl, RESET);
         Cmpt = 0;
       }
       
       if( Is_xyz ( & N ) ) {
         firstChar = (char*) malloc(2 * sizeof(char));
         firstChar[0] = Node_value_As(N)[0];
         firstChar[1] = '\0';
         
         if(strcmp(firstChar, "X") == 0 || strcmp(firstChar, "Y") == 0 || strcmp(firstChar, "a") == 0) {
             printf(" %s%s%s", RED, Node_value_As(N), RESET);
         } else if(strcmp(firstChar, "Z") == 0 || strcmp(firstChar, "a") > 0) {
             printf(" %s%s%s", GREEN, Node_value_As(N), RESET);
         } else {
             printf(" %s%s%s", YELLOW, Node_value_As(N), RESET);
         }
         
         free(firstChar);
         Cmpt = Cmpt + 1;
       }
       
       // Process children nodes
       if( ( Lc_As ( N ) != NULL ) || ( Rc_As ( N ) != NULL )) {
         Level = Level + 1;
         if( Lc_As ( N ) != NULL ) {
           Enqueue_FAs ( Q , Lc_As ( N ) );
           Enqueue_Fi ( L , Level );
         }
         
         if( Rc_As ( N ) != NULL ) {
           Enqueue_FAs ( Q , Rc_As ( N ) );
           Enqueue_Fi ( L , Level );
         }
       }
     }
     
     // Print summary for the last level
     printf("\n%s%s%s%d words in level %d%s\n", 
            BG_BLACK, BOLD, RED, Cmpt, Current_lvl, RESET);
    }
  /*------------------------------------------------------------------------------------------*/
  /* use BST-1 only */

  void Count_xyz (Pointer_As *N , int *Cmpt)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( ( *N != NULL )) {
       if( ( Is_xyz ( & *N ) )) {
         _Px1 =  Lc_As ( *N ) ;
         Count_xyz ( &_Px1, & *Cmpt ) ;
         if( ( Is_xyz ( & *N ) )) {
           *Cmpt  =  *Cmpt + 1 ;
          
         } ;
         _Px2 =  Rc_As ( *N ) ;
         Count_xyz ( &_Px2, & *Cmpt ) ;
        
       } ;
      
     } ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  void Search_bst1 (Pointer_As *P , string255 *Word , Pointer_As *Result)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( *P != NULL ) {
       // Check if current node matches the word
       if( strcmp( *Word, Node_value_As ( *P )) == 0 ) {
         *Result = *P;
         return; // Found the word, exit the function
       }
       
       // If the word is less than current node, search left subtree
       if( strcmp( *Word, Node_value_As ( *P )) < 0 ) {
         _Px1 = Lc_As ( *P );
         Search_bst1 ( &_Px1, Word, Result );
       }
       // If the word is greater than current node, search right subtree
       else {
         _Px2 = Rc_As ( *P );
         Search_bst1 ( &_Px2, Word, Result );
       }
     }
    }
  /*------------------------------------------------------------------------------------------*/
  void Search_bst2 (Pointer_As *P , string255 *Word , Pointer_As *Result)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( *P != NULL ) {
       // Check if current node matches the word
       if( strcmp( *Word, Node_value_As ( *P )) == 0 ) {
         *Result = *P;
         return; // Found the word, exit the function
       }
       
       // If the word is less than current node, search left subtree
       if( strcmp( *Word, Node_value_As ( *P )) < 0 ) {
         _Px1 = Lc_As ( *P );
         Search_bst2 ( &_Px1, Word, Result );
       }
       // If the word is greater than current node, search right subtree
       else {
         _Px2 = Rc_As ( *P );
         Search_bst2 ( &_Px2, Word, Result );
       }
     }
    }
  /*------------------------------------------------------------------------------------------*/
  void Search_bst3 (Pointer_As *P , string255 *Word , Pointer_As *Result)
    {
      /** Local variables **/
      Pointer_As _Px1=NULL;
      Pointer_As _Px2=NULL;

      /** Body of function **/
     if( *P != NULL ) {
       // Check if current node matches the word
       if( strcmp( *Word, Node_value_As ( *P )) == 0 ) {
         *Result = *P;
         return; // Found the word, exit the function
       }
       
       // If the word is less than current node, search left subtree
       if( strcmp( *Word, Node_value_As ( *P )) < 0 ) {
         _Px1 = Lc_As ( *P );
         Search_bst3 ( &_Px1, Word, Result );
       }
       // If the word is greater than current node, search right subtree
       else {
         _Px2 = Rc_As ( *P );
         Search_bst3 ( &_Px2, Word, Result );
       }
     }
    }
  /*------------------------------------------------------------------------------------------*/
  void Single_word_search (Pointer_As *P1 , Pointer_As *P2 , Pointer_As *P3 , string255 *Word , Pointer_As *Result)
    {
      /** Body of function **/
     // Initialize Result to NULL before search
     *Result = NULL;
     
     if( ( (strcmp( Caract ( *Word , 1 ), "X") == 0  ) || (strcmp( Caract ( *Word , 1 ), "Y") == 0  ) || (strcmp( Caract ( *Word , 1 ), "a") == 0  ) )) {
       Search_bst1 ( & *P1 , & *Word , & *Result ) ;
       }
     else
       {
       if( (strcmp( Caract ( *Word , 1 ), "a") > 0  )) {
         Search_bst2 ( & *P2 , & *Word , & *Result ) ;
         }
       else
         {
         Search_bst3 ( & *P3 , & *Word , & *Result ) ;
        
       } ;
      
     } ;
    
    }
  /*------------------------------------------------------------------------------------------*/
  Pointer_As Next_inorder (Pointer_As *P)
    {
      /** Local variables **/
     Pointer_As Next_inorder2 =NULL;
     Pointer_As Current = *P;

      /** Body of function **/
     if( ( Current == NULL )) {
       Next_inorder2  =  NULL ;
       }
     else
       {
       if( ( Rc_As ( Current ) != NULL )) {
         // Go to right child
         Current  =  Rc_As ( Current ) ;
         // Then all the way to the left
         while( ( Lc_As ( Current ) != NULL )) {
           Current  =  Lc_As ( Current ) ;
          
 } ;
         Next_inorder2  =  Current ;
         }
       else
         {
         // Go up until we're coming from a left child
         Pointer_As Child = Current;
         Current = Parent_As(Current);
         
         while( ( Current != NULL ) && ( Child == Rc_As ( Current ) ) ) {
           Child = Current;
           Current = Parent_As ( Current ) ;
          
 } ;
         Next_inorder2 = Current;
        
       } ;
      
     } ;
    
     return Next_inorder2 ;
    }
  /*------------------------------------------------------------------------------------------*/
  void Range_search (Pointer_As *Bst1 , Pointer_As *Bst2 , Pointer_As *Bst3 , string255 *Word_1 , string255 *Word_2)
    {
      /** Local variables **/
      Pointer_As Result_node=NULL;
      Pointer_As Current_node=NULL;
      bool Upper_bound;
      string2 firstChar;
      int wordCount = 0;

      /** Body of function **/
     Single_word_search ( & *Bst1 , & *Bst2 , & *Bst3 , & *Word_1 , & Result_node ) ;
     Upper_bound  =  False ;
     
     if (Result_node == NULL) {
         printf("%s%s%sNo words found in the specified range.%s\n", BG_BLACK, RED, BOLD, RESET);
         return;
     }
     
     // Make a copy of the starting node
     Current_node = Result_node;
     
     printf("%s%s[", BG_BLACK, WHITE);
     
     while( ( ( Current_node != NULL ) && ( ! Upper_bound ) )) {
       firstChar = (char*) malloc(2 * sizeof(char));
       firstChar[0] = Node_value_As(Current_node)[0];
       firstChar[1] = '\0';
       
       // Add comma between words after the first one
       if (wordCount > 0) {
           printf("%s, ", WHITE);
       }
       wordCount++;
       
       // Color words differently based on first character
       if(strcmp(firstChar, "X") == 0 || strcmp(firstChar, "Y") == 0 || strcmp(firstChar, "a") == 0) {
           printf("%s%s%s", RED, Node_value_As(Current_node), WHITE);
       } else if(strcmp(firstChar, "a") > 0 || strcmp(firstChar, "Z") == 0) {
           printf("%s%s%s", GREEN, Node_value_As(Current_node), WHITE);
       } else {
           printf("%s%s%s", YELLOW, Node_value_As(Current_node), WHITE);
       }
       
       free(firstChar);
       
       if( (strcmp( Node_value_As ( Current_node ), *Word_2) == 0  )) {
         Upper_bound  =  True ;
       } else {
         // Save current node before getting next
         Pointer_As Temp_node = Current_node;
         Current_node = Next_inorder(&Temp_node);
       }
     }
     
     printf("%s]%s", WHITE, RESET);
     
     if (wordCount == 0) {
         printf("\n%s%s%sNo words found in the specified range.%s", BG_BLACK, RED, BOLD, RESET);
     } else {
         printf("\n%s%s%sFound %d words in the range.%s", BG_BLACK, CYAN, BOLD, wordCount, RESET);
     }
    }
  /*------------------------------------------------------------------------------------------*/
  void freeBST(Pointer_As *root) {
        if (*root == NULL) return; 
        freeBST(&((*root)->Fg)); // Free left subtree
        freeBST(&((*root)->Fd)); // Free right subtree

        if ((*root)->Val ) {
         free((*root)->Val);
         (*root)->Val = NULL;
         } 
        free(*root);
        *root = NULL;
    }
   /*------------------------------------------------------------------------------------------*/
  void Write_file (FILE *F , int *Lines)
    {
      /** Local variables **/
      Typestruct1_s Buff ;
      string255 Word;
      int I;

      /** Body of function **/
     Buff = (char*) malloc(255 * sizeof(char));
     Word = (char*) malloc(255 * sizeof(char));
     Open_s (&F , (char*)"F.txt" , (char*)"N" ) ;
     for( I  =  1 ;I <=  *Lines ; ++I){
       printf ( " %s", "Type a word: " ) ;
       scanf ( " %[^\n]", Word ) ;
       strcpy (Buff,   Word) ;
       Writeseq_s ( F , Buff ) ;
      
     } ;
     Close_s ( F ) ;
    
    }
 /*------------------------------------------------------------------------------------------*/
void showMainMenu() {
    clearScreen();
    displayMenu("T P - Z  M E N U");

    printf("\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t|   %s1.%s %sGenerate random words file%s                  |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s2.%s %sBuild BST variants (1, 2, 3)%s                |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s3.%s %sCount X/Y/Z words%s                           |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s4.%s %sDisplay tree depths%s                         |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s5.%s %sShow X/Y/Z words by level%s                   |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s6.%s %sPerform inorder traversal%s                   |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s7.%s %sSearch for a word%s                           |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s8.%s %sRange search [Word1, Word2]%s                 |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s9.%s %sSimulate word search efficiency%s             |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s10.%s %sSimulate range search efficiency%s           |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t|   %s0.%s %sExit program%s                                |\n", RED, RESET, WHITE, RESET);
    printf("\t\t\t+--------------------------------------------------+\n\n");
    printf("\t\t\t%s>>>%s Enter your choice: %s", RED, WHITE, RESET);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Search_word = (char*) malloc(255 * sizeof(char));
    Word1 = (char*) malloc(255 * sizeof(char));
    Word2 = (char*) malloc(255 * sizeof(char));
    S  = (char*) malloc(255 * sizeof(char));
    Bst1  =  NULL ;
    Bst2  =  NULL ;
    Bst3  =  NULL ;
    Search_result  =  NULL ;
    Choice  =  1 ;
    Cmpt  =  0 ;
    bool Done = false;
    int M, N;

    while (Choice != 0) {
        showMainMenu();
        scanf(" %d", &Choice);

        if (Choice == 1) {
            clearScreen();
            displayMenu("GENERATE FILE WITH RANDOM WORDS ");
            printf("\n\t%s->%s How many words does your file contain: ", GREEN, RESET);
            scanf(" %d", &Lines);
            printf("\n\t%sGenerating file with random words...%s\n", RED, RESET);
            Create_file(F, &Lines);
            printf("\n\t%s%sFILE GENERATED SUCCESSFULLY!%s\n", GREEN, BOLD, RESET);
            Done = true;
            pauseScreen();
        }
        else if (Choice == 2) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("CONSTRUCTING BST VARIANTS ");
            printf("\n\t%sConstructing BST-1, BST-2, and BST-3 from file...%s\n", WHITE, RESET);

            printf("\t%sBuilding BST-1...%s", RED, RESET);
            Create_bst1(&Bst1, F, &Lines);
            printf(" %s[DONE]%s\n", GREEN, RESET);

            printf("\t%sBuilding BST-2...%s", RED, RESET);
            Create_bst2(&Bst2, F, &Lines);
            printf(" %s[DONE]%s\n", GREEN, RESET);

            printf("\t%sBuilding BST-3...%s", RED, RESET);
            Create_bst3(&Bst3, F, &Lines);
            printf(" %s[DONE]%s\n", GREEN, RESET);

            printf("\n\t%s%sALL TREES CONSTRUCTED SUCCESSFULLY!%s\n", CYAN, BOLD, RESET);
            pauseScreen();
        }
        else if (Choice == 3) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("COUNTING WORDS STARTING WITH X, Y, AND Z");
            Cmpt = 0;
            Count_xyz(&Bst1, &Cmpt);
            printf("\n\t%sThere are: %s%d%s words that start with X, Y or Z\n", RED, GREEN, Cmpt, RESET);
            pauseScreen();
        }
        else if (Choice == 4) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("TREE DEPTH ANALYSIS ");
            Depth1 = Depth(&Bst1);
            Depth2 = Depth(&Bst2);
            Depth3 = Depth(&Bst3);
            printf("\n\t%sBST-1 depth:%s %s%d%s\n", RED, RESET, CYAN, Depth1, RESET);
            printf("\t%sBST-2 depth:%s %s%d%s\n", RED, RESET, CYAN, Depth2, RESET);
            printf("\t%sBST-3 depth:%s %s%d%s\n", RED, RESET, CYAN, Depth3, RESET);
            pauseScreen();
        }
        else if (Choice == 5) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("DISPLAY NODES BY LEVEL");
            
            printf("\t\t\t+-------------------------------------------------------------+\n");
            printf("\t\t\t|        %s1.%s %sBST-1%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t|        %s2.%s %sBST-2%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t|        %s3.%s %sBST-3%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t+-------------------------------------------------------------+\n\n");
            printf("\t\t\t\t%s>>>%s Enter your choice: %s", RED, WHITE, RESET);
            
            scanf(" %d", &Choice_level);

            clearScreen();
            if (Choice_level == 1) {
                displayMenu("BST-1 LEVEL ANALYSIS");
                Xyz_in_level(&Bst1);
            } else if (Choice_level == 2) {
                displayMenu("BST-2 LEVEL ANALYSIS");
                Xyz_in_level(&Bst2);
            } else if (Choice_level == 3) {
                displayMenu("BST-3 LEVEL ANALYSIS");
                Xyz_in_level(&Bst3);
            } else {
                printf(RED "\n\tInvalid choice! Please select 1, 2, or 3.\n" RESET);
            }
            pauseScreen();
        }
        else if (Choice == 6) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("DISPLAY BST ");
            
            printf("\t\t\t+-------------------------------------------------------------+\n");
            printf("\t\t\t|        %s1.%s %sBST-1%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t|        %s2.%s %sBST-2%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t|        %s3.%s %sBST-3%s                                           |\n", RED, RESET, WHITE, RESET);
            printf("\t\t\t+-------------------------------------------------------------+\n\n");
            printf("\t\t\t\t%s>>>%s Enter your choice: %s", RED, WHITE, RESET);
            
            scanf(" %d", &Choice_level);

            clearScreen();
            if (Choice_level == 1) {
                displayMenu("BST-1 INORDER TRAVERSAL ");
                Inorder_bst(&Bst1);
            } else if (Choice_level == 2) {
                displayMenu("BST-2 INORDER TRAVERSAL ");
                Inorder_bst(&Bst2);
            } else if (Choice_level == 3) {
                displayMenu("BST-3 INORDER TRAVERSAL ");
                Inorder_bst(&Bst3);
            } else {
                printf(RED "\n\tInvalid choice! Please select 1, 2, or 3.\n" RESET);
            }
            printf("\n");
            pauseScreen();
        }
        else if (Choice == 7) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("SINGLE WORD SEARCH");
            printf("\n\t%s->%s Enter word to search: ", GREEN, RESET);
            scanf(" %[^\n]", Search_word);
            Single_word_search(&Bst1, &Bst2, &Bst3, &Search_word, &Search_result);
            if (Search_result != NULL) {
                printf(GREEN "\n\tWord '%s' found in the tree!\n" RESET, Search_word);
            } else {
                printf(RED "\n\tWord '%s' not found in any tree.\n" RESET, Search_word);
            }
            pauseScreen();
        }
        else if (Choice == 8) {
            if (!Done) {
                printf(RED "\n\tPlease treat option 1 first\n" RESET);
                pauseScreen();
                continue;
            }
            clearScreen();
            displayMenu("RANGE SEARCH [WORD1, WORD2] ");
            printf("\n\t%s->%s Enter first word (lower bound): ", GREEN, RESET);
            scanf(" %[^\n]", Word1);
            printf("\t%s->%s Enter second word (upper bound): ", GREEN, RESET);
            scanf(" %[^\n]", Word2);
            
            // Validate that Word1 is lexicographically less than or equal to Word2
            if (strcmp(Word1, Word2) > 0) {
                printf("\n\t%s%sError: First word must come before or equal to second word in dictionary order.%s\n", 
                       RED, BOLD, RESET);
                printf("\t%sSwapping words to proceed with search...%s\n", YELLOW, RESET);
                string255 Temp = (char*) malloc(255 * sizeof(char));
                strcpy(Temp, Word1);
                strcpy(Word1, Word2);
                strcpy(Word2, Temp);
                free(Temp);
                
                printf("\n\t%sNew range: '%s' to '%s'%s\n\n", 
                       CYAN, Word1, Word2, RESET);
            } else {
                printf("\n\t%sPerforming range search from '%s' to '%s'...%s\n\n", 
                       WHITE, Word1, Word2, RESET);
            }
            
            Range_search(&Bst1, &Bst2, &Bst3, &Word1, &Word2);
            pauseScreen();
        }
        else if (Choice == 9) {
            clearScreen();
            displayMenu("WORD SEARCH EFFICIENCY SIMULATION");
            
            printf("\n\t%s->%s Enter number of simulations (M >= 10): ", GREEN, RESET);
            scanf(" %d", &M);
            if (M < 10) {
                printf(RED "\n\tNumber of simulations must be at least 10. Setting M = 10.\n" RESET);
                M = 10;
            }
            
            printf("\t%s->%s Enter number of words per file (N >= 10,000): ", GREEN, RESET);
            scanf(" %d", &N);
            if (N < 10000) {
                printf(RED "\n\tNumber of words must be at least 10,000. Setting N = 10,000.\n" RESET);
                N = 10000;
            }
            
            printf("\n\t%s%sStarting simulation with M=%d and N=%d...%s\n", 
                   YELLOW, BOLD, M, N, RESET);
            
            SimulateWordSearch(M, N);
        }
        else if (Choice == 10) {
            clearScreen();
            displayMenu("RANGE SEARCH EFFICIENCY SIMULATION");
            
            printf("\n\t%s->%s Enter number of simulations (M >= 10): ", GREEN, RESET);
            scanf(" %d", &M);
            if (M < 10) {
                printf(RED "\n\tNumber of simulations must be at least 10. Setting M = 10.\n" RESET);
                M = 10;
            }
            
            printf("\t%s->%s Enter number of words per file (N >= 10,000): ", GREEN, RESET);
            scanf(" %d", &N);
            if (N < 10000) {
                printf(RED "\n\tNumber of words must be at least 10,000. Setting N = 10,000.\n" RESET);
                N = 10000;
            }
            
            printf("\n\t%s%sStarting simulation with M=%d and N=%d...%s\n", 
                   YELLOW, BOLD, M, N, RESET);
            
            SimulateRangeSearch(M, N);
        }
        else if (Choice == 0) {
            clearScreen();
            displayMenu("THANK YOU FOR USING THE PROGRAM");
        }
        else {
            printf(RED "\n\tInvalid choice! Please select a valid option.\n" RESET);
            pauseScreen();
        }
    }

    // Free allocated memory for BSTs before exiting
    freeBST(&Bst1);
    freeBST(&Bst2);
    freeBST(&Bst3);

    // Free string memory
    free(Search_word);
    free(Word1);
    free(Word2);
    free(S);

    return 0;
}

/*------------------------------------------------------------------------------------------*/
void Create_bst0 (Pointer_As *Bst0, FILE *F, int *Lines)
  {
    Pointer_As N=NULL;
    Typestruct1_s Word;
    int I;

   Word = (char*) malloc(255 * sizeof(char));
   if (Word == NULL) {
     printf("Memory allocation failed!\n");
     return;
   }
   
   Open_s (&F, (char*)"F.txt", (char*)"A");
   for (I = 1; I <= *Lines; ++I) {
     Readseq_s(F, Word);
     Insert_bst(Bst0, &N, &Word);
   }
   Close_s(F);
   free(Word); // Free allocated memory
  }

int Search_bst0 (Pointer_As *P, string255 *Word, Pointer_As *Result, int *PathLength)
  {
    Pointer_As Temp = *P;

   *Result = NULL;
   *PathLength = 0;
   
   // Track path length as we search
   while (Temp != NULL) {
     if (strcmp(*Word, Node_value_As(Temp)) == 0) {
       *Result = Temp;
       break;
     }
     
     (*PathLength)++;
     
     if (strcmp(*Word, Node_value_As(Temp)) < 0) {
       Temp = Lc_As(Temp);
     } else {
       Temp = Rc_As(Temp);
     }
   }
   
   return *PathLength;
  }

int Search_bst_triplet(Pointer_As *P1, Pointer_As *P2, Pointer_As *P3, string255 *Word, Pointer_As *Result)
  {
    int PathLength = 0;
    
   *Result = NULL;
   
   // Pick the right tree based on first letter
   if ((strcmp(Caract(*Word, 1), "X") == 0) || (strcmp(Caract(*Word, 1), "Y") == 0) || (strcmp(Caract(*Word, 1), "a") == 0)) {
     // BST1 for X, Y, a
     Pointer_As Temp = *P1;
     while (Temp != NULL) {
       if (strcmp(*Word, Node_value_As(Temp)) == 0) {
         *Result = Temp;
         break;
       }
       
       PathLength++;
       
       if (strcmp(*Word, Node_value_As(Temp)) < 0) {
         Temp = Lc_As(Temp);
       } else {
         Temp = Rc_As(Temp);
       }
     }
   }
   else if (strcmp(Caract(*Word, 1), "a") > 0) {
     // BST2 for letters after 'a'
     Pointer_As Temp = *P2;
     while (Temp != NULL) {
       if (strcmp(*Word, Node_value_As(Temp)) == 0) {
         *Result = Temp;
         break;
       }
       
       PathLength++;
       
       if (strcmp(*Word, Node_value_As(Temp)) < 0) {
         Temp = Lc_As(Temp);
       } else {
         Temp = Rc_As(Temp);
       }
     }
   }
   else {
     // BST3 for everything else
     Pointer_As Temp = *P3;
     while (Temp != NULL) {
       if (strcmp(*Word, Node_value_As(Temp)) == 0) {
         *Result = Temp;
         break;
       }
       
       PathLength++;
       
       if (strcmp(*Word, Node_value_As(Temp)) < 0) {
         Temp = Lc_As(Temp);
       } else {
         Temp = Rc_As(Temp);
       }
     }
   }
   
   return PathLength;
  }

int Range_search_bst0(Pointer_As *Bst0, string255 *Word_1, string255 *Word_2, int *NodesTraversed)
  {
    Pointer_As Result_node=NULL;
    Pointer_As Current_node=NULL;
    bool Upper_bound;
    int SearchPathLength = 0;
    int RangeOpsCount = 0;
    
   *NodesTraversed = 0;
   
   // First find the lower bound
   Search_bst0(Bst0, Word_1, &Result_node, &SearchPathLength);
   *NodesTraversed = SearchPathLength;
   
   if (Result_node == NULL) {
     return *NodesTraversed;
   }
   
   Current_node = Result_node;
   Upper_bound = False;
   
   // Count traversal operations in the range
   while ((Current_node != NULL) && (!Upper_bound)) {
     if (strcmp(Node_value_As(Current_node), *Word_2) == 0) {
       Upper_bound = True;
     } else {
       RangeOpsCount++;
       
       Pointer_As Temp_node = Current_node;
       Current_node = Next_inorder(&Temp_node);
     }
   }
   
   *NodesTraversed += RangeOpsCount;
   
   return *NodesTraversed;
  }

int Range_search_triplet(Pointer_As *Bst1, Pointer_As *Bst2, Pointer_As *Bst3, string255 *Word_1, string255 *Word_2)
  {
    Pointer_As Result_node=NULL;
    Pointer_As Current_node=NULL;
    bool Upper_bound;
    int SearchPathLength = 0;
    int RangeOpsCount = 0;
    
   // Find starting point - using the triplet approach
   SearchPathLength = Search_bst_triplet(Bst1, Bst2, Bst3, Word_1, &Result_node);
   
   if (Result_node == NULL) {
     return SearchPathLength;
   }
   
   Current_node = Result_node;
   Upper_bound = False;
   
   // Now traverse to upper bound
   while ((Current_node != NULL) && (!Upper_bound)) {
     if (strcmp(Node_value_As(Current_node), *Word_2) == 0) {
       Upper_bound = True;
     } else {
       RangeOpsCount++;
       
       Pointer_As Temp_node = Current_node;
       Current_node = Next_inorder(&Temp_node);
     }
   }
   
   return SearchPathLength + RangeOpsCount;
  }

void Create_random_file(FILE *F, int Lines, char *Filename)
  {
    Typestruct1_s S;
    int I;

   S = (char*) malloc(255 * sizeof(char));
   Open_s(&F, Filename, (char*)"N");
   for (I = 0; I <= Lines; ++I) {
     strcpy(S, Aleachaine(Aleanombre(5) + 1));
     Writeseq_s(F, S);
   }
   Close_s(F);
   free(S);
  }


void Create_random_pairs_file(FILE *F, int Lines, char *Filename)
  {
    Typestruct1_s Word1, Word2, Temp;
    int I;

   Word1 = (char*) malloc(255 * sizeof(char));
   Word2 = (char*) malloc(255 * sizeof(char));
   Temp = (char*) malloc(255 * sizeof(char));
   
   Open_s(&F, Filename, (char*)"N");
   for (I = 0; I <= Lines; ++I) {
     // Generate pair of words for range search
     strcpy(Word1, Aleachaine(Aleanombre(5) + 1));
     strcpy(Word2, Aleachaine(Aleanombre(5) + 1));
     
     // Make sure first word comes before second one
     if (strcmp(Word1, Word2) > 0) {
       strcpy(Temp, Word1);
       strcpy(Word1, Word2);
       strcpy(Word2, Temp);
     }
     
     Writeseq_s(F, Word1);
     Writeseq_s(F, Word2);
   }
   Close_s(F);
   free(Word1);
   free(Word2);
   free(Temp);
  }

/* Module 2: Simulation algorithm to evaluate word search efficiency */
void SimulateWordSearch(int M, int N)
    {
      FILE *F, *F2;
      Pointer_As Bst0 = NULL, Bst1 = NULL, Bst2 = NULL, Bst3 = NULL;
      Pointer_As Result = NULL;
      Typestruct1_s Word;
      int I, J;
      int BST0_Success[M], BST0_Failure[M];
      int Triplet_Success[M], Triplet_Failure[M];
      double Ratio_Success[M], Ratio_Failure[M];
      int PathLength;
      int TripletPathLength;
      int SimLines = N;
      
     Word = (char*) malloc(255 * sizeof(char));
     if (Word == NULL) {
       printf("%s%sMemory allocation failed!%s\n", RED, BOLD, RESET);
       return;
     }
     
     clearScreen();
     displayMenu("WORD SEARCH EFFICIENCY SIMULATION");
     
     printf("\n%s%s%sRunning %d simulations with %d words each...%s\n\n", BG_BLACK, CYAN, BOLD, M, N, RESET);
     
     // Zero out the arrays before we start
     for (I = 0; I < M; I++) {
       BST0_Success[I] = BST0_Failure[I] = 0;
       Triplet_Success[I] = Triplet_Failure[I] = 0;
       Ratio_Success[I] = Ratio_Failure[I] = 0.0;
     }
     
     // Main simulation loop - each iteration is a complete test
     for (I = 0; I < M; I++) {
       printf("\n%s%s%sSimulation %d of %d:%s\n", BG_BLACK, BOLD, WHITE, I+1, M, RESET);
       
       // Create test data file
       printf("%s- Generating file F with %d random words...%s", YELLOW, N, RESET);
       Create_random_file(F, N, (char*)"F.txt");
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Set up the trees we're testing
       printf("%s- Building BST0...%s", YELLOW, RESET);
       Create_bst0(&Bst0, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST1...%s", YELLOW, RESET);
       Create_bst1(&Bst1, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST2...%s", YELLOW, RESET);
       Create_bst2(&Bst2, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST3...%s", YELLOW, RESET);
       Create_bst3(&Bst3, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Create file for words not in the tree
       printf("%s- Generating file F2 with %d random words...%s", YELLOW, N, RESET);
       Create_random_file(F2, N, (char*)"F2.txt");
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Test successful searches (words that are in the tree)
       printf("%s- Performing successful searches...%s", YELLOW, RESET);
       Open_s(&F, (char*)"F.txt", (char*)"A");
       for (J = 1; J <= N; J++) {
         Readseq_s(F, Word);
         
         // Test standard BST
         PathLength = 0;
         Result = NULL;
         Search_bst0(&Bst0, &Word, &Result, &PathLength);
         BST0_Success[I] += PathLength;
         
         // Test triplet BST approach
         Result = NULL;
         TripletPathLength = Search_bst_triplet(&Bst1, &Bst2, &Bst3, &Word, &Result);
         Triplet_Success[I] += TripletPathLength;
       }
       Close_s(F);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Test unsuccessful searches (words not in the tree)
       printf("%s- Performing unsuccessful searches...%s", YELLOW, RESET);
       Open_s(&F2, (char*)"F2.txt", (char*)"A");
       for (J = 1; J <= N; J++) {
         Readseq_s(F2, Word);
         
         // Test standard BST
         PathLength = 0;
         Result = NULL;
         Search_bst0(&Bst0, &Word, &Result, &PathLength);
         BST0_Failure[I] += PathLength;
         
         // Test triplet BST approach
         Result = NULL;
         TripletPathLength = Search_bst_triplet(&Bst1, &Bst2, &Bst3, &Word, &Result);
         Triplet_Failure[I] += TripletPathLength;
       }
       Close_s(F2);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Calculate efficiency ratios
       if (BST0_Success[I] > 0) {
         Ratio_Success[I] = (double)Triplet_Success[I] / BST0_Success[I];
       }
       
       if (BST0_Failure[I] > 0) {
         Ratio_Failure[I] = (double)Triplet_Failure[I] / BST0_Failure[I];
       }
       
       // Clean up trees before next iteration
       freeBST(&Bst0);
       freeBST(&Bst1);
       freeBST(&Bst2);
       freeBST(&Bst3);
       
       printf("%s%sCompleted simulation %d of %d%s\n", BOLD, GREEN, I+1, M, RESET);
     }
     
     // Show the results table
     clearScreen();
     displayMenu("WORD SEARCH EFFICIENCY RESULTS");
     
     printf("\n%s%s%s+==================================================================================================+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     printf("%s%s%s| %-10s | %-12s | %-12s | %-12s | %-12s | %-10s | %-10s |%s\n", 
            BG_BLACK, BOLD, WHITE, "Simulation", "BST0 Success", "Triplet Succ", "BST0 Failure", "Triplet Fail", "Ratio Succ", "Ratio Fail", RESET);
     printf("%s%s%s+--------------------------------------------------------------------------------------------------+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     
     double Avg_Ratio_Success = 0.0, Avg_Ratio_Failure = 0.0;
     
     for (I = 0; I < M; I++) {
       printf("%s%s%s| %-10d | %-12d | %-12d | %-12d | %-12d | %-.8f | %-.8f |%s\n", 
              BG_BLACK, BOLD, WHITE, I+1, BST0_Success[I], Triplet_Success[I], BST0_Failure[I], Triplet_Failure[I], 
              Ratio_Success[I], Ratio_Failure[I], RESET);
       
       Avg_Ratio_Success += Ratio_Success[I];
       Avg_Ratio_Failure += Ratio_Failure[I];
     }
     
     if (M > 0) {
       Avg_Ratio_Success /= M;
       Avg_Ratio_Failure /= M;
     }
     
     printf("%s%s%s+--------------------------------------------------------------------------------------------------+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     printf("%s%s%s| %-10s | %-12s | %-12s | %-12s | %-12s | %-.8f | %-.8f |%s\n", 
            BG_BLACK, BOLD, CYAN, "AVERAGE", "", "", "", "", Avg_Ratio_Success, Avg_Ratio_Failure, RESET);
     printf("%s%s%s+==================================================================================================+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     
     free(Word);
     
     // Explain what the results mean
     printf("\n%s%s%sInterpretation: %s\n", BG_BLACK, BOLD, YELLOW, RESET);
     printf("- Ratio < 1.0: The Triplet approach is more efficient than BST0\n");
     printf("- Ratio > 1.0: BST0 is more efficient than the Triplet approach\n\n");
     
     if (Avg_Ratio_Success < 1.0) {
       printf("%s%s%sFor successful searches: The Triplet approach is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, GREEN, WHITE, (1.0 - Avg_Ratio_Success) * 100, GREEN, RESET);
     } else if (Avg_Ratio_Success > 1.0) {
       printf("%s%s%sFor successful searches: BST0 is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, RED, WHITE, (Avg_Ratio_Success - 1.0) * 100, RED, RESET);
     } else {
       printf("%s%s%sFor successful searches: Both approaches have equal efficiency.%s\n", 
              BG_BLACK, BOLD, YELLOW, RESET);
     }
     
     if (Avg_Ratio_Failure < 1.0) {
       printf("%s%s%sFor unsuccessful searches: The Triplet approach is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, GREEN, WHITE, (1.0 - Avg_Ratio_Failure) * 100, GREEN, RESET);
     } else if (Avg_Ratio_Failure > 1.0) {
       printf("%s%s%sFor unsuccessful searches: BST0 is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, RED, WHITE, (Avg_Ratio_Failure - 1.0) * 100, RED, RESET);
     } else {
       printf("%s%s%sFor unsuccessful searches: Both approaches have equal efficiency.%s\n", 
              BG_BLACK, BOLD, YELLOW, RESET);
     }
     
     pauseScreen();
}
  
  /* Module 3: Simulation algorithm to evaluate range search efficiency */
  void SimulateRangeSearch(int M, int N)
    {
      FILE *F, *F2;
      Pointer_As Bst0 = NULL, Bst1 = NULL, Bst2 = NULL, Bst3 = NULL;
      Typestruct1_s Word1, Word2;
      int I, J;
      int BST0_Nodes[M], Triplet_Nodes[M];
      double Ratio[M];
      int NodesTraversed;
      int SimLines = N;
      int PairsLines = N/2;
      
     Word1 = (char*) malloc(255 * sizeof(char));
     Word2 = (char*) malloc(255 * sizeof(char));
     
     if (Word1 == NULL || Word2 == NULL) {
       printf("%s%sMemory allocation failed!%s\n", RED, BOLD, RESET);
       if (Word1) free(Word1);
       if (Word2) free(Word2);
       return;
     }
     
     clearScreen();
     displayMenu("RANGE SEARCH EFFICIENCY SIMULATION");
     
     printf("\n%s%s%sRunning %d simulations with %d words each...%s\n\n", BG_BLACK, CYAN, BOLD, M, N, RESET);
     
     // Reset counters
     for (I = 0; I < M; I++) {
       BST0_Nodes[I] = Triplet_Nodes[I] = 0;
       Ratio[I] = 0.0;
     }
     
     // Each simulation uses different random data
     for (I = 0; I < M; I++) {
       printf("\n%s%s%sSimulation %d of %d:%s\n", BG_BLACK, BOLD, WHITE, I+1, M, RESET);
       
       // Create dictionary file
       printf("%s- Generating file F with %d random words...%s", YELLOW, N, RESET);
       Create_random_file(F, N, (char*)"F.txt");
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Create range query test file - half as many pairs as words
       printf("%s- Generating file F2 with %d random word pairs...%s", YELLOW, PairsLines, RESET);
       Create_random_pairs_file(F2, PairsLines, (char*)"F2.txt");
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Build both types of trees we're comparing
       printf("%s- Building BST0...%s", YELLOW, RESET);
       Create_bst0(&Bst0, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST1...%s", YELLOW, RESET);
       Create_bst1(&Bst1, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST2...%s", YELLOW, RESET);
       Create_bst2(&Bst2, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       printf("%s- Building BST3...%s", YELLOW, RESET);
       Create_bst3(&Bst3, F, &SimLines);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Now run range queries on both approaches
       printf("%s- Performing range searches...%s", YELLOW, RESET);
       Open_s(&F2, (char*)"F2.txt", (char*)"A");
       BST0_Nodes[I] = 0;
       Triplet_Nodes[I] = 0;
       
       for (J = 1; J <= PairsLines; J++) {
         // Get a pair of words defining our range
         Readseq_s(F2, Word1);
         Readseq_s(F2, Word2);
         
         // Test standard BST
         NodesTraversed = 0;
         Range_search_bst0(&Bst0, &Word1, &Word2, &NodesTraversed);
         BST0_Nodes[I] += NodesTraversed;
         
         // Test triplet BST structure
         Triplet_Nodes[I] += Range_search_triplet(&Bst1, &Bst2, &Bst3, &Word1, &Word2);
       }
       Close_s(F2);
       printf(" %s[DONE]%s\n", GREEN, RESET);
       
       // Ratio < 1 means triplet is better
       if (BST0_Nodes[I] > 0) {
         Ratio[I] = (double)Triplet_Nodes[I] / BST0_Nodes[I];
       } else {
         Ratio[I] = 1.0; // Equal if no nodes traversed
       }
       
       // Free memory before next round
       freeBST(&Bst0);
       freeBST(&Bst1);
       freeBST(&Bst2);
       freeBST(&Bst3);
       
       printf("%s%sCompleted simulation %d of %d%s\n", BOLD, GREEN, I+1, M, RESET);
     }
     
     // Show results summary
     clearScreen();
     displayMenu("RANGE SEARCH EFFICIENCY RESULTS");
     
     printf("\n%s%s%s+=============================================================+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     printf("%s%s%s| %-10s | %-15s | %-15s | %-10s |%s\n", 
            BG_BLACK, BOLD, WHITE, "Simulation", "BST0 Nodes", "Triplet Nodes", "Ratio", RESET);
     printf("%s%s%s+-------------------------------------------------------------+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     
     double Avg_Ratio = 0.0;
     
     for (I = 0; I < M; I++) {
       printf("%s%s%s| %-10d | %-15d | %-15d | %-.8f |%s\n", 
              BG_BLACK, BOLD, WHITE, I+1, BST0_Nodes[I], Triplet_Nodes[I], Ratio[I], RESET);
       
       Avg_Ratio += Ratio[I];
     }
     
     if (M > 0) {
       Avg_Ratio /= M;
     }
     
     printf("%s%s%s+-------------------------------------------------------------+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     printf("%s%s%s| %-10s | %-15s | %-15s | %-.8f |%s\n", 
            BG_BLACK, BOLD, CYAN, "AVERAGE", "", "", Avg_Ratio, RESET);
     printf("%s%s%s+=============================================================+%s\n", 
            BG_BLACK, BOLD, WHITE, RESET);
     
     free(Word1);
     free(Word2);
     
     // Help interpret the results
     printf("\n%s%s%sInterpretation: %s\n", BG_BLACK, BOLD, YELLOW, RESET);
     printf("- Ratio < 1.0: The Triplet approach is more efficient than BST0\n");
     printf("- Ratio > 1.0: BST0 is more efficient than the Triplet approach\n\n");
     
     if (Avg_Ratio < 1.0) {
       printf("%s%s%sFor range searches: The Triplet approach is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, GREEN, WHITE, (1.0 - Avg_Ratio) * 100, GREEN, RESET);
     } else if (Avg_Ratio > 1.0) {
       printf("%s%s%sFor range searches: BST0 is %s%.2f%%%s more efficient.%s\n", 
              BG_BLACK, BOLD, RED, WHITE, (Avg_Ratio - 1.0) * 100, RED, RESET);
     } else {
       printf("%s%s%sFor range searches: Both approaches have equal efficiency.%s\n", 
              BG_BLACK, BOLD, YELLOW, RESET);
     }
     
     pauseScreen();
    }

/*------------------------------------------------------------------------------------------*/
