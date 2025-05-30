
/* GRAMATICA 1
    A → B C
    C → B C | ε
    B → D | E F
    F → TKN_LPAREN G TKN_RPAREN TKN_LBRACE TKN_RBRACE | TKN_SEMICOLON

    D → TKN_CLASS TKN_ID J TKN_LBRACE TKN_RBRACE TKN_SEMICOLON
    J → TKN_COLON K | ε
    K → L TKN_COMMA K | L
    L → M TKN_ID | TKN_ID
    M → TKN_PUBLIC | TKN_PRIVATE | TKN_PROTECTED

    G → N | ε
    N → E TKN_COMMA N | E

    E → O P TKN_ID
    O → TKN_INT | TKN_CHAR | TKN_LONG | TKN_FLOAT | TKN_DOUBLE | TKN_STRING | TKN_VOID | TKN_ID
    P → TKN_STAR | TKN_AMPERSAND | ε
*/

/* ESTADOS 1
I0
A' → •A / {$} 
A → •C / {$} 
C → •B C / {$} 
C → •ε / {$}
B → •D / {class, int, char, long, float, double, string, void, id, $}
B → •E F / {class, int, char, long, float, double, string, void, id, $}
D → •class id J { } ; / {class, int, char, long, float, double, string, void, id, $}
E → •O P id / {(, ;}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

I0 -> I1 (despues de id)
O → id• / {*, &, id}
I0 -> I2 (despues de void)
O → void• / {*, &, id}
I0 -> I3 (despues de string)
O → string• / {*, &, id}
I0 -> I4 (despues de double)
O → double• / {*, &, id}
I0 -> I5 (despues de float)
O → float• / {*, &, id}
I0 -> I6 (despues de long)
O → long• / {*, &, id}
I0 -> I7 (despues de char)
O → char• / {*, &, id}
I0 -> I8 (despues de int)
O → int• / {*, &, id}

I0 -> I9 (despues de O)
E → O •P id / {(, ;}
P → •* / {id}
P → •& / {id}
P → •ε / {id}

I9 -> I10 (despues de *)
P → *• / {id}
I9 -> I11 (&)
P → &• / {id}
I9 -> I12 (P)
E → O P •id / {(, ;}
I12 -> I13 (id)
E → O P id• / {(, ;}

I0 -> I14 (despues de class)
D → class •id J { } ; / {class, int, char, long, float, double, string, void, id, $}

I14 -> I15 (despues de  id)
D → class id• J { } ; / { { }
J → •: K / { { }
J → •ε / { { }

I15 -> I16 (despues de  :)
J → : •K / { { }
K → •L , K / { { } 
K → •L / { { }
L → •M id / { id }
L → •id / { id }
M → •public / { id }
M → •private / { id }
M → •protected / { id }

I16 -> I17 (despues de  K)
J → : K• / { { }
I16 -> I18 (despues de  public)
M → public• / { id }
I16 -> I19 (despues de  private)
M → private• / { id }
I16 -> I20 (despues de protected)
M → protected• / { id }
I16 -> I21 (despues de  id)
L → id• / { id }
I16 -> I22 (despues de  M)
L → M •id / { id }
I22 -> I23 (despues de  id)
L → M id• / { id }
I16 -> I24 (despues de L)
K → L• / { { }
I16 -> I25 (despues de L)
K → L •, K / { { } 

I25 -> I26 (despues de ,)
K → L , •K / { , }
K → •L , K / { , } 
K → •L / { { }
L → •M id / { id }
L → •id / { id }
M → •public / { id }
M → •private / { id }
M → •protected / { id }

I26 -> I27 (despues de  public)
M → public• / { id }
I26 -> I28 (despues de  private)
M → private• / { id }
I26 -> I29 (despues de protected)
M → protected• / { id }
I26 -> I30 (despues de  id)
L → id• / { id }
I26 -> I31 (despues de  M)
L → M •id / { id }
I26 -> I32 (despues de id)
L → M id• / { id }

I26 -> I33 (despues de K)
K → L , K• / { , }
I26 -> I34 despues de L)
K → L• / { , }
I26 -> I35 (despues de L)
K → L •, K / { , }

I15 -> I36(despues de J)
D → class id J• { } ; / { { }
I15 -> I37(despues de {)
D → class id J {• } ; / { { }
I15 -> I38(despues de })
D → class id J { }• ; / { { }
I15 -> I39(despues de ;)
D → class id J { } ;• / { { }

I0 -> I40 (despues de D)
B → D• / {class, int, char, long, float, double, string, void, id, $}

I0 -> I41 (despues de E)
B → E •F / {class, int, char, long, float, double, string, void, id, $}
F → •( G ) { } / {class, int, char, long, float, double, string, void, id, $}
F → •; / {class, int, char, long, float, double, string, void, id, $}

I41 -> I42 (despues de F)
B → E F• / {class, int, char, long, float, double, string, void, id, $}

I41 -> I85 (despues de ;)
F → ;• / { ( }

I41 -> I43 (despues de ()
F → ( •G ) { } / { ) }
G → •N / { ) }
G → •ε / { ) }
N → •E , N / { ) }
N → •E / { ) }
E → •O P id / {,, )}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

I43 -> I44 (despues de id)
O → id• / {*, &, id}
I43 -> I45 (despues de void)
O → void• / {*, &, id}
I43 -> I46 (despues de string)
O → string• / {*, &, id}
I43 -> I47 (despues de double)
O → double• / {*, &, id}
I43 -> I48 (despues de float)
O → float• / {*, &, id}
I43 -> I49 (despues de long)
O → long• / {*, &, id}
I43 -> I50 (despues de char)
O → char• / {*, &, id}
I43 -> I51 (despues de int)
O → int• / {*, &, id}

I43 -> I52 (despues de G)
F → ( G• ) { } / { ) }
I52 -> I53 (despues de ))
F → ( G )• { } / { ) }
I53 -> I54 (despues de {)
F → ( G ) {• } / { ) }
I54 -> I55 (despues de })
F → ( G ) {  }• / { ) }

I43 -> I56 (despues de N)
G → N• / { ) }
I43 -> I57 (despues de E)
N → E• / { ) }
I43 -> I58 (despues de E)
N → E• , N / { ) }

I58 -> I59 (despues de ,)
N → E , •N / { , }
N → •E , N / { , }
N → •E / { ) }
E → •O P id / {,, )}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

I59 -> I60 (despues de id)
O → id• / {*, &, id}
I59 -> I61 (despues de void)
O → void• / {*, &, id}
I59 -> I62 (despues de string)
O → string• / {*, &, id}
I59 -> I63 (despues de double)
O → double• / {*, &, id}
I59 -> I64 (despues de float)
O → float• / {*, &, id}
I59 -> I65 (despues de long)
O → long• / {*, &, id}
I59 -> I66 (despues de char)
O → char• / {*, &, id}
I59 -> I67 (despues de int)
O → int• / {*, &, id}

I59 -> I68 (despues de E)
N → E• / { , }
I59 -> I69 (despues de E)
N → E• , N / { , }
I59 -> I70 (N)
N → E , N• / { , }

I59 -> I71 (despues de O)
E → O •P id / {,, )}
P → •* / {id}
P → •& / {id}
P → •ε / {id}

I71 -> I74 (despues de *)
P → *• / {id}
I71 -> I75 (&)
P → &• / {id}
I71 -> I72 (P)
E → O P •id / {,, )}
I72 -> I73 (id)
E → O P id• / {,, )}

I43 -> I76 (despues de O)
E → O •P id / {,, )}
P → •* / {id}
P → •& / {id}
P → •ε / {id}

I76 -> I79 (despues de *)
P → *• / {id}
I76 -> I80 (&)
P → &• / {id}
I76 -> I77 (P)
E → O P •id / {,, )}
I77 -> I78 (id)
E → O P id• / {,, )}

I0 -> I81 (despues de B)
C → B •C / {$}
C → •B C / {$} 
C → •ε / {$}
B → •D / {class, int, char, long, float, double, string, void, id, $}
B → •E F / {class, int, char, long, float, double, string, void, id, $} 
D → •class id J { } ; / {class, int, char, long, float, double, string, void, id, $} 
E → •O P id / {(, ;}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

I81 -> I82(despues de C)
C → B C• / {$}

IO -> I83 (A)
A’ → A• / {$}

IO -> I84 (C)
A’ → C• / {$}

*/

