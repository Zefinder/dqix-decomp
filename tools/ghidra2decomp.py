import optparse
import os 
from enum import StrEnum
from collections import OrderedDict

class Target(StrEnum):
    ARM = 'arm'
    THUMB = 'thumb'

    @staticmethod
    def parse(value: str):
        for e in Target:
            if value.lower() == e:
                return e
                
        return Target.ARM


class LayoutOptions(StrEnum):
    ADDRESS = 'address'
    BYTES = 'bytes'
    MNEMONIC = 'mnemonic'
    OPERAND = 'operand'
    EOL_COMMENT = 'eol_comment'

    @staticmethod
    def parse(value: str):
        for e in LayoutOptions:
            if value.lower() == e:
                return e
                
        return LayoutOptions.ADDRESS


# def write_output(output: str, target: Target):
#     with open(output, 'w') as file:
#         file.write()

def process_operand(mnemonic: str, operand: str, externs: list[str]) -> str:
    # If the mnemonic is a jump that refers to a function...
    if mnemonic.startswith('bl'):
        # ... the operand is a function, if does not start with _ then custom
        if not operand.startswith('_'):
            externs.append(f'extern void *{operand} // This needs user data')

    # If the mnemonic is a load or store containing [], then process
    if mnemonic.startswith('ldr') or mnemonic.startswith('str'):
        # Check if pointer call
        if '[->' in operand:
            operand = operand.replace('[->', '=[')
        elif '[' in operand:
            operand = operand.replace('[', '=').replace(']', '')
    
    return operand


def main(input: str, output: str, target: Target, layout: list[LayoutOptions]) -> None:
    with open(input, 'r') as file: 
        function_name: str = ''
        asm_lines: list[str] = ['.' + target]
        externs: list[str] = []

        error = False # If true stop parsing
        line_number = 0
        while (line := file.readline()) != '':
            line_number += 1
            if (error):
                break

            # Strip line and continue if line is empty
            line = line.strip()
            if line == '':
                continue
            
            # Split line into info and remove empty info
            info: list[str] = [value.strip() for value in line.split(' ') if value.strip() != '']

            # If function name is not set, search for it
            if function_name == '':
                # Function name starts with "func" as first info
                if info[0].startswith('func_'):
                    function_name = info[0]
                    asm_lines.append(function_name + ':')
            else:
                # If starts with a label, then just write the label
                if info[0].startswith('LAB_'):
                    asm_lines.append(info[0] + ':')
                else:
                    mnemonic: str = ''
                    operand: str = ''
                    index = 0
                    for option in layout:
                        if option == LayoutOptions.ADDRESS:
                            index += 1
                        
                        elif option == LayoutOptions.BYTES: 
                            index += 4 # 32 bits

                        elif option == LayoutOptions.MNEMONIC:
                            if index >= len(info):
                                print(f'Something is wrong with the assembly at line {line_number}: {line}')
                                error = True
                                break

                            mnemonic = info[index]
                            index += 1

                        elif option == LayoutOptions.OPERAND:
                            if index >= len(info):
                                print(f'Something is wrong with the assembly at line {line_number}: {line}')
                                error = True
                                break

                            # If there is a [ in the operand, then the next index should contain ]
                            operand = info[index]
                            index += 1
                            if '[' in operand:
                                if not ']' in operand:
                                    operand += info[index]
                                    index += 1
                            
                            if mnemonic != '':
                                operand = process_operand(mnemonic, operand, externs)

                        # End of line comment means nothing else
                        elif option == LayoutOptions.EOL_COMMENT:
                            break
                    
                    asm_lines.append(f'\t{mnemonic} {operand}')

    # Write in output file
    with open(output, 'w') as file:
        for line in asm_lines:
            file.write(line + '\n')


if __name__ == '__main__':
    default_out = 'out.S'
    default_target = Target.ARM
    default_layout = ','.join(LayoutOptions)

    parser = optparse.OptionParser(description='Simple script that allows a user to transform ghidra copied disassembly to readable assembly for decomp.me. Be sure that the registers are not hidden by parameters!', usage='python %prog -i file [-o file] [-t arm|thumb] [-l] [-r]')
    parser.add_option('-i', '--input', help='Input file to format')
    parser.add_option('-o', '--output', default=default_out, help='Output file. If not specified, will be out.S')
    parser.add_option('-t', '--target', default=default_target, help='Specified the target (ARM or thumb). If unknown then ARM')
    parser.add_option('-l', '--layout', default=default_layout, help='Sets the layout of a line, each value is separated with a comma. ' \
        'If not specified, it will be the default ghidra layout.\nPossible values: ' + ', '.join(LayoutOptions))
    parser.add_option('-r', '--replace', action='store_true', default=False, help='Replace the output file if existing')

    opts, args = parser.parse_args()
    input = opts.input
    output = opts.output
    target = opts.target
    layout = list(OrderedDict.fromkeys([LayoutOptions.parse(value) for value in opts.layout.split(',')]))

    if input == None or input.strip() == '':
        print('Input file must be specified!')
        exit(1)
    
    if not os.path.exists(input):
        print('Input file does not exist!')
        exit(1)
    
    if os.path.exists(output) and not opts.replace:
        print('Output file already exists! Add -r to auto replace OR remove the file')
        exit(1)

    main(input, output, target, layout)