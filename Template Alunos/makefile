# Flags de compilação para capturar warnings
parametrosCompilacao=-Wall -Wextra -Wshadow -Wconversion -Wsign-compare -Wpedantic -Wformat=2 -Wundef -Wnull-dereference -Wdouble-promotion -Wcast-align -Wstrict-overflow=5 -Wredundant-decls -Wunreachable-code -Wlogical-op -Winline


# Nome do programa final
nomePrograma=trab

# Alvo principal
all: $(nomePrograma)

# Compilar o programa final
$(nomePrograma): main.o ordenacao.o
	gcc -o $(nomePrograma) main.o ordenacao.o $(parametrosCompilacao)

# Compilar main.o com os warnings
main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

# Compilar ordenacao.o com os warnings
ordenacao.o: ordenacao.h ordenacao.c
	gcc -c ordenacao.c $(parametrosCompilacao)

# Limpar arquivos gerados
clean:
	rm -f *.o *.gch $(nomePrograma)
