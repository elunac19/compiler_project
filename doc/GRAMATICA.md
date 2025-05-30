---
## Estados de la Gramática Final

A continuación, se presentan los estados de la gramática final, organizados por su número de estado y las producciones que contienen, junto con sus *lookaheads*.

---

### Estado I0:
1.  **A’ → . A**, { $ }
2.  **A → . C**, { $ }
3.  **C → . B C**, { $ }
4.  **C → . ε**, { $ }
5.  **B → . D**, { class, int, char, long, float, double, string, void, id, (, $ }
6.  **B → . E F**, { class, int, char, long, float, double, string, void, id, (, $ }
7.  **D → . class id J { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }
8.  **E → . O P id**, { (, ; }
9.  **O → . int**, { *, &, id }
10. **O → . char**, { *, &, id }
11. **O → . long**, { *, &, id }
12. **O → . float**, { *, &, id }
13. **O → . double**, { *, &, id }
14. **O → . string**, { *, &, id }
15. **O → . void**, { *, &, id }
16. **O → . id**, { *, &, id }

---

### Estado I1:
*GOTO(0, int)*
1.  **O → int •**, { *, &, id }

---

### Estado I2:
*GOTO(0, char)*
1.  **O → char •**, { *, &, id }

---

### Estado I3:
*GOTO(0, long)*
1.  **O → long •**, { *, &, id }

---

### Estado I4:
*GOTO(0, float)*
1.  **O → float •**, { *, &, id }

---

### Estado I5:
*GOTO(0, double)*
1.  **O → double •**, { *, &, id }

---

### Estado I6:
*GOTO(0, string)*
1.  **O → string •**, { *, &, id }

---

### Estado I7:
*GOTO(0, void)*
1.  **O → void •**, { *, &, id }

---

### Estado I8:
*GOTO(0, id)*
1.  **O → id •**, { *, &, id }

---

### Estado I9:
*GOTO(0, O)*
1.  **E → O • P id**, { (, ; }
2.  **P → •***, { id }
3.  **P → •&**, { id }
4.  **P → •ε**, { id, (, ; }

---

### Estado I10:
*GOTO(9, \**)*
1.  **P → * •**, { id }

---

### Estado I11:
*GOTO(9, &)*
1.  **P → & •**, { id }

---

### Estado I12:
*GOTO(9, P)*
1.  **E → O P • id**, { (, ; }

---

### Estado I13:
*GOTO(12, id)*
1.  **E → O P id •**, { (, ; }

---

### Estado I14:
*GOTO(0, class)*
1.  **D → class • id J { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I15:
*GOTO(14, id)*
1.  **D → class id • J { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }
2.  **J → . : K**, { { }
3.  **J → . ε**, { { }

---

### Estado I16:
*GOTO(15, J)*
1.  **D → class id J . { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I17:
*GOTO(16, {)*
1.  **D → class id J { . } ;**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I18:
*GOTO(17, })*
1.  **D → class id J { } . ;**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I19:
*GOTO(18, ;)*
1.  **D → class id J { } ; •**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I20:
*GOTO(15, :)*
1.  **J → : • K**, { { }
2.  **K → • K , L**, { { }
3.  **K → • L**, { { }
4.  **L → • M id**, { { }
5.  **L → • id**, { { }
6.  **M → • public**, { id }
7.  **M → • private**, { id }
8.  **M → • protected**, { id }

---

### Estado I21:
*GOTO(20, public)*
1.  **M → public •**, { id }

---

### Estado I22:
*GOTO(20, private)*
1.  **M → private •**, { id }

---

### Estado I23:
*GOTO(20, protected)*
1.  **M → protected •**, { id }

---

### Estado I24:
*GOTO(20, id)*
1.  **L → id •**, { { }

---

### Estado I25:
*GOTO(20, M)*
1.  **L → M • id**, { { }

---

### Estado I26:
*GOTO(25, id)*
1.  **L → M id •**, { { }

---

### Estado I27:
*GOTO(20, K)*
1.  **J → : K •**, { { }
2.  **K → K . , L**, { { }

---

### Estado I28:
*GOTO(20, L)*
1.  **K → L •**, { { }

---

### Estado I29:
*GOTO(27, ,)*
1.  **K → K , . L**, { { }
2.  **L → . M id**, { { }
3.  **L → . id**, { { }
4.  **M → . public**, { id }
5.  **M → . private**, { id }
6.  **M → . protected**, { id }

---

### Estado I30:
*GOTO(29, L)*
1.  **K → K , L •**, { { }

---

### Estado I31:
*GOTO(0, E)*
1.  **B → E . F**, { class, int, char, long, float, double, string, void, id, (, $ }
2.  **F → . ( G ) { }**, { class, int, char, long, float, double, string, void, id, (, $ }
3.  **F → . ;**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I32:
*GOTO(31, ( )*
1.  **F → ( . G ) { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }
2.  **G → . N**, { ) }
3.  **G → . ε**, { ) }
4.  **N → . N, E**, { ) }
5.  **N → . E**, { ) }
6.  **E → . O P id**, { ) }
7.  **O → . int**, { *, &, id }
8.  **O → . char**, { *, &, id }
9.  **O → . long**, { *, &, id }
10. **O → . float**, { *, &, id }
11. **O → . double**, { *, &, id }
12. **O → . string**, { *, &, id }
13. **O → . void**, { *, &, id }
14. **O → . id**, { *, &, id }

---

### Estado I33:
*GOTO(31, ;)*
1.  **F → ; •**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I34:
*GOTO(31, F)*
1.  **B → E F •**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I35:
*GOTO(32, N)*
1.  **G → N •**, { ) }
2.  **N → N . , E**, { ) }

---

### Estado I36:
*GOTO(32, E)*
1.  **N → E •**, { ) }

---

### Estado I37:
*GOTO(32, G)*
1.  **F → ( G . ) { }**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I38:
*GOTO(32, O)*
1.  **E → O . P id**, { ) }
2.  **P → .***, { id }
3.  **P → .&**, { id }
4.  **P → .ε**, { id, ) }

---

### Estado I39:
*GOTO(35, ,)*
1.  **N → N , . E**, { ) }
2.  **E → . O P id**, { ) }
3.  **O → . int**, { *, &, id }
4.  **O → . char**, { *, &, id }
5.  **O → . long**, { *, &, id }
6.  **O → . float**, { *, &, id }
7.  **O → . double**, { *, &, id }
8.  **O → . string**, { *, &, id }
9.  **O → . void**, { *, &, id }
10. **O → . id**, { *, &, id }

---

### Estado I40:
*GOTO(39, E)*
1.  **N → N , E •**, { ) }

---

### Estado I41:
*GOTO(37, ) )*
1.  **F → ( G ) • { }**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I42:
*GOTO(41, {)*
1.  **F → ( G ) { • }**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I43:
*GOTO(42, })*
1.  **F → ( G ) { } •**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I44:
*GOTO(38, P)*
1.  **E → O P . id**, { ) }

---

### Estado I45:
*GOTO(44, id)*
1.  **E → O P id •**, { ) }

---

### Estado I46:
*GOTO(0, B)*
1.  **C → B . C**, { $ }
2.  **C → . B C**, { $ }
3.  **C → . ε**, { $ }
4.  **B → . D**, { class, int, char, long, float, double, string, void, id, (, $ }
5.  **B → . E F**, { class, int, char, long, float, double, string, void, id, (, $ }
6.  **D → . class id J { } ;**, { class, int, char, long, float, double, string, void, id, (, $ }
7.  **E → . O P id**, { (, ; }
8.  **O → . int**, { *, &, id }
9.  **O → . char**, { *, &, id }
10. **O → . long**, { *, &, id }
11. **O → . float**, { *, &, id }
12. **O → . double**, { *, &, id }
13. **O → . string**, { *, &, id }
14. **O → . void**, { *, &, id }
15. **O → . id**, { *, &, id }

---

### Estado I47:
*GOTO(46, C)*
1.  **C → B C •**, { $ }

---

### Estado I48:
*GOTO(0, D)*
1.  **B → D •**, { class, int, char, long, float, double, string, void, id, (, $ }

---

### Estado I49:
*GOTO(0, A)*
1.  **A’ → A •**, { $ }

---

### Estado I50:
*GOTO(0, C)*
1.  **A → C •**, { $ }

---
## Tabla de Análisis Sintáctico LR(1) - Acciones y GOTO

Aquí tienes la tabla de análisis sintáctico LR(1) que incluye las acciones (Shift, Reduce, Accept) y las transiciones GOTO para cada estado.

---

### Estado I0
**ACTION:**
* **class**: S14
* **int**: S1
* **char**: S2
* **long**: S3
* **float**: S4
* **double**: S5
* **string**: S6
* **void**: S7
* **id**: S8
* **(**: S32

**GOTO:**
* **A**: 49
* **C**: 50
* **B**: 46
* **D**: 48
* **E**: 31
* **O**: 9

---

### Estado I1
**ACTION:**
* **\***: R9 (Reducir por `O → int`)
* **&**: R9 (Reducir por `O → int`)
* **id**: R9 (Reducir por `O → int`)
* **)**: R9 (Reducir por `O → int`)
* **,**: R9 (Reducir por `O → int`)
* **;**: R9 (Reducir por `O → int`)
* **class**: R9 (Reducir por `O → int`)
* **int**: R9 (Reducir por `O → int`)
* **char**: R9 (Reducir por `O → int`)
* **long**: R9 (Reducir por `O → int`)
* **float**: R9 (Reducir por `O → int`)
* **double**: R9 (Reducir por `O → int`)
* **string**: R9 (Reducir por `O → int`)
* **void**: R9 (Reducir por `O → int`)
* **(**: R9 (Reducir por `O → int`)
* **$**: R9 (Reducir por `O → int`)

---

### Estado I2
**ACTION:**
* **\***: R10 (Reducir por `O → char`)
* **&**: R10 (Reducir por `O → char`)
* **id**: R10 (Reducir por `O → char`)
* **)**: R10 (Reducir por `O → char`)
* **,**: R10 (Reducir por `O → char`)
* **;**: R10 (Reducir por `O → char`)
* **class**: R10 (Reducir por `O → char`)
* **int**: R10 (Reducir por `O → char`)
* **char**: R10 (Reducir por `O → char`)
* **long**: R10 (Reducir por `O → char`)
* **float**: R10 (Reducir por `O → char`)
* **double**: R10 (Reducir por `O → char`)
* **string**: R10 (Reducir por `O → char`)
* **void**: R10 (Reducir por `O → char`)
* **(**: R10 (Reducir por `O → char`)
* **$**: R10 (Reducir por `O → char`)

---

### Estado I3
**ACTION:**
* **\***: R11 (Reducir por `O → long`)
* **&**: R11 (Reducir por `O → long`)
* **id**: R11 (Reducir por `O → long`)
* **)**: R11 (Reducir por `O → long`)
* **,**: R11 (Reducir por `O → long`)
* **;**: R11 (Reducir por `O → long`)
* **class**: R11 (Reducir por `O → long`)
* **int**: R11 (Reducir por `O → long`)
* **char**: R11 (Reducir por `O → long`)
* **long**: R11 (Reducir por `O → long`)
* **float**: R11 (Reducir por `O → long`)
* **double**: R11 (Reducir por `O → long`)
* **string**: R11 (Reducir por `O → long`)
* **void**: R11 (Reducir por `O → long`)
* **(**: R11 (Reducir por `O → long`)
* **$**: R11 (Reducir por `O → long`)

---

### Estado I4
**ACTION:**
* **\***: R12 (Reducir por `O → float`)
* **&**: R12 (Reducir por `O → float`)
* **id**: R12 (Reducir por `O → float`)
* **)**: R12 (Reducir por `O → float`)
* **,**: R12 (Reducir por `O → float`)
* **;**: R12 (Reducir por `O → float`)
* **class**: R12 (Reducir por `O → float`)
* **int**: R12 (Reducir por `O → float`)
* **char**: R12 (Reducir por `O → float`)
* **long**: R12 (Reducir por `O → float`)
* **float**: R12 (Reducir por `O → float`)
* **double**: R12 (Reducir por `O → float`)
* **string**: R12 (Reducir por `O → float`)
* **void**: R12 (Reducir por `O → float`)
* **(**: R12 (Reducir por `O → float`)
* **$**: R12 (Reducir por `O → float`)

---

### Estado I5
**ACTION:**
* **\***: R13 (Reducir por `O → double`)
* **&**: R13 (Reducir por `O → double`)
* **id**: R13 (Reducir por `O → double`)
* **)**: R13 (Reducir por `O → double`)
* **,**: R13 (Reducir por `O → double`)
* **;**: R13 (Reducir por `O → double`)
* **class**: R13 (Reducir por `O → double`)
* **int**: R13 (Reducir por `O → double`)
* **char**: R13 (Reducir por `O → double`)
* **long**: R13 (Reducir por `O → double`)
* **float**: R13 (Reducir por `O → double`)
* **double**: R13 (Reducir por `O → double`)
* **string**: R13 (Reducir por `O → double`)
* **void**: R13 (Reducir por `O → double`)
* **(**: R13 (Reducir por `O → double`)
* **$**: R13 (Reducir por `O → double`)

---

### Estado I6
**ACTION:**
* **\***: R14 (Reducir por `O → string`)
* **&**: R14 (Reducir por `O → string`)
* **id**: R14 (Reducir por `O → string`)
* **)**: R14 (Reducir por `O → string`)
* **,**: R14 (Reducir por `O → string`)
* **;**: R14 (Reducir por `O → string`)
* **class**: R14 (Reducir por `O → string`)
* **int**: R14 (Reducir por `O → string`)
* **char**: R14 (Reducir por `O → string`)
* **long**: R14 (Reducir por `O → string`)
* **float**: R14 (Reducir por `O → string`)
* **double**: R14 (Reducir por `O → string`)
* **string**: R14 (Reducir por `O → string`)
* **void**: R14 (Reducir por `O → string`)
* **(**: R14 (Reducir por `O → string`)
* **$**: R14 (Reducir por `O → string`)

---

### Estado I7
**ACTION:**
* **\***: R15 (Reducir por `O → void`)
* **&**: R15 (Reducir por `O → void`)
* **id**: R15 (Reducir por `O → void`)
* **)**: R15 (Reducir por `O → void`)
* **,**: R15 (Reducir por `O → void`)
* **;**: R15 (Reducir por `O → void`)
* **class**: R15 (Reducir por `O → void`)
* **int**: R15 (Reducir por `O → void`)
* **char**: R15 (Reducir por `O → void`)
* **long**: R15 (Reducir por `O → void`)
* **float**: R15 (Reducir por `O → void`)
* **double**: R15 (Reducir por `O → void`)
* **string**: R15 (Reducir por `O → void`)
* **void**: R15 (Reducir por `O → void`)
* **(**: R15 (Reducir por `O → void`)
* **$**: R15 (Reducir por `O → void`)

---

### Estado I8
**ACTION:**
* **\***: R16 (Reducir por `O → id`)
* **&**: R16 (Reducir por `O → id`)
* **id**: R16 (Reducir por `O → id`)
* **)**: R16 (Reducir por `O → id`)
* **,**: R16 (Reducir por `O → id`)
* **;**: R16 (Reducir por `O → id`)
* **class**: R16 (Reducir por `O → id`)
* **int**: R16 (Reducir por `O → id`)
* **char**: R16 (Reducir por `O → id`)
* **long**: R16 (Reducir por `O → id`)
* **float**: R16 (Reducir por `O → id`)
* **double**: R16 (Reducir por `O → id`)
* **string**: R16 (Reducir por `O → id`)
* **void**: R16 (Reducir por `O → id`)
* **(**: R16 (Reducir por `O → id`)
* **$**: R16 (Reducir por `O → id`)

---

### Estado I9
**ACTION:**
* **\***: S10
* **&**: S11
* **id**: S13 (Shift/Reduce conflict for R19, resolving to Shift)
* **(**: S13 (Shift/Reduce conflict for R19, resolving to Shift)
* **;**: S13 (Shift/Reduce conflict for R19, resolving to Shift)

**GOTO:**
* **P**: 12

---

### Estado I10
**ACTION:**
* **id**: R17 (Reducir por `P → *`)

---

### Estado I11
**ACTION:**
* **id**: R18 (Reducir por `P → &`)

---

### Estado I12
**ACTION:**
* **id**: S13

---

### Estado I13
**ACTION:**
* **(**: R8 (Reducir por `E → O P id`)
* **;**: R8 (Reducir por `E → O P id`)
* **class**: R8 (Reducir por `E → O P id`)
* **int**: R8 (Reducir por `E → O P id`)
* **char**: R8 (Reducir por `E → O P id`)
* **long**: R8 (Reducir por `E → O P id`)
* **float**: R8 (Reducir por `E → O P id`)
* **double**: R8 (Reducir por `E → O P id`)
* **string**: R8 (Reducir por `E → O P id`)
* **void**: R8 (Reducir por `E → O P id`)
* **id**: R8 (Reducir por `E → O P id`)
* **$**: R8 (Reducir por `E → O P id`)

---

### Estado I14
**ACTION:**
* **id**: S15

---

### Estado I15
**ACTION:**
* **{**: R21 (Reducir por `J → ε`)
* **:**: S20

**GOTO:**
* **J**: 16

---

### Estado I16
**ACTION:**
* **{**: S17

---

### Estado I17
**ACTION:**
* **}**: S18

---

### Estado I18
**ACTION:**
* **;**: S19

---

### Estado I19
**ACTION:**
* **class**: R7 (Reducir por `D → class id J { } ;`)
* **int**: R7 (Reducir por `D → class id J { } ;`)
* **char**: R7 (Reducir por `D → class id J { } ;`)
* **long**: R7 (Reducir por `D → class id J { } ;`)
* **float**: R7 (Reducir por `D → class id J { } ;`)
* **double**: R7 (Reducir por `D → class id J { } ;`)
* **string**: R7 (Reducir por `D → class id J { } ;`)
* **void**: R7 (Reducir por `D → class id J { } ;`)
* **id**: R7 (Reducir por `D → class id J { } ;`)
* **(**: R7 (Reducir por `D → class id J { } ;`)
* **$**: R7 (Reducir por `D → class id J { } ;`)

---

### Estado I20
**ACTION:**
* **public**: S21
* **private**: S22
* **protected**: S23
* **id**: S24

**GOTO:**
* **K**: 27
* **L**: 28
* **M**: 25

---

### Estado I21
**ACTION:**
* **id**: R26 (Reducir por `M → public`)

---

### Estado I22
**ACTION:**
* **id**: R27 (Reducir por `M → private`)

---

### Estado I23
**ACTION:**
* **id**: R28 (Reducir por `M → protected`)

---

### Estado I24
**ACTION:**
* **{**: R25 (Reducir por `L → id`)
* **,**: R25 (Reducir por `L → id`)

---

### Estado I25
**ACTION:**
* **id**: S26

---

### Estado I26
**ACTION:**
* **{**: R24 (Reducir por `L → M id`)
* **,**: R24 (Reducir por `L → M id`)

---

### Estado I27
**ACTION:**
* **{**: R20 (Reducir por `J → : K`)
* **,**: S29

---

### Estado I28
**ACTION:**
* **{**: R23 (Reducir por `K → L`)
* **,**: R23 (Reducir por `K → L`)

---

### Estado I29
**ACTION:**
* **public**: S21
* **private**: S22
* **protected**: S23
* **id**: S24

**GOTO:**
* **L**: 30
* **M**: 25

---

### Estado I30
**ACTION:**
* **{**: R22 (Reducir por `K → K , L`)

---

### Estado I31
**ACTION:**
* **(**: S32
* **;**: S33

**GOTO:**
* **F**: 34

---

### Estado I32
**ACTION:**
* **int**: S1
* **char**: S2
* **long**: S3
* **float**: S4
* **double**: S5
* **string**: S6
* **void**: S7
* **id**: S8
* **)**: R30 (Reducir por `G → ε`)

**GOTO:**
* **G**: 37
* **N**: 35
* **E**: 36
* **O**: 38

---

### Estado I33
**ACTION:**
* **class**: R34 (Reducir por `F → ;`)
* **int**: R34 (Reducir por `F → ;`)
* **char**: R34 (Reducir por `F → ;`)
* **long**: R34 (Reducir por `F → ;`)
* **float**: R34 (Reducir por `F → ;`)
* **double**: R34 (Reducir por `F → ;`)
* **string**: R34 (Reducir por `F → ;`)
* **void**: R34 (Reducir por `F → ;`)
* **id**: R34 (Reducir por `F → ;`)
* **(**: R34 (Reducir por `F → ;`)
* **$**: R34 (Reducir por `F → ;`)

---

### Estado I34
**ACTION:**
* **class**: R6 (Reducir por `B → E F`)
* **int**: R6 (Reducir por `B → E F`)
* **char**: R6 (Reducir por `B → E F`)
* **long**: R6 (Reducir por `B → E F`)
* **float**: R6 (Reducir por `B → E F`)
* **double**: R6 (Reducir por `B → E F`)
* **string**: R6 (Reducir por `B → E F`)
* **void**: R6 (Reducir por `B → E F`)
* **id**: R6 (Reducir por `B → E F`)
* **(**: R6 (Reducir por `B → E F`)
* **$**: R6 (Reducir por `B → E F`)

---

### Estado I35
**ACTION:**
* **)**: R29 (Reducir por `G → N`)
* **,**: S39

---

### Estado I36
**ACTION:**
* **)**: R32 (Reducir por `N → E`)

---

### Estado I37
**ACTION:**
* **)**: S41

---

### Estado I38
**ACTION:**
* **\***: S10 (Redirección a I10)
* **&**: S11 (Redirección a I11)
* **id**: S45 (Shift/Reduce conflict for R19, resolving to Shift)
* **)**: R19 (Reducir por `P → ε`)

---

### Estado I39
**ACTION:**
* **int**: S1 (Redirección a I1)
* **char**: S2 (Redirección a I2)
* **long**: S3 (Redirección a I3)
* **float**: S4 (Redirección a I4)
* **double**: S5 (Redirección a I5)
* **string**: S6 (Redirección a I6)
* **void**: S7 (Redirección a I7)
* **id**: S8 (Redirección a I8)

**GOTO:**
* **E**: 40
* **O**: 38 (Redirección a I38)

---

### Estado I40
**ACTION:**
* **)**: R31 (Reducir por `N → N , E`)

---

### Estado I41
**ACTION:**
* **{**: S42

---

### Estado I42
**ACTION:**
* **}**: S43

---

### Estado I43
**ACTION:**
* **class**: R33 (Reducir por `F → ( G ) { } ;`)
* **int**: R33 (Reducir por `F → ( G ) { } ;`)
* **char**: R33 (Reducir por `F → ( G ) { } ;`)
* **long**: R33 (Reducir por `F → ( G ) { } ;`)
* **float**: R33 (Reducir por `F → ( G ) { } ;`)
* **double**: R33 (Reducir por `F → ( G ) { } ;`)
* **string**: R33 (Reducir por `F → ( G ) { } ;`)
* **void**: R33 (Reducir por `F → ( G ) { } ;`)
* **id**: R33 (Reducir por `F → ( G ) { } ;`)
* **(**: R33 (Reducir por `F → ( G ) { } ;`)
* **$**: R33 (Reducir por `F → ( G ) { } ;`)

---

### Estado I44
**ACTION:**
* **id**: S45
* **)**: R8 (Reducir por `E → O P id`)

---

### Estado I45
**ACTION:**
* **)**: R8 (Reducir por `E → O P id`)

---

### Estado I46
**ACTION:**
* **class**: S14 (Redirección a I14)
* **int**: S1 (Redirección a I1)
* **char**: S2 (Redirección a I2)
* **long**: S3 (Redirección a I3)
* **float**: S4 (Redirección a I4)
* **double**: S5 (Redirección a I5)
* **string**: S6 (Redirección a I6)
* **void**: S7 (Redirección a I7)
* **id**: S8 (Redirección a I8)
* **(**: S32 (Redirección a I32)
* **$**: R4 (Reducir por `C → ε`)

**GOTO:**
* **C**: 47
* **B**: 46 (Autorreferencia)
* **D**: 48 (Redirección a I48)
* **E**: 31 (Redirección a I31)
* **O**: 9 (Redirección a I9)

---

### Estado I47
**ACTION:**
* **$**: R3 (Reducir por `C → B C`)

---

### Estado I48
**ACTION:**
* **class**: R5 (Reducir por `B → D`)
* **int**: R5 (Reducir por `B → D`)
* **char**: R5 (Reducir por `B → D`)
* **long**: R5 (Reducir por `B → D`)
* **float**: R5 (Reducir por `B → D`)
* **double**: R5 (Reducir por `B → D`)
* **string**: R5 (Reducir por `B → D`)
* **void**: R5 (Reducir por `B → D`)
* **id**: R5 (Reducir por `B → D`)
* **(**: R5 (Reducir por `B → D`)
* **$**: R5 (Reducir por `B → D`)

---

### Estado I49
**ACTION:**
* **$**: **acc** (Aceptar)

---

### Estado I50
**ACTION:**
* **$**: R2 (Reducir por `A → C`)