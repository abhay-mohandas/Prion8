from opcode import BASE, OPEX0
import sys


def read_asm(asmfile):
    instr_lines = []
    with open(asmfile, "r") as file:
        for line in file:
            iline = line.split(";")[0] # ignores comment in asm
            iline = iline.strip()     # removes blank spaces
            if iline:   # skip empty lines
                instr_lines.append(iline)
    return instr_lines

def write_bin(out_bin_file,out_bin_data):
    with open(out_bin_file, "wb") as file:
        file.write(out_bin_data)
    print(f"Written {len(out_bin_data)} bytes → {out_bin_file}")
    return

def main():
    if len(sys.argv) < 2:
        print("Usage: python assembler.py <input.asm>")
        sys.exit(1)
    asmfile = sys.argv[1]
    out_bin_file = "output.bin"
    out_bin_data = bytearray()

    instr_lines = read_asm(asmfile)
    # decode instructions
    write_bin(out_bin_file,out_bin_data)

    return


main()