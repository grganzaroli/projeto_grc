import os
from pathlib import Path


# --------------------------- DEFINICAO DE FUNCOES ---------------------------

def cls():
    os.system('cls' if os.name == 'nt' else 'clear')


def ber_meter(filename1, filename2):

    if Path(filename2).is_file():
        file1 = open(filename1, 'rb')
        file2 = open(filename2, 'rb')

        file1_size = int(os.path.getsize(filename1))
        file2_size = int(os.path.getsize(filename2))

        error = 0

    # if file1_size != file2_size:
    #    print(filename1 + ' E ' + filename2 + ' POSSUEM TAMANHOS DIFERENTES\n')
    #    return -1
    # else:

        pcnt = file2_size/100
        count = 0
        for x in range(0, file2_size, 1):
            by1 = ord(file1.read(1))
            by2 = ord(file2.read(1))

            xor_result = by1 ^ by2

            if xor_result != 0:
                for y in range(8):
                    error += xor_result & 1
                    xor_result >>= 1

            if x > pcnt:
                pcnt += file2_size/100
                count += 1
                print(str(count) + " %")

        print("\nNumero de erros = " + str(error))
        print("Total de bits = " + str(file2_size))

        print('\n' + filename2 + ' OK\n')
        return error
    # fim do else

    else:
        print(filename1 + ' NAO EXISTE!\n')
        return -2


def main(base_file, tested_file):
    file_errors = []

    for file in tested_file:
        print('Processando ' + file + '...\n')

        error = ber_meter(base_file, file)
        if error != -2:
            tested_file_size = int(os.path.getsize(file))*8

        file_errors.append(error)

    cls()

    print('ARQUIVOS PROCESSADOS:')

    results_files = open("ber_results_"+base_file.split('.')[0]+'.txt', 'w')

    for x in range(tested_file.__len__()):
        if file_errors[x] >= 0:
            print("\nNumero de erros = " + str(file_errors[x]))
            results_files.write("Numero de erros = " + str(file_errors[x])+'\n')

            print("Total de bits = " + str(tested_file_size))
            results_files.write("Total de bits = " + str(tested_file_size)+'\n')

            if file_errors[x] > 0:
                print('BER = ' + str(file_errors[x]/tested_file_size))
                results_files.write('BER = ' + str(file_errors[x]/tested_file_size)+'\n')

            else:
                print('BER = 0')
                results_files.write('BER = 0\n')

            print('Calculado entre ' + base_file + ' e ' + tested_file[x])
            results_files.write('Calculado entre ' + base_file + ' e ' + tested_file[x]+'\n\n')

        elif file_errors[x] == -1:
            print('\nERRO: ' + base_file + ' E ' + tested_file[x] + ' POSSUEM TAMANHOS DIFERENTES\n')
            results_files.write('ERRO: ' + base_file + ' E ' + tested_file[x] + ' POSSUEM TAMANHOS DIFERENTES\n\n')
        else:
            print('\nERRO: ' + tested_file[x] + ' NAO EXISTE!')
            results_files.write('ERRO: ' + tested_file[x] + ' NAO EXISTE!'+'\n\n')

    results_files.close()
    input("\nPress Enter to continue...")


# --------------------------- SCRIPT IRA RODAR DAQUI PARA BAIXO ---------------------------

base_file = 'PN.ts'
tested_file = ['PN_error_validation_1.bin',
               'PN_error_validation_2.bin',
               'PN_error_validation_3.bin',
               'PN_error_validation_4.bin',
               'PN_error_validation_5.bin',
               'PN_error_validation_6.bin',
               'PN_error_validation_7.bin',
               'PN_error_validation_8.bin',
               'PN_error_validation_9.bin',
               'PN_error_validation_10.bin',
               'PN_error_validation_11.bin',
               'PN_error_validation_12.bin',
               'PN_error_validation_13.bin',
               'PN_error_validation_14.bin',
               'PN_error_validation_15.bin']

main(base_file, tested_file)
