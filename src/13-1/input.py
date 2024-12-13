import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

OUT_FILENAME = 'input.h'
OUT_FILEPATH = os.path.join(SCRIPT_DIR, OUT_FILENAME)

INCLUDE_GUARD_DEF = f"{OUT_FILENAME.replace('.', '_').upper()}__"

TEST_INPUT_1 = """
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279
"""

INPUT = """
Button A: X+11, Y+67
Button B: X+17, Y+16
Prize: X=2413, Y=6293

Button A: X+22, Y+48
Button B: X+43, Y+21
Prize: X=3637, Y=10139

Button A: X+23, Y+12
Button B: X+31, Y+99
Prize: X=3660, Y=8370

Button A: X+11, Y+27
Button B: X+62, Y+11
Prize: X=17345, Y=17180

Button A: X+45, Y+17
Button B: X+15, Y+49
Prize: X=13745, Y=15517

Button A: X+64, Y+35
Button B: X+12, Y+36
Prize: X=2524, Y=4251

Button A: X+21, Y+48
Button B: X+40, Y+17
Prize: X=5881, Y=14712

Button A: X+45, Y+11
Button B: X+12, Y+61
Prize: X=959, Y=11016

Button A: X+85, Y+33
Button B: X+33, Y+59
Prize: X=5586, Y=2492

Button A: X+25, Y+45
Button B: X+66, Y+29
Prize: X=2842, Y=4038

Button A: X+13, Y+39
Button B: X+49, Y+35
Prize: X=3096, Y=4024

Button A: X+43, Y+44
Button B: X+47, Y+13
Prize: X=403, Y=272

Button A: X+20, Y+70
Button B: X+67, Y+17
Prize: X=14809, Y=14559

Button A: X+17, Y+41
Button B: X+59, Y+27
Prize: X=3121, Y=5433

Button A: X+31, Y+82
Button B: X+86, Y+35
Prize: X=9811, Y=10168

Button A: X+70, Y+13
Button B: X+59, Y+57
Prize: X=7380, Y=5054

Button A: X+35, Y+97
Button B: X+75, Y+48
Prize: X=6765, Y=10596

Button A: X+72, Y+97
Button B: X+68, Y+24
Prize: X=12084, Y=11209

Button A: X+29, Y+86
Button B: X+36, Y+17
Prize: X=3505, Y=6355

Button A: X+37, Y+89
Button B: X+27, Y+18
Prize: X=1846, Y=3032

Button A: X+16, Y+43
Button B: X+46, Y+26
Prize: X=7382, Y=16655

Button A: X+34, Y+30
Button B: X+81, Y+16
Prize: X=9573, Y=3288

Button A: X+11, Y+47
Button B: X+54, Y+16
Prize: X=13689, Y=4763

Button A: X+73, Y+27
Button B: X+50, Y+93
Prize: X=9403, Y=10854

Button A: X+86, Y+72
Button B: X+15, Y+43
Prize: X=7485, Y=8367

Button A: X+16, Y+45
Button B: X+17, Y+11
Prize: X=8612, Y=2586

Button A: X+17, Y+45
Button B: X+50, Y+28
Prize: X=19421, Y=9613

Button A: X+35, Y+22
Button B: X+23, Y+45
Prize: X=17353, Y=2219

Button A: X+59, Y+32
Button B: X+14, Y+54
Prize: X=5488, Y=7478

Button A: X+19, Y+67
Button B: X+97, Y+30
Prize: X=5414, Y=4425

Button A: X+50, Y+83
Button B: X+47, Y+13
Prize: X=11105, Y=7385

Button A: X+36, Y+60
Button B: X+85, Y+15
Prize: X=5770, Y=5310

Button A: X+92, Y+57
Button B: X+13, Y+37
Prize: X=2054, Y=3183

Button A: X+24, Y+82
Button B: X+57, Y+11
Prize: X=12464, Y=4442

Button A: X+62, Y+26
Button B: X+13, Y+28
Prize: X=16392, Y=18966

Button A: X+23, Y+50
Button B: X+95, Y+41
Prize: X=1505, Y=1451

Button A: X+45, Y+77
Button B: X+81, Y+34
Prize: X=3213, Y=1523

Button A: X+11, Y+65
Button B: X+46, Y+45
Prize: X=4883, Y=7760

Button A: X+66, Y+21
Button B: X+13, Y+65
Prize: X=19649, Y=11324

Button A: X+52, Y+21
Button B: X+20, Y+35
Prize: X=4128, Y=5044

Button A: X+15, Y+68
Button B: X+56, Y+16
Prize: X=16333, Y=9548

Button A: X+39, Y+97
Button B: X+32, Y+15
Prize: X=4738, Y=8361

Button A: X+68, Y+44
Button B: X+17, Y+84
Prize: X=1411, Y=5220

Button A: X+42, Y+17
Button B: X+53, Y+79
Prize: X=9630, Y=15051

Button A: X+17, Y+88
Button B: X+81, Y+28
Prize: X=4603, Y=3480

Button A: X+29, Y+51
Button B: X+41, Y+14
Prize: X=3198, Y=2777

Button A: X+16, Y+41
Button B: X+70, Y+21
Prize: X=6112, Y=4259

Button A: X+17, Y+46
Button B: X+63, Y+16
Prize: X=2935, Y=4406

Button A: X+81, Y+62
Button B: X+21, Y+93
Prize: X=4254, Y=7564

Button A: X+41, Y+13
Button B: X+22, Y+55
Prize: X=2492, Y=7584

Button A: X+20, Y+91
Button B: X+80, Y+55
Prize: X=1240, Y=2552

Button A: X+67, Y+31
Button B: X+19, Y+53
Prize: X=4751, Y=845

Button A: X+96, Y+11
Button B: X+26, Y+71
Prize: X=7462, Y=4052

Button A: X+55, Y+25
Button B: X+19, Y+60
Prize: X=16578, Y=2220

Button A: X+32, Y+18
Button B: X+21, Y+38
Prize: X=11759, Y=17880

Button A: X+23, Y+63
Button B: X+80, Y+14
Prize: X=1688, Y=3598

Button A: X+26, Y+46
Button B: X+39, Y+13
Prize: X=15577, Y=19587

Button A: X+25, Y+12
Button B: X+12, Y+50
Prize: X=16734, Y=15600

Button A: X+64, Y+12
Button B: X+23, Y+66
Prize: X=15636, Y=16760

Button A: X+20, Y+55
Button B: X+72, Y+35
Prize: X=15028, Y=19515

Button A: X+35, Y+90
Button B: X+24, Y+12
Prize: X=1088, Y=1704

Button A: X+46, Y+71
Button B: X+59, Y+21
Prize: X=8119, Y=7697

Button A: X+40, Y+11
Button B: X+47, Y+71
Prize: X=14448, Y=6900

Button A: X+80, Y+27
Button B: X+15, Y+30
Prize: X=2270, Y=1614

Button A: X+55, Y+32
Button B: X+12, Y+29
Prize: X=12767, Y=18896

Button A: X+75, Y+60
Button B: X+24, Y+81
Prize: X=2307, Y=4503

Button A: X+83, Y+29
Button B: X+38, Y+90
Prize: X=4750, Y=4882

Button A: X+18, Y+50
Button B: X+53, Y+21
Prize: X=13580, Y=4972

Button A: X+47, Y+77
Button B: X+82, Y+37
Prize: X=8464, Y=6274

Button A: X+17, Y+49
Button B: X+56, Y+16
Prize: X=3317, Y=2581

Button A: X+84, Y+14
Button B: X+11, Y+70
Prize: X=7036, Y=4172

Button A: X+66, Y+24
Button B: X+14, Y+49
Prize: X=6362, Y=15623

Button A: X+55, Y+80
Button B: X+73, Y+12
Prize: X=7687, Y=2328

Button A: X+13, Y+32
Button B: X+62, Y+27
Prize: X=9285, Y=15374

Button A: X+11, Y+26
Button B: X+51, Y+16
Prize: X=1464, Y=2624

Button A: X+70, Y+43
Button B: X+12, Y+29
Prize: X=10940, Y=9281

Button A: X+50, Y+11
Button B: X+32, Y+46
Prize: X=2778, Y=1741

Button A: X+34, Y+13
Button B: X+30, Y+52
Prize: X=7086, Y=1563

Button A: X+16, Y+46
Button B: X+69, Y+17
Prize: X=4134, Y=666

Button A: X+42, Y+54
Button B: X+71, Y+27
Prize: X=6241, Y=4617

Button A: X+34, Y+86
Button B: X+83, Y+58
Prize: X=4411, Y=4016

Button A: X+12, Y+60
Button B: X+75, Y+72
Prize: X=2385, Y=6168

Button A: X+40, Y+21
Button B: X+44, Y+70
Prize: X=4620, Y=13108

Button A: X+93, Y+55
Button B: X+12, Y+52
Prize: X=8634, Y=8878

Button A: X+34, Y+12
Button B: X+15, Y+30
Prize: X=5904, Y=16592

Button A: X+32, Y+11
Button B: X+43, Y+77
Prize: X=739, Y=17403

Button A: X+93, Y+19
Button B: X+20, Y+93
Prize: X=1814, Y=993

Button A: X+30, Y+61
Button B: X+42, Y+17
Prize: X=8978, Y=2341

Button A: X+15, Y+64
Button B: X+78, Y+32
Prize: X=16535, Y=14944

Button A: X+99, Y+52
Button B: X+32, Y+81
Prize: X=10211, Y=6583

Button A: X+71, Y+23
Button B: X+16, Y+63
Prize: X=7591, Y=8958

Button A: X+54, Y+77
Button B: X+95, Y+42
Prize: X=1529, Y=1526

Button A: X+89, Y+58
Button B: X+16, Y+50
Prize: X=6214, Y=7532

Button A: X+58, Y+23
Button B: X+20, Y+45
Prize: X=13886, Y=4416

Button A: X+50, Y+18
Button B: X+60, Y+77
Prize: X=5090, Y=3439

Button A: X+73, Y+36
Button B: X+17, Y+44
Prize: X=14590, Y=14080

Button A: X+38, Y+16
Button B: X+19, Y+73
Prize: X=2090, Y=5040

Button A: X+59, Y+14
Button B: X+24, Y+56
Prize: X=15380, Y=7480

Button A: X+67, Y+24
Button B: X+41, Y+98
Prize: X=6027, Y=3242

Button A: X+16, Y+45
Button B: X+54, Y+18
Prize: X=19638, Y=14489

Button A: X+71, Y+41
Button B: X+13, Y+87
Prize: X=1387, Y=5809

Button A: X+16, Y+34
Button B: X+62, Y+21
Prize: X=8980, Y=11350

Button A: X+20, Y+53
Button B: X+96, Y+48
Prize: X=4508, Y=4103

Button A: X+98, Y+82
Button B: X+16, Y+61
Prize: X=3210, Y=3781

Button A: X+92, Y+93
Button B: X+68, Y+16
Prize: X=9584, Y=5680

Button A: X+66, Y+12
Button B: X+26, Y+57
Prize: X=7548, Y=5136

Button A: X+16, Y+77
Button B: X+52, Y+11
Prize: X=2404, Y=18690

Button A: X+53, Y+32
Button B: X+12, Y+40
Prize: X=13510, Y=12432

Button A: X+25, Y+52
Button B: X+56, Y+25
Prize: X=11743, Y=11982

Button A: X+45, Y+21
Button B: X+39, Y+70
Prize: X=13715, Y=17273

Button A: X+69, Y+32
Button B: X+23, Y+90
Prize: X=7613, Y=10988

Button A: X+20, Y+55
Button B: X+65, Y+31
Prize: X=7580, Y=6788

Button A: X+97, Y+98
Button B: X+11, Y+58
Prize: X=5903, Y=7558

Button A: X+80, Y+50
Button B: X+25, Y+91
Prize: X=3675, Y=4935

Button A: X+20, Y+36
Button B: X+44, Y+13
Prize: X=8936, Y=6562

Button A: X+55, Y+32
Button B: X+13, Y+47
Prize: X=12045, Y=4519

Button A: X+35, Y+19
Button B: X+14, Y+43
Prize: X=14172, Y=5221

Button A: X+90, Y+11
Button B: X+80, Y+73
Prize: X=15250, Y=7301

Button A: X+22, Y+41
Button B: X+60, Y+34
Prize: X=3636, Y=4286

Button A: X+25, Y+73
Button B: X+78, Y+45
Prize: X=8736, Y=9609

Button A: X+92, Y+72
Button B: X+22, Y+69
Prize: X=8586, Y=11121

Button A: X+18, Y+46
Button B: X+76, Y+50
Prize: X=3662, Y=16348

Button A: X+85, Y+14
Button B: X+39, Y+89
Prize: X=4667, Y=5971

Button A: X+16, Y+72
Button B: X+53, Y+51
Prize: X=4091, Y=6597

Button A: X+88, Y+74
Button B: X+29, Y+88
Prize: X=7108, Y=9794

Button A: X+18, Y+50
Button B: X+53, Y+18
Prize: X=15535, Y=566

Button A: X+16, Y+80
Button B: X+80, Y+13
Prize: X=4992, Y=2365

Button A: X+36, Y+13
Button B: X+12, Y+20
Prize: X=6620, Y=4369

Button A: X+52, Y+21
Button B: X+72, Y+97
Prize: X=4548, Y=3331

Button A: X+55, Y+27
Button B: X+26, Y+59
Prize: X=3241, Y=14331

Button A: X+56, Y+39
Button B: X+16, Y+48
Prize: X=6552, Y=6885

Button A: X+37, Y+11
Button B: X+47, Y+67
Prize: X=5768, Y=6866

Button A: X+69, Y+45
Button B: X+34, Y+76
Prize: X=3067, Y=6091

Button A: X+12, Y+33
Button B: X+54, Y+40
Prize: X=8198, Y=15562

Button A: X+15, Y+63
Button B: X+52, Y+16
Prize: X=6077, Y=6785

Button A: X+30, Y+77
Button B: X+49, Y+15
Prize: X=17677, Y=17745

Button A: X+93, Y+34
Button B: X+15, Y+26
Prize: X=1791, Y=1578

Button A: X+45, Y+13
Button B: X+39, Y+79
Prize: X=5049, Y=2881

Button A: X+63, Y+93
Button B: X+81, Y+37
Prize: X=9090, Y=8712

Button A: X+33, Y+27
Button B: X+26, Y+96
Prize: X=4804, Y=9012

Button A: X+15, Y+44
Button B: X+68, Y+17
Prize: X=1502, Y=6143

Button A: X+92, Y+42
Button B: X+50, Y+83
Prize: X=12554, Y=11207

Button A: X+12, Y+33
Button B: X+83, Y+63
Prize: X=14493, Y=16544

Button A: X+22, Y+77
Button B: X+95, Y+89
Prize: X=4105, Y=7793

Button A: X+80, Y+89
Button B: X+13, Y+65
Prize: X=2938, Y=6604

Button A: X+98, Y+11
Button B: X+51, Y+71
Prize: X=2133, Y=1088

Button A: X+49, Y+15
Button B: X+26, Y+74
Prize: X=586, Y=3754

Button A: X+15, Y+79
Button B: X+92, Y+21
Prize: X=10041, Y=9774

Button A: X+41, Y+14
Button B: X+28, Y+75
Prize: X=7145, Y=469

Button A: X+99, Y+58
Button B: X+11, Y+71
Prize: X=4422, Y=5883

Button A: X+20, Y+84
Button B: X+21, Y+21
Prize: X=2650, Y=5082

Button A: X+84, Y+49
Button B: X+18, Y+89
Prize: X=7110, Y=4383

Button A: X+62, Y+50
Button B: X+20, Y+56
Prize: X=5556, Y=7152

Button A: X+38, Y+65
Button B: X+41, Y+23
Prize: X=13168, Y=9055

Button A: X+71, Y+70
Button B: X+25, Y+98
Prize: X=3780, Y=8568

Button A: X+71, Y+14
Button B: X+23, Y+73
Prize: X=2419, Y=13234

Button A: X+22, Y+49
Button B: X+53, Y+32
Prize: X=15191, Y=2036

Button A: X+18, Y+36
Button B: X+34, Y+11
Prize: X=13290, Y=8011

Button A: X+19, Y+69
Button B: X+86, Y+43
Prize: X=3790, Y=3799

Button A: X+31, Y+61
Button B: X+29, Y+15
Prize: X=19068, Y=18308

Button A: X+40, Y+23
Button B: X+16, Y+49
Prize: X=2928, Y=490

Button A: X+50, Y+11
Button B: X+33, Y+82
Prize: X=19860, Y=3614

Button A: X+38, Y+11
Button B: X+46, Y+75
Prize: X=8694, Y=13399

Button A: X+99, Y+83
Button B: X+12, Y+46
Prize: X=4365, Y=6355

Button A: X+11, Y+85
Button B: X+79, Y+13
Prize: X=3939, Y=5997

Button A: X+93, Y+37
Button B: X+43, Y+63
Prize: X=10165, Y=7945

Button A: X+13, Y+63
Button B: X+70, Y+19
Prize: X=7539, Y=18874

Button A: X+14, Y+57
Button B: X+68, Y+50
Prize: X=2150, Y=1721

Button A: X+56, Y+49
Button B: X+14, Y+52
Prize: X=2184, Y=2229

Button A: X+30, Y+90
Button B: X+22, Y+13
Prize: X=1614, Y=3411

Button A: X+99, Y+37
Button B: X+29, Y+87
Prize: X=3346, Y=6658

Button A: X+79, Y+36
Button B: X+19, Y+60
Prize: X=9003, Y=8636

Button A: X+99, Y+21
Button B: X+26, Y+36
Prize: X=5883, Y=4083

Button A: X+38, Y+71
Button B: X+45, Y+16
Prize: X=7552, Y=612

Button A: X+18, Y+46
Button B: X+73, Y+33
Prize: X=8668, Y=7196

Button A: X+78, Y+95
Button B: X+79, Y+15
Prize: X=7507, Y=7600

Button A: X+56, Y+22
Button B: X+18, Y+49
Prize: X=13844, Y=7450

Button A: X+14, Y+59
Button B: X+65, Y+18
Prize: X=6730, Y=1720

Button A: X+14, Y+75
Button B: X+24, Y+23
Prize: X=500, Y=1095

Button A: X+36, Y+85
Button B: X+95, Y+64
Prize: X=1051, Y=1680

Button A: X+80, Y+26
Button B: X+12, Y+55
Prize: X=496, Y=9574

Button A: X+18, Y+73
Button B: X+89, Y+77
Prize: X=9808, Y=13654

Button A: X+71, Y+16
Button B: X+12, Y+31
Prize: X=1825, Y=864

Button A: X+34, Y+11
Button B: X+49, Y+55
Prize: X=3425, Y=1617

Button A: X+43, Y+17
Button B: X+41, Y+81
Prize: X=5921, Y=6941

Button A: X+22, Y+57
Button B: X+68, Y+25
Prize: X=16658, Y=12697

Button A: X+21, Y+68
Button B: X+42, Y+15
Prize: X=5324, Y=14446

Button A: X+19, Y+58
Button B: X+69, Y+32
Prize: X=15537, Y=18904

Button A: X+73, Y+12
Button B: X+20, Y+76
Prize: X=18244, Y=16580

Button A: X+67, Y+31
Button B: X+31, Y+62
Prize: X=8226, Y=7285

Button A: X+52, Y+24
Button B: X+11, Y+27
Prize: X=5837, Y=17849

Button A: X+28, Y+53
Button B: X+39, Y+15
Prize: X=3114, Y=4365

Button A: X+42, Y+22
Button B: X+44, Y+71
Prize: X=4948, Y=4414

Button A: X+34, Y+93
Button B: X+91, Y+29
Prize: X=4353, Y=3770

Button A: X+12, Y+68
Button B: X+40, Y+12
Prize: X=16052, Y=15576

Button A: X+43, Y+21
Button B: X+17, Y+35
Prize: X=13778, Y=10546

Button A: X+86, Y+22
Button B: X+48, Y+65
Prize: X=6174, Y=6377

Button A: X+34, Y+13
Button B: X+51, Y+77
Prize: X=5531, Y=18192

Button A: X+18, Y+59
Button B: X+54, Y+33
Prize: X=414, Y=925

Button A: X+30, Y+93
Button B: X+90, Y+59
Prize: X=9840, Y=12244

Button A: X+25, Y+73
Button B: X+75, Y+45
Prize: X=4925, Y=4985

Button A: X+87, Y+23
Button B: X+66, Y+76
Prize: X=7626, Y=3070

Button A: X+47, Y+15
Button B: X+15, Y+28
Prize: X=12406, Y=16291

Button A: X+48, Y+88
Button B: X+95, Y+20
Prize: X=3968, Y=4808

Button A: X+45, Y+79
Button B: X+89, Y+14
Prize: X=8177, Y=6105

Button A: X+26, Y+93
Button B: X+73, Y+67
Prize: X=1775, Y=4602

Button A: X+44, Y+82
Button B: X+42, Y+19
Prize: X=4586, Y=6235

Button A: X+64, Y+28
Button B: X+21, Y+43
Prize: X=14447, Y=3917

Button A: X+19, Y+72
Button B: X+76, Y+63
Prize: X=1957, Y=6291

Button A: X+96, Y+13
Button B: X+73, Y+72
Prize: X=4548, Y=2852

Button A: X+30, Y+12
Button B: X+38, Y+52
Prize: X=6852, Y=17392

Button A: X+58, Y+75
Button B: X+91, Y+24
Prize: X=2932, Y=3042

Button A: X+15, Y+43
Button B: X+79, Y+37
Prize: X=9051, Y=7189

Button A: X+12, Y+42
Button B: X+23, Y+12
Prize: X=12218, Y=16160

Button A: X+53, Y+71
Button B: X+80, Y+30
Prize: X=3217, Y=2689

Button A: X+31, Y+44
Button B: X+32, Y+11
Prize: X=9632, Y=2025

Button A: X+16, Y+27
Button B: X+43, Y+20
Prize: X=19702, Y=3192

Button A: X+83, Y+40
Button B: X+25, Y+65
Prize: X=1539, Y=2595

Button A: X+33, Y+16
Button B: X+40, Y+85
Prize: X=1704, Y=1023

Button A: X+26, Y+45
Button B: X+54, Y+26
Prize: X=17802, Y=3818

Button A: X+15, Y+60
Button B: X+65, Y+30
Prize: X=15440, Y=18680

Button A: X+70, Y+33
Button B: X+18, Y+54
Prize: X=468, Y=15296

Button A: X+45, Y+89
Button B: X+99, Y+63
Prize: X=11952, Y=13280

Button A: X+97, Y+47
Button B: X+18, Y+84
Prize: X=1575, Y=3699

Button A: X+66, Y+23
Button B: X+11, Y+49
Prize: X=10869, Y=14202

Button A: X+22, Y+72
Button B: X+53, Y+17
Prize: X=10629, Y=17691

Button A: X+80, Y+18
Button B: X+58, Y+54
Prize: X=8884, Y=6012

Button A: X+28, Y+79
Button B: X+51, Y+17
Prize: X=2126, Y=1684

Button A: X+48, Y+95
Button B: X+95, Y+30
Prize: X=12580, Y=10360

Button A: X+19, Y+45
Button B: X+96, Y+34
Prize: X=8983, Y=3679

Button A: X+24, Y+59
Button B: X+74, Y+56
Prize: X=3744, Y=3160

Button A: X+57, Y+22
Button B: X+22, Y+66
Prize: X=12291, Y=19658

Button A: X+57, Y+20
Button B: X+79, Y+96
Prize: X=5089, Y=4312

Button A: X+26, Y+87
Button B: X+65, Y+25
Prize: X=5070, Y=6955

Button A: X+52, Y+23
Button B: X+35, Y+91
Prize: X=4584, Y=3840

Button A: X+37, Y+16
Button B: X+39, Y+90
Prize: X=2723, Y=4688

Button A: X+64, Y+14
Button B: X+11, Y+40
Prize: X=5126, Y=4204

Button A: X+46, Y+22
Button B: X+64, Y+96
Prize: X=5296, Y=6064

Button A: X+18, Y+67
Button B: X+78, Y+39
Prize: X=8718, Y=8071

Button A: X+37, Y+58
Button B: X+39, Y+16
Prize: X=13770, Y=19600

Button A: X+60, Y+16
Button B: X+15, Y+58
Prize: X=2495, Y=6778

Button A: X+93, Y+20
Button B: X+26, Y+92
Prize: X=9092, Y=9300

Button A: X+81, Y+65
Button B: X+13, Y+67
Prize: X=7276, Y=8950

Button A: X+17, Y+90
Button B: X+94, Y+13
Prize: X=7628, Y=4035

Button A: X+11, Y+35
Button B: X+96, Y+28
Prize: X=7526, Y=4802

Button A: X+62, Y+56
Button B: X+16, Y+58
Prize: X=5774, Y=7262

Button A: X+51, Y+17
Button B: X+70, Y+92
Prize: X=6792, Y=4324

Button A: X+71, Y+13
Button B: X+12, Y+83
Prize: X=9169, Y=18347

Button A: X+26, Y+12
Button B: X+32, Y+72
Prize: X=2322, Y=4620

Button A: X+86, Y+16
Button B: X+60, Y+84
Prize: X=11328, Y=7716

Button A: X+14, Y+20
Button B: X+97, Y+33
Prize: X=2221, Y=1167

Button A: X+49, Y+19
Button B: X+62, Y+91
Prize: X=5564, Y=4568

Button A: X+16, Y+66
Button B: X+35, Y+11
Prize: X=18001, Y=5237

Button A: X+36, Y+43
Button B: X+85, Y+18
Prize: X=5656, Y=1410

Button A: X+30, Y+71
Button B: X+45, Y+17
Prize: X=15860, Y=19075

Button A: X+77, Y+36
Button B: X+14, Y+44
Prize: X=13451, Y=216

Button A: X+13, Y+46
Button B: X+81, Y+41
Prize: X=1577, Y=11369

Button A: X+25, Y+47
Button B: X+81, Y+43
Prize: X=7405, Y=5179

Button A: X+70, Y+15
Button B: X+40, Y+57
Prize: X=3370, Y=4548

Button A: X+11, Y+43
Button B: X+49, Y+27
Prize: X=8601, Y=15933

Button A: X+21, Y+51
Button B: X+63, Y+12
Prize: X=893, Y=4667

Button A: X+38, Y+78
Button B: X+45, Y+16
Prize: X=4985, Y=7254

Button A: X+57, Y+29
Button B: X+26, Y+45
Prize: X=8640, Y=7648

Button A: X+21, Y+60
Button B: X+64, Y+20
Prize: X=16455, Y=7000

Button A: X+12, Y+36
Button B: X+54, Y+15
Prize: X=8630, Y=3209

Button A: X+27, Y+52
Button B: X+46, Y+29
Prize: X=15857, Y=13321

Button A: X+42, Y+18
Button B: X+27, Y+47
Prize: X=17894, Y=3678

Button A: X+85, Y+83
Button B: X+16, Y+89
Prize: X=7778, Y=8182

Button A: X+39, Y+68
Button B: X+70, Y+38
Prize: X=6445, Y=5606

Button A: X+82, Y+16
Button B: X+18, Y+60
Prize: X=3032, Y=5732

Button A: X+70, Y+41
Button B: X+27, Y+63
Prize: X=2461, Y=1583

Button A: X+12, Y+90
Button B: X+50, Y+18
Prize: X=4238, Y=7866

Button A: X+50, Y+92
Button B: X+51, Y+14
Prize: X=4905, Y=4634

Button A: X+40, Y+99
Button B: X+58, Y+40
Prize: X=2246, Y=4834

Button A: X+59, Y+64
Button B: X+94, Y+16
Prize: X=11159, Y=3680

Button A: X+19, Y+82
Button B: X+84, Y+34
Prize: X=7451, Y=7846

Button A: X+74, Y+31
Button B: X+23, Y+64
Prize: X=6201, Y=12610

Button A: X+58, Y+44
Button B: X+18, Y+85
Prize: X=6062, Y=8166

Button A: X+71, Y+41
Button B: X+30, Y+77
Prize: X=6318, Y=5200

Button A: X+12, Y+62
Button B: X+71, Y+14
Prize: X=14215, Y=1096

Button A: X+53, Y+41
Button B: X+24, Y+66
Prize: X=6682, Y=8110

Button A: X+73, Y+22
Button B: X+13, Y+44
Prize: X=10874, Y=18360

Button A: X+39, Y+56
Button B: X+34, Y+14
Prize: X=18229, Y=13962

Button A: X+84, Y+42
Button B: X+24, Y+62
Prize: X=5772, Y=5286

Button A: X+87, Y+12
Button B: X+32, Y+42
Prize: X=10514, Y=4194

Button A: X+49, Y+18
Button B: X+18, Y+51
Prize: X=14968, Y=10151

Button A: X+82, Y+20
Button B: X+75, Y+89
Prize: X=8266, Y=8804

Button A: X+17, Y+48
Button B: X+34, Y+12
Prize: X=17006, Y=12224

Button A: X+28, Y+63
Button B: X+41, Y+18
Prize: X=1281, Y=1323

Button A: X+12, Y+43
Button B: X+52, Y+15
Prize: X=13440, Y=17274

Button A: X+36, Y+94
Button B: X+71, Y+23
Prize: X=4361, Y=6353

Button A: X+57, Y+21
Button B: X+18, Y+51
Prize: X=2105, Y=18239

Button A: X+46, Y+97
Button B: X+60, Y+37
Prize: X=5748, Y=8898

Button A: X+49, Y+11
Button B: X+13, Y+43
Prize: X=14800, Y=4844

Button A: X+30, Y+68
Button B: X+63, Y+25
Prize: X=2687, Y=10971

Button A: X+13, Y+39
Button B: X+58, Y+25
Prize: X=15102, Y=7529

Button A: X+20, Y+87
Button B: X+81, Y+81
Prize: X=7301, Y=9780

Button A: X+45, Y+30
Button B: X+39, Y+85
Prize: X=6693, Y=9890

Button A: X+14, Y+40
Button B: X+68, Y+22
Prize: X=754, Y=776

Button A: X+11, Y+43
Button B: X+55, Y+33
Prize: X=6259, Y=7177

Button A: X+50, Y+11
Button B: X+39, Y+83
Prize: X=9592, Y=4010

Button A: X+27, Y+44
Button B: X+27, Y+11
Prize: X=7253, Y=19526

Button A: X+38, Y+18
Button B: X+34, Y+54
Prize: X=3490, Y=2070

Button A: X+15, Y+72
Button B: X+58, Y+16
Prize: X=1464, Y=14304

Button A: X+65, Y+11
Button B: X+20, Y+84
Prize: X=10335, Y=13317

Button A: X+57, Y+32
Button B: X+24, Y+41
Prize: X=19202, Y=15484

Button A: X+97, Y+24
Button B: X+17, Y+75
Prize: X=5373, Y=5931

Button A: X+40, Y+23
Button B: X+15, Y+35
Prize: X=15690, Y=2895

Button A: X+63, Y+83
Button B: X+68, Y+24
Prize: X=11213, Y=9001

Button A: X+16, Y+70
Button B: X+92, Y+64
Prize: X=9316, Y=8600

Button A: X+12, Y+30
Button B: X+90, Y+28
Prize: X=8286, Y=4364

Button A: X+20, Y+82
Button B: X+84, Y+51
Prize: X=5844, Y=4596

Button A: X+18, Y+68
Button B: X+82, Y+76
Prize: X=7520, Y=8304

Button A: X+12, Y+60
Button B: X+99, Y+63
Prize: X=6993, Y=7749

Button A: X+43, Y+17
Button B: X+35, Y+59
Prize: X=374, Y=12314

Button A: X+78, Y+33
Button B: X+41, Y+97
Prize: X=1588, Y=1787

Button A: X+92, Y+80
Button B: X+11, Y+63
Prize: X=7158, Y=10606

Button A: X+69, Y+42
Button B: X+25, Y+60
Prize: X=4579, Y=5922

Button A: X+92, Y+35
Button B: X+45, Y+87
Prize: X=9989, Y=9740

Button A: X+50, Y+14
Button B: X+16, Y+62
Prize: X=2112, Y=994
"""

