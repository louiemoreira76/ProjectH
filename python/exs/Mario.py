tam = int(input("Qual o tamanho da pirâmide que você deseja (de 1 a 8): "))

while tam < 1 or tam > 8:
    tam = int(input("Insira novamente, pode ser de 1 a 8: "))

for i in range(tam):    

    for j in range(tam - i - 1):
        print(" ", end="")
    
    for j in range(i + 1):
        print("#", end="")
    
    print("")
