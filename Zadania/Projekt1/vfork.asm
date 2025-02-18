section .data
         childMessage db 'Proces potomny', 10, 0       ; Wiadomo�� dla procesu potomnego z now� lini� i ko�cem stringa na ko�cu
         childMsgLen equ $ - childMessage              ; D�ugo�� wiadomo�ci procesu potomnego
         parentMessage db 'Proces macierzysty', 10, 0  ; Wiadomo�� dla procesu macierzystego z now� lini� i ko�cem stringa na ko�cu
         parentMsgLen equ $ - parentMessage            ; D�ugo�� wiadomo�ci procesu macierzystego

section .text
         global _start

_start:
         ; syscall vfork
         mov rax, 58  ; Numer syscall dla vfork
         syscall      ; Wywo�anie syscall

         ; Sprawdzenie, czy proces jest rodzicem czy dzieckiem
         test rax, rax     ; Sprawdzenie warto�ci w rejestrze rax
         jz child_process  ; Je�li rax == 0, to jest obecnie proces potomny, w przeciwnym wypadku, jest obecnie proces macierzysty

parent_process:
         ; Wy�wietlanie komunikatu dla procesu macierzystego
         mov rax, 1              ; Numer syscall dla write
         mov rdi, 1              ; Deskryptor pliku (STDOUT)
         mov rsi, parentMessage  ; Wska�nik na wiadomo��
         mov rdx, parentMsgLen   ; D�ugo�� wiadomo�ci
         syscall                 ; Wywo�anie syscall write

         ; syscall exit(0)
         mov rax, 60   ; Numer syscall dla exit
         xor rdi, rdi  ; Kod powrotu 0
         syscall       ; Wywo�anie syscall exit

child_process:
         ; Wy�wietlanie komunikatu dla procesu potomnego
         mov rax, 1             ; Numer syscall dla write
         mov rdi, 1             ; Deskryptor pliku (STDOUT)
         mov rsi, childMessage  ; Wska�nik na wiadomo��
         mov rdx, childMsgLen   ; D�ugo�� wiadomo�ci
         syscall                ; Wywo�anie syscall write

         ; syscall exit(1)
         mov rax, 60  ; Numer syscall dla exit
         mov rdi, 1   ; Kod powrotu 1
         syscall      ; Wywo�anie syscall exit
