# Nom de l'exécutable à générer
EXECUTABLE := projet

# Compilateur C++
CC := g++

# Options de compilation
CFLAGS := -Wall -std=c++11

# Détection automatique de tous les fichiers .cpp
SOURCES := $(wildcard *.cpp)

# Convertir les .cpp en .o pour la liaison
OBJECTS := $(SOURCES:.cpp=.o)

# Lien de l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compilation des objets
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Commande par défaut
all: $(EXECUTABLE)

.PHONY: all clean
