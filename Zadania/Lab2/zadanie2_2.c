#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Zadanie 1.4.1

float a1(int n) {
	if (n == 0) return 1;
	if (n == 1) return 4;
	
	return 2 * a1(n - 1) + 0.5 * a1(n - 2);
}

    /*
    - Dokonaj analizy wywołania a1(4).

    * a1_1(4) = 42.25
      4 == 0   false
      4 == 1   false
    
      return 2 * a1_2(3) + 0.5 * a1_?(2) = 2 * 19 + 0.5 * a1_7(2) = 38 + 0.5 * a1_7(2) = 38 + 0.5 * 8.5 = 38 + 4.25 = 42.25
    
    * a1_2(3) = 19
      3 == 0   false
      3 == 1   false
    
      return 2 * a1_3(2) + 0.5 * a1_?(1) = 2 * 8.5 + 0.5 a1_6(1) = 17 + 0.5 a1_6(1) = 17 + 0.5 * 4 = 17 + 2 = 19
    
    * a1_3(2) = 8.5
      2 == 0   false
      2 == 1   false
    
      return 2 * a1_4(1) + 0.5 * a1_?(0) = 2 * 4 + 0.5 * a1_5(0) = 8 + 0.5 * a1_5(0) = 8 + 0.5 * 1 = 8 + 0.5 = 8.5
    
    * a1_4(1) = 4
      1 == 0   false
      1 == 1   true
    
      return 4   

    * a1_5(0) = 1 
      0 == 0   true
    
      return 1
    
    * a1_6(1) = 4
      1 == 0   false
      1 == 1   true
    
      return 4 
    
    * a1_7(2) = 8.5
      2 == 0   false
      2 == 1   false
    
      return 2 * a1_8(1) + 0.5 * a1_?(0) = 2 * 4 + 0.5 * a1_9(0) = 8 + 0.5 * a1_9(0) = 8 + 0.5 * 1 = 8 + 0.5 = 8.5

    * a1_8(1) = 4
      1 == 0   false
      1 == 1   true
    
      return 4
    
    * a1_9(0) = 1 
      0 == 0   true

      return 1



    - Narysuj drzewo wywołań dla a1(4).

      a1_1(4) = 42.25
      a1_2(3) = 19
      a1_3(2) = 8.5
      a1_4(1) = 4
      a1_5(0) = 1
      a1_6(1) = 4
      a1_7(2) = 8.5
      a1_8(1) = 4
      a1_9(0) = 1
    */

// Koniec zadania 1.4.1



// Zadanie 2.2.1

float a2(int n) {
    float r0 = 1;
	float r1 = 4;
	float r2 = 2 * r1 + 0.5 * r0;
  
	if (n == 0) return r0;
	if (n == 1) return r1;
	if (n == 2) return r2;

    int i;
	for (i = 1; i <= n - 2; i++) {
		r0 = r1;
		r1 = r2;
		r2 = 2 * r1 + 0.5 * r0;
	}
	
	return r2;
}

    /*
    - Narysuj schemat dla ramki trójzębnej analogicznie jak dla ciągu Fibonacciego.

      r0  r1  r2
      |---|---|       
      0   1   2   3   4   5   6    indeksy
      1   4   x   x   x   x   x    wartości
          |---|---|
          r0  r1  r2



    - Dokonaj analizy wywołania a2(4).

    * a2(4) = 
      r0 = 1
      r1 = 4
      r2 = 2 * 4 + 0.5 * 1 = 8 + 0.5 = 8.5
    
      n = 4
      4 == 0   false
      4 == 1   false
      4 == 2   false
    
      i
      i = 1
      1 <= 2   r0 = r1 = 4
               r1 = r2 = 8.5
               r2 = 2 * r1 + 0.5 r0 = 2 * 8.5 + 0.5 * 4 = 17 + 2 = 19   i = 2
            
      2 <= 2   r0 = r1 = 8.5
               r1 = r2 = 19
               r2 = 2 * r1 + 0.5 r0 = 2 * 19 + 0.5 * 8.5 = 38 + 4.25 = 42.25   i = 3
            
      3 <= 2   false
    
      return r2 = 42.25
    
    
    
    - Narysuj graf obliczeń dla a2(4).

      a(0)    a(1)    a(2)
                 \   /  |
                  a(3)  |
                     \  |
                      a(4)
    */

// Koniec zadania 2.2.1



// Zadanie 2.2.2

float a3(int n) {
	float r0 = 1;
	float r1 = 4;
	
	if (n == 0) return r0;
	if (n == 1) return r1;
	
	int i; 
    float pom;
	for (i = 1; i <= n - 1; i++) {
		pom = r0;
		r0 = r1;
		r1 = 2 * r0 + 0.5 * pom;
	}
	
	return r1;
}

    /*
    - Narysuj schemat dla ramki dwuzębnej analogicznie jak dla ciągu Fibonacciego.
      r0  r1
      |---|      
      0   1   2   3   4   5   6    indeksy
      1   4   x   x   x   x   x    wartości
      |   |---|
      pom r0  r1



    - Dokonaj analizy wywołania a3(4).

    * a3(4) = 
      r0 = 1
      r1 = 4
    
      n = 4
      4 == 0   false
      4 == 1   false
    
      i, pom
      i = 1
      1 <= 3   pom = r0 = 1
               r0  = r1 = 4
               r1  = 2 * r0 + 0.5 * pom = 2 * 4 + 0.5 * 1 = 8 + 0.5 = 8.5   i = 2
            
      2 <= 3   pom = r0 = 4
               r0  = r1 = 8.5
               r1  = 2 * r0 + 0.5 * pom = 2 * 8.5 + 0.5 * 4 = 17 + 2 = 19   i = 3
            
      3 <= 3   pom = r0 = 8.5
               r0  = r1 = 19
               r1  = 2 * r0 + 0.5 * pom = 2 * 19 + 0.5 * 8.5 = 38 + 4.25 = 42.25   i = 4
            
      4 <= 3   false
    
      return r1 = 42.25
    
    
    
    - Narysuj graf obliczeń dla a3(4).

      a(0)    a(1)
         \   /  |
          a(2)  |
          |  \  |
          |   a(3)
          |  /
          a(4)
    */

// Koniec zadania 2.2.2



int main() {
    int n = 4;

    printf("\na1(%d) = %f", n, a1(n));
    printf("\na2(%d) = %f", n, a2(n));
    printf("\na3(%d) = %f\n\n", n, a3(n));

    return 0;
}
