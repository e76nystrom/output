# ATMEL ATMEGA32U4 / ARDUINO LEONARDO / Flora
#
# D0			PD2			RXD1/INT2
# D1			PD3			TXD1/INT3
# D2			PD1	SDA		SDA/INT1
# D3			PD0	PWM8/SCL	OC0B/SCL/INT0
# D4	A6		PD4			ADC8
# D5			PC6	???		OC3A/#OC4A
# D6	A7		PD7	FastPWM		OC4D/ADC10
# D7			PE6			INT6/AIN0
#
# D8	A8		PB4			ADC11/PCINT4
# D9	A9		PB5	PWM16		OC1A/#OC4B/ADC12/PCINT5
# D10	A10		PB6	PWM16		OC1B/0c4B/ADC13/PCINT6
# D11			PB7	PWM8/16		0C0A/OC1C/RTS/PCINT7
# D12	A11		PD6			T1/OC4D/ADC9
# D13			PC7	PWM10		CLK0/OC4A
#
# A0	D18		PF7			ADC7
# A1	D19		PF6			ADC6
# A2	D20 		PF5			ADC5
# A3	D21 		PF4			ADC4
# A4	D22		PF1			ADC1
# A5	D23 		PF0			ADC0
#
# New pins D14..D17 to map SPI port to digital pins
#
# MISO	D14		PB3			MISO,PCINT3
# SCK	D15		PB1			SCK,PCINT1
# MOSI	D16		PB2			MOSI,PCINT2
# SS	D17		PB0			RXLED,SS/PCINT0
#
# TXLED			PD5
# RXLED			PB0
# HWB			PE2			HWB

digitalDef = \
[\
 [0, "PD3"],
 [1, "PD2"],
 [2, "PD1"],
 [3, "PD0"],
 [4, "PD4"],
 [5, "PC6"],
 [6, "PD7"],
 [7, "PE6"],

 [8, "PB4"],
 [9, "PB5"],
 [10, "PB6"],
 [11, "PB7"],
 [12, "PD6"],
 [13, "PC7"],

 [14, "PB3"],
 [15, "PB1"],
 [16, "PB2"],
 [17, "PB0"],

 [18, "PF7"],
 [19, "PF6"],
 [20, "PF5"],
 [21, "PF4"],
 [22, "PF1"],
 [23, "PF0"],
]

analogDef = \
[\
 [0, "PF7"],
 [1, "PF6"],
 [2, "PF5"],
 [3, "PF4"],
 [6, "PC4"],
 [7, "PC5"],
 [8, "PD4"],
 [10, "PD7"],
 [11, "PB4"],
 [12, "PB5"],
 [13, "PB6"],
]

altDef = \
[\
 ["INT0", "PD0"],
 ["INT1", "PD1"],
 ["INT2", "PD2"],
 ["INT3", "PD3"],

 ["TXLED", "PD5"],
 ["RXLED", "PB0"],

 ["T0", "PD7"],
 ["T1", "PD6"],

 ["CLK0", "PB0"],

 ["OC0A", "PB7"],
 ["OC0B", "PD0"],

 ["OC1A", "PB5"],
 ["OC1B", "PB6"],
 ["OC1C", "PB7"],

 ["OC3A", "PC6"],

 ["OC4A", "PC7"],
 ["OC4AC", "PC6"],
 ["OC4B", "PB6"],
 ["OC4D", "PD7"],
 ["OC4DC", "PD6"],

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
