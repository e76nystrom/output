#!/cygdrive/c/Python27/Python.exe

inputTest = True                # simulated inputs for testing

if inputTest:
    inTest = "in, test"
else:
    inTest = "in"

if True:
    defineMega = \
        (\
         ("INPUT_LOOP", 1),
         ("SPINDLE_PWM_TEST", 1),
         ("CHARGE_PUMP_TEST", 1),

         ("TMR2_PWM_TIMER", 1),
         ("TMR3_PWM_TIMER", 0),
        )

    pinsMega = \
        (\
         ("A",        64, "out"),
         ("B",        65, "out"),
         ("INDDX",    66, "out"),
         ("SYNC",     67, "out"),
         ("T1_PWM_A", 11, "out"), # fast pwm also
         ("T3_PWM_A",  5, "out"), # spindle pwm simulator
         ("T4_PWM_A",  6, "out"), # charge pump simulator

         ("CHG_PUMP", 20, ("exti, rising")),
         ("PWM",      21, ("exti, change")),

         ("SP_FWD",     23, inTest),
         ("SP_REV",     25, inTest),
         ("E_STOP_NO",  29, inTest),
         ("E_STOP_NC",  31, inTest),
         ("E_STOP_RST", 27, inTest + ", low"),

         ("FAST_PWM",   11, "out"),
         ("VFD_FWD",    28, "out"),
         ("VFD_REV",    30, "out"),
         ("SP_ENA",     60, "out"),
         ("E_STOP_PC",  61, "out"),
         ("E_STOP_RLY", 62, "out"),
         ("STEP_DIS",   63, "out"),
         ("W_DOG",      38, "out"),
         ("PILOT",      46, "out"),

         ("LED",        13, "out"),     # built in led
         ("T2",         68, "out"),
         ("DBG0",       32, "out"),
         ("DBG1",       33, "out"),
         ("DBG2",       34, "out"),
         ("DBG3",       35, "out"),
         ("DBG4",       36, "out"),
         ("DBG5",       37, "out"),

         ("PIN2",	14, "in"),
         ("PIN3",	10, "in"),
         ("PIN4",	12, "in"),
         ("PIN5",	15, "in"),
         ("PIN6",	14, "in"),
         ("PIN7",	17, "in"),
         ("PIN8",	16, "in"),
         ("PIN9",	22, "in"),
         ("PIN10",	24, "in"),
         ("PIN11",	26, "in"),
         ("PIN12",	59, "in"),
         ("PIN13",	58, "in"),
         ("PIN15",	2,  "in"),

         ("PIN1",	3,  "out"),
         ("PIN14",	7,  "out"),
         ("PIN16",	8,  "out"),
         ("PIN17",	9,  "out"),

         ("OUT1",	57, "out"),
         ("OUT2",	55, "out"),
         ("OUT3",	54, "out"),
         ("OUT4",	56, "out"),

         ("SW12_V1",	41, "out"),
         ("SW12_V2",	43, "out"),

      )
else:
    defineMega = \
        (\
         ("SPINDLE_PWM_TEST", 1), \
         ("CHARGE_PUMP_TEST", 1), \

         ("TMR2_PWM_TIMER", 1), \
         ("TMR3_PWM_TIMER", 0), \
        )

    pinsMega = \
        (\
         ("A",    22, "out"),
         ("B",    23, "out"),
         ("SYNC", 24, "out"),
         ("INDEX", 9, "out"),
         ("T2",    8, "out"),
         ("T1_PWM_A", 11, "out"),
         ("T3_PWM_A",  5, "out"),       # spindle pwm simulator
         ("T4_PWM_A",  6, "out"),       # charge pump simulator

         ("CHG_PUMP", 20, ("exti, rising")),
         ("PWM",      21, ("exti, change")),

         ("SP_FWD",     54, inTest),
         ("SP_REV",     55, inTest),
         ("E_STOP_NO",  56, inTest),
         ("E_STOP_NC",  57, inTest),
         ("E_STOP_RST", 58, inTest + ", low"),

         ("FAST_PWM",   11, "out"),
         ("VFD_FWD",    14, "out"),
         ("VFD_REV",    15, "out"),
         ("SP_ENA",     16, "out"),
         ("STEP_DIS",   17, "out"),
         ("E_STOP_RLY", 50, "out"),
         ("E_STOP_PC",  52, "out"),
         ("W_DOG",       2, "out"),

         ("LED",        13, "out"),     # built in led
         ("DBG0",       26, "out"),
         ("DBG1",       27, "out"),
         ("DBG2",       28, "out"),
         ("DBG3",       29, "out"),
        )