/* GRAMATICA 2
A → C
C → B C | ε
B → D | E F
F → ( G ) { } | ;

D → class id J { } ;
J → : K | ε
K → K , L | L
L → M id | id 
M → public | private | protected 

G → N |ε
N → N, E | E

E → O P id 
O → int | char | long | float | double | string | void | id
P → * | & | ε 
*/

/* ESTADOS 2
0
A' → •A / {$} 
A → •C / {$} 
C → •B C / {$} 
C → •ε / {$}
B → •D / {class, int, char, long, float, double, string, void, id, $}
B → •E F / {class, int, char, long, float, double, string, void, id, $}
D → •class id J { } ; / {class, int, char, long, float, double, string, void, id, $}
E → •O P id / {(, ;}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

0 -> 1 (despues de id)
O → id• / {*, &, id})

0 -> 2 (despues de void)
O → void• / {*, &, id})

0 -> 3 (despues de string)
O → string• / {*, &, id})

0 -> 4 (despues de double)
O → double• / {*, &, id})

0 -> 5 (despues de float)
O → float• / {*, &, id})

0 -> 6 (despues de long)
O → long• / {*, &, id})

0 -> 7 (despues de char)
O → char• / {*, &, id})

0 -> 8 (despues de int)
O → int• / {*, &, id}) 

0 -> 9 (despues de O)
E → O •P id / {(, ;}
P → •* / {id}
P → •& / {id}
P → •ε / {id}

9 -> 10 (despues de *)
P → *• / {id}

9 -> 11 (despues de &)
P → &• / {id}

9 -> 12 (despues de P)
E → O P •id / {(, ;}

12 -> 13 (despues de id)
E → O P id• / {(, ;}

0 -> 14 (despues de class)
D → class •id J { } ; / {class, int, char, long, float, double, string, void, id, $}

14 -> 15 (despues de id)
D → class id• J { } ; / { { }
J → •: K / { { }
J → •ε / { { }

15 -> 16 (despues de J)
D → class id J• { } ; / { { }

16 -> 17 (despues de {)
D → class id J {• } ; / { { }

17 -> 18 (despues de })
D → class id J { }• ; / { { }

18 -> 19 (despues de ;)
D → class id J { } ;•  / { { }

15 -> 20 (despues de ;)
J → : •K / { { }
K → •K , L / { , }
K → •L / { { }
L → •M id / { id }
L → •id / { id }
M → •public / { id }
M → •private / { id }
M → •protected / { id }

20 -> 21 (despues de public)
M → public• / { id }

20 -> 22 (despues de private)
M → private• / { id }

20 -> 23 (despues de protected)
M → protected• / { id }

20 -> 24 (despues de id)
L → id• / { id }

20 -> 25 (despues de M)
L → M •id / { id }

25 -> 26 (despues de id)
L → M id• / { id }

20 -> 27 (despues de K)
J → : K• / { { }

20 -> 28 (despues de L)
K → L• / { { }

20 -> 29 (despues de K)
K → K• , L / { , }

29 -> 30 (despues de ,)
K → K , •L / { , }
L → •M id / { id }
L → •id / { id }
M → •public / { id }
M → •private / { id }
M → •protected / { id }

30 -> 31 (despues de id)
K → K , L• / { , }

0 -> 32 (despues de E)
B → E •F / {class, int, char, long, float, double, string, void, id, $}
F → •( G ) { } 
F → •; / { ( }

32 -> 33 (despues de F)
B → E F• / {class, int, char, long, float, double, string, void, id, $}

33 -> 34 (despues de ;)
F → ;• / { ( }

32 -> 35 (despues de ()
F → ( •G ) { } / { ) }
G → •N / { ) }
G → •ε / { ) }
N → •N , E / { , }
N → •E / { ) }
E → •O P id / {,, )}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void /{*, &, id})
O → •id / {*, &, id})

35 -> 36 (despues de N)
G → N• / { ) }

35 -> 37 (despues de E)
N → E• / { ) }

35 -> 42 (despues de N)
N → N •, E / { , }

42 -> 43 (despues de ,)
N → N , •E / { , }
E → •O P id / {,, )}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

43 -> 44 (despues de E)
N → N , E• / { , }

35 -> 38 (despues de G)
F → ( G• ) { } / { ) }

38 -> 39 (despues de ))
F → ( G )• { } / { ) }

39 -> 40 (despues de {)
F → ( G ) {• } / { ) }

40 -> 41 (despues de })
F → ( G ) {  }• / { ) }

35 -> 45 (despues de O)
E → O •P id / {,, )}
P → •* / {id}
P → •& / {id}
P → •ε / {id}

45 -> 46 (despues de P)
E → O P •id / {,, )}

46 -> 47 (despues de id)
E → O P id• / {,, )}

45 -> 48 (despues de *)
P → *• / {id}

45 -> 49 (despues de *)
P → &• / {id}

0 -> 50 (despues de B)
C → B •C / {$}
C → •B C / {$} 
C → •ε / {$}
B → •D / {class, int, char, long, float, double, string, void, id, $}
B → •E F /  {class, int, char, long, float, double, string, void, id, $}
D → •class id J { } ; /  {class, int, char, long, float, double, string, void, id, $}
E → •O P id / {(, ;}
O → •int / {*, &, id})
O → •char / {*, &, id})
O → •long / {*, &, id})
O → •float / {*, &, id})
O → •double / {*, &, id})
O → •string / {*, &, id})
O → •void / {*, &, id})
O → •id / {*, &, id})

50 -> 51 (despues de C)
C → B C• / {$}

0 -> 52 (despues de D)
B → D• /{class, int, char, long, float, double, string, void, id, $}

0 -> 53 (despues de C)
A → C• / {$} 

0 -> 54 (despues de A)
A’ → A• / {$}

'*/

