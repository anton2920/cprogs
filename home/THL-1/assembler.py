import sys

ths_name = 'THL-1 assembler'


def assemble(text):

    # Initializing variables
    isa = {
        'nop':  0b0000,
        'lda':  0b0001,
        'ldi':  0b0010,
        'sta':  0b0011,
        'add':  0b0100,
        'sub':  0b0101,
        'and':  0b0110,
        'or':   0b0111,
        'jmp':  0b1000,
        'jc':   0b1001,
        'jz':   0b1010,
        'js':   0b1011,
        'cmp':  0b1100,
        'test': 0b1101,
        'out':  0b1110,
        'halt': 0b1111
    }

    section = ''
    labels = {}
    data_address = 0x15
    instr_address = 0x0
    opcode = [0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0]

    for _str in text:
        row = _str.lower()
        if section == '':
            if row.split(' ')[1] == '.data':
                section = 'data'
            elif row.split(' ')[1] == '.text':
                section = 'text'
        else:
            if section == 'data':
                if row.endswith(':') and not labels.get(row):
                    labels[row] = data_address
                else:
                    if row.split(' ')[0] == '.byte':
                        opcode[data_address] = int(row.split(' ')[1])
                        data_address -= 1
            elif section == 'text':
                if row.ends(':') and not labels.get(row):
                    labels[row] = instr_address
                    instr_address -= 1
            else:
                sys.exit(-6585)

    # Returning value
    return opcode


def main():

    # Main part
    if len(sys.argv) != 2:
        print(ths_name + ': one file must be provided', end='\n')
        return 1
    try:
        file = open(sys.argv[1], 'r')
    except FileNotFoundError:
        print(ths_name + ': can\'t open ' + sys.argv[1], end='\n')
        return None
    text = file.read().split('\n')
    opcode = assemble(text)


    return 0


if __name__ == '__main__':
    main()
