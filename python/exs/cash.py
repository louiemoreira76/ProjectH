troco = float(input("Quanto dinheiro estamos lhe devendo: "))

while troco <= 0:
    troco = float(input("Numero invalido tente novamente: "))

moedas  = 0
centavos = int(round(troco * 100))

while centavos >= 25:

    centavos -= 25
    moedas+=1
    print(centavos)

while centavos >= 10:
    centavos -= 10
    moedas+=1
    print(centavos)

while centavos >= 5:
    centavos -= 5
    moedas+=1
    print(centavos)

while centavos >= 1:
    centavos -= 1
    moedas+=1
    print(centavos)

print("Número total de moedas: ", moedas)
