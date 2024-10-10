# Nome do projeto
PROJ_NAME=arvores

# Arquivos .c
C_SOURCE=arvores.c  # Substitua 'arvores.c' pelo nome do seu arquivo principal

# Arquivos .h
H_SOURCE=arvores.h

# Arquivos objeto
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c     	\
     	-Wall  	\
     	-g     	\
     	-pedantic

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c $(H_SOURCE)
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm -rf *.o $(PROJ_NAME) *~
