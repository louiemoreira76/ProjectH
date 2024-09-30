
while True:
    num = input("Digite seu numero de cartão de crédito: ") #STRING
    if num.isdigit() and len(num) in [13, 15, 16]:  
        break  
    else:
        print("Entrada inválida. Por favor, insira novamente.") #13 a 16 dígitos
cal = 0
last = str(num[-1])

for i in range(len(num) - 2, -1, -2):
    digito = int(num[i]) * 2

    cal += digito

cal = cal + int(last)

for i in range(len(num) -1, -1, -2): #ordem normal
    cal += i

zero = cal % 10 # Pega o último dígito usando módulo

if int(zero) != 0:
    print("Não é valido")

if len(num) == 15 and ((num[0] == '3' and num[1] == '4') or (num[0] == '3' and num[1] == '7')):
    print("American Express")
elif len(num) == 16 and ((num[0] == '5' and num[1] == '1') or (num[0] == '5' and num[1] == '2') or (num[0] == '5' and num[1] == '3') or (num[0] == '5' and num[1] == '4') or (num[0] == '5' and num[1] == '5')):
    print("MasterCard")
elif len(num) >= 13 and len(num) <= 16 and (num[0] == '4'):
    print("Visa")
else:
    print("INVALID")


# American Express usa números de 15   começam com 34 ou 37
#MasterCard usa números de 16 começa 1, 52, 53, 54 ou 55
#Visa usa números de 13 e 16 dígitos começam com 4.
#algoritmo inventado por Hans Peter Luhn, da IBM