/* GRAMATICA FINAL
A → C
C → B C | ε
B → D | E F
F → ( G ) { } | ;

D → class id J { } ;
J → : K | ε
K → K , L | L
L → M id | id 
M → public | private | protected 

G → N |ε
N → N, E | E

E → O P id 
O → int | char | long | float | double | string | void | id
P → * | & | ε 
*/

/* ESTADOS FINAL
Estado I0:
1. A’ → . A , { $ }
2. A → . C , { $ }
3. C → . B C , { $ }
4. C → . , { $ }
5. B → . D , { class, int, char, long, float, double, string, void, id, (, $ }
6. B → . E F , { class, int, char, long, float, double, string, void, id, (, $ }
7. D → . class id J { } ; , { class, int, char, long, float, double, string, void, id, (, $ }
8. E → . O P id , { (, ; }
9. O → . int , { *, &, id }
10. O → . char , { *, &, id }
11. O → . long , { *, &, id }
12. O → . float , { *, &, id }
13. O → . double , { *, &, id }
14. O → . string , { *, &, id }
15. O → . void , { *, &, id }
16. O → . id , { *, &, id }

Estado I1:
GOTO(0, int)
1. O → int • , { *, &, id }

Estado I2:
GOTO(0, char)
1. O → char • , { *, &, id }

Estado I3:
GOTO(0, long)
1. O → long • , { *, &, id }

Estado I4:
GOTO(0, float)
1. O → float • , { *, &, id }

Estado I5:
GOTO(0, double)
1. O → double • , { *, &, id }

Estado I6:
GOTO(0, string)
1. O → string • , { *, &, id }

Estado I7:
GOTO(0, void)
1. O → void • , { *, &, id }

Estado I8:
GOTO(0, id)
1. O → id • , { *, &, id }

Estado I9:
GOTO(0, O)
1. E → O • P id , { (, ; }
2. P → • * , { id }
3. P → • & , { id }
4. P → • , { id, (, ; }

Estado I10:
GOTO(9, *)
1. P → * • , { id }

Estado I11:
GOTO(9, &)
1. P → & • , { id }

Estado I12:
GOTO(9, P)
1. E → O P • id , { (, ; }

Estado I13:
GOTO(12, id)
1. E → O P id • , { (, ; } 

Estado I14:
GOTO(0, class)
1. D → class • id J { } ; , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I15:
GOTO(14, id)
1. D → class id • J { } ; , { class, int, char, long, float, double, string, void, id, (, $ }
2. J → . : K , { { }
3. J → . , { { }

Estado I16:
GOTO(15, J)
1. D → class id J . { } ; , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I17:
GOTO(16, {)
1. D → class id J { . } ; , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I18:
GOTO(17, })
1. D → class id J { } . ; , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I19:
GOTO(18, ;)
1. D → class id J { } ; • , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I20:
GOTO(15, :)
1. J → : • K , { { }
2. K → • K , L , { { }
3. K → • L , { { }
4. L → • M id , { { }
5. L → • id , { { }
6. M → • public , { id }
7. M → • private , { id }
8. M → • protected , { id }

Estado I21:
GOTO(20, public)
1. M → public • , { id }

Estado I22:
GOTO(20, private)
1. M → private • , { id }

Estado I23:
GOTO(20, protected)
1. M → protected • , { id }

Estado I24:
GOTO(20, id)
1. L → id • , { { }

Estado I25:
GOTO(20, M)
1. L → M • id , { { }

Estado I26:
GOTO(25, id)
1. L → M id • , { { }

Estado I27:
GOTO(20, K)
1. J → : K • , { { }
2. K → K . , L , { { }

Estado I28:
GOTO(20, L)
1. K → L • , { { }

Estado I29:
GOTO(27, ,)
1. K → K , . L , { { }
2. L → . M id , { { }
3. L → . id , { { }
4. M → . public , { id }
5. M → . private , { id }
6. M → . protected , { id }

Estado I30:
GOTO(29, L)
1. K → K , L • , { { }

// Redirecciones de I29 a estados existentes
GOTO(29, public) = 21
GOTO(29, private) = 22
GOTO(29, protected) = 23
GOTO(29, id) = 24 
GOTO(29, M) = 25

Estado I31:
GOTO(0, E)
1. B → E . F , { class, int, char, long, float, double, string, void, id, (, $ }
2. F → . ( ) , { class, int, char, long, float, double, string, void, id, (, $ }
3. F → . ; , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I32:
GOTO(31, ()
1. F → ( . G ) { } ; , { class, int, char, long, float, double, string, void, id, (, $ }
2. G → . N , { ) }
3. G → . , { ) }
4. N → . N, E , { ) }
5. N → . E , { ) }
6. E → . O P id , { ) }
7. O → . int , { *, &, id }
8. O → . char , { *, &, id }
9. O → . long , { *, &, id }
10. O → . float , { *, &, id }
11. O → . double , { *, &, id }
12. O → . string , { *, &, id }
13. O → . void , { *, &, id }
14. O → . id , { *, &, id }

Estado I33:
GOTO(31, ;)
1. F → ; • , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I34:
GOTO(31, F)
1. B → E F • , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I36:
GOTO(32, E)
1. N → E • , { ) }

Estado I37:
GOTO(32, G)
1. F → ( G . ) { } , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I38:
GOTO(32, O)
1. E → O . P id , { ) }
2. P → . * , { id }
3. P → . & , { id }
4. P → . , { id, ) }

// Redirecciones de I32 a estados existentes para tipos primitivos
GOTO(32, int) = 1
GOTO(32, char) = 2
GOTO(32, long) = 3
GOTO(32, float) = 4
GOTO(32, double) = 5
GOTO(32, string) = 6
GOTO(32, void) = 7
GOTO(32, id) = 8

Estado I39:
GOTO(35, ,)
1. N → N , . E , { ) }
2. E → . O P id , { ) }
3. O → . int , { *, &, id }
4. O → . char , { *, &, id }
5. O → . long , { *, &, id }
6. O → . float , { *, &, id }
7. O → . double , { *, &, id }
8. O → . string , { *, &, id }
9. O → . void , { *, &, id }
10. O → . id , { *, &, id }

// Redirecciones de I39 a estados existentes para tipos primitivos
GOTO(39, int) = 1
GOTO(39, char) = 2
GOTO(39, long) = 3
GOTO(39, float) = 4
GOTO(39, double) = 5
GOTO(39, string) = 6
GOTO(39, void) = 7
GOTO(39, id) = 8

Estado I40:
GOTO(39, E)
1. N → N , E • , { ) }

// Redirección de I39 a estado existente
GOTO(39, O) = 38

Estado I41:
GOTO(37, ))
1. F → ( G ) • { }, { class, int, char, long, float, double, string, void, id, (, $ }

Estado I42:
GOTO(41, {)
1. F → ( G ) { • }, { class, int, char, long, float, double, string, void, id, (, $ }

Estado I43:
GOTO(42, })
1. F → ( G ) { } • , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I44:
GOTO(38, P)
1. E → O P . id , { ) }

Estado I45:
GOTO(46, id)
1. E → O P id • , { ) }

// Redirecciones de I38 a estados existentes
GOTO(38, *) = 10 
GOTO(38, &) = 11 

Estado I46: // Este SÍ es un nuevo estado
GOTO(0, B)
1. C → B . C , { $ }
2. C → . B C , { $ }
3. C → . , { $ }
4. B → . D , { class, int, char, long, float, double, string, void, id, (, $ }
5. B → . E F , { class, int, char, long, float, double, string, void, id, (, $ }
6. D → . class id J { } ; , { class, int, char, long, float, double, string, void, id, (, $ }
7. E → . O P id , { (, ; }
8. O → . int , { *, &, id }
9. O → . char , { *, &, id }
10. O → . long , { *, &, id }
11. O → . float , { *, &, id }
12. O → . double , { *, &, id }
13. O → . string , { *, &, id }
14. O → . void , { *, &, id }
15. O → . id , { *, &, id }

Estado I47:
GOTO(46, C)
1. C → B C • , { $ }

// Redirecciones de I46 a estados existentes
GOTO(46, B) = 46 
GOTO(46, D) = 48
GOTO(46, E) = 31 
GOTO(46, class) = 14
GOTO(46, int) = 1
GOTO(46, char) = 2 
GOTO(46, long) = 3
GOTO(46, float) = 4 
GOTO(46, double) = 5 
GOTO(46, string) = 6 
GOTO(46, void) = 7 
GOTO(46, id) = 8 
GOTO(46, '(') = 32 
GOTO(46, O) = 9

Estado I48:
GOTO(0, D)
1. B → D • , { class, int, char, long, float, double, string, void, id, (, $ }

Estado I49:
GOTO(0, A)
1. A’ → A • , { $ } // ESTADO DE ACEPTACIÓN

Estado I50:
GOTO(0, C)
1. A → C • , { $ }
*/
  
