# ATMEL ATMEGA32U4 / ARDUINO LEONARDO / Flora
#
# D0			PD2		RXD1/INT2
# D1			PD3		TXD1/INT3
# D2			PD1 SDA		SDA/INT1
# D3			PD0 PWM8/SCL	OC0B/SCL/INT0
# D4	A6		PD4		ADC8
# D5			PC6		OC3A/#OC4A
# D6	A7		PD7 FastPWM	OC4D/ADC10
# D7			PE6		INT6/AIN0
#
# D8	A8		PB4		ADC11/PCINT4
# D9	A9		PB5 PWM16	OC1A/#OC4B/ADC12/PCINT5
# D10	A10		PB6 PWM16	OC1B/0c4B/ADC13/PCINT6
# D11			PB7 PWM8/16	0C0A/OC1C/RTS/PCINT7
# D12	A11		PD6		T1/OC4D/ADC9
# D13			PC7 PWM10	CLK0/OC4A
#
# A0	D18		PF7		ADC7
# A1	D19		PF6		ADC6
# A2	D20	 	PF5		ADC5
# A3	D21 		PF4		ADC4
# A4	D22		PF1		ADC1
# A5	D23 		PF0		ADC0
#
# New pins D14..D17 to map SPI port to digital pins
#
# MISO	D14		PB3		MISO,PCINT3
# SCK	D15		PB1		SCK,PCINT1
# MOSI	D16		PB2		MOSI,PCINT2
# SS	D17		PB0		RXLED,SS/PCINT0
#
# TXLED			PD5
# RXLED			PB0
# HWB			PE2		HWB

digitalDef = \
[\
 [0, "PD3"],	# D0 - PD2
 [1, "PD2"],    # D1 - PD3
 [2, "PD1"],    # D2 - PD1
 [3, "PD0"],    # D3 - PD0
 [4, "PD4"],    # D4 - PD4
 [5, "PC6"],    # D5 - PC6
 [6, "PD7"],    # D6 - PD7
 [7, "PE6"],    # D7 - PE6

 [8, "PB4"],    # D8 - PB4
 [9, "PB5"],    # D9 - PB5
 [10, "PB6"],   # D10 - PB6
 [11, "PB7"],   # D11 - PB7 x
 [12, "PD6"],   # D12 - PD6 x
 [13, "PC7"],   # D13 - PC7 x

 [14, "PB3"],   # D14 - PB3 - MISO
 [15, "PB1"],   # D15 - PB1 - SCK
 [16, "PB2"],   # D16 - PB2 - MOSI
 [17, "PB0"],   # D17 - PB0 - SS - TX Led Yellow

 [18, "PF7"],   # D18 - PF7 - A0
 [19, "PF6"],   # D19 - PF6 - A1
 [20, "PF5"],	# D20 - PF5 - A2
 [21, "PF4"],	# D21 - PF4 - A3
 [22, "PF1"],	# D22 - PF1 - A4 x
 [23, "PF0"],	# D23 - PF0 - A5 x

 [24, "PD4"],	# D24 - PD4
 [25, "PD7"],	# D25 - PD7 - D6 - A7
 [26, "PB4"],	# D26 - PB4 - D8 - A8
 [27, "PB5"],	# D27 - PB5 - D9 - A9
 [28, "PB6"],	# D28 - PB6 - D10 - A10
 [29, "PD6"],	# D29 - PD6 - D12 - A11
 [30, "PD5"],	# D30 - PD5 - RX Led Green
]

analogDef = \
[\
 [0, "PF7"],	# A0  - D18 - PF7 - ADC7
 [1, "PF6"],	# A1  - D19 - PF6 - ADC6
 [2, "PF5"],	# A2  - D20 - PF5 - ADC5
 [3, "PF4"],	# A3  - D21 - PF4 - ADC4
 [4, "PF1"],	# A4  - D22 - PF1 - ADC1
 [5, "PF0"],	# A5  - D23 - PF0 - ADC0
 [6, "PD4"],	# A6  - D4  - PD4 - ADC8
 [7, "PD7"],	# A7  - D6  - PD7 - ADC10
 [8, "PB4"],	# A8  - D8  - PB4 - ADC11
 [9, "PB5"],	# A9  - D9  - PB5 - ADC12
 [10, "PB6"],	# A10 - D10 - PB6 - ADC13
 [11, "PD6"],	# A11 - D12 - PD6 - ADC9
]

altDef = \
[\
 ["INT0", "PD0"],
 ["INT1", "PD1"],
 ["INT2", "PD2"],
 ["INT3", "PD3"],
 ["INT6", "PE6"],

 ["TXLED", "PB0"],
 ["RXLED", "PD5"],

 ["T0", "PD7"],
 ["T1", "PD6"],

 ["CLK0", "PC7"],

 ["OC0A", "PB7"],
 ["OC0B", "PD0"],

 ["OC1A", "PB5"],
 ["OC1B", "PB6"],
 ["OC1C", "PB7"],

 ["OC3A", "PC6"],

 ["OC4A", "PC7"],
 ["OC4AN", "PC6"],
 ["OC4B", "PB6"],
 ["OC4BN", "PB5"],
 ["OC4D", "PD7"],
 ["OC4DN", "PD6"],

 ["ICP1", "PD4"],
 ["ICP3", "PC7"],

 ["PCINT0", "PB0"],
 ["PCINT1", "PB1"],
 ["PCINT2", "PB2"],
 ["PCINT3", "PB3"],
 ["PCINT4", "PB4"],
 ["PCINT5", "PB5"],
 ["PCINT6", "PB6"],
 ["PCINT7", "PB7"],

]
