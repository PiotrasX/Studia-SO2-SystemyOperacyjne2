public class zadanie2_4 {
    public static void main(String[] args) {
        // Drzewo 1:
        //       ___A___
        //      /  / \  \
        //     B  C   D  f1
        //    / \  \
        //   D  f1  E
        
        String[][][] drzewo1 = new String[4][4][4]; 
        
        // Poziom 0 - katalog główny A
        drzewo1[0][0][0] = "A";
        
        // Poziom 1 - dzieci A
        drzewo1[1][0][0] = "B";
        drzewo1[1][1][0] = "C";
        drzewo1[1][2][0] = "D";
        drzewo1[1][3][0] = "f1";
        
        // Poziom 2 - dzieci B
        drzewo1[2][0][0] = "D";
        drzewo1[2][0][1] = "f1";
        
        // Poziom 2 - dzieci C
        drzewo1[2][1][0] = "E";


        
        // Drzewo 2:
        //        _____X_____
        //       /     |     \
        //      Y      Z      f1
        //     / \    / \
        //    X  f1  Z  f1
        
        String[][][] drzewo2 = new String[4][4][4];
        
        // Poziom 0 - katalog główny X
        drzewo2[0][0][0] = "X";
        
        // Poziom 1 - dzieci X
        drzewo2[1][0][0] = "Y";
        drzewo2[1][1][0] = "Z";
        drzewo2[1][2][0] = "f1";
        
        // Poziom 2 - dzieci Y
        drzewo2[2][0][0] = "X";
        drzewo2[2][0][1] = "f1";
        
        // Poziom 2 - dzieci Z
        drzewo2[2][1][0] = "Z";
        drzewo2[2][1][1] = "f1";
        


        // Testowanie: Wyświetl strukturę drzewa 1
        System.out.println("\nDrzewo 1:");
        wyswietlStrukture(drzewo1);
        
        // Testowanie: Wyświetl strukturę drzewa 2
        System.out.println("Drzewo 2:");
        wyswietlStrukture(drzewo2);
    }
    
    public static void wyswietlStrukture(String[][][] drzewo) {
        for (int i = 0; i < drzewo.length; i++) {
            for (int j = 0; j < drzewo[i].length; j++) {
                for (int k = 0; k < drzewo[i][j].length; k++) {
                    if (drzewo[i][j][k] != null) {
                        System.out.println("Poziom " + i + ", indeks [" + i + "][" + j + "][" + k + "] = " + drzewo[i][j][k]);
                    }
                }
            }
        }
        System.out.println();
    }
}