# input = TEST_INPUT_1
input = INPUT

machines: list[dict] = list()
machine = dict()

for line in input.splitlines():
    line = line.strip()
    if not line:
        continue

    line = line.split(' ')

    if line[0] == 'Button':
        button = line[1].removesuffix(':')
        x = line[2].removeprefix('X+').removesuffix(',')
        y = line[3].removeprefix('Y+').removesuffix(',')
        machine[button] = (int(x), int(y))
        continue

    if line[0] == 'Prize:':
        x = line[1].removeprefix('X=').removesuffix(',')
        y = line[2].removeprefix('Y=').removesuffix(',')
        machine['Prize'] = (int(x), int(y))
        machines.append(machine)
        machine = dict()

STRUCT = f"""
typedef struct {{
    int xy[2];
}} xy_t;

typedef struct {{
    xy_t buttons[2];
    xy_t prize;
}} machine_t;
"""

with open(OUT_FILEPATH, 'w') as file:
    file.write(f"#ifndef {INCLUDE_GUARD_DEF}\n")
    file.write(f"#define {INCLUDE_GUARD_DEF}\n")

    file.write(f"{STRUCT}\n")

    file.write("static const machine_t MACHINES[] = {\n")

    for machine in machines:
        machine_str = "    { "
        machine_str += f"{{ {{{{ {machine['A'][0]}, {machine['A'][1]} }}}}, {{{{ {machine['B'][0]}, {machine['B'][1]} }}}} }}, "
        machine_str += f"{{{{ {machine['Prize'][0]}, {machine['Prize'][1]} }}}}"
        machine_str += " },\n"
        file.write(machine_str)

    file.write("};\n")

    file.write("\n")
    file.write(f"#endif // {INCLUDE_GUARD_DEF}\n")
