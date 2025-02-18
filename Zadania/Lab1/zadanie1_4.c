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



int main() {
    int n = 4;

    printf("\na1(%d) = %f\n\n", n, a1(n));

    return 0;
}
