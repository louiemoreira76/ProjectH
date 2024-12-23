import csv
import sys

def longest_match(sequence, subsequence):
    """Retorna a execução mais longa de repetições consecutivas de 'subsequence' em 'sequence'."""
    longest_run = 0
    subseq_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0
        while sequence[i + count * subseq_len : i + (count + 1) * subseq_len] == subsequence:
            count += 1
        longest_run = max(longest_run, count)

    return longest_run

def main():
    # Verifica o número de argumentos da linha de comando
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Lê os argumentos da linha de comando
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Lê o arquivo CSV na memória
    with open(database_file, mode='r') as csv_file:
        reader = csv.DictReader(csv_file)
        database = list(reader)

    # Lê o arquivo de sequência de DNA na memória
    with open(sequence_file, mode='r') as txt_file:
        sequence = txt_file.read().strip()

    # Obtém as STRs a partir do cabeçalho do CSV
    strs = reader.fieldnames[1:]  # Ignora a coluna "name"

    # Calcula o número máximo de repetições para cada STR na sequência de DNA
    str_counts = {str_: longest_match(sequence, str_) for str_ in strs}

    # Verifica se as contagens correspondem a algum indivíduo
    for person in database:
        if all(str_counts[str_] == int(person[str_]) for str_ in strs):
            print(person['name'])
            return

    # Se nenhuma correspondência for encontrada
    print("No match")

if __name__ == "__main__":
    main()
