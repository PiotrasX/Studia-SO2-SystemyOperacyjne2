section .data
         childMessage db 'Proces potomny', 10, 0       ; Wiadomoœæ dla procesu potomnego z now¹ lini¹ i koñcem stringa na koñcu
         childMsgLen equ $ - childMessage              ; D³ugoœæ wiadomoœci procesu potomnego
         parentMessage db 'Proces macierzysty', 10, 0  ; Wiadomoœæ dla procesu macierzystego z now¹ lini¹ i koñcem stringa na koñcu
         parentMsgLen equ $ - parentMessage            ; D³ugoœæ wiadomoœci procesu macierzystego

section .text
         global _start

_start:
         ; syscall vfork
         mov rax, 58  ; Numer syscall dla vfork
         syscall      ; Wywo³anie syscall

         ; Sprawdzenie, czy proces jest rodzicem czy dzieckiem
         test rax, rax     ; Sprawdzenie wartoœci w rejestrze rax
         jz child_process  ; Jeœli rax == 0, to jest obecnie proces potomny, w przeciwnym wypadku, jest obecnie proces macierzysty

parent_process:
         ; Wyœwietlanie komunikatu dla procesu macierzystego
         mov rax, 1              ; Numer syscall dla write
         mov rdi, 1              ; Deskryptor pliku (STDOUT)
         mov rsi, parentMessage  ; WskaŸnik na wiadomoœæ
         mov rdx, parentMsgLen   ; D³ugoœæ wiadomoœci
         syscall                 ; Wywo³anie syscall write

         ; syscall exit(0)
         mov rax, 60   ; Numer syscall dla exit
         xor rdi, rdi  ; Kod powrotu 0
         syscall       ; Wywo³anie syscall exit

child_process:
         ; Wyœwietlanie komunikatu dla procesu potomnego
         mov rax, 1             ; Numer syscall dla write
         mov rdi, 1             ; Deskryptor pliku (STDOUT)
         mov rsi, childMessage  ; WskaŸnik na wiadomoœæ
         mov rdx, childMsgLen   ; D³ugoœæ wiadomoœci
         syscall                ; Wywo³anie syscall write

         ; syscall exit(1)
         mov rax, 60  ; Numer syscall dla exit
         mov rdi, 1   ; Kod powrotu 1
         syscall      ; Wywo³anie syscall exit
