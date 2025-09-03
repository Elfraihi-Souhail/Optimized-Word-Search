
   LET
       Cmpt : INTEGER ;
       Search_word , Word1 , Word2 : STRING ;
       Bst1 , Bst2 , Bst3 , Search_result : BST OF STRING ;
       F : FILE OF STRINGS BUFFER S ;
       Lines , Depth1 , Depth2 , Depth3 : INTEGER ;
       Choice , Choice_level , Counter : INTEGER ;
       Accepted : BOOLEAN ;
       Create_file : ACTION ;
       Create_node : ACTION ;
       Left_rotate , Right_rotate : ACTION ;
       Insert_bst : ACTION ;
       Create_bst1 , Create_bst2 , Create_bst3 : ACTION ;
       Depth : FUNCTION ( INTEGER ) ;
       Inorder_bst , Inorder_count : ACTION ;
       Is_xyz : FUNCTION ( BOOLEAN ) ;
       Count_xyz : ACTION ;
       Xyz_in_level : ACTION ;
       Search_bst1 , Search_bst2 , Search_bst3 : ACTION ;
       Write_file : ACTION ;
       Next_inorder : FUNCTION ( BST OF STRING ) ;
       Single_word_search : ACTION ;
       Range_search : ACTION ;
   BEGIN
       Bst1 := NULL ;
       Bst2 := NULL ;
       Bst3 := NULL ;
       Search_result := NULL ;
       Choice := 1 ;
       Cmpt := 0 ;
       WHILE ( Choice <> 0 )
           WRITE ( '==================================================' ) ;
           WRITE ( '    OPTIMIZED WORD SEARCH USING BST VARIANTS    ' ) ;
           WRITE ( '==================================================' ) ;
           WRITE ( '' ) ;
           WRITE ( '== Initial Tree Construction & Verification ==' ) ;
           WRITE ( '1. Generate file with random words' ) ;
           WRITE ( '2. Construct BST-1, BST-2, and BST-3 from file' ) ;
           WRITE ( '3. Count words starting with X, Y, and Z' ) ;
           WRITE ( '4. Compute and display tree depth for all variants' ) ;
           WRITE ( '5. Display nodes that start with X, Y, Z per level' ) ;
           WRITE ( '6. Inorder traversal display' ) ;
           WRITE ( '7. Single Word Search' ) ;
           WRITE ( '8. Range Search [Word1, Word2]' ) ;
           WRITE ( '' ) ;
           WRITE ( '==================================================' ) ;
           WRITE ( '0. Exit Program' ) ;
           WRITE ( '==================================================' ) ;
           WRITE ( 'Enter your choice: ' ) ;
           READ ( Choice ) ;
           IF ( Choice = 0 )
               WRITE ( 'Exiting program...' ) ;
           ELSE
               IF ( Choice = 1 )
                   WRITE ( '' ) ;
                   WRITE ( 'How many words does your file contains? ' ) ;
                   READ ( Lines ) ;
                   WRITE ( 'Generating file with random words...' ) ;
                   CALL Create_file ( F , Lines ) ;
                   WRITE ( 'File generated successfully!' ) ;
               ELSE
                   IF ( Choice = 2 )
                       WRITE ( '' ) ;
                       WRITE ( 'Constructing BST-1, BST-2, and BST-3 from file...' ) ;
                       CALL Create_bst1 ( Bst1 , F , Lines ) ;
                       WRITE ( 'BST-1 constructed successfully!' ) ;
                       CALL Create_bst2 ( Bst2 , F , Lines ) ;
                       WRITE ( 'BST-2 constructed successfully!' ) ;
                       CALL Create_bst3 ( Bst3 , F , Lines ) ;
                       WRITE ( 'BST-3 constructed successfully!' ) ;
                       WRITE ( 'All trees constructed successfully!' ) ;
                   ELSE
                       IF ( Choice = 3 )
                           WRITE ( '' ) ;
                           WRITE ( 'Counting words starting with X, Y, and Z...' ) ;
                           Cmpt := 0 ;
                           CALL Count_xyz ( Bst1 , Cmpt ) ;
                           WRITE ( 'There are : ' , Cmpt , ' words that start with X, Y or Z' ) ;
                       ELSE
                           IF ( Choice = 4 )
                               WRITE ( '' ) ;
                               WRITE ( 'Computing tree depths...' ) ;
                               Depth1 := Depth ( Bst1 ) ;
                               Depth2 := Depth ( Bst2 ) ;
                               Depth3 := Depth ( Bst3 ) ;
                               WRITE ( 'BST1 depth: ' , Depth1 ) ;
                               WRITE ( 'BST2 depth: ' , Depth2 ) ;
                               WRITE ( 'BST3 depth: ' , Depth3 ) ;
                           ELSE
                               IF ( Choice = 5 )
                                   WRITE ( '' ) ;
                                   WRITE ( 'Displaying nodes that start with X, Y, Z per level...' ) ;
                                   WRITE ( 'Which BST ?' , '1. BST-1' , '2. BST-2' , '3. BST-3' ) ;
                                   READ ( Choice_level ) ;
                                   IF ( Choice_level = 1 )
                                       WRITE ( '==================================================' ) ;
                                       WRITE ( 'Displaying for BST-1 :' ) ;
                                       WRITE ( '==================================================' ) ;
                                       CALL Xyz_in_level ( Bst1 ) ;
                                   ELSE
                                       IF ( Choice_level = 2 )
                                           WRITE ( '==================================================' ) ;
                                           WRITE ( 'Displaying for BST-2 :' ) ;
                                           WRITE ( '==================================================' ) ;
                                           CALL Xyz_in_level ( Bst2 ) ;
                                       ELSE
                                           IF ( Choice_level = 3 )
                                               WRITE ( '==================================================' ) ;
                                               WRITE ( 'Displaying for BST-3 :' ) ;
                                               WRITE ( '==================================================' ) ;
                                               CALL Xyz_in_level ( Bst3 ) ;
                                           ELSE
                                               WRITE ( 'Error' ) ;
                                           ENDIF ;
                                       ENDIF ;
                                   ENDIF ;
                               ELSE
                                   IF ( Choice = 7 )
                                       WRITE ( '' ) ;
                                       WRITE ( 'Enter word to search: ' ) ;
                                       READ ( Search_word ) ;
                                       CALL Single_word_search ( Bst1 , Bst2 , Bst3 , Search_word , Search_result ) ;
                                       IF ( Search_result <> NULL )
                                           WRITE ( 'Word found!' ) ;
                                       ELSE
                                           WRITE ( 'Word not found!' ) ;
                                       ENDIF ;
                                   ELSE
                                       IF ( Choice = 8 )
                                           WRITE ( '' ) ;
                                           Accepted := FALSE ;
                                           WHILE ( NOT Accepted )
                                               WRITE ( 'Enter first word (Word1): ' ) ;
                                               READ ( Word1 ) ;
                                               WRITE ( 'Enter second word (Word2): ' ) ;
                                               READ ( Word2 ) ;
                                               IF ( Word1 > Word2 )
                                                   WRITE ( 'Error, lower bound <= upper bound' ) ;
                                               ELSE
                                                   Accepted := TRUE ;
                                               ENDIF ;
                                           ENDWHILE ;
                                           WRITE ( 'Words that are in the range [Word1 , Word2] are :' ) ;
                                           CALL Range_search ( Bst1 , Bst2 , Bst3 , Word1 , Word2 ) ;
                                       ELSE
                                           IF ( Choice = 6 )
                                               WRITE ( 'Display :' , '1. BST-1' , '2. BST-2' , '3. BST-3' ) ;
                                               READ ( Choice_level ) ;
                                               IF ( Choice_level = 1 )
                                                   WRITE ( '=================================================' ) ;
                                                   WRITE ( 'Displaying for BST-1 :' ) ;
                                                   WRITE ( '=================================================' ) ;
                                                   CALL Inorder_bst ( Bst1 ) ;
                                               ELSE
                                                   IF ( Choice_level = 2 )
                                                       WRITE ( '=================================================' )
                                                       ;
                                                       WRITE ( 'Displaying for BST-2 :' ) ;
                                                       WRITE ( '=================================================' )
                                                       ;
                                                       CALL Inorder_bst ( Bst2 ) ;
                                                   ELSE
                                                       IF ( Choice_level = 3 )
                                                           WRITE ( '=========================================' ) ;
                                                           WRITE ( 'Displaying for BST-3 :' ) ;
                                                           WRITE ( '=========================================' ) ;
                                                           CALL Inorder_bst ( Bst3 ) ;
                                                       ELSE
                                                           WRITE ( 'Error' ) ;
                                                       ENDIF ;
                                                   ENDIF ;
                                               ENDIF ;
                                           ELSE
                                               WRITE ( '=================================================' ) ;
                                               WRITE ( 'Invalid choice! Please try again.' ) ;
                                               WRITE ( '=================================================' ) ;
                                           ENDIF ;
                                       ENDIF ;
                                   ENDIF ;
                               ENDIF ;
                           ENDIF ;
                       ENDIF ;
                   ENDIF ;
               ENDIF ;
           ENDIF ;
       ENDWHILE ;
   END
  /*===================================================================== */
   ACTION Create_file ( F , Lines )
   LET
       F : FILE OF STRINGS BUFFER S ;
       I , Lines : INTEGER ;
   BEGIN
       OPEN ( F , 'F.txt' , 'N' ) ;
       FOR I := 0 , Lines
           S := RANDSTRING ( RANDNUMBER ( 5 ) + 1 ) ;
           WRITESEQ ( F , S ) ;
       EFOR ;
       CLOSE ( F ) ;
   END
  /*===================================================================== */
   ACTION Create_node ( P , Word )
   LET
       P : BST OF STRING ;
       Word : STRING ;
   BEGIN
       ALLOCATE_NODE ( P ) ;
       ASS_NODE_VAL ( P , Word ) ;
       ASS_PARENT ( P , NULL ) ;
       ASS_RC ( P , NULL ) ;
       ASS_LC ( P , NULL ) ;
   END
  /*===================================================================== */
   FUNCTION Is_xyz ( R ) : BOOLEAN ;
   LET
       R : BST OF STRING ;
       Word : STRING ;
       X , Y , Z , W : CHAR ;
   BEGIN
       IF ( R <> NULL )
           X := 'X' ;
           Y := 'Y' ;
           Z := 'a' ;
           Word := NODE_VALUE ( R ) ;
           W := CHARACT ( Word , 1 ) ;
           IF ( ( W = X ) OR ( W = Y ) OR ( W = Z ) )
               Is_xyz := TRUE ;
           ELSE
               Is_xyz := FALSE ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Insert_bst ( P , N , Word )
   LET
       P , N : BST OF STRING ;
       Word : STRING ;
       Q : BST OF STRING ;
       Inserted : BOOLEAN ;
   BEGIN
       IF ( P = NULL )
           CALL Create_node ( P , Word ) ;
           N := P ;
           Inserted := TRUE ;
       ELSE
           IF ( Word = NODE_VALUE ( P ) )
               N := P ;
               Inserted := FALSE ;
           ELSE
               IF ( Word < NODE_VALUE ( P ) )
                   Q := LC ( P ) ;
                   CALL Insert_bst ( Q , N , Word ) ;
                   ASS_LC ( P , Q ) ;
                   ASS_PARENT ( Q , P ) ;
                   Inserted := TRUE ;
               ELSE
                   Q := RC ( P ) ;
                   CALL Insert_bst ( Q , N , Word ) ;
                   ASS_RC ( P , Q ) ;
                   ASS_PARENT ( Q , P ) ;
                   Inserted := TRUE ;
               ENDIF ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Left_rotate ( P , Q )
   LET
       P , Q : BST OF STRING ;
      /* P is the parent of Q - standard left rotation for rebalancing */
   BEGIN
       ASS_RC ( P , LC ( Q ) ) ;
       IF ( LC ( Q ) <> NULL )
           ASS_PARENT ( LC ( Q ) , P ) ;
       ENDIF ;
       ASS_LC ( Q , P ) ;
       ASS_PARENT ( Q , PARENT ( P ) ) ;
       IF ( PARENT ( Q ) <> NULL )
           IF ( P = LC ( PARENT ( Q ) ) )
               ASS_LC ( PARENT ( Q ) , Q ) ;
           ELSE
               ASS_RC ( PARENT ( Q ) , Q ) ;
           ENDIF ;
       ENDIF ;
       ASS_PARENT ( P , Q ) ;
   END
  /*===================================================================== */
   ACTION Right_rotate ( P , Q )
   LET
       P , Q : BST OF STRING ;
      /* P is the parent of Q - mirror of left rotation */
   BEGIN
       ASS_LC ( P , RC ( Q ) ) ;
       IF ( RC ( Q ) <> NULL )
           ASS_PARENT ( RC ( Q ) , P ) ;
       ENDIF ;
       ASS_RC ( Q , P ) ;
       ASS_PARENT ( Q , PARENT ( P ) ) ;
       IF ( PARENT ( Q ) <> NULL )
           IF ( P = LC ( PARENT ( Q ) ) )
               ASS_LC ( PARENT ( Q ) , Q ) ;
           ELSE
               ASS_RC ( PARENT ( Q ) , Q ) ;
           ENDIF ;
       ENDIF ;
       ASS_PARENT ( P , Q ) ;
   END
  /*===================================================================== */
   FUNCTION Depth ( P ) : INTEGER ;
   LET
       P : BST OF STRINGS ;
       Right_depth , Left_depth : INTEGERS ;
   BEGIN
       IF ( P = NULL )
           Depth := - 1 ;
       ELSE
           Left_depth := Depth ( LC ( P ) ) ;
           Right_depth := Depth ( RC ( P ) ) ;
           Depth := MAX ( Left_depth , Right_depth ) + 1 ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Inorder_bst ( P )
   LET
       P : BST OF STRING ;
   BEGIN
       IF ( P <> NULL )
           CALL Inorder_bst ( LC ( P ) ) ;
           WRITE ( NODE_VALUE ( P ) ) ;
           CALL Inorder_bst ( RC ( P ) ) ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Inorder_count ( P , Counter )
   LET
       P : BST OF STRING ;
       Counter : INTEGER ;
   BEGIN
       IF ( P <> NULL )
           CALL Inorder_count ( LC ( P ) , Counter ) ;
           Counter := Counter + 1 ;
           CALL Inorder_count ( RC ( P ) , Counter ) ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Create_bst1 ( Bst1 , F , Lines )
   LET
       Bst1 , N : BST OF STRING ;
       F : FILE OF STRING BUFFER Word ;
       I , Lines : INTEGER ;
   BEGIN
       OPEN ( F , 'F.txt' , 'O' ) ;
       FOR I := 1 , Lines
           READSEQ ( F , Word ) ;
           CALL Insert_bst ( Bst1 , N , Word ) ;
          /* BST-1: Priority to XYZ nodes - move them to root */
           IF ( Is_xyz ( N ) )
               WHILE ( PARENT ( N ) <> NULL )
                   IF ( N = RC ( PARENT ( N ) ) )
                       CALL Left_rotate ( PARENT ( N ) , N ) ;
                   ELSE
                       CALL Right_rotate ( PARENT ( N ) , N ) ;
                   ENDIF ;
               ENDWHILE ;
               Bst1 := N ;
           ENDIF ;
       EFOR ;
       CLOSE ( F ) ;
   END
  /*===================================================================== */
   ACTION Create_bst2 ( Bst2 , F , Lines )
   LET
       Bst2 , N , Temp : BST OF STRING ;
       F : FILE OF STRING BUFFER Word ;
       I , Curr_depth , Target_depth , Lines : INTEGER ;
       First_char : CHAR ;
   BEGIN
       OPEN ( F , 'F.txt' , 'O' ) ;
       FOR I := 1 , Lines
           READSEQ ( F , Word ) ;
           CALL Insert_bst ( Bst2 , N , Word ) ;
           IF ( N <> NULL )
               First_char := CHARACT ( Word , 1 ) ;
              /* BST-2: XYZ nodes halfway up, other special chars at root */
               IF ( ( First_char = 'X' ) OR ( First_char = 'Y' ) OR ( First_char = 'a' ) )
              /* Calculate current node depth */
                   Curr_depth := 0 ;
                   Temp := N ;
                   WHILE ( PARENT ( Temp ) <> NULL )
                       Curr_depth := Curr_depth + 1 ;
                       Temp := PARENT ( Temp ) ;
                   ENDWHILE ;
                  /* Move XYZ nodes to halfway depth */
                   Target_depth := Curr_depth / 2 ;
                   WHILE ( ( PARENT ( N ) <> NULL ) AND ( Curr_depth > Target_depth ) )
                       IF ( N = RC ( PARENT ( N ) ) )
                           CALL Left_rotate ( PARENT ( N ) , N ) ;
                       ELSE
                           CALL Right_rotate ( PARENT ( N ) , N ) ;
                       ENDIF ;
                       Curr_depth := Curr_depth - 1 ;
                   ENDWHILE ;
               ELSE
              /* Nodes > 'a' or Z go to root */
                   IF ( ( First_char > 'a' ) OR ( First_char = 'Z' ) )
                       WHILE ( PARENT ( N ) <> NULL )
                           IF ( N = RC ( PARENT ( N ) ) )
                               CALL Left_rotate ( PARENT ( N ) , N ) ;
                           ELSE
                               CALL Right_rotate ( PARENT ( N ) , N ) ;
                           ENDIF ;
                       ENDWHILE ;
                       Bst2 := N ;
                   ENDIF ;
               ENDIF ;
           ENDIF ;
       EFOR ;
       CLOSE ( F ) ;
   END
  /*===================================================================== */
   ACTION Create_bst3 ( Bst3 , F , Lines )
   LET
       Bst3 , N : BST OF STRING ;
       F : FILE OF STRING BUFFER Word ;
       I , Lines : INTEGER ;
   BEGIN
       OPEN ( F , 'F.txt' , 'O' ) ;
       FOR I := 1 , Lines
           READSEQ ( F , Word ) ;
           CALL Insert_bst ( Bst3 , N , Word ) ;
          /* BST-3: Opposite of BST-1, give priority to non-XYZ nodes */
           IF ( NOT ( Is_xyz ( N ) ) )
               WHILE ( PARENT ( N ) <> NULL )
                   IF ( N = RC ( PARENT ( N ) ) )
                       CALL Left_rotate ( PARENT ( N ) , N ) ;
                   ELSE
                       CALL Right_rotate ( PARENT ( N ) , N ) ;
                   ENDIF ;
               ENDWHILE ;
               Bst3 := N ;
           ENDIF ;
       EFOR ;
       CLOSE ( F ) ;
   END
  /*===================================================================== */
   ACTION Xyz_in_level ( R )
   LET
       R , N : BST OF STRING ;
       Q : QUEUE OF BST OF STRING ;
       L : QUEUE OF INTEGER ;
       Cmpt , Level , Current_lvl : INTEGER ;
   BEGIN
  /* Level-order traversal to count XYZ nodes by level */
       CREATEQUEUE ( Q ) ;
       CREATEQUEUE ( L ) ;
       Level := 1 ;
       IF ( R <> NULL )
           ENQUEUE ( Q , R ) ;
           ENQUEUE ( L , Level ) ;
       ENDIF ;
       Cmpt := 0 ;
       Current_lvl := 1 ;
       WHILE ( NOT EMPTY_QUEUE ( Q ) )
           DEQUEUE ( Q , N ) ;
           DEQUEUE ( L , Level ) ;
           IF ( ( Is_xyz ( N ) ) AND ( Current_lvl <> Level ) )
               WRITE ( 'LEVEL ' , Current_lvl , ' : ' , Cmpt ) ;
               Current_lvl := Level ;
               Cmpt := 0 ;
           ENDIF ;
           IF ( Is_xyz ( N ) )
               WRITE ( NODE_VALUE ( N ) ) ;
               Cmpt := Cmpt + 1 ;
           ENDIF ;
           IF ( LC ( N ) <> NULL ) OR ( RC ( N ) <> NULL )
               Level := Level + 1 ;
               IF ( LC ( N ) <> NULL )
                   ENQUEUE ( Q , LC ( N ) ) ;
                   ENQUEUE ( L , Level ) ;
               ENDIF ;
               IF ( RC ( N ) <> NULL )
                   ENQUEUE ( Q , RC ( N ) ) ;
                   ENQUEUE ( L , Level ) ;
               ENDIF ;
           ENDIF ;
       ENDWHILE ;
       WRITE ( 'LEVEL ' , Current_lvl , ' : ' , Cmpt ) ;
   END
  /*===================================================================== */
   ACTION Count_xyz ( N , Cmpt )
   LET
       N : BST OF STRING ;
       Cmpt : INTEGER ;
   BEGIN
  /* Counts X,Y,Z nodes - BST-1 is best for this */
       IF ( N <> NULL )
           IF ( Is_xyz ( N ) )
               CALL Count_xyz ( LC ( N ) , Cmpt ) ;
               IF ( Is_xyz ( N ) )
                   Cmpt := Cmpt + 1 ;
               ENDIF ;
               CALL Count_xyz ( RC ( N ) , Cmpt ) ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Search_bst1 ( P , Word , Result )
   LET
       Result : BST OF STRING ;
       P : POINTER TO BST OF STRING ;
       Word : STRING ;
   BEGIN
  /* Search for words in BST-1 (good for XYZ words) */
       IF ( P <> NULL )
           IF ( Is_xyz ( P ) )
               CALL Search_bst1 ( LC ( P ) , Word , Result ) ;
               IF ( Word = NODE_VALUE ( P ) )
                   Result := P ;
                   P := NULL ;
               ENDIF ;
               IF ( P <> NULL )
                   CALL Search_bst1 ( RC ( P ) , Word , Result ) ;
               ENDIF ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Search_bst2 ( P , Word , Result )
   LET
       Result : BST OF STRING ;
       P : POINTER TO BST OF STRING ;
       Word : STRING ;
   BEGIN
  /* Search for words in BST-2 (good for non-XYZ words) */
       IF ( P <> NULL )
           IF ( NOT Is_xyz ( P ) )
               CALL Search_bst2 ( LC ( P ) , Word , Result ) ;
               IF ( Word = NODE_VALUE ( P ) )
                   Result := P ;
                   P := NULL ;
               ENDIF ;
               IF ( P <> NULL )
                   CALL Search_bst2 ( RC ( P ) , Word , Result ) ;
               ENDIF ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Search_bst3 ( P , Word , Result )
   LET
       Result : BST OF STRING ;
       P : POINTER TO BST OF STRING ;
       Word : STRING ;
   BEGIN
  /* Search for words in BST-3 (optimized for non-XYZ words) */
       IF ( P <> NULL )
           IF ( NOT Is_xyz ( P ) )
               CALL Search_bst3 ( LC ( P ) , Word , Result ) ;
               IF ( Word = NODE_VALUE ( P ) )
                   Result := P ;
                   P := NULL ;
               ENDIF ;
               IF ( P <> NULL )
                   CALL Search_bst3 ( RC ( P ) , Word , Result ) ;
               ENDIF ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Single_word_search ( P1 , P2 , P3 , Word , Result )
   LET
       Result : BST OF STRING ;
       P1 , P2 , P3 : POINTER TO BST OF STRING ;
       Word : STRING ;
   BEGIN
  /* Smart search - picks the right tree based on first letter */
       IF ( ( CHARACT ( Word , 1 ) = 'X' ) OR ( CHARACT ( Word , 1 ) = 'Y' ) OR ( CHARACT ( Word , 1 ) = 'a' ) )
           CALL Search_bst1 ( P1 , Word , Result ) ;
       ELSE
           IF ( ( CHARACT ( Word , 1 ) > 'a' ) OR ( CHARACT ( Word , 1 ) = 'Z' ) )
               CALL Search_bst2 ( P2 , Word , Result ) ;
           ELSE
               CALL Search_bst3 ( P3 , Word , Result ) ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   FUNCTION Next_inorder ( P ) : BST OF STRING ;
   LET
       P : BST OF STRING ;
   BEGIN
  /* Gets the next node in inorder traversal - needed for range search */
       IF ( P = NULL )
           Next_inorder := NULL ;
       ELSE
           IF ( RC ( P ) <> NULL )
               P := RC ( P ) ;
               WHILE ( LC ( P ) <> NULL )
                   P := LC ( P ) ;
               ENDWHILE ;
               Next_inorder := P ;
           ELSE
               WHILE ( ( PARENT ( P ) <> NULL ) AND ( P = RC ( PARENT ( P ) ) ) )
                   P := PARENT ( P ) ;
               ENDWHILE ;
               IF ( PARENT ( P ) = NULL )
                   Next_inorder := NULL ;
               ELSE
                   P := PARENT ( P ) ;
                   Next_inorder := P ;
               ENDIF ;
           ENDIF ;
       ENDIF ;
   END
  /*===================================================================== */
   ACTION Range_search ( Bst1 , Bst2 , Bst3 , Word_1 , Word_2 )
   LET
       Bst1 , Bst2 , Bst3 , Result_node : BST OF STRING ;
       Word_1 , Word_2 : STRING ;
       Upper_bound : BOOLEAN ;
   BEGIN
  /* Finds the starting point with smart tree selection */
       CALL Single_word_search ( Bst1 , Bst2 , Bst3 , Word_1 , Result_node ) ;
       Upper_bound := FALSE ;
      /* Traverse in order until upper bound or NULL */
       WHILE ( ( Result_node <> NULL ) AND ( NOT Upper_bound ) )
           WRITE ( NODE_VALUE ( Result_node ) ) ;
           IF ( NODE_VALUE ( Result_node ) = Word_2 )
               Upper_bound := TRUE ;
           ELSE
               Result_node := Next_inorder ( Result_node ) ;
           ENDIF ;
       ENDWHILE ;
   END
  /*===================================================================== */
   ACTION Write_file ( F , Lines )
   LET
       F : FILE OF STRING BUFFER Buff ;
       Word : STRING ;
       Lines , I : INTEGER ;
   BEGIN
  /* Creates a file with manually entered words */
       OPEN ( F , 'F.txt' , 'N' ) ;
       FOR I := 1 , Lines
           WRITE ( 'Type a word: ' ) ;
           READ ( Word ) ;
           Buff := Word ;
           WRITESEQ ( F , Buff ) ;
       EFOR ;
       CLOSE ( F ) ;
   END
