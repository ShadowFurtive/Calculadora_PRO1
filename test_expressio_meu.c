// De POSTFIXA a POSTFIXA
a b a not or and 
a b or a b b and or and 
8 x != not x 8 == or 
18 
x 12 + 12 x + / 
b b and a or b a or and 
8 x == -1 x * 8 != not or 
0 
//
// De POSTFIXA a INFIXA
a and ( b or not a )
( a or b ) and ( a or b and b )
not 8 != x or x == 8
18
( x + 12 ) / ( 12 + x )
( b and b or a ) and ( b or a )
8 == x or not -1 * x != 8
0
//
// De INFIXA a POSTFIXA
a b a not or and 
a b a not or and 
a b or a b b and or and 
a b or a b b and or and 
18 
x 3 + 2 y * + 2 y * 3 + x + - 
x 3 + 2 y * + 2 y * 3 x + + - 
x 12 + 12 x + / 
//
// De INFIXA a INFIXA
a and ( b or not a )
a and ( b or not a )
( a or b ) and ( a or b and b )
( a or b ) and ( a or b and b )
18
x + 3 + 2 * y - 2 * y + 3 + x
x + 3 + 2 * y - 2 * y + 3 + x
( x + 12 ) / ( 12 + x )
//
// Llista d'OPERANDS
a b 
a b a b b 
8 x 0 x 8 
18 
x 12 12 x 
b b a b a 
8 x -1 x 8 0 
0 
x 3 2 y 2 y 3 x 
//
// EXPANDEIX llegeix un token i una 2a expressió,
// canvia els tokens de la 1a expressió per la 2a expressió
// i l'expressió resultant l'avalua i la mostra infixa
T
not 8 != y or y == 8
not 8 != 2 + x or 2 + x == 8
1
( y + 12 ) / ( 12 + y )
( 2 * y + 12 ) / ( 12 + 2 * y )
T
8 == y or not -1 * y != 8
8 == 2 + y or not -1 * ( 2 + y ) != 8
4 + 2 * y - 2 * y + 3 + 1
y + 3 + 2 * y - 2 * y + 3 + y
x + 3 + 2 - 5 + x
x + 3 + 2 * x - 2 * x + 3 + x
x + 3 + 2 * ( 2 + y ) - 2 * ( 2 + y ) + 3 + x
