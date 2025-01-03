import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

OUT_FILENAME = 'input.h'
OUT_FILEPATH = os.path.join(SCRIPT_DIR, OUT_FILENAME)

INCLUDE_GUARD_DEF = f"{OUT_FILENAME.replace('.', '_').upper()}__"

TEST_INPUT_1 = """
............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
"""

TEST_INPUT_2 = """
T.........
...T......
.T........
..........
..........
..........
..........
..........
..........
..........
"""

INPUT = """
........5..................................e..3...
.......q...........m................e.............
....m.......................................e.....
.........................................C........
.u.m........................8.....................
...........7......9.......8...........F...s.......
6...q..............................s..............
..................................................
..................................................
..................................................
..........9....................F..................
.................................M....D...........
.........U........................................
..q................................8..............
.......9..........................................
0....6.....................e..Qs...............F..
.................................Q...D............
.0.u....................................2.........
..................................................
........u................Q........................
.....E........1...................................
...n....v....................................3....
......u..0................N.......................
............................................z.....
.........7....U.........4.....Z...Q.....D.....V...
..............n1.........f.................2......
E.............................f..............z....
...E........1.Z.......U......................D....
.......n...v....7Z...N............................
..........7..N.....Zf...........................3.
................................b............V....
............4..................................9..
..n...v........................5................2.
.........v.................5.........S............
..........................s.......................
.....U.........4..C.....................S..V......
..................................................
......................c........b............M.....
...........4.Wc....d.......1.....b.....S..........
..E........c............................5......z..
..............w..C....................SM.2........
........................d.........................
...............c......C3..........................
...............w....W.............................
..................................................
.........d.......B....w...........................
....B.....W.......dw..........................M...
...............W......................N...V.......
.B................................................
....................B...............b.............
"""

# input = TEST_INPUT_1
# input = TEST_INPUT_2
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