defineMini = \
(\
 ("SPINDLE_PWM_TEST", 0),
 ("CHARGE_PUMP_TEST", 0),

 ("TMR2_PWM_TIMER", 1),
 ("TMR3_PWM_TIMER", 0),
)

pinsMini = \
(\
 ("T1_PWM_A",  9, "out"),

 ("CHG_PUMP",  2, ("exti, rising")),
 ("PWM",       3, ("exti, change")),

 ("SP_FWD",      4, inTest),
 ("SP_REV",      5, inTest),
 ("E_STOP_NO",  18, inTest),
 ("E_STOP_NC",  19, inTest),
 ("E_STOP_RST",  8, inTest + ", low"),

 ("FAST_PWM",    9, "out"),
 ("VFD_FWD",     6, "out"),
 ("VFD_REV",     7, "out"),
 ("SP_ENA",     14, "out"),
 ("STEP_DIS",   15, "out"),
 ("E_STOP_RLY", 17, "out"),
 ("E_STOP_PC",  16, "out"),
 ("W_DOG",      10, "out"),

 ("LED",        -1, "out"),     # built in led
 ("T2",         -1, "out"),
 ("DBG0",       -1, "out"),
 ("DBG1",       -1, "out"),
 ("DBG2",       -1, "out"),
 ("DBG3",       -1, "out"),
)

defineMicro = \
(\
 ("SPINDLE_PWM_TEST", 0),
 ("CHARGE_PUMP_TEST", 0),

 ("TMR2_PWM_TIMER", 0),
 ("TMR3_PWM_TIMER", 1),
)

pinsMicro = \
(\
 ("T1_PWM_A",  9, "out"),

 ("CHG_PUMP",  2, ("exti, rising")),
 ("PWM",       3, ("exti, change")),

 ("SP_FWD",      4, inTest),
 ("SP_REV",      5, inTest),
 ("E_STOP_NC",  15, inTest),
 ("E_STOP_NO",  14, inTest),
 ("E_STOP_RST",  6, inTest + ", low"),

 ("FAST_PWM",    9, "out"),
 ("VFD_FWD",     7, "out"),
 ("VFD_REV",     8, "out"),
 ("STEP_DIS",   21, "out"),
 ("E_STOP_RLY", 20, "out"),
 ("SP_ENA",     19, "out"),
 ("E_STOP_PC",  18, "out"),
 ("SWITCH",     16, "out"),
 ("W_DOG",      10, "out"),

 ("LED",        30, "out"),     # built in led
 ("T2",         -1, "out"),
 ("DBG0",       -1, "out"),
 ("DBG1",       -1, "out"),
 ("DBG2",       -1, "out"),
 ("DBG3",       -1, "out"),
)

outFile = "config"

commonDefines = \
(\
 ("DEBUG", 1),                  # general debug
 ("CP_DEBUG", 1),               # charge pump debug

 ("CONSOLE", 1),                # enable debug console
 ("FLASH_STRINGS", 1),          # put strings in flash
 ("INPUT_TEST", (0, 1)[inputTest]), # simulated inputs for testing
)

configMega = {'def' : 'mega',
              'type' : 'ARDUINO_AVR_MEGA2560',
              'defines' : defineMega,
              'config' : pinsMega}

configMini = {'def' : 'mini',
              'type' : 'ARDUINO_AVR_PROMICRO',
              'defines' : defineMini,
              'config' : pinsMini}

configMicro = {'def' : 'micro32u4',
               'type' : 'ARDUINO_AVR_PROMICRO16',
               'defines' : defineMicro,
               'config' : pinsMicro}

configLeonardo = {'def' : 'micro32u4',
                  'type' : 'ARDUINO_AVR_LEONARDO',
                  'defines' : defineMicro,
                  'config' : pinsMicro}

pinConfig = (configMega, configMini, configMicro, configLeonardo)
