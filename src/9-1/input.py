import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

OUT_FILENAME = 'input.h'
OUT_FILEPATH = os.path.join(SCRIPT_DIR, OUT_FILENAME)

INCLUDE_GUARD_DEF = f"{OUT_FILENAME.replace('.', '_').upper()}__"

TEST_INPUT_1 = """

"""

INPUT = """

"""

# input = TEST_INPUT_1
input = INPUT

map: list[list[str]] = list()
antenna_types: set[str] = set()

cols = None

for line in input.splitlines():
    line = line.strip()
    if not line:
        continue
    
    row = line

    if cols:
        assert(len(row) == cols)
    else:
        cols = len(row)

    for c in row:
        if c != '.':
            antenna_types.add(c)

    map.append(row)

rows = len(map)

STRUCT = f"""
typedef struct {{
    char data[ROWS][COLS];
}} map_t;
"""

with open(OUT_FILEPATH, 'w') as file:
    file.write(f"#ifndef {INCLUDE_GUARD_DEF}\n")
    file.write(f"#define {INCLUDE_GUARD_DEF}\n")

    file.write("\n")
    file.write(f"#define ROWS ({rows})\n")
    file.write(f"#define COLS ({cols})\n")

    file.write(f"{STRUCT}\n")

    antenna_types = sorted(list(antenna_types))
    antenna_types = [f"'{c}', " for c in antenna_types]
    antenna_types = ''.join(antenna_types).removesuffix(', ')

    file.write(f"static const char ANTENNA_TYPES[] = {{ {antenna_types} }};\n")

    file.write("\n")
    file.write("static const map_t MAP = {{\n")
    for row in map:
        row = [f"'{c}', " for c in row]
        row = ''.join(row).removesuffix(', ')

        file.write(f"    {{ {row} }},\n")
    file.write("}};\n")

    file.write("\n")
    file.write(f"#endif // {INCLUDE_GUARD_DEF}\n")