/* TABLA GOTO-ACTION FINAL
Estado I0
ACTION:
    class: S14
    int: S1
    char: S2
    long: S3
    float: S4
    double: S5
    string: S6
    void: S7
    id: S8
    (: S32
GOTO:
    A: 49
    C: 50
    B: 46
    D: 48
    E: 31
    O: 9

Estado I1
ACTION:
    *: R9
    &: R9
    id: R9
    ): R9
    ,: R9
    ;: R9
    class: R9
    int: R9
    char: R9
    long: R9
    float: R9
    double: R9
    string: R9
    void: R9
    (: R9
    $: R9

Estado I2
ACTION: (Igual que I1, solo cambia el número de producción)
    *: R10
    &: R10
    id: R10
    ): R10
    ,: R10
    ;: R10
    class: R10
    int: R10
    char: R10
    long: R10
    float: R10
    double: R10
    string: R10
    void: R10
    (: R10
    $: R10

Estado I3
ACTION:
    *: R11
    &: R11
    id: R11
    ): R11
    ,: R11
    ;: R11
    class: R11
    int: R11
    char: R11
    long: R11
    float: R11
    double: R11
    string: R11
    void: R11
    (: R11
    $: R11

Estado I4
ACTION:
    *: R12
    &: R12
    id: R12
    ): R12
    ,: R12
    ;: R12
    class: R12
    int: R12
    char: R12
    long: R12
    float: R12
    double: R12
    string: R12
    void: R12
    (: R12
    $: R12

Estado I5
ACTION:
    *: R13
    &: R13
    id: R13
    ): R13
    ,: R13
    ;: R13
    class: R13
    int: R13
    char: R13
    long: R13
    float: R13
    double: R13
    string: R13
    void: R13
    (: R13
    $: R13

Estado I6
ACTION:
    *: R14
    &: R14
    id: R14
    ): R14
    ,: R14
    ;: R14
    class: R14
    int: R14
    char: R14
    long: R14
    float: R14
    double: R14
    string: R14
    void: R14
    (: R14
    $: R14

Estado I7
ACTION:
    *: R15
    &: R15
    id: R15
    ): R15
    ,: R15
    ;: R15
    class: R15
    int: R15
    char: R15
    long: R15
    float: R15
    double: R15
    string: R15
    void: R15
    (: R15
    $: R15

Estado I8
    ACTION:
    *: R16
    &: R16
    id: R16
    ): R16
    ,: R16
    ;: R16
    class: R16
    int: R16
    char: R16
    long: R16
    float: R16
    double: R16
    string: R16
    void: R16
    (: R16
    $: R16

Estado I9
ACTION:
    *: S10
    &: S11
    id: S13 (Shift/Reduce conflict for R19, resolving to Shift)
    (: S13 (Shift/Reduce conflict for R19, resolving to Shift)
    ;: S13 (Shift/Reduce conflict for R19, resolving to Shift)
GOTO:
    P: 12

Estado I10
ACTION:
    id: R17 (Lookahead)

Estado I11
ACTION:
    id: R18 (Lookahead)

Estado I12
ACTION:
    id: S13

Estado I13
ACTION:
    (: R8
    ;: R8
    class: R8
    int: R8
    char: R8
    long: R8
    float: R8
    double: R8
    string: R8
    void: R8
    id: R8
    $: R8

Estado I14
ACTION:
    id: S15

Estado I15
ACTION:
    {: R21
    :: S20
GOTO:
    J: 16  

Estado I16
ACTION:
    {: S17

Estado I17
ACTION:
    }: S18

Estado I18
ACTION:
    ;: S19

Estado I19
ACTION:
    class: R7
    int: R7
    char: R7
    long: R7
    float: R7
    double: R7
    string: R7
    void: R7
    id: R7
    (: R7
    $: R7

Estado I20
ACTION:
    public: S21
    private: S22
    protected: S23
    id: S24
    GOTO:
    K: 27
    L: 28
    M: 25

Estado I21
ACTION:
    id: R26 

Estado I22
ACTION:
    id: R27

Estado I23
ACTION:
    id: R28

Estado I24
ACTION:
    {: R25
    ,: R25 //SE AGREFGO DE ULTOIMO MOMENTO

Estado I25
ACTION:
    id: S26

Estado I26
ACTION:
    {: R24
    ,: R24 //SE AGREFGO DE ULTOIMO MOMENTO

Estado I27
ACTION:
    {: R20
    ,: S29

Estado I28
ACTION:
    {: R23
    ,: R23

Estado I29
ACTION:
    public: S21
    private: S22
    protected: S23
    id: S24
    GOTO:
    L: 30
    M: 25

Estado I30
ACTION:
    {: R22


Estado I31
ACTION:
    (: S32
    ;: S33
GOTO:
    F: 34
  
Estado I32
ACTION:
    int: S1
    char: S2
    long: S3
    float: S4
    double: S5
    string: S6
    void: S7
    id: S8
    ): R30
GOTO:
    G: 37
    N: 35
    E: 36
    O: 38

Estado I33
ACTION:
    class: R34
    int: R34
    char: R34
    long: R34
    float: R34
    double: R34
    string: R34
    void: R34
    id: R34
    (: R34
    $: R34

Estado I34
ACTION:
    class: R6
    int: R6
    char: R6
    long: R6
    float: R6
    double: R6
    string: R6
    void: R6
    id: R6
    (: R6
    $: R6

Estado I35
ACTION:
    ): R29
    ,: S39

Estado I36
ACTION:
    ): R32

Estado I37
ACTION:
    ): S41

Estado I38
ACTION:
    *: S10 (Redirección a I10)
    &: S11 (Redirección a I11)
    id: S45 (Shift/Reduce conflict for R19, resolving to Shift)
    ): R19 (Reduce for P → ε)

Estado I39
ACTION:
    int: S1 (Redirección a I1)
    char: S2 (Redirección a I2)
    long: S3 (Redirección a I3)
    float: S4 (Redirección a I4)
    double: S5 (Redirección a I5)
    string: S6 (Redirección a I6)
    void: S7 (Redirección a I7)
    id: S8 (Redirección a I8)
GOTO:
    E: 40
    O: 38 (Redirección a I38)

Estado I40
ACTION:
    ): R31

Estado I41
ACTION:
    {: S42

Estado I42
ACTION:
    }: S43

Estado I43
ACTION:
    class: R33
    int: R33
    char: R33
    long: R33
    float: R33
    double: R33
    string: R33
    void: R33
    id: R33
    (: R33
    $: R33

Estado I44
ACTION:
    id: S45
    ): R8 (Lookahead para E → O P id • era { ) })

Estado I45
ACTION:
    ): R8

Estado I46
ACTION:
    class: S14 (Redirección a I14)
    int: S1 (Redirección a I1)
    char: S2 (Redirección a I2)
    long: S3 (Redirección a I3)
    float: S4 (Redirección a I4)
    double: S5 (Redirección a I5)
    string: S6 (Redirección a I6)
    void: S7 (Redirección a I7)
    id: S8 (Redirección a I8)
    (: S32 (Redirección a I32)
    $: R4 (Reduce for C → ε)
GOTO:
    C: 47
    B: 46 (Autorreferencia)
    D: 48 (Redirección a I48)
    E: 31 (Redirección a I31)
    O: 9 (Redirección a I9)

Estado I47
ACTION:
    $: R3

Estado I48
ACTION:
    class: R5
    int: R5
    char: R5
    long: R5
    float: R5
    double: R5
    string: R5
    void: R5
    id: R5
    (: R5
    $: R5

Estado I49
ACTION:
    $: acc

Estado I50
ACTION:
    $: R2

*/