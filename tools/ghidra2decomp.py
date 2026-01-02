import optparse
import os 
from enum import StrEnum
from collections import OrderedDict
import re

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


class DataType(StrEnum):
    BYTE='BYTE'
    CHAR = 'CHAR'
    DOUBLE = 'DOUBLE'
    DWORD = 'DWORD'
    FLOAT = 'FLOAT'
    INT = 'INT'
    LONG = 'LONG'
    LONGDOUBLE = 'LONGDOUBLE'
    POINTER = 'PTR'
    QWORD = 'QWORD'
    STRING = 'STRING'
    UINT = 'UINT'
    ULONG = 'ULONG'
    WORD = 'WORD'
    ERROR = ''

    @staticmethod
    def parse(value: str):
        for e in DataType:
            if value.lower() == e:
                return e
                
        return DataType.ERROR


class DataLabel(object):
    type: DataType
    name: str
    data: str
    used: bool

    def __init__(self, type: DataType, name: str, data: str = '', used: bool = False) -> None:
        self.type = type
        self.name = name
        self.data = data
        self.used = used


REGISTER_PATTERN = re.compile('^r[0-9]{1,2},')
XREF_PATTERN = re.compile('XREF\\[([0-9]+)\\]')


def process_operand(mnemonic: str, operand: str, externs: list[str], data_labels: dict[str, DataLabel]) -> tuple[str, str]:
    label_to_replace: str = ''
    # If the mnemonic is a jump that refers to a function...
    if mnemonic == 'bl':
        # ... the operand is a function, if does not start with _ then custom
        if not operand.startswith('_'):
            externs.append(f'extern void *{operand} // This needs user data')

    # If the mnemonic is a load or store containing [], then process
    if mnemonic.startswith('ldr') or mnemonic.startswith('str'):
        # Check if pointer call
        if '[->' in operand:
            value = value = operand.split('[->')[1].split(']')[0]
            operand = operand.replace('[->', '=[')
            externs.append(f'extern void *{value}; // This needs the user for the pointer type')
        elif '[' in operand:
            value = operand.split('[')[1].split(']')[0]
            # If value is a register, then DO NOT CHANGE
            if not REGISTER_PATTERN.match(value):
                operand = operand.replace('[', '=').replace(']', '')
                islabel: bool = True

                try:
                    int(value)
                except Exception:
                    islabel = True
                
                if islabel:
                    # Check in the label list if the label exists
                    if value not in data_labels:
                        # Add label and add to replace list
                        data_labels[value] = DataLabel(DataType.ERROR, value, '', True)
                        label_to_replace = value
                    else:
                        label: DataLabel = data_labels[value]
                        if label.data != '':
                            operand.replace(value, data_labels[value].data)
                        else:
                            label_to_replace = value
    
    return operand, label_to_replace


def process_instruction(line_number: int, wrote_line: int, line: str, info: list[str], layout: list[LayoutOptions], data_labels: dict[str, DataLabel]) -> tuple[str, str, list[str], tuple[str, int], bool]:
    mnemonic: str = ''
    operand: str = ''
    externs: list[str] = []
    replace: tuple[str, int] = ('', -1)
    error: bool = False
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
            if mnemonic.startswith('ldmia'):
                # Ghidra will say ldmiage instead of ldmgeia
                cond = mnemonic[5:]
                if cond != '':
                    mnemonic = 'ldm' + cond + 'ia'
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
                while not ']' in operand:
                    if info[index].startswith(']'):
                        operand += info[index]
                    else:
                        operand = operand + ' ' + info[index]
                    index += 1
            
            if operand.endswith('lsl'):
                operand = operand + ' ' + info[index]
                index += 1
            
            if mnemonic != '':
                operand, label_to_replace = process_operand(mnemonic, operand, externs, data_labels)
                if label_to_replace != '':
                    # Line to replace is the next index because this one is not yet written
                    replace = (label_to_replace, wrote_line + 1)

        # End of line comment means nothing else
        elif option == LayoutOptions.EOL_COMMENT:
            break

    return mnemonic, operand, externs, replace, error


def process_data(type: DataType, line_number: int, line: str, info: list[str], layout: list[LayoutOptions]) -> tuple[str, bool]:
    # TODO Not always the same size! Change StrEnum to enum with custom size
    # For now consider always 4 bytes since almost always pointers in code
    byte_size = 4
    error: bool = False
    data: str = ''
    index = 0

    # Try to read bytes
    if LayoutOptions.BYTES in layout:
        for option in layout:
            if option == LayoutOptions.ADDRESS:
                index += 1
            
            elif option == LayoutOptions.BYTES: 
                # Check OOB
                if index + byte_size >= len(info):
                    print(f'Something is wrong with the assembly at line {line_number}: {line}')
                    error = True
                    break

                for _ in range(0, byte_size):
                    data = info[index] + data
                    index += 1

                break

            elif option == LayoutOptions.MNEMONIC:
                index += 1

            elif option == LayoutOptions.OPERAND:
                index += 1

            # End of line comment means nothing else
            elif option == LayoutOptions.EOL_COMMENT:
                print('Got EOL comment before bytes, ignore!')
                error = True
                break
    else: 
        print('No bytes in layout, cannot determine data, ignore!')
        error = True

    return '0x' + data, error


def main(input: str, output: str, target: Target, layout: list[LayoutOptions]) -> None:
    with open(input, 'r') as file: 
        function_name: str = ''
        asm_lines: list[str] = ['.' + target]
        externs: list[str] = []
        data_labels: dict[str, DataLabel] = {}
        labels_to_update: dict[str, list[int]] = {}
        dataline: bool = False
        current_label: DataLabel = DataLabel(DataType.ERROR, '') # Only used when processing data
        hasbytes = LayoutOptions.BYTES in layout
        xref_lines_left: int = 0

        error = False # If true stop parsing
        line_number = 0
        wrote_line = 0
        while (line := file.readline()) != '':
            line_number += 1
            if (error):
                break

            # Strip line and continue if line is empty
            line = line.strip()
            if line == '':
                continue

            # This line is a XREF, continue
            if xref_lines_left > 0:
                xref_lines_left -= 1
                continue
            
            # Sometimes ghidra puts random spaces... remove spaces between some symbols
            # like comma or braces
            line = ','.join([a.strip() for a in line.split(',')])

            # Split line into info and remove empty info
            info: list[str] = [value.strip() for value in line.split(' ') if value.strip() != '']
            first_info = info[0]

            # If is data, then analyse data
            if dataline:
                data, dataerror = process_data(current_label.type, line_number, line, info, layout)
                if dataerror:
                    print('Something went wrong when analysing data, ignore if future data')
                    hasbytes = False

                current_label.data = data
                # TODO Work on data line to check length
                dataline = False

            else: 
                # If function name is not set, search for it
                if function_name == '':
                    # Function name starts with "func" as first info
                    if first_info.startswith('func_'):
                        function_name = first_info
                        asm_lines.append(function_name + ':')
                        wrote_line += 1

                        # Check the XREF to see the number of lines to skip
                        matcher = XREF_PATTERN.search(line)
                        if matcher != None:
                            # First group is the number of ref
                            # Must be an int because of the regex
                            xref_lines_left = int(matcher.group(1)) - 1
                            # TODO Count the number of comma to check how many refs are present on the same line!

                else:
                    # If starts with a label, then just write the label
                    if first_info.startswith('LAB_'):
                        asm_lines.append(first_info + ':')
                        wrote_line += 1

                        # Check the XREF to see the number of lines to skip
                        matcher = XREF_PATTERN.match(line)
                        if matcher != None:
                            # TODO Remove duplicate, DRY is important
                            # First group is the number of ref
                            # Must be an int because of the regex
                            xref_lines_left = int(matcher.group(1)) - 1
                        continue
                            
                    elif hasbytes:
                        # If bytes in layout then look at data too
                        # Check if first info is a type 
                        for type in DataType:
                            if first_info.startswith(type + '_'):
                                # Next line is data
                                dataline = True
                                if first_info not in data_labels:
                                    label = DataLabel(type, first_info)
                                    data_labels[first_info] = label
                                    current_label = label
                                else:
                                    current_label = data_labels[first_info]

                    if not dataline:
                        mnemonic, operand, line_externs, (replace_name, replace_line), error = process_instruction(line_number, wrote_line, line, info, layout, data_labels)
                        if error:
                            break

                        for extern in line_externs:
                            externs.append(extern)
                        if replace_line != -1:
                            if replace_name not in labels_to_update:
                                labels_to_update[replace_name] = [replace_line]
                            else: 
                                labels_to_update[replace_name].append(replace_line)
                        asm_lines.append(f'\t{mnemonic} {operand}')
                        wrote_line += 1

    for label_name in labels_to_update:
        label: DataLabel = data_labels[label_name]
        if label.data != '':
            for line_number in labels_to_update[label_name]:
                asm_lines[line_number] = asm_lines[line_number].replace(label_name, label.data)

    # Write in output file
    with open(output, 'w') as file:
        for line in asm_lines:
            file.write(line + '\n')

        # Write exports
        if len(externs) != 0:
            file.write('\nExterns to add in decomp.me in C:\n')
            for line in externs:
